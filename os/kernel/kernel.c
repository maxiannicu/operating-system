#include "../modules/display.h"
#include "../modules/keyboard.h"
#include "../modules/timer.h"
#include "../tools/string.h"
#include "isr.h"

void main(){
	clear_screen();	
	isr_init();

	keyboard_init();
	//timer_init(50);
}
