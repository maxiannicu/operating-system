#ifndef IO_H
#define IO_H
#include <stdint.h>

void io_init();

char io_get_char();
void io_get_str(char *str,uint8_t size);

void io_put_char(char c);
void io_put_str(char *str);

#endif
