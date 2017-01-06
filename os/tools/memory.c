#include "memory.h"

void memory_copy(int32_t *src,int32_t *dst,int bytes){
	uint32_t i;
	for(i=0;i<bytes;i++)
		*(dst+i) = *(src+i);
}
