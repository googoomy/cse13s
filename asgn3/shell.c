#include "shell.h"

#include "stats.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//algorithm supplied by asgn3.pdf with python pseudocode
//shell sort is a variation of insertion sort but first sorts pairs of elements that start with a gap and continues until the gap reaches one

//instead of using python generators I am using a static variable to keep track of gaps
static uint32_t iter_val = 0;

//gaps() keeps track of the current gap
uint32_t gaps(uint32_t n) {
    if (iter_val <= 0) {
        iter_val = (uint32_t)(log(3 + 2 * n) / log(3));
    } else {
        iter_val -= 1;
    }
    uint32_t power = pow(3, iter_val);
    uint32_t r = floor((power - 1) / 2);
    return r;
}

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t iters = (uint32_t)(log(3 + 2 * n) / log(3));
    //in the python pseudocode this for statemenet is in gaps() but i moved it here
    for (uint32_t i = iters; i > 0; i -= 1) {
        //keep track of current gap
        uint32_t gap = gaps(i);
        for (uint32_t k = gap; k < n; k++) {
            uint32_t j = k;
            uint32_t temp = move(stats, A[k]);
            while (j >= gap && cmp(stats, temp, A[j - gap]) == -1) {
                //move is the same as A[j] = A[j-gap];
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            //move is the same as A[j] = temp;
            A[j] = move(stats, temp);
        }
    }
    return;
}
