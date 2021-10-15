#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>

void insertion_sort(uint32_t *A, uint32_t n){
	uint32_t j = 0;
	uint32_t temp = 0;
	for(uint32_t i = 1; i < n; i+=1){
		j = i;
		temp = A[i];
		while(j > 0 && temp < A[j-1]){
			A[j] = A[j-1];
			j -= 1;
		}
		A[j] = temp;
	}	
}
