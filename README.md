
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

