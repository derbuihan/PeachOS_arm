# PeachOS_arm

PeachOS_arm is a simple operating system for the Raspberry Pi 3B+.

## Requirements

- M1 Mac
- QEMU (`brew install qemu`)
- Cross-compiler for aarch64-elf (`brew install aarch64-elf-gcc aarch64-elf-binutils aarch64-elf-gdb`)

## Usage

Build

```bash
$ make all
```

Run the following command to run the kernel on QEMU:

```bash
$ qemu-system-aarch64 -m 1024 -M raspi3b -cpu cortex-a53 -kernel ./bin/kernel8.img -nographic -serial null -chardev stdio,id=uart1 -serial chardev:uart1 -monitor none   
```

Debug

```bash
$ qemu-system-aarch64 -m 1024 -M raspi3b -cpu cortex-a53 -kernel ./bin/kernel8.img -nographic -serial null -chardev stdio,id=uart1 -serial chardev:uart1 -monitor none -S -s
```

```bash
$ aarch64-elf-gdb -q ./build/kernel8.elf
(gdb) break kernel.c:30
(gdb) target remote localhost:1234
(gdb) c
(gdb) print ptr
```

## References

- https://github.com/s-matyukevich/raspberry-pi-os
- https://github.com/nibblebits/PeachOS/
