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
    parameter int TILE_HEIGHT = 64,

    parameter int URAM_SIZE   = (TILE_WIDTH / 2) * (TILE_HEIGHT / 2),
    parameter int URAM_ADDRW  = $clog2(URAM_SIZE),

    parameter logic [47:0] INITIAL_CLEAR_COLOR = 0,
    parameter logic [23:0] INITIAL_CLEAR_DEPTH = 24'hFFFFFF
) (
    input logic clk,
    input logic rstn,

    output logic ready,

    // Write port (2x2 quad) - 1 cycle, 4 pixels
    // (x, y) must both be even - TODO: Allow odd x and y
    input logic [POS_ADDRW-1:0] i_write_x,
    input logic [POS_ADDRW-1:0] i_write_y,
    input logic [71:0]          i_pixel_data [4], // [0]=(x,y), [1]=(x+1,y), [2]=(x,y+1), [3]=(x+1,y+1)
    input logic [3:0]           i_write_mask,
    input logic                 i_write_valid,

    // Read port (2x2 quad) - 1 cycle, 4 pixels
    // (x, y) must both be even - TODO: Allow odd x and y
    input  logic [POS_ADDRW-1:0] i_read_x,  // Must be even
    input  logic [POS_ADDRW-1:0] i_read_y,  // Must be even
    input  logic                 i_read_valid,
    output logic [71:0]          o_read_data[4],
    output logic                 o_read_valid,

    // Clear interface
    input  logic        i_clear,
    input  logic [23:0] i_clear_depth,
    input  logic [47:0] i_clear_color,
    output logic        o_clear_done
);

    // =========================================================================
    // URAM declarations - 4 banks by (X parity, Y parity)
    // Bank 0: even X, even Y  -> (0,0), (2,0), (0,2), (2,2), ...
    // Bank 1: odd X,  even Y  -> (1,0), (3,0), (1,2), (3,2), ...
    // Bank 2: even X, odd Y   -> (0,1), (2,1), (0,3), (2,3), ...
    // Bank 3: odd X,  odd Y   -> (1,1), (3,1), (1,3), (3,3), ...
    // =========================================================================
    (* ram_style = "ultra", rw_addr_collision = "no" *) logic [71:0] URAM_BANK0 [URAM_SIZE];
    (* ram_style = "ultra", rw_addr_collision = "no" *) logic [71:0] URAM_BANK1 [URAM_SIZE];
    (* ram_style = "ultra", rw_addr_collision = "no" *) logic [71:0] URAM_BANK2 [URAM_SIZE];
    (* ram_style = "ultra", rw_addr_collision = "no" *) logic [71:0] URAM_BANK3 [URAM_SIZE];

    // State machine
    typedef enum logic {
        READY,
        CLEARING
    } state_t;
    state_t state;

    // Clear counter
    logic [URAM_ADDRW-1:0] clear_addr;
    logic [71:0] clear_data;

    // =========================================================================
    // Address calculation
    // 
    // For (X parity, Y parity) banking:
    //   addr = (y / 2) * (TILE_WIDTH / 2) + (x / 2)
    //
    // Both write and read are 2x2 quads at (x, y) where both are even:
    //   All 4 pixels map to SAME address in their respective banks
    //   Bank 0: (x, y)     -> addr
    //   Bank 1: (x+1, y)   -> addr  
    //   Bank 2: (x, y+1)   -> addr
    //   Bank 3: (x+1, y+1) -> addr
    // =========================================================================
    
    // Write address - same for all banks
    logic [URAM_ADDRW-1:0] wr_addr;
    always_comb begin
        wr_addr = URAM_ADDRW'(i_write_y >> 1) * URAM_ADDRW'(TILE_WIDTH / 2) + URAM_ADDRW'(i_write_x >> 1);
    end

    // Read address - same for all banks (2x2 quad read)
    logic [URAM_ADDRW-1:0] rd_addr;
    always_comb begin
        rd_addr = URAM_ADDRW'(i_read_y >> 1) * URAM_ADDRW'(TILE_WIDTH / 2) + URAM_ADDRW'(i_read_x >> 1);
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
                    // Write 2x2 quad
                    // TODO: Allow i_write_x to be odd -> bank0 and bank2 must get 1 added to the 
                    // write address (and similarly for the read address)
                    bank0_we      = i_write_mask[0];
                    bank0_wr_addr = wr_addr;
                    bank0_wr_data = i_pixel_data[0];  // (x, y)

                    bank1_we      = i_write_mask[1];
                    bank1_wr_addr = wr_addr;
                    bank1_wr_data = i_pixel_data[1];  // (x+1, y)

                    bank2_we      = i_write_mask[2];
                    bank2_wr_addr = wr_addr;
                    bank2_wr_data = i_pixel_data[2];  // (x, y+1)

                    bank3_we      = i_write_mask[3];
                    bank3_wr_addr = wr_addr;
                    bank3_wr_data = i_pixel_data[3];  // (x+1, y+1)
                end

                // Read 2x2 quad
                bank0_rd_addr = rd_addr;
                bank1_rd_addr = rd_addr;
                bank2_rd_addr = rd_addr;
                bank3_rd_addr = rd_addr;
            end

            default: begin end
        endcase
    end

    // URAM SDP
    logic [71:0] bank0_rd_data, bank1_rd_data, bank2_rd_data, bank3_rd_data;

    // Bank 0
    always_ff @(posedge clk) begin
        if (bank0_we) begin
            URAM_BANK0[bank0_wr_addr] <= bank0_wr_data;
        end
        bank0_rd_data <= URAM_BANK0[bank0_rd_addr];
    end

    // Bank 1
    always_ff @(posedge clk) begin
        if (bank1_we) begin
            URAM_BANK1[bank1_wr_addr] <= bank1_wr_data;
        end
        bank1_rd_data <= URAM_BANK1[bank1_rd_addr];
    end

    // Bank 2
    always_ff @(posedge clk) begin
        if (bank2_we) begin
            URAM_BANK2[bank2_wr_addr] <= bank2_wr_data;
        end
        bank2_rd_data <= URAM_BANK2[bank2_rd_addr];
    end

    // Bank 3
    always_ff @(posedge clk) begin
        if (bank3_we) begin
            URAM_BANK3[bank3_wr_addr] <= bank3_wr_data;
        end
        bank3_rd_data <= URAM_BANK3[bank3_rd_addr];
    end

    // Read output
    logic read_valid_d1;
    always_ff @(posedge clk) begin
        if (~rstn) begin
            read_valid_d1 <= 1'b0;
        end else begin
            read_valid_d1 <= i_read_valid && (state == READY);
        end
    end

    assign o_read_valid   = read_valid_d1;
    assign o_read_data[0] = bank0_rd_data;  // (x, y)     - even X, even Y
    assign o_read_data[1] = bank1_rd_data;  // (x+1, y)   - odd X,  even Y
    assign o_read_data[2] = bank2_rd_data;  // (x, y+1)   - even X, odd Y
    assign o_read_data[3] = bank3_rd_data;  // (x+1, y+1) - odd X,  odd Y

    // State machine
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
