#include "io.h"
#include "../drivers/keyboard.h"
#include "../drivers/display.h"


void io_init(){
	keyboard_init();
	display_clear_screen();
}

char io_get_char(){
	return keyboard_get();
}

void io_get_str(char *str,uint8_t size){
	int16_t counter = -1;
	char c = 0;
	while(1){
		c = keyboard_get();
		display_print_char(c);

		if(c == KEY_BACKSPACE){
			counter--;
			if (counter < -1)
				counter = -1;
		} else if (c == KEY_ENTER){
			goto finish_get_str;
		} else if(counter >= size - 2){
			goto finish_get_str;
		} else {
			str[++counter] = c;
		}
	}

	finish_get_str:
	str[counter+1] = '\0';
	return;
}

void io_put_char(char c){
	display_print_char(c);
}

void io_put_str(char *str){
	display_print_str(str);
}
