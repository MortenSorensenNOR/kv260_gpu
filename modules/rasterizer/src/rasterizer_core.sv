`timescale 1ns / 1ps

module rasterizer_core #(
    parameter integer SIGNED    = 1,
    parameter integer INT_BITS  = 16,
    parameter integer FRAC_BITS = 16,
    parameter integer DATA_WIDTH = INT_BITS + FRAC_BITS,
    parameter  integer AREA_FRAC_BITS  = 4,

    parameter int N_ATTR = 4,  // depth, R, G, B

    parameter signed SCREEN_WIDTH  = 640,
    parameter signed SCREEN_HEIGHT = 360
) (
    input logic clk,
    input logic rstn,

    // Input data signals
    input logic signed [DATA_WIDTH-1:0] i_v0[3],
    input logic signed [DATA_WIDTH-1:0] i_v1[3],
    input logic signed [DATA_WIDTH-1:0] i_v2[3],

    // Input vertex attributes minus 1 (not including z value from i_v*)
    input logic signed [DATA_WIDTH-1:0] i_attr_v0[N_ATTR-1],
    input logic signed [DATA_WIDTH-1:0] i_attr_v1[N_ATTR-1],
    input logic signed [DATA_WIDTH-1:0] i_attr_v2[N_ATTR-1],

    // Ready/valid for input
    input  logic i_dv,
    output logic o_ready,

    // Output data signals
    output logic signed [DATA_WIDTH-1:0] o_fragment_x,
    output logic signed [DATA_WIDTH-1:0] o_fragment_y,
    output logic signed [DATA_WIDTH-1:0] o_fragment_attr [N_ATTR],

    // Ready/valid for output
    output logic o_dv,
    input  logic i_ready,

    // Mostly for convenience - is backend done? only useful when rendering
    // just one triangle
    output logic done,
    output logic culled_triangle
);

    // Rasterizer Frontend Output data signals
    logic signed [DATA_WIDTH-1:0] w_bb_tl[2];
    logic signed [DATA_WIDTH-1:0] w_bb_br[2];
    logic signed [DATA_WIDTH-1:0] w_edge_val0;
    logic signed [DATA_WIDTH-1:0] w_edge_val1;
    logic signed [DATA_WIDTH-1:0] w_edge_val2;
    logic signed [DATA_WIDTH-1:0] w_edge_delta0[2];
    logic signed [DATA_WIDTH-1:0] w_edge_delta1[2];
    logic signed [DATA_WIDTH-1:0] w_edge_delta2[2];

    logic signed [DATA_WIDTH-1:0] w_attr0   [N_ATTR];
    logic signed [DATA_WIDTH-1:0] w_attr_dx [N_ATTR];
    logic signed [DATA_WIDTH-1:0] w_attr_dy [N_ATTR];

    // Rasterizer Frontend Ready/valid for output
    logic w_rasterizer_frontend_o_dv;
    logic w_rasterizer_frontend_i_ready;

    rasterizer_frontend #(
        .SIGNED(SIGNED),
        .INT_BITS(INT_BITS),
        .FRAC_BITS(FRAC_BITS),
        .DATA_WIDTH(DATA_WIDTH),
        .AREA_FRAC_BITS(AREA_FRAC_BITS),
        .N_ATTR(N_ATTR),
        .SCREEN_WIDTH(SCREEN_WIDTH),
        .SCREEN_HEIGHT(SCREEN_HEIGHT)
    ) rasterizer_frontend_inst (
        .clk(clk),
        .rstn(rstn),

        .i_v0(i_v0),
        .i_v1(i_v1),
        .i_v2(i_v2),
        .i_attr_v0(i_attr_v0),
        .i_attr_v1(i_attr_v1),
        .i_attr_v2(i_attr_v2),

        .i_dv(i_dv),
        .o_ready(o_ready),

        .o_bb_tl(w_bb_tl),
        .o_bb_br(w_bb_br),
        .o_edge_val0(w_edge_val0),
        .o_edge_val1(w_edge_val1),
        .o_edge_val2(w_edge_val2),
        .o_edge_delta0(w_edge_delta0),
        .o_edge_delta1(w_edge_delta1),
        .o_edge_delta2(w_edge_delta2),

        .o_attr0(w_attr0),
        .o_attr_dx(w_attr_dx),
        .o_attr_dy(w_attr_dy),

        .o_dv(w_rasterizer_frontend_o_dv),
        .i_ready(w_rasterizer_frontend_i_ready),

        .culled_triangle(culled_triangle)
    );

    rasterizer_backend #(
        .INT_BITS(INT_BITS),
        .FRAC_BITS(FRAC_BITS),
        .DATA_WIDTH(DATA_WIDTH),
        .N_ATTR(N_ATTR),
        .SCREEN_WIDTH(SCREEN_WIDTH),
        .SCREEN_HEIGHT(SCREEN_HEIGHT)
    ) rasterizer_backend_inst (
        .clk(clk),
        .rstn(rstn),

        .i_bb_tl(w_bb_tl),
        .i_bb_br(w_bb_br),

        .i_edge_val0(w_edge_val0),
        .i_edge_val1(w_edge_val1),
        .i_edge_val2(w_edge_val2),

        .i_edge_delta0(w_edge_delta0),
        .i_edge_delta1(w_edge_delta1),
        .i_edge_delta2(w_edge_delta2),

        .i_attr0(w_attr0),
        .i_attr_dx(w_attr_dx),
        .i_attr_dy(w_attr_dy),

        .i_dv(w_rasterizer_frontend_o_dv),
        .o_ready(w_rasterizer_frontend_i_ready),

        .o_fragment_x(o_fragment_x),
        .o_fragment_y(o_fragment_y),
        .o_fragment_attr(o_fragment_attr),

        .o_dv(o_dv),
        .i_ready(i_ready),
        .done(done)
    );

endmodule
