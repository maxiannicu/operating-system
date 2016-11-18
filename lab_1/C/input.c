#include "input.h"

void    __NOINLINE __REGPARM print(const char   *s){
    while(*s){
        __asm__ __volatile__ ("int  $0x10" : : "a"(0x0E00 | *s), "b"(7));
        s++;
    }
}


