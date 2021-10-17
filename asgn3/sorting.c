#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "set.h"
#include "stats.h"
#include "insert.h"
#include "shell.h"
#include "heap.h"
#include "quick.h"

#define OPTIONS "aeisqr:n:p:h"

typedef enum {INSERTION, SHELL, HEAP, QUICK, NUM_SORTS } Sorts;

int main(int argc, char ** argv){
	Set s = empty_set();
	int opt = 0;
	uint32_t seed = 13371453;
	uint32_t size = 100;
	uint32_t elements = 100;
	while((opt = getopt(argc, argv, OPTIONS)) != -1){
		switch(opt){
			case 'a':
				s = insert_set(INSERTION, s);
				s = insert_set(SHELL, s);
				s = insert_set(HEAP, s);
				s = insert_set(QUICK, s);
				break;
			case 'e':
				s = insert_set(HEAP, s);
				break;
			case 'i':
				s = insert_set(INSERTION, s);
				break;
			case 's':
				s = insert_set(SHELL, s);
				break;
			case 'q':
				s = insert_set(QUICK, s);
				break;
			case 'r':
				seed = strtoul(optarg, NULL, 10);
				printf("seed %u\n", seed);
				break;
			case 'n':
				size = strtoul(optarg, NULL, 10);
				printf("size %u\n", size);
				break;
			case 'p':
				elements = strtoul(optarg, NULL, 10);
				printf("size %u\n", elements);
				break;
			case 'h':
				s = empty_set();
				break;	
		}
	
	}
	

	Stats stats;
	stats.moves = 0;
	stats.compares = 0;
	uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
	for(uint32_t i = 0; i < size; i+=1){
		A[i] = random() & (((long)1 << (30))-1);
	}	
	if(member_set(INSERTION, s)){
		insertion_sort(&stats, A, size);
		printf("Insertion Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stats.moves, stats.compares);
		if(elements > 0){
			for(uint32_t i = 0; i < elements; i += 1){
				printf("%13" PRIu32, A[i]);
				if((i+1)%5 == 0){
					printf("\n");
				}	
			}
		}
		reset(&stats);
	}
	if(member_set(SHELL, s)){
		shell_sort(&stats, A, size);
		printf("Shell Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stats.moves, stats.compares);
		if(elements > 0){
			for(uint32_t i = 0; i < elements; i+=1){
				printf("%13" PRIu32, A[i]);
				if((i+1)%5 == 0){
					printf("\n");
				}
			}
		}
		reset(&stats);
	}
	if(member_set(HEAP, s)){
		heap_sort(&stats, A, size);
		printf("Heap Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size, stats.moves, stats.compares);
		if(elements > 0){
			for(uint32_t i = 0; i < elements; i+=1){
				printf("%13" PRIu32, A[i]);
				if((i+1)%5 == 0){
					printf("\n");
				}
			}
		}
		reset(&stats);
	}
	free(A);
	return 0;
}
