#include "shell.h"
#include "stats.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

uint32_t gaps(uint32_t n){
	static uint32_t iter_val = 0;

	if (iter_val <= 0){
		iter_val = (uint32_t)(log(3+2*n)/log(3));
	}
	else{
		iter_val -= 1;
	}
	uint32_t r =floor((pow(3,iter_val)- 1)/2);
	return r;
}

void shell_sort(Stats *stats, uint32_t *A, uint32_t n){
	uint32_t iters = (uint32_t)(log(3+2*n)/log(3));
	for(uint32_t i = 0; i < iters; i++){
		uint32_t gap = gaps(n);
		for(uint32_t k = gap; k < n; k++){
			uint32_t j = i;
			uint32_t temp = move(stats, A[i];
			while(j >= gap && comp(stats, temp, A[j-gap]) == -1)){
				A[j] = A[j-gap];
				j-= gap;
			}
			A[j] = temp;
		}
	}	
	return ;
}




