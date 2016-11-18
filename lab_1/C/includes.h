#ifndef INCLUDES_H
#define INCLUDES_H
__asm__(".code16gcc\n");
 
#define __NOINLINE  __attribute__((noinline))
#define __REGPARM   __attribute__ ((regparm(3)))
#define __NORETURN  __attribute__((noreturn))


#endif
