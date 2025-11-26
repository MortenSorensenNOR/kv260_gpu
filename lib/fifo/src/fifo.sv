`timescale 1ns / 1ps

module fifo #(
    parameter integer DEPTH  = 8,
    parameter integer DWIDTH = 16
) (
    input logic clk, 
    input logic rstn,
        
    input logic [DWIDTH-1:0] din,
    input logic wr_en,

    output logic [DWIDTH-1:0] dout,
    input  logic rd_en,

    output logic empty,
    output logic full
);

    logic [$clog2(DEPTH)-1:0] wptr;
    logic [$clog2(DEPTH)-1:0] rptr;
    logic [DWIDTH-1 : 0] fifo[DEPTH];

    int i;
    initial begin
        for (i = 0; i < DWIDTH; i++) begin
            fifo[i] = '0;
        end
    end

    always @(posedge clk) begin
        if (~rstn) begin
            wptr <= 0;
        end else begin
            if (wr_en & !full) begin
                fifo[wptr] <= din;
                wptr       <= wptr + 1;
            end
        end
    end

    always @(posedge clk) begin
        if (~rstn) begin
            rptr <= 0;
        end else begin
            if (rd_en & !empty) begin
                dout <= fifo[rptr];
                rptr <= rptr + 1;
            end
        end
    end

    assign full  = (wptr + 1) == rptr;
    assign empty = wptr == rptr;
endmodule
