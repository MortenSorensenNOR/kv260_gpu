// === Tile buffer module ===:
// Tile buffer for a tile-based rasterizer implemented in UltraRAM blocks.
// Tile is 128x64 pixels, with 16 bit color depth per color channel + 24 bit
// Tile is split into four banks, where each (x,y) pixel position maps to each
// bank based on x modulo 4. This is to sustain high read throughput
// sequentially when reading scanline. Writes therefore are buffered and take
// two cycles for four pixels in a 2x2 quad, or 1 cycle for a 1x4 row (last
// one is definetly a TODO). This tradeof is made because currently (might
// change in the future) the raster frontend will not be able to sustain
// a 4 pixel/cycle throughput, but the readback will -> AXI 128 bit bus
// enables 4 32 bit rgb values per AXI beat.

`timescale 1ns / 1ps

module tile_buffer #(
    parameter int POS_ADDRW   = 8,
    parameter int TILE_WIDTH  = 128,
    parameter int TILE_HEIGHT = 128,

    parameter int URAM_SIZE   = TILE_WIDTH / 4 * TILE_HEIGHT,
    parameter int URAM_ADDRW  = $clog2(URAM_SIZE),

    parameter logic [47:0] INITIAL_CLEAR_COLOR = 0,
    parameter logic [23:0] INITIAL_CLEAR_DEPTH = 24'hFFFFFF
) (
    input logic clk,
    input logic rstn,

    output logic ready,

    // Write port (2x2 quad) - takes 2 cycles
    // Cycle 1: pixels (x, y) and (x+1, y)
    // Cycle 2: pixels (x, y+1) and (x+1, y+1)
    input logic [POS_ADDRW-1:0] i_write_x,  // Must be even
    input logic [POS_ADDRW-1:0] i_write_y,  // Row to write (can be any value)
    input logic [71:0]          i_pixel_data [2], // [0]=(x,y), [1]=(x+1,y)
    input logic [1:0]           i_write_mask,
    input logic                 i_write_valid,

    // Read port (4 sequential pixels) - 1 cycle
    input  logic [POS_ADDRW-1:0] i_read_x,  // Must be aligned to 4 (x % 4 == 0)
    input  logic [POS_ADDRW-1:0] i_read_y,
    input  logic                 i_read_valid,
    output logic [71:0]          o_read_data[4], // [0]=x, [1]=x+1, [2]=x+2, [3]=x+3
    output logic                 o_read_valid,

    // Clear interface
    input  logic        i_clear,
    input  logic [23:0] i_clear_depth,
    input  logic [47:0] i_clear_color,
    output logic        o_clear_done
);
    typedef logic [POS_ADDRW-1:0]  pos_addr_t;
    typedef logic [URAM_ADDRW-1:0] uram_addr_t;

    // =========================================================================
    // URAM declarations - 4 banks by (x % 4)
    // Bank 0: x = 0, 4, 8, 12, ...
    // Bank 1: x = 1, 5, 9, 13, ...
    // Bank 2: x = 2, 6, 10, 14, ...
    // Bank 3: x = 3, 7, 11, 15, ...
    // =========================================================================
    (* ram_style = "ultra", rw_addr_collision = "no" *) logic [71:0] URAM_BANK0 [URAM_SIZE];
    (* ram_style = "ultra", rw_addr_collision = "no" *) logic [71:0] URAM_BANK1 [URAM_SIZE];
    (* ram_style = "ultra", rw_addr_collision = "no" *) logic [71:0] URAM_BANK2 [URAM_SIZE];
    (* ram_style = "ultra", rw_addr_collision = "no" *) logic [71:0] URAM_BANK3 [URAM_SIZE];

    // State machine
    typedef enum logic [1:0] {
        READY,
        CLEARING
    } state_t;
    state_t state;

    // Clear counters - iterate over bank address space
    logic [URAM_ADDRW-1:0] clear_addr;
    logic [71:0] clear_data;

    // =========================================================================
    // Address calculation
    // 
    // Memory layout per bank:
    //   addr = y * (TILE_WIDTH / 4) + (x / 4)
    //
    // For write at (x, y) where x is even:
    //   x % 4 == 0: Bank 0 gets (x, y),   Bank 1 gets (x+1, y)
    //   x % 4 == 2: Bank 2 gets (x, y),   Bank 3 gets (x+1, y)
    //
    // For read at (x, y) where x % 4 == 0:
    //   Bank 0 gets x, Bank 1 gets x+1, Bank 2 gets x+2, Bank 3 gets x+3
    //   All at same address: y * (TILE_WIDTH / 4) + (x / 4)
    // =========================================================================
    
    // Write address calculation
    logic [URAM_ADDRW-1:0] wr_addr;
    logic                  wr_x_bit1;  // Bit 1 of x determines which bank pair (0,1) or (2,3)
    
    always_comb begin
        wr_addr   = URAM_ADDRW'(i_write_y) * URAM_ADDRW'(TILE_WIDTH / 4) + URAM_ADDRW'(i_write_x >> 2);
        wr_x_bit1 = i_write_x[1];  // 0 = banks 0,1 | 1 = banks 2,3
    end

    // Read address calculation
    logic [URAM_ADDRW-1:0] rd_addr;
    
    always_comb begin
        rd_addr = URAM_ADDRW'(i_read_y) * URAM_ADDRW'(TILE_WIDTH / 4) + URAM_ADDRW'(i_read_x >> 2);
    end

    // Per-bank control signals
    logic                  bank0_we, bank1_we, bank2_we, bank3_we;
    logic [URAM_ADDRW-1:0] bank0_wr_addr, bank1_wr_addr, bank2_wr_addr, bank3_wr_addr;
    logic [71:0]           bank0_wr_data, bank1_wr_data, bank2_wr_data, bank3_wr_data;
    logic [URAM_ADDRW-1:0] bank0_rd_addr, bank1_rd_addr, bank2_rd_addr, bank3_rd_addr;

    always_comb begin
        // Defaults
        bank0_we = 1'b0;
        bank1_we = 1'b0;
        bank2_we = 1'b0;
        bank3_we = 1'b0;

        bank0_wr_addr = '0;
        bank1_wr_addr = '0;
        bank2_wr_addr = '0;
        bank3_wr_addr = '0;

        bank0_wr_data = '0;
        bank1_wr_data = '0;
        bank2_wr_data = '0;
        bank3_wr_data = '0;

        bank0_rd_addr = '0;
        bank1_rd_addr = '0;
        bank2_rd_addr = '0;
        bank3_rd_addr = '0;

        case (state)
            CLEARING: begin
                // Write same clear value to all banks at same address
                bank0_we = 1'b1;
                bank1_we = 1'b1;
                bank2_we = 1'b1;
                bank3_we = 1'b1;

                bank0_wr_addr = clear_addr;
                bank1_wr_addr = clear_addr;
                bank2_wr_addr = clear_addr;
                bank3_wr_addr = clear_addr;

                bank0_wr_data = clear_data;
                bank1_wr_data = clear_data;
                bank2_wr_data = clear_data;
                bank3_wr_data = clear_data;
            end

            READY: begin
                if (i_write_valid) begin
                    // Write 2 pixels based on x alignment
                    // x[1] == 0: write to banks 0, 1
                    // x[1] == 1: write to banks 2, 3
                    if (wr_x_bit1 == 1'b0) begin
                        bank0_we      = i_write_mask[0];
                        bank0_wr_addr = wr_addr;
                        bank0_wr_data = i_pixel_data[0];

                        bank1_we      = i_write_mask[1];
                        bank1_wr_addr = wr_addr;
                        bank1_wr_data = i_pixel_data[1];
                    end else begin
                        bank2_we      = i_write_mask[0];
                        bank2_wr_addr = wr_addr;
                        bank2_wr_data = i_pixel_data[0];

                        bank3_we      = i_write_mask[1];
                        bank3_wr_addr = wr_addr;
                        bank3_wr_data = i_pixel_data[1];
                    end
                end

                // Read addresses - always set for read port
                bank0_rd_addr = rd_addr;
                bank1_rd_addr = rd_addr;
                bank2_rd_addr = rd_addr;
                bank3_rd_addr = rd_addr;
            end

            default: begin
                // Keep defaults
            end
        endcase
    end

    // URAM instances - Simple Dual Port (write port + read port)
    logic [71:0] bank0_rd_data, bank1_rd_data, bank2_rd_data, bank3_rd_data;

    // Bank 0 - Write port
    always_ff @(posedge clk) begin
        if (bank0_we) begin
            URAM_BANK0[bank0_wr_addr] <= bank0_wr_data;
        end
    end
    // Bank 0 - Read port
    always_ff @(posedge clk) begin
        bank0_rd_data <= URAM_BANK0[bank0_rd_addr];
    end

    // Bank 1 - Write port
    always_ff @(posedge clk) begin
        if (bank1_we) begin
            URAM_BANK1[bank1_wr_addr] <= bank1_wr_data;
        end
    end
    // Bank 1 - Read port
    always_ff @(posedge clk) begin
        bank1_rd_data <= URAM_BANK1[bank1_rd_addr];
    end

    // Bank 2 - Write port
    always_ff @(posedge clk) begin
        if (bank2_we) begin
            URAM_BANK2[bank2_wr_addr] <= bank2_wr_data;
        end
    end
    // Bank 2 - Read port
    always_ff @(posedge clk) begin
        bank2_rd_data <= URAM_BANK2[bank2_rd_addr];
    end

    // Bank 3 - Write port
    always_ff @(posedge clk) begin
        if (bank3_we) begin
            URAM_BANK3[bank3_wr_addr] <= bank3_wr_data;
        end
    end
    // Bank 3 - Read port
    always_ff @(posedge clk) begin
        bank3_rd_data <= URAM_BANK3[bank3_rd_addr];
    end

    // Read output - direct mapping (1 cycle latency from URAM)
    logic read_valid_d1;

    always_ff @(posedge clk) begin
        if (~rstn) begin
            read_valid_d1 <= 1'b0;
        end else begin
            read_valid_d1 <= i_read_valid && (state == READY);
        end
    end

    assign o_read_valid   = read_valid_d1;
    assign o_read_data[0] = bank0_rd_data;
    assign o_read_data[1] = bank1_rd_data;
    assign o_read_data[2] = bank2_rd_data;
    assign o_read_data[3] = bank3_rd_data;

    // State machine and clear logic
    always_ff @(posedge clk) begin
        if (~rstn) begin
            state      <= CLEARING;
            clear_addr <= '0;
            clear_data <= {INITIAL_CLEAR_COLOR, INITIAL_CLEAR_DEPTH};
        end else begin
            case (state)
                READY: begin
                    if (i_clear) begin
                        state      <= CLEARING;
                        clear_addr <= '0;
                        clear_data <= {i_clear_color, i_clear_depth};
                    end
                end

                CLEARING: begin
                    // Clear one address per cycle (covers all 4 banks)
                    if (clear_addr >= URAM_ADDRW'(URAM_SIZE - 1)) begin
                        clear_addr <= '0;
                        state      <= READY;
                    end else begin
                        clear_addr <= clear_addr + 1;
                    end
                end

                default: begin
                    state <= READY;
                end
            endcase
        end
    end

    // Output status
    assign ready = (state == READY);

    always_ff @(posedge clk) begin
        if (~rstn) begin
            o_clear_done <= 1'b0;
        end else begin
            o_clear_done <= (state == CLEARING) && (clear_addr >= URAM_ADDRW'(URAM_SIZE - 1));
        end
    end

endmodule
