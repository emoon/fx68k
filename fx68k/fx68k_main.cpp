#include "Vfx68k.h"
#include "verilated.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static const char s_phi1_values[] = { 0, 0, 0, 0, 0, 1, 1, 0 };
static const char s_phi2_values[] = { 0, 1, 1, 0, 0, 0, 0, 0 };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Needs to match the Rust side

struct CpuState {
    uint32_t d_registers[8];
    uint32_t a_registers[8];
    uint32_t pc;
    uint32_t flags;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Fx68kState {
    Vfx68k* top;
    void* memory_interface;
    int cycle;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" void* fx68k_ver_new_instance(void* memory_interface) {
    Fx68kState* state = new Fx68kState;
    Vfx68k* top = new Vfx68k;

    state->memory_interface = memory_interface;
    state->top = top;
    state->cycle = 1;

    // reset the CPU
	top->pwrUp = 1;
	top->extReset = 1;

    for (int i = 0; i < 10; ++i) {
        int clk = state->cycle & 1;
        int pih1 = s_phi1_values[state->cycle & 7];
        int pih2 = s_phi2_values[state->cycle & 7];

        top->enPhi1 = pih1;
        top->enPhi2 = pih2;
        top->clk = clk;
        top->eval();

        state->cycle++;
    }

    // done with power up, assert the pins
	top->pwrUp = 0;
	top->extReset = 0;

    top->iEdb = 0x0000;
	top->VPAn = 1;
	top->BERRn = 1;
	top->BRn = 1;
	top->BGACKn = 1;
	top->IPL0n = 1;
	top->IPL1n = 1;
	top->IPL2n = 1;
	top->VPAn = 1;
	top->BGACKn = 1;
	top->DTACKn = 1;

    return (void*)state;
}

extern "C" {
    uint8_t fx68k_mem_read_u8(void* context, uint32_t cycle, uint32_t address);
    uint16_t fx68k_mem_read_u16(void* context, uint32_t cycle, uint32_t address);
    void fx68k_mem_write_u8(void* context, uint32_t cycle, uint32_t address, uint8_t value);
    void fx68k_mem_write_u16(void* context, uint32_t cycle, uint32_t address, uint16_t value);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" void fx68k_ver_step_cycle(void* instance) {
    Fx68kState* state = (Fx68kState*)instance;
    Vfx68k* top = state->top;

    int clk = state->cycle & 1;
    int pih1 = s_phi1_values[state->cycle & 7];
    int pih2 = s_phi2_values[state->cycle & 7];

    top->clk = clk;
    top->enPhi1 = pih1;
    top->enPhi2 = pih2;

    top->eval();

    if (top->ASn == 0 && top->DTACKn == 1 && pih1 == 1) {
        uint32_t address = top->eab * 2;

        if (top->eRWn) {
            if (top->LDSn) {
                uint16_t v0 = fx68k_mem_read_u8(state->memory_interface, state->cycle, address);
                top->iEdb = (v0 << 8);
            }
            else if (top->UDSn) {
                uint16_t v0 = fx68k_mem_read_u8(state->memory_interface, state->cycle, address + 1);
                top->iEdb = v0;
            }
            else {
                top->iEdb = fx68k_mem_read_u16(state->memory_interface, state->cycle, address);
            }

            top->DTACKn = 0;
        } else if (top->LDSn == 0 || top->UDSn == 0) {
            if (top->LDSn) {
                fx68k_mem_write_u8(state->memory_interface, state->cycle, address, top->oEdb >> 8);
            }
            else if (top->UDSn) {
                fx68k_mem_write_u8(state->memory_interface, state->cycle, address + 1, top->oEdb & 0xff);
            } else {
                fx68k_mem_write_u16(state->memory_interface, state->cycle, address, top->oEdb);
            }
            top->DTACKn = 0;
        }
    }

    if (top->ASn == 1)
    {
        top->iEdb = 0x0000;
        top->DTACKn = 1;
    }

    state->cycle++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" CpuState fx68k_ver_cpu_state(void* instance) {
    Fx68kState* inst = (Fx68kState*)instance;
    Vfx68k* top = inst->top;

    CpuState state;

    for (int i = 0; i < 8; ++i) {
        uint32_t dreg = (uint32_t(top->fx68k__DOT__excUnit__DOT__regs68H[i + 0]) << 16) | top->fx68k__DOT__excUnit__DOT__regs68L[i + 0];
        uint32_t areg = (uint32_t(top->fx68k__DOT__excUnit__DOT__regs68H[i + 8]) << 16) | top->fx68k__DOT__excUnit__DOT__regs68L[i + 8];
        state.d_registers[i] = dreg;
        state.a_registers[i] = areg;
    }

    state.pc = (uint32_t(top->fx68k__DOT__excUnit__DOT__PcH) << 16) | top->fx68k__DOT__excUnit__DOT__PcL;
    state.flags = top->fx68k__DOT__excUnit__DOT__alu__DOT__ccrCore;

    return state;
}

