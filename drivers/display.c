#include "display.h"
#include "../kernel/low_level.h"
#include "../kernel/memory.h"

void print(char* message){
	print_at(message,-1,-1);
}

void print_char(char c){
	print_char_at(c,-1,-1,WHITE_ON_BLACK);
}

void print_at(char* message,int32_t col,int32_t row){
	// Update the cursor if col and row not negative .
	if (col >= 0 && row >= 0) {
		set_cursor(get_screen_offset(col,row));
	}

	// Loop through each char of the message and print it .
	int32_t i = 0;
	while (message[i] != 0){
		print_char_at(message[i++],col,row,WHITE_ON_BLACK);
	}
}

void print_char_at(char character,int32_t col,int32_t row,char attribute_byte){
	unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
	
	if(!attribute_byte)
		attribute_byte = WHITE_ON_BLACK;
	
	int32_t offset;
	if(col >= 0 && row >=0){
		offset = get_screen_offset(col,row);
	} else {
		offset = get_cursor();
	}

	if(character == '\n'){
		int rows = offset / (2*MAX_COLS);
		offset = get_screen_offset(79,rows);
	} else {
		vidmem[offset] = character;
		vidmem[offset+1] = attribute_byte;
	}

	offset += 2;
	offset = handle_scrolling(offset);
	set_cursor(offset);
}

int32_t get_cursor(){
	port_byte_out(REG_SCREEN_CTRL,14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8;
	port_byte_out(REG_SCREEN_CTRL,15);
	offset += port_byte_in(REG_SCREEN_DATA);

	return offset*2;
}

int32_t get_screen_offset(int32_t col,int32_t row){
	return 2*(MAX_COLS*row+col);
}

void set_cursor(int32_t offset){
	offset /= 2;
	port_byte_out(REG_SCREEN_CTRL,14);
	port_byte_out(REG_SCREEN_DATA,(unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL,15);
	port_byte_out(REG_SCREEN_DATA,offset);
}

void clear_screen(){
	int32_t row;
	int32_t col;

	for(row = 0;row < MAX_ROWS;row++){
		for(col = 0; col < MAX_COLS;col++){
			print_char_at(' ',col,row,WHITE_ON_BLACK);
		}
	}

	set_cursor(get_screen_offset(0,0));
}

int32_t handle_scrolling(int32_t cursor_offset){
	if (cursor_offset < MAX_ROWS*MAX_COLS*2) {
		return cursor_offset;
	}

	/* Shuffle the rows back one . */
	int32_t i;
	for (i =1; i < MAX_ROWS;i ++) {
		memory_copy (get_screen_offset(0,i)+VIDEO_ADDRESS,get_screen_offset(0,i-1)+VIDEO_ADDRESS,MAX_COLS*2);
	}

	char * last_line = get_screen_offset(0,MAX_ROWS-1) + VIDEO_ADDRESS ;
	for (i=0; i < MAX_COLS*2;i++) {
		last_line[i] = 0;
	}

	cursor_offset -= 2*MAX_COLS;

	return cursor_offset ;
}
