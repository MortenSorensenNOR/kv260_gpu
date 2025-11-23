// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"
#include "Vtop.h"
#include "Vtop___024root.h"

// FUNCTIONS
Vtop__Syms::~Vtop__Syms()
{

    // Tear down scope hierarchy
    __Vhier.remove(0, &__Vscope_rasterizer_frontend);
    __Vhier.remove(&__Vscope_rasterizer_frontend, &__Vscope_rasterizer_frontend__edge_compute_inst);
    __Vhier.remove(&__Vscope_rasterizer_frontend, &__Vscope_rasterizer_frontend__fast_inverse_inst);

}

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(1241);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_TOP.configure(this, name(), "TOP", "TOP", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_rasterizer_frontend.configure(this, name(), "rasterizer_frontend", "rasterizer_frontend", "rasterizer_frontend", -9, VerilatedScope::SCOPE_MODULE);
    __Vscope_rasterizer_frontend__edge_compute_inst.configure(this, name(), "rasterizer_frontend.edge_compute_inst", "edge_compute_inst", "edge_compute", -9, VerilatedScope::SCOPE_MODULE);
    __Vscope_rasterizer_frontend__fast_inverse_inst.configure(this, name(), "rasterizer_frontend.fast_inverse_inst", "fast_inverse_inst", "fast_inverse", -9, VerilatedScope::SCOPE_MODULE);

    // Set up scope hierarchy
    __Vhier.add(0, &__Vscope_rasterizer_frontend);
    __Vhier.add(&__Vscope_rasterizer_frontend, &__Vscope_rasterizer_frontend__edge_compute_inst);
    __Vhier.add(&__Vscope_rasterizer_frontend, &__Vscope_rasterizer_frontend__fast_inverse_inst);

    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_TOP.varInsert(__Vfinal,"clk", &(TOP.clk), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"culled_triangle", &(TOP.culled_triangle), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_attr_v0", &(TOP.i_attr_v0), false, VLVT_UINT32,VLVD_IN|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_attr_v1", &(TOP.i_attr_v1), false, VLVT_UINT32,VLVD_IN|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_attr_v2", &(TOP.i_attr_v2), false, VLVT_UINT32,VLVD_IN|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_dv", &(TOP.i_dv), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_ready", &(TOP.i_ready), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_v0", &(TOP.i_v0), false, VLVT_UINT32,VLVD_IN|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_v1", &(TOP.i_v1), false, VLVT_UINT32,VLVD_IN|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_v2", &(TOP.i_v2), false, VLVT_UINT32,VLVD_IN|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_attr0", &(TOP.o_attr0), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_attr_dx", &(TOP.o_attr_dx), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_attr_dy", &(TOP.o_attr_dy), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_bb_br", &(TOP.o_bb_br), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_bb_tl", &(TOP.o_bb_tl), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_dv", &(TOP.o_dv), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_edge_delta0", &(TOP.o_edge_delta0), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_edge_delta1", &(TOP.o_edge_delta1), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_edge_delta2", &(TOP.o_edge_delta2), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_edge_val0", &(TOP.o_edge_val0), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_edge_val1", &(TOP.o_edge_val1), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_edge_val2", &(TOP.o_edge_val2), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_ready", &(TOP.o_ready), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"rstn", &(TOP.rstn), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"AREA_INT_BITS", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__AREA_INT_BITS))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"AREA_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__AREA_WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"DATA_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__DATA_WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"FRAC_BITS", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__FRAC_BITS))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"INT_BITS", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__INT_BITS))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"N_ATTR", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__N_ATTR))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"SCREEN_HEIGHT", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__SCREEN_HEIGHT))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"SCREEN_HEIGHT_FP", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__SCREEN_HEIGHT_FP))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"SCREEN_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__SCREEN_WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"SCREEN_WIDTH_FP", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__SCREEN_WIDTH_FP))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"SIGNED", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__SIGNED))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"TILE_MAX_X", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__TILE_MAX_X))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"TILE_MAX_Y", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__TILE_MAX_Y))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"TILE_MIN_X", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__TILE_MIN_X))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"TILE_MIN_Y", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__TILE_MIN_Y))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"clk", &(TOP.rasterizer_frontend__DOT__clk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"culled_triangle", &(TOP.rasterizer_frontend__DOT__culled_triangle), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"current_state", &(TOP.rasterizer_frontend__DOT__current_state), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,3,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i", &(TOP.rasterizer_frontend__DOT__i), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_attr_v0", &(TOP.rasterizer_frontend__DOT__i_attr_v0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_attr_v1", &(TOP.rasterizer_frontend__DOT__i_attr_v1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_attr_v2", &(TOP.rasterizer_frontend__DOT__i_attr_v2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_dv", &(TOP.rasterizer_frontend__DOT__i_dv), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_max_x", &(TOP.rasterizer_frontend__DOT__i_max_x), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_max_y", &(TOP.rasterizer_frontend__DOT__i_max_y), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_min_x", &(TOP.rasterizer_frontend__DOT__i_min_x), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_min_y", &(TOP.rasterizer_frontend__DOT__i_min_y), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_ready", &(TOP.rasterizer_frontend__DOT__i_ready), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_v0", &(TOP.rasterizer_frontend__DOT__i_v0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_v1", &(TOP.rasterizer_frontend__DOT__i_v1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"i_v2", &(TOP.rasterizer_frontend__DOT__i_v2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"next_state", &(TOP.rasterizer_frontend__DOT__next_state), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,3,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_attr0", &(TOP.rasterizer_frontend__DOT__o_attr0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_attr_dx", &(TOP.rasterizer_frontend__DOT__o_attr_dx), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_attr_dy", &(TOP.rasterizer_frontend__DOT__o_attr_dy), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_bb_br", &(TOP.rasterizer_frontend__DOT__o_bb_br), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_bb_tl", &(TOP.rasterizer_frontend__DOT__o_bb_tl), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_dv", &(TOP.rasterizer_frontend__DOT__o_dv), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_edge_delta0", &(TOP.rasterizer_frontend__DOT__o_edge_delta0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_edge_delta1", &(TOP.rasterizer_frontend__DOT__o_edge_delta1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_edge_delta2", &(TOP.rasterizer_frontend__DOT__o_edge_delta2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_edge_val0", &(TOP.rasterizer_frontend__DOT__o_edge_val0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_edge_val1", &(TOP.rasterizer_frontend__DOT__o_edge_val1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_edge_val2", &(TOP.rasterizer_frontend__DOT__o_edge_val2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"o_ready", &(TOP.rasterizer_frontend__DOT__o_ready), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_area", &(TOP.rasterizer_frontend__DOT__r_area), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,39,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_area_division_in_A", &(TOP.rasterizer_frontend__DOT__r_area_division_in_A), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_area_division_in_A_dv", &(TOP.rasterizer_frontend__DOT__r_area_division_in_A_dv), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_area_reciprocal", &(TOP.rasterizer_frontend__DOT__r_area_reciprocal), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_attr0", &(TOP.rasterizer_frontend__DOT__r_attr0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_attr_dx", &(TOP.rasterizer_frontend__DOT__r_attr_dx), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_attr_dy", &(TOP.rasterizer_frontend__DOT__r_attr_dy), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_attr_v0", &(TOP.rasterizer_frontend__DOT__r_attr_v0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_attr_v1", &(TOP.rasterizer_frontend__DOT__r_attr_v1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_attr_v2", &(TOP.rasterizer_frontend__DOT__r_attr_v2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_barycentric_weight", &(TOP.rasterizer_frontend__DOT__r_barycentric_weight), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_barycentric_weight_delta", &(TOP.rasterizer_frontend__DOT__r_barycentric_weight_delta), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,2,1 ,0,2 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_bb_br", &(TOP.rasterizer_frontend__DOT__r_bb_br), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_bb_tl", &(TOP.rasterizer_frontend__DOT__r_bb_tl), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_bb_valid", &(TOP.rasterizer_frontend__DOT__r_bb_valid), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_edge_delta0", &(TOP.rasterizer_frontend__DOT__r_edge_delta0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_edge_delta1", &(TOP.rasterizer_frontend__DOT__r_edge_delta1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_edge_delta2", &(TOP.rasterizer_frontend__DOT__r_edge_delta2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_edge_function_p", &(TOP.rasterizer_frontend__DOT__r_edge_function_p), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_edge_function_v1", &(TOP.rasterizer_frontend__DOT__r_edge_function_v1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_edge_function_v2", &(TOP.rasterizer_frontend__DOT__r_edge_function_v2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_edge_val0", &(TOP.rasterizer_frontend__DOT__r_edge_val0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_edge_val1", &(TOP.rasterizer_frontend__DOT__r_edge_val1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_edge_val2", &(TOP.rasterizer_frontend__DOT__r_edge_val2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_v0", &(TOP.rasterizer_frontend__DOT__r_v0), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_v1", &(TOP.rasterizer_frontend__DOT__r_v1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"r_v2", &(TOP.rasterizer_frontend__DOT__r_v2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"rstn", &(TOP.rasterizer_frontend__DOT__rstn), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_area_division_ready", &(TOP.rasterizer_frontend__DOT__w_area_division_ready), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_area_reciprocal", &(TOP.rasterizer_frontend__DOT__w_area_reciprocal), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_area_reciprocal_dv", &(TOP.rasterizer_frontend__DOT__w_area_reciprocal_dv), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_attr", &(TOP.rasterizer_frontend__DOT__w_attr), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,63,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_attr_dx", &(TOP.rasterizer_frontend__DOT__w_attr_dx), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,63,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_attr_dy", &(TOP.rasterizer_frontend__DOT__w_attr_dy), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,3 ,63,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_bb_br", &(TOP.rasterizer_frontend__DOT__w_bb_br), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_bb_tl", &(TOP.rasterizer_frontend__DOT__w_bb_tl), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_bb_valid", &(TOP.rasterizer_frontend__DOT__w_bb_valid), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_bw_delta_mul", &(TOP.rasterizer_frontend__DOT__w_bw_delta_mul), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,2,1 ,0,2 ,0,1 ,63,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_bw_mul", &(TOP.rasterizer_frontend__DOT__w_bw_mul), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,2 ,63,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_edge_function_delta", &(TOP.rasterizer_frontend__DOT__w_edge_function_delta), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_edge_function_val", &(TOP.rasterizer_frontend__DOT__w_edge_function_val), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_rasterizer_frontend.varInsert(__Vfinal,"w_should_be_culled", &(TOP.rasterizer_frontend__DOT__w_should_be_culled), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend__edge_compute_inst.varInsert(__Vfinal,"DATA_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__edge_compute_inst__DOT__DATA_WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend__edge_compute_inst.varInsert(__Vfinal,"edge_delta", &(TOP.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_delta), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend__edge_compute_inst.varInsert(__Vfinal,"edge_function", &(TOP.rasterizer_frontend__DOT__edge_compute_inst__DOT__edge_function), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_rasterizer_frontend__edge_compute_inst.varInsert(__Vfinal,"p", &(TOP.rasterizer_frontend__DOT__edge_compute_inst__DOT__p), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend__edge_compute_inst.varInsert(__Vfinal,"v1", &(TOP.rasterizer_frontend__DOT__edge_compute_inst__DOT__v1), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend__edge_compute_inst.varInsert(__Vfinal,"v2", &(TOP.rasterizer_frontend__DOT__edge_compute_inst__DOT__v2), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,1 ,31,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"A", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"AX", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__AX), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"A_dv", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_dv), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"A_inv", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"A_inv_dv", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__A_inv_dv), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"DATA_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__DATA_WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"MAX_SHIFT", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__MAX_SHIFT))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"NUM_ITERATIONS", const_cast<void*>(static_cast<const void*>(&(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__NUM_ITERATIONS))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"X", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"X_two_AX", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__X_two_AX), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,64,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"clk", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__clk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"current_state", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__current_state), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,1,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"i", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__i), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"iter", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__iter), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,3,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"next_state", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__next_state), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,1,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"r_A", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"r_A_scaled", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_A_scaled), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"r_shift_amt", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__r_shift_amt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,5,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"ready", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__ready), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"rstn", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__rstn), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"two_fp", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"two_fp_minus_AX", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__two_fp_minus_AX), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"w_A_inv", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_A_inv), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"w_X_next", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_X_next), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,64,0);
        __Vscope_rasterizer_frontend__fast_inverse_inst.varInsert(__Vfinal,"w_shift_amt", &(TOP.rasterizer_frontend__DOT__fast_inverse_inst__DOT__w_shift_amt), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,5,0);
    }
}
