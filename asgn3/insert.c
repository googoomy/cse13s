#include "insert.h"

#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    //algorithm from the python pseudocode in asgn3.pdf
    //goes through each element and placess them in the correct position
    for (uint32_t i = 1; i < n; i += 1) {
        uint32_t j = i;
        //seting temp to the element in A[i]
        uint32_t temp = move(stats, A[i]);
        while (j > 0 && cmp(stats, temp, A[j - 1]) == -1) {
            //move means A[j] = A[j-1];
            A[j] = move(stats, A[j - 1]);
            j -= 1;
        }
        //move means A[j] = temp;
        A[j] = move(stats, temp);
    }
    return;
}
