#include "sorting.h"

void sorting_swap(int32_t *a,int32_t *b){
	int32_t c = *b;
	*b = *a;
	*a = c;
}

void sorting_bubble(int32_t *arr,int32_t count){
	int i=0;
	int e=0;
	for(i = 0; i < count-1; i++){
		for(e = i+1; e < count;e++){
			if(arr[i] > arr[e]){
				sorting_swap(arr+i,arr+e);
			}
		}
	}
}
