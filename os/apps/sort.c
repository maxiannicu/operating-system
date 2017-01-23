#include "sort.h"
#include "../runtime/sorting.h"
#include "../modules/io.h"
#include <stdint.h>
#define MAX_ELEMENTS 100

void sort_start(){
	int32_t data[MAX_ELEMENTS];
	int32_t count = 0;
	while(!(count > 0 && count < MAX_ELEMENTS)){
		io_printf("Please enter number of elements (0 < count < %d): ",MAX_ELEMENTS);
		io_scanf("%d",&count);
	}
	int32_t i = 0;
	for(i = 0;i < count;i++){
		io_printf("Please add element %d:",i+1);
		io_scanf("%d",data+i);
	}
	io_printf("Sorting elements...\n");
	sorting_bubble(data,count);

	io_printf("Your sorted elements are : ");
	for(i = 0;i < count;i++){
		io_printf("%d ",data[i]);
	}
	io_printf("\n");
}
