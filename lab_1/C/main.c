/*
 * A simple bootloader skeleton for x86, using gcc.
 *
 * Prashant Borole (boroleprashant at Google mail)
 * */
 
/* XXX these must be at top */
#include "includes.h"
#include "input.h"
#include "convert.h"

__asm__ ("jmpl  $0, $main\n");
 
void __NORETURN main(){
    int usedBase = 16;
    int i;
    print("Lets count in the base ");
    print(intToString(usedBase,10));
    print("\n");
    for(i = 0;i < 100;i++){
        print(intToString(i,usedBase));
        print("\n\r");
    }
    while(1);
}
