# Structure
1. Assembly
2. C

# Requirements
1. **nasm** - the Netwide Assembler, a portable 80x86 assembler
2. **gcc** - GNU project C and C++ compiler
3. **qemu-system** - emulating system (can be replaced with **VirtualBox**)
4. **bash** - Unix shell and command language

To install them, run the following command (**Ubuntu**):

`sudo apt-get install build-essential qemu nasm gcc`


# How to
To build and run bootloader, please run following command from one **C** or **ASM**
`./build.sh`

You'll have following generated structure folder tree
```
.
├── ASM
│   ├── bootloader.asm
│   ├── .build
│   │   ├── bootloader.bin
│   │   └── bootloader.flp
│   └── build.sh
├── C
│   ├── .build
│   │   ├── bootloader.bin
│   │   ├── bootloader.flp
│   ├── build.sh
│   ├── convert.c
│   ├── convert.h
│   ├── includes.h
│   ├── input.c
│   ├── input.h
│   ├── linker.ld
│   └── main.c
```

In *.build* folder, you have 2 files:
1. Binary executable
2. Floopy image

