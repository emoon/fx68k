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
}

extern "C" {
    fn fx68k_ver_new_instance(memory_interface: *mut c_void) -> *mut c_void;
    fn fx68k_ver_step_cycle(context: *mut c_void);
    fn fx68k_ver_cpu_state(context: *mut c_void) -> CpuState;
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
pub extern "C" fn fx68k_mem_read_u8(context: *mut Box<dyn MemoryInterface>, cycle: u32, address: u32) -> u8 {
    println!("reading fx68k_mem_read_u8");
    unsafe {
        let cb: &mut Box<dyn MemoryInterface> = std::mem::transmute(context);
        cb.read_u8(cycle, address).unwrap()
    }
}

#[no_mangle]
pub extern "C" fn fx68k_mem_read_u16(context: *mut Box<dyn MemoryInterface>, cycle: u32, address: u32) -> u16 {
    println!("reading fx68k_mem_read_u16 {} {}", cycle, address);
    unsafe {
        let cb: &mut Box<dyn MemoryInterface> = std::mem::transmute(context);
        cb.read_u16(cycle, address).unwrap()
    }
}

#[no_mangle]
pub extern "C" fn fx68k_mem_write_u8(context: *mut Box<dyn MemoryInterface>, cycle: u32, address: u32, value: u8) {
    unsafe {
        let cb: &mut Box<dyn MemoryInterface> = std::mem::transmute(context);
        cb.write_u8(cycle, address, value).unwrap()
    }
}

#[no_mangle]
pub extern "C" fn fx68k_mem_write_u16(context: *mut Box<dyn MemoryInterface>, cycle: u32, address: u32, value: u16) {
    unsafe {
        let cb: &mut Box<dyn MemoryInterface> = std::mem::transmute(context);
        cb.write_u16(cycle, address, value).unwrap()
    }
}

impl Fx68k {
    pub fn new<T: MemoryInterface>(memory_interface: T) -> Fx68k {
        unsafe {
            let f: Box<Box<dyn MemoryInterface>> = Box::new(Box::new(memory_interface));
            let memory_interface = Box::into_raw(f) as *mut _;

            Fx68k {
                ffi_instance: fx68k_ver_new_instance(memory_interface),
            }
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

    /// Get the current state of the CPU (registers, pc, flags, etc)
    pub fn cpu_state(&self) -> CpuState {
        unsafe {
            fx68k_ver_cpu_state(self.ffi_instance)
        }
    }
}

pub struct Fx68kVecMemoryInterface {
    data: Vec<u8>,
}

impl Fx68kVecMemoryInterface {
    pub fn new(data: Vec<u8>) -> Fx68kVecMemoryInterface {
        Fx68kVecMemoryInterface {
            data: data.clone(),
        }
    }
}

impl MemoryInterface for Fx68kVecMemoryInterface {
    fn read_u8(&mut self, _cycle: u32, address: u32) -> Option<u8> {
        Some(self.data[address as usize])
    }

    fn read_u16(&mut self, _cycle: u32, address: u32) -> Option<u16> {
        let v0 = self.data[address as usize + 0] as u16;
        let v1 = self.data[address as usize + 1] as u16;
        Some((v0 << 8) | v1)
    }

    fn write_u8(&mut self, _cycle: u32, address: u32, value: u8) -> Option<()> {
        self.data[address as usize] = value;
        Some(())
    }

    fn write_u16(&mut self, _cycle: u32, address: u32, value: u16) -> Option<()> {
        self.data[address as usize + 0] = (value >> 8) as u8;
        self.data[address as usize + 1] = (value & 0xff) as u8;
        Some(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_read_init() {
        let data = vec![0,0,0,8, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0];
        let mut core = Fx68k::new(Fx68kVecMemoryInterface::new(data));

        // step the CPU until it reaches address 4
        for _ in 0..1000 {
            core.step();
            let state = core.cpu_state();

            if state.pc == 4 {
                return;
            }
        }

        // fail the test if we didn't get to the correct address above
        panic!("fail to step");
    }
}

