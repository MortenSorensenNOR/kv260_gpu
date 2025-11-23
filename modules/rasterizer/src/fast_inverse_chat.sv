`timescale 1ns / 1ps

// Newton-Raphson iterative division: 1/D
// Uses formula: X_{n+1} = X_n * (2 - D * X_n)
// Input: Q-format number to invert
// Output: Reciprocal in potentially different Q-format

module fast_inverse #(
    parameter integer DATA_WIDTH = 32,
    parameter integer OUTPUT_WIDTH = 32,  // Can be different from input
    parameter integer NUM_ITERATIONS = 8
) (
    input  logic clk,
    input  logic rstn,

    output logic ready,
    input  logic signed [DATA_WIDTH-1:0] A,
    input  logic A_dv,

    output logic signed [OUTPUT_WIDTH-1:0] A_inv,
    output logic A_inv_dv
);

    typedef enum logic [1:0] {
        IDLE,
        COMPUTING,
        DONE
    } state_t;

    state_t state, next_state;

    // Iteration counter
    typedef logic [$clog2(NUM_ITERATIONS+1)-1:0] iter_count_t;
    logic [$clog2(NUM_ITERATIONS+1)-1:0] iteration_count;

    // Working registers - use wider width for intermediate calculations
    // Need extra bits to handle multiplication results
    localparam int WORK_WIDTH = DATA_WIDTH + OUTPUT_WIDTH;
    logic signed [WORK_WIDTH-1:0] x_current;  // Current approximation
    logic signed [DATA_WIDTH-1:0] d_value;     // Value to invert

    // Initial guess: for normalized inputs (area > 1), start with a reasonable estimate
    // For Q24.8 input representing area in pixels, initial guess in Q4.28
    // If area ≈ 256 (1 pixel in Q24.8), reciprocal ≈ 1 (Q4.28)
    // Initial guess: shift input left to align decimal points
    logic signed [WORK_WIDTH-1:0] initial_guess;

    // Calculate initial guess based on format conversion
    // If input is Q24.8 and output is Q4.28, we need to scale by 2^20
    localparam int GUESS_SHIFT = OUTPUT_WIDTH - DATA_WIDTH;

    always_comb begin
        if (GUESS_SHIFT > 0) begin
            // Output has more fractional bits
            // Rough reciprocal: divide 2^(2*OUTPUT_FRAC_BITS) by input
            // For simplicity, use a fixed initial guess based on expected range
            initial_guess = WORK_WIDTH'(1) << (OUTPUT_WIDTH - 4);  // Start at 0.0625 in output format
        end else begin
            initial_guess = WORK_WIDTH'(1) << (OUTPUT_WIDTH - 4);
        end
    end

    // Newton-Raphson iteration: x_next = x * (2 - d * x)
    logic signed [2*WORK_WIDTH-1:0] d_times_x;
    logic signed [WORK_WIDTH-1:0] two_minus_dx;
    logic signed [2*WORK_WIDTH-1:0] x_next_full;
    logic signed [WORK_WIDTH-1:0] x_next;

    // Determine fractional bits for each format
    // Assuming input is Q(INT).(DATA_WIDTH-INT) and output is Q(INT2).(OUTPUT_WIDTH-INT2)
    // For our use case: input Q24.8, output Q4.28
    localparam int OUTPUT_FRAC_BITS = 28;  // Known for Q4.28

    always_comb begin
        // d * x: Q24.8 * Q(4+28+24+8).28 ≈ scaled multiplication
        // Keep precision by working in extended format
        d_times_x = $signed(d_value) * $signed(x_current);

        // 2 - d*x: represent 2 in the working format
        // 2 in Q(WORK_WIDTH) format with OUTPUT_FRAC_BITS fractional bits
        two_minus_dx = (WORK_WIDTH'(2) << OUTPUT_FRAC_BITS) - WORK_WIDTH'(d_times_x >>> OUTPUT_FRAC_BITS);

        // x * (2 - d*x)
        x_next_full = $signed(x_current) * $signed(two_minus_dx);

        // Extract result, accounting for double fractional bits
        x_next = WORK_WIDTH'(x_next_full >>> OUTPUT_FRAC_BITS);
    end

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
        ready = 1'b0;

        case (state)
            IDLE: begin
                ready = 1'b1;
                if (A_dv) begin
                    next_state = COMPUTING;
                end
            end

            COMPUTING: begin
                if (iteration_count >= iter_count_t'(NUM_ITERATIONS)) begin
                    next_state = DONE;
                end
            end

            DONE: begin
                next_state = IDLE;
            end

            default: next_state = IDLE;
        endcase
    end

    // Datapath
    always_ff @(posedge clk) begin
        if (~rstn) begin
            iteration_count <= '0;
            x_current <= '0;
            d_value <= '0;
            A_inv <= '0;
            A_inv_dv <= 1'b0;
        end else begin
            case (state)
                IDLE: begin
                    A_inv_dv <= 1'b0;
                    if (A_dv) begin
                        d_value <= A;
                        x_current <= initial_guess;
                        iteration_count <= '0;
                    end
                end

                COMPUTING: begin
                    x_current <= x_next;
                    iteration_count <= iteration_count + 1'd1;
                end

                DONE: begin
                    // Truncate to output width
                    A_inv <= OUTPUT_WIDTH'(x_current);
                    A_inv_dv <= 1'b1;
                    iteration_count <= '0;
                end

                default: begin
                    A_inv_dv <= 1'b0;
                end
            endcase
        end
    end

endmodule
