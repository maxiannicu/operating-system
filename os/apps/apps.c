#include "apps.h"
#include "../modules/shell.h"
#include "../runtime/string.h"
#include "calculator.h"
#include "clearscreen.h"
#include "shutdown.h"
#include "sort.h"

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

void apps_init_shutdown(){
	Task shutdown;
	strcpy(shutdown.name,"shutdown");
	strcpy(shutdown.description,"Shutdowns PC");
	shutdown.entry = &shutdown_start;
	shell_add(shutdown);
}

void apps_init_sort(){
	Task sortTask;
	strcpy(sortTask.name,"sort");
	strcpy(sortTask.description,"Sorts an array of numbers");
	sortTask.entry = &sort_start;
	shell_add(sortTask);
}

void apps_init(){
	apps_init_calculator();
	apps_init_clear_screen();
	apps_init_shutdown();
	apps_init_sort();
}
