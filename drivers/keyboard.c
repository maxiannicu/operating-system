#include "keyboard.h"
#include "display.h"
#include "../kernel/isr.h"
#include "../kernel/low_level.h"
#include "../tools/string.h"

#define SCAN_CODE_MAP_SIZE 57
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

void print_letter(uint8_t scancode) {
	if(scancode < SCAN_CODE_MAP_SIZE){
		print_char(keyboard_get_key(scancode));
	} else  {
		if (scancode <= 0x7f) {
			print("Unknown key down");
		} else if (scancode <= 0x39 + 0x80) {
			print("key up ");
			print_letter(scancode - 0x80);
		} else {
			print("Unknown key up");
		}
    }
}


static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);
    char *sc_ascii;
    itoa(scancode, sc_ascii,10);
    print("Keyboard scancode: ");
    print(sc_ascii);
    print(", ");
    print_letter(scancode);
    print("\n");
}

void keyboard_init() {
   isr_register_handler(IRQ1, keyboard_callback);
}

char keyboard_get_key(uint8_t scancode){
	return scancode_ascii_map[scancode];
}
