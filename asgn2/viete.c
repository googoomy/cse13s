#include "mathlib.h"

#include <stdlib.h>
#include <stdio.h>

static int num_terms = 0;

double pi_viete(void){
	double prev_val = -1;
	double curr_val = 0;
	double final_val = 1;
	double numerator = 2;
	double denominator = 0;
	while(absolute(prev_val-curr_val) > EPSILON){
		prev_val = curr_val;
		//if(num_terms == 0){
		//	final_val = 1;
		//}else{
		denominator = sqrt_newton(2+denominator);
		curr_val = denominator/2;
		final_val *= curr_val;
		//}
		num_terms += 1;
	}
	return numerator/final_val;
}

int pi_viete_factors(void){
	return num_terms;
}
