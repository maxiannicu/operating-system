BUILD_PATH=".build" 
BINARY_NAME="bootloader.bin"
FLOOPY_IMAGE_NAME="bootloader.flp"


OBJECT_FILES=""

rm -r $BUILD_PATH
mkdir $BUILD_PATH



for FILENAME in *.c
do
	OBJECT_FILENAME="${FILENAME::(-2)}.o"
	gcc -c -g -Os -march=i686 -m32 -ffreestanding -Wall -Werror -I. -o $BUILD_PATH/$OBJECT_FILENAME $FILENAME
	 
	if [ "$OBJECT_FILENAME" == "main.o" ];
	then
		OBJECT_FILES="${BUILD_PATH}/${OBJECT_FILENAME} ${OBJECT_FILES}"
	else
		OBJECT_FILES="${OBJECT_FILES} ${BUILD_PATH}/${OBJECT_FILENAME}"
	fi
done

ld -m elf_i386 -static -Tlinker.ld -nostdlib --nmagic -o $BUILD_PATH/build.elf $OBJECT_FILES

objcopy -O binary $BUILD_PATH/build.elf $BUILD_PATH/$BINARY_NAME
dd status=noxfer conv=notrunc if=$BUILD_PATH/$BINARY_NAME of=$BUILD_PATH/$FLOOPY_IMAGE_NAME

qemu-system-x86_64 -fda $BUILD_PATH/$FLOOPY_IMAGE_NAME
