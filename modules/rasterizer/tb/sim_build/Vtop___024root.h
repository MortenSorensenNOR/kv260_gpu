// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ rasterizer_frontend__DOT__clk;
        CData/*0:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk;
        VL_IN8(clk,0,0);
        VL_IN8(rstn,0,0);
        VL_IN8(i_dv,0,0);
        VL_OUT8(o_ready,0,0);
        VL_OUT8(o_dv,0,0);
        VL_IN8(i_ready,0,0);
        VL_OUT8(culled_triangle,0,0);
        CData/*0:0*/ rasterizer_frontend__DOT__rstn;
        CData/*0:0*/ rasterizer_frontend__DOT__i_dv;
        CData/*0:0*/ rasterizer_frontend__DOT__o_ready;
        CData/*0:0*/ rasterizer_frontend__DOT__o_dv;
        CData/*0:0*/ rasterizer_frontend__DOT__i_ready;
        CData/*0:0*/ rasterizer_frontend__DOT__culled_triangle;
        CData/*0:0*/ rasterizer_frontend__DOT__w_bb_valid;
        CData/*0:0*/ rasterizer_frontend__DOT__r_bb_valid;
        CData/*0:0*/ rasterizer_frontend__DOT__w_area_division_ready;
        CData/*0:0*/ rasterizer_frontend__DOT__r_area_division_in_A_dv;
        CData/*0:0*/ rasterizer_frontend__DOT__w_area_reciprocal_dv;
        CData/*0:0*/ rasterizer_frontend__DOT__w_should_be_culled;
        CData/*3:0*/ rasterizer_frontend__DOT__current_state;
        CData/*3:0*/ rasterizer_frontend__DOT__next_state;
        CData/*0:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn;
        CData/*0:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__ready;
        CData/*0:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv;
        CData/*0:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv;
        CData/*3:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter;
        CData/*5:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt;
        CData/*5:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt;
        CData/*1:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state;
        CData/*1:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__next_state;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rasterizer_frontend__DOT__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk__0;
        CData/*0:0*/ __VactContinue;
        VL_OUT(o_edge_val0,31,0);
        VL_OUT(o_edge_val1,31,0);
        VL_OUT(o_edge_val2,31,0);
        IData/*31:0*/ rasterizer_frontend__DOT__o_edge_val0;
        IData/*31:0*/ rasterizer_frontend__DOT__o_edge_val1;
        IData/*31:0*/ rasterizer_frontend__DOT__o_edge_val2;
        IData/*31:0*/ rasterizer_frontend__DOT__i;
        IData/*31:0*/ rasterizer_frontend__DOT__r_edge_val0;
        IData/*31:0*/ rasterizer_frontend__DOT__r_edge_val1;
        IData/*31:0*/ rasterizer_frontend__DOT__r_edge_val2;
        IData/*31:0*/ rasterizer_frontend__DOT__i_min_x;
        IData/*31:0*/ rasterizer_frontend__DOT__i_max_x;
        IData/*31:0*/ rasterizer_frontend__DOT__i_min_y;
        IData/*31:0*/ rasterizer_frontend__DOT__i_max_y;
        IData/*31:0*/ rasterizer_frontend__DOT__r_area_division_in_A;
        IData/*31:0*/ rasterizer_frontend__DOT__w_area_reciprocal;
        IData/*31:0*/ rasterizer_frontend__DOT__r_area_reciprocal;
        IData/*31:0*/ rasterizer_frontend__DOT____Vlvbound_h0f83b07d__0;
        IData/*31:0*/ rasterizer_frontend__DOT____Vlvbound_h3fb89b02__0;
        IData/*31:0*/ rasterizer_frontend__DOT____Vlvbound_hdd0e909d__0;
        IData/*31:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__A;
        IData/*31:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv;
        IData/*31:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__i;
        VlWide<3>/*64:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__X_two_AX;
        VlWide<3>/*64:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next;
        IData/*31:0*/ __VactIterCount;
        QData/*39:0*/ rasterizer_frontend__DOT__r_area;
    };
    struct {
        QData/*63:0*/ rasterizer_frontend__DOT__w_edge_function_val;
        QData/*63:0*/ rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_function;
        QData/*63:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A;
        QData/*63:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A_scaled;
        QData/*63:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__X;
        QData/*63:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp;
        QData/*63:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__AX;
        QData/*63:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp_minus_AX;
        QData/*63:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_A_inv;
        VL_IN(i_v0[3],31,0);
        VL_IN(i_v1[3],31,0);
        VL_IN(i_v2[3],31,0);
        VL_IN(i_attr_v0[3],31,0);
        VL_IN(i_attr_v1[3],31,0);
        VL_IN(i_attr_v2[3],31,0);
        VL_OUT(o_bb_tl[2],31,0);
        VL_OUT(o_bb_br[2],31,0);
        VL_OUT(o_edge_delta0[2],31,0);
        VL_OUT(o_edge_delta1[2],31,0);
        VL_OUT(o_edge_delta2[2],31,0);
        VL_OUT(o_attr0[4],31,0);
        VL_OUT(o_attr_dx[4],31,0);
        VL_OUT(o_attr_dy[4],31,0);
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__i_v0;
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__i_v1;
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__i_v2;
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__i_attr_v0;
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__i_attr_v1;
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__i_attr_v2;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__o_bb_tl;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__o_bb_br;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__o_edge_delta0;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__o_edge_delta1;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__o_edge_delta2;
        VlUnpacked<IData/*31:0*/, 4> rasterizer_frontend__DOT__o_attr0;
        VlUnpacked<IData/*31:0*/, 4> rasterizer_frontend__DOT__o_attr_dx;
        VlUnpacked<IData/*31:0*/, 4> rasterizer_frontend__DOT__o_attr_dy;
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__r_v0;
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__r_v1;
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__r_v2;
        VlUnpacked<IData/*31:0*/, 4> rasterizer_frontend__DOT__r_attr_v0;
        VlUnpacked<IData/*31:0*/, 4> rasterizer_frontend__DOT__r_attr_v1;
        VlUnpacked<IData/*31:0*/, 4> rasterizer_frontend__DOT__r_attr_v2;
        VlUnpacked<IData/*31:0*/, 4> rasterizer_frontend__DOT__r_attr0;
        VlUnpacked<IData/*31:0*/, 4> rasterizer_frontend__DOT__r_attr_dx;
        VlUnpacked<IData/*31:0*/, 4> rasterizer_frontend__DOT__r_attr_dy;
        VlUnpacked<QData/*63:0*/, 4> rasterizer_frontend__DOT__w_attr;
        VlUnpacked<QData/*63:0*/, 4> rasterizer_frontend__DOT__w_attr_dx;
        VlUnpacked<QData/*63:0*/, 4> rasterizer_frontend__DOT__w_attr_dy;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__r_edge_delta0;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__r_edge_delta1;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__r_edge_delta2;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__r_edge_function_v1;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__r_edge_function_v2;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__r_edge_function_p;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__w_edge_function_delta;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__w_bb_tl;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__w_bb_br;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__r_bb_tl;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__r_bb_br;
        VlUnpacked<QData/*63:0*/, 3> rasterizer_frontend__DOT__w_bw_mul;
        VlUnpacked<VlUnpacked<QData/*63:0*/, 2>, 3> rasterizer_frontend__DOT__w_bw_delta_mul;
        VlUnpacked<IData/*31:0*/, 3> rasterizer_frontend__DOT__r_barycentric_weight;
        VlUnpacked<VlUnpacked<IData/*31:0*/, 2>, 3> rasterizer_frontend__DOT__r_barycentric_weight_delta;
    };
    struct {
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__edge_compute_inst__DOT__v1;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__edge_compute_inst__DOT__v2;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__edge_compute_inst__DOT__p;
        VlUnpacked<IData/*31:0*/, 2> rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // PARAMETERS
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__SIGNED = 1U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__INT_BITS = 0x00000010U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__FRAC_BITS = 0x00000010U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__DATA_WIDTH = 0x00000020U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__AREA_INT_BITS = 0x00000018U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__AREA_WIDTH = 0x00000028U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__N_ATTR = 4U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__SCREEN_WIDTH = 0x00000040U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__SCREEN_HEIGHT = 0x00000040U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__SCREEN_WIDTH_FP = 0x00400000U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__SCREEN_HEIGHT_FP = 0x00400000U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__TILE_MIN_X = 0U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__TILE_MIN_Y = 0U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__TILE_MAX_X = 0x00400000U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__TILE_MAX_Y = 0x00400000U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__edge_compute_inst__DOT__DATA_WIDTH = 0x00000020U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__DATA_WIDTH = 0x00000020U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__NUM_ITERATIONS = 8U;
    static constexpr IData/*31:0*/ rasterizer_frontend__DOT__fast_inverse_inst__DOT__MAX_SHIFT = 6U;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
