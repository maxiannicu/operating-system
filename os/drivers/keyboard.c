#include "keyboard.h"
#include "display.h"

#include "../kernel/isr.h"
#include "../runtime/ports.h"
#include "../runtime/string.h"

#define SCAN_CODE_MAP_SIZE 57

char buffer_key;
volatile char buffer_full;

const char scancode_ascii_map[SCAN_CODE_MAP_SIZE] = {
		KEY_ERROR,
		KEY_ESC,
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'0',
		'-',
		'+',
		KEY_BACKSPACE,
		KEY_TAB,
		'q',
		'w',
		'e',
		'r',
		't',
		'y',
		'u',
		'i',
		'o',
		'p',
		'[',
		']',
		KEY_ENTER,
		KEY_LEFT_CONTROL, // LEFT CONTROL
		'a',
		's',
		'd',
		'f',
		'g',
		'h',
		'j',
		'k',
		'l',
		';',
		'\'',
		'`',
		KEY_LEFT_SHIFT,
		'\\',
		'z',
		'x',
		'c',
		'v',
		'b',
		'n',
		'm',
		',',
		'.',
		'/',
		KEY_RIGHT_SHIFT,
		'*',
		KEY_LEFT_ALT,
		KEY_SPACE
};

char keyboard_get_key(uint8_t scancode){
	return scancode_ascii_map[scancode];
}


void print_letter(uint8_t scancode) {
	if(scancode < SCAN_CODE_MAP_SIZE){
		display_print_char(keyboard_get_key(scancode));
	} else  {
		if (scancode <= 0x7f) {
			display_print_str("Unknown key down");
		} else if (scancode <= 0x39 + 0x80) {
			display_print_str("key up ");
			print_letter(scancode - 0x80);
		} else {
			display_print_str("Unknown key up");
		}
    }
}


static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);

    if(scancode < SCAN_CODE_MAP_SIZE){
		char key = keyboard_get_key(scancode);

		if(key < 128){
			buffer_full = 1;
			buffer_key = key;
		}
    }
}

void keyboard_init() {
   isr_register_handler(IRQ1, keyboard_callback);
   buffer_full = 0;
   buffer_key = 0;
}

char keyboard_get(){
	buffer_key = 0;
	buffer_full = 0;
	while(!buffer_full); // wait for key
	char return_key = buffer_key;

	return return_key;
}
