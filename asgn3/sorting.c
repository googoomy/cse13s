#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "set.h"

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
				elements = stroul(optarg, NULL, 10);
				printf("size %u\n", elements);
				break;
			case 'h':
				s = empty_set();
				break;	
		}
	
	}

	uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
	for(uint32_t i = 0; i < size; i+=1){
		A[i] = random() & 1 << (30) - 1;
	}	
	if(member_set(INSERTION, s)){
	
	}
	return 0;
}
