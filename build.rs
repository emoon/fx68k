use cc;

fn main() {
    cc::Build::new()
        .cpp(true)
        .opt_level(3)  // always optimize for speed
        .include("fx68k/verilator_inc")
        .include("fx68k/fx68k_verilator")
        .file("fx68k/fx68k_verilator/Vfx68k___024unit.cpp")
        .file("fx68k/fx68k_verilator/Vfx68k__ALLcls.cpp")
        .file("fx68k/fx68k_verilator/Vfx68k__ALLsup.cpp")
        .file("fx68k/fx68k_verilator/Vfx68k__Syms.cpp")
        .file("fx68k/fx68k_main.cpp")
        .compile("fx68k_ver");
}
