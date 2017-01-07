#include "io.h"
#include "../runtime/string.h"
#include "../drivers/keyboard.h"
#include "../drivers/display.h"
#include <stdarg.h>


void io_init(){
	keyboard_init();
	display_clear_screen();
}

char io_get_char(){
	return keyboard_get();
}

int32_t io_get_int(){
	char num[20];
	io_get_str(num,20);

	return atoi(num);
}

void io_get_str(char *str,uint8_t size){
	int16_t counter = -1;
	char c = 0;
	while(1){
		c = keyboard_get();

		if(c == KEY_BACKSPACE){
			counter--;
			if (counter < -1){
				counter = -1;
				continue;
			}
		} else if (c == KEY_ENTER){
			goto finish_get_str;
		} else if(counter >= size - 2){
			goto finish_get_str;
		} else {
			str[++counter] = c;
		}

		display_print_char(c);
	}

	finish_get_str:
	display_print_char(c);
	str[counter+1] = '\0';
	return;
}

void io_put_char(char c){
	display_print_char(c);
}

void io_put_int(int32_t val){
	char str[20];
	itoa(val,str,10);
	display_print_str(str);
}

void io_put_str(char *str){
	display_print_str(str);
}

void io_printf(char* format,...)
{
    char *traverse;
    int32_t i;
    char *s;

    char temp[200];

    //Module 1: Initializing printf's arguments
    va_list arg;
    va_start(arg, format);

    for(traverse = format; *traverse != '\0'; traverse++)
    {
        while( *traverse != '%' )
        {
            io_put_char(*traverse);
            traverse++;
        }

        traverse++;

        //Module 2: Fetching and executing arguments
        switch(*traverse)
        {
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
            			io_put_char(i);
                        break;

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        itoa(i,temp,10);
                        io_put_str(temp);
                        break;

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
						itoa(i,temp,8);
						io_put_str(temp);
                        break;

            case 's': s = va_arg(arg,char *);       //Fetch string
            			io_put_str(s);
                        break;

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
						itoa(i,temp,16);
						io_put_str(temp);
                        break;
        }
    }

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg);
}

void io_scanf(char* format,...){
	char *traverse;
	int32_t *i;
	char *s;
	char *c;

	//Module 1: Initializing scanf's arguments
	va_list arg;
	va_start(arg, format);

	for(traverse = format; *traverse != '\0'; traverse++)
	{
		while( *traverse != '%' )
		{
			io_put_char(*traverse);
			traverse++;
		}

		traverse++;

		//Module 2: Fetching and executing arguments
		switch(*traverse)
		{
			case 'c' : c = va_arg(arg,char*);     //Fetch char argument
						*c = io_get_char();
						break;

			case 'd' : i = va_arg(arg,int*);         //Fetch Decimal/Integer argument
						*i = io_get_int();
						break;

			case 's': s = va_arg(arg,char*);       //Fetch string
						io_get_str(s,250);
						break;
		}
	}

	//Module 3: Closing argument list to necessary clean-up
	va_end(arg);
}
