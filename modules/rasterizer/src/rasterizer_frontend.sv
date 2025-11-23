`timescale 1ns / 1ps

module rasterizer_frontend #(
    parameter integer SIGNED    = 1,
    parameter integer INT_BITS  = 16,
    parameter integer FRAC_BITS = 16,
    parameter integer DATA_WIDTH = INT_BITS + FRAC_BITS,

    // Assumed to be in this order (for now):
    // 1.    depth
    // 2-4.  color
    // 5-7.  normal
    // 8-10. uv
    parameter int N_ATTR = 4,  // depth, R, G, B

    parameter signed SCREEN_WIDTH  = 640,
    parameter signed SCREEN_HEIGHT = 360
) (
    input logic clk,
    input logic rstn,

    // Input data signals
    input logic signed [DATA_WIDTH-1:0] i_v0[3],
    input logic signed [DATA_WIDTH-1:0] i_v1[3],
    input logic signed [DATA_WIDTH-1:0] i_v2[3],

    // Input vertex attributes (minus z value as it is included in i_v*)
    input logic signed [DATA_WIDTH-1:0] i_attr_v0[N_ATTR-1],
    input logic signed [DATA_WIDTH-1:0] i_attr_v1[N_ATTR-1],
    input logic signed [DATA_WIDTH-1:0] i_attr_v2[N_ATTR-1],

    // Ready/valid for input
    input  logic i_dv,
    output logic o_ready,

    // Output data signals
    output logic signed [DATA_WIDTH-1:0] o_bb_tl[2],
    output logic signed [DATA_WIDTH-1:0] o_bb_br[2],
    output logic signed [DATA_WIDTH-1:0] o_edge_val0,
    output logic signed [DATA_WIDTH-1:0] o_edge_val1,
    output logic signed [DATA_WIDTH-1:0] o_edge_val2,
    output logic signed [DATA_WIDTH-1:0] o_edge_delta0[2],
    output logic signed [DATA_WIDTH-1:0] o_edge_delta1[2],
    output logic signed [DATA_WIDTH-1:0] o_edge_delta2[2],

    output logic signed [DATA_WIDTH-1:0] o_attr0   [N_ATTR],
    output logic signed [DATA_WIDTH-1:0] o_attr_dx [N_ATTR],
    output logic signed [DATA_WIDTH-1:0] o_attr_dy [N_ATTR],

    // Ready/valid for output
    output logic o_dv,
    input  logic i_ready,

    // Mostly for debug
    output logic culled_triangle
);
    typedef logic signed [DATA_WIDTH-1:0] s_dw_t;

    int i;
    localparam [DATA_WIDTH-1:0] SCREEN_WIDTH_FP  = s_dw_t'($signed(SCREEN_WIDTH))  << FRAC_BITS;
    localparam [DATA_WIDTH-1:0] SCREEN_HEIGHT_FP = s_dw_t'($signed(SCREEN_HEIGHT)) << FRAC_BITS;

    // Register input data
    logic signed [DATA_WIDTH-1:0] r_v0[3];
    logic signed [DATA_WIDTH-1:0] r_v1[3];
    logic signed [DATA_WIDTH-1:0] r_v2[3];

    // Register input attributes
    logic signed [DATA_WIDTH-1:0] r_attr_v0[N_ATTR];
    logic signed [DATA_WIDTH-1:0] r_attr_v1[N_ATTR];
    logic signed [DATA_WIDTH-1:0] r_attr_v2[N_ATTR];

    // Attribute planes (value at bb_tl and deltas)
    logic signed [DATA_WIDTH-1:0] r_attr0   [N_ATTR];
    logic signed [DATA_WIDTH-1:0] r_attr_dx [N_ATTR];
    logic signed [DATA_WIDTH-1:0] r_attr_dy [N_ATTR];

    // Wide intermediates for muls
    logic signed [2*DATA_WIDTH-1:0] w_attr    [N_ATTR];
    logic signed [2*DATA_WIDTH-1:0] w_attr_dx [N_ATTR];
    logic signed [2*DATA_WIDTH-1:0] w_attr_dy [N_ATTR];

    // Edge function data registers
    logic signed [DATA_WIDTH-1:0] r_edge_val0;
    logic signed [DATA_WIDTH-1:0] r_edge_val1;
    logic signed [DATA_WIDTH-1:0] r_edge_val2;
    logic signed [DATA_WIDTH-1:0] r_edge_delta0[2];
    logic signed [DATA_WIDTH-1:0] r_edge_delta1[2];
    logic signed [DATA_WIDTH-1:0] r_edge_delta2[2];
    logic signed [DATA_WIDTH-1:0] r_area;

    // Edge function compute
    logic signed [DATA_WIDTH-1:0]   r_edge_function_v1[2];
    logic signed [DATA_WIDTH-1:0]   r_edge_function_v2[2];
    logic signed [DATA_WIDTH-1:0]   r_edge_function_p[2];
    logic signed [2*DATA_WIDTH-1:0] w_edge_function_val;
    logic signed [DATA_WIDTH-1:0]   w_edge_function_delta[2];

    edge_compute #(
        .DATA_WIDTH(DATA_WIDTH)
    ) edge_compute_inst (
        .v1(r_edge_function_v1),
        .v2(r_edge_function_v2),
        .p(r_edge_function_p),
        .edge_function(w_edge_function_val),
        .edge_delta(w_edge_function_delta)
    );

    // Bounding box coumpute
    // For now, just one tile with max width and height
    localparam logic signed [DATA_WIDTH-1:0] TILE_MIN_X = 0,               TILE_MIN_Y = 0;
    localparam logic signed [DATA_WIDTH-1:0] TILE_MAX_X = SCREEN_WIDTH_FP, TILE_MAX_Y = SCREEN_HEIGHT_FP;

    logic signed [DATA_WIDTH-1:0] w_bb_tl[2];
    logic signed [DATA_WIDTH-1:0] w_bb_br[2];
    logic w_bb_valid;

    logic signed [DATA_WIDTH-1:0] r_bb_tl[2];
    logic signed [DATA_WIDTH-1:0] r_bb_br[2];
    logic r_bb_valid;

    // logic to store intermediate bbox coordinates
    logic signed [DATA_WIDTH-1:0] i_min_x, i_max_x, i_min_y, i_max_y;

    always_comb begin
        // Calculate bbox of vertex 0, 1 and 2
        i_min_x = (r_v0[0] < r_v1[0]) ? ((r_v0[0] < r_v2[0]) ? r_v0[0] : r_v2[0]) : ((r_v1[0] < r_v2[0]) ? r_v1[0] : r_v2[0]);
        i_max_x = (r_v0[0] > r_v1[0]) ? ((r_v0[0] > r_v2[0]) ? r_v0[0] : r_v2[0]) : ((r_v1[0] > r_v2[0]) ? r_v1[0] : r_v2[0]);
        i_min_y = (r_v0[1] < r_v1[1]) ? ((r_v0[1] < r_v2[1]) ? r_v0[1] : r_v2[1]) : ((r_v1[1] < r_v2[1]) ? r_v1[1] : r_v2[1]);
        i_max_y = (r_v0[1] > r_v1[1]) ? ((r_v0[1] > r_v2[1]) ? r_v0[1] : r_v2[1]) : ((r_v1[1] > r_v2[1]) ? r_v1[1] : r_v2[1]);

        // Clamp min and max values of bbox to edges tile
        w_bb_tl[0] = (i_min_x < TILE_MIN_X) ? TILE_MIN_X : i_min_x;
        w_bb_br[0] = (i_max_x > TILE_MAX_X) ? TILE_MAX_X : i_max_x;
        w_bb_tl[1] = (i_min_y < TILE_MIN_Y) ? TILE_MIN_Y : i_min_y;
        w_bb_br[1] = (i_max_y > TILE_MAX_Y) ? TILE_MAX_Y : i_max_y;

        // Check if bbox is inside tile
        w_bb_valid = (w_bb_tl[0] < w_bb_br[0]) && (w_bb_tl[1] < w_bb_br[1]);
    end

    // DIVIDER UNIT
    logic                  w_area_division_ready;
    logic [DATA_WIDTH-1:0] r_area_division_in_A;
    logic                  r_area_division_in_A_dv;

    logic [DATA_WIDTH-1:0] w_area_reciprocal;
    logic                  w_area_reciprocal_dv;
    logic [DATA_WIDTH-1:0] r_area_reciprocal;

    fast_inverse #(
        .DATA_WIDTH(DATA_WIDTH),
        .NUM_ITERATIONS(8)
    ) fast_inverse_inst (
        .clk (clk),
        .rstn(rstn),

        .ready(w_area_division_ready),
        .A(r_area_division_in_A),
        .A_dv(r_area_division_in_A_dv),

        .A_inv(w_area_reciprocal),
        .A_inv_dv(w_area_reciprocal_dv)
    );

    // Barycentric coordinate compute
    logic signed [2*DATA_WIDTH-1:0] w_bw_mul[3];
    logic signed [2*DATA_WIDTH-1:0] w_bw_delta_mul[3][2];

    logic signed [DATA_WIDTH-1:0] r_barycentric_weight[3];
    logic signed [DATA_WIDTH-1:0] r_barycentric_weight_delta[3][2];

    always_comb begin
        // barycentric weights
        w_bw_mul[0] = $signed(r_edge_val0) * $signed(r_area_reciprocal);
        w_bw_mul[1] = $signed(r_edge_val1) * $signed(r_area_reciprocal);
        w_bw_mul[2] = $signed(r_edge_val2) * $signed(r_area_reciprocal);

        // deltas
        w_bw_delta_mul[0][0] = $signed(r_edge_delta0[0]) * $signed(r_area_reciprocal);
        w_bw_delta_mul[0][1] = $signed(r_edge_delta0[1]) * $signed(r_area_reciprocal);

        w_bw_delta_mul[1][0] = $signed(r_edge_delta1[0]) * $signed(r_area_reciprocal);
        w_bw_delta_mul[1][1] = $signed(r_edge_delta1[1]) * $signed(r_area_reciprocal);

        w_bw_delta_mul[2][0] = $signed(r_edge_delta2[0]) * $signed(r_area_reciprocal);
        w_bw_delta_mul[2][1] = $signed(r_edge_delta2[1]) * $signed(r_area_reciprocal);
    end

    // Attribute planes
    always_comb begin
        foreach (w_attr[i]) begin
            // value at bb_tl
            w_attr[i] =
                $signed(r_barycentric_weight[0]) * $signed(r_attr_v0[i]) +
                $signed(r_barycentric_weight[1]) * $signed(r_attr_v1[i]) +
                $signed(r_barycentric_weight[2]) * $signed(r_attr_v2[i]);

            // d/dx
            w_attr_dx[i] =
                $signed(r_barycentric_weight_delta[0][0]) * $signed(r_attr_v0[i]) +
                $signed(r_barycentric_weight_delta[1][0]) * $signed(r_attr_v1[i]) +
                $signed(r_barycentric_weight_delta[2][0]) * $signed(r_attr_v2[i]);

            // d/dy
            w_attr_dy[i] =
                $signed(r_barycentric_weight_delta[0][1]) * $signed(r_attr_v0[i]) +
                $signed(r_barycentric_weight_delta[1][1]) * $signed(r_attr_v1[i]) +
                $signed(r_barycentric_weight_delta[2][1]) * $signed(r_attr_v2[i]);
        end
    end

    logic w_should_be_culled;
    always_comb begin
        w_should_be_culled = $signed(r_area) <= $signed({(DATA_WIDTH){1'b0}}) || ~r_bb_valid;
    end

        // ========== STATE ==========
    typedef enum logic [3:0] {
        IDLE,
        COMPUTE_AREA,
        COMPUTE_EDGE_0, // Also starts computation of area reciprocal
        COMPUTE_EDGE_1,
        COMPUTE_EDGE_2,
        REGISTER_AREA_RECIPROCAL,
        COMPUTE_BARYCENTRIC,
        COMPUTE_ATTRS,
        DONE
    } state_t;
    state_t current_state = IDLE, next_state;

    always_ff @(posedge clk) begin
        if (~rstn) begin
            current_state <= IDLE;
        end else begin
            current_state <= next_state;
        end
    end

    always_comb begin
        next_state = current_state;
        o_ready = 1'b0;

        case (current_state)
            IDLE: begin
                if (i_dv) begin
                    next_state = COMPUTE_AREA;
                end
                o_ready = 1'b1;
            end

            COMPUTE_AREA: begin
                next_state = COMPUTE_EDGE_0;
            end

            COMPUTE_EDGE_0: begin
                if (w_should_be_culled) begin
                    if (i_ready) begin
                        next_state = IDLE;
                    end
                end else if (w_area_division_ready) begin
                    next_state = COMPUTE_EDGE_1;
                end
            end

            COMPUTE_EDGE_1: begin
                next_state = COMPUTE_EDGE_2;
            end

            COMPUTE_EDGE_2: begin
                next_state = REGISTER_AREA_RECIPROCAL;
            end

            REGISTER_AREA_RECIPROCAL: begin
                if (w_area_reciprocal_dv) begin
                    next_state = COMPUTE_BARYCENTRIC;
                end
            end

            COMPUTE_BARYCENTRIC: begin
                next_state = COMPUTE_ATTRS;
            end

            COMPUTE_ATTRS: begin
                next_state = DONE;
            end

            DONE: begin
                if (i_ready) begin
                    next_state = IDLE;
                end
            end

            default: begin
                next_state = IDLE;
            end
        endcase
    end

    always_ff @(posedge clk) begin
        if (~rstn) begin
            foreach (r_v0[i]) r_v0[i] <= '0;
            foreach (r_v1[i]) r_v1[i] <= '0;
            foreach (r_v2[i]) r_v2[i] <= '0;

            foreach (r_attr_v0[i]) r_attr_v0[i] <= '0;
            foreach (r_attr_v1[i]) r_attr_v1[i] <= '0;
            foreach (r_attr_v2[i]) r_attr_v2[i] <= '0;

            foreach (r_bb_tl[i]) r_bb_tl[i] <= '0;
            foreach (r_bb_br[i]) r_bb_br[i] <= '0;

            r_area_division_in_A_dv <= 1'b0;
            r_area_division_in_A <= '0;

            foreach (r_edge_function_v1[i]) r_edge_function_v1[i] <= '0;
            foreach (r_edge_function_v2[i]) r_edge_function_v2[i] <= '0;
            foreach (r_edge_function_p[i] ) r_edge_function_p[i]  <= '0;

            r_edge_val0 <= '0;
            r_edge_val1 <= '0;
            r_edge_val2 <= '0;
            foreach (r_edge_delta0[i]) r_edge_delta0[i] <= '0;
            foreach (r_edge_delta1[i]) r_edge_delta1[i] <= '0;
            foreach (r_edge_delta2[i]) r_edge_delta2[i] <= '0;

            o_dv <= '0;
            culled_triangle <= '0;

        end else begin
            case (current_state)
                IDLE: begin
                    if (i_dv) begin
                        foreach (r_v0[i]) r_v0[i] <= i_v0[i];
                        foreach (r_v1[i]) r_v1[i] <= i_v1[i];
                        foreach (r_v2[i]) r_v2[i] <= i_v2[i];

                        for (i = 1; i < 4; i++) begin
                            r_attr_v0[i] <= i_attr_v0[i-1];
                            r_attr_v1[i] <= i_attr_v1[i-1];
                            r_attr_v2[i] <= i_attr_v2[i-1];
                        end
                        r_attr_v0[0] <= i_v0[2];
                        r_attr_v1[0] <= i_v1[2];
                        r_attr_v2[0] <= i_v2[2];

                        // Add values to register in order to compute area
                        r_edge_function_v1 <= '{i_v0[0], i_v0[1]};
                        r_edge_function_v2 <= '{i_v1[0], i_v1[1]};
                        r_edge_function_p  <= '{i_v2[0], i_v2[1]};

                    end else begin
                        foreach (r_edge_function_v1[i]) r_edge_function_v1[i] <= '0;
                        foreach (r_edge_function_v2[i]) r_edge_function_v2[i] <= '0;
                        foreach (r_edge_function_p[i] ) r_edge_function_p[i]  <= '0;
                    end

                    r_edge_val0 <= '0;
                    r_edge_val1 <= '0;
                    r_edge_val2 <= '0;
                    foreach (r_edge_delta0[i]) r_edge_delta0[i] <= '0;
                    foreach (r_edge_delta1[i]) r_edge_delta1[i] <= '0;
                    foreach (r_edge_delta2[i]) r_edge_delta2[i] <= '0;
                    r_area <= '0;
                    o_dv   <= '0;

                    r_barycentric_weight[0] <= '0;
                    r_barycentric_weight[1] <= '0;
                    r_barycentric_weight[2] <= '0;

                    r_barycentric_weight_delta[0] <= '{'0, '0};
                    r_barycentric_weight_delta[1] <= '{'0, '0};
                    r_barycentric_weight_delta[2] <= '{'0, '0};

                    foreach (r_attr0   [i]) r_attr0   [i] <= '0;
                    foreach (r_attr_dx [i]) r_attr_dx [i] <= '0;
                    foreach (r_attr_dy [i]) r_attr_dy [i] <= '0;

                    culled_triangle <= '0;
                end

                COMPUTE_AREA: begin
                    r_area <= w_edge_function_val[DATA_WIDTH + FRAC_BITS - 1 : FRAC_BITS];

                    // Bounding box
                    foreach (r_bb_tl[i]) r_bb_tl[i] <= w_bb_tl[i];
                    foreach (r_bb_br[i]) r_bb_br[i] <= w_bb_br[i];
                    r_bb_valid <= w_bb_valid;

                    // For i_ready compute
                    r_edge_function_v1 <= '{r_v0[0], r_v0[1]};
                    r_edge_function_v2 <= '{r_v1[0], r_v1[1]};
                    r_edge_function_p  <= w_bb_tl;
                end

                COMPUTE_EDGE_0: begin
                    if (w_should_be_culled) begin
                        culled_triangle <= 1'b1;
                    end else begin
                        culled_triangle <= 1'b0;
                    end

                    r_edge_val0   <= w_edge_function_val[DATA_WIDTH + FRAC_BITS - 1 : FRAC_BITS];
                    r_edge_delta0 <= w_edge_function_delta;

                    // Area reciprocal compute
                    if (w_area_division_ready) begin
                        r_area_division_in_A <= r_area;
                        r_area_division_in_A_dv <= 1'b1;

                        // For i_ready compute
                        r_edge_function_v1 <= '{r_v1[0], r_v1[1]};
                        r_edge_function_v2 <= '{r_v2[0], r_v2[1]};
                        r_edge_function_p  <= r_bb_tl;
                    end else begin
                        r_area_division_in_A_dv <= 1'b0;
                    end
                end

                COMPUTE_EDGE_1: begin
                    r_area_division_in_A_dv <= 1'b0;
                    r_edge_val1   <= w_edge_function_val[DATA_WIDTH + FRAC_BITS - 1 : FRAC_BITS];
                    r_edge_delta1 <= w_edge_function_delta;

                    // For i_ready compute
                    r_edge_function_v1 <= '{r_v2[0], r_v2[1]};
                    r_edge_function_v2 <= '{r_v0[0], r_v0[1]};
                    r_edge_function_p  <= r_bb_tl;
                end

                COMPUTE_EDGE_2: begin
                    r_edge_val2   <= w_edge_function_val[DATA_WIDTH + FRAC_BITS - 1 : FRAC_BITS];
                    r_edge_delta2 <= w_edge_function_delta;
                end

                REGISTER_AREA_RECIPROCAL: begin
                    if (w_area_reciprocal_dv) begin
                        r_area_reciprocal <= w_area_reciprocal;
                    end
                    foreach (r_edge_function_v1[i]) r_edge_function_v1[i] <= '0;
                    foreach (r_edge_function_v2[i]) r_edge_function_v2[i] <= '0;
                    foreach (r_edge_function_p[i] ) r_edge_function_p[i]  <= '0;
                end

                COMPUTE_BARYCENTRIC: begin
                    r_barycentric_weight[0] <= s_dw_t'(w_bw_mul[0] >>> FRAC_BITS);
                    r_barycentric_weight[1] <= s_dw_t'(w_bw_mul[1] >>> FRAC_BITS);
                    r_barycentric_weight[2] <= s_dw_t'(w_bw_mul[2] >>> FRAC_BITS);

                    r_barycentric_weight_delta[0] <= '{
                        s_dw_t'(w_bw_delta_mul[0][0] >>> FRAC_BITS),
                        s_dw_t'(w_bw_delta_mul[0][1] >>> FRAC_BITS)
                    };
                    r_barycentric_weight_delta[1] <= '{
                        s_dw_t'(w_bw_delta_mul[1][0] >>> FRAC_BITS),
                        s_dw_t'(w_bw_delta_mul[1][1] >>> FRAC_BITS)
                    };
                    r_barycentric_weight_delta[2] <= '{
                        s_dw_t'(w_bw_delta_mul[2][0] >>> FRAC_BITS),
                        s_dw_t'(w_bw_delta_mul[2][1] >>> FRAC_BITS)
                    };
                end

                COMPUTE_ATTRS: begin
                    // Attributes
                    foreach (r_attr0[i]) begin
                        r_attr0[i]   <= s_dw_t'(w_attr[i]    >>> FRAC_BITS);
                        r_attr_dx[i] <= s_dw_t'(w_attr_dx[i] >>> FRAC_BITS);
                        r_attr_dy[i] <= s_dw_t'(w_attr_dy[i] >>> FRAC_BITS);
                    end
                end

                DONE: begin
                    if (i_ready) begin
                        foreach (o_bb_tl[i]) o_bb_tl[i] <= r_bb_tl[i];
                        foreach (o_bb_br[i]) o_bb_br[i] <= r_bb_br[i];

                        o_edge_val0 <= r_edge_val0;
                        o_edge_val1 <= r_edge_val1;
                        o_edge_val2 <= r_edge_val2;

                        foreach (o_edge_delta0[i]) o_edge_delta0[i] <= r_edge_delta0[i];
                        foreach (o_edge_delta1[i]) o_edge_delta1[i] <= r_edge_delta1[i];
                        foreach (o_edge_delta2[i]) o_edge_delta2[i] <= r_edge_delta2[i];

                        foreach (o_attr0[i]) begin
                            o_attr0[i]   <= r_attr0[i];
                            o_attr_dx[i] <= r_attr_dx[i];
                            o_attr_dy[i] <= r_attr_dy[i];
                        end

                        o_dv <= '1;
                    end else begin
                        o_dv <= '0;
                    end
                end

                default: begin
                end
            endcase
        end
    end

endmodule

module edge_compute #(
    parameter unsigned DATA_WIDTH = 24
) (
    input logic signed [DATA_WIDTH-1:0] v1[2],
    input logic signed [DATA_WIDTH-1:0] v2[2],
    input logic signed [DATA_WIDTH-1:0] p[2],

    output logic signed [2*DATA_WIDTH-1:0] edge_function,
    output logic signed [DATA_WIDTH-1:0]   edge_delta[2]
);

    /* verilator lint_off WIDTH */
    always_comb begin
        edge_function = ((p[0] - v1[0]) * (v2[1] - v1[1])) - ((p[1] - v1[1]) * (v2[0] - v1[0]));
        edge_delta = '{v2[1] - v1[1], -(v2[0] - v1[0])};
    end
    /* verilator lint_on WIDTH */
endmodule
