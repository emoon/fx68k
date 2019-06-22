# fx68k

This create allows you to use the [fx68k](https://github.com/ijor/fx68k) CPU core from Rust. The intended purpose of this crate is to used for *verification* meaning if you have an CPU emulator implemented this can be used to verify that it's correct. The C++ code is generated from the SystemVerilog files using [Verilator](https://www.veripool.org/wiki/verilator)

# Performance

The performance of this crate is very low. When tested on my machine (AMD TR2 3.5 Ghz) it runs about ~5% of a 7 Mhz 68000 CPU so it's not intended to be used for real-time purposes.

# LICENCE

The original fx68k core code is under GPL v3 so this crate is under the same licence as it's pretty much just a "wrapper" around it. An option is to only depend on this crate as a dev dependency (running for tests) That way you can still keep the rest of your code in the licence you desire.
