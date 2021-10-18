#include "heap.h"

#include "set.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//this heap sort algorithm was supplied to us through the asgn3.pdf
//heap sort can be visualized as a tree even though in C it is formatted as a 2d array
//part of this algorithm is to fix the heap by making children that are higher than the parents switch places
uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    //to see if the children and parents need to be swapped we need to find the greatest child so return the right child if it greater or the left child if that one is greater
    if (right <= last && cmp(stats, A[right - 1], A[left - 1]) == 1) {
        return right;
    }
    return left;
}

//fix_heap will swap the parent with the child if the parent is less than the child
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);

    while (mother <= floor(last / 2) && !found) {
        if (cmp(stats, A[mother - 1], A[great - 1]) == -1) {
            //swap the mother node with the greatest child
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}

//build_heap() makes sure the entire heap tree is following the rules of the max heap
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = floor(last / 2); father > first - 1; father -= 1) {
        fix_heap(stats, A, father, last);
    }
}

//heap_sort() will take out teh already sorted elements out of the top of the tree since those are already the greatest for the tree at the end of fixing the heap
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last);
    for (uint32_t leaf = last; leaf > first; leaf -= 1) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }
    return;
}
