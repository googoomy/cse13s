#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double e(void) {
    int count = 0;
    double current_Value = 0;
    double prev_Term = 0;
    //double curr_Term = 0;
    double k_Factorial = 0;

    //while(absolute(prev_Term - curr_Term) > EPSILON){
    while (1) {
        //for(num_terms = 0; (absolute(prev_Term - current_Value) > EPSILON); num_terms++){
        if (k_Factorial == 0) {
            k_Factorial = 1;
            current_Value += k_Factorial;
        } else {
            prev_Term = current_Value;
            k_Factorial = count * k_Factorial;
            current_Value += (1 / k_Factorial);
        }
        //k_Factorial = count*k_Factorial;
        //prev_Term = curr_Term;
        //curr_Term = 1/k_Factorial;
        //current_Value = current_Value + curr_Term;
        count = count + 1;
        num_terms = num_terms + 1;
        if (absolute(prev_Term - current_Value) < EPSILON) {
            break;
        }
    }

    return current_Value;
}

int e_terms(void) {
    return num_terms;
}
