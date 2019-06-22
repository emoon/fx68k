// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vfx68k__Syms_H_
#define _Vfx68k__Syms_H_

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vfx68k.h"
#include "Vfx68k___024unit.h"

// SYMS CLASS
class Vfx68k__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vfx68k*                        TOPp;
    
    // CREATORS
    Vfx68k__Syms(Vfx68k* topp, const char* namep);
    ~Vfx68k__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(64);

#endif // guard
