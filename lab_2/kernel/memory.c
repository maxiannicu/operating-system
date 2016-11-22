#include "memory.h"

void memory_copy(char *src,char *dst,int bytes){
	int i;
	for(i=0;i<bytes;i++)
		*(dst+i) = *(src+i);
}
