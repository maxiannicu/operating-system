BUILD_PATH=".build" 

rm -r $BUILD_PATH
mkdir $BUILD_PATH
nasm -f bin -o $BUILD_PATH/bootloader.bin bootloader.asm 
dd status=noxfer conv=notrunc if=$BUILD_PATH/bootloader.bin of=$BUILD_PATH/bootloader.flp
qemu-system-x86_64 -fda $BUILD_PATH/bootloader.flp
