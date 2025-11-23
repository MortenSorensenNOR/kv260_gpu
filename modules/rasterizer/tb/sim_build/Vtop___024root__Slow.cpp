// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop__Syms.h"
#include "Vtop___024root.h"

// Parameter definitions for Vtop___024root
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__SIGNED;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__INT_BITS;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__FRAC_BITS;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__AREA_INT_BITS;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__AREA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__N_ATTR;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__SCREEN_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__SCREEN_HEIGHT;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__SCREEN_WIDTH_FP;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__SCREEN_HEIGHT_FP;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__TILE_MIN_X;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__TILE_MIN_Y;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__TILE_MAX_X;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__TILE_MAX_Y;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__edge_compute_inst__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__fast_inverse_inst__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__fast_inverse_inst__DOT__NUM_ITERATIONS;
constexpr IData/*31:0*/ Vtop___024root::rasterizer_frontend__DOT__fast_inverse_inst__DOT__MAX_SHIFT;


void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf);

Vtop___024root::Vtop___024root(Vtop__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vtop___024root___ctor_var_reset(this);
}

void Vtop___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtop___024root::~Vtop___024root() {
}
