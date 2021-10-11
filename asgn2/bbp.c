#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double pi_bbp(void) {
    double prev_val = -1;
    //current value that is being calculated
    double curr_val = 0;
    //final_val is the pi that is being estimated
    double final_val = 0;
    //16^-k number is multiplier
    double multiplier = 0;
    //the fraction 16^-k is multiplying is fraction
    double fraction = 0;
    //top of the fraction
    double numerator = 0;
    //bottom of the fraction
    double denominator = 0;
    //while loop breaks once the previous term - current term is less than epsiolon
    while (absolute(prev_val - curr_val) > EPSILON) {
        prev_val = curr_val; //set previous term to current term before current term is changed
        if (num_terms == 0) { //16^0 is 1
            multiplier = 1;
        } else {
            multiplier *= 1 / 16.0;
        }
        numerator = num_terms * (120 * num_terms + 151) + 47;
        denominator
            = num_terms * (num_terms * (num_terms * (512 * num_terms + 1024) + 712) + 194) + 15;
        fraction = numerator / denominator;
        curr_val = fraction * multiplier; //set current value to the 16^-k times the fraction
        final_val += curr_val;
        num_terms += 1;
    }
    return final_val;
}

int pi_bbp_terms(void) {
    return num_terms;
}
