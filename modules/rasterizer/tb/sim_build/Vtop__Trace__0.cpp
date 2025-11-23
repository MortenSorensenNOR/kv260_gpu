// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgBit(oldp+0,(vlSelfRef.clk));
    bufp->chgBit(oldp+1,(vlSelfRef.rstn));
    bufp->chgIData(oldp+2,(vlSelfRef.i_v0[0]),32);
    bufp->chgIData(oldp+3,(vlSelfRef.i_v0[1]),32);
    bufp->chgIData(oldp+4,(vlSelfRef.i_v0[2]),32);
    bufp->chgIData(oldp+5,(vlSelfRef.i_v1[0]),32);
    bufp->chgIData(oldp+6,(vlSelfRef.i_v1[1]),32);
    bufp->chgIData(oldp+7,(vlSelfRef.i_v1[2]),32);
    bufp->chgIData(oldp+8,(vlSelfRef.i_v2[0]),32);
    bufp->chgIData(oldp+9,(vlSelfRef.i_v2[1]),32);
    bufp->chgIData(oldp+10,(vlSelfRef.i_v2[2]),32);
    bufp->chgIData(oldp+11,(vlSelfRef.i_attr_v0[0]),32);
    bufp->chgIData(oldp+12,(vlSelfRef.i_attr_v0[1]),32);
    bufp->chgIData(oldp+13,(vlSelfRef.i_attr_v0[2]),32);
    bufp->chgIData(oldp+14,(vlSelfRef.i_attr_v1[0]),32);
    bufp->chgIData(oldp+15,(vlSelfRef.i_attr_v1[1]),32);
    bufp->chgIData(oldp+16,(vlSelfRef.i_attr_v1[2]),32);
    bufp->chgIData(oldp+17,(vlSelfRef.i_attr_v2[0]),32);
    bufp->chgIData(oldp+18,(vlSelfRef.i_attr_v2[1]),32);
    bufp->chgIData(oldp+19,(vlSelfRef.i_attr_v2[2]),32);
    bufp->chgBit(oldp+20,(vlSelfRef.i_dv));
    bufp->chgBit(oldp+21,(vlSelfRef.o_ready));
    bufp->chgIData(oldp+22,(vlSelfRef.o_bb_tl[0]),32);
    bufp->chgIData(oldp+23,(vlSelfRef.o_bb_tl[1]),32);
    bufp->chgIData(oldp+24,(vlSelfRef.o_bb_br[0]),32);
    bufp->chgIData(oldp+25,(vlSelfRef.o_bb_br[1]),32);
    bufp->chgIData(oldp+26,(vlSelfRef.o_edge_val0),32);
    bufp->chgIData(oldp+27,(vlSelfRef.o_edge_val1),32);
    bufp->chgIData(oldp+28,(vlSelfRef.o_edge_val2),32);
    bufp->chgIData(oldp+29,(vlSelfRef.o_edge_delta0[0]),32);
    bufp->chgIData(oldp+30,(vlSelfRef.o_edge_delta0[1]),32);
    bufp->chgIData(oldp+31,(vlSelfRef.o_edge_delta1[0]),32);
    bufp->chgIData(oldp+32,(vlSelfRef.o_edge_delta1[1]),32);
    bufp->chgIData(oldp+33,(vlSelfRef.o_edge_delta2[0]),32);
    bufp->chgIData(oldp+34,(vlSelfRef.o_edge_delta2[1]),32);
    bufp->chgIData(oldp+35,(vlSelfRef.o_attr0[0]),32);
    bufp->chgIData(oldp+36,(vlSelfRef.o_attr0[1]),32);
    bufp->chgIData(oldp+37,(vlSelfRef.o_attr0[2]),32);
    bufp->chgIData(oldp+38,(vlSelfRef.o_attr0[3]),32);
    bufp->chgIData(oldp+39,(vlSelfRef.o_attr_dx[0]),32);
    bufp->chgIData(oldp+40,(vlSelfRef.o_attr_dx[1]),32);
    bufp->chgIData(oldp+41,(vlSelfRef.o_attr_dx[2]),32);
    bufp->chgIData(oldp+42,(vlSelfRef.o_attr_dx[3]),32);
    bufp->chgIData(oldp+43,(vlSelfRef.o_attr_dy[0]),32);
    bufp->chgIData(oldp+44,(vlSelfRef.o_attr_dy[1]),32);
    bufp->chgIData(oldp+45,(vlSelfRef.o_attr_dy[2]),32);
    bufp->chgIData(oldp+46,(vlSelfRef.o_attr_dy[3]),32);
    bufp->chgBit(oldp+47,(vlSelfRef.o_dv));
    bufp->chgBit(oldp+48,(vlSelfRef.i_ready));
    bufp->chgBit(oldp+49,(vlSelfRef.culled_triangle));
    bufp->chgBit(oldp+50,(vlSelfRef.rasterizer_frontend__DOT__clk));
    bufp->chgBit(oldp+51,(vlSelfRef.rasterizer_frontend__DOT__rstn));
    bufp->chgIData(oldp+52,(vlSelfRef.rasterizer_frontend__DOT__i_v0[0]),32);
    bufp->chgIData(oldp+53,(vlSelfRef.rasterizer_frontend__DOT__i_v0[1]),32);
    bufp->chgIData(oldp+54,(vlSelfRef.rasterizer_frontend__DOT__i_v0[2]),32);
    bufp->chgIData(oldp+55,(vlSelfRef.rasterizer_frontend__DOT__i_v1[0]),32);
    bufp->chgIData(oldp+56,(vlSelfRef.rasterizer_frontend__DOT__i_v1[1]),32);
    bufp->chgIData(oldp+57,(vlSelfRef.rasterizer_frontend__DOT__i_v1[2]),32);
    bufp->chgIData(oldp+58,(vlSelfRef.rasterizer_frontend__DOT__i_v2[0]),32);
    bufp->chgIData(oldp+59,(vlSelfRef.rasterizer_frontend__DOT__i_v2[1]),32);
    bufp->chgIData(oldp+60,(vlSelfRef.rasterizer_frontend__DOT__i_v2[2]),32);
    bufp->chgIData(oldp+61,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v0[0]),32);
    bufp->chgIData(oldp+62,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v0[1]),32);
    bufp->chgIData(oldp+63,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v0[2]),32);
    bufp->chgIData(oldp+64,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v1[0]),32);
    bufp->chgIData(oldp+65,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v1[1]),32);
    bufp->chgIData(oldp+66,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v1[2]),32);
    bufp->chgIData(oldp+67,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v2[0]),32);
    bufp->chgIData(oldp+68,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v2[1]),32);
    bufp->chgIData(oldp+69,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v2[2]),32);
    bufp->chgBit(oldp+70,(vlSelfRef.rasterizer_frontend__DOT__i_dv));
    bufp->chgBit(oldp+71,(vlSelfRef.rasterizer_frontend__DOT__o_ready));
    bufp->chgIData(oldp+72,(vlSelfRef.rasterizer_frontend__DOT__o_bb_tl[0]),32);
    bufp->chgIData(oldp+73,(vlSelfRef.rasterizer_frontend__DOT__o_bb_tl[1]),32);
    bufp->chgIData(oldp+74,(vlSelfRef.rasterizer_frontend__DOT__o_bb_br[0]),32);
    bufp->chgIData(oldp+75,(vlSelfRef.rasterizer_frontend__DOT__o_bb_br[1]),32);
    bufp->chgIData(oldp+76,(vlSelfRef.rasterizer_frontend__DOT__o_edge_val0),32);
    bufp->chgIData(oldp+77,(vlSelfRef.rasterizer_frontend__DOT__o_edge_val1),32);
    bufp->chgIData(oldp+78,(vlSelfRef.rasterizer_frontend__DOT__o_edge_val2),32);
    bufp->chgIData(oldp+79,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0[0]),32);
    bufp->chgIData(oldp+80,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0[1]),32);
    bufp->chgIData(oldp+81,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1[0]),32);
    bufp->chgIData(oldp+82,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1[1]),32);
    bufp->chgIData(oldp+83,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2[0]),32);
    bufp->chgIData(oldp+84,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2[1]),32);
    bufp->chgIData(oldp+85,(vlSelfRef.rasterizer_frontend__DOT__o_attr0[0]),32);
    bufp->chgIData(oldp+86,(vlSelfRef.rasterizer_frontend__DOT__o_attr0[1]),32);
    bufp->chgIData(oldp+87,(vlSelfRef.rasterizer_frontend__DOT__o_attr0[2]),32);
    bufp->chgIData(oldp+88,(vlSelfRef.rasterizer_frontend__DOT__o_attr0[3]),32);
    bufp->chgIData(oldp+89,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[0]),32);
    bufp->chgIData(oldp+90,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[1]),32);
    bufp->chgIData(oldp+91,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[2]),32);
    bufp->chgIData(oldp+92,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[3]),32);
    bufp->chgIData(oldp+93,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[0]),32);
    bufp->chgIData(oldp+94,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[1]),32);
    bufp->chgIData(oldp+95,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[2]),32);
    bufp->chgIData(oldp+96,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[3]),32);
    bufp->chgBit(oldp+97,(vlSelfRef.rasterizer_frontend__DOT__o_dv));
    bufp->chgBit(oldp+98,(vlSelfRef.rasterizer_frontend__DOT__i_ready));
    bufp->chgBit(oldp+99,(vlSelfRef.rasterizer_frontend__DOT__culled_triangle));
    bufp->chgIData(oldp+100,(vlSelfRef.rasterizer_frontend__DOT__i),32);
    bufp->chgIData(oldp+101,(vlSelfRef.rasterizer_frontend__DOT__r_v0[0]),32);
    bufp->chgIData(oldp+102,(vlSelfRef.rasterizer_frontend__DOT__r_v0[1]),32);
    bufp->chgIData(oldp+103,(vlSelfRef.rasterizer_frontend__DOT__r_v0[2]),32);
    bufp->chgIData(oldp+104,(vlSelfRef.rasterizer_frontend__DOT__r_v1[0]),32);
    bufp->chgIData(oldp+105,(vlSelfRef.rasterizer_frontend__DOT__r_v1[1]),32);
    bufp->chgIData(oldp+106,(vlSelfRef.rasterizer_frontend__DOT__r_v1[2]),32);
    bufp->chgIData(oldp+107,(vlSelfRef.rasterizer_frontend__DOT__r_v2[0]),32);
    bufp->chgIData(oldp+108,(vlSelfRef.rasterizer_frontend__DOT__r_v2[1]),32);
    bufp->chgIData(oldp+109,(vlSelfRef.rasterizer_frontend__DOT__r_v2[2]),32);
    bufp->chgIData(oldp+110,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[0]),32);
    bufp->chgIData(oldp+111,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[1]),32);
    bufp->chgIData(oldp+112,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[2]),32);
    bufp->chgIData(oldp+113,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[3]),32);
    bufp->chgIData(oldp+114,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[0]),32);
    bufp->chgIData(oldp+115,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[1]),32);
    bufp->chgIData(oldp+116,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[2]),32);
    bufp->chgIData(oldp+117,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[3]),32);
    bufp->chgIData(oldp+118,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[0]),32);
    bufp->chgIData(oldp+119,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[1]),32);
    bufp->chgIData(oldp+120,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[2]),32);
    bufp->chgIData(oldp+121,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[3]),32);
    bufp->chgIData(oldp+122,(vlSelfRef.rasterizer_frontend__DOT__r_attr0[0]),32);
    bufp->chgIData(oldp+123,(vlSelfRef.rasterizer_frontend__DOT__r_attr0[1]),32);
    bufp->chgIData(oldp+124,(vlSelfRef.rasterizer_frontend__DOT__r_attr0[2]),32);
    bufp->chgIData(oldp+125,(vlSelfRef.rasterizer_frontend__DOT__r_attr0[3]),32);
    bufp->chgIData(oldp+126,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[0]),32);
    bufp->chgIData(oldp+127,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[1]),32);
    bufp->chgIData(oldp+128,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[2]),32);
    bufp->chgIData(oldp+129,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[3]),32);
    bufp->chgIData(oldp+130,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[0]),32);
    bufp->chgIData(oldp+131,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[1]),32);
    bufp->chgIData(oldp+132,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[2]),32);
    bufp->chgIData(oldp+133,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[3]),32);
    bufp->chgQData(oldp+134,(vlSelfRef.rasterizer_frontend__DOT__w_attr[0]),64);
    bufp->chgQData(oldp+136,(vlSelfRef.rasterizer_frontend__DOT__w_attr[1]),64);
    bufp->chgQData(oldp+138,(vlSelfRef.rasterizer_frontend__DOT__w_attr[2]),64);
    bufp->chgQData(oldp+140,(vlSelfRef.rasterizer_frontend__DOT__w_attr[3]),64);
    bufp->chgQData(oldp+142,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[0]),64);
    bufp->chgQData(oldp+144,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[1]),64);
    bufp->chgQData(oldp+146,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[2]),64);
    bufp->chgQData(oldp+148,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[3]),64);
    bufp->chgQData(oldp+150,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[0]),64);
    bufp->chgQData(oldp+152,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[1]),64);
    bufp->chgQData(oldp+154,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[2]),64);
    bufp->chgQData(oldp+156,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[3]),64);
    bufp->chgIData(oldp+158,(vlSelfRef.rasterizer_frontend__DOT__r_edge_val0),32);
    bufp->chgIData(oldp+159,(vlSelfRef.rasterizer_frontend__DOT__r_edge_val1),32);
    bufp->chgIData(oldp+160,(vlSelfRef.rasterizer_frontend__DOT__r_edge_val2),32);
    bufp->chgIData(oldp+161,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[0]),32);
    bufp->chgIData(oldp+162,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[1]),32);
    bufp->chgIData(oldp+163,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[0]),32);
    bufp->chgIData(oldp+164,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[1]),32);
    bufp->chgIData(oldp+165,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[0]),32);
    bufp->chgIData(oldp+166,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[1]),32);
    bufp->chgQData(oldp+167,(vlSelfRef.rasterizer_frontend__DOT__r_area),40);
    bufp->chgIData(oldp+169,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[0]),32);
    bufp->chgIData(oldp+170,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[1]),32);
    bufp->chgIData(oldp+171,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[0]),32);
    bufp->chgIData(oldp+172,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[1]),32);
    bufp->chgIData(oldp+173,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[0]),32);
    bufp->chgIData(oldp+174,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[1]),32);
    bufp->chgQData(oldp+175,(vlSelfRef.rasterizer_frontend__DOT__w_edge_function_val),64);
    bufp->chgIData(oldp+177,(vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta[0]),32);
    bufp->chgIData(oldp+178,(vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta[1]),32);
    bufp->chgIData(oldp+179,(vlSelfRef.rasterizer_frontend__DOT__w_bb_tl[0]),32);
    bufp->chgIData(oldp+180,(vlSelfRef.rasterizer_frontend__DOT__w_bb_tl[1]),32);
    bufp->chgIData(oldp+181,(vlSelfRef.rasterizer_frontend__DOT__w_bb_br[0]),32);
    bufp->chgIData(oldp+182,(vlSelfRef.rasterizer_frontend__DOT__w_bb_br[1]),32);
    bufp->chgBit(oldp+183,(vlSelfRef.rasterizer_frontend__DOT__w_bb_valid));
    bufp->chgIData(oldp+184,(vlSelfRef.rasterizer_frontend__DOT__r_bb_tl[0]),32);
    bufp->chgIData(oldp+185,(vlSelfRef.rasterizer_frontend__DOT__r_bb_tl[1]),32);
    bufp->chgIData(oldp+186,(vlSelfRef.rasterizer_frontend__DOT__r_bb_br[0]),32);
    bufp->chgIData(oldp+187,(vlSelfRef.rasterizer_frontend__DOT__r_bb_br[1]),32);
    bufp->chgBit(oldp+188,(vlSelfRef.rasterizer_frontend__DOT__r_bb_valid));
    bufp->chgIData(oldp+189,(vlSelfRef.rasterizer_frontend__DOT__i_min_x),32);
    bufp->chgIData(oldp+190,(vlSelfRef.rasterizer_frontend__DOT__i_max_x),32);
    bufp->chgIData(oldp+191,(vlSelfRef.rasterizer_frontend__DOT__i_min_y),32);
    bufp->chgIData(oldp+192,(vlSelfRef.rasterizer_frontend__DOT__i_max_y),32);
    bufp->chgBit(oldp+193,(vlSelfRef.rasterizer_frontend__DOT__w_area_division_ready));
    bufp->chgIData(oldp+194,(vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A),32);
    bufp->chgBit(oldp+195,(vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A_dv));
    bufp->chgIData(oldp+196,(vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal),32);
    bufp->chgBit(oldp+197,(vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal_dv));
    bufp->chgIData(oldp+198,(vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal),32);
    bufp->chgQData(oldp+199,(vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[0]),64);
    bufp->chgQData(oldp+201,(vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[1]),64);
    bufp->chgQData(oldp+203,(vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[2]),64);
    bufp->chgQData(oldp+205,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                             [0U][0U]),64);
    bufp->chgQData(oldp+207,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                             [0U][1U]),64);
    bufp->chgQData(oldp+209,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                             [1U][0U]),64);
    bufp->chgQData(oldp+211,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                             [1U][1U]),64);
    bufp->chgQData(oldp+213,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                             [2U][0U]),64);
    bufp->chgQData(oldp+215,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                             [2U][1U]),64);
    bufp->chgIData(oldp+217,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[0]),32);
    bufp->chgIData(oldp+218,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[1]),32);
    bufp->chgIData(oldp+219,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[2]),32);
    bufp->chgIData(oldp+220,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                             [0U][0U]),32);
    bufp->chgIData(oldp+221,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                             [0U][1U]),32);
    bufp->chgIData(oldp+222,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                             [1U][0U]),32);
    bufp->chgIData(oldp+223,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                             [1U][1U]),32);
    bufp->chgIData(oldp+224,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                             [2U][0U]),32);
    bufp->chgIData(oldp+225,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                             [2U][1U]),32);
    bufp->chgBit(oldp+226,(vlSelfRef.rasterizer_frontend__DOT__w_should_be_culled));
    bufp->chgCData(oldp+227,(vlSelfRef.rasterizer_frontend__DOT__current_state),4);
    bufp->chgCData(oldp+228,(vlSelfRef.rasterizer_frontend__DOT__next_state),4);
    bufp->chgIData(oldp+229,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1[0]),32);
    bufp->chgIData(oldp+230,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1[1]),32);
    bufp->chgIData(oldp+231,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2[0]),32);
    bufp->chgIData(oldp+232,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2[1]),32);
    bufp->chgIData(oldp+233,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__p[0]),32);
    bufp->chgIData(oldp+234,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__p[1]),32);
    bufp->chgQData(oldp+235,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_function),64);
    bufp->chgIData(oldp+237,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta[0]),32);
    bufp->chgIData(oldp+238,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta[1]),32);
    bufp->chgBit(oldp+239,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk));
    bufp->chgBit(oldp+240,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn));
    bufp->chgBit(oldp+241,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__ready));
    bufp->chgIData(oldp+242,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A),32);
    bufp->chgBit(oldp+243,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv));
    bufp->chgIData(oldp+244,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv),32);
    bufp->chgBit(oldp+245,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv));
    bufp->chgCData(oldp+246,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter),4);
    bufp->chgQData(oldp+247,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A),64);
    bufp->chgQData(oldp+249,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A_scaled),64);
    bufp->chgQData(oldp+251,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X),64);
    bufp->chgIData(oldp+253,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i),32);
    bufp->chgCData(oldp+254,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt),6);
    bufp->chgCData(oldp+255,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt),6);
    bufp->chgQData(oldp+256,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp),64);
    bufp->chgQData(oldp+258,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__AX),64);
    bufp->chgQData(oldp+260,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp_minus_AX),64);
    bufp->chgWData(oldp+262,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X_two_AX),65);
    bufp->chgWData(oldp+265,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next),65);
    bufp->chgQData(oldp+268,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_A_inv),64);
    bufp->chgCData(oldp+270,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state),2);
    bufp->chgCData(oldp+271,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__next_state),2);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
