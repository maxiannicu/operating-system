#ifndef STRING_H
#define STRING_H
#include <stdint.h>

int32_t strlen(char *str);

char* itoa(int32_t num, char* str, int32_t base);

int32_t atoi(char* str);

void reverse(char* str);

int32_t strcmp(const char* s1, const char* s2);

void strcpy(char dest[], const char source[]);

#endif
