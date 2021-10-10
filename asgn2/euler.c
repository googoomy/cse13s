#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double pi_euler(void){
	double prev_val = -1;
	double curr_val = 0;
	double final_val = 0;
	double k_val = 1;
	while(absolute(prev_val-curr_val) > EPSILON){
		prev_val = curr_val;
		curr_val = 1/(k_val*k_val);
		final_val += curr_val;
		k_val += 1;
		num_terms += 1;
		
	}
	final_val *= 6;
	final_val = sqrt_newton(final_val);
	return final_val;

}

int pi_euler_terms(void){
	return num_terms;
}
