`timescale 1ns / 1ps

module fast_inverse #(
    parameter unsigned DATA_WIDTH = 24,
    parameter unsigned NUM_ITERATIONS = 4
    ) (
    input logic clk,
    input logic rstn,

    output logic ready,

    input logic [DATA_WIDTH-1:0] A,
    input logic A_dv,

    output logic [DATA_WIDTH-1:0] A_inv,
    output logic A_inv_dv
    );

    localparam unsigned MAX_SHIFT = $clog2(DATA_WIDTH)+1;
    logic [$clog2(NUM_ITERATIONS):0] iter = '0;

    logic [2 * DATA_WIDTH - 1:0] r_A;
    logic [2 * DATA_WIDTH - 1:0] r_A_scaled;
    logic [2 * DATA_WIDTH - 1:0] X;

    integer i;
    logic [$clog2(DATA_WIDTH):0] w_shift_amt;
    logic [$clog2(DATA_WIDTH):0] r_shift_amt;
    always_comb begin
        w_shift_amt = 0;
        for (i = DATA_WIDTH-1; i >= 0; i = i - 1) begin
            if (r_A[i+DATA_WIDTH] == 1'b1) begin
                w_shift_amt = MAX_SHIFT'(i+1);
                break;
            end
        end
    end

    logic [2*DATA_WIDTH-1:0] two_fp = 2 << DATA_WIDTH;
    logic [2*DATA_WIDTH-1:0] AX;
    logic [2*DATA_WIDTH-1:0] two_fp_minus_AX;
    logic [2*DATA_WIDTH:0] X_two_AX;
    /* verilator lint_off UNUSED */
    logic [2*DATA_WIDTH:0] w_X_next;
    /* verilator lint_on UNUSED */
    always_comb begin
        AX = ((r_A_scaled * X) >> DATA_WIDTH);
        two_fp_minus_AX = (two_fp - AX);
        X_two_AX = X * two_fp_minus_AX;
        w_X_next = (X_two_AX >> DATA_WIDTH);
    end

    logic [2*DATA_WIDTH-1:0] w_A_inv;
    always_comb begin
        if (r_shift_amt == '0) begin
            // No shift, nothing to round
            w_A_inv = X[2*DATA_WIDTH-1:0];
        end else begin
            // Round-to-nearest: add 0.5 LSB at the shift position
            w_A_inv = (X + ({{(2*DATA_WIDTH-1){1'b0}},1'b1} << (r_shift_amt-1)))
            >> r_shift_amt;
        end
    end

    typedef enum logic [1:0] {
        IDLE,
        PREPROCESS,
        PROCESS,
        POSTPROCESS
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
        ready = 1'b0;

        case (current_state)
            IDLE: begin
                if (A_dv) begin
                    next_state = PREPROCESS;
                end else begin
                    ready = 1'b1;
                end
            end

            PREPROCESS: begin
                next_state = PROCESS;
            end

            PROCESS: begin
                if (iter == NUM_ITERATIONS-1) begin
                    next_state = POSTPROCESS;
                end
            end

            POSTPROCESS: begin
                next_state = IDLE;
            end

            default: begin
                next_state = IDLE;
            end
        endcase
    end

    always_ff @(posedge clk) begin
        if (~rstn) begin
            iter <= 0;
            r_A <= '0;

            X <= (1 << DATA_WIDTH);

            A_inv <= 0;
            A_inv_dv <= 0;
        end else begin
            case (current_state)
                IDLE: begin
                    if (A_dv) begin
                        r_A <= {A, {DATA_WIDTH{1'b0}}};
                    end

                    // 1.25 is the initial guess
                    X <= (1 << DATA_WIDTH);
                    iter <= 0;
                    A_inv <= 0;
                    A_inv_dv <= 0;
                end

                PREPROCESS: begin
                    r_shift_amt <= w_shift_amt;
                    r_A_scaled <= r_A >> w_shift_amt;
                end

                PROCESS: begin
                    iter <= iter + 1;
                    X <= w_X_next[2 * DATA_WIDTH-1:0];
                end

                POSTPROCESS: begin
                    A_inv <= w_A_inv[DATA_WIDTH-1:0];
                    A_inv_dv <= 1;
                end

                default: begin
                    A_inv_dv <= 0;
                end
            endcase
        end
    end

endmodule
