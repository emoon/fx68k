#/bin/sh
verilator --cc --clk clk -Wno-fatal fx68k.sv fx68kAlu.sv uaddrPla.sv fx68k_MicroRom.v fx68k_NanoRom.v --exe fx68k_main.cpp --Mdir fx68k_verilator
