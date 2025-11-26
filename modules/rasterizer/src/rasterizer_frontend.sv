`timescale 1ns / 1ps

module rasterizer_frontend #(
    parameter integer SIGNED    = 1,
    parameter integer INT_BITS  = 16,
    parameter integer FRAC_BITS = 16,
    parameter integer DATA_WIDTH = INT_BITS + FRAC_BITS,

    parameter  integer AREA_FRAC_BITS  = 4,
    localparam integer AREA_INT_BITS   = DATA_WIDTH - AREA_FRAC_BITS,
    localparam integer AREA_WIDTH      = DATA_WIDTH,
    localparam integer EDGE_AREA_SHIFT = 2*FRAC_BITS - AREA_FRAC_BITS,

    // Assumed to be in this order (for now):
    // 1.    depth
    // 2-4.  color
    // 5-7.  normal
    // 8-10. uv
    parameter int N_ATTR = 4  // depth, R, G, B
) (
    input logic clk,
    input logic rstn,

    input logic [31:0] screen_width,
    input logic [31:0] screen_height,

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
    typedef logic signed [AREA_WIDTH-1:0] area_t;

    function automatic area_t edgefun_to_area_with_round(input logic signed [2*DATA_WIDTH-1:0] v);
        logic signed [2*DATA_WIDTH-1:0] rounded;
        localparam int SHIFT = EDGE_AREA_SHIFT;
        localparam int ROUND = 1 << (SHIFT-1);
        typedef logic signed [2*DATA_WIDTH-1:0] s_ddw_t;

        rounded = v + s_ddw_t'(ROUND);  // shift left region up by 0.5 LSB
        edgefun_to_area_with_round = rounded[SHIFT +: AREA_WIDTH];
    endfunction

    int i;
    localparam int SHIFT = FRAC_BITS - AREA_FRAC_BITS;  // = 4

    // Screen parameters
    s_dw_t screen_width_fp;
    s_dw_t screen_height_fp;

    assign screen_width_fp = s_dw_t'($signed(screen_width))  << FRAC_BITS;
    assign screen_height_fp = s_dw_t'($signed(screen_height)) << FRAC_BITS;

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

    // Edge function data registers
    area_t r_edge_val0;
    area_t r_edge_val1;
    area_t r_edge_val2;
    area_t r_edge_delta0[2];
    area_t r_edge_delta1[2];
    area_t r_edge_delta2[2];
    area_t r_area;

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
    logic signed [DATA_WIDTH-1:0] tile_min_x, tile_min_y;
    logic signed [DATA_WIDTH-1:0] tile_max_x, tile_max_y;
    always_comb begin
        tile_min_x = 0;               
        tile_min_y = 0;
        tile_max_x = screen_width_fp; 
        tile_max_y = screen_height_fp;
    end

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
        w_bb_tl[0] = (i_min_x < tile_min_x) ? tile_min_x : i_min_x;
        w_bb_br[0] = (i_max_x > tile_max_x) ? tile_max_x : i_max_x;
        w_bb_tl[1] = (i_min_y < tile_min_y) ? tile_min_y : i_min_y;
        w_bb_br[1] = (i_max_y > tile_max_y) ? tile_max_y : i_max_y;

        // Check if bbox is inside tile
        w_bb_valid = (w_bb_tl[0] < w_bb_br[0]) && (w_bb_tl[1] < w_bb_br[1]);
    end

    // DIVIDER UNIT
    localparam int AREA_INV_FRAC_BITS = DATA_WIDTH - AREA_FRAC_BITS; // 28
    localparam int AREA_INV_INT_BITS  = DATA_WIDTH - AREA_INV_FRAC_BITS;

    logic  w_area_division_ready;
    area_t r_area_division_in_A;
    logic  r_area_division_in_A_dv;

    logic [DATA_WIDTH-1:0] w_area_reciprocal;
    logic                  w_area_reciprocal_dv;
    logic [DATA_WIDTH-1:0] r_area_reciprocal;

    fast_inverse_q #(
        .DATA_WIDTH    (DATA_WIDTH),
        .A_FRAC_BITS   (AREA_FRAC_BITS),        // area: Q28.4
        .INV_FRAC_BITS (AREA_INV_FRAC_BITS),     // area_inv: Q4.28
        .NUM_ITERATIONS(3)
    ) fast_inverse_inst (
        .clk        (clk),
        .rstn       (rstn),
        .ready      (w_area_division_ready),
        .A          (r_area),
        .A_dv       (r_area_division_in_A_dv),
        .A_inv      (w_area_reciprocal),
        .A_inv_dv   (w_area_reciprocal_dv)
    );

    // Barycentric coordinate compute
    logic signed [2*DATA_WIDTH-1:0] w_bw_mul[3];
    logic signed [2*DATA_WIDTH-1:0] w_bw_delta_mul[3][2];

    logic signed [DATA_WIDTH-1:0] r_barycentric_weight[3];
    logic signed [DATA_WIDTH-1:0] r_barycentric_weight_delta[3][2];

    always_comb begin
        // barycentric weights
        w_bw_mul[0] = $signed(r_edge_val1) * $signed(r_area_reciprocal);
        w_bw_mul[1] = $signed(r_edge_val2) * $signed(r_area_reciprocal);
        w_bw_mul[2] = $signed(r_edge_val0) * $signed(r_area_reciprocal);

        // deltas
        w_bw_delta_mul[0][0] = $signed(r_edge_delta1[0]) * $signed(r_area_reciprocal);
        w_bw_delta_mul[0][1] = $signed(r_edge_delta1[1]) * $signed(r_area_reciprocal);

        w_bw_delta_mul[1][0] = $signed(r_edge_delta2[0]) * $signed(r_area_reciprocal);
        w_bw_delta_mul[1][1] = $signed(r_edge_delta2[1]) * $signed(r_area_reciprocal);

        w_bw_delta_mul[2][0] = $signed(r_edge_delta0[0]) * $signed(r_area_reciprocal);
        w_bw_delta_mul[2][1] = $signed(r_edge_delta0[1]) * $signed(r_area_reciprocal);
    end

    // Attribute planes
    logic [$clog2(N_ATTR)-1:0] attr_iter;
    typedef logic [$clog2(N_ATTR)-1:0] attr_iter_t;

    // Wide intermediates for muls
    logic signed [2*DATA_WIDTH-1:0] w_attr;
    logic signed [2*DATA_WIDTH-1:0] w_attr_dx;
    logic signed [2*DATA_WIDTH-1:0] w_attr_dy;

    always_comb begin
        // value at bb_tl
        w_attr =
            $signed(r_barycentric_weight[0]) * $signed(r_attr_v0[attr_iter]) +
            $signed(r_barycentric_weight[1]) * $signed(r_attr_v1[attr_iter]) +
            $signed(r_barycentric_weight[2]) * $signed(r_attr_v2[attr_iter]);

        // d/dx
        w_attr_dx =
            $signed(r_barycentric_weight_delta[0][0]) * $signed(r_attr_v0[attr_iter]) +
            $signed(r_barycentric_weight_delta[1][0]) * $signed(r_attr_v1[attr_iter]) +
            $signed(r_barycentric_weight_delta[2][0]) * $signed(r_attr_v2[attr_iter]);

        // d/dy
        w_attr_dy =
            $signed(r_barycentric_weight_delta[0][1]) * $signed(r_attr_v0[attr_iter]) +
            $signed(r_barycentric_weight_delta[1][1]) * $signed(r_attr_v1[attr_iter]) +
            $signed(r_barycentric_weight_delta[2][1]) * $signed(r_attr_v2[attr_iter]);
    end

    localparam area_t MIN_AREA = area_t'(1);

    logic w_should_be_culled;
    always_comb begin
        w_should_be_culled = $signed(r_area) <= MIN_AREA || ~r_bb_valid;
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
                if (attr_iter == attr_iter_t'(N_ATTR-1)) begin
                    next_state = DONE;
                end
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

            r_barycentric_weight[0] <= '0;
            r_barycentric_weight[1] <= '0;
            r_barycentric_weight[2] <= '0;

            r_barycentric_weight_delta[0] <= '{'0, '0};
            r_barycentric_weight_delta[1] <= '{'0, '0};
            r_barycentric_weight_delta[2] <= '{'0, '0};

            foreach (r_attr0   [i]) r_attr0   [i] <= '0;
            foreach (r_attr_dx [i]) r_attr_dx [i] <= '0;
            foreach (r_attr_dy [i]) r_attr_dy [i] <= '0;
            attr_iter <= '0;

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
                    attr_iter <= '0;

                    culled_triangle <= '0;
                end

                COMPUTE_AREA: begin
                    r_area <= edgefun_to_area_with_round(w_edge_function_val);

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
                        $display("area:       %b", r_area);
                        $display("area logic: %b", $signed(r_area) <= MIN_AREA);
                        $display("bb logic:   %b", ~r_bb_valid);
                    end else begin
                        culled_triangle <= 1'b0;
                    end

                    r_edge_val0   <= edgefun_to_area_with_round(w_edge_function_val);
                    r_edge_delta0[0] <= area_t'((w_edge_function_delta[0] + (1 <<< (SHIFT-1))) >>> SHIFT);
                    r_edge_delta0[1] <= area_t'((w_edge_function_delta[1] + (1 <<< (SHIFT-1))) >>> SHIFT);

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
                    r_edge_val1   <= edgefun_to_area_with_round(w_edge_function_val);
                    r_edge_delta1[0] <= area_t'((w_edge_function_delta[0] + (1 <<< (SHIFT-1))) >>> SHIFT);
                    r_edge_delta1[1] <= area_t'((w_edge_function_delta[1] + (1 <<< (SHIFT-1))) >>> SHIFT);

                    // For i_ready compute
                    r_edge_function_v1 <= '{r_v2[0], r_v2[1]};
                    r_edge_function_v2 <= '{r_v0[0], r_v0[1]};
                    r_edge_function_p  <= r_bb_tl;
                end

                COMPUTE_EDGE_2: begin
                    r_edge_val2   <= edgefun_to_area_with_round(w_edge_function_val);
                    r_edge_delta2[0] <= area_t'((w_edge_function_delta[0] + (1 <<< (SHIFT-1))) >>> SHIFT);
                    r_edge_delta2[1] <= area_t'((w_edge_function_delta[1] + (1 <<< (SHIFT-1))) >>> SHIFT);
                end

                REGISTER_AREA_RECIPROCAL: begin
                    if (w_area_reciprocal_dv) begin
                        r_area_reciprocal <= w_area_reciprocal;


                        $display("area:     %b", r_area);
                        $display("area inv: %b", w_area_reciprocal);
                        $display("");

                        $display("e1: %b", r_edge_val0);
                        $display("e2: %b", r_edge_val1);
                        $display("e3: %b", r_edge_val2);
                        $display("");

                        // $display("e1_delta: %b, %b", r_edge_delta0[0], r_edge_delta0[1]);
                        // $display("e2_delta: %b, %b", r_edge_delta1[0], r_edge_delta1[1]);
                        // $display("e3_delta: %b, %b", r_edge_delta2[0], r_edge_delta2[1]);
                        // $display("");

                    end
                    foreach (r_edge_function_v1[i]) r_edge_function_v1[i] <= '0;
                    foreach (r_edge_function_v2[i]) r_edge_function_v2[i] <= '0;
                    foreach (r_edge_function_p[i] ) r_edge_function_p[i]  <= '0;
                end

                COMPUTE_BARYCENTRIC: begin
                    r_barycentric_weight[0] <= s_dw_t'(w_bw_mul[0] >>> AREA_FRAC_BITS);
                    r_barycentric_weight[1] <= s_dw_t'(w_bw_mul[1] >>> AREA_FRAC_BITS);
                    r_barycentric_weight[2] <= s_dw_t'(w_bw_mul[2] >>> AREA_FRAC_BITS);

                    r_barycentric_weight_delta[0] <= '{
                        s_dw_t'(w_bw_delta_mul[0][0] >>> AREA_FRAC_BITS),
                        s_dw_t'(w_bw_delta_mul[0][1] >>> AREA_FRAC_BITS)
                    };
                    r_barycentric_weight_delta[1] <= '{
                        s_dw_t'(w_bw_delta_mul[1][0] >>> AREA_FRAC_BITS),
                        s_dw_t'(w_bw_delta_mul[1][1] >>> AREA_FRAC_BITS)
                    };
                    r_barycentric_weight_delta[2] <= '{
                        s_dw_t'(w_bw_delta_mul[2][0] >>> AREA_FRAC_BITS),
                        s_dw_t'(w_bw_delta_mul[2][1] >>> AREA_FRAC_BITS)
                    };
                end

                COMPUTE_ATTRS: begin
                    // Attributes
                    r_attr0[attr_iter]   <= s_dw_t'(w_attr    >>> AREA_INV_FRAC_BITS);
                    r_attr_dx[attr_iter] <= s_dw_t'(w_attr_dx >>> AREA_INV_FRAC_BITS);
                    r_attr_dy[attr_iter] <= s_dw_t'(w_attr_dy >>> AREA_INV_FRAC_BITS);

                    attr_iter <= attr_iter + 1;
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
