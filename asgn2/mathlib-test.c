#include "mathlib.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define OPTIONS "haebmrvns"

int main(int argc, char **argv){
	int opt = 0;
	int no_input = true;
	int h_flag = false;
	int a_flag = false;
	int e_flag = false;

	while((opt = getopt(argc, argv, OPTIONS)) != -1){
		no_input = false;
		switch(opt){
			case 'h':
				h_flag = true; 
				break;
			case 'a':
				a_flag = true;
				break;
			case 'e':
				e_flag = true;
				break;
		}
	}

	if (e_flag){
		printf("testing e(): %16.15lf, num_terms: %d\n", e(), e_terms());
	}
}
