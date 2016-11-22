C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
C_HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

	

#kernel
kernel.bin: ${OBJ} kernel/entry.o
	ld -o $@ -m elf_i386 -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${C_HEADERS}
	gcc -ffreestanding -m32 -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

#bootloader
%.bin: %.asm
	nasm -f bin -I bootloader/ -o $@ $<

#os
os.bin: bootloader/bootloader.bin kernel.bin
	cat $^ > os.bin

#commands
build: os.bin

clean:
	rm -fr *.bin *.o os.bin
	rm -fr kernel/*.o boot/*.bin drivers/*.o

rebuild : clean build

run: os.bin 
	qemu-system-x86_64 -fda $<
