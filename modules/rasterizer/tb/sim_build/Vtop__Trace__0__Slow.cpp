// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+1,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"rstn",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("i_v0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+3+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_v1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+6+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_v2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+9+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_attr_v0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+12+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_attr_v1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+15+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_attr_v2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+18+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBit(c+21,0,"i_dv",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+22,0,"o_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("o_bb_tl", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+23+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_bb_br", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+25+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+27,0,"o_edge_val0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+28,0,"o_edge_val1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+29,0,"o_edge_val2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("o_edge_delta0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+30+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_edge_delta1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+32+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_edge_delta2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+34+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_attr0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+36+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_attr_dx", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+40+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_attr_dy", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+44+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBit(c+48,0,"o_dv",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+49,0,"i_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+50,0,"culled_triangle",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("rasterizer_frontend", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+273,0,"SIGNED",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+274,0,"INT_BITS",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+274,0,"FRAC_BITS",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+275,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+276,0,"AREA_INT_BITS",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+277,0,"AREA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+278,0,"N_ATTR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+279,0,"SCREEN_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+279,0,"SCREEN_HEIGHT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+51,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+52,0,"rstn",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("i_v0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+53+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_v1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+56+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_v2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+59+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_attr_v0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+62+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_attr_v1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+65+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("i_attr_v2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+68+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBit(c+71,0,"i_dv",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+72,0,"o_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("o_bb_tl", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+73+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_bb_br", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+75+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+77,0,"o_edge_val0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+78,0,"o_edge_val1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+79,0,"o_edge_val2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("o_edge_delta0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+80+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_edge_delta1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+82+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_edge_delta2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+84+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_attr0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+86+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_attr_dx", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+90+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("o_attr_dy", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+94+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBit(c+98,0,"o_dv",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+99,0,"i_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+100,0,"culled_triangle",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+101,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+280,0,"SCREEN_WIDTH_FP",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+280,0,"SCREEN_HEIGHT_FP",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("r_v0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+102+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_v1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+105+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_v2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+108+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_attr_v0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+111+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_attr_v1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+115+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_attr_v2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+119+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_attr0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+123+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_attr_dx", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+127+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_attr_dy", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+131+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("w_attr", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declQuad(c+135+i*2,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 63,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("w_attr_dx", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declQuad(c+143+i*2,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 63,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("w_attr_dy", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declQuad(c+151+i*2,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 63,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+159,0,"r_edge_val0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+160,0,"r_edge_val1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+161,0,"r_edge_val2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("r_edge_delta0", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+162+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_edge_delta1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+164+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_edge_delta2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+166+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declQuad(c+168,0,"r_area",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 39,0);
    tracep->pushPrefix("r_edge_function_v1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+170+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_edge_function_v2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+172+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_edge_function_p", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+174+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declQuad(c+176,0,"w_edge_function_val",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("w_edge_function_delta", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+178+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+281,0,"TILE_MIN_X",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+281,0,"TILE_MIN_Y",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+282,0,"TILE_MAX_X",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+282,0,"TILE_MAX_Y",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("w_bb_tl", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+180+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("w_bb_br", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+182+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBit(c+184,0,"w_bb_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("r_bb_tl", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+185+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_bb_br", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+187+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declBit(c+189,0,"r_bb_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+190,0,"i_min_x",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+191,0,"i_max_x",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+192,0,"i_min_y",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+193,0,"i_max_y",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+194,0,"w_area_division_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+195,0,"r_area_division_in_A",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+196,0,"r_area_division_in_A_dv",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+197,0,"w_area_reciprocal",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+198,0,"w_area_reciprocal_dv",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+199,0,"r_area_reciprocal",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("w_bw_mul", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declQuad(c+200+i*2,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 63,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("w_bw_delta_mul", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declQuad(c+206,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+208,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declQuad(c+210,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+212,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declQuad(c+214,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+216,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("r_barycentric_weight", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+218+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("r_barycentric_weight_delta", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+221,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+222,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+223,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+224,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+225,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+226,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->declBit(c+227,0,"w_should_be_culled",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+228,0,"current_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+229,0,"next_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->pushPrefix("edge_compute_inst", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+283,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("v1", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+230+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("v2", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+232+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("p", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+234+i*1,0,"",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->declQuad(c+236,0,"edge_function",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("edge_delta", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+238+i*1,0,"",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("fast_inverse_inst", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+283,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+284,0,"NUM_ITERATIONS",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+240,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+241,0,"rstn",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+242,0,"ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+243,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+244,0,"A_dv",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+245,0,"A_inv",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+246,0,"A_inv_dv",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+285,0,"MAX_SHIFT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+247,0,"iter",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declQuad(c+248,0,"r_A",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+250,0,"r_A_scaled",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+252,0,"X",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+254,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->declBus(c+255,0,"w_shift_amt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+256,0,"r_shift_amt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declQuad(c+257,0,"two_fp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+259,0,"AX",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+261,0,"two_fp_minus_AX",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declArray(c+263,0,"X_two_AX",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 64,0);
    tracep->declArray(c+266,0,"w_X_next",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 64,0);
    tracep->declQuad(c+269,0,"w_A_inv",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+271,0,"current_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+272,0,"next_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vtop___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vtop___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_const_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_const_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+273,(1U),32);
    bufp->fullIData(oldp+274,(0x10U),32);
    bufp->fullIData(oldp+275,(0x20U),32);
    bufp->fullIData(oldp+276,(0x18U),32);
    bufp->fullIData(oldp+277,(0x28U),32);
    bufp->fullIData(oldp+278,(4U),32);
    bufp->fullIData(oldp+279,(0x40U),32);
    bufp->fullIData(oldp+280,(0x400000U),32);
    bufp->fullIData(oldp+281,(0U),32);
    bufp->fullIData(oldp+282,(0x400000U),32);
    bufp->fullIData(oldp+283,(0x20U),32);
    bufp->fullIData(oldp+284,(8U),32);
    bufp->fullIData(oldp+285,(6U),32);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelfRef.clk));
    bufp->fullBit(oldp+2,(vlSelfRef.rstn));
    bufp->fullIData(oldp+3,(vlSelfRef.i_v0[0]),32);
    bufp->fullIData(oldp+4,(vlSelfRef.i_v0[1]),32);
    bufp->fullIData(oldp+5,(vlSelfRef.i_v0[2]),32);
    bufp->fullIData(oldp+6,(vlSelfRef.i_v1[0]),32);
    bufp->fullIData(oldp+7,(vlSelfRef.i_v1[1]),32);
    bufp->fullIData(oldp+8,(vlSelfRef.i_v1[2]),32);
    bufp->fullIData(oldp+9,(vlSelfRef.i_v2[0]),32);
    bufp->fullIData(oldp+10,(vlSelfRef.i_v2[1]),32);
    bufp->fullIData(oldp+11,(vlSelfRef.i_v2[2]),32);
    bufp->fullIData(oldp+12,(vlSelfRef.i_attr_v0[0]),32);
    bufp->fullIData(oldp+13,(vlSelfRef.i_attr_v0[1]),32);
    bufp->fullIData(oldp+14,(vlSelfRef.i_attr_v0[2]),32);
    bufp->fullIData(oldp+15,(vlSelfRef.i_attr_v1[0]),32);
    bufp->fullIData(oldp+16,(vlSelfRef.i_attr_v1[1]),32);
    bufp->fullIData(oldp+17,(vlSelfRef.i_attr_v1[2]),32);
    bufp->fullIData(oldp+18,(vlSelfRef.i_attr_v2[0]),32);
    bufp->fullIData(oldp+19,(vlSelfRef.i_attr_v2[1]),32);
    bufp->fullIData(oldp+20,(vlSelfRef.i_attr_v2[2]),32);
    bufp->fullBit(oldp+21,(vlSelfRef.i_dv));
    bufp->fullBit(oldp+22,(vlSelfRef.o_ready));
    bufp->fullIData(oldp+23,(vlSelfRef.o_bb_tl[0]),32);
    bufp->fullIData(oldp+24,(vlSelfRef.o_bb_tl[1]),32);
    bufp->fullIData(oldp+25,(vlSelfRef.o_bb_br[0]),32);
    bufp->fullIData(oldp+26,(vlSelfRef.o_bb_br[1]),32);
    bufp->fullIData(oldp+27,(vlSelfRef.o_edge_val0),32);
    bufp->fullIData(oldp+28,(vlSelfRef.o_edge_val1),32);
    bufp->fullIData(oldp+29,(vlSelfRef.o_edge_val2),32);
    bufp->fullIData(oldp+30,(vlSelfRef.o_edge_delta0[0]),32);
    bufp->fullIData(oldp+31,(vlSelfRef.o_edge_delta0[1]),32);
    bufp->fullIData(oldp+32,(vlSelfRef.o_edge_delta1[0]),32);
    bufp->fullIData(oldp+33,(vlSelfRef.o_edge_delta1[1]),32);
    bufp->fullIData(oldp+34,(vlSelfRef.o_edge_delta2[0]),32);
    bufp->fullIData(oldp+35,(vlSelfRef.o_edge_delta2[1]),32);
    bufp->fullIData(oldp+36,(vlSelfRef.o_attr0[0]),32);
    bufp->fullIData(oldp+37,(vlSelfRef.o_attr0[1]),32);
    bufp->fullIData(oldp+38,(vlSelfRef.o_attr0[2]),32);
    bufp->fullIData(oldp+39,(vlSelfRef.o_attr0[3]),32);
    bufp->fullIData(oldp+40,(vlSelfRef.o_attr_dx[0]),32);
    bufp->fullIData(oldp+41,(vlSelfRef.o_attr_dx[1]),32);
    bufp->fullIData(oldp+42,(vlSelfRef.o_attr_dx[2]),32);
    bufp->fullIData(oldp+43,(vlSelfRef.o_attr_dx[3]),32);
    bufp->fullIData(oldp+44,(vlSelfRef.o_attr_dy[0]),32);
    bufp->fullIData(oldp+45,(vlSelfRef.o_attr_dy[1]),32);
    bufp->fullIData(oldp+46,(vlSelfRef.o_attr_dy[2]),32);
    bufp->fullIData(oldp+47,(vlSelfRef.o_attr_dy[3]),32);
    bufp->fullBit(oldp+48,(vlSelfRef.o_dv));
    bufp->fullBit(oldp+49,(vlSelfRef.i_ready));
    bufp->fullBit(oldp+50,(vlSelfRef.culled_triangle));
    bufp->fullBit(oldp+51,(vlSelfRef.rasterizer_frontend__DOT__clk));
    bufp->fullBit(oldp+52,(vlSelfRef.rasterizer_frontend__DOT__rstn));
    bufp->fullIData(oldp+53,(vlSelfRef.rasterizer_frontend__DOT__i_v0[0]),32);
    bufp->fullIData(oldp+54,(vlSelfRef.rasterizer_frontend__DOT__i_v0[1]),32);
    bufp->fullIData(oldp+55,(vlSelfRef.rasterizer_frontend__DOT__i_v0[2]),32);
    bufp->fullIData(oldp+56,(vlSelfRef.rasterizer_frontend__DOT__i_v1[0]),32);
    bufp->fullIData(oldp+57,(vlSelfRef.rasterizer_frontend__DOT__i_v1[1]),32);
    bufp->fullIData(oldp+58,(vlSelfRef.rasterizer_frontend__DOT__i_v1[2]),32);
    bufp->fullIData(oldp+59,(vlSelfRef.rasterizer_frontend__DOT__i_v2[0]),32);
    bufp->fullIData(oldp+60,(vlSelfRef.rasterizer_frontend__DOT__i_v2[1]),32);
    bufp->fullIData(oldp+61,(vlSelfRef.rasterizer_frontend__DOT__i_v2[2]),32);
    bufp->fullIData(oldp+62,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v0[0]),32);
    bufp->fullIData(oldp+63,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v0[1]),32);
    bufp->fullIData(oldp+64,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v0[2]),32);
    bufp->fullIData(oldp+65,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v1[0]),32);
    bufp->fullIData(oldp+66,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v1[1]),32);
    bufp->fullIData(oldp+67,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v1[2]),32);
    bufp->fullIData(oldp+68,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v2[0]),32);
    bufp->fullIData(oldp+69,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v2[1]),32);
    bufp->fullIData(oldp+70,(vlSelfRef.rasterizer_frontend__DOT__i_attr_v2[2]),32);
    bufp->fullBit(oldp+71,(vlSelfRef.rasterizer_frontend__DOT__i_dv));
    bufp->fullBit(oldp+72,(vlSelfRef.rasterizer_frontend__DOT__o_ready));
    bufp->fullIData(oldp+73,(vlSelfRef.rasterizer_frontend__DOT__o_bb_tl[0]),32);
    bufp->fullIData(oldp+74,(vlSelfRef.rasterizer_frontend__DOT__o_bb_tl[1]),32);
    bufp->fullIData(oldp+75,(vlSelfRef.rasterizer_frontend__DOT__o_bb_br[0]),32);
    bufp->fullIData(oldp+76,(vlSelfRef.rasterizer_frontend__DOT__o_bb_br[1]),32);
    bufp->fullIData(oldp+77,(vlSelfRef.rasterizer_frontend__DOT__o_edge_val0),32);
    bufp->fullIData(oldp+78,(vlSelfRef.rasterizer_frontend__DOT__o_edge_val1),32);
    bufp->fullIData(oldp+79,(vlSelfRef.rasterizer_frontend__DOT__o_edge_val2),32);
    bufp->fullIData(oldp+80,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0[0]),32);
    bufp->fullIData(oldp+81,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta0[1]),32);
    bufp->fullIData(oldp+82,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1[0]),32);
    bufp->fullIData(oldp+83,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta1[1]),32);
    bufp->fullIData(oldp+84,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2[0]),32);
    bufp->fullIData(oldp+85,(vlSelfRef.rasterizer_frontend__DOT__o_edge_delta2[1]),32);
    bufp->fullIData(oldp+86,(vlSelfRef.rasterizer_frontend__DOT__o_attr0[0]),32);
    bufp->fullIData(oldp+87,(vlSelfRef.rasterizer_frontend__DOT__o_attr0[1]),32);
    bufp->fullIData(oldp+88,(vlSelfRef.rasterizer_frontend__DOT__o_attr0[2]),32);
    bufp->fullIData(oldp+89,(vlSelfRef.rasterizer_frontend__DOT__o_attr0[3]),32);
    bufp->fullIData(oldp+90,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[0]),32);
    bufp->fullIData(oldp+91,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[1]),32);
    bufp->fullIData(oldp+92,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[2]),32);
    bufp->fullIData(oldp+93,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dx[3]),32);
    bufp->fullIData(oldp+94,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[0]),32);
    bufp->fullIData(oldp+95,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[1]),32);
    bufp->fullIData(oldp+96,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[2]),32);
    bufp->fullIData(oldp+97,(vlSelfRef.rasterizer_frontend__DOT__o_attr_dy[3]),32);
    bufp->fullBit(oldp+98,(vlSelfRef.rasterizer_frontend__DOT__o_dv));
    bufp->fullBit(oldp+99,(vlSelfRef.rasterizer_frontend__DOT__i_ready));
    bufp->fullBit(oldp+100,(vlSelfRef.rasterizer_frontend__DOT__culled_triangle));
    bufp->fullIData(oldp+101,(vlSelfRef.rasterizer_frontend__DOT__i),32);
    bufp->fullIData(oldp+102,(vlSelfRef.rasterizer_frontend__DOT__r_v0[0]),32);
    bufp->fullIData(oldp+103,(vlSelfRef.rasterizer_frontend__DOT__r_v0[1]),32);
    bufp->fullIData(oldp+104,(vlSelfRef.rasterizer_frontend__DOT__r_v0[2]),32);
    bufp->fullIData(oldp+105,(vlSelfRef.rasterizer_frontend__DOT__r_v1[0]),32);
    bufp->fullIData(oldp+106,(vlSelfRef.rasterizer_frontend__DOT__r_v1[1]),32);
    bufp->fullIData(oldp+107,(vlSelfRef.rasterizer_frontend__DOT__r_v1[2]),32);
    bufp->fullIData(oldp+108,(vlSelfRef.rasterizer_frontend__DOT__r_v2[0]),32);
    bufp->fullIData(oldp+109,(vlSelfRef.rasterizer_frontend__DOT__r_v2[1]),32);
    bufp->fullIData(oldp+110,(vlSelfRef.rasterizer_frontend__DOT__r_v2[2]),32);
    bufp->fullIData(oldp+111,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[0]),32);
    bufp->fullIData(oldp+112,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[1]),32);
    bufp->fullIData(oldp+113,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[2]),32);
    bufp->fullIData(oldp+114,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v0[3]),32);
    bufp->fullIData(oldp+115,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[0]),32);
    bufp->fullIData(oldp+116,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[1]),32);
    bufp->fullIData(oldp+117,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[2]),32);
    bufp->fullIData(oldp+118,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v1[3]),32);
    bufp->fullIData(oldp+119,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[0]),32);
    bufp->fullIData(oldp+120,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[1]),32);
    bufp->fullIData(oldp+121,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[2]),32);
    bufp->fullIData(oldp+122,(vlSelfRef.rasterizer_frontend__DOT__r_attr_v2[3]),32);
    bufp->fullIData(oldp+123,(vlSelfRef.rasterizer_frontend__DOT__r_attr0[0]),32);
    bufp->fullIData(oldp+124,(vlSelfRef.rasterizer_frontend__DOT__r_attr0[1]),32);
    bufp->fullIData(oldp+125,(vlSelfRef.rasterizer_frontend__DOT__r_attr0[2]),32);
    bufp->fullIData(oldp+126,(vlSelfRef.rasterizer_frontend__DOT__r_attr0[3]),32);
    bufp->fullIData(oldp+127,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[0]),32);
    bufp->fullIData(oldp+128,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[1]),32);
    bufp->fullIData(oldp+129,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[2]),32);
    bufp->fullIData(oldp+130,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dx[3]),32);
    bufp->fullIData(oldp+131,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[0]),32);
    bufp->fullIData(oldp+132,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[1]),32);
    bufp->fullIData(oldp+133,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[2]),32);
    bufp->fullIData(oldp+134,(vlSelfRef.rasterizer_frontend__DOT__r_attr_dy[3]),32);
    bufp->fullQData(oldp+135,(vlSelfRef.rasterizer_frontend__DOT__w_attr[0]),64);
    bufp->fullQData(oldp+137,(vlSelfRef.rasterizer_frontend__DOT__w_attr[1]),64);
    bufp->fullQData(oldp+139,(vlSelfRef.rasterizer_frontend__DOT__w_attr[2]),64);
    bufp->fullQData(oldp+141,(vlSelfRef.rasterizer_frontend__DOT__w_attr[3]),64);
    bufp->fullQData(oldp+143,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[0]),64);
    bufp->fullQData(oldp+145,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[1]),64);
    bufp->fullQData(oldp+147,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[2]),64);
    bufp->fullQData(oldp+149,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dx[3]),64);
    bufp->fullQData(oldp+151,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[0]),64);
    bufp->fullQData(oldp+153,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[1]),64);
    bufp->fullQData(oldp+155,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[2]),64);
    bufp->fullQData(oldp+157,(vlSelfRef.rasterizer_frontend__DOT__w_attr_dy[3]),64);
    bufp->fullIData(oldp+159,(vlSelfRef.rasterizer_frontend__DOT__r_edge_val0),32);
    bufp->fullIData(oldp+160,(vlSelfRef.rasterizer_frontend__DOT__r_edge_val1),32);
    bufp->fullIData(oldp+161,(vlSelfRef.rasterizer_frontend__DOT__r_edge_val2),32);
    bufp->fullIData(oldp+162,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[0]),32);
    bufp->fullIData(oldp+163,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta0[1]),32);
    bufp->fullIData(oldp+164,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[0]),32);
    bufp->fullIData(oldp+165,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta1[1]),32);
    bufp->fullIData(oldp+166,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[0]),32);
    bufp->fullIData(oldp+167,(vlSelfRef.rasterizer_frontend__DOT__r_edge_delta2[1]),32);
    bufp->fullQData(oldp+168,(vlSelfRef.rasterizer_frontend__DOT__r_area),40);
    bufp->fullIData(oldp+170,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[0]),32);
    bufp->fullIData(oldp+171,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v1[1]),32);
    bufp->fullIData(oldp+172,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[0]),32);
    bufp->fullIData(oldp+173,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_v2[1]),32);
    bufp->fullIData(oldp+174,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[0]),32);
    bufp->fullIData(oldp+175,(vlSelfRef.rasterizer_frontend__DOT__r_edge_function_p[1]),32);
    bufp->fullQData(oldp+176,(vlSelfRef.rasterizer_frontend__DOT__w_edge_function_val),64);
    bufp->fullIData(oldp+178,(vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta[0]),32);
    bufp->fullIData(oldp+179,(vlSelfRef.rasterizer_frontend__DOT__w_edge_function_delta[1]),32);
    bufp->fullIData(oldp+180,(vlSelfRef.rasterizer_frontend__DOT__w_bb_tl[0]),32);
    bufp->fullIData(oldp+181,(vlSelfRef.rasterizer_frontend__DOT__w_bb_tl[1]),32);
    bufp->fullIData(oldp+182,(vlSelfRef.rasterizer_frontend__DOT__w_bb_br[0]),32);
    bufp->fullIData(oldp+183,(vlSelfRef.rasterizer_frontend__DOT__w_bb_br[1]),32);
    bufp->fullBit(oldp+184,(vlSelfRef.rasterizer_frontend__DOT__w_bb_valid));
    bufp->fullIData(oldp+185,(vlSelfRef.rasterizer_frontend__DOT__r_bb_tl[0]),32);
    bufp->fullIData(oldp+186,(vlSelfRef.rasterizer_frontend__DOT__r_bb_tl[1]),32);
    bufp->fullIData(oldp+187,(vlSelfRef.rasterizer_frontend__DOT__r_bb_br[0]),32);
    bufp->fullIData(oldp+188,(vlSelfRef.rasterizer_frontend__DOT__r_bb_br[1]),32);
    bufp->fullBit(oldp+189,(vlSelfRef.rasterizer_frontend__DOT__r_bb_valid));
    bufp->fullIData(oldp+190,(vlSelfRef.rasterizer_frontend__DOT__i_min_x),32);
    bufp->fullIData(oldp+191,(vlSelfRef.rasterizer_frontend__DOT__i_max_x),32);
    bufp->fullIData(oldp+192,(vlSelfRef.rasterizer_frontend__DOT__i_min_y),32);
    bufp->fullIData(oldp+193,(vlSelfRef.rasterizer_frontend__DOT__i_max_y),32);
    bufp->fullBit(oldp+194,(vlSelfRef.rasterizer_frontend__DOT__w_area_division_ready));
    bufp->fullIData(oldp+195,(vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A),32);
    bufp->fullBit(oldp+196,(vlSelfRef.rasterizer_frontend__DOT__r_area_division_in_A_dv));
    bufp->fullIData(oldp+197,(vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal),32);
    bufp->fullBit(oldp+198,(vlSelfRef.rasterizer_frontend__DOT__w_area_reciprocal_dv));
    bufp->fullIData(oldp+199,(vlSelfRef.rasterizer_frontend__DOT__r_area_reciprocal),32);
    bufp->fullQData(oldp+200,(vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[0]),64);
    bufp->fullQData(oldp+202,(vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[1]),64);
    bufp->fullQData(oldp+204,(vlSelfRef.rasterizer_frontend__DOT__w_bw_mul[2]),64);
    bufp->fullQData(oldp+206,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                              [0U][0U]),64);
    bufp->fullQData(oldp+208,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                              [0U][1U]),64);
    bufp->fullQData(oldp+210,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                              [1U][0U]),64);
    bufp->fullQData(oldp+212,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                              [1U][1U]),64);
    bufp->fullQData(oldp+214,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                              [2U][0U]),64);
    bufp->fullQData(oldp+216,(vlSelfRef.rasterizer_frontend__DOT__w_bw_delta_mul
                              [2U][1U]),64);
    bufp->fullIData(oldp+218,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[0]),32);
    bufp->fullIData(oldp+219,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[1]),32);
    bufp->fullIData(oldp+220,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight[2]),32);
    bufp->fullIData(oldp+221,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                              [0U][0U]),32);
    bufp->fullIData(oldp+222,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                              [0U][1U]),32);
    bufp->fullIData(oldp+223,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                              [1U][0U]),32);
    bufp->fullIData(oldp+224,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                              [1U][1U]),32);
    bufp->fullIData(oldp+225,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                              [2U][0U]),32);
    bufp->fullIData(oldp+226,(vlSelfRef.rasterizer_frontend__DOT__r_barycentric_weight_delta
                              [2U][1U]),32);
    bufp->fullBit(oldp+227,(vlSelfRef.rasterizer_frontend__DOT__w_should_be_culled));
    bufp->fullCData(oldp+228,(vlSelfRef.rasterizer_frontend__DOT__current_state),4);
    bufp->fullCData(oldp+229,(vlSelfRef.rasterizer_frontend__DOT__next_state),4);
    bufp->fullIData(oldp+230,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1[0]),32);
    bufp->fullIData(oldp+231,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1[1]),32);
    bufp->fullIData(oldp+232,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2[0]),32);
    bufp->fullIData(oldp+233,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2[1]),32);
    bufp->fullIData(oldp+234,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__p[0]),32);
    bufp->fullIData(oldp+235,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__p[1]),32);
    bufp->fullQData(oldp+236,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_function),64);
    bufp->fullIData(oldp+238,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta[0]),32);
    bufp->fullIData(oldp+239,(vlSelfRef.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta[1]),32);
    bufp->fullBit(oldp+240,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk));
    bufp->fullBit(oldp+241,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn));
    bufp->fullBit(oldp+242,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__ready));
    bufp->fullIData(oldp+243,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A),32);
    bufp->fullBit(oldp+244,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv));
    bufp->fullIData(oldp+245,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv),32);
    bufp->fullBit(oldp+246,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv));
    bufp->fullCData(oldp+247,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter),4);
    bufp->fullQData(oldp+248,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A),64);
    bufp->fullQData(oldp+250,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A_scaled),64);
    bufp->fullQData(oldp+252,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X),64);
    bufp->fullIData(oldp+254,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i),32);
    bufp->fullCData(oldp+255,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt),6);
    bufp->fullCData(oldp+256,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt),6);
    bufp->fullQData(oldp+257,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp),64);
    bufp->fullQData(oldp+259,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__AX),64);
    bufp->fullQData(oldp+261,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp_minus_AX),64);
    bufp->fullWData(oldp+263,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X_two_AX),65);
    bufp->fullWData(oldp+266,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next),65);
    bufp->fullQData(oldp+269,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_A_inv),64);
    bufp->fullCData(oldp+271,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state),2);
    bufp->fullCData(oldp+272,(vlSelfRef.rasterizer_frontend__DOT__fast_inverse_inst__DOT__next_state),2);
}
