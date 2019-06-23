use cc;

fn main() {
    cc::Build::new()
        .cpp(true)
        // .opt_level(3)  // always optimize for speed
        .define("VM_SC", "0")
        .define("VM_COVERAGE", "0")
        .define("VM_TRACE", "0")
        .define("VL_PRINTF", "printf")
        // .flag("-faligned-new")
        .pic(false)
        // .include("/usr/local/share/verilator/include")
        // .include("/usr/local/share/verilator/include/vltstd")
        .include("fx68k/verilator_inc")
        .include("fx68k/fx68k_verilator")
        .file("fx68k/verilator_inc/verilated.cpp")
        .file("fx68k/fx68k_verilator/Vfx68k__ALLcls.cpp")
        .file("fx68k/fx68k_verilator/Vfx68k__ALLsup.cpp")
        .file("fx68k/fx68k_main.cpp")
        .compile("fx68k_ver");
}
