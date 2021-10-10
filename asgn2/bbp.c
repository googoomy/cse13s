#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double pi_bbp(void) {
    double prev_val = -1;
    double curr_val = 0;
    double final_val = 0;
    double multiplier = 0;
    double fraction = 0;
    double numerator = 0;
    double denominator = 0;
    while (absolute(prev_val - curr_val) > EPSILON) {
        prev_val = curr_val;
        if (num_terms == 0) {
            multiplier = 1;
        } else {
            multiplier *= 1 / 16.0;
        }
        numerator = num_terms * (120 * num_terms + 151) + 47;
        denominator
            = num_terms * (num_terms * (num_terms * (512 * num_terms + 1024) + 712) + 194) + 15;
        //fraction = (num_terms*(120*num_terms+151)+47)/(num_terms*(num_terms*(num_terms*(512*num_terms + 1024)+712)+194)+15);
        //fraction = (4/(8*num_terms+1))-(2/(8*num_terms+4))-(1/(8*num_terms+5))-(1/(8*num_terms+6));
        fraction = numerator / denominator;
        curr_val = fraction * multiplier;
        final_val += curr_val;
        num_terms += 1;
    }
    return final_val;
}

int pi_bbp_terms(void) {
    return num_terms;
}
