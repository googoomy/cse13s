#include "quick.h"

#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//this quick sort algorithm was supplied to us in python code in asgn3.pdf
//quick sort involves a recusive sorting partition based on a pivot number in the set.
//a pivot number is chosen and each side of it needs to be ordered. numbers on its left need to be less than it and numbers on the right need to be greater than it
//and each of those partitions will be subject to the same pivot number and partitions until sorted.

//partition() places elements is the right spots based on the pivot number
uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;
    for (uint32_t j = lo; j < hi; j++) {
        if (cmp(stats, A[j - 1], A[hi - 1]) == -1) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}

//quick_sorter() is where all the recursive divide by conquer strategy happens.
//it will give each left and right side a partition and sort it using itself
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    if (lo < hi) {
        uint32_t p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
    return;
}

//quick_sort() calls the recursive function to finish off the sorting
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
    return;
}
