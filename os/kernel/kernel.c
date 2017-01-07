#include "isr.h"
#include "../modules/io.h"
#include "../modules/shell.h"
#include "../apps/apps.h"

void main(){
	isr_init();
	io_init();
	shell_init();
	apps_init();
	shell_run();
}
