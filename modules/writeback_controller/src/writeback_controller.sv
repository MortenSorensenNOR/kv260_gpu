// Controller for reading out of the tile buffer and writing back to
// framebuffer in main system memory through the decicated HP AXI port.
// Module assumes (for now) that the burst size of the AXI port is euqal to
// the number of beats (128 bit packets) of two rows of the tile buffer. With
// tile size of 128x128 and XRGB8888 pixel format and a AXI bus width of 128
// bits that is 64 beats per burst.
//
// For now we are also assuming that the tile buffer read has a delay of only
// one cycle. In the future if this changes the logic will have to change to
// await an actual i_read_valid
//
// Also, currently the tile buffer color data is Q8.8 per RGB color channel.
// This might change to a Q0.16 at some point to simply facilitate normalized
// color. That would mean that this module would be responsible for color
// channel conversion back to XRGB8888 when writing back to the framebuffer.

`timescale 1ns / 1ps

module writeback_controller #(
    parameter int POS_ADDRW   = 8,
    parameter int TILE_WIDTH  = 128,
    parameter int TILE_HEIGHT = 128,

    parameter int BURST_SIZE = 64,
    parameter int BURST_BITS = $clog2(BURST_SIZE)
) (
    input logic clk,
    input logic rstn,

    // Ctrl
    output logic writeback_ready,
    input  logic writeback_start,
    output logic writeback_done,

    // Controller to tile
    output logic o_read_start,  // Indicate to the tile buffer that we wish to start writeback
    output logic o_read_done,  // Indicate to the tile buffer that writeback has finished -> next tile rendering can take place

    output logic [POS_ADDRW-1:0] o_read_pos_x,  // Default read is 2x2 quad (assumed x even)
    output logic [POS_ADDRW-1:0] o_read_pos_y,  // Default read is 2x2 quad (assumed y even)
    output logic                 o_read_en,

    input logic        i_read_ready,
    input logic [71:0] i_read_data [4],
    input logic        i_read_valid,

    // Controller to AXI
    input  logic         i_write_ready,
    output logic [127:0] o_write_data,
    output logic         o_write_valid

    // Not necessary since burst size is equal to the size of two rows (when combined into 128 bit beats
    // output logic                  o_fifo_full_write, // Does the FIFO buffer have at least BURST_SIZE elements ready?
    // output logic                  o_flush,           // o_read_done has been signaled and we need to flush out the last of the fifo -> burst of size < BURST_SIZEe
    // output logic [burst_cntr_t-1:0] o_flush_size       // Number of bytes in the output flush
);
    // State
    typedef enum logic [2:0] {
        IDLE,
        READ_ROW,         // Read every value inside one row of the tile buffer -> gives 2x2 quad -> two rows of data
        READ_SECOND_QUAD, // Read second set of 2x2 pixels to create the two 4x pixel rows. Since we write 128 bits per beat we have 4 pixels, meaning two 2x2 reads per 4 pixels
        WRITE_BACK,  // Finished reading the two rows -> start AXI transaction
        DONE
    } state_t;
    state_t state, next_state;

    // Reads are 2x2 quads so two reads are needed for one FIFO element of 4x pixels
    // Buffer the previous read to combine the two reads into two (4,1) pixel segments
    logic [71:0] pixel_read_buffer[4];
    always_ff @(posedge clk) begin
        if (~rstn) begin
            foreach (pixel_read_buffer[i]) pixel_read_buffer[i] <= '0;
        end else begin
            if (i_read_valid) begin
                foreach (pixel_read_buffer[i]) pixel_read_buffer[i] <= i_read_data[i];
            end
        end
    end

    // Split FIFO into two banks, for even and odd rows of the tile buffer data
    // Because reads are done in 2x2 quads the data has to be buffered into two 
    // rows to avoid double reads of rows.   
    localparam int FIFO_depth = int'($ceil(TILE_WIDTH / 4));

    logic [127:0] fifo_bank0_write_data;
    logic         fifo_bank0_write_en;
    logic [127:0] fifo_bank1_write_data;
    logic         fifo_bank1_write_en;

    logic [127:0] fifo_bank0_read_data;
    logic         fifo_bank0_read_en;
    logic [127:0] fifo_bank1_read_data;
    logic         fifo_bank1_read_en;

    logic         fifo_bank0_empty;
    logic         fifo_bank0_full;
    logic         fifo_bank1_empty;
    logic         fifo_bank1_full;

    fifo #(
        .DEPTH(FIFO_depth),
        .DWIDTH(128)  // 4x 32 bit pixel data XRGB8888
    ) pixel_fifo_bank0 (
        .clk  (clk),
        .rstn (rstn),
        .din  (fifo_bank0_write_data),
        .wr_en(fifo_bank0_write_en),
        .dout (fifo_bank0_read_data),
        .rd_en(fifo_bank0_read_en),
        .empty(fifo_bank0_empty),
        .full (fifo_bank0_full)
    );

    fifo #(
        .DEPTH(FIFO_depth),
        .DWIDTH(128)  // 4x 32 bit pixel data XRGB8888
    ) pixel_fifo_bank1 (
        .clk  (clk),
        .rstn (rstn),
        .din  (fifo_bank1_write_data),
        .wr_en(fifo_bank1_write_en),
        .dout (fifo_bank1_read_data),
        .rd_en(fifo_bank1_read_en),
        .empty(fifo_bank1_empty),
        .full (fifo_bank1_full)
    );

    // Write logic
    typedef logic [BURST_BITS:0] burst_cntr_t;
    burst_cntr_t burst_idx;
    logic axi_write_bank_select;

    logic [31:0] pixel_rgba_row0[4];
    logic [31:0] pixel_rgba_row1[4];
    always_comb begin
        // R, G, B, A=0xff (currently no alpha value in tile buffer -> could add)
        pixel_rgba_row0[0] = {
            8'hFF, pixel_read_buffer[0][71:64], pixel_read_buffer[0][55:48], pixel_read_buffer[0][39:32]
        };
        pixel_rgba_row0[1] = {
            8'hFF, pixel_read_buffer[1][71:64], pixel_read_buffer[1][55:48], pixel_read_buffer[1][39:32]
        };
        pixel_rgba_row0[2] = {
            8'hFF, i_read_data[0][71:64], i_read_data[0][55:48], i_read_data[0][39:32]
        };
        pixel_rgba_row0[3] = {
            8'hFF, i_read_data[1][71:64], i_read_data[1][55:48], i_read_data[1][39:32]
        };

        pixel_rgba_row1[0] = {
            8'hFF, pixel_read_buffer[2][71:64], pixel_read_buffer[2][55:48], pixel_read_buffer[2][39:32]
        };
        pixel_rgba_row1[1] = {
            8'hFF, pixel_read_buffer[3][71:64], pixel_read_buffer[3][55:48], pixel_read_buffer[3][39:32]
        };
        pixel_rgba_row1[2] = {
            8'hFF, i_read_data[2][71:64], i_read_data[2][55:48], i_read_data[2][39:32]
        };
        pixel_rgba_row1[3] = {
            8'hFF, i_read_data[3][71:64], i_read_data[3][55:48], i_read_data[3][39:32]
        };

        fifo_bank0_write_data = {
            pixel_rgba_row0[0], pixel_rgba_row0[1], pixel_rgba_row0[2], pixel_rgba_row0[3]
        };
        fifo_bank1_write_data = {
            pixel_rgba_row1[0], pixel_rgba_row1[1], pixel_rgba_row1[2], pixel_rgba_row1[3]
        };
    end

    // Tile buffer read logic
    logic [POS_ADDRW-1:0] read_pos_x;
    logic [POS_ADDRW-1:0] read_pos_y;
    logic                 read_en;

    // State machine
    always_ff @(posedge clk) begin
        if (~rstn) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    always_comb begin
        next_state = state;
        writeback_ready = 1'b0;

        case (state)
            IDLE: begin
                if (writeback_start) begin
                    next_state = READ_ROW;
                end
                writeback_ready = 1'b1;
            end

            READ_ROW: begin
                if (~fifo_bank0_full) begin
                    next_state = READ_SECOND_QUAD;
                end
            end

            READ_SECOND_QUAD: begin
                if (read_pos_x == POS_ADDRW'(TILE_WIDTH - 2)) begin
                    next_state = WRITE_BACK;
                end else begin
                    next_state = READ_ROW;
                end
            end

            WRITE_BACK: begin
                // Something something has started writing values -> start
                // reading in the next row into fifo
                if (burst_idx >= burst_cntr_t'(BURST_SIZE)) begin
                    if (read_pos_y < POS_ADDRW'(TILE_HEIGHT - 2)) begin
                        // Want to start reading on the next y row
                        next_state = READ_ROW;
                    end else begin
                        next_state = DONE;
                    end
                end
            end

            DONE: begin
                next_state = IDLE;
            end

            default: begin
                next_state = IDLE;
            end
        endcase
    end

    always_ff @(posedge clk) begin
        if (~rstn) begin
            read_pos_x <= '0;
            read_pos_y <= '0;
            read_en <= '0;
            o_read_start <= '0;

            fifo_bank0_read_en <= '0;
            fifo_bank1_read_en <= '0;
            burst_idx <= '0;
            axi_write_bank_select <= '0;
        end else begin
            case (state)
                IDLE: begin
                    if (writeback_start) begin
                        // Assuming that the tile buffer starts at ready (TODO: maybe fix this assumption?)
                        read_en <= 1;
                        o_read_start <= 1;
                    end else begin
                        read_en <= 0;
                        o_read_start <= '0;
                    end

                    read_pos_x <= '0;
                    read_pos_y <= '0;
                    writeback_done <= 1'b0;
                    o_read_done <= 1'b0;

                    fifo_bank0_read_en <= '0;
                    fifo_bank1_read_en <= '0;
                    burst_idx <= '0;
                    axi_write_bank_select <= '0;

                    o_write_valid <= '0;
                end

                READ_ROW: begin
                    o_read_start <= 0;

                    if (~fifo_bank0_full) begin
                        // We read (x, y) at this state
                        // Setup read for next state (READ_SECOND_QUAD)
                        read_pos_x <= read_pos_x + 2;
                        read_en    <= 1;
                        fifo_bank0_write_en <= 1;
                        fifo_bank1_write_en <= 1;
                    end
                end

                READ_SECOND_QUAD: begin
                    if (read_pos_x == POS_ADDRW'(TILE_WIDTH - 2)) begin
                        read_pos_x <= 0;
                        read_pos_y <= read_pos_y + 2;
                        read_en <= 0;
                    end else begin
                        read_en <= 1;
                        read_pos_x <= read_pos_x + 2;
                    end

                    fifo_bank0_write_en <= 0;
                    fifo_bank1_write_en <= 0;
                end

                WRITE_BACK: begin
                    // something something axi
                    if (burst_idx == burst_cntr_t'(BURST_SIZE / 2)) begin
                        axi_write_bank_select <= 1;
                    end

                    if (i_write_ready && o_write_valid) begin
                        burst_idx <= burst_idx + 1;

                        if (axi_write_bank_select) begin
                            fifo_bank1_read_en <= 1;
                            fifo_bank0_read_en <= 0;
                        end else begin
                            fifo_bank1_read_en <= 0;
                            fifo_bank0_read_en <= 1;
                        end
                    end else begin
                        fifo_bank0_read_en <= 0;
                        fifo_bank1_read_en <= 0;
                    end

                    o_write_valid <= (burst_idx < burst_cntr_t'(BURST_SIZE));

                    // TODO: write logic to the AXI bus

                    // AXI done
                    if (burst_idx >= burst_cntr_t'(BURST_SIZE)) begin
                        if (read_pos_y < POS_ADDRW'(TILE_HEIGHT - 2)) begin
                            // Want to start reading on the next y row
                            read_en <= 1;
                        end
                    end
                end

                DONE: begin
                    writeback_done <= 1'b1;
                    o_read_done <= 1'b1;
                end

                default: begin
                end
            endcase
        end
    end

    // Assigning output signals
    assign o_read_pos_x = read_pos_x;
    assign o_read_pos_y = read_pos_y;
    assign o_read_en    = read_en;
    assign o_write_data  = axi_write_bank_select ?  fifo_bank1_read_data : fifo_bank0_read_data;

endmodule
