`timescale 1ns / 1ps

module rasterizer_backend #(
    parameter integer INT_BITS   = 16,
    parameter integer FRAC_BITS  = 16,
    parameter integer DATA_WIDTH = INT_BITS + FRAC_BITS,

    // Assumed to be in this order (for now):
    // 1.    depth
    // 2-4.  color
    // 5-7.  normal
    // 8-10. uv
    parameter int N_ATTR = 4,

    parameter signed SCREEN_WIDTH  = 640,
    parameter signed SCREEN_HEIGHT = 360
) (
    input logic clk,
    input logic rstn,

    // Input data signals
    input logic signed [DATA_WIDTH-1:0] i_bb_tl[2],
    input logic signed [DATA_WIDTH-1:0] i_bb_br[2],

    input logic signed [DATA_WIDTH-1:0] i_edge_val0,
    input logic signed [DATA_WIDTH-1:0] i_edge_val1,
    input logic signed [DATA_WIDTH-1:0] i_edge_val2,

    input logic signed [DATA_WIDTH-1:0] i_edge_delta0[2],
    input logic signed [DATA_WIDTH-1:0] i_edge_delta1[2],
    input logic signed [DATA_WIDTH-1:0] i_edge_delta2[2],

    // Generic interpolated attributes at bb_tl
    input  logic signed [DATA_WIDTH-1:0] i_attr0   [N_ATTR],
    input  logic signed [DATA_WIDTH-1:0] i_attr_dx [N_ATTR],
    input  logic signed [DATA_WIDTH-1:0] i_attr_dy [N_ATTR],

    // Ready/valid for input
    input  logic i_dv,
    output logic o_ready,

    // Output data signals
    output logic signed [DATA_WIDTH-1:0] o_fragment_x,
    output logic signed [DATA_WIDTH-1:0] o_fragment_y,
    output logic signed [DATA_WIDTH-1:0] o_fragment_attr [N_ATTR],

    // Ready/valid for output
    output logic o_dv,
    input  logic i_ready,

    output logic done
);

    typedef logic signed [DATA_WIDTH-1:0] s_dw_t;
    typedef logic [INT_BITS-1:0] iw_t;

    // ====================== REGISTERS ======================
    // Latched triangle setup
    s_dw_t r_bb_tl[2], r_bb_br[2];
    s_dw_t r_edge_val0_start_row, r_edge_val1_start_row, r_edge_val2_start_row;
    s_dw_t r_edge_delta0[2], r_edge_delta1[2], r_edge_delta2[2];

    s_dw_t r_attr_start_row [N_ATTR];
    s_dw_t r_attr_dx        [N_ATTR];
    s_dw_t r_attr_dy        [N_ATTR];

    // Current scan position
    s_dw_t r_cur_x, r_cur_y;

    // Current edge/z/attr at (r_cur_x, r_cur_y)
    s_dw_t r_edge_val0, r_edge_val1, r_edge_val2;
    s_dw_t r_cur_attr [N_ATTR];

    // Loop indices in integer pixels (for bounds)
    logic [INT_BITS-1:0] r_pix_x, r_pix_y;

    // ====================== LOGIC ======================
    logic pixel_inside_triangle;
    logic advance_pixel;

    always_comb begin
        pixel_inside_triangle = (r_edge_val0 >= 0) && (r_edge_val1 >= 0) && (r_edge_val2 >= 0);
        advance_pixel         = (!pixel_inside_triangle) || (pixel_inside_triangle && i_ready);
    end

    // ====================== FSM ======================
    typedef enum logic [2:0] {
        IDLE,
        SETUP_ROW,
        SCAN_ROW,
        NEXT_ROW,
        DONE
    } state_t;
    state_t state, next_state;

    always_ff @(posedge clk) begin
        if (~rstn) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    // State machine logic
    always_comb begin
        next_state = state;
        o_ready = 1'b0;
        done    = 1'b0;

        case (state)
            IDLE: begin
                o_ready = 1'b1;
                if (i_dv) begin
                    next_state = SETUP_ROW;
                end
            end

            SETUP_ROW: begin
                if (r_pix_y >= iw_t'(r_bb_br[1] >>> FRAC_BITS)) begin
                    next_state = DONE;
                end else begin
                    next_state = SCAN_ROW;
                end
            end

            SCAN_ROW: begin
                if (r_pix_x >= iw_t'(r_bb_br[0] >>> FRAC_BITS)) begin
                    next_state = NEXT_ROW;
                end
            end

            NEXT_ROW: begin
                next_state = SETUP_ROW;
            end

            DONE: begin
                next_state = IDLE;
                done       = 1'b1;
            end

            default: begin
                next_state = IDLE;
            end
        endcase
    end

    // Logic
    always_ff @(posedge clk) begin
        if (~rstn) begin
            r_pix_y <= '0;
            r_pix_x <= '0;

            r_cur_x <= '0;
            r_cur_y <= '0;

            r_edge_val0 <= '0;
            r_edge_val1 <= '0;
            r_edge_val2 <= '0;
            foreach (r_cur_attr[i]) r_cur_attr[i] <= '0;

            foreach(r_bb_tl[i]) r_bb_tl[i] <= '0;
            foreach(r_bb_br[i]) r_bb_br[i] <= '0;

            r_edge_val0_start_row <= '0;
            r_edge_val1_start_row <= '0;
            r_edge_val2_start_row <= '0;

            foreach (r_edge_delta0[i]) r_edge_delta0[i] <= '0;
            foreach (r_edge_delta1[i]) r_edge_delta1[i] <= '0;
            foreach (r_edge_delta2[i]) r_edge_delta2[i] <= '0;

            foreach (r_attr_start_row[i]) r_attr_start_row[i] <= '0;
            foreach (r_attr_dx[i]) r_attr_dx[i] <= '0;
            foreach (r_attr_dy[i]) r_attr_dy[i] <= '0;

            o_fragment_x <= '0;
            o_fragment_y <= '0;
            foreach (o_fragment_attr[i]) o_fragment_attr[i] <= '0;
            o_dv <= '0;
        end else begin
            case (state)
                IDLE: begin
                    if (i_dv && o_ready) begin
                        r_pix_y <= iw_t'(i_bb_tl[1] >>> FRAC_BITS);
                        r_pix_x <= iw_t'(i_bb_tl[0] >>> FRAC_BITS);

                        foreach(r_bb_tl[i]) r_bb_tl[i] <= i_bb_tl[i];
                        foreach(r_bb_br[i]) r_bb_br[i] <= i_bb_br[i];

                        r_edge_val0_start_row <= i_edge_val0;
                        r_edge_val1_start_row <= i_edge_val1;
                        r_edge_val2_start_row <= i_edge_val2;

                        foreach (r_edge_delta0[i]) r_edge_delta0[i] <= i_edge_delta0[i];
                        foreach (r_edge_delta1[i]) r_edge_delta1[i] <= i_edge_delta1[i];
                        foreach (r_edge_delta2[i]) r_edge_delta2[i] <= i_edge_delta2[i];

                        foreach (r_attr_start_row[i]) r_attr_start_row[i] <= i_attr0[i];
                        foreach (r_attr_dx[i]) r_attr_dx[i] <= i_attr_dx[i];
                        foreach (r_attr_dy[i]) r_attr_dy[i] <= i_attr_dy[i];

                        o_dv <= 1'b0;
                    end
                end

                SETUP_ROW: begin
                    if (r_pix_y < iw_t'(r_bb_br[1] >>> FRAC_BITS)) begin
                        r_pix_x <= iw_t'(r_bb_tl[0] >>> FRAC_BITS);
                        r_cur_x <= r_bb_tl[0];
                        r_cur_y <= s_dw_t'(r_pix_y) <<< FRAC_BITS;

                        r_edge_val0 <= r_edge_val0_start_row;
                        r_edge_val1 <= r_edge_val1_start_row;
                        r_edge_val2 <= r_edge_val2_start_row;

                        foreach (r_cur_attr[i])
                            r_cur_attr[i] <= r_attr_start_row[i];
                    end
                end

                SCAN_ROW: begin
                    if (pixel_inside_triangle && i_ready) begin
                        o_fragment_x   <= r_cur_x;
                        o_fragment_y   <= r_cur_y;
                        foreach (o_fragment_attr[i])
                            o_fragment_attr[i] <= r_cur_attr[i];

                        o_dv <= 1'b1;
                    end else begin
                        o_dv <= 1'b0;
                    end

                    if (advance_pixel) begin
                        // step x in pixel + fixed-point
                        r_pix_x <= r_pix_x + 1;
                        r_cur_x <= r_cur_x + (1 <<< FRAC_BITS);  // one pixel

                        // increment edge, z, attrs in x
                        r_edge_val0 <= r_edge_val0 + r_edge_delta0[0];
                        r_edge_val1 <= r_edge_val1 + r_edge_delta1[0];
                        r_edge_val2 <= r_edge_val2 + r_edge_delta2[0];

                        foreach (r_cur_attr[i])
                            r_cur_attr[i] <= r_cur_attr[i] + r_attr_dx[i];
                    end
                end

                NEXT_ROW: begin
                    // Next pixel row
                    r_pix_y <= r_pix_y + 1;

                    // Update row start edge/z/attrs by dy
                    r_edge_val0_start_row <= r_edge_val0_start_row + r_edge_delta0[1];
                    r_edge_val1_start_row <= r_edge_val1_start_row + r_edge_delta1[1];
                    r_edge_val2_start_row <= r_edge_val2_start_row + r_edge_delta2[1];

                    foreach (r_attr_start_row[i])
                        r_attr_start_row[i] <= r_attr_start_row[i] + r_attr_dy[i];
                end

                DONE: begin
                    o_dv <= '0;
                end

                default: begin
                end
            endcase
        end
    end

endmodule
