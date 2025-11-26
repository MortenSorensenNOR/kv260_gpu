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
    // Tile-level iteration
    logic [INT_BITS-1:0] r_tile_x, r_tile_y;
    logic [1:0]          r_sub_x, r_sub_y;  // 0..3

    // Edge / attr at tile origin
    s_dw_t r_edge_val0_tile, r_edge_val1_tile, r_edge_val2_tile;
    s_dw_t r_attr_tile [N_ATTR];

    // Edge / attr at current pixel inside tile
    // (you already have r_edge_val0/1/2 and r_cur_attr[], we keep using them)

    // Flags for tile classification
    logic tile_all_inside;
    logic tile_all_outside;
    // 4x delta for stepping tile →  tile in X and Y
    s_dw_t r_edge_delta0_4x[2];
    s_dw_t r_edge_delta1_4x[2];
    s_dw_t r_edge_delta2_4x[2];

    s_dw_t r_attr_dx_4x [N_ATTR];
    s_dw_t r_attr_dy_4x [N_ATTR];

    // Latched triangle setup
    s_dw_t r_bb_tl[2], r_bb_br[2];
    s_dw_t r_edge_val0_start_row, r_edge_val1_start_row, r_edge_val2_start_row;
    s_dw_t r_edge_delta0[2], r_edge_delta1[2], r_edge_delta2[2];
    logic  e0_top_left, e1_top_left, e2_top_left;

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
    logic pixel_inside_triangle_base;  // per-pixel test from edges
    logic pixel_inside_triangle;       // final test (with tile_all_inside)
    logic advance_pixel;

    always_comb begin
        // Edge 0 top-left?
        e0_top_left = (r_edge_delta0[1] > 0) || ((r_edge_delta0[1] == 0) && (r_edge_delta0[0] < 0));

        // Edge 1 top-left?
        e1_top_left = (r_edge_delta1[1] > 0) || ((r_edge_delta1[1] == 0) && (r_edge_delta1[0] < 0));

        // Edge 2 top-left?
        e2_top_left = (r_edge_delta2[1] > 0) || ((r_edge_delta2[1] == 0) && (r_edge_delta2[0] < 0));
    end

    logic e0_pass, e1_pass, e2_pass;
    always_comb begin
        e0_pass = (r_edge_val0 > 0) || ((r_edge_val0 == 0) && e0_top_left);
        e1_pass = (r_edge_val1 > 0) || ((r_edge_val1 == 0) && e1_top_left);
        e2_pass = (r_edge_val2 > 0) || ((r_edge_val2 == 0) && e2_top_left);

        pixel_inside_triangle_base = e0_pass && e1_pass && e2_pass;

        pixel_inside_triangle = tile_all_inside ? 1'b1 : pixel_inside_triangle_base;
        advance_pixel         = (!pixel_inside_triangle) || (pixel_inside_triangle && i_ready);
    end


    // ====================== TILE COVERAGE (4-corner test) ======================
    s_dw_t dx0_3, dx1_3, dx2_3, dy0_3, dy1_3, dy2_3;
    s_dw_t e0_tl, e0_tr, e0_bl, e0_br, e1_tl, e1_tr, e1_bl, e1_br, e2_tl, e2_tr, e2_bl, e2_br;

    logic e0_all_in, e1_all_in, e2_all_in;
    logic e0_all_out, e1_all_out, e2_all_out;

    always_comb begin
        tile_all_inside  = 1'b0;
        tile_all_outside = 1'b0;

        // 3*dx = 4*dx - dx (we already have 4x deltas)
        dx0_3 = r_edge_delta0_4x[0] - r_edge_delta0[0];
        dx1_3 = r_edge_delta1_4x[0] - r_edge_delta1[0];
        dx2_3 = r_edge_delta2_4x[0] - r_edge_delta2[0];

        // 3*dy = 4*dy - dy
        dy0_3 = r_edge_delta0_4x[1] - r_edge_delta0[1];
        dy1_3 = r_edge_delta1_4x[1] - r_edge_delta1[1];
        dy2_3 = r_edge_delta2_4x[1] - r_edge_delta2[1];

        // Edge 0 at 4 tile corners
        e0_tl = r_edge_val0_tile;
        e0_tr = r_edge_val0_tile + dx0_3;
        e0_bl = r_edge_val0_tile + dy0_3;
        e0_br = r_edge_val0_tile + dx0_3 + dy0_3;

        // Edge 1 at 4 tile corners
        e1_tl = r_edge_val1_tile;
        e1_tr = r_edge_val1_tile + dx1_3;
        e1_bl = r_edge_val1_tile + dy1_3;
        e1_br = r_edge_val1_tile + dx1_3 + dy1_3;

        // Edge 2 at 4 tile corners
        e2_tl = r_edge_val2_tile;
        e2_tr = r_edge_val2_tile + dx2_3;
        e2_bl = r_edge_val2_tile + dy2_3;
        e2_br = r_edge_val2_tile + dx2_3 + dy2_3;

        // For each edge, all 4 corners inside or outside
        e0_all_in  = (e0_tl > 0) && (e0_tr > 0) && (e0_bl > 0) && (e0_br > 0);
        e1_all_in  = (e1_tl > 0) && (e1_tr > 0) && (e1_bl > 0) && (e1_br > 0);
        e2_all_in  = (e2_tl > 0) && (e2_tr > 0) && (e2_bl > 0) && (e2_br > 0);

        e0_all_out = (e0_tl < 0) && (e0_tr < 0) && (e0_bl < 0) && (e0_br < 0);
        e1_all_out = (e1_tl < 0) && (e1_tr < 0) && (e1_bl < 0) && (e1_br < 0);
        e2_all_out = (e2_tl < 0) && (e2_tr < 0) && (e2_bl < 0) && (e2_br < 0);

        // Entire tile fully inside triangle if ALL edges have all 4 corners >= 0
        tile_all_inside  = e0_all_in && e1_all_in && e2_all_in;

        // Entire tile totally outside if ANY edge has all 4 corners < 0
        tile_all_outside = e0_all_out || e1_all_out || e2_all_out;
    end

    // ====================== FSM ======================
    typedef enum logic [2:0] {
        IDLE,
        SETUP_TILE_ROW,
        SETUP_TILE,
        SCAN_TILE,
        NEXT_TILE,
        NEXT_TILE_ROW,
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
        o_ready    = 1'b0;
        done       = 1'b0;

        case (state)
            IDLE: begin
                o_ready = 1'b1;
                if (i_dv) next_state = SETUP_TILE_ROW;
            end

            SETUP_TILE_ROW: begin
                // Have we gone past bb bottom?
                if (r_tile_y >= iw_t'(r_bb_br[1] >>> FRAC_BITS))
                    next_state = DONE;
                else
                    next_state = SETUP_TILE;
            end

            SETUP_TILE: begin
                // Have we gone past bb right?
                if (r_tile_x >= iw_t'(r_bb_br[0] >>> FRAC_BITS)) begin
                    next_state = NEXT_TILE_ROW;
                end else if (tile_all_outside) begin
                    // Entire 4x4 block is outside triangle: skip it
                    next_state = NEXT_TILE;
                end else begin
                    // Tile is partially or fully covered: scan pixels
                    next_state = SCAN_TILE;
                end
            end

            SCAN_TILE: begin
                // SCAN_TILE walks r_sub_x, r_sub_y within 4x4
                // When finished all subpixels → NEXT_TILE
                if ((r_sub_y == 2'd3) && (r_sub_x == 2'd3) && advance_pixel)
                    next_state = NEXT_TILE;
            end

            NEXT_TILE: begin
                next_state = SETUP_TILE;
            end

            NEXT_TILE_ROW: begin
                next_state = SETUP_TILE_ROW;
            end

            DONE: begin
                done       = 1'b1;
                next_state = IDLE;
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

                        // Precompute 4x deltas for tiles
                        foreach (r_edge_delta0[i]) r_edge_delta0_4x[i] <= i_edge_delta0[i] <<< 2;
                        foreach (r_edge_delta1[i]) r_edge_delta1_4x[i] <= i_edge_delta1[i] <<< 2;
                        foreach (r_edge_delta2[i]) r_edge_delta2_4x[i] <= i_edge_delta2[i] <<< 2;

                        foreach (r_attr_dx[i]) begin
                            r_attr_dx[i]   <= i_attr_dx[i];
                            r_attr_dx_4x[i]<= i_attr_dx[i] <<< 2;
                        end

                        foreach (r_attr_dy[i]) begin
                            r_attr_dy[i]   <= i_attr_dy[i];
                            r_attr_dy_4x[i]<= i_attr_dy[i] <<< 2;
                        end

                        // Tile grid starts at bb_tl
                        r_tile_y <= iw_t'(i_bb_tl[1] >>> FRAC_BITS);
                        r_tile_x <= iw_t'(i_bb_tl[0] >>> FRAC_BITS);

                        // Row-start edge/attr at bb_tl (for tile row 0)
                        r_edge_val0_start_row <= i_edge_val0;
                        r_edge_val1_start_row <= i_edge_val1;
                        r_edge_val2_start_row <= i_edge_val2;

                        foreach (r_attr_start_row[i]) r_attr_start_row[i] <= i_attr0[i];

                        o_dv <= 1'b0;
                    end
                end

                SETUP_TILE_ROW: begin
                    if (r_tile_y < iw_t'(r_bb_br[1] >>> FRAC_BITS)) begin
                        // Reset tile X at start of row
                        r_tile_x <= iw_t'(r_bb_tl[0] >>> FRAC_BITS);

                        // Edge/attr at start of this tile row (top-left tile in row)
                        r_edge_val0_tile <= r_edge_val0_start_row;
                        r_edge_val1_tile <= r_edge_val1_start_row;
                        r_edge_val2_tile <= r_edge_val2_start_row;

                        foreach (r_attr_tile[i])
                            r_attr_tile[i] <= r_attr_start_row[i];

                        // And we init subpixel cursor for first tile when we go into SETUP_TILE
                    end
                end

                NEXT_TILE_ROW: begin
                    // Move down by 4 pixels
                    r_tile_y <= r_tile_y + 4;

                    // Update row start edge/attr by 4×dy
                    r_edge_val0_start_row <= r_edge_val0_start_row + r_edge_delta0_4x[1];
                    r_edge_val1_start_row <= r_edge_val1_start_row + r_edge_delta1_4x[1];
                    r_edge_val2_start_row <= r_edge_val2_start_row + r_edge_delta2_4x[1];

                    foreach (r_attr_start_row[i])
                        r_attr_start_row[i] <= r_attr_start_row[i] + r_attr_dy_4x[i];
                end

                SETUP_TILE: begin
                    if (r_tile_x < iw_t'(r_bb_br[0] >>> FRAC_BITS)) begin
                        r_sub_x <= 2'd0;
                        r_sub_y <= 2'd0;

                        // Pixel coords
                        r_pix_x <= r_tile_x;
                        r_pix_y <= r_tile_y;

                        // Fixed-point
                        // r_cur_x <= s_dw_t'(r_tile_x) <<< FRAC_BITS;
                        // r_cur_y <= s_dw_t'(r_tile_y) <<< FRAC_BITS;

                        r_cur_x <= (s_dw_t'(r_tile_x) <<< FRAC_BITS) + (1 <<< (FRAC_BITS-1));
                        r_cur_y <= (s_dw_t'(r_tile_y) <<< FRAC_BITS) + (1 <<< (FRAC_BITS-1));


                        // Edge/attrs at tile origin
                        r_edge_val0 <= r_edge_val0_tile;
                        r_edge_val1 <= r_edge_val1_tile;
                        r_edge_val2 <= r_edge_val2_tile;

                        foreach (r_cur_attr[i])
                            r_cur_attr[i] <= r_attr_tile[i];

                        // (Optional) here you can also precompute tile_all_inside / tile_all_outside
                        // by checking edges at the 4 corners using increments.
                    end
                end

                NEXT_TILE: begin
                    // Move to next tile in X
                    r_tile_x <= r_tile_x + 4;

                    // Update tile origin edge/attr by 4×dx
                    r_edge_val0_tile <= r_edge_val0_tile + r_edge_delta0_4x[0];
                    r_edge_val1_tile <= r_edge_val1_tile + r_edge_delta1_4x[0];
                    r_edge_val2_tile <= r_edge_val2_tile + r_edge_delta2_4x[0];

                    foreach (r_attr_tile[i])
                        r_attr_tile[i] <= r_attr_tile[i] + r_attr_dx_4x[i];
                end

                SCAN_TILE: begin
                    if (pixel_inside_triangle && i_ready) begin
                        // Emit fragment at current pixel
                        o_fragment_x <= r_cur_x;
                        o_fragment_y <= r_cur_y;
                        foreach (o_fragment_attr[i])
                            o_fragment_attr[i] <= r_cur_attr[i];
                        o_dv <= 1'b1;
                    end else begin
                        o_dv <= 1'b0;
                    end

                    if (advance_pixel) begin
                        // Advance внутри 4×4 tile
                        if (r_sub_x < 2'd3) begin
                            // Move to next pixel in row
                            r_sub_x <= r_sub_x + 2'd1;
                            r_pix_x <= r_pix_x + 1;
                            r_cur_x <= r_cur_x + (1 <<< FRAC_BITS);

                            r_edge_val0 <= r_edge_val0 + r_edge_delta0[0];
                            r_edge_val1 <= r_edge_val1 + r_edge_delta1[0];
                            r_edge_val2 <= r_edge_val2 + r_edge_delta2[0];

                            foreach (r_cur_attr[i])
                                r_cur_attr[i] <= r_cur_attr[i] + r_attr_dx[i];

                        end else begin
                            // End of sub-row in tile; move down to next sub-row
                            r_sub_x <= 2'd0;
                            r_pix_x <= r_tile_x; // back to left of tile
                            r_cur_x <= s_dw_t'(r_tile_x) <<< FRAC_BITS;

                            if (r_sub_y < 2'd3) begin
                                r_sub_y <= r_sub_y + 2'd1;
                                r_pix_y <= r_pix_y + 1;
                                r_cur_y <= r_cur_y + (1 <<< FRAC_BITS);

                                // step edges and attrs by +dy and reset per-row dx
                                r_edge_val0 <= r_edge_val0 + r_edge_delta0[1]
                                - r_edge_delta0[0]*3; // because we already walked 3 in x
                                r_edge_val1 <= r_edge_val1 + r_edge_delta1[1]
                                - r_edge_delta1[0]*3;
                                r_edge_val2 <= r_edge_val2 + r_edge_delta2[1]
                                - r_edge_delta2[0]*3;

                                foreach (r_cur_attr[i])
                                    r_cur_attr[i] <= r_cur_attr[i] + r_attr_dy[i]
                                - r_attr_dx[i]*3;
                            end
                        end
                    end
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
