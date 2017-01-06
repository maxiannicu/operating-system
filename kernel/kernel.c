#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../tools/string.h"
#include "timer.h"
#include "isr.h"

void main(){
	clear_screen();	
	isr_init();

	keyboard_init();
	//timer_init(50);
}
