#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Attribute byte for our default colour scheme .
#define WHITE_ON_BLACK 0x0f

//Screen device I / O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void display_print_str(char* message);
void display_print_str_at(char* message,int32_t col,int32_t row);
void display_print_char(char c);
void display_print_char_at(char character,int32_t col,int32_t row,char attribute_byte);
int32_t display_get_cursor();
int32_t display_get_screen_offset(int32_t col,int32_t row);
void display_set_cursor(int32_t offset);
void display_clear_screen();
int32_t display_handle_scrolling(int32_t cursor_offset);

#endif
