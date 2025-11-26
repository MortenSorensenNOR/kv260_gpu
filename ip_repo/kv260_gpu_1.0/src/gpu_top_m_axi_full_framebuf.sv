`timescale 1 ns / 1 ps

module gpu_top_m_axi_full_framebuf #(
    // Base address of targeted slave (acts as a base for usr_wr_addr)
    parameter C_M_TARGET_SLAVE_BASE_ADDR    = 32'h40000000,
    // Burst Length (kept for compatibility, but we use single-beat writes)
    parameter integer C_M_AXI_BURST_LEN    = 16,
    // Thread ID Width
    parameter integer C_M_AXI_ID_WIDTH    = 1,
    // Width of Address Bus
    parameter integer C_M_AXI_ADDR_WIDTH    = 32,
    // Width of Data Bus
    parameter integer C_M_AXI_DATA_WIDTH    = 32,
    // Width of User Write Address Bus
    parameter integer C_M_AXI_AWUSER_WIDTH    = 0,
    // Width of User Read Address Bus
    parameter integer C_M_AXI_ARUSER_WIDTH    = 0,
    // Width of User Write Data Bus
    parameter integer C_M_AXI_WUSER_WIDTH    = 0,
    // Width of User Read Data Bus
    parameter integer C_M_AXI_RUSER_WIDTH    = 0,
    // Width of User Response Bus
    parameter integer C_M_AXI_BUSER_WIDTH    = 0
) (
    // Simple write-only user interface
    input  logic                             usr_wr_valid,
    output logic                             usr_wr_ready,
    input  logic [C_M_AXI_ADDR_WIDTH-1 : 0]  usr_wr_addr,  // offset from C_M_TARGET_SLAVE_BASE_ADDR
    input  logic [C_M_AXI_DATA_WIDTH-1 : 0]  usr_wr_data,

    // Initiate AXI transactions (unused in this simplified version)
    input  logic  INIT_AXI_TXN,
    // Asserts when transaction is complete (unused; tied low)
    output logic  TXN_DONE,
    // Asserts when ERROR is detected (unused; tied low)
    output logic   ERROR,

    // Global Clock Signal.
    input  logic  M_AXI_ACLK,
    // Global Reset Signal. This signal is Active Low
    input  logic  M_AXI_ARESETN,

    // Master Interface Write Address ID
    output logic [C_M_AXI_ID_WIDTH-1 : 0]    M_AXI_AWID,
    // Master Interface Write Address
    output logic [C_M_AXI_ADDR_WIDTH-1 : 0]  M_AXI_AWADDR,
    // Burst length. The burst length gives the exact number of transfers in a burst
    output logic [7 : 0]                     M_AXI_AWLEN,
    // Burst size. This signal indicates the size of each transfer in the burst
    output logic [2 : 0]                     M_AXI_AWSIZE,
    // Burst type. The burst type and the size information,
    // determine how the address for each transfer within the burst is calculated.
    output logic [1 : 0]                     M_AXI_AWBURST,
    // Lock type. Provides additional information about the
    // atomic characteristics of the transfer.
    output logic                             M_AXI_AWLOCK,
    // Memory type. This signal indicates how transactions
    // are required to progress through a system.
    output logic [3 : 0]                     M_AXI_AWCACHE,
    // Protection type. This signal indicates the privilege
    // and security level of the transaction, and whether
    // the transaction is a data access or an instruction access.
    output logic [2 : 0]                     M_AXI_AWPROT,
    // Quality of Service, QoS identifier sent for each write transaction.
    output logic [3 : 0]                     M_AXI_AWQOS,
    // Optional User-defined signal in the write address channel.
    output logic [C_M_AXI_AWUSER_WIDTH-1:0]  M_AXI_AWUSER,
    // Write address valid. This signal indicates that
    // the channel is signaling valid write address and control information.
    output logic                             M_AXI_AWVALID,
    // Write address ready. This signal indicates that
    // the slave is ready to accept an address and associated control signals
    input  logic                             M_AXI_AWREADY,

    // Master Interface Write Data.
    output logic [C_M_AXI_DATA_WIDTH-1 : 0]  M_AXI_WDATA,
    // Write strobes. This signal indicates which byte
    // lanes hold valid data. There is one write strobe
    // bit for each eight bits of the write data bus.
    output logic [C_M_AXI_DATA_WIDTH/8-1:0]  M_AXI_WSTRB,
    // Write last. This signal indicates the last transfer in a write burst.
    output logic                             M_AXI_WLAST,
    // Optional User-defined signal in the write data channel.
    output logic [C_M_AXI_WUSER_WIDTH-1:0]   M_AXI_WUSER,
    // Write valid. This signal indicates that valid write
    // data and strobes are available
    output logic                             M_AXI_WVALID,
    // Write ready. This signal indicates that the slave
    // can accept the write data.
    input  logic                             M_AXI_WREADY,

    // Master Interface Write Response.
    input  logic [C_M_AXI_ID_WIDTH-1 : 0]    M_AXI_BID,
    // Write response. This signal indicates the status of the write transaction.
    input  logic [1 : 0]                     M_AXI_BRESP,
    // Optional User-defined signal in the write response channel
    input  logic [C_M_AXI_BUSER_WIDTH-1 : 0] M_AXI_BUSER,
    // Write response valid. This signal indicates that the
    // channel is signaling a valid write response.
    input  logic                             M_AXI_BVALID,
    // Response ready. This signal indicates that the master
    // can accept a write response.
    output logic                             M_AXI_BREADY,

    // Master Interface Read Address.
    output logic [C_M_AXI_ID_WIDTH-1 : 0]    M_AXI_ARID,
    // Read address. This signal indicates the initial
    // address of a read burst transaction.
    output logic [C_M_AXI_ADDR_WIDTH-1 : 0]  M_AXI_ARADDR,
    // Burst length. The burst length gives the exact number of transfers in a burst
    output logic [7 : 0]                     M_AXI_ARLEN,
    // Burst size. This signal indicates the size of each transfer in the burst
    output logic [2 : 0]                     M_AXI_ARSIZE,
    // Burst type. The burst type and the size information,
    // determine how the address for each transfer within the burst is calculated.
    output logic [1 : 0]                     M_AXI_ARBURST,
    // Lock type. Provides additional information about the
    // atomic characteristics of the transfer.
    output logic                             M_AXI_ARLOCK,
    // Memory type. This signal indicates how transactions
    // are required to progress through a system.
    output logic [3 : 0]                     M_AXI_ARCACHE,
    // Protection type. This signal indicates the privilege
    // and security level of the transaction, and whether
    // the transaction is a data access or an instruction access.
    output logic [2 : 0]                     M_AXI_ARPROT,
    // Quality of Service, QoS identifier sent for each read transaction
    output logic [3 : 0]                     M_AXI_ARQOS,
    // Optional User-defined signal in the read address channel.
    output logic [C_M_AXI_ARUSER_WIDTH-1:0]  M_AXI_ARUSER,
    // Read address valid. This signal indicates that
    // the channel is signaling valid read address and control information
    output logic                             M_AXI_ARVALID,
    // Read address ready. This signal indicates that
    // the slave is ready to accept an address and associated control signals
    input  logic                             M_AXI_ARREADY,
    // Read ID tag. This signal is the identification tag
    // for the read data group of signals generated by the slave.
    input  logic [C_M_AXI_ID_WIDTH-1 : 0]    M_AXI_RID,
    // Master Read Data
    input  logic [C_M_AXI_DATA_WIDTH-1 : 0]  M_AXI_RDATA,
    // Read response. This signal indicates the status of the read transfer
    input  logic [1 : 0]                     M_AXI_RRESP,
    // Read last. This signal indicates the last transfer in a read burst
    input  logic                             M_AXI_RLAST,
    // Optional User-defined signal in the read address channel.
    input  logic [C_M_AXI_RUSER_WIDTH-1 : 0] M_AXI_RUSER,
    // Read valid. This signal indicates that the channel
    // is signaling the required read data.
    input  logic                             M_AXI_RVALID,
    // Read ready. This signal indicates that the master can
    // accept the read data and response information.
    output logic                             M_AXI_RREADY
);

    // ---------------------------
    // Utility: clogb2
    // ---------------------------
    function integer clogb2 (input integer bit_depth);
        begin
            for (clogb2 = 0; bit_depth > 0; clogb2 = clogb2+1)
                bit_depth = bit_depth >> 1;
        end
    endfunction

    // ---------------------------
    // Simple write FSM
    // ---------------------------

    localparam W_IDLE = 2'd0,
               W_AW   = 2'd1,
               W_W    = 2'd2,  // not really needed separately, but kept for clarity
               W_B    = 2'd3;

    logic [1:0] wstate;

    // AXI write address/data/control regs
    logic [C_M_AXI_ADDR_WIDTH-1 : 0] axi_awaddr;
    logic                            axi_awvalid;
    logic [C_M_AXI_DATA_WIDTH-1 : 0] axi_wdata;
    logic                            axi_wvalid;
    logic                            axi_wlast;
    logic                            axi_bready;

    // ---------------------------
    // AXI write channel assignments
    // ---------------------------

    // IDs (single ID)
    assign M_AXI_AWID    = {C_M_AXI_ID_WIDTH{1'b0}};

    // Use base address + user offset
    assign M_AXI_AWADDR  = C_M_TARGET_SLAVE_BASE_ADDR + axi_awaddr;

    // Single-beat burst (AWLEN = 0 => 1 transfer)
    assign M_AXI_AWLEN   = 8'd0;

    // Size = log2(bytes per beat)
    assign M_AXI_AWSIZE  = clogb2((C_M_AXI_DATA_WIDTH/8) - 1);

    // INCR burst
    assign M_AXI_AWBURST = 2'b01;

    assign M_AXI_AWLOCK  = 1'b0;
    assign M_AXI_AWCACHE = 4'b0010;
    assign M_AXI_AWPROT  = 3'h0;
    assign M_AXI_AWQOS   = 4'h0;
    assign M_AXI_AWUSER  = {C_M_AXI_AWUSER_WIDTH{1'b0}};
    assign M_AXI_AWVALID = axi_awvalid;

    // Write data
    assign M_AXI_WDATA   = axi_wdata;
    assign M_AXI_WSTRB   = {(C_M_AXI_DATA_WIDTH/8){1'b1}};
    assign M_AXI_WLAST   = axi_wlast;
    assign M_AXI_WUSER   = {C_M_AXI_WUSER_WIDTH{1'b0}};
    assign M_AXI_WVALID  = axi_wvalid;

    // Write response
    assign M_AXI_BREADY  = axi_bready;

    // ---------------------------
    // AXI read channel: disabled (we're write-only)
    // ---------------------------

    assign M_AXI_ARID    = {C_M_AXI_ID_WIDTH{1'b0}};
    assign M_AXI_ARADDR  = {C_M_AXI_ADDR_WIDTH{1'b0}};
    assign M_AXI_ARLEN   = 8'd0;
    assign M_AXI_ARSIZE  = clogb2((C_M_AXI_DATA_WIDTH/8) - 1);
    assign M_AXI_ARBURST = 2'b01;
    assign M_AXI_ARLOCK  = 1'b0;
    assign M_AXI_ARCACHE = 4'b0010;
    assign M_AXI_ARPROT  = 3'h0;
    assign M_AXI_ARQOS   = 4'h0;
    assign M_AXI_ARUSER  = {C_M_AXI_ARUSER_WIDTH{1'b0}};
    assign M_AXI_ARVALID = 1'b0;                  // never initiate reads
    assign M_AXI_RREADY  = 1'b0;                  // never accept reads

    // ---------------------------
    // User / status
    // ---------------------------

    // Simple ready: user can present a new transfer in IDLE
    assign usr_wr_ready = (wstate == W_IDLE);

    // We don't use the INIT/ERROR/TXN_DONE mechanism here
    assign TXN_DONE = 1'b0;

    // ---------------------------
    // Main write FSM
    // ---------------------------

    always @(posedge M_AXI_ACLK) begin
        if (!M_AXI_ARESETN) begin
            wstate      <= W_IDLE;
            axi_awaddr  <= {C_M_AXI_ADDR_WIDTH{1'b0}};
            axi_awvalid <= 1'b0;
            axi_wdata   <= {C_M_AXI_DATA_WIDTH{1'b0}};
            axi_wvalid  <= 1'b0;
            axi_wlast   <= 1'b0;
            axi_bready  <= 1'b0;
            ERROR       <= 1'b0;
        end else begin
            // default: no new error flagging here (you can extend this if you want)
            ERROR <= 1'b0;

            case (wstate)
                W_IDLE: begin
                    // Take a new user write request
                    if (usr_wr_valid) begin
                        axi_awaddr  <= usr_wr_addr;
                        axi_wdata   <= usr_wr_data;
                        axi_awvalid <= 1'b1;
                        axi_wvalid  <= 1'b1;
                        axi_wlast   <= 1'b1;  // single beat
                        axi_bready  <= 1'b0;
                        wstate      <= W_AW;
                    end
                end

                W_AW: begin
                    // Address and data can complete in any order, or same cycle

                    if (M_AXI_AWREADY)
                        axi_awvalid <= 1'b0;

                    if (M_AXI_WREADY) begin
                        axi_wvalid  <= 1'b0;
                        axi_wlast   <= 1'b0;
                        axi_bready  <= 1'b1;  // start waiting for response
                        wstate      <= W_B;
                    end
                end

                W_B: begin
                    // Wait for write response
                    if (M_AXI_BVALID && axi_bready) begin
                        axi_bready <= 1'b0;

                        // Optional: flag error if BRESP[1] set
                        if (M_AXI_BRESP[1])
                            ERROR <= 1'b1;

                        wstate <= W_IDLE;
                    end
                end

                default: begin
                    wstate <= W_IDLE;
                end
            endcase
        end
    end

endmodule
