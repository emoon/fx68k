#![allow(clippy::borrowed_box, clippy::transmute_ptr_to_ref)]

use byteorder::{BigEndian, WriteBytesExt};
use std::ffi::c_void;

/// Holds all the CPU state data such as registers, flags, etc
#[repr(C)]
pub struct CpuState {
    /// data registers
    d_registers: [u32; 8],
    /// address registers
    a_registers: [u32; 8],
    /// program counter
    pc: u32,
    /// status flags
    flags: u32,
    /// last read address
    last_read_address: u32,
    /// last written address
    last_written_address: u32,
}

#[derive(Copy, Clone)]
pub struct CodeAdress(u32);

#[derive(Copy, Clone)]
pub struct StackAddress(u32);

#[derive(Copy, Clone, PartialEq)]
pub enum Register {
    Data(u8),
    Address(u8),
}

extern "C" {
    fn fx68k_ver_new_instance(memory_interface: *mut c_void) -> *mut c_void;
    fn fx68k_ver_step_cycle(context: *mut c_void);
    fn fx68k_ver_cpu_state(context: *mut c_void) -> CpuState;
    fn fx68k_update_memory(context: *mut c_void, address: u32, data: *const c_void, length: u32);
    fn fx68k_update_register(context: *mut c_void, register: u32, value: u32);
}

pub struct Fx68k {
    /// private ffi instance
    ffi_instance: *mut c_void,
}

pub trait MemoryInterface {
    /// read u8 value from memory address. cycle is the current CPU cycle the read is being executed on.
    fn read_u8(&mut self, cycle: u32, address: u32) -> Option<u8>;
    /// read u16 value from memory address. cycle is the current CPU cycle the read is being executed on.
    fn read_u16(&mut self, cycle: u32, address: u32) -> Option<u16>;
    /// write u8 value to memory address. cycle is the current CPU cycle the write is being executed on.
    fn write_u8(&mut self, cycle: u32, address: u32, value: u8) -> Option<()>;
    /// write u16 value to memory address. cycle is the current CPU cycle the write is being executed on.
    fn write_u16(&mut self, cycle: u32, address: u32, value: u16) -> Option<()>;
}

#[no_mangle]
pub unsafe extern "C" fn fx68k_mem_read_u8(
    context: *mut Box<dyn MemoryInterface>,
    cycle: u32,
    address: u32,
) -> u8 {
    //println!("reading fx68k_mem_read_u8");
    let cb: &mut Box<dyn MemoryInterface> = std::mem::transmute(context);
    cb.read_u8(cycle, address).unwrap()
}

#[no_mangle]
pub unsafe extern "C" fn fx68k_mem_read_u16(
    context: *mut Box<dyn MemoryInterface>,
    cycle: u32,
    address: u32,
) -> u16 {
    //println!("reading fx68k_mem_read_u16 {} {}", cycle, address);
    let cb: &mut Box<dyn MemoryInterface> = std::mem::transmute(context);
    cb.read_u16(cycle, address).unwrap()
}

#[no_mangle]
pub unsafe extern "C" fn fx68k_mem_write_u8(
    context: *mut Box<dyn MemoryInterface>,
    cycle: u32,
    address: u32,
    value: u8,
) {
    let cb: &mut Box<dyn MemoryInterface> = std::mem::transmute(context);
    cb.write_u8(cycle, address, value).unwrap()
}

#[no_mangle]
pub unsafe extern "C" fn fx68k_mem_write_u16(
    context: *mut Box<dyn MemoryInterface>,
    cycle: u32,
    address: u32,
    value: u16,
) {
    let cb: &mut Box<dyn MemoryInterface> = std::mem::transmute(context);
    cb.write_u16(cycle, address, value).unwrap()
}

impl Fx68k {
    /// Create a new instance with a memory interface. Using this the CPU will boot up and read
    /// from address 0 and 4 to fetch the stack pointer and where to start code execution so it's
    /// up to the memory implementation to have this data correct.
    pub fn new_with_memory_interface<T: MemoryInterface>(memory_interface: T) -> Fx68k {
        unsafe {
            let f: Box<Box<dyn MemoryInterface>> = Box::new(Box::new(memory_interface));
            let memory_interface = Box::into_raw(f) as *mut _;

            Fx68k {
                ffi_instance: fx68k_ver_new_instance(memory_interface),
            }
        }
    }

    /// Create a new instance with some m68k code. Memory will be allocated to the size of
    /// memory_size, the CPU will boot up using this memory with code_address an stack_address set
    /// with the start_address and stack_address being setup. After the boot up is complete the
    /// data in code will be copied to the location of code_start_address in the memory.
    pub fn new_with_code(
        code: &[u8],
        code_address: CodeAdress,
        stack_address: StackAddress,
        memory_size: usize,
    ) -> Fx68k {
        let mut data = vec![0; memory_size];

        // Write the initial startup data
        data.write_u32::<BigEndian>(code_address.0).unwrap();
        data.write_u32::<BigEndian>(stack_address.0).unwrap();

        // setup the core
        let mut core = Fx68k::new_with_memory_interface(Fx68kVecMemoryInterface::new(data));

        // this will boot the core, setup the new PC and stack pointer
        core.boot();

        // write the code to the ram memory
        core.update_memory(code_address.0, code);

        // and finished
        core
    }

    /// Boot up the core. Run for n number of cycles and expect pc being 0, 4 and then something
    /// else (depending on the data in memory) if this ends up not being true the boot of the core
    /// has failed and this function will return false otherwise true.
    pub fn boot(&mut self) {
        // this is a kinda ugly hard coded value, but will do for now
        for _ in 0..242 {
            self.step();
        }
    }

