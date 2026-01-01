// === Tile buffer module ===:
// Tile buffer for a tile-based rasterizer implemented in UltraRAM blocks.
// Tile is 128x64 pixels, with 16 bit color depth per color channel + 24 bit
// depth value. Module supports four simultanious writes and reads, where
// writes are assumed to be in a 2x2 tile 
//     (x, y)   (x + 1, y)
//     (x, y+1) (x + 1, y + 1)
// with an accompanying 4 bit flag for which values are valid, i_write_tvalid,
// whilst reads are assumed to be sequential
//    Bank 0:
//        (x, y)   (x + 2, y)
//    Bank 1: 
//        (x+1, y) (x + 3, y)
//
// Reads and writes are assumed (for simplicity of the interface) to not
// happen at the same time. TODO: Remove this assumption in the implementation

`timescale 1ns / 1ps

module tile_buffer #(
    parameter int POS_ADDRW   = 8,
    parameter int TILE_WIDTH  = 128,
    parameter int TILE_HEIGHT = 64,

    parameter int URAM_SIZE   = TILE_WIDTH / 2 * TILE_HEIGHT,
    parameter int URAM_ADDRW  = $clog2(URAM_SIZE),

    parameter logic [47:0] INITIAL_CLEAR_COLOR = 0,
    parameter logic [23:0] INITIAL_CLEAR_DEPTH = 24'hFFFFFF
) (
    input logic clk,
    input logic rstn,

    output logic ready, // Not clearing data

    input logic [POS_ADDRW-1:0] i_write_x,
    input logic [POS_ADDRW-1:0] i_write_y,
    input logic [71:0]          i_pixel_data [4], // (x, y), (x+1, y), (x, y+1), (x+1, y+1)
    input logic [3:0]           i_write_mask,     // ---"---
    input logic                 i_write_valid,

    input  logic [POS_ADDRW-1:0] i_read_x,
    input  logic [POS_ADDRW-1:0] i_read_y,
    input  logic                 i_read_valid,
    output logic [71:0]          o_read_data[4], // (x, y), (x+1, y), (x+2, y), (x+3, y)
    output logic                 o_read_valid,

    input  logic        i_clear,
    input  logic [23:0] i_clear_depth,
    input  logic [47:0] i_clear_color,
    output logic        o_clear_done
);
    typedef logic [POS_ADDRW-1:0]  pos_addr_t;
    typedef logic [URAM_ADDRW-1:0] uram_addr_t;

    localparam int COLOR_WIDTH = 48;
    localparam int DEPTH_WIDTH = 24;
    
    // UltraRAM blocks
    logic [COLOR_WIDTH + DEPTH_WIDTH - 1 : 0] URAM_BANK0 [URAM_SIZE]; // Even x-pos (* ram_style = "ultra" *) 
    logic [COLOR_WIDTH + DEPTH_WIDTH - 1 : 0] URAM_BANK1 [URAM_SIZE]; // Odd  x-pos (* ram_style = "ultra" *) 

    // Initial clear at device start
    initial begin
        foreach (URAM_BANK0[i]) URAM_BANK0[i] = {INITIAL_CLEAR_COLOR, INITIAL_CLEAR_DEPTH};
        foreach (URAM_BANK1[i]) URAM_BANK1[i] = {INITIAL_CLEAR_COLOR, INITIAL_CLEAR_DEPTH};
    end

    // State
    typedef enum logic [0:0] {
        READY,
        CLEARING
    } state_t;
    state_t state;

    // Write address logic
    logic [POS_ADDRW-1:0] clear_x, clear_y;
    logic [23:0] clear_depth;
    logic [47:0] clear_color;

    logic [POS_ADDRW-1:0]  write_x, write_y;
    logic [URAM_ADDRW-1:0] write_y_line;
    logic [URAM_ADDRW-1:0] write_pos_tl;
    logic [URAM_ADDRW-1:0] write_addr [4];

    always_comb begin
        case (state)
            CLEARING: begin
                write_x = clear_x; 
                write_y = clear_y; 
            end

            default: begin
                write_x = i_write_x >> 1; // x pos is assumed to be even
                write_y = i_write_y;
            end
        endcase

        write_y_line = uram_addr_t'((TILE_WIDTH/2) * write_y);
        write_pos_tl = write_y_line + uram_addr_t'(write_x);
    end

    always_comb begin
        case (state)
            READY: begin
                write_addr[0] = write_pos_tl;                              // (x, y)      Bank0
                write_addr[1] = write_pos_tl;                              // (x+1, y)    Bank1

                write_addr[2] = write_pos_tl + uram_addr_t'(TILE_WIDTH/2); // (x, y+1)    Bank0
                write_addr[3] = write_pos_tl + uram_addr_t'(TILE_WIDTH/2); // (x+1, y+1)  Bank1
            end

            CLEARING: begin
                write_addr[0] = write_pos_tl; // (x, y)     Bank0
                write_addr[1] = write_pos_tl; // (x + 1, y) Bank1

                write_addr[2] = write_pos_tl + 1; // (x + 2, y) Bank0
                write_addr[3] = write_pos_tl + 1; // (x + 3, y) Bank1
            end

            default: begin
                foreach (write_addr[i]) write_addr[i] = '0;
            end
        endcase
    end

    // Read access logic
    logic [POS_ADDRW-1:0]  read_x;
    logic [URAM_ADDRW-1:0] read_y_line;
    logic [URAM_ADDRW-1:0] read_pos_tl;
    logic [URAM_ADDRW-1:0] read_addr [4];

    always_comb begin
        read_x = i_read_x >> 1;
        read_y_line = uram_addr_t'((TILE_WIDTH/2) * i_read_y);
        read_pos_tl = read_y_line + uram_addr_t'(read_x);

        read_addr[0] = read_pos_tl;
        read_addr[1] = read_pos_tl;

        if (read_x == pos_addr_t'(TILE_WIDTH/2)) begin
            // Clamp to edge (try to avoid) - will look odd due to odd and
            // even bank mapping clamp to last and second to last value
            read_addr[2] = read_pos_tl;
            read_addr[3] = read_pos_tl;
        end else begin
            read_addr[2] = read_pos_tl+1;
            read_addr[3] = read_pos_tl+1;
        end
    end

    always_ff @(posedge clk) begin
        if (~rstn) begin
            state <= CLEARING;

            clear_x <= '0;
            clear_y <= '0;
            clear_depth <= INITIAL_CLEAR_DEPTH;
            clear_color <= INITIAL_CLEAR_COLOR;
        end else begin
            case (state)
                READY: begin
                    if (i_write_valid) begin
                        if (i_write_mask[0]) begin
                            URAM_BANK0[write_addr[0]] <= i_pixel_data[0];
                        end

                        if (i_write_mask[1]) begin
                            URAM_BANK1[write_addr[1]] <= i_pixel_data[1];
                        end

                        if (i_write_mask[2]) begin
                            URAM_BANK0[write_addr[2]] <= i_pixel_data[2];
                        end

                        if (i_write_mask[3]) begin
                            URAM_BANK1[write_addr[3]] <= i_pixel_data[3];
                        end

                        foreach (o_read_data[i]) o_read_data[i] <= '0;
                        o_read_valid <= 1'b0;
                    end else if (i_read_valid) begin
                        o_read_data[0] <= URAM_BANK0[read_addr[0]];
                        o_read_data[1] <= URAM_BANK1[read_addr[1]];
                        o_read_data[2] <= URAM_BANK0[read_addr[2]];
                        o_read_data[3] <= URAM_BANK1[read_addr[3]];
                        o_read_valid <= 1'b1;
                    end else begin
                        foreach (o_read_data[i]) o_read_data[i] <= '0;
                        o_read_valid <= 1'b0;
                    end

                    if (i_clear) begin
                        state <= CLEARING;

                        clear_color <= i_clear_color;
                        clear_depth <= i_clear_depth;
                    end
                end

                CLEARING: begin
                    if (clear_x >= pos_addr_t'(TILE_WIDTH/2 - 2)) begin
                        if (clear_y == pos_addr_t'(TILE_HEIGHT - 1)) begin
                            clear_x <= '0;
                            clear_y <= '0;

                            state <= READY; // Finished clearing
                        end else begin
                            clear_x <= '0;
                            clear_y <= clear_y + 1;
                        end
                    end else begin
                        clear_x <= clear_x + 2;
                        clear_y <= clear_y;
                    end

                    // Clear to specified values. Bank0 has all even x-values 
                    // and Bank1 has all odd values. clear_x is iterated until 
                    // TILE_WIDTH/2 - 2 -> last two x-values of each bank.
                    URAM_BANK0[write_addr[0]] <= {clear_color, clear_depth};
                    URAM_BANK1[write_addr[1]] <= {clear_color, clear_depth};
                    URAM_BANK0[write_addr[2]] <= {clear_color, clear_depth};
                    URAM_BANK1[write_addr[3]] <= {clear_color, clear_depth};
                end

                default: begin
                    state <= READY;
                end
            endcase
        end
    end

    // Ready logic
    always_comb begin
        ready = ~(state == CLEARING);
    end

    always_ff @(posedge clk) begin
        if (~rstn) begin
            o_clear_done <= 1'b0;
        end else begin
            if (state == CLEARING) begin
                if ((clear_x >= pos_addr_t'(TILE_WIDTH/2 - 2)) && (clear_y == pos_addr_t'(TILE_HEIGHT - 1))) begin
                    o_clear_done <= 1'b1;
                end
            end else begin
                o_clear_done <= 1'b0;
            end
        end
    end

    endmodule
