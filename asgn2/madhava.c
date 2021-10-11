#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double pi_madhava(void) {
    double prev_val = -1;
    //current value of the summation
    double current_val = 0;
    //the approximation of pi
    double final_val = 0;
    //top of the fraction
    double numerator = 0;
    //-3^-k
    double expo = 0;
    //2k+1
    double denominator = 0;
    //if the difference between previous term and current term is less than epsilon break out of while loop
    while (absolute(prev_val - current_val) > EPSILON) {
        numerator = 1;
        if (num_terms == 0) {
            //-3^0 is 1
            expo = 1;
        } else {
            expo *= -3;
        }
        //-3^k*(2k+1)
        denominator = expo * (2 * num_terms + 1);
        prev_val = current_val;
        current_val = numerator / denominator;
        final_val += current_val;
        num_terms += 1;
    }
    //at the end multiply the approximation by sqrt(12)
    final_val = final_val * sqrt_newton(12);
    return final_val;
}

int pi_madhava_terms() {
    return num_terms;
}
