#include "apps.h"
#include "../modules/shell.h"
#include "../runtime/string.h"
#include "calculator.h"
#include "clearscreen.h"

void apps_init_calculator(){
	Task calculator;
	strcpy(calculator.name,"calculator");
	strcpy(calculator.description,"Simple decimal calculator");
	calculator.entry = &calculator_start;
	shell_add(calculator);
}

void apps_init_clear_screen(){
	Task calculator;
	strcpy(calculator.name,"clear");
	strcpy(calculator.description,"Clears screen");
	calculator.entry = &clear_screen_start;
	shell_add(calculator);
}

void apps_init(){
	apps_init_calculator();
	apps_init_clear_screen();
}
