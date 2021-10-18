#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//users can input these into the command line
#define OPTIONS "aeisqr:n:p:h"

//these are teh different types of sorts available in this test harness
typedef enum { INSERTION, SHELL, HEAP, QUICK, NUM_SORTS } Sorts;

int main(int argc, char **argv) {
    //the instructions to run which sorts are stored in set s
    Set s = empty_set();
    int opt = 0;
    //the default seed if the user doesn't put in anything is 13371453
    uint32_t seed = 13371453;
    //the default size of the array is 100
    uint32_t size = 100;
    //the default elements displayed is 100
    uint32_t elements = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        //when the user selects -a all sorts will be ran
        case 'a':
            s = insert_set(INSERTION, s);
            s = insert_set(SHELL, s);
            s = insert_set(HEAP, s);
            s = insert_set(QUICK, s);
            break;
        //-e -i -s and -q specifies the sort the user wants to see be ran
        case 'e': s = insert_set(HEAP, s); break;
        case 'i': s = insert_set(INSERTION, s); break;
        case 's': s = insert_set(SHELL, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        //-r seed lets the user determine the random seed the program is running under
        case 'r': seed = strtoul(optarg, NULL, 10); break;
        //-n size lets the user determine the array size
        case 'n': size = strtoul(optarg, NULL, 10); break;
        //-p elements lets the user decide the amount of elements being displayed
        case 'p':
            elements = strtoul(optarg, NULL, 10);
            //printf("size %u\n", elements);
            break;
        //-h will tell the user about the program
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
    //set the seed so random elements can be stored in array
    srandom(seed);
    //stats for moves and comparisons are needed to be displayed in the output
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;
    //if the size given is less than the elements given then just display the entire array
    if (size < elements) {
        elements = size;
    }
    //create an array of random elements that are bit masked
    uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
    for (uint32_t i = 0; i < size; i += 1) {
        A[i] = random() & (((long) 1 << (30)) - 1);
    }

    //if -h
    if (member_set(HEAP, s)) {
        //run the sort
        heap_sort(&stats, A, size);
        //display the statistics
        printf("Heap Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
            stats.moves, stats.compares);
        if (elements > 0) {
            for (uint32_t i = 0; i < elements; i += 1) {
                printf("%13" PRIu32, A[i]);
                if ((i + 1) % 5 == 0 || elements - (i + 1) == 0) {
                    printf("\n");
                }
            }
        }
        //reset stats for other sorts
        reset(&stats);
    }
    if (member_set(SHELL, s)) {
        //reset the array to how it was unsorted
        srandom(seed);
        uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
        for (uint32_t i = 0; i < size; i += 1) {
            A[i] = random() & (((long) 1 << (30)) - 1);
        }

        //run sort
        shell_sort(&stats, A, size);
        //display the statistics
        printf("Shell Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
            stats.moves, stats.compares);
        if (elements > 0) {
            for (uint32_t i = 0; i < elements; i += 1) {
                printf("%13" PRIu32, A[i]);
                if ((i + 1) % 5 == 0 || elements - (i + 1) == 0) {
                    printf("\n");
                }
            }
        }
        //reset the stats
        reset(&stats);
    }
    if (member_set(INSERTION, s)) {
        //reset the array to unsorted
        srandom(seed);
        uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
        for (uint32_t i = 0; i < size; i += 1) {
            A[i] = random() & (((long) 1 << (30)) - 1);
        }

        //run the insert sort
        insertion_sort(&stats, A, size);
        //print the statistics
        printf("Insertion Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
            stats.moves, stats.compares);
        if (elements > 0) {
            for (uint32_t i = 0; i < elements; i += 1) {
                //display the sorted array with columns of 5
                printf("%13" PRIu32, A[i]);
                if ((i + 1) % 5 == 0 || elements - (i + 1) == 0) {
                    printf("\n");
                }
            }
        }
        //reset teh stats
        reset(&stats);
    }
    if (member_set(QUICK, s)) {
        //reset teh array to unsorted
        srandom(seed);
        uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
        for (uint32_t i = 0; i < size; i += 1) {
            A[i] = random() & (((long) 1 << (30)) - 1);
        }

        //run quick sort
        quick_sort(&stats, A, size);
        //display the statistics
        printf("Quick Sort, %u elements, %" PRIu64 " moves, %" PRIu64 " compares\n", size,
            stats.moves, stats.compares);
        if (elements > 0) {
            for (uint32_t i = 0; i < elements; i += 1) {
                printf("%13" PRIu32, A[i]);
                if ((i + 1) % 5 == 0 || elements - (i + 1) == 0) {
                    printf("\n");
                }
            }
        }
        //reset the stats
        reset(&stats);
    }

    //free up A
    free(A);
    return 0;
}
