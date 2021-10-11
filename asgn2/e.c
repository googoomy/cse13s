#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

static int num_terms = 0;

double e(void) {
    //count is the current number for the factorial
    int count = 0;
    //cuurent value of the summation
    double current_Value = 0;
    //previous term of the summation
    double prev_Term = 0;
    //k_factorial is the current factorial so we dont have to recalculate
    double k_Factorial = 0;

    while (1) {
        //0! is 1
        if (k_Factorial == 0) {
            k_Factorial = 1;
            current_Value += k_Factorial;
        } else {
            prev_Term = current_Value;
            //1/k!
            k_Factorial = count * k_Factorial;
            current_Value += (1 / k_Factorial);
        }
        count = count + 1;
        num_terms = num_terms + 1;
        //if the difference between previous term and current term is less than epsilon break out of while loop
        if (absolute(prev_Term - current_Value) < EPSILON) {
            break;
        }
    }
    return current_Value;
}

int e_terms(void) {
    return num_terms;
}
