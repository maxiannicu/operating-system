#include "../drivers/timer.h"
#include "../runtime/string.h"
#include "isr.h"
#include "../modules/io.h"

void main(){
	isr_init();
	io_init();
	//timer_init(50);

	char name[20];
	while(1){
		io_put_str("Enter your name:");

		io_get_str(name,20);

		io_put_str("Hello : ");
		io_put_str(name);
		io_put_str("\n");
	}
}
