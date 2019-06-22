use std::ffi::c_void;

extern "C" {
    fn fx68k_ver_new_instance(memory_interface: *mut c_void) -> *mut c_void;
    fn fx68k_ver_step_cycle(context: *mut c_void);
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
    unsafe {
        let mut cb: Box<Box<dyn MemoryInterface>> = Box::from_raw(context);
        cb.read_u8(cycle, address).unwrap()
    }
}

#[no_mangle]
pub extern "C" fn fx68k_mem_read_u16(context: *mut Box<dyn MemoryInterface>, cycle: u32, address: u32) -> u16 {
    unsafe {
        let mut cb: Box<Box<dyn MemoryInterface>> = Box::from_raw(context);
        cb.read_u16(cycle, address).unwrap()
    }
}

#[no_mangle]
pub extern "C" fn fx68k_mem_write_u8(context: *mut Box<dyn MemoryInterface>, cycle: u32, address: u32, value: u8) {
    unsafe {
        let mut cb: Box<Box<dyn MemoryInterface>> = Box::from_raw(context);
        cb.write_u8(cycle, address, value).unwrap()
    }
}

#[no_mangle]
pub extern "C" fn fx68k_mem_write_u16(context: *mut Box<dyn MemoryInterface>, cycle: u32, address: u32, value: u16) {
    unsafe {
        let mut cb: Box<Box<dyn MemoryInterface>> = Box::from_raw(context);
        cb.write_u16(cycle, address, value).unwrap()
    }
}

impl Fx68k {
    pub fn new<T: MemoryInterface>(memory_interface: Box<Box<T>>) -> Fx68k {
        unsafe {
            let memory_interface =
                Box::into_raw(memory_interface) as *mut Box<dyn MemoryInterface> as *mut c_void;

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
}

pub struct Fx68kVecMemoryInterface {
    data: Vec<u8>,
}

impl Fx68kVecMemoryInterface {
    pub fn new(data: Vec<u8>) -> Box<Box<Fx68kVecMemoryInterface>> {
        Box::new(Box::new(Fx68kVecMemoryInterface {
            data: data.clone(),
        }))
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
    fn test_init() {
        let data = vec![0, 0, 0, 8, 0,0,0,0, 0,0,0,0, 0,0,0,0];
        let mut core = Fx68k::new(Fx68kVecMemoryInterface::new(data));
        core.step();
    }
}

