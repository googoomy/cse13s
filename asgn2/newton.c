#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_iters = 0;
//CITE: DARRELL LONG
double sqrt_newton(double x) {
    double z = 0.0;
    //first guess for square root is 1
    double y = 1.0;
    //if the difference between y and z is less than epsilon break out of while loop
    while (absolute(y - z) > EPSILON) {
        //continuously get closer to teh actual square root through each loop
        z = y;
        y = 0.5 * (z + x / z);
        num_iters += 1;
    }
    return y;
}

int sqrt_newton_iters(void) {
    return num_iters;
}
