`timescale 1ns / 1ps

module gpu_top #(
    // Parameters of Axi Slave Bus Interface S_AXI_CTRL
    parameter integer C_S_AXI_CTRL_DATA_WIDTH = 32,
    parameter integer C_S_AXI_CTRL_ADDR_WIDTH = 7,

    // Parameters of Axi Master Bus Interface M_AXI_FRAMEBUF
    parameter  C_M_AXI_FRAMEBUF_TARGET_SLAVE_BASE_ADDR = 32'h00000000,
    parameter integer C_M_AXI_FRAMEBUF_BURST_LEN       = 16,
    parameter integer C_M_AXI_FRAMEBUF_ID_WIDTH        = 1,
    parameter integer C_M_AXI_FRAMEBUF_ADDR_WIDTH      = 32,
    parameter integer C_M_AXI_FRAMEBUF_DATA_WIDTH      = 32,
    parameter integer C_M_AXI_FRAMEBUF_AWUSER_WIDTH    = 0,
    parameter integer C_M_AXI_FRAMEBUF_ARUSER_WIDTH    = 0,
    parameter integer C_M_AXI_FRAMEBUF_WUSER_WIDTH     = 0,
    parameter integer C_M_AXI_FRAMEBUF_RUSER_WIDTH     = 0,
    parameter integer C_M_AXI_FRAMEBUF_BUSER_WIDTH     = 0
) (
    // Ports of Axi Slave Bus Interface S_AXI_CTRL
    input  logic                                     s_axi_ctrl_aclk,
    input  logic                                     s_axi_ctrl_aresetn,
    input  logic [C_S_AXI_CTRL_ADDR_WIDTH-1     : 0] s_axi_ctrl_awaddr,
    input  logic [2 : 0]                             s_axi_ctrl_awprot,
    input  logic                                     s_axi_ctrl_awvalid,
    output logic                                     s_axi_ctrl_awready,
    input  logic [C_S_AXI_CTRL_DATA_WIDTH-1     : 0] s_axi_ctrl_wdata,
    input  logic [(C_S_AXI_CTRL_DATA_WIDTH/8)-1 : 0] s_axi_ctrl_wstrb,
    input  logic                                     s_axi_ctrl_wvalid,
    output logic                                     s_axi_ctrl_wready,
    output logic [1 : 0]                             s_axi_ctrl_bresp,
    output logic                                     s_axi_ctrl_bvalid,
    input  logic                                     s_axi_ctrl_bready,
    input  logic [C_S_AXI_CTRL_ADDR_WIDTH-1     : 0] s_axi_ctrl_araddr,
    input  logic [2 : 0]                             s_axi_ctrl_arprot,
    input  logic                                     s_axi_ctrl_arvalid,
    output logic                                     s_axi_ctrl_arready,
    output logic [C_S_AXI_CTRL_DATA_WIDTH-1     : 0] s_axi_ctrl_rdata,
    output logic [1 : 0]                             s_axi_ctrl_rresp,
    output logic                                     s_axi_ctrl_rvalid,
    input  logic                                     s_axi_ctrl_rready,

    // Ports of Axi Master Bus Interface M_AXI_FRAMEBUF
    input  logic                                       m_axi_framebuf_aclk,
    input  logic                                       m_axi_framebuf_aresetn,
    output logic [C_M_AXI_FRAMEBUF_ID_WIDTH-1     : 0] m_axi_framebuf_awid,
    output logic [C_M_AXI_FRAMEBUF_ADDR_WIDTH-1   : 0] m_axi_framebuf_awaddr,
    output logic [7 : 0]                               m_axi_framebuf_awlen,
    output logic [2 : 0]                               m_axi_framebuf_awsize,
    output logic [1 : 0]                               m_axi_framebuf_awburst,
    output logic                                       m_axi_framebuf_awlock,
    output logic [3 : 0]                               m_axi_framebuf_awcache,
    output logic [2 : 0]                               m_axi_framebuf_awprot,
    output logic [3 : 0]                               m_axi_framebuf_awqos,
    output logic [C_M_AXI_FRAMEBUF_AWUSER_WIDTH-1 : 0] m_axi_framebuf_awuser,
    output logic                                       m_axi_framebuf_awvalid,
    input  logic                                       m_axi_framebuf_awready,
    output logic [C_M_AXI_FRAMEBUF_DATA_WIDTH-1   : 0] m_axi_framebuf_wdata,
    output logic [C_M_AXI_FRAMEBUF_DATA_WIDTH/8-1 : 0] m_axi_framebuf_wstrb,
    output logic                                       m_axi_framebuf_wlast,
    output logic [C_M_AXI_FRAMEBUF_WUSER_WIDTH-1  : 0] m_axi_framebuf_wuser,
    output logic                                       m_axi_framebuf_wvalid,
    input  logic                                       m_axi_framebuf_wready,
    input  logic [C_M_AXI_FRAMEBUF_ID_WIDTH-1     : 0] m_axi_framebuf_bid,
    input  logic [1 : 0]                               m_axi_framebuf_bresp,
    input  logic [C_M_AXI_FRAMEBUF_BUSER_WIDTH-1  : 0] m_axi_framebuf_buser,
    input  logic                                       m_axi_framebuf_bvalid,
    output logic                                       m_axi_framebuf_bready,
    output logic [C_M_AXI_FRAMEBUF_ID_WIDTH-1     : 0] m_axi_framebuf_arid,
    output logic [C_M_AXI_FRAMEBUF_ADDR_WIDTH-1   : 0] m_axi_framebuf_araddr,
    output logic [7 : 0]                               m_axi_framebuf_arlen,
    output logic [2 : 0]                               m_axi_framebuf_arsize,
    output logic [1 : 0]                               m_axi_framebuf_arburst,
    output logic                                       m_axi_framebuf_arlock,
    output logic [3 : 0]                               m_axi_framebuf_arcache,
    output logic [2 : 0]                               m_axi_framebuf_arprot,
    output logic [3 : 0]                               m_axi_framebuf_arqos,
    output logic [C_M_AXI_FRAMEBUF_ARUSER_WIDTH-1 : 0] m_axi_framebuf_aruser,
    output logic                                       m_axi_framebuf_arvalid,
    input  logic                                       m_axi_framebuf_arready,
    input  logic [C_M_AXI_FRAMEBUF_ID_WIDTH-1     : 0] m_axi_framebuf_rid,
    input  logic [C_M_AXI_FRAMEBUF_DATA_WIDTH-1   : 0] m_axi_framebuf_rdata,
    input  logic [1 : 0]                               m_axi_framebuf_rresp,
    input  logic                                       m_axi_framebuf_rlast,
    input  logic [C_M_AXI_FRAMEBUF_RUSER_WIDTH-1  : 0] m_axi_framebuf_ruser,
    input  logic                                       m_axi_framebuf_rvalid,
    output logic                                       m_axi_framebuf_rready,

    output logic [31:0] dbg_fragment_x,
    output logic [31:0] dbg_fragment_y,
    output logic        dbg_fragment_dv,
    output logic [31:0] dbg_fb_wr_addr,
    output logic [31:0] dbg_fb_wr_data,
    output logic        dbg_fb_wr_valid,
    output logic        dbg_fb_wr_ready
);

    // TODO: Right now I only have axi ports for ctrl and for the framebuffer
    // I need a general data interface for the gpu. There are two choices:
    // 1. Another master axi port that can read from DRAM. This means that 
    //    the cpu writes some data to a buffer in DRAM, sets the relevant
    //    attributes for the gpu, i.e. pointer, data type, stride etc. and the
    //    gpu auto fetches this data as it is needed. This could work quite
    //    well.
    // 2. A slave axi port where the cpu writes data to local buffers on the
    //    gpu. This would mean that I would have to instantiate BRAM buffers
    //    in PL, have the gpu read directly from these, and have the cpu
    //    manage the layout of data when it does its writes.
    //
    // In a "traditional" gpu sense, the common approach is to use descriptors
    // of some kind that the gpu uses to know where to look for data. This
    // would align best with option (1). I'm just unsure if I want to commit
    // myself to that right now, as this is still quite early in the testing
    // phase, and implementing a full on discriptor set model might be more
    // work than it is worth for right now, though the idea of doing things
    // "propperly" is still nice.

    // AXI CTRL
    logic [31:0] w_status;
    logic [31:0] w_cmd;
    logic        w_cmd_valid;
    logic [31:0] w_fb_base;
    logic [31:0] w_fb_stride;
    logic [31:0] w_fb_width;
    logic [31:0] w_fb_height;
    logic [31:0] w_clear_color;

    logic signed [31:0] w_v0[3];
    logic signed [31:0] w_v1[3];
    logic signed [31:0] w_v2[3];
    logic signed [31:0] w_v0_attr[3];
    logic signed [31:0] w_v1_attr[3];
    logic signed [31:0] w_v2_attr[3];

    // AXI FRAMEBUF
    logic                                      w_usr_wr_valid;
    logic                                      w_usr_wr_ready;
    logic [C_M_AXI_FRAMEBUF_ADDR_WIDTH-1 : 0]  w_usr_wr_addr;
    logic [C_M_AXI_FRAMEBUF_DATA_WIDTH-1 : 0]  w_usr_wr_data;

    // Instantiation of Axi Bus Interface S_AXI_CTRL
    gpu_top_s_axi_lite_ctrl # (
        .C_S_AXI_DATA_WIDTH(C_S_AXI_CTRL_DATA_WIDTH),
        .C_S_AXI_ADDR_WIDTH(C_S_AXI_CTRL_ADDR_WIDTH)
    ) gpu_top_s_axi_lite_ctrl_inst (
        .i_status     (w_status),
        .o_cmd        (w_cmd),
        .o_cmd_valid  (w_cmd_valid),
        .o_fb_base    (w_fb_base),
        .o_fb_stride  (w_fb_stride),
        .o_fb_width   (w_fb_width),
        .o_fb_height  (w_fb_height),
        .o_clear_color(w_clear_color),

        .o_v0(w_v0),
        .o_v1(w_v1),
        .o_v2(w_v2),
        .o_v0_attr(w_v0_attr),
        .o_v1_attr(w_v1_attr),
        .o_v2_attr(w_v2_attr),

        .S_AXI_ACLK(s_axi_ctrl_aclk),
        .S_AXI_ARESETN(s_axi_ctrl_aresetn),
        .S_AXI_AWADDR(s_axi_ctrl_awaddr),
        .S_AXI_AWPROT(s_axi_ctrl_awprot),
        .S_AXI_AWVALID(s_axi_ctrl_awvalid),
        .S_AXI_AWREADY(s_axi_ctrl_awready),
        .S_AXI_WDATA(s_axi_ctrl_wdata),
        .S_AXI_WSTRB(s_axi_ctrl_wstrb),
        .S_AXI_WVALID(s_axi_ctrl_wvalid),
        .S_AXI_WREADY(s_axi_ctrl_wready),
        .S_AXI_BRESP(s_axi_ctrl_bresp),
        .S_AXI_BVALID(s_axi_ctrl_bvalid),
        .S_AXI_BREADY(s_axi_ctrl_bready),
        .S_AXI_ARADDR(s_axi_ctrl_araddr),
        .S_AXI_ARPROT(s_axi_ctrl_arprot),
        .S_AXI_ARVALID(s_axi_ctrl_arvalid),
        .S_AXI_ARREADY(s_axi_ctrl_arready),
        .S_AXI_RDATA(s_axi_ctrl_rdata),
        .S_AXI_RRESP(s_axi_ctrl_rresp),
        .S_AXI_RVALID(s_axi_ctrl_rvalid),
        .S_AXI_RREADY(s_axi_ctrl_rready)
    );

    // Instantiation of Axi Bus Interface M_AXI_FRAMEBUF
    gpu_top_m_axi_full_framebuf #(
        .C_M_TARGET_SLAVE_BASE_ADDR(C_M_AXI_FRAMEBUF_TARGET_SLAVE_BASE_ADDR),
        .C_M_AXI_BURST_LEN(C_M_AXI_FRAMEBUF_BURST_LEN),
        .C_M_AXI_ID_WIDTH(C_M_AXI_FRAMEBUF_ID_WIDTH),
        .C_M_AXI_ADDR_WIDTH(C_M_AXI_FRAMEBUF_ADDR_WIDTH),
        .C_M_AXI_DATA_WIDTH(C_M_AXI_FRAMEBUF_DATA_WIDTH),
        .C_M_AXI_AWUSER_WIDTH(C_M_AXI_FRAMEBUF_AWUSER_WIDTH),
        .C_M_AXI_ARUSER_WIDTH(C_M_AXI_FRAMEBUF_ARUSER_WIDTH),
        .C_M_AXI_WUSER_WIDTH(C_M_AXI_FRAMEBUF_WUSER_WIDTH),
        .C_M_AXI_RUSER_WIDTH(C_M_AXI_FRAMEBUF_RUSER_WIDTH),
        .C_M_AXI_BUSER_WIDTH(C_M_AXI_FRAMEBUF_BUSER_WIDTH)
    ) gpu_top_m_axi_full_framebuf_inst (
        .usr_wr_valid(w_usr_wr_valid),
        .usr_wr_ready(w_usr_wr_ready),
        .usr_wr_addr(w_usr_wr_addr),
        .usr_wr_data(w_usr_wr_data),

        .M_AXI_ACLK(m_axi_framebuf_aclk),
        .M_AXI_ARESETN(m_axi_framebuf_aresetn),
        .M_AXI_AWID(m_axi_framebuf_awid),
        .M_AXI_AWADDR(m_axi_framebuf_awaddr),
        .M_AXI_AWLEN(m_axi_framebuf_awlen),
        .M_AXI_AWSIZE(m_axi_framebuf_awsize),
        .M_AXI_AWBURST(m_axi_framebuf_awburst),
        .M_AXI_AWLOCK(m_axi_framebuf_awlock),
        .M_AXI_AWCACHE(m_axi_framebuf_awcache),
        .M_AXI_AWPROT(m_axi_framebuf_awprot),
        .M_AXI_AWQOS(m_axi_framebuf_awqos),
        .M_AXI_AWUSER(m_axi_framebuf_awuser),
        .M_AXI_AWVALID(m_axi_framebuf_awvalid),
        .M_AXI_AWREADY(m_axi_framebuf_awready),
        .M_AXI_WDATA(m_axi_framebuf_wdata),
        .M_AXI_WSTRB(m_axi_framebuf_wstrb),
        .M_AXI_WLAST(m_axi_framebuf_wlast),
        .M_AXI_WUSER(m_axi_framebuf_wuser),
        .M_AXI_WVALID(m_axi_framebuf_wvalid),
        .M_AXI_WREADY(m_axi_framebuf_wready),
        .M_AXI_BID(m_axi_framebuf_bid),
        .M_AXI_BRESP(m_axi_framebuf_bresp),
        .M_AXI_BUSER(m_axi_framebuf_buser),
        .M_AXI_BVALID(m_axi_framebuf_bvalid),
        .M_AXI_BREADY(m_axi_framebuf_bready),
        .M_AXI_ARID(m_axi_framebuf_arid),
        .M_AXI_ARADDR(m_axi_framebuf_araddr),
        .M_AXI_ARLEN(m_axi_framebuf_arlen),
        .M_AXI_ARSIZE(m_axi_framebuf_arsize),
        .M_AXI_ARBURST(m_axi_framebuf_arburst),
        .M_AXI_ARLOCK(m_axi_framebuf_arlock),
        .M_AXI_ARCACHE(m_axi_framebuf_arcache),
        .M_AXI_ARPROT(m_axi_framebuf_arprot),
        .M_AXI_ARQOS(m_axi_framebuf_arqos),
        .M_AXI_ARUSER(m_axi_framebuf_aruser),
        .M_AXI_ARVALID(m_axi_framebuf_arvalid),
        .M_AXI_ARREADY(m_axi_framebuf_arready),
        .M_AXI_RID(m_axi_framebuf_rid),
        .M_AXI_RDATA(m_axi_framebuf_rdata),
        .M_AXI_RRESP(m_axi_framebuf_rresp),
        .M_AXI_RLAST(m_axi_framebuf_rlast),
        .M_AXI_RUSER(m_axi_framebuf_ruser),
        .M_AXI_RVALID(m_axi_framebuf_rvalid),
        .M_AXI_RREADY(m_axi_framebuf_rready)
    );

    gpu_core #(
        .FRAMEBUF_ADDR_WIDTH(C_M_AXI_FRAMEBUF_ADDR_WIDTH),
        .FRAMEBUF_DATA_WIDTH(C_M_AXI_FRAMEBUF_DATA_WIDTH)
    ) gpu_core_inst (
        .clk(s_axi_ctrl_aclk),
        .rstn(s_axi_ctrl_aresetn),

        .cmd        (w_cmd),
        .cmd_valid  (w_cmd_valid),
        .fb_base    (w_fb_base),
        .fb_stride  (w_fb_stride),
        .fb_width   (w_fb_width),
        .fb_height  (w_fb_height),
        .clear_color(w_clear_color),

        .v0(w_v0),
        .v1(w_v1),
        .v2(w_v2),
        .v0_attr(w_v0_attr),
        .v1_attr(w_v1_attr),
        .v2_attr(w_v2_attr),

        .fb_wr_valid(w_usr_wr_valid),
        .fb_wr_ready(w_usr_wr_ready),
        .fb_wr_addr(w_usr_wr_addr),
        .fb_wr_data(w_usr_wr_data),

        .status(w_status),

        .render_done_dbg(),
        .dbg_fragment_x(dbg_fragment_x),
        .dbg_fragment_y(dbg_fragment_y),
        .dbg_fragment_dv(dbg_fragment_dv),
        .dbg_fb_wr_addr(dbg_fb_wr_addr),
        .dbg_fb_wr_data(dbg_fb_wr_data),
        .dbg_fb_wr_valid(dbg_fb_wr_valid),
        .dbg_fb_wr_ready(dbg_fb_wr_ready)
    );

endmodule
