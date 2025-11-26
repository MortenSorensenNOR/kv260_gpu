`timescale 1ns / 1ps

module gpu_core #(
    parameter integer FRAMEBUF_ADDR_WIDTH = 32,
    parameter integer FRAMEBUF_DATA_WIDTH = 32
) (
    input  logic clk,
    input  logic rstn,

    // ctrl registers
    input  logic [31:0] cmd,
    input  logic        cmd_valid,

    input  logic [31:0] fb_base,
    input  logic [31:0] fb_stride,
    input  logic [31:0] fb_width,
    input  logic [31:0] fb_height,
    input  logic [31:0] clear_color,

    logic signed [31:0] v0[3],
    logic signed [31:0] v1[3],
    logic signed [31:0] v2[3],
    logic signed [31:0] v0_attr[3],
    logic signed [31:0] v1_attr[3],
    logic signed [31:0] v2_attr[3],

    // framebuffer signals
    output logic                             fb_wr_valid,
    input  logic                             fb_wr_ready,
    output logic [FRAMEBUF_ADDR_WIDTH-1 : 0] fb_wr_addr,
    output logic [FRAMEBUF_DATA_WIDTH-1 : 0] fb_wr_data,

    // status + debug
    output logic [31:0] status
);

    logic busy;
    logic clear_done;
    logic render_done;
    typedef enum logic [1:0] {
        NOP,
        CLEAR_OP,
        RENDER_OP
    } cmd_t;

    // module instantiations
    // command queue
    logic [31:0] current_cmd;
    logic        read_cmd;

    logic cmd_queue_empty, cmd_queue_full;
    fifo #(
        .DEPTH(32),
        .DWIDTH(32)
    ) fifo_inst (
        .clk   (clk),
        .rstn  (rstn),

        .din   (cmd),
        .wr_en (cmd_valid),

        .dout  (current_cmd),
        .rd_en (read_cmd),

        .empty (cmd_queue_empty),
        .full  (cmd_queue_full)
    );

    logic rasterizer_core_dv;
    logic w_rasterizer_core_ready;

    logic signed [31:0] w_fragment_x, w_fragment_y;
    logic signed [31:0] w_fragment_attr[4];
    logic        w_fragment_dv;
    logic        rasterizer_core_i_ready;

    logic w_rasterizer_core_done;
    logic w_rasterizer_core_culled_triangle;
    rasterizer_core #(
        .SIGNED        (1),
        .INT_BITS      (16),
        .FRAC_BITS     (16),
        .AREA_FRAC_BITS(12),
        .N_ATTR        (4),
    
        .SCREEN_WIDTH  (640),
        .SCREEN_HEIGHT (360)
    ) rasterizer_core_inst (
        .clk(clk),
        .rstn(rstn),

        .i_v0(v0),
        .i_v1(v1),
        .i_v2(v2),
        .i_attr_v0(v0_attr),
        .i_attr_v1(v1_attr),
        .i_attr_v2(v2_attr),
        .i_dv(rasterizer_core_dv),
        .o_ready(w_rasterizer_core_ready),
    
        .o_fragment_x(w_fragment_x),
        .o_fragment_y(w_fragment_y),
        .o_fragment_attr(w_fragment_attr),
        .o_dv(w_fragment_dv),
        .i_ready(rasterizer_core_i_ready),
    
        .done(w_rasterizer_core_done),
        .culled_triangle(w_rasterizer_core_culled_triangle)
    );

    // state machine logic
    typedef enum logic [2:0] {
        IDLE,
        READ_CMD,

        // clear
        CLEAR_WRITE,
        CLEAR_ADVANCE,
        CLEAR_DONE,

        // render
        RENDER,
        RENDER_DONE
    } state_t;
    state_t state, next_state;

    always_ff @(posedge clk) begin
        if (~rstn) begin
            state <= IDLE;
        end else begin
            state <= next_state;
        end
    end

    always_comb begin
        next_state = state;
        busy       = 1'b1;

        case (state)
            IDLE: begin
                busy = 1'b0;

                if (~cmd_queue_empty) begin
                    next_state = READ_CMD;
                end
            end

            READ_CMD: begin
                if (cmd_t'(current_cmd) == CLEAR_OP) begin
                    next_state = CLEAR_WRITE;
                end else if (cmd_t'(current_cmd) == RENDER_OP) begin
                    next_state = RENDER;
                end else begin
                    next_state = IDLE;
                end
            end

            CLEAR_WRITE: begin
                if (fb_wr_valid && fb_wr_ready) begin
                    next_state = CLEAR_ADVANCE;
                end
            end

            CLEAR_ADVANCE: begin
                if (x == fb_width - 1) begin
                    if (y == fb_height - 1) begin
                        next_state = CLEAR_DONE;
                    end else begin
                        next_state = CLEAR_WRITE;
                    end
                end else begin
                    next_state = CLEAR_WRITE;
                end
            end

            CLEAR_DONE: begin
                next_state = IDLE;
            end

            RENDER: begin
                if (w_rasterizer_core_done) begin
                    next_state = RENDER_DONE;
                end
            end

            // RENDER_DONE will fall through to default -> IDLE on next cycle
            default: begin
                next_state = IDLE;
            end
        endcase
    end

    // -------- fixed point color conversion: Q16.16 -> 8-bit 0..255 --------
    function automatic logic [7:0] fixed_to_8 (
        input logic signed [31:0] fx
    );
        logic [47:0] mult;
        logic [31:0] scaled;
        begin
            // clamp negative to 0
            if (fx[31]) begin
                fixed_to_8 = 8'h00;
            end else begin
                // approx: (fx * 255) >> 16
                mult   = fx * 16'd255;
                scaled = mult[47:16];  // >> 16

                // clamp >255
                if (scaled[31:8] != 0)
                    fixed_to_8 = 8'hFF;
                else
                    fixed_to_8 = scaled[7:0];
            end
        end
    endfunction

    // Handshake back to rasterizer: ready when we don't have a pending write,
    // or the pending write is being accepted.
    always_comb begin
        rasterizer_core_i_ready = (~fb_wr_valid) || fb_wr_ready;
    end

    logic [31:0] x, y;

    always_ff @(posedge clk) begin
        if (~rstn) begin
            read_cmd       <= '0;
            clear_done     <= '0;
            render_done    <= '0;

            fb_wr_valid    <= 1'b0;
            fb_wr_addr     <= '0;
            fb_wr_data     <= '0;

            rasterizer_core_dv <= 1'b0;

            x <= '0;
            y <= '0;
        end else begin
            case (state)
                IDLE: begin
                    x <= 0;
                    y <= 0;

                    fb_wr_valid        <= 1'b0;
                    rasterizer_core_dv <= 1'b0;

                    if (~cmd_queue_empty) begin
                        read_cmd <= 1'b1;
                    end else begin
                        read_cmd <= '0;
                    end
                end

                READ_CMD: begin
                    read_cmd           <= 1'b0;
                    rasterizer_core_dv <= 1'b0;

                    if (cmd_t'(current_cmd) == CLEAR_OP) begin
                        clear_done <= 1'b0;
                    end else if (cmd_t'(current_cmd) == RENDER_OP) begin
                        render_done <= 1'b0;
                    end
                end

                CLEAR_WRITE: begin
                    // issue clear write
                    fb_wr_addr  <= fb_base + (y * fb_stride) + (x << 2);
                    fb_wr_data  <= clear_color;
                    fb_wr_valid <= 1'b1;

                    if (fb_wr_valid && fb_wr_ready) begin
                        fb_wr_valid <= 1'b0;
                    end
                end

                CLEAR_ADVANCE: begin
                    if (x == fb_width - 1) begin
                        x <= 0;
                        if (y == fb_height - 1) begin
                            y <= 0;
                        end else begin
                            y <= y + 1;
                        end
                    end else begin
                        x <= x + 1;
                    end
                end

                CLEAR_DONE: begin
                    fb_wr_addr      <= '0;
                    fb_wr_data      <= '0;
                    fb_wr_valid     <= 1'b0;
                    clear_done      <= 1'b1;
                    rasterizer_core_dv <= 1'b0;
                end

                RENDER: begin
                    // Kick rasterizer when it is ready to accept a new triangle
                    if (w_rasterizer_core_ready) begin
                        rasterizer_core_dv <= 1'b1;
                    end else begin
                        rasterizer_core_dv <= 1'b0;
                    end

                    // When we get a fragment and we can accept it, write it to FB
                    if (w_fragment_dv && rasterizer_core_i_ready) begin
                        // optional bounds check vs fb_width/height
                        if ((w_fragment_x < fb_width) && (w_fragment_y < fb_height)) begin
                            fb_wr_addr <= fb_base
                                        + (w_fragment_y * fb_stride)
                                        + (w_fragment_x << 2);

                            // Pack as 0xRRGGBBAA
                            fb_wr_data <= {
                                fixed_to_8(w_fragment_attr[1]), // R
                                fixed_to_8(w_fragment_attr[2]), // G
                                fixed_to_8(w_fragment_attr[3]), // B
                                8'hFF
                            };

                            fb_wr_valid <= 1'b1;
                        end
                    end else if (fb_wr_valid && fb_wr_ready) begin
                        fb_wr_valid <= 1'b0;
                    end
                end

                RENDER_DONE: begin
                    // clean up after render
                    rasterizer_core_dv <= 1'b0;
                    fb_wr_valid        <= 1'b0;
                    render_done <= 1'b1;
                end

                default: begin
                    fb_wr_valid        <= 1'b0;
                    rasterizer_core_dv <= 1'b0;
                end
            endcase
        end
    end

    // status logic
    always_comb begin
        status[0]    = busy;
        status[1]    = clear_done;
        status[2]    = render_done;
        status[7:3]  = 0;
        status[15:8] = current_cmd[7:0];
        status[31:16]= 0;
    end

endmodule
