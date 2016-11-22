OS_BINARY = os.bin
C_SOURCES = $(wildcard kernel/*.c drivers/*.c tools/*.c)
C_HEADERS = $(wildcard kernel/*.h drivers/*.h tools/*.h)
OBJ = ${C_SOURCES:.c=.o}

	

#kernel
kernel.bin: kernel/entry.o ${OBJ}
	ld -o $@ -m elf_i386 -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${C_HEADERS}
	gcc -ffreestanding -m32 -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

#bootloader
%.bin: %.asm
	nasm -f bin -I bootloader/ -o $@ $<

#os
${OS_BINARY}: bootloader/bootloader.bin kernel.bin
	cat $^ > ${OS_BINARY}

%.dis : %.bin
	ndisasm -b 32 $< > $@

#commands
build: ${OS_BINARY}

clean:
	rm -fr *.bin *.o ${OS_BINARY} *.dis
	rm -fr kernel/*.o bootloader/*.bin drivers/*.o tools/*.o

rebuild : clean build

run: ${OS_BINARY}
	qemu-system-x86_64 -fda $<
