#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "aeisqr:n:p:h"

typedef enum { INSERTION, SHELL, HEAP, QUICK, NUM_SORTS } Sorts;

int main(int argc, char **argv) {
    Set s = empty_set();
    int opt = 0;
    uint32_t seed = 13371453;
    uint32_t size = 100;
    uint32_t elements = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            s = insert_set(INSERTION, s);
            s = insert_set(SHELL, s);
            s = insert_set(HEAP, s);
            s = insert_set(QUICK, s);
            break;
        case 'e': s = insert_set(HEAP, s); break;
        case 'i': s = insert_set(INSERTION, s); break;
        case 's': s = insert_set(SHELL, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        case 'r':
            seed = strtoul(optarg, NULL, 10);
            //printf("seed %u\n", seed);
            break;
        case 'n':
            size = strtoul(optarg, NULL, 10);
            elements = size;
            //printf("size %u\n", size);
            break;
        case 'p':
            elements = strtoul(optarg, NULL, 10);
            //printf("size %u\n", elements);
            break;
        case 'h':
            s = empty_set();
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms.\n\n");
            printf("USAGE\n");
            printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
            printf("OPTIONS\n");
            printf("  -h              display program help and usage.\n");
            printf("  -a              enable all sorts.\n");
            printf("  -e              enable Heap Sort.\n");
            printf("  -i              enable Insertion Sort.\n");
            printf("  -s              enable Shell Sort.\n");
            printf("  -q              enable Quick Sort.\n");
            printf("  -n length       specify number of array elements (default: 100).\n");
            printf("  -p elements     specify number of elements to print (default: 100).\n");
            printf("  -r seed         specify random seed (default: 13371453).\n");
            break;
        }
    }

    srandom(seed);
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;
    if (size < elements) {
        elements = size;
    }
    uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
    for (uint32_t i = 0; i < size; i += 1) {
        A[i] = random() & (((long) 1 << (30)) - 1);
    }
    //uint32_t B[size];
    //for (uint32_t i = 0; i < size; i += 1) {
    //    B[i] = A[i];
    //}
    //uint32_t A[size];
    if (member_set(HEAP, s)) {
        //memcpy(A, B, size);
        //uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
        //for (uint32_t i = 0; i < size; i += 1) {
        //	A[i] = random() & (((long) 1 << (30)) - 1);
        //}
        heap_sort(&stats, A, size);
        printf("Heap Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
            stats.moves, stats.compares);
        if (elements > 0) {
            for (uint32_t i = 0; i < elements; i += 1) {
                printf("%13" PRIu32, A[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }
        }
        //free(A);
        //memcpy(A, B, size);
        //for (uint32_t i = 0; i < size; i += 1) {
        //    A[i] = B[i];
        //}
        reset(&stats);
    }
    if (member_set(SHELL, s)) {
        //uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
        //for (uint32_t i = 0; i < size; i += 1) {
        //	A[i] = random() & (((long) 1 << (30)) - 1);
        //}
        //memcpy(A, B, size);
	srandom(seed);
	uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
    	for (uint32_t i = 0; i < size; i += 1) {
        	A[i] = random() & (((long) 1 << (30)) - 1);
    	}
        shell_sort(&stats, A, size);
        printf("Shell Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
            stats.moves, stats.compares);
        if (elements > 0) {
            for (uint32_t i = 0; i < elements; i += 1) {
                printf("%13" PRIu32, A[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }
        }
        //free(A);
        //memcpy(A, B, size);
        //for (uint32_t i = 0; i < size; i += 1) {
        //    A[i] = B[i];
        //}
        reset(&stats);
    }
    if (member_set(INSERTION, s)) {
        //uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
        //for (uint32_t i = 0; i < size; i += 1) {
        //	A[i] = random() & (((long) 1 << (30)) - 1);
        //}
        //memcpy(A, B, size);
        srandom(seed);
	uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
    	for (uint32_t i = 0; i < size; i += 1) {
        	A[i] = random() & (((long) 1 << (30)) - 1);
    	}

	insertion_sort(&stats, A, size);
        printf("Insertion Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
            stats.moves, stats.compares);
        if (elements > 0) {
            for (uint32_t i = 0; i < elements; i += 1) {
                printf("%13" PRIu32, A[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }
        }
        //for (uint32_t i = 0; i < size; i += 1) {
        //    A[i] = B[i];
        //}
        //free(A);
        //memcpy(A, B, size);
        reset(&stats);
    }
    if (member_set(QUICK, s)) {
        //uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
        //for (uint32_t i = 0; i < size; i += 1) {
        //	A[i] = random() & (((long) 1 << (30)) - 1);
        //}
        //memcpy(A,B, size);
	srandom(seed);
	uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
    	for (uint32_t i = 0; i < size; i += 1) {
        	A[i] = random() & (((long) 1 << (30)) - 1);
    	}


	quick_sort(&stats, A, size);
        printf("Quick Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
            stats.moves, stats.compares);
        if (elements > 0) {
            for (uint32_t i = 0; i < elements; i += 1) {
                printf("%13" PRIu32, A[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }
        }
        //free(A);
        //memcpy(A, B, size);
        reset(&stats);
    }
    free(A);
    return 0;
}
