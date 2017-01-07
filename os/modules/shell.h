#ifndef SHELL_H
#define SHELL_H

typedef struct {
	char name[20];
	char description[250];
    void (*entry)(void);
} Task ;


void shell_init();
void shell_add(Task task);
void shell_run();
void shell_show_commands();

#endif
