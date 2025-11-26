`timescale 1ns / 1ps

module gpu_core #(
    parameter integer SIGNED          = 1,
    parameter integer INT_BITS        = 16,
    parameter integer FRAC_BITS       = 16,
    parameter integer DATA_WIDTH      = INT_BITS + FRAC_BITS,
    parameter integer AREA_FRAC_BITS  = 10,
    parameter integer N_ATTR          = 4,  // depth, R, G, B

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
    output logic [31:0] status,

    output logic render_done_dbg,
    output logic [31:0] dbg_fragment_x,
    output logic [31:0] dbg_fragment_y,
    output logic        dbg_fragment_dv,
    output logic [31:0] dbg_fb_wr_addr,
    output logic [31:0] dbg_fb_wr_data,
    output logic        dbg_fb_wr_valid,
    output logic        dbg_fb_wr_ready
);

    logic busy;
    logic clear_done;
    logic render_started, render_has_culled, render_done;

    logic render_has_sampled;
    logic [7:0] render_color_sample;
    typedef enum logic [1:0] {
        NOP,
        CLEAR_OP,
        RENDER_OP
    } cmd_t;

    // ----------------------------------------------------------------
    // Command queue
    // ----------------------------------------------------------------
    logic [31:0] last_executed_cmd;
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

    // ----------------------------------------------------------------
    // Rasterizer core
    // ----------------------------------------------------------------
    logic rasterizer_core_dv;
    logic w_rasterizer_core_ready;

    logic signed [31:0] w_fragment_x, w_fragment_y;
    logic signed [31:0] w_fragment_attr[4];
    logic               w_fragment_dv;
    logic               rasterizer_core_i_ready;

    logic w_rasterizer_core_done;
    logic w_rasterizer_core_culled_triangle;

    rasterizer_core #(
        .SIGNED(SIGNED),
        .INT_BITS(INT_BITS),
        .FRAC_BITS(FRAC_BITS),
        .AREA_FRAC_BITS(AREA_FRAC_BITS),
        .N_ATTR(N_ATTR)
    ) rasterizer_core_inst (
        .clk(clk),
        .rstn(rstn),

        .screen_width(fb_width),
        .screen_height(fb_height),

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

    // ----------------------------------------------------------------
    // State machine
    // ----------------------------------------------------------------
    typedef enum logic [2:0] {
        IDLE,
        READ_CMD,
        CMD_EXEC,

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

    // loop coords for clear
    logic [31:0] x, y;

    // regs for clear write (addr/data/valid)
    logic                             clear_wr_valid_r;
    logic [FRAMEBUF_ADDR_WIDTH-1 : 0] clear_wr_addr_r;
    logic [FRAMEBUF_DATA_WIDTH-1 : 0] clear_wr_data_r;

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

    // Convert Q16.16 -> integer pixel coords
    logic [31:0] frag_x_int;
    logic [31:0] frag_y_int;
    assign frag_x_int = {16'b0, w_fragment_x[DATA_WIDTH-1:FRAC_BITS]};
    assign frag_y_int = {16'b0, w_fragment_y[DATA_WIDTH-1:FRAC_BITS]};

    // ----------------------------------------------------------------
    // Next-state logic
    // ----------------------------------------------------------------
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
                next_state = CMD_EXEC;
            end

            CMD_EXEC: begin
                unique case (cmd_t'(current_cmd))
                    CLEAR_OP:  next_state = CLEAR_WRITE;
                    RENDER_OP: next_state = RENDER;
                    default:   next_state = IDLE;
                endcase
            end

            // clear FSM: wait for one write, then advance x/y
            CLEAR_WRITE: begin
                if (clear_wr_valid_r && fb_wr_ready)
                    next_state = CLEAR_ADVANCE;
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

    // ----------------------------------------------------------------
    // Sequential logic
    // ----------------------------------------------------------------
    always_ff @(posedge clk) begin
        if (~rstn) begin
            read_cmd            <= '0;
            clear_done          <= '0;
            render_started      <= '0;
            render_has_culled   <= '0;
            render_done         <= '0;

            render_has_sampled  <= '0;
            render_color_sample <= '0;
            last_executed_cmd   <= '0;

            rasterizer_core_dv  <= 1'b0;

            x <= '0;
            y <= '0;

            clear_wr_valid_r <= 1'b0;
            clear_wr_addr_r  <= '0;
            clear_wr_data_r  <= '0;
        end else begin
            case (state)
                IDLE: begin
                    x <= 0;
                    y <= 0;

                    rasterizer_core_dv <= 1'b0;
                    clear_wr_valid_r   <= 1'b0;

                    if (~cmd_queue_empty)
                        read_cmd <= 1'b1;
                    else
                        read_cmd <= 1'b0;
                end

                READ_CMD: begin
                    read_cmd           <= 1'b0;
                    rasterizer_core_dv <= 1'b0;
                end

                CMD_EXEC: begin
                    if (cmd_t'(current_cmd) == CLEAR_OP) begin
                        clear_done <= 1'b0;
                    end else if (cmd_t'(current_cmd) == RENDER_OP) begin
                        render_done       <= 1'b0;
                        render_has_culled <= 1'b0;
                        render_started    <= 1'b1;
                        render_has_sampled  <= 1'b0;
                    end
                    last_executed_cmd <= current_cmd;
                end

                // ---------------- CLEAR PATH ----------------
                CLEAR_WRITE: begin
                    // If not currently holding a pending write, generate one
                    if (!clear_wr_valid_r) begin
                        clear_wr_addr_r  <= fb_base + (y * fb_stride) + (x << 2);
                        clear_wr_data_r  <= clear_color;
                        clear_wr_valid_r <= 1'b1;
                    end

                    // Once AXI writer accepts it, drop valid flag
                    if (clear_wr_valid_r && fb_wr_ready) begin
                        clear_wr_valid_r <= 1'b0;
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
                    clear_done         <= 1'b1;
                    clear_wr_valid_r   <= 1'b0;
                    rasterizer_core_dv <= 1'b0;
                end

                // ---------------- RENDER PATH ----------------
                RENDER: begin
                    // Kick rasterizer when it is ready to accept a new triangle
                    if (w_rasterizer_core_ready)
                        rasterizer_core_dv <= 1'b1;
                    else
                        rasterizer_core_dv <= 1'b0;

                    if (w_rasterizer_core_culled_triangle)
                        render_has_culled <= 1'b1;

                    // Debug sample: first fragment color
                    if (w_fragment_dv && rasterizer_core_i_ready && !render_has_sampled) begin
                        render_color_sample <= fixed_to_8(w_fragment_attr[1]);
                        render_has_sampled  <= 1'b1;
                    end
                end

                RENDER_DONE: begin
                    rasterizer_core_dv <= 1'b0;
                    render_done        <= 1'b1;
                end

                default: begin
                    rasterizer_core_dv <= 1'b0;
                end
            endcase
        end
    end

    // ----------------------------------------------------------------
    // Combinational outputs / mux to AXI writer
    // ----------------------------------------------------------------
    always_comb begin
        // defaults
        fb_wr_valid          = 1'b0;
        fb_wr_addr           = '0;
        fb_wr_data           = '0;
        rasterizer_core_i_ready = 1'b0;

        case (state)
            // CLEAR: drive from clear regs
            CLEAR_WRITE: begin
                fb_wr_valid = clear_wr_valid_r;
                fb_wr_addr  = clear_wr_addr_r;
                fb_wr_data  = clear_wr_data_r;
            end

            // RENDER: drive directly from backend fragment stream
            RENDER: begin
                // backend only produces o_dv when i_ready is 1;
                // here we connect i_ready directly to fb_wr_ready
                rasterizer_core_i_ready = fb_wr_ready;

                fb_wr_valid = w_fragment_dv;
                fb_wr_addr  = fb_base + (frag_y_int * fb_stride) + (frag_x_int << 2);
                fb_wr_data  = {
                    8'hFF,
                    fixed_to_8(w_fragment_attr[1]),
                    fixed_to_8(w_fragment_attr[2]),
                    fixed_to_8(w_fragment_attr[3])
                };
            end

            default: begin
                // nothing
            end
        endcase
    end

    // ----------------------------------------------------------------
    // Status / debug
    // ----------------------------------------------------------------
    always_comb begin
        status[0]    = busy;
        status[1]    = clear_done;
        status[2]    = render_started;
        status[3]    = render_has_culled;
        status[4]    = render_done;
        status[5]    = render_has_sampled;
        status[7:6]  = 0;
        status[15:8] = render_color_sample;
        status[31:24]= last_executed_cmd[7:0];
    end

    assign render_done_dbg = render_done;
    assign dbg_fragment_x   = w_fragment_x;
    assign dbg_fragment_y   = w_fragment_y;
    assign dbg_fragment_dv  = w_fragment_dv;
    assign dbg_fb_wr_addr   = fb_wr_addr;
    assign dbg_fb_wr_data   = fb_wr_data;
    assign dbg_fb_wr_valid  = fb_wr_valid;
    assign dbg_fb_wr_ready  = fb_wr_ready;

endmodule
