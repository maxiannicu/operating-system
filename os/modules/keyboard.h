#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdint.h>

// ascii keys
#define KEY_ERROR 0
#define KEY_ESC 0x1B
#define KEY_BACKSPACE 0x8
#define KEY_TAB 0x9
#define KEY_ENTER 0xD
#define KEY_SPACE 0x20

// additional non ascii keys
#define KEY_LEFT_CONTROL 128
#define KEY_LEFT_SHIFT 129
#define KEY_RIGHT_SHIFT 130
#define KEY_LEFT_ALT 131

void keyboard_init();
char keyboard_get_key(uint8_t scancode);

#endif
