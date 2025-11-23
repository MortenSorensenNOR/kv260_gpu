// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_static__TOP(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__rasterizer_frontend__DOT__clk__0 
        = vlSelfRef.rasterizer_frontend__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk__0 
        = vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk;
}

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.rasterizer_frontend__DOT__current_state = 0U;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter = 0U;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp = 0x200000000ULL;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state = 0U;
}

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/home/morten/dev/graphics/kv260_gpu/modules/rasterizer/src/rasterizer_frontend_simple.sv", 7, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtop___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
    }
}

extern const VlUnpacked<CData/*1:0*/, 128> Vtop__ConstPool__TABLE_h08df8bb1_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vtop__ConstPool__TABLE_h4a04a26f_0;
extern const VlUnpacked<CData/*3:0*/, 512> Vtop__ConstPool__TABLE_h83416bf4_0;
extern const VlUnpacked<CData/*0:0*/, 512> Vtop__ConstPool__TABLE_hc1c85e0c_0;

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*6:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    VlWide<3>/*95:0*/ __Vtemp_2;
    VlWide<3>/*95:0*/ __Vtemp_3;
    VlWide<3>/*95:0*/ __Vtemp_4;
    VlWide<3>/*95:0*/ __Vtemp_6;
    // Body
    vlSelfRef.o_edge_val0 = vlSelfRef.rasterizer_frontend__DOT__o_edge_val0;
    vlSelfRef.o_edge_val1 = vlSelfRef.rasterizer_frontend__DOT__o_edge_val1;
    vlSelfRef.o_edge_val2 = vlSelfRef.rasterizer_frontend__DOT__o_edge_val2;
    vlSelfRef.o_dv = vlSelfRef.rasterizer_frontend__DOT__o_dv;
    vlSelfRef.culled_triangle = vlSelfRef.rasterizer_frontend__DOT__culled_triangle;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A 
        = vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A;
    vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal 
        = vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_A_inv 
        = ((0U == (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt))
            ? vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X
            : ((vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X 
                + VL_SHIFTL_QQI(64,64,32, 1ULL, ((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt) 
                                                 - (IData)(1U)))) 
               >> (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt)));
    vlSelfRef.o_bb_tl[0U] = vlSelfRef.rasterizer_frontend__DOT__o_bb_tl
        [0U];
    vlSelfRef.o_bb_tl[1U] = vlSelfRef.rasterizer_frontend__DOT__o_bb_tl
        [1U];
    vlSelfRef.o_bb_br[0U] = vlSelfRef.rasterizer_frontend__DOT__o_bb_br
        [0U];
    vlSelfRef.o_bb_br[1U] = vlSelfRef.rasterizer_frontend__DOT__o_bb_br
        [1U];
    vlSelfRef.o_edge_delta0[0U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0
        [0U];
    vlSelfRef.o_edge_delta0[1U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0
        [1U];
    vlSelfRef.o_edge_delta1[0U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1
        [0U];
    vlSelfRef.o_edge_delta1[1U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1
        [1U];
    vlSelfRef.o_edge_delta2[0U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2
        [0U];
    vlSelfRef.o_edge_delta2[1U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2
        [1U];
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt = 0U;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i = 0x1fU;
    {
        while (VL_LTES_III(32, 0U, vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i)) {
            if ((1U & (IData)((vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A 
                               >> (0x3fU & ((IData)(0x20U) 
                                            + vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i)))))) {
                vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt 
                    = (0x3fU & ((IData)(1U) + vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i));
                goto __Vlabel0;
            }
            vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i 
                = (vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i 
                   - (IData)(1U));
        }
        __Vlabel0: ;
    }
    vlSelfRef.rasterizer_frontend__DOT__i_v0[0U] = 
        vlSelfRef.i_v0[0U];
    vlSelfRef.rasterizer_frontend__DOT__i_v0[1U] = 
        vlSelfRef.i_v0[1U];
    vlSelfRef.rasterizer_frontend__DOT__i_v0[2U] = 
        vlSelfRef.i_v0[2U];
    vlSelfRef.rasterizer_frontend__DOT__i_v1[0U] = 
        vlSelfRef.i_v1[0U];
    vlSelfRef.rasterizer_frontend__DOT__i_v1[1U] = 
        vlSelfRef.i_v1[1U];
    vlSelfRef.rasterizer_frontend__DOT__i_v1[2U] = 
        vlSelfRef.i_v1[2U];
    vlSelfRef.rasterizer_frontend__DOT__i_v2[0U] = 
        vlSelfRef.i_v2[0U];
    vlSelfRef.rasterizer_frontend__DOT__i_v2[1U] = 
        vlSelfRef.i_v2[1U];
    vlSelfRef.rasterizer_frontend__DOT__i_v2[2U] = 
        vlSelfRef.i_v2[2U];
    vlSelfRef.rasterizer_frontend__DOT__i_attr_v0[0U] 
        = vlSelfRef.i_attr_v0[0U];
    vlSelfRef.rasterizer_frontend__DOT__i_attr_v0[1U] 
        = vlSelfRef.i_attr_v0[1U];
    vlSelfRef.rasterizer_frontend__DOT__i_attr_v0[2U] 
        = vlSelfRef.i_attr_v0[2U];
    vlSelfRef.rasterizer_frontend__DOT__i_attr_v1[0U] 
        = vlSelfRef.i_attr_v1[0U];
    vlSelfRef.rasterizer_frontend__DOT__i_attr_v1[1U] 
        = vlSelfRef.i_attr_v1[1U];
    vlSelfRef.rasterizer_frontend__DOT__i_attr_v1[2U] 
        = vlSelfRef.i_attr_v1[2U];
    vlSelfRef.rasterizer_frontend__DOT__i_attr_v2[0U] 
        = vlSelfRef.i_attr_v2[0U];
    vlSelfRef.rasterizer_frontend__DOT__i_attr_v2[1U] 
        = vlSelfRef.i_attr_v2[1U];
    vlSelfRef.rasterizer_frontend__DOT__i_attr_v2[2U] 
        = vlSelfRef.i_attr_v2[2U];
    vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[0U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_val0), 
                      VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[1U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_val1), 
                      VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[2U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_val2), 
                      VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul[0U][0U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0
                                        [0U]), VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul[0U][1U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0
                                        [1U]), VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul[1U][0U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1
                                        [0U]), VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul[1U][1U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1
                                        [1U]), VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul[2U][0U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2
                                        [0U]), VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul[2U][1U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2
                                        [1U]), VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_attr[0U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                          [0U]), VL_EXTENDS_QI(64,32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                                               [0U])) 
            + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, 
                                            vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                            [1U]), 
                          VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                        [0U]))) + VL_MULS_QQQ(64, 
                                                              VL_EXTENDS_QI(64,32, 
                                                                            vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                                                            [2U]), 
                                                              VL_EXTENDS_QI(64,32, 
                                                                            vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                                                            [0U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr[1U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                          [0U]), VL_EXTENDS_QI(64,32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                                               [1U])) 
            + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, 
                                            vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                            [1U]), 
                          VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                        [1U]))) + VL_MULS_QQQ(64, 
                                                              VL_EXTENDS_QI(64,32, 
                                                                            vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                                                            [2U]), 
                                                              VL_EXTENDS_QI(64,32, 
                                                                            vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                                                            [1U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr[2U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                          [0U]), VL_EXTENDS_QI(64,32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                                               [2U])) 
            + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, 
                                            vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                            [1U]), 
                          VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                        [2U]))) + VL_MULS_QQQ(64, 
                                                              VL_EXTENDS_QI(64,32, 
                                                                            vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                                                            [2U]), 
                                                              VL_EXTENDS_QI(64,32, 
                                                                            vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                                                            [2U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr[3U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                          [0U]), VL_EXTENDS_QI(64,32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                                               [3U])) 
            + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, 
                                            vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                            [1U]), 
                          VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                        [3U]))) + VL_MULS_QQQ(64, 
                                                              VL_EXTENDS_QI(64,32, 
                                                                            vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight
                                                                            [2U]), 
                                                              VL_EXTENDS_QI(64,32, 
                                                                            vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                                                            [3U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[0U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                          [0U][0U]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                      [0U])) + VL_MULS_QQQ(64, 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                                                         [1U]
                                                                         [0U]), 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                                                         [0U]))) 
           + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                           [2U][0U]), 
                         VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                       [0U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[1U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                          [0U][0U]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                      [1U])) + VL_MULS_QQQ(64, 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                                                         [1U]
                                                                         [0U]), 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                                                         [1U]))) 
           + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                           [2U][0U]), 
                         VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                       [1U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[2U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                          [0U][0U]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                      [2U])) + VL_MULS_QQQ(64, 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                                                         [1U]
                                                                         [0U]), 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                                                         [2U]))) 
           + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                           [2U][0U]), 
                         VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                       [2U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[3U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                          [0U][0U]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                      [3U])) + VL_MULS_QQQ(64, 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                                                         [1U]
                                                                         [0U]), 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                                                         [3U]))) 
           + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                           [2U][0U]), 
                         VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                       [3U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[0U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                          [0U][1U]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                      [0U])) + VL_MULS_QQQ(64, 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                                                         [1U]
                                                                         [1U]), 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                                                         [0U]))) 
           + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                           [2U][1U]), 
                         VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                       [0U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[1U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                          [0U][1U]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                      [1U])) + VL_MULS_QQQ(64, 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                                                         [1U]
                                                                         [1U]), 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                                                         [1U]))) 
           + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                           [2U][1U]), 
                         VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                       [1U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[2U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                          [0U][1U]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                      [2U])) + VL_MULS_QQQ(64, 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                                                         [1U]
                                                                         [1U]), 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                                                         [2U]))) 
           + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                           [2U][1U]), 
                         VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                       [2U])));
    vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[3U] 
        = ((VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                          [0U][1U]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v0
                                      [3U])) + VL_MULS_QQQ(64, 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                                                         [1U]
                                                                         [1U]), 
                                                           VL_EXTENDS_QI(64,32, 
                                                                         vlSelfRef.rasterizer_frontend__DOT__r_attr_v1
                                                                         [3U]))) 
           + VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                                           [2U][1U]), 
                         VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_attr_v2
                                       [3U])));
    vlSelfRef.rasterizer_frontend__DOT__clk = vlSelfRef.clk;
    vlSelfRef.rasterizer_frontend__DOT__rstn = vlSelfRef.rstn;
    vlSelfRef.o_attr0[0U] = vlSelfRef.rasterizer_frontend__DOT__o_attr0
        [0U];
    vlSelfRef.o_attr0[1U] = vlSelfRef.rasterizer_frontend__DOT__o_attr0
        [1U];
    vlSelfRef.o_attr0[2U] = vlSelfRef.rasterizer_frontend__DOT__o_attr0
        [2U];
    vlSelfRef.o_attr0[3U] = vlSelfRef.rasterizer_frontend__DOT__o_attr0
        [3U];
    vlSelfRef.o_attr_dx[0U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dx
        [0U];
    vlSelfRef.o_attr_dx[1U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dx
        [1U];
    vlSelfRef.o_attr_dx[2U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dx
        [2U];
    vlSelfRef.o_attr_dx[3U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dx
        [3U];
    vlSelfRef.o_attr_dy[0U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dy
        [0U];
    vlSelfRef.o_attr_dy[1U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dy
        [1U];
    vlSelfRef.o_attr_dy[2U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dy
        [2U];
    vlSelfRef.o_attr_dy[3U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dy
        [3U];
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__AX 
        = VL_SHIFTR_QQI(64,64,32, (vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A_scaled 
                                   * vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X), 0x20U);
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp_minus_AX 
        = (vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp 
           - vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__AX);
    __Vtemp_2[0U] = (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X);
    __Vtemp_2[1U] = (IData)((vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X 
                             >> 0x20U));
    __Vtemp_2[2U] = 0U;
    __Vtemp_3[0U] = (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp_minus_AX);
    __Vtemp_3[1U] = (IData)((vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp_minus_AX 
                             >> 0x20U));
    __Vtemp_3[2U] = 0U;
    VL_MUL_W(3, __Vtemp_4, __Vtemp_2, __Vtemp_3);
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X_two_AX[0U] 
        = __Vtemp_4[0U];
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X_two_AX[1U] 
        = __Vtemp_4[1U];
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X_two_AX[2U] 
        = (1U & __Vtemp_4[2U]);
    VL_SHIFTR_WWI(65,65,32, __Vtemp_6, vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X_two_AX, 0x20U);
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next[0U] 
        = __Vtemp_6[0U];
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next[1U] 
        = __Vtemp_6[1U];
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next[2U] 
        = (1U & __Vtemp_6[2U]);
    vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__p[0U] 
        = vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p
        [0U];
    vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__p[1U] 
        = vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p
        [1U];
    vlSelfRef.rasterizer_frontend__DOT__i_min_x = (
                                                   VL_LTS_III(32, 
                                                              vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                              [0U], 
                                                              vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                              [0U])
                                                    ? 
                                                   (VL_LTS_III(32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                               [0U], 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                               [0U])
                                                     ? 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                    [0U]
                                                     : 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                    [0U])
                                                    : 
                                                   (VL_LTS_III(32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                               [0U], 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                               [0U])
                                                     ? 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                    [0U]
                                                     : 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                    [0U]));
    vlSelfRef.rasterizer_frontend__DOT__i_max_x = (
                                                   VL_GTS_III(32, 
                                                              vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                              [0U], 
                                                              vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                              [0U])
                                                    ? 
                                                   (VL_GTS_III(32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                               [0U], 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                               [0U])
                                                     ? 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                    [0U]
                                                     : 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                    [0U])
                                                    : 
                                                   (VL_GTS_III(32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                               [0U], 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                               [0U])
                                                     ? 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                    [0U]
                                                     : 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                    [0U]));
    vlSelfRef.rasterizer_frontend__DOT__i_min_y = (
                                                   VL_LTS_III(32, 
                                                              vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                              [1U], 
                                                              vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                              [1U])
                                                    ? 
                                                   (VL_LTS_III(32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                               [1U], 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                               [1U])
                                                     ? 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                    [1U]
                                                     : 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                    [1U])
                                                    : 
                                                   (VL_LTS_III(32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                               [1U], 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                               [1U])
                                                     ? 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                    [1U]
                                                     : 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                    [1U]));
    vlSelfRef.rasterizer_frontend__DOT__i_max_y = (
                                                   VL_GTS_III(32, 
                                                              vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                              [1U], 
                                                              vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                              [1U])
                                                    ? 
                                                   (VL_GTS_III(32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                               [1U], 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                               [1U])
                                                     ? 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v0
                                                    [1U]
                                                     : 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                    [1U])
                                                    : 
                                                   (VL_GTS_III(32, 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                               [1U], 
                                                               vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                               [1U])
                                                     ? 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v1
                                                    [1U]
                                                     : 
                                                    vlSelfRef.rasterizer_frontend__DOT__r_v2
                                                    [1U]));
    vlSelfRef.rasterizer_frontend__DOT__w_bb_tl[0U] 
        = (VL_GTS_III(32, 0U, vlSelfRef.rasterizer_frontend__DOT__i_min_x)
            ? 0U : vlSelfRef.rasterizer_frontend__DOT__i_min_x);
    vlSelfRef.rasterizer_frontend__DOT__w_bb_br[0U] 
        = (VL_LTS_III(32, 0x400000U, vlSelfRef.rasterizer_frontend__DOT__i_max_x)
            ? 0x400000U : vlSelfRef.rasterizer_frontend__DOT__i_max_x);
    vlSelfRef.rasterizer_frontend__DOT__w_bb_tl[1U] 
        = (VL_GTS_III(32, 0U, vlSelfRef.rasterizer_frontend__DOT__i_min_y)
            ? 0U : vlSelfRef.rasterizer_frontend__DOT__i_min_y);
    vlSelfRef.rasterizer_frontend__DOT__w_bb_br[1U] 
        = (VL_LTS_III(32, 0x400000U, vlSelfRef.rasterizer_frontend__DOT__i_max_y)
            ? 0x400000U : vlSelfRef.rasterizer_frontend__DOT__i_max_y);
    vlSelfRef.rasterizer_frontend__DOT__w_bb_valid 
        = (VL_LTS_III(32, vlSelfRef.rasterizer_frontend__DOT__w_bb_tl
                      [0U], vlSelfRef.rasterizer_frontend__DOT__w_bb_br
                      [0U]) & VL_LTS_III(32, vlSelfRef.rasterizer_frontend__DOT__w_bb_tl
                                         [1U], vlSelfRef.rasterizer_frontend__DOT__w_bb_br
                                         [1U]));
    vlSelfRef.rasterizer_frontend__DOT__i_dv = vlSelfRef.i_dv;
    vlSelfRef.rasterizer_frontend__DOT__i_ready = vlSelfRef.i_ready;
    vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal_dv 
        = vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv;
    vlSelfRef.rasterizer_frontend__DOT__w_should_be_culled 
        = (1U & (VL_GTES_IQQ(40, 0ULL, vlSelfRef.rasterizer_frontend__DOT__r_area) 
                 | (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__r_bb_valid))));
    vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1[0U] 
        = vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1
        [0U];
    vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1[1U] 
        = vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1
        [1U];
    vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2[0U] 
        = vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2
        [0U];
    vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2[1U] 
        = vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2
        [1U];
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv 
        = vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A_dv;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk 
        = vlSelfRef.rasterizer_frontend__DOT__clk;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn 
        = vlSelfRef.rasterizer_frontend__DOT__rstn;
    vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_function 
        = (VL_MULS_QQQ(64, (VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__p
                                          [0U]) - VL_EXTENDS_QI(64,32, 
                                                                vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1
                                                                [0U])), 
                       (VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2
                                      [1U]) - VL_EXTENDS_QI(64,32, 
                                                            vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1
                                                            [1U]))) 
           - VL_MULS_QQQ(64, (VL_EXTENDS_QI(64,32, 
                                            vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__p
                                            [1U]) - 
                              VL_EXTENDS_QI(64,32, 
                                            vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1
                                            [1U])), 
                         (VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2
                                        [0U]) - VL_EXTENDS_QI(64,32, 
                                                              vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1
                                                              [0U]))));
    vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta[0U] 
        = (vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2
           [1U] - vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1
           [1U]);
    vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta[1U] 
        = (- (vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2
              [0U] - vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1
              [0U]));
    __Vtableidx2 = (((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv) 
                     << 6U) | (((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter) 
                                << 2U) | (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state)));
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__next_state 
        = Vtop__ConstPool__TABLE_h08df8bb1_0[__Vtableidx2];
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__ready 
        = Vtop__ConstPool__TABLE_h4a04a26f_0[__Vtableidx2];
    vlSelfRef.rasterizer_frontend__DOT__w_edge_function_val 
        = vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_function;
    vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta[0U] 
        = vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta
        [0U];
    vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta[1U] 
        = vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta
        [1U];
    vlSelfRef.rasterizer_frontend__DOT__w_area_division_ready 
        = vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__ready;
    __Vtableidx1 = ((((IData)(vlSelfRef.rasterizer_frontend__DOT__i_dv) 
                      << 8U) | (((IData)(vlSelfRef.rasterizer_frontend__DOT__w_area_division_ready) 
                                 << 7U) | ((IData)(vlSelfRef.rasterizer_frontend__DOT__w_should_be_culled) 
                                           << 6U))) 
                    | (((IData)(vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal_dv) 
                        << 5U) | (((IData)(vlSelfRef.rasterizer_frontend__DOT__i_ready) 
                                   << 4U) | (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))));
    vlSelfRef.rasterizer_frontend__DOT__next_state 
        = Vtop__ConstPool__TABLE_h83416bf4_0[__Vtableidx1];
    vlSelfRef.rasterizer_frontend__DOT__o_ready = Vtop__ConstPool__TABLE_hc1c85e0c_0
        [__Vtableidx1];
    vlSelfRef.o_ready = vlSelfRef.rasterizer_frontend__DOT__o_ready;
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge rasterizer_frontend.clk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge rasterizer_frontend.fast_inverse_inst.clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge rasterizer_frontend.clk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge rasterizer_frontend.fast_inverse_inst.clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rstn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5377340664288042355ull);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->i_v0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7957143212346167178ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->i_v1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18135194636480763821ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->i_v2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16099866619636296195ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->i_attr_v0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10272909809115065320ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->i_attr_v1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14662224095053819371ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->i_attr_v2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2064237383241795530ull);
    }
    vlSelf->i_dv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3373279059641199820ull);
    vlSelf->o_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5902872893213290355ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->o_bb_tl[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16618254949520185830ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->o_bb_br[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4501116573673185824ull);
    }
    vlSelf->o_edge_val0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3000521138767715177ull);
    vlSelf->o_edge_val1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14348600577255073931ull);
    vlSelf->o_edge_val2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4223528587267489953ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->o_edge_delta0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6917376964624686690ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->o_edge_delta1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13253540891431561763ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->o_edge_delta2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11580245837626926361ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->o_attr0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 283765158945455871ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->o_attr_dx[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12347532344921407711ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->o_attr_dy[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10308403383745728798ull);
    }
    vlSelf->o_dv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3886378380652278687ull);
    vlSelf->i_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12116946353889193432ull);
    vlSelf->culled_triangle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 844872441925378548ull);
    vlSelf->rasterizer_frontend__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16268323642798280395ull);
    vlSelf->rasterizer_frontend__DOT__rstn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1673434790096737208ull);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__i_v0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14630344011293627009ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__i_v1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 349538901318722035ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__i_v2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4861124136671667095ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__i_attr_v0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9363555765598122975ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__i_attr_v1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4220666754042390137ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__i_attr_v2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12280099102672711751ull);
    }
    vlSelf->rasterizer_frontend__DOT__i_dv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2889127938815037537ull);
    vlSelf->rasterizer_frontend__DOT__o_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3237209176994970954ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__o_bb_tl[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12313922613272949593ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__o_bb_br[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16266782494790277100ull);
    }
    vlSelf->rasterizer_frontend__DOT__o_edge_val0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14976610910250984301ull);
    vlSelf->rasterizer_frontend__DOT__o_edge_val1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13597754960162184461ull);
    vlSelf->rasterizer_frontend__DOT__o_edge_val2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2723235815074602259ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__o_edge_delta0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12629457810357567228ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__o_edge_delta1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6975518253644200671ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__o_edge_delta2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14193051224519009249ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__o_attr0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1460849902501232681ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__o_attr_dx[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9752444171217713423ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__o_attr_dy[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11442695736976662605ull);
    }
    vlSelf->rasterizer_frontend__DOT__o_dv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7912417503158460191ull);
    vlSelf->rasterizer_frontend__DOT__i_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15646137224743250258ull);
    vlSelf->rasterizer_frontend__DOT__culled_triangle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15264613711602939347ull);
    vlSelf->rasterizer_frontend__DOT__i = 0;
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_v0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16969019062864997029ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_v1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17576268400891199780ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_v2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2624825425934258863ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_attr_v0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13248073121409292954ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_attr_v1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8429212257961027694ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_attr_v2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8749497838815775167ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_attr0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17850263566443630507ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_attr_dx[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5941079374169191400ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_attr_dy[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16994123989758158711ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__w_attr[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16026032659315972639ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__w_attr_dx[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17793534383912556766ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__w_attr_dy[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7208921879701573605ull);
    }
    vlSelf->rasterizer_frontend__DOT__r_edge_val0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1672241398389545660ull);
    vlSelf->rasterizer_frontend__DOT__r_edge_val1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8182795964820306777ull);
    vlSelf->rasterizer_frontend__DOT__r_edge_val2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5193093142887743098ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_edge_delta0[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8447363211140432765ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_edge_delta1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17121631791335224597ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_edge_delta2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11382165931448828188ull);
    }
    vlSelf->rasterizer_frontend__DOT__r_area = VL_SCOPED_RAND_RESET_Q(40, __VscopeHash, 2142411292399220419ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_edge_function_v1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13079195634280801970ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_edge_function_v2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10372629800823881091ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_edge_function_p[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10029330638163162824ull);
    }
    vlSelf->rasterizer_frontend__DOT__w_edge_function_val = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14708023143523576711ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__w_edge_function_delta[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14103544879220227891ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__w_bb_tl[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17553649505712709983ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__w_bb_br[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8542106946250891540ull);
    }
    vlSelf->rasterizer_frontend__DOT__w_bb_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18323347511199768659ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_bb_tl[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2260223966909981875ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_bb_br[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5064435534384608806ull);
    }
    vlSelf->rasterizer_frontend__DOT__r_bb_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8017987711739933768ull);
    vlSelf->rasterizer_frontend__DOT__i_min_x = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3064317196065900085ull);
    vlSelf->rasterizer_frontend__DOT__i_max_x = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14476608579730894264ull);
    vlSelf->rasterizer_frontend__DOT__i_min_y = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15556855619039568929ull);
    vlSelf->rasterizer_frontend__DOT__i_max_y = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7808897668279214736ull);
    vlSelf->rasterizer_frontend__DOT__w_area_division_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12066109065382108774ull);
    vlSelf->rasterizer_frontend__DOT__r_area_division_in_A = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12231165999509072721ull);
    vlSelf->rasterizer_frontend__DOT__r_area_division_in_A_dv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17571887593545903790ull);
    vlSelf->rasterizer_frontend__DOT__w_area_reciprocal = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6223684204311910945ull);
    vlSelf->rasterizer_frontend__DOT__w_area_reciprocal_dv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4158848931935356573ull);
    vlSelf->rasterizer_frontend__DOT__r_area_reciprocal = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8774395963512110509ull);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__w_bw_mul[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9911292430611177840ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 2; ++__Vi1) {
            vlSelf->rasterizer_frontend__DOT__w_bw_delta_mul[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5883243048933179047ull);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__r_barycentric_weight[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8575732343026690ull);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 2; ++__Vi1) {
            vlSelf->rasterizer_frontend__DOT__r_barycentric_weight_delta[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4955314297777646011ull);
        }
    }
    vlSelf->rasterizer_frontend__DOT__w_should_be_culled = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17027596038121767235ull);
    vlSelf->rasterizer_frontend__DOT__current_state = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8981364374230031478ull);
    vlSelf->rasterizer_frontend__DOT__next_state = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 16921823075973722207ull);
    vlSelf->rasterizer_frontend__DOT____Vlvbound_h0f83b07d__0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1381254735186018854ull);
    vlSelf->rasterizer_frontend__DOT____Vlvbound_h3fb89b02__0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 59691725586688636ull);
    vlSelf->rasterizer_frontend__DOT____Vlvbound_hdd0e909d__0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3667511979014916375ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__edge_compute_inst__DOT__v1[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16536733702494955994ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__edge_compute_inst__DOT__v2[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4873197637523002679ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__edge_compute_inst__DOT__p[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8205301300412365947ull);
    }
    vlSelf->rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_function = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11052525325403835909ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5654726238198506198ull);
    }
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5555387113305086655ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15397657045449361633ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15849352053210727ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__A = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17177762343767098695ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17373982931631026316ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11540167677162408231ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11519507316742307100ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 870658369456794426ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7628924760352889008ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A_scaled = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10595282681226740995ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__X = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5846364122415846758ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8829537162422248385ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 1115693137854854981ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 10658080166131500478ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 3699039098980639399ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__AX = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6960050928283468518ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp_minus_AX = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8525711148761672ull);
    VL_SCOPED_RAND_RESET_W(65, vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__X_two_AX, __VscopeHash, 2474474247495021475ull);
    VL_SCOPED_RAND_RESET_W(65, vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next, __VscopeHash, 13641051659328144642ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_A_inv = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11898454067165394804ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8967800246718387586ull);
    vlSelf->rasterizer_frontend__DOT__fast_inverse_inst__DOT__next_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15660879603605617697ull);
    vlSelf->__Vtrigprevexpr___TOP__rasterizer_frontend__DOT__clk__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1793834623734604454ull);
    vlSelf->__Vtrigprevexpr___TOP__rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16385376702617867643ull);
}
