`timescale 1ns / 1ps

// Generic reciprocal with configurable input and output Q formats.
// - A is interpreted as Q(A_INT_BITS,  A_FRAC_BITS)
// - A_inv is interpreted as Q(INV_INT_BITS, INV_FRAC_BITS)
// Constraint: A_FRAC_BITS + INV_FRAC_BITS == DATA_WIDTH
//
// This matches the common "area / area_inv" pair:
//   area     : Q28.4   -> A_FRAC_BITS   = 4
//   area_inv : Q4.28   -> INV_FRAC_BITS = 28
//   DATA_WIDTH = 32

module fast_inverse_q #(
    parameter int unsigned DATA_WIDTH     = 32,
    parameter int unsigned A_FRAC_BITS    = 4,   // fractional bits of input A
    parameter int unsigned INV_FRAC_BITS  = 28,  // fractional bits of output A_inv
    parameter int unsigned NUM_ITERATIONS = 4
) (
    input  logic                     clk,
    input  logic                     rstn,

    output logic                     ready,

    // Input: A > 0, in Q(A_INT_BITS, A_FRAC_BITS)
    input  logic [DATA_WIDTH-1:0]    A,
    input  logic                     A_dv,

    // Output: approx 1 / A_real in Q(INV_INT_BITS, INV_FRAC_BITS)
    output logic [DATA_WIDTH-1:0]    A_inv,
    output logic                     A_inv_dv
);

    // ----------------------------------------------------------------
    //  Q-format bookkeeping / safety checks
    // ----------------------------------------------------------------
    localparam int unsigned A_INT_BITS   = DATA_WIDTH - A_FRAC_BITS;
    localparam int unsigned INV_INT_BITS = DATA_WIDTH - INV_FRAC_BITS;
    localparam int unsigned MAX_SHIFT    = $clog2(DATA_WIDTH) + 1;

    // We rely on the relationship:
    //   INV_FRAC_BITS = DATA_WIDTH - A_FRAC_BITS
    // so that the raw Newton-Raphson result, which approximates 1/A_raw
    // in Q(DATA_WIDTH fractional bits), can be reinterpreted as
    // Q(INV_INT_BITS, INV_FRAC_BITS) to approximate 1 / (A_raw / 2^A_FRAC_BITS).
    initial begin
        // synthesis translate_off
        if (A_FRAC_BITS + INV_FRAC_BITS != DATA_WIDTH) begin
            $error("fast_inverse_q: A_FRAC_BITS (%0d) + INV_FRAC_BITS (%0d) must equal DATA_WIDTH (%0d)",
                   A_FRAC_BITS, INV_FRAC_BITS, DATA_WIDTH);
        end
        // synthesis translate_on
    end

    // ----------------------------------------------------------------
    //  Internal state (same structure as your original module)
    // ----------------------------------------------------------------
    logic [$clog2(NUM_ITERATIONS):0] iter = '0;
    typedef logic [$clog2(NUM_ITERATIONS):0] iter_t;

    // r_A holds A shifted up by DATA_WIDTH bits
    logic [2*DATA_WIDTH-1:0] r_A;
    logic [2*DATA_WIDTH-1:0] r_A_scaled;
    logic [2*DATA_WIDTH-1:0] X;

    integer i;
    logic [$clog2(DATA_WIDTH):0] w_shift_amt;
    logic [$clog2(DATA_WIDTH):0] r_shift_amt;

    // Find normalization shift (like original code)
    always_comb begin
        w_shift_amt = '0;
        // Look for MSB in upper DATA_WIDTH bits of r_A
        for (i = DATA_WIDTH-1; i >= 0; i = i - 1) begin
            if (r_A[i+DATA_WIDTH] == 1'b1) begin
                w_shift_amt = MAX_SHIFT'(i+1);
                break;
            end
        end
    end

    // Internal "2.0" in Q(DATA_WIDTH fractional bits)
    logic [2*DATA_WIDTH-1:0] two_fp = 2 << DATA_WIDTH;

    logic [2*DATA_WIDTH-1:0] AX;
    logic [2*DATA_WIDTH-1:0] two_fp_minus_AX;
    logic [2*DATA_WIDTH:0]   X_two_AX;
    /* verilator lint_off UNUSED */
    logic [2*DATA_WIDTH:0]   w_X_next;
    /* verilator lint_on UNUSED */

    always_comb begin
        // All math here is in a "virtual" Q format with DATA_WIDTH fractional bits.
        AX             = (r_A_scaled * X) >> DATA_WIDTH;
        two_fp_minus_AX = two_fp - AX;
        X_two_AX       = X * two_fp_minus_AX;
        w_X_next       = X_two_AX >> DATA_WIDTH;
    end

    // Post-processing: undo normalization shift.
    // The bit pattern of A_inv is later *interpreted* as Q(INV_INT_BITS, INV_FRAC_BITS).
    logic [2*DATA_WIDTH-1:0] w_A_inv_full;
    always_comb begin
        if (r_shift_amt == '0) begin
            // No shift, nothing to round
            w_A_inv_full = X;
        end else begin
            // Round-to-nearest at shift position
            w_A_inv_full = (X + ({{(2*DATA_WIDTH-1){1'b0}},1'b1} << (r_shift_amt-1)))
                           >> r_shift_amt;
        end
    end

    // ----------------------------------------------------------------
    //  FSM (same states as before)
    // ----------------------------------------------------------------
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
        ready      = 1'b0;

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
                if (iter == iter_t'(NUM_ITERATIONS-1)) begin
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

    // ----------------------------------------------------------------
    //  Sequential logic
    // ----------------------------------------------------------------
    always_ff @(posedge clk) begin
        if (~rstn) begin
            iter        <= '0;
            r_A         <= '0;
            r_shift_amt <= '0;
            r_A_scaled  <= '0;

            // Initial guess X0 ~ 1.0 in internal Q(DATA_WIDTH)
            X           <= (1 << DATA_WIDTH);

            A_inv       <= '0;
            A_inv_dv    <= 1'b0;
        end else begin
            case (current_state)
                IDLE: begin
                    if (A_dv) begin
                        // Shift input up by DATA_WIDTH bits
                        r_A <= {A, {DATA_WIDTH{1'b0}}};
                    end

                    // Reset state for new iteration
                    X        <= (1 << DATA_WIDTH);  // X0 ~ 1.0
                    iter     <= '0;
                    A_inv    <= '0;
                    A_inv_dv <= 1'b0;
                end

                PREPROCESS: begin
                    // Latch normalization shift and scale A accordingly
                    r_shift_amt <= w_shift_amt;
                    r_A_scaled  <= r_A >> w_shift_amt;
                end

                PROCESS: begin
                    iter <= iter + 1'b1;
                    X    <= w_X_next[2*DATA_WIDTH-1:0];
                end

                POSTPROCESS: begin
                    // Truncate to DATA_WIDTH bits for output.
                    // Interpreting A_inv as Q(INV_INT_BITS, INV_FRAC_BITS) gives
                    // approx 1 / (A_raw / 2^A_FRAC_BITS).
                    A_inv    <= w_A_inv_full[DATA_WIDTH-1:0];
                    A_inv_dv <= 1'b1;
                end

                default: begin
                    A_inv_dv <= 1'b0;
                end
            endcase
        end
    end

endmodule
