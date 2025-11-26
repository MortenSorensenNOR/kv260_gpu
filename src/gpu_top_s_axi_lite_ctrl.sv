
`timescale 1 ns / 1 ps

module gpu_top_s_axi_lite_ctrl #(
    // Users to add parameters here

    // User parameters ends
    // Do not modify the parameters beyond this line

    // Width of S_AXI data bus
    parameter integer C_S_AXI_DATA_WIDTH    = 32,
    // Width of S_AXI address bus
    parameter integer C_S_AXI_ADDR_WIDTH    = 7
) (
    // Users to add ports here
    input  logic [31:0] i_status,
    output logic [31:0] o_cmd,
    output logic        o_cmd_valid,
    output logic [31:0] o_fb_base,
    output logic [31:0] o_fb_stride,
    output logic [31:0] o_fb_width,
    output logic [31:0] o_fb_height,
    output logic [31:0] o_clear_color,

    logic signed [31:0] o_v0[3],
    logic signed [31:0] o_v1[3],
    logic signed [31:0] o_v2[3],
    logic signed [31:0] o_v0_attr[3],
    logic signed [31:0] o_v1_attr[3],
    logic signed [31:0] o_v2_attr[3],

    // User ports ends
    // Do not modify the ports beyond this line

    // Global Clock Signal
    input logic  S_AXI_ACLK,
    // Global Reset Signal. This Signal is Active LOW
    input logic  S_AXI_ARESETN,
    // Write address (issued by master, acceped by Slave)
    input logic [C_S_AXI_ADDR_WIDTH-1 : 0] S_AXI_AWADDR,
    // Write channel Protection type. This signal indicates the
    // privilege and security level of the transaction, and whether
    // the transaction is a data access or an instruction access.
    input logic [2 : 0] S_AXI_AWPROT,
    // Write address valid. This signal indicates that the master signaling
    // valid write address and control information.
    input logic  S_AXI_AWVALID,
    // Write address ready. This signal indicates that the slave is ready
    // to accept an address and associated control signals.
    output logic  S_AXI_AWREADY,
    // Write data (issued by master, acceped by Slave)
    input logic [C_S_AXI_DATA_WIDTH-1 : 0] S_AXI_WDATA,
    // Write strobes. This signal indicates which byte lanes hold
    // valid data. There is one write strobe bit for each eight
    // bits of the write data bus.
    input logic [(C_S_AXI_DATA_WIDTH/8)-1 : 0] S_AXI_WSTRB,
    // Write valid. This signal indicates that valid write
    // data and strobes are available.
    input logic  S_AXI_WVALID,
    // Write ready. This signal indicates that the slave
    // can accept the write data.
    output logic  S_AXI_WREADY,
    // Write response. This signal indicates the status
    // of the write transaction.
    output logic [1 : 0] S_AXI_BRESP,
    // Write response valid. This signal indicates that the channel
    // is signaling a valid write response.
    output logic  S_AXI_BVALID,
    // Response ready. This signal indicates that the master
    // can accept a write response.
    input logic  S_AXI_BREADY,
    // Read address (issued by master, acceped by Slave)
    input logic [C_S_AXI_ADDR_WIDTH-1 : 0] S_AXI_ARADDR,
    // Protection type. This signal indicates the privilege
    // and security level of the transaction, and whether the
    // transaction is a data access or an instruction access.
    input logic [2 : 0] S_AXI_ARPROT,
    // Read address valid. This signal indicates that the channel
    // is signaling valid read address and control information.
    input logic  S_AXI_ARVALID,
    // Read address ready. This signal indicates that the slave is
    // ready to accept an address and associated control signals.
    output logic  S_AXI_ARREADY,
    // Read data (issued by slave)
    output logic [C_S_AXI_DATA_WIDTH-1 : 0] S_AXI_RDATA,
    // Read response. This signal indicates the status of the
    // read transfer.
    output logic [1 : 0] S_AXI_RRESP,
    // Read valid. This signal indicates that the channel is
    // signaling the required read data.
    output logic  S_AXI_RVALID,
    // Read ready. This signal indicates that the master can
    // accept the read data and response information.
    input logic  S_AXI_RREADY
);

    // AXI4LITE signals
    logic [C_S_AXI_ADDR_WIDTH-1 : 0] axi_awaddr;
    logic                            axi_awready;
    logic                            axi_wready;
    logic [1 : 0]                    axi_bresp;
    logic                            axi_bvalid;
    logic [C_S_AXI_ADDR_WIDTH-1 : 0] axi_araddr;
    logic                            axi_arready;
    logic [1 : 0]                    axi_rresp;
    logic                            axi_rvalid;

    // Example-specific design signals
    // local parameter for addressing 32 bit / 64 bit C_S_AXI_DATA_WIDTH
    // ADDR_LSB is used for addressing 32/64 bit registers/memories
    // ADDR_LSB = 2 for 32 bits (n downto 2)
    // ADDR_LSB = 3 for 64 bits (n downto 3)
    localparam integer ADDR_LSB = (C_S_AXI_DATA_WIDTH/32) + 1;
    localparam integer OPT_MEM_ADDR_BITS = 4;

    //----------------------------------------------
    //-- Signals for user logic register space example
    //------------------------------------------------
    //-- Number of Slave Registers 32
    logic [C_S_AXI_DATA_WIDTH-1:0] status;
    logic [C_S_AXI_DATA_WIDTH-1:0] cmd;
    logic [C_S_AXI_DATA_WIDTH-1:0] FB_BASE;
    logic [C_S_AXI_DATA_WIDTH-1:0] FB_STRIDE;
    logic [C_S_AXI_DATA_WIDTH-1:0] FB_WIDTH;
    logic [C_S_AXI_DATA_WIDTH-1:0] FB_HEIGHT;
    logic [C_S_AXI_DATA_WIDTH-1:0] FB_FORMAT;
    logic [C_S_AXI_DATA_WIDTH-1:0] DB_BASE;
    logic [C_S_AXI_DATA_WIDTH-1:0] DB_STRIDE;
    logic [C_S_AXI_DATA_WIDTH-1:0] DB_WIDTH;
    logic [C_S_AXI_DATA_WIDTH-1:0] DB_HEIGHT;
    logic [C_S_AXI_DATA_WIDTH-1:0] DB_FORMAT;
    logic [C_S_AXI_DATA_WIDTH-1:0] CLEAR_COLOR;
    logic [C_S_AXI_DATA_WIDTH-1:0] v0_x;
    logic [C_S_AXI_DATA_WIDTH-1:0] v0_y;
    logic [C_S_AXI_DATA_WIDTH-1:0] v0_z;
    logic [C_S_AXI_DATA_WIDTH-1:0] v1_x;
    logic [C_S_AXI_DATA_WIDTH-1:0] v1_y;
    logic [C_S_AXI_DATA_WIDTH-1:0] v1_z;
    logic [C_S_AXI_DATA_WIDTH-1:0] v2_x;
    logic [C_S_AXI_DATA_WIDTH-1:0] v2_y;
    logic [C_S_AXI_DATA_WIDTH-1:0] v2_z;
    logic [C_S_AXI_DATA_WIDTH-1:0] v0_attr1;
    logic [C_S_AXI_DATA_WIDTH-1:0] v0_attr2;
    logic [C_S_AXI_DATA_WIDTH-1:0] v0_attr3;
    logic [C_S_AXI_DATA_WIDTH-1:0] v1_attr1;
    logic [C_S_AXI_DATA_WIDTH-1:0] v1_attr2;
    logic [C_S_AXI_DATA_WIDTH-1:0] v1_attr3;
    logic [C_S_AXI_DATA_WIDTH-1:0] v2_attr1;
    logic [C_S_AXI_DATA_WIDTH-1:0] v2_attr2;
    logic [C_S_AXI_DATA_WIDTH-1:0] v2_attr3;
    logic [C_S_AXI_DATA_WIDTH-1:0] slv_reg31;
    integer byte_index;

    // I/O Connections assignments
    assign S_AXI_AWREADY = axi_awready;
    assign S_AXI_WREADY  = axi_wready;
    assign S_AXI_BRESP   = axi_bresp;
    assign S_AXI_BVALID  = axi_bvalid;
    assign S_AXI_ARREADY = axi_arready;
    assign S_AXI_RRESP   = axi_rresp;
    assign S_AXI_RVALID  = axi_rvalid;

    //state machine varibles
    logic [1:0] state_write;
    logic [1:0] state_read;
    localparam Idle = 2'b00,Raddr = 2'b10,Rdata = 2'b11 ,Waddr = 2'b10,Wdata = 2'b11;

    logic  slv_reg_wren;
    logic [4:0] wr_addr; 
    always_comb begin
        wr_addr = (S_AXI_AWVALID)
                ? S_AXI_AWADDR[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB]
                : axi_awaddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB];

        slv_reg_wren = axi_wready  && S_AXI_WVALID &&
                       axi_awready && S_AXI_AWVALID;
    end

    logic        cmd_valid;   // 1-cycle pulse
    logic [31:0] cmd_data;    // command payload this cycle

    always_ff @(posedge S_AXI_ACLK) begin
        if (!S_AXI_ARESETN) begin
            cmd_valid <= 1'b0;
            cmd_data  <= '0;
        end else begin
            // Default: no command this cycle
            cmd_valid <= 1'b0;

            // New command when AXI writes to address 0x01
            if (slv_reg_wren && (wr_addr == 5'h01)) begin
                cmd_valid <= 1'b1;
                cmd_data  <= S_AXI_WDATA;   // or masked with WSTRB if you care
            end
        end
    end

    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            axi_awready <= 0;
            axi_wready <= 0;
            axi_bvalid <= 0;
            axi_bresp <= 0;
            axi_awaddr <= 0;
            state_write <= Idle;
        end else begin
            case(state_write)
                Idle: begin
                    if(S_AXI_ARESETN == 1'b1) begin
                        axi_awready <= 1'b1;
                        axi_wready <= 1'b1;
                        state_write <= Waddr;
                    end else state_write <= state_write;
                end

                //At this state, slave is ready to receive address along with corresponding control signals and first data packet. Response valid is also handled at this state
                Waddr: begin
                    if (S_AXI_AWVALID && S_AXI_AWREADY) begin
                        axi_awaddr <= S_AXI_AWADDR;
                        if(S_AXI_WVALID) begin
                            axi_awready <= 1'b1;
                            state_write <= Waddr;
                            axi_bvalid <= 1'b1;
                        end else begin
                            axi_awready <= 1'b0;
                            state_write <= Wdata;
                            if (S_AXI_BREADY && axi_bvalid) axi_bvalid <= 1'b0;
                        end
                    end else begin
                        state_write <= state_write;
                        if (S_AXI_BREADY && axi_bvalid) axi_bvalid <= 1'b0;
                    end
                end

                Wdata: begin
                    //At this state, slave is ready to receive the data packets until the number of transfers is equal to burst length

                    if (S_AXI_WVALID) begin
                        state_write <= Waddr;
                        axi_bvalid <= 1'b1;
                        axi_awready <= 1'b1;
                    end else begin
                        state_write <= state_write;
                        if (S_AXI_BREADY && axi_bvalid) axi_bvalid <= 1'b0;
                    end
                end
            endcase
        end
    end

    // Implement memory mapped register select and write logic generation
    // The write data is accepted and written to memory mapped registers when
    // axi_awready, S_AXI_WVALID, axi_wready and S_AXI_WVALID are asserted. Write strobes are used to
    // select byte enables of slave registers while writing.
    // These registers are cleared when reset (active low) is applied.
    // Slave register write enable is asserted when valid address and data are available
    // and the slave is ready to accept the write address and write data.

    always @( posedge S_AXI_ACLK ) begin
        if ( S_AXI_ARESETN == 1'b0 ) begin
            cmd <= 0;
            FB_BASE <= 0;
            FB_STRIDE <= 0;
            FB_WIDTH <= 0;
            FB_HEIGHT <= 0;
            FB_FORMAT <= 0;
            DB_BASE <= 0;
            DB_STRIDE <= 0;
            DB_WIDTH <= 0;
            DB_HEIGHT <= 0;
            DB_FORMAT <= 0;
            CLEAR_COLOR <= 0;
            v0_x <= 0;
            v0_y <= 0;
            v0_z <= 0;
            v1_x <= 0;
            v1_y <= 0;
            v1_z <= 0;
            v2_x <= 0;
            v2_y <= 0;
            v2_z <= 0;
            v0_attr1 <= 0;
            v0_attr2 <= 0;
            v0_attr3 <= 0;
            v1_attr1 <= 0;
            v1_attr2 <= 0;
            v1_attr3 <= 0;
            v2_attr1 <= 0;
            v2_attr2 <= 0;
            v2_attr3 <= 0;
            slv_reg31 <= 0;
        end else begin
            if (S_AXI_WVALID) begin
                case ( (S_AXI_AWVALID) ? S_AXI_AWADDR[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] : axi_awaddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] )
                    5'h00:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 0
                                // status[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h01:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 1
                                cmd[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h02:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 2
                                FB_BASE[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h03:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 3
                                FB_STRIDE[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h04:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 4
                                FB_WIDTH[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h05:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 5
                                FB_HEIGHT[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h06:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 6
                                FB_FORMAT[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h07:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 7
                                DB_BASE[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h08:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 8
                                DB_STRIDE[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h09:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 9
                                DB_WIDTH[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h0A:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 10
                                DB_HEIGHT[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h0B:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 11
                                DB_FORMAT[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h0C:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 12
                                CLEAR_COLOR[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h0D:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 13
                                v0_x[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h0E:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 14
                                v0_y[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h0F:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 15
                                v0_z[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h10:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 16
                                v1_x[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h11:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 17
                                v1_y[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h12:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 18
                                v1_z[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h13:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 19
                                v2_x[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h14:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 20
                                v2_y[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h15:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 21
                                v2_z[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h16:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 22
                                v0_attr1[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h17:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 23
                                v0_attr2[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h18:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 24
                                v0_attr3[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h19:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 25
                                v1_attr1[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h1A:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 26
                                v1_attr2[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h1B:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 27
                                v1_attr3[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h1C:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 28
                                v2_attr1[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h1D:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 29
                                v2_attr2[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h1E:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 30
                                v2_attr3[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    5'h1F:
                        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
                            if ( S_AXI_WSTRB[byte_index] == 1 ) begin
                                // Respective byte enables are asserted as per write strobes
                                // Slave register 31
                                slv_reg31[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                            end
                    default : begin
                        // status <= status;
                        cmd <= cmd;
                        FB_BASE <= FB_BASE;
                        FB_STRIDE <= FB_STRIDE;
                        FB_WIDTH <= FB_WIDTH;
                        FB_HEIGHT <= FB_HEIGHT;
                        FB_FORMAT <= FB_FORMAT;
                        DB_BASE <= DB_BASE;
                        DB_STRIDE <= DB_STRIDE;
                        DB_WIDTH <= DB_WIDTH;
                        DB_HEIGHT <= DB_HEIGHT;
                        DB_FORMAT <= DB_FORMAT;
                        CLEAR_COLOR <= CLEAR_COLOR;
                        v0_x <= v0_x;
                        v0_y <= v0_y;
                        v0_z <= v0_z;
                        v1_x <= v1_x;
                        v1_y <= v1_y;
                        v1_z <= v1_z;
                        v2_x <= v2_x;
                        v2_y <= v2_y;
                        v2_z <= v2_z;
                        v0_attr1 <= v0_attr1;
                        v0_attr2 <= v0_attr2;
                        v0_attr3 <= v0_attr3;
                        v1_attr1 <= v1_attr1;
                        v1_attr2 <= v1_attr2;
                        v1_attr3 <= v1_attr3;
                        v2_attr1 <= v2_attr1;
                        v2_attr2 <= v2_attr2;
                        v2_attr3 <= v2_attr3;
                        slv_reg31 <= slv_reg31;
                    end
                endcase
            end
        end
    end

    // Implement read state machine
    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            //asserting initial values to all 0's during reset
            axi_arready <= 1'b0;
            axi_rvalid <= 1'b0;
            axi_rresp <= 1'b0;
            state_read <= Idle;
        end else begin
            case(state_read)
                Idle:     //Initial state inidicating reset is done and ready to receive read/write transactions
                begin
                    if (S_AXI_ARESETN == 1'b1) begin
                        state_read <= Raddr;
                        axi_arready <= 1'b1;
                    end
                    else state_read <= state_read;
                end

                Raddr:        //At this state, slave is ready to receive address along with corresponding control signals
                begin
                    if (S_AXI_ARVALID && S_AXI_ARREADY)
                    begin
                        state_read <= Rdata;
                        axi_araddr <= S_AXI_ARADDR;
                        axi_rvalid <= 1'b1;
                        axi_arready <= 1'b0;
                    end
                    else state_read <= state_read;
                end

                Rdata:        //At this state, slave is ready to send the data packets until the number of transfers is equal to burst length
                begin
                    if (S_AXI_RVALID && S_AXI_RREADY)
                    begin
                        axi_rvalid <= 1'b0;
                        axi_arready <= 1'b1;
                        state_read <= Raddr;
                    end
                    else state_read <= state_read;
                end

            endcase
        end
    end

    // Implement memory mapped register select and read logic generation
    assign S_AXI_RDATA = (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h0) ? status : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h1) ? cmd : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h2) ? FB_BASE : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h3) ? FB_STRIDE : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h4) ? FB_WIDTH : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h5) ? FB_HEIGHT : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h6) ? FB_FORMAT : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h7) ? DB_BASE : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h8) ? DB_STRIDE : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h9) ? DB_WIDTH : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'hA) ? DB_HEIGHT : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'hB) ? DB_FORMAT : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'hC) ? CLEAR_COLOR : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'hD) ? v0_x : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'hE) ? v0_y : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'hF) ? v0_z : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h10) ? v1_x : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h11) ? v1_y : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h12) ? v1_z : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h13) ? v2_x : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h14) ? v2_y : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h15) ? v2_z : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h16) ? v0_attr1 : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h17) ? v0_attr2 : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h18) ? v0_attr3 : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h19) ? v1_attr1 : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h1A) ? v1_attr2 : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h1B) ? v1_attr3 : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h1C) ? v2_attr1 : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h1D) ? v2_attr2 : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h1E) ? v2_attr3 : (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] == 5'h1F) ? slv_reg31 : 0;

    // Add user logic here
    assign status        = i_status;
    assign o_cmd         = cmd_data;
    assign o_cmd_valid   = cmd_valid;
    assign o_fb_base     = FB_BASE;
    assign o_fb_stride   = FB_STRIDE;
    assign o_fb_width    = FB_WIDTH;
    assign o_fb_height   = FB_HEIGHT;
    assign o_clear_color = CLEAR_COLOR;

    assign o_v0 = {$signed(v0_x), $signed(v0_y), $signed(v0_z)};
    assign o_v1 = {$signed(v1_x), $signed(v1_y), $signed(v1_z)};
    assign o_v2 = {$signed(v2_x), $signed(v2_y), $signed(v2_z)};
    assign o_v0_attr[3] = {$signed(v0_attr1), $signed(v0_attr2), $signed(v0_attr3)};
    assign o_v1_attr[3] = {$signed(v1_attr1), $signed(v1_attr2), $signed(v1_attr3)};
    assign o_v2_attr[3] = {$signed(v2_attr1), $signed(v2_attr2), $signed(v2_attr3)};

    // User logic ends
endmodule
