#include "Vfx68k.h"
#include "verilated.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static const char s_phi1_values[] = { 0, 0, 0, 0, 0, 1, 1, 0 };
static const char s_phi2_values[] = { 0, 1, 1, 0, 0, 0, 0, 0 };

#if 0

int main(int argc, char** argv, char** env) {
    Verilated::commandArgs(argc, argv);
    //Verilated::traceEverOn(true);
    //Verilated::debug(0);

    //VerilatedVcdC* trace = new VerilatedVcdC;
    Vfx68k* top = new Vfx68k;

    //top->trace(trace, 99);
    //trace->open("trace.vcd");

    size_t size = 0;

    uint8_t* memory = File_loadToMemory("temp.bin", &size);

    if (!memory) {
        printf("unable to load asm code\n");
        return 0;
    }


    // clk  l h l h l h l h
    // phi1 l h l l l h l l
    // phi2 l l l h l l l h

    const char phi1_values[] = { 0, 0, 0, 0, 0, 1, 1, 0 };
    const char phi2_values[] = { 0, 1, 1, 0, 0, 0, 0, 0 };

    int cycle = 1;

    // reset the CPU

	top->pwrUp = 1;
	top->extReset = 1;

    for (int i = 0; i < 10; ++i) {
        int clk = cycle & 1;
        int pih1 = phi1_values[cycle & 7];
        int pih2 = phi2_values[cycle & 7];

        top->enPhi1 = pih1;
        top->enPhi2 = pih2;
        top->clk = clk;
        top->eval();
        //trace->dump(cycle);
        //trace->flush();

        cycle++;
    }

    //

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

    // this is hack to not put data on the bus for the first time the address is zero
    //int init_done = 0;

    uint64_t start_time = get_time();

    while (1) {
        int clk = cycle & 1;
        int pih1 = phi1_values[cycle & 7];
        int pih2 = phi2_values[cycle & 7];

        top->clk = clk;
        top->enPhi1 = pih1;
        top->enPhi2 = pih2;

        top->eval();

        //trace->dump(cycle);
        //trace->flush();

        //printf("---------- INPUT --------------\n");
        //printf("clk      %08x\n", clk);
        //printf("pih1     %08x\n", pih1);
        //printf("pih2     %08x\n", pih2);

        /*
        printf("---------- OUTPUT --------------\n");
        printf("eRWn     %08x\n", top->eRWn);
        printf("ASn      %08x\n", top->ASn);
        printf("LDSn     %08x\n", top->LDSn);
        printf("UDSn     %08x\n", top->UDSn);
        printf("E        %08x\n", top->E);
        //printf("VMAn     %08x\n", top->VMAn);
        printf("FC0      %08x\n", top->FC0);
        printf("FC1      %08x\n", top->FC1);
        printf("FC2      %08x\n", top->FC2);
        //printf("BGn      %08x\n", top->BGn);
        //printf("oRESETn  %08x\n", top->oRESETn);
        //printf("oHALTEDn %08x\n", top->oHALTEDn);
        printf("eab      %08x\n", top->eab);
        printf("oEdb     %08x\n", top->oEdb);


        printf("d6 low   %08x\n", top->fx68k__DOT__excUnit__DOT__regs68L[6]);
        printf("d6 high  %08x\n", top->fx68k__DOT__excUnit__DOT__regs68H[6]);

        printf("d7 low   %08x\n", top->fx68k__DOT__excUnit__DOT__regs68L[7]);
        printf("d7 high  %08x\n", top->fx68k__DOT__excUnit__DOT__regs68H[7]);
        */

        //printf("d0 low   %08x\n", top->fx68k__DOT__excUnit__DOT__regs68L[0]);
        //printf("d0 high  %08x\n", top->fx68k__DOT__excUnit__DOT__regs68H[0]);
        //


        if (top->ASn == 0 && top->DTACKn == 1 && pih1 == 1) {
            uint32_t address = top->eab * 2;

            if (top->eRWn) {
                if (top->LDSn) {
                    uint16_t v0 = memory[address + 0];
                    top->iEdb = (v0 << 8);
                }
                else if (top->UDSn) {
                    uint16_t v0 = memory[address + 1];
                    top->iEdb = v0;
                }
                else
                {
                    // if we are trying to read outside valid memory return 0 as data for now
                    if (address + 2 >= size) {
                        top->iEdb = 0;
                    } else {
                        uint16_t v0 = memory[address + 0];
                        uint16_t v1 = memory[address + 1];
                        top->iEdb = (v0 << 8) | v1;
                    }
                }

                top->DTACKn = 0;
            } else if (top->LDSn == 0 || top->UDSn == 0) {
                if (top->LDSn) {
                    memory[address + 0] = top->oEdb >> 8;
                }
                else if (top->UDSn) {
                    memory[address + 1] = top->oEdb & 0xff;
                } else {
                    memory[address + 0] = top->oEdb >> 8;
                    memory[address + 1] = top->oEdb & 0xff;
                }
                top->DTACKn = 0;
            }
        }

        if (top->ASn == 1)
        {
            top->iEdb = 0x0000;
            top->DTACKn = 1;
        }

        uint16_t pc_low = top->fx68k__DOT__excUnit__DOT__PcL;

        printf("pc %08x\n", pc_low);

        if (pc_low == 34) {
            break;
        }

        cycle++;
    }

    uint64_t end_time = get_time();

    printf("%llx %llx\n", start_time, end_time);

    double total_time = end_time - start_time;

    printf("time ms (cycle count %d) %f\n", total_time / 1000.0, cycle);

    uint16_t pc_low = top->fx68k__DOT__excUnit__DOT__PcL;

    //printf("PC %08d\n", pc_low);
    //printf("written data %d\n", memory[512]);
    //printf("written data %d\n", memory[513]);
    //printf("written data %d\n", memory[514]);
    //printf("written data %d\n", memory[515]);

    return 0;
}

#endif

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
                //memory[address + 0] = top->oEdb >> 8;
            }
            else if (top->UDSn) {
                fx68k_mem_write_u8(state->memory_interface, state->cycle, address + 1, top->oEdb & 0xff);
                //memory[address + 1] = top->oEdb & 0xff;
            } else {
                fx68k_mem_write_u16(state->memory_interface, state->cycle, address, top->oEdb);
                //memory[address + 0] = top->oEdb >> 8;
                //memory[address + 1] = top->oEdb & 0xff;
            }
            top->DTACKn = 0;
        }
    }

    if (top->ASn == 1)
    {
        top->DTACKn = 1;
    }

    /*
    uint16_t pc_low = top->fx68k__DOT__excUnit__DOT__PcL;

    printf("pc %08x\n", pc_low);

    if (pc_low == 34) {
        break;
    }
    */

    state->cycle++;
}
