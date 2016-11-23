# Intro
This project contains simple written in : 
1. Assembly (Contains I/O base operations)
2. C (Contains Output operations, counter in hex)

# Requirements
0. **bash**
1. **nasm** - the Netwide Assembler, a portable 80x86 assembler
2. **make** - GNU make utility to maintain groups of programs
2. **gcc** - GNU project C and C++ compiler
3. **qemu-system** - emulating system (can be replaced with **VirtualBox**)

To install them, run the following command (**Ubuntu**):

`sudo apt-get install build-essential qemu nasm gcc`


# Commands

`make build` - builds bootloader and kernel
`make clean` - clean project
`make rebuild` - clean project and builds bootloader and kernel
`make run` - builds project and run in **QEMU**

# Bootloader Codebase
```
.
├── bootloader
    ├── bootloader.asm - bootloader
    ├── gdt.asm - Global Descriptor Table
    ├── io.asm - IO methods for 16 bit
    ├── io_pm.asm - IO methods for 32 bit - protected mode
    └── switch_pm.asm - Switch from 16bit to 32bit
```


# Kernel Codebase
```
.
├── drivers
│   ├── display.c
│   └── display.h - set of methods for manipulating display
├── kernel
│   ├── entry.asm - entry point for kernel, calls main function frm kernel
│   ├── kernel.c - kernel
│   ├── low_level.c
│   ├── low_level.h - set functions for GPIO in/out 
│   ├── memory.c 
│   └── memory.h - set of methods for memory management
└── tools
    ├── string.c
    └── string.h - set of methods for string
```


