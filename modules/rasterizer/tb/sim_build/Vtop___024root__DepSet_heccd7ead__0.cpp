// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

extern const VlUnpacked<CData/*1:0*/, 128> Vtop__ConstPool__TABLE_h08df8bb1_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vtop__ConstPool__TABLE_h4a04a26f_0;
extern const VlUnpacked<CData/*3:0*/, 512> Vtop__ConstPool__TABLE_h83416bf4_0;
extern const VlUnpacked<CData/*0:0*/, 512> Vtop__ConstPool__TABLE_hc1c85e0c_0;

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
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
    vlSelfRef.rasterizer_frontend__DOT__clk = vlSelfRef.clk;
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

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);
void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf);
void Vtop___024root___nba_sequent__TOP__2(Vtop___024root* vlSelf);
void Vtop___024root___nba_comb__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_comb__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<3>/*95:0*/ __Vtemp_2;
    VlWide<3>/*95:0*/ __Vtemp_3;
    VlWide<3>/*95:0*/ __Vtemp_4;
    VlWide<3>/*95:0*/ __Vtemp_6;
    // Body
    if (vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn) {
        if ((2U & (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state))) {
            if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state)))) {
                vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter 
                    = (0xfU & ((IData)(1U) + (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter)));
                vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X 
                    = (((QData)((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next[1U])) 
                        << 0x20U) | (QData)((IData)(
                                                    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next[0U])));
            }
            if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state))) {
                vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv 
                    = (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_A_inv);
                vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv = 1U;
            }
        } else if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state)))) {
            vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter = 0U;
            vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv = 0U;
            vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv = 0U;
            vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X = 0x100000000ULL;
        }
        if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state))) {
                vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt 
                    = vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt;
            }
        }
    } else {
        vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter = 0U;
        vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv = 0U;
        vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv = 0U;
        vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X = 0x100000000ULL;
    }
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_A_inv 
        = ((0U == (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt))
            ? vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X
            : ((vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X 
                + VL_SHIFTL_QQI(64,64,32, 1ULL, ((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt) 
                                                 - (IData)(1U)))) 
               >> (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt)));
    if (vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn) {
        if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state) 
                      >> 1U)))) {
            if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state))) {
                vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A_scaled 
                    = (vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A 
                       >> (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt));
            }
        }
    }
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
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt = 0U;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i = 0x1fU;
    if (vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn) {
        if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state)))) {
                if (vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv) {
                    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A 
                        = ((QData)((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A)) 
                           << 0x20U);
                }
            }
        }
    } else {
        vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A = 0ULL;
    }
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
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state 
        = ((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn)
            ? (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__next_state)
            : 0U);
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v0;
    __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v4;
    __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v5;
    __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v5 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v6;
    __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v6 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_delta0__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_delta0__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v0;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_delta0__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_delta0__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v2;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v4;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_v2__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_v2__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v2__v0;
    __VdlySet__rasterizer_frontend__DOT__r_v2__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_v2__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_v2__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v2__v1;
    __VdlySet__rasterizer_frontend__DOT__r_v2__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_v2__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_v2__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v2__v2;
    __VdlySet__rasterizer_frontend__DOT__r_v2__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v2__v3;
    __VdlySet__rasterizer_frontend__DOT__r_v2__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_dy__v0;
    __VdlySet__rasterizer_frontend__DOT__r_attr_dy__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v3 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_dy__v4;
    __VdlySet__rasterizer_frontend__DOT__r_attr_dy__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_v0__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_v0__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v0__v0;
    __VdlySet__rasterizer_frontend__DOT__r_v0__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_v0__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_v0__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v0__v1;
    __VdlySet__rasterizer_frontend__DOT__r_v0__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_v0__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_v0__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v0__v2;
    __VdlySet__rasterizer_frontend__DOT__r_v0__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v0__v3;
    __VdlySet__rasterizer_frontend__DOT__r_v0__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr0__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_attr0__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr0__v0;
    __VdlySet__rasterizer_frontend__DOT__r_attr0__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr0__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_attr0__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr0__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_attr0__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr0__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_attr0__v3 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr0__v4;
    __VdlySet__rasterizer_frontend__DOT__r_attr0__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_bb_br__v0;
    __VdlyVal__rasterizer_frontend__DOT__o_bb_br__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__o_bb_br__v0;
    __VdlySet__rasterizer_frontend__DOT__o_bb_br__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_bb_br__v1;
    __VdlyVal__rasterizer_frontend__DOT__o_bb_br__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v0;
    __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__o_attr_dy__v0;
    __VdlySet__rasterizer_frontend__DOT__o_attr_dy__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v1;
    __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v2;
    __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v3;
    __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_v1__v0;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v1__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v3 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_v1__v4;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v1__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v0;
    __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__o_attr_dx__v0;
    __VdlySet__rasterizer_frontend__DOT__o_attr_dx__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v1;
    __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v2;
    __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v3;
    __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_v0__v0;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v0__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v3 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_v0__v4;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v0__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr0__v0;
    __VdlyVal__rasterizer_frontend__DOT__o_attr0__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__o_attr0__v0;
    __VdlySet__rasterizer_frontend__DOT__o_attr0__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr0__v1;
    __VdlyVal__rasterizer_frontend__DOT__o_attr0__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr0__v2;
    __VdlyVal__rasterizer_frontend__DOT__o_attr0__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_attr0__v3;
    __VdlyVal__rasterizer_frontend__DOT__o_attr0__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_edge_delta2__v0;
    __VdlyVal__rasterizer_frontend__DOT__o_edge_delta2__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__o_edge_delta2__v0;
    __VdlySet__rasterizer_frontend__DOT__o_edge_delta2__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_edge_delta2__v1;
    __VdlyVal__rasterizer_frontend__DOT__o_edge_delta2__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v0;
    __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v3;
    __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_bb_br__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_bb_br__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_bb_br__v0;
    __VdlySet__rasterizer_frontend__DOT__r_bb_br__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_bb_br__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_bb_br__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_bb_br__v2;
    __VdlySet__rasterizer_frontend__DOT__r_bb_br__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_edge_delta0__v0;
    __VdlyVal__rasterizer_frontend__DOT__o_edge_delta0__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__o_edge_delta0__v0;
    __VdlySet__rasterizer_frontend__DOT__o_edge_delta0__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_edge_delta0__v1;
    __VdlyVal__rasterizer_frontend__DOT__o_edge_delta0__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_dx__v0;
    __VdlySet__rasterizer_frontend__DOT__r_attr_dx__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v3 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_dx__v4;
    __VdlySet__rasterizer_frontend__DOT__r_attr_dx__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_bb_tl__v0;
    __VdlyVal__rasterizer_frontend__DOT__o_bb_tl__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__o_bb_tl__v0;
    __VdlySet__rasterizer_frontend__DOT__o_bb_tl__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_bb_tl__v1;
    __VdlyVal__rasterizer_frontend__DOT__o_bb_tl__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v0;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v2;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v4;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v4 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v4;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v5;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v5 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v6;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v6 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v6;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v6 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v7;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v7 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v8;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v8 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v8;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v8 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v9;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v9 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v10;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v10 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v12;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v12 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_edge_delta1__v0;
    __VdlyVal__rasterizer_frontend__DOT__o_edge_delta1__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__o_edge_delta1__v0;
    __VdlySet__rasterizer_frontend__DOT__o_edge_delta1__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__o_edge_delta1__v1;
    __VdlyVal__rasterizer_frontend__DOT__o_edge_delta1__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v0;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v2;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v3 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v4;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v4 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v4;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v4;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v5;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v5 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v5;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v5 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v6;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v6 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v6;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v6 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v6;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v6 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v7;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v7 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v7;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v7 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v8;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v8 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v8;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v8 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v8;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v8 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v9;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v9 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v9;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v9 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v10;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v10 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v12;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v12 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_delta2__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_delta2__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v0;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_delta2__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_delta2__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v2;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v4;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_delta1__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_delta1__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v0;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_edge_delta1__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_edge_delta1__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v2;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v4;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_v2__v0;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v2__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v3;
    __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v3 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_attr_v2__v4;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v2__v4 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_bb_tl__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_bb_tl__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_bb_tl__v0;
    __VdlySet__rasterizer_frontend__DOT__r_bb_tl__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_bb_tl__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_bb_tl__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_bb_tl__v2;
    __VdlySet__rasterizer_frontend__DOT__r_bb_tl__v2 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_v1__v0;
    __VdlyVal__rasterizer_frontend__DOT__r_v1__v0 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v1__v0;
    __VdlySet__rasterizer_frontend__DOT__r_v1__v0 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_v1__v1;
    __VdlyVal__rasterizer_frontend__DOT__r_v1__v1 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v1__v1;
    __VdlySet__rasterizer_frontend__DOT__r_v1__v1 = 0;
    IData/*31:0*/ __VdlyVal__rasterizer_frontend__DOT__r_v1__v2;
    __VdlyVal__rasterizer_frontend__DOT__r_v1__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v1__v2;
    __VdlySet__rasterizer_frontend__DOT__r_v1__v2 = 0;
    CData/*0:0*/ __VdlySet__rasterizer_frontend__DOT__r_v1__v3;
    __VdlySet__rasterizer_frontend__DOT__r_v1__v3 = 0;
    // Body
    __VdlySet__rasterizer_frontend__DOT__r_bb_br__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_bb_br__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_bb_tl__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_bb_tl__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_dy__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_dy__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr0__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr0__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_dx__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_dx__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v3 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__o_bb_br__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__o_edge_delta2__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__o_edge_delta0__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__o_edge_delta1__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v6 = 0U;
    __VdlySet__rasterizer_frontend__DOT__o_attr_dy__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__o_attr_dx__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__o_attr0__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v1__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v1__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v0__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v0__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v2__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_attr_v2__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v2__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v2__v1 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v2__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v2__v3 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v0__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v0__v1 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v0__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v0__v3 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v1__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v1__v1 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v1__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_v1__v3 = 0U;
    __VdlySet__rasterizer_frontend__DOT__o_bb_tl__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v6 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v8 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v10 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v12 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v0 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v2 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v4 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v6 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v8 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v10 = 0U;
    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v12 = 0U;
    if (vlSelfRef.rasterizer_frontend__DOT__rstn) {
        if ((8U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
            if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                          >> 2U)))) {
                if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                              >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                        if (vlSelfRef.rasterizer_frontend__DOT__i_ready) {
                            __VdlyVal__rasterizer_frontend__DOT__o_bb_br__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__r_bb_br
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__o_bb_br__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__o_bb_br__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__r_bb_br
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__o_edge_delta2__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__o_edge_delta2__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__o_edge_delta2__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__o_edge_delta0__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__o_edge_delta0__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__o_edge_delta0__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__o_edge_delta1__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__o_edge_delta1__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__o_edge_delta1__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr_dy
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__o_attr_dy__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr_dy
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v2 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr_dy
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v3 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr_dy
                                [3U];
                            __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr_dx
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__o_attr_dx__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr_dx
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v2 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr_dx
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v3 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr_dx
                                [3U];
                            __VdlyVal__rasterizer_frontend__DOT__o_attr0__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr0
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__o_attr0__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__o_attr0__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr0
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__o_attr0__v2 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr0
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__o_attr0__v3 
                                = vlSelfRef.rasterizer_frontend__DOT__r_attr0
                                [3U];
                            __VdlyVal__rasterizer_frontend__DOT__o_bb_tl__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__r_bb_tl
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__o_bb_tl__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__o_bb_tl__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__r_bb_tl
                                [1U];
                            vlSelfRef.rasterizer_frontend__DOT__o_edge_val0 
                                = vlSelfRef.rasterizer_frontend__DOT__r_edge_val0;
                            vlSelfRef.rasterizer_frontend__DOT__o_edge_val2 
                                = vlSelfRef.rasterizer_frontend__DOT__r_edge_val2;
                            vlSelfRef.rasterizer_frontend__DOT__o_edge_val1 
                                = vlSelfRef.rasterizer_frontend__DOT__r_edge_val1;
                            vlSelfRef.rasterizer_frontend__DOT__o_dv = 1U;
                        } else {
                            vlSelfRef.rasterizer_frontend__DOT__o_dv = 0U;
                        }
                    }
                }
            }
        } else {
            if ((4U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                              >> 1U)))) {
                    if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                        __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v0 = 1U;
                    }
                }
            } else if ((2U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v2 
                        = vlSelfRef.rasterizer_frontend__DOT__r_bb_tl
                        [0U];
                    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v2 = 1U;
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v3 
                        = vlSelfRef.rasterizer_frontend__DOT__r_bb_tl
                        [1U];
                } else if (vlSelfRef.rasterizer_frontend__DOT__w_area_division_ready) {
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v4 
                        = vlSelfRef.rasterizer_frontend__DOT__r_bb_tl
                        [0U];
                    __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v4 = 1U;
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v5 
                        = vlSelfRef.rasterizer_frontend__DOT__r_bb_tl
                        [1U];
                }
            } else if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v6 
                    = vlSelfRef.rasterizer_frontend__DOT__w_bb_tl
                    [0U];
                __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v6 = 1U;
                __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v7 
                    = vlSelfRef.rasterizer_frontend__DOT__w_bb_tl
                    [1U];
            } else if (vlSelfRef.rasterizer_frontend__DOT__i_dv) {
                __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v8 
                    = vlSelfRef.rasterizer_frontend__DOT__i_v2
                    [0U];
                __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v8 = 1U;
                __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v9 
                    = vlSelfRef.rasterizer_frontend__DOT__i_v2
                    [1U];
            } else {
                __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v10 = 1U;
            }
            if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                          >> 2U)))) {
                if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                              >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                        vlSelfRef.rasterizer_frontend__DOT__o_dv = 0U;
                    }
                }
            }
        }
        if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                      >> 3U)))) {
            if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                          >> 2U)))) {
                if ((2U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                    if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_delta0__v0 
                            = vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta
                            [0U];
                        __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_delta0__v1 
                            = vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta
                            [1U];
                        vlSelfRef.rasterizer_frontend__DOT__culled_triangle 
                            = vlSelfRef.rasterizer_frontend__DOT__w_should_be_culled;
                        if (vlSelfRef.rasterizer_frontend__DOT__w_area_division_ready) {
                            vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A 
                                = (IData)(vlSelfRef.rasterizer_frontend__DOT__r_area);
                        }
                    }
                    if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_delta1__v0 
                            = vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta
                            [0U];
                        __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_delta1__v1 
                            = vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta
                            [1U];
                    }
                    vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A_dv 
                        = ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) 
                           && (IData)(vlSelfRef.rasterizer_frontend__DOT__w_area_division_ready));
                } else if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                    __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v2 = 1U;
                    __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v2 = 1U;
                    vlSelfRef.rasterizer_frontend__DOT__culled_triangle = 0U;
                }
                if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                              >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                        if (vlSelfRef.rasterizer_frontend__DOT__i_dv) {
                            vlSelfRef.rasterizer_frontend__DOT__i = 1U;
                            vlSelfRef.rasterizer_frontend__DOT__i = 2U;
                            vlSelfRef.rasterizer_frontend__DOT__i = 3U;
                            vlSelfRef.rasterizer_frontend__DOT__i = 4U;
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_attr_v1
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__r_attr_v1__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__i_attr_v1
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v2 
                                = vlSelfRef.rasterizer_frontend__DOT__i_attr_v1
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v3 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v1
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_attr_v0
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__r_attr_v0__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__i_attr_v0
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v2 
                                = vlSelfRef.rasterizer_frontend__DOT__i_attr_v0
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v3 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v0
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_attr_v2
                                [0U];
                            __VdlySet__rasterizer_frontend__DOT__r_attr_v2__v0 = 1U;
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v1 
                                = vlSelfRef.rasterizer_frontend__DOT__i_attr_v2
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v2 
                                = vlSelfRef.rasterizer_frontend__DOT__i_attr_v2
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v3 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v2
                                [2U];
                            vlSelfRef.rasterizer_frontend__DOT____Vlvbound_hdd0e909d__0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v2
                                [0U];
                            __VdlyVal__rasterizer_frontend__DOT__r_v2__v0 
                                = vlSelfRef.rasterizer_frontend__DOT____Vlvbound_hdd0e909d__0;
                            __VdlySet__rasterizer_frontend__DOT__r_v2__v0 = 1U;
                            vlSelfRef.rasterizer_frontend__DOT____Vlvbound_hdd0e909d__0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v2
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__r_v2__v1 
                                = vlSelfRef.rasterizer_frontend__DOT____Vlvbound_hdd0e909d__0;
                            __VdlySet__rasterizer_frontend__DOT__r_v2__v1 = 1U;
                            vlSelfRef.rasterizer_frontend__DOT____Vlvbound_hdd0e909d__0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v2
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__r_v2__v2 
                                = vlSelfRef.rasterizer_frontend__DOT____Vlvbound_hdd0e909d__0;
                            __VdlySet__rasterizer_frontend__DOT__r_v2__v2 = 1U;
                            vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h0f83b07d__0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v0
                                [0U];
                            __VdlyVal__rasterizer_frontend__DOT__r_v0__v0 
                                = vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h0f83b07d__0;
                            __VdlySet__rasterizer_frontend__DOT__r_v0__v0 = 1U;
                            vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h0f83b07d__0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v0
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__r_v0__v1 
                                = vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h0f83b07d__0;
                            __VdlySet__rasterizer_frontend__DOT__r_v0__v1 = 1U;
                            vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h0f83b07d__0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v0
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__r_v0__v2 
                                = vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h0f83b07d__0;
                            __VdlySet__rasterizer_frontend__DOT__r_v0__v2 = 1U;
                            vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h3fb89b02__0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v1
                                [0U];
                            __VdlyVal__rasterizer_frontend__DOT__r_v1__v0 
                                = vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h3fb89b02__0;
                            __VdlySet__rasterizer_frontend__DOT__r_v1__v0 = 1U;
                            vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h3fb89b02__0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v1
                                [1U];
                            __VdlyVal__rasterizer_frontend__DOT__r_v1__v1 
                                = vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h3fb89b02__0;
                            __VdlySet__rasterizer_frontend__DOT__r_v1__v1 = 1U;
                            vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h3fb89b02__0 
                                = vlSelfRef.rasterizer_frontend__DOT__i_v1
                                [2U];
                            __VdlyVal__rasterizer_frontend__DOT__r_v1__v2 
                                = vlSelfRef.rasterizer_frontend__DOT____Vlvbound_h3fb89b02__0;
                            __VdlySet__rasterizer_frontend__DOT__r_v1__v2 = 1U;
                        }
                    }
                    if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                        __VdlyVal__rasterizer_frontend__DOT__r_bb_br__v0 
                            = vlSelfRef.rasterizer_frontend__DOT__w_bb_br
                            [0U];
                        __VdlySet__rasterizer_frontend__DOT__r_bb_br__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_bb_br__v1 
                            = vlSelfRef.rasterizer_frontend__DOT__w_bb_br
                            [1U];
                        __VdlyVal__rasterizer_frontend__DOT__r_bb_tl__v0 
                            = vlSelfRef.rasterizer_frontend__DOT__w_bb_tl
                            [0U];
                        __VdlySet__rasterizer_frontend__DOT__r_bb_tl__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_bb_tl__v1 
                            = vlSelfRef.rasterizer_frontend__DOT__w_bb_tl
                            [1U];
                        vlSelfRef.rasterizer_frontend__DOT__r_bb_valid 
                            = vlSelfRef.rasterizer_frontend__DOT__w_bb_valid;
                        vlSelfRef.rasterizer_frontend__DOT__r_area 
                            = (0xffffffffffULL & (vlSelfRef.rasterizer_frontend__DOT__w_edge_function_val 
                                                  >> 0x10U));
                    } else {
                        vlSelfRef.rasterizer_frontend__DOT__r_area = 0ULL;
                    }
                }
                if ((2U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                    if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                        vlSelfRef.rasterizer_frontend__DOT__r_edge_val0 
                            = (IData)((vlSelfRef.rasterizer_frontend__DOT__w_edge_function_val 
                                       >> 0x10U));
                    }
                    if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                        vlSelfRef.rasterizer_frontend__DOT__r_edge_val1 
                            = (IData)((vlSelfRef.rasterizer_frontend__DOT__w_edge_function_val 
                                       >> 0x10U));
                    }
                } else if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                    vlSelfRef.rasterizer_frontend__DOT__r_edge_val0 = 0U;
                    vlSelfRef.rasterizer_frontend__DOT__r_edge_val1 = 0U;
                }
            }
            if ((4U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                if ((2U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                    if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                        __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v0 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr_dy
                                                     [0U], 0x10U));
                        __VdlySet__rasterizer_frontend__DOT__r_attr_dy__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v1 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr_dy
                                                     [1U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v2 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr_dy
                                                     [2U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v3 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr_dy
                                                     [3U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_attr0__v0 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr
                                                     [0U], 0x10U));
                        __VdlySet__rasterizer_frontend__DOT__r_attr0__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_attr0__v1 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr
                                                     [1U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_attr0__v2 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr
                                                     [2U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_attr0__v3 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr
                                                     [3U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v0 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr_dx
                                                     [0U], 0x10U));
                        __VdlySet__rasterizer_frontend__DOT__r_attr_dx__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v1 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr_dx
                                                     [1U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v2 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr_dx
                                                     [2U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v3 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_attr_dx
                                                     [3U], 0x10U));
                    }
                    if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                        __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v0 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_bw_mul
                                                     [0U], 0x10U));
                        __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v1 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_bw_mul
                                                     [1U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v2 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_bw_mul
                                                     [2U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v0 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                                                     [0U]
                                                     [0U], 0x10U));
                        __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v1 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                                                     [0U]
                                                     [1U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v2 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                                                     [1U]
                                                     [0U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v3 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                                                     [1U]
                                                     [1U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v4 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                                                     [2U]
                                                     [0U], 0x10U));
                        __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v5 
                            = (IData)(VL_SHIFTRS_QQI(64,64,32, 
                                                     vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                                                     [2U]
                                                     [1U], 0x10U));
                    }
                }
                if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                              >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_delta2__v0 
                            = vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta
                            [0U];
                        __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v0 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_delta2__v1 
                            = vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta
                            [1U];
                        vlSelfRef.rasterizer_frontend__DOT__r_edge_val2 
                            = (IData)((vlSelfRef.rasterizer_frontend__DOT__w_edge_function_val 
                                       >> 0x10U));
                    }
                    if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                        __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v0 = 1U;
                        if (vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal_dv) {
                            vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal 
                                = vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal;
                        }
                    }
                }
            } else {
                if ((1U & (~ ((IData)(vlSelfRef.rasterizer_frontend__DOT__current_state) 
                              >> 1U)))) {
                    if ((1U & (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state)))) {
                        __VdlySet__rasterizer_frontend__DOT__r_attr_dy__v4 = 1U;
                        __VdlySet__rasterizer_frontend__DOT__r_attr0__v4 = 1U;
                        __VdlySet__rasterizer_frontend__DOT__r_attr_dx__v4 = 1U;
                        __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v3 = 1U;
                        __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v2 = 1U;
                        __VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v6 = 1U;
                        vlSelfRef.rasterizer_frontend__DOT__r_edge_val2 = 0U;
                    }
                }
                if ((2U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                    if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v2 
                            = vlSelfRef.rasterizer_frontend__DOT__r_v2
                            [0U];
                        __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v2 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v2 
                            = vlSelfRef.rasterizer_frontend__DOT__r_v0
                            [0U];
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v3 
                            = vlSelfRef.rasterizer_frontend__DOT__r_v2
                            [1U];
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v3 
                            = vlSelfRef.rasterizer_frontend__DOT__r_v0
                            [1U];
                    } else if (vlSelfRef.rasterizer_frontend__DOT__w_area_division_ready) {
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v4 
                            = vlSelfRef.rasterizer_frontend__DOT__r_v1
                            [0U];
                        __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v4 = 1U;
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v4 
                            = vlSelfRef.rasterizer_frontend__DOT__r_v2
                            [0U];
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v5 
                            = vlSelfRef.rasterizer_frontend__DOT__r_v1
                            [1U];
                        __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v5 
                            = vlSelfRef.rasterizer_frontend__DOT__r_v2
                            [1U];
                    }
                } else if ((1U & (IData)(vlSelfRef.rasterizer_frontend__DOT__current_state))) {
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v6 
                        = vlSelfRef.rasterizer_frontend__DOT__r_v0
                        [0U];
                    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v6 = 1U;
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v6 
                        = vlSelfRef.rasterizer_frontend__DOT__r_v1
                        [0U];
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v7 
                        = vlSelfRef.rasterizer_frontend__DOT__r_v0
                        [1U];
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v7 
                        = vlSelfRef.rasterizer_frontend__DOT__r_v1
                        [1U];
                } else if (vlSelfRef.rasterizer_frontend__DOT__i_dv) {
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v8 
                        = vlSelfRef.rasterizer_frontend__DOT__i_v0
                        [0U];
                    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v8 = 1U;
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v8 
                        = vlSelfRef.rasterizer_frontend__DOT__i_v1
                        [0U];
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v9 
                        = vlSelfRef.rasterizer_frontend__DOT__i_v0
                        [1U];
                    __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v9 
                        = vlSelfRef.rasterizer_frontend__DOT__i_v1
                        [1U];
                } else {
                    __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v10 = 1U;
                }
            }
        }
        vlSelfRef.rasterizer_frontend__DOT__current_state 
            = vlSelfRef.rasterizer_frontend__DOT__next_state;
    } else {
        __VdlySet__rasterizer_frontend__DOT__r_bb_br__v2 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_bb_tl__v2 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v4 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v4 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v4 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_attr_v1__v4 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_attr_v0__v4 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_attr_v2__v4 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_v2__v3 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_v0__v3 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_v1__v3 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v12 = 1U;
        __VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v12 = 1U;
        vlSelfRef.rasterizer_frontend__DOT__culled_triangle = 0U;
        vlSelfRef.rasterizer_frontend__DOT__o_dv = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A_dv = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_val0 = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_val2 = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_val1 = 0U;
        vlSelfRef.rasterizer_frontend__DOT__current_state = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v1;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight__v2;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_barycentric_weight__v3) {
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[2U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_bb_br__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_bb_br[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_bb_br__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_bb_br[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_bb_br__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_bb_br__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_bb_br[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_bb_br[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__o_bb_br__v0) {
        vlSelfRef.rasterizer_frontend__DOT__o_bb_br[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_bb_br__v0;
        vlSelfRef.rasterizer_frontend__DOT__o_bb_br[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_bb_br__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_delta2__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_delta2__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_delta2__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__o_edge_delta2__v0) {
        vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_edge_delta2__v0;
        vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_edge_delta2__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_delta0__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_delta0__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_delta0__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__o_edge_delta0__v0) {
        vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_edge_delta0__v0;
        vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_edge_delta0__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_delta1__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_delta1__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_delta1__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__o_edge_delta1__v0) {
        vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_edge_delta1__v0;
        vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_edge_delta1__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[0U][0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[0U][1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v1;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[1U][0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[1U][1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v3;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[2U][0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v4;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[2U][1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_barycentric_weight_delta__v5;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_barycentric_weight_delta__v6) {
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[0U][0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[0U][1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[1U][0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[1U][1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[2U][0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta[2U][1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_dy__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v1;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[3U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_dy__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_dy__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[2U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[3U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__o_attr_dy__v0) {
        vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v0;
        vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v1;
        vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v2;
        vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[3U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr_dy__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_dx__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v1;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[3U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_dx__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_dx__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[2U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[3U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__o_attr_dx__v0) {
        vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v0;
        vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v1;
        vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v2;
        vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[3U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr_dx__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr0__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr0[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr0__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_attr0[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr0__v1;
        vlSelfRef.rasterizer_frontend__DOT__r_attr0[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr0__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_attr0[3U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr0__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr0__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr0[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr0[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr0[2U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr0[3U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__o_attr0__v0) {
        vlSelfRef.rasterizer_frontend__DOT__o_attr0[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr0__v0;
        vlSelfRef.rasterizer_frontend__DOT__o_attr0[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr0__v1;
        vlSelfRef.rasterizer_frontend__DOT__o_attr0[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr0__v2;
        vlSelfRef.rasterizer_frontend__DOT__o_attr0[3U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_attr0__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_v1__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v1;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[3U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v1__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_v1__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[2U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[3U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_v0__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v1;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[3U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v0__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_v0__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[2U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[3U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_v2__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v1;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[3U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_attr_v2__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_attr_v2__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[2U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[3U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_bb_tl__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_bb_tl[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_bb_tl__v0;
        vlSelfRef.rasterizer_frontend__DOT__r_bb_tl[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_bb_tl__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_bb_tl__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_bb_tl[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_bb_tl[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__o_bb_tl__v0) {
        vlSelfRef.rasterizer_frontend__DOT__o_bb_tl[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_bb_tl__v0;
        vlSelfRef.rasterizer_frontend__DOT__o_bb_tl[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__o_bb_tl__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v4;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v5;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v6) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v6;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v7;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v8) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v8;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_p__v9;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v10) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_p__v12) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v2__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_v2[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_v2__v0;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v2__v1) {
        vlSelfRef.rasterizer_frontend__DOT__r_v2[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_v2__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v2__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_v2[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_v2__v2;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v2__v3) {
        vlSelfRef.rasterizer_frontend__DOT__r_v2[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_v2[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_v2[2U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v0__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_v0[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_v0__v0;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v0__v1) {
        vlSelfRef.rasterizer_frontend__DOT__r_v0[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_v0__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v0__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_v0[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_v0__v2;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v0__v3) {
        vlSelfRef.rasterizer_frontend__DOT__r_v0[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_v0[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_v0[2U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v1__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_v1[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_v1__v0;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v1__v1) {
        vlSelfRef.rasterizer_frontend__DOT__r_v1[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_v1__v1;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v1__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_v1[2U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_v1__v2;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_v1__v3) {
        vlSelfRef.rasterizer_frontend__DOT__r_v1[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_v1[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_v1[2U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v0) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v2) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v3;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v2;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v3;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v4) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v4;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v5;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v4;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v5;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v6) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v6;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v7;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v6;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v7;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v8) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v8;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v1__v9;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[0U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v8;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[1U] 
            = __VdlyVal__rasterizer_frontend__DOT__r_edge_function_v2__v9;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v10) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[1U] = 0U;
    }
    if (__VdlySet__rasterizer_frontend__DOT__r_edge_function_v1__v12) {
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[1U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[0U] = 0U;
        vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[1U] = 0U;
    }
    vlSelfRef.o_bb_br[0U] = vlSelfRef.rasterizer_frontend__DOT__o_bb_br
        [0U];
    vlSelfRef.o_bb_br[1U] = vlSelfRef.rasterizer_frontend__DOT__o_bb_br
        [1U];
    vlSelfRef.o_edge_delta2[0U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2
        [0U];
    vlSelfRef.o_edge_delta2[1U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2
        [1U];
    vlSelfRef.o_edge_delta0[0U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0
        [0U];
    vlSelfRef.o_edge_delta0[1U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0
        [1U];
    vlSelfRef.o_edge_delta1[0U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1
        [0U];
    vlSelfRef.o_edge_delta1[1U] = vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1
        [1U];
    vlSelfRef.o_attr_dy[0U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dy
        [0U];
    vlSelfRef.o_attr_dy[1U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dy
        [1U];
    vlSelfRef.o_attr_dy[2U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dy
        [2U];
    vlSelfRef.o_attr_dy[3U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dy
        [3U];
    vlSelfRef.o_attr_dx[0U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dx
        [0U];
    vlSelfRef.o_attr_dx[1U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dx
        [1U];
    vlSelfRef.o_attr_dx[2U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dx
        [2U];
    vlSelfRef.o_attr_dx[3U] = vlSelfRef.rasterizer_frontend__DOT__o_attr_dx
        [3U];
    vlSelfRef.o_attr0[0U] = vlSelfRef.rasterizer_frontend__DOT__o_attr0
        [0U];
    vlSelfRef.o_attr0[1U] = vlSelfRef.rasterizer_frontend__DOT__o_attr0
        [1U];
    vlSelfRef.o_attr0[2U] = vlSelfRef.rasterizer_frontend__DOT__o_attr0
        [2U];
    vlSelfRef.o_attr0[3U] = vlSelfRef.rasterizer_frontend__DOT__o_attr0
        [3U];
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
    vlSelfRef.o_bb_tl[0U] = vlSelfRef.rasterizer_frontend__DOT__o_bb_tl
        [0U];
    vlSelfRef.o_bb_tl[1U] = vlSelfRef.rasterizer_frontend__DOT__o_bb_tl
        [1U];
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
    vlSelfRef.culled_triangle = vlSelfRef.rasterizer_frontend__DOT__culled_triangle;
    vlSelfRef.o_dv = vlSelfRef.rasterizer_frontend__DOT__o_dv;
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
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv 
        = vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A_dv;
    vlSelfRef.o_edge_val0 = vlSelfRef.rasterizer_frontend__DOT__o_edge_val0;
    vlSelfRef.o_edge_val2 = vlSelfRef.rasterizer_frontend__DOT__o_edge_val2;
    vlSelfRef.o_edge_val1 = vlSelfRef.rasterizer_frontend__DOT__o_edge_val1;
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A 
        = vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A;
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
    vlSelfRef.rasterizer_frontend__DOT__w_edge_function_val 
        = vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_function;
    vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta[0U] 
        = vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta
        [0U];
    vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta[1U] 
        = vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta
        [1U];
    vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[0U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_val0), 
                      VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[1U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_val1), 
                      VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[2U] 
        = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_edge_val2), 
                      VL_EXTENDS_QI(64,32, vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal));
    vlSelfRef.rasterizer_frontend__DOT__w_should_be_culled 
        = (1U & (VL_GTES_IQQ(40, 0ULL, vlSelfRef.rasterizer_frontend__DOT__r_area) 
                 | (~ (IData)(vlSelfRef.rasterizer_frontend__DOT__r_bb_valid))));
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__2(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__2\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal 
        = vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv;
    vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal_dv 
        = vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv;
}

VL_INLINE_OPT void Vtop___024root___nba_comb__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    SData/*8:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*6:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    // Body
    __Vtableidx2 = (((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv) 
                     << 6U) | (((IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter) 
                                << 2U) | (IData)(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state)));
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__next_state 
        = Vtop__ConstPool__TABLE_h08df8bb1_0[__Vtableidx2];
    vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__ready 
        = Vtop__ConstPool__TABLE_h4a04a26f_0[__Vtableidx2];
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

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/home/morten/dev/graphics/kv260_gpu/modules/rasterizer/src/rasterizer_frontend_simple.sv", 7, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/home/morten/dev/graphics/kv260_gpu/modules/rasterizer/src/rasterizer_frontend_simple.sv", 7, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/home/morten/dev/graphics/kv260_gpu/modules/rasterizer/src/rasterizer_frontend_simple.sv", 7, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.rstn & 0xfeU)))) {
        Verilated::overWidthError("rstn");}
    if (VL_UNLIKELY(((vlSelfRef.i_dv & 0xfeU)))) {
        Verilated::overWidthError("i_dv");}
    if (VL_UNLIKELY(((vlSelfRef.i_ready & 0xfeU)))) {
        Verilated::overWidthError("i_ready");}
}
#endif  // VL_DEBUG
