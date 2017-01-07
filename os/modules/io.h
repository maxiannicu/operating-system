#ifndef IO_H
#define IO_H
#include <stdint.h>

void io_init();

int8_t io_is_char_printable(char c);
char io_get_char();
int32_t io_get_int();
void io_get_str(char *str,uint8_t size);

void io_put_char(char c);
void io_put_int(int32_t val);
void io_put_str(char *str);

void io_printf(char* format,...);
void io_scanf(char* format,...);

#endif
