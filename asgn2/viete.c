#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double pi_viete(void) {
    double prev_val = -1;
    //current term for the summation
    double curr_val = 0;
    //start viete at 1 so when multipliers multiply it isn't 0
    double final_val = 1;
    //2/pi's 2
    double numerator = 2;
    //sqrt(2)s
    double current_sqrt = 0;
    //once the diff between the previous term and current term is less than epsilon break out of the while loop
    while (absolute(prev_val - curr_val) > EPSILON) {
        prev_val = curr_val;
        current_sqrt = sqrt_newton(2 + current_sqrt);
        curr_val = current_sqrt / 2;
        final_val *= curr_val;
        num_terms += 1;
    }
    //pi will be the ratio of 2/the product
    return numerator / final_val;
}

int pi_viete_factors(void) {
    return num_terms;
}
