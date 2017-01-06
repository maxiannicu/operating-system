BOOTLOADER_BINARY = bootloader.bin
KERNEL_BINARY = kernel.bin
C_SOURCES = $(wildcard os/kernel/*.c os/modules/*.c os/tools/*.c)
C_HEADERS = $(wildcard os/kernel/*.h os/modules/*.h os/tools/*.h)
OBJ = ${C_SOURCES:.c=.o}

	

#kernel
${KERNEL_BINARY}: os/kernel/entry.o ${OBJ} os/kernel/interrupt.o
	ld -o $@ -m elf_i386 -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${C_HEADERS}
	gcc -ffreestanding -m32 -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

#bootloader
%.bin: bootloader/%.asm
	nasm -f bin -I bootloader/ -o $@ $<

%.dis : %.bin
	ndisasm -b 32 $< > $@

#commands
all: rebuild

build: ${BOOTLOADER_BINARY} ${KERNEL_BINARY}

clean:
	rm -fr *.bin *.o
	rm -fr os/kernel/*.o os/drivers/*.o os/tools/*.o

rebuild : clean build

run: build
	qemu-system-x86_64 -fda ${BOOTLOADER_BINARY} -fdb ${KERNEL_BINARY}
