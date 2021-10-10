#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_iters = 0;

double sqrt_newton(double x){
	double z = 0.0;
	double y = 1.0;
	while (absolute(y-z) > EPSILON){
		z = y;
		y = 0.5 * (z+x/z);
		num_iters += 1;
	}
	return y;
}

int sqrt_newton_iters(void){
	return num_iters;
}
