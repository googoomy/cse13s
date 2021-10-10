#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double pi_madhava(void){
	double prev_val = -1;
	double current_val = 0;
	double final_val = 0;
	double numerator = 0;
	double expo = 0;
	double denominator = 0;
	while(absolute(prev_val - current_val) > EPSILON){
	//while(1){
		numerator = 1;
		if(num_terms == 0){
			expo = 1;
		}else{
			expo *= -3;
		}
		denominator = expo*(2*num_terms + 1);
		prev_val = current_val;
		current_val = numerator/denominator;
		final_val += current_val;
		num_terms += 1;
		//if (absolute(prev_val-current_val) < EPSILON){
		//	break;
		//}
	}
	final_val = final_val*sqrt_newton(12);
	return final_val;
}

int pi_madhava_terms(){
	return num_terms;
}
