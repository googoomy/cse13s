#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double pi_euler(void) {
    double prev_val = -1;
    //current value of the summation
    double curr_val = 0;
    //the approximation of pi
    double final_val = 0;
    //the k in 1/k^2
    double k_val = 1;
    while (1) {
        prev_val = curr_val;
        //1/k^2
        curr_val = 1 / (k_val * k_val);
        final_val += curr_val;
        k_val += 1;
        num_terms += 1;
        if (curr_val < EPSILON) {
            break;
        }
    }
    //multiply the summation by 6 and then sqrt it to get pi
    final_val *= 6;
    final_val = sqrt_newton(final_val);
    return final_val;
}

int pi_euler_terms(void) {
    return num_terms;
}
