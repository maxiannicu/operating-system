#include "display.h"

#include "../runtime/memory.h"
#include "../runtime/ports.h"

void display_print_str(char* message){
	display_print_str_at(message,-1,-1);
}

void display_print_char(char c){
	display_print_char_at(c,-1,-1,WHITE_ON_BLACK);
}

void display_print_str_at(char* message,int32_t col,int32_t row){
	// Update the cursor if col and row not negative .
	if (col >= 0 && row >= 0) {
		display_set_cursor(display_get_screen_offset(col,row));
	}

	// Loop through each char of the message and print it .
	int32_t i = 0;
	while (message[i] != 0){
		display_print_char_at(message[i++],col,row,WHITE_ON_BLACK);
	}
}

void display_print_char_at(char character,int32_t col,int32_t row,char attribute_byte){
	unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
	
	if(!attribute_byte)
		attribute_byte = WHITE_ON_BLACK;
	
	int32_t offset;
	if(col >= 0 && row >=0){
		offset = display_get_screen_offset(col,row);
	} else {
		offset = display_get_cursor();
	}

	if(character == '\n'){
		int rows = offset / (2*MAX_COLS);
		offset = display_get_screen_offset(79,rows);
	} else if(character == '\t'){
		offset += 6;
	} else if(character == 0x8) { // backspace
		vidmem[offset-2] = ' ';
		vidmem[offset-1] = attribute_byte;
		offset -= 4;
	} else {
		vidmem[offset] = character;
		vidmem[offset+1] = attribute_byte;
	}

	offset += 2;
	offset = display_handle_scrolling(offset);
	display_set_cursor(offset);
}

int32_t display_get_cursor(){
	port_byte_out(REG_SCREEN_CTRL,14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL,15);
	offset += port_byte_in(REG_SCREEN_DATA);

	return offset*2;
}

int32_t display_get_screen_offset(int32_t col,int32_t row){
	return 2*(MAX_COLS*row+col);
}

void display_set_cursor(int32_t offset){
	offset /= 2;
	port_byte_out(REG_SCREEN_CTRL,14);
	port_byte_out(REG_SCREEN_DATA,(unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL,15);
	port_byte_out(REG_SCREEN_DATA,offset);
}

void display_clear_screen(){
	int32_t row;
	int32_t col;

	for(row = 0;row < MAX_ROWS;row++){
		for(col = 0; col < MAX_COLS;col++){
			display_print_char_at(' ',col,row,WHITE_ON_BLACK);
		}
	}

	display_set_cursor(display_get_screen_offset(0,0));
}

int32_t display_handle_scrolling(int32_t cursor_offset){
	if (cursor_offset < MAX_ROWS*MAX_COLS*2) {
		return cursor_offset;
	}

	/* Shuffle the rows back one . */
	int32_t i;
	for (i =1; i < MAX_ROWS;i ++) {
		mem_cpy (display_get_screen_offset(0,i)+VIDEO_ADDRESS,display_get_screen_offset(0,i-1)+VIDEO_ADDRESS,MAX_COLS*2);
	}

	char * last_line = display_get_screen_offset(0,MAX_ROWS-1) + VIDEO_ADDRESS ;
	for (i=0; i < MAX_COLS*2;i++) {
		last_line[i] = 0;
	}

	cursor_offset -= 2*MAX_COLS;

	return cursor_offset ;
}