    /// Updated memory the memory for a core
    pub fn update_memory(&mut self, address: u32, data: &[u8]) {
        unsafe {
            fx68k_update_memory(
                self.ffi_instance,
                address,
                data.as_ptr() as *const c_void,
                data.len() as u32,
            );
        }
    }

    /// step the CPU one cycle (notice that this doesn't step one CPU cycle but a cycle with the
    /// timer that the 68k CPU requires (see the user manual for more info) and step_cpu_cycle to
    /// step with the CPU timing clock
    pub fn step(&mut self) {
        unsafe {
            fx68k_ver_step_cycle(self.ffi_instance);
        }
    }

    /// step one CPU instruction. In this context it means stepping the CPU until the PC has
    /// changed. Return value is number of cycles that was needed for the PC to change. If PC
    /// wasn't able to change in 10000 steps None will be returned
    pub fn step_instruction(&mut self) -> Option<usize> {
        let prev_pc = self.cpu_state().pc;

        for i in 0..10000 {
            self.step();

            if self.cpu_state().pc != prev_pc {
                return Some(i);
            }
        }

        None
    }

    /// Run until reached a certain PC and returns number of cycles it took
    pub fn run_until(&mut self, pc: u32) -> usize {
        let mut total_cycle = 0;

        loop {
            total_cycle += self.step_instruction().unwrap();

            if self.cpu_state().pc == pc {
                return total_cycle;
            }
        }
    }

    /// Get the current state of the CPU (registers, pc, flags, etc)
    pub fn cpu_state(&self) -> CpuState {
        unsafe { fx68k_ver_cpu_state(self.ffi_instance) }
    }

    /// Update a register for the CPU
    pub fn set_register(&mut self, register: Register, data: u32) {
        unsafe {
            match register {
                Register::Data(reg) => {
                    fx68k_update_register(self.ffi_instance, u32::from(reg), data)
                }
                Register::Address(reg) => {
                    fx68k_update_register(self.ffi_instance, u32::from(reg + 8), data)
                }
            }
        }
    }
}

pub struct Fx68kVecMemoryInterface {
    data: Vec<u8>,
}

impl Fx68kVecMemoryInterface {
    pub fn new(data: Vec<u8>) -> Fx68kVecMemoryInterface {
        Fx68kVecMemoryInterface { data: data.clone() }
    }
}

impl MemoryInterface for Fx68kVecMemoryInterface {
    fn read_u8(&mut self, _cycle: u32, address: u32) -> Option<u8> {
        Some(self.data[address as usize])
    }

    fn read_u16(&mut self, _cycle: u32, address: u32) -> Option<u16> {
        let v0 = u16::from(self.data[address as usize]);
        let v1 = u16::from(self.data[address as usize + 1]);
        Some((v0 << 8) | v1)
    }

    fn write_u8(&mut self, _cycle: u32, address: u32, value: u8) -> Option<()> {
        self.data[address as usize] = value;
        Some(())
    }

    fn write_u16(&mut self, _cycle: u32, address: u32, value: u16) -> Option<()> {
        self.data[address as usize] = (value >> 8) as u8;
        self.data[address as usize + 1] = (value & 0xff) as u8;
        Some(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_read_boot_ok() {
        let mut data = vec![];
        // Write the initial startup data
        data.write_u32::<BigEndian>(0).unwrap();
        data.write_u32::<BigEndian>(8).unwrap();

        let mut core = Fx68k::new_with_memory_interface(Fx68kVecMemoryInterface::new(data));
        core.boot();

        let state = core.cpu_state();

        // make sure last address read was
        assert_eq!(state.last_read_address, 6);
    }

    #[test]
    fn test_new_code() {
        // create a core with a nop instruction and step it
        let mut _core = Fx68k::new_with_code(&[0x4e, 0x71], CodeAdress(0), StackAddress(0), 16);
    }

    #[test]
    fn test_moveq() {
        // create a core and run moveq #100,d0
        let mut core = Fx68k::new_with_code(&[0x70, 0x64], CodeAdress(0), StackAddress(0), 16);
        let _cycles = core.step_instruction();
        let _cycles = core.step_instruction();
        let state = core.cpu_state();

        // Make sure d0 was written correct
        assert_eq!(100, state.d_registers[0]);
    }

    #[test]
    fn test_two_instructions() {
        // create a core and run moveq #100,d0
        let mut core = Fx68k::new_with_code(
            &[0x70, 0x64, 0x70, 0x65, 0x4e, 0x71],
            CodeAdress(0),
            StackAddress(0),
            16,
        );
        // Make sure d0 was written correct
        core.run_until(4);
        assert_eq!(100, core.cpu_state().d_registers[0]);

        // Make sure d0 was written correct
        core.run_until(6);
        assert_eq!(101, core.cpu_state().d_registers[0]);
    }

    #[test]
    fn test_two_nop_instructions() {
        // create a core and run moveq #100,d0
        let mut core = Fx68k::new_with_code(
            &[0x4e, 0x71, 0x4e, 0x71],
            CodeAdress(0),
            StackAddress(0),
            16,
        );
        core.step_instruction();
        core.step_instruction();
    }

    #[test]
    fn test_divs_instructions() {
        // create a core and two divs #2,d0 instructions and update the d0 register before running
        let mut core = Fx68k::new_with_code(
            &[0x81, 0xfc, 0x00, 0x02, 0x81, 0xfc, 0x00, 0x02, 0x4e, 0x71],
            CodeAdress(0),
            StackAddress(0),
            16,
        );
        core.set_register(Register::Data(0), 8);

        core.run_until(8);
        assert_eq!(4, core.cpu_state().d_registers[0]);

        core.run_until(12);
        assert_eq!(2, core.cpu_state().d_registers[0]);
    }
}
