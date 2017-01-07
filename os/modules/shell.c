#include "shell.h"
#include "io.h"
#include "../runtime/string.h"

#define MAX_TASKS 20

Task tasks[20];
int tasks_count = 0;

void shell_init(){
	Task task;
	strcpy(task.name,"help");
	strcpy(task.description,"Shows all existing commands");
	task.entry = &shell_show_commands;
	shell_add(task);
}

void shell_add(Task task){
	if(tasks_count < MAX_TASKS){
		tasks[tasks_count++] = task;
	}
}

void shell_run(){
	char cmd[50];
	int8_t i;
	int8_t commandFound;
	while(1){
		io_scanf("shell $ %s",cmd);
		commandFound = 0;
		for(i = 0; i < tasks_count;i++){
			if(strcmp(cmd,tasks[i].name) == 0){
				tasks[i].entry();
				commandFound = 1;
			}
		}
		if(!commandFound){
			io_printf("Error : command not found\n");
		}
	}
}

void shell_show_commands(){
	int8_t i;
	for(i = 0; i < tasks_count;i++){
		io_printf("------------------------------%c",'\n');
		Task *task = &tasks[i];
		io_printf("%s\n",task->name);
		io_printf("\t%s\n",task->description);
	}
}
