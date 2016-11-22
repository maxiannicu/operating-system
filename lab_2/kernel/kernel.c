#include "../drivers/display.h"
#include "../tools/string.h"

void main(){
	clear_screen();	
	int i;
	for(i=0; i < 200;i++){
		char str[20];
		itoa(i,str,10);
		print(str);
		print("\n");
	}
}
