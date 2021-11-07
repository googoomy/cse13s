#include "defines.h"
#include "header.h"
#include "node.h"
#include "pq.h"
#include "code.h"
#include "io.h"
#include "stack.h"
#include "huffman.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define OPTIONS "hi:o:v"

static FILE *input_file = NULL;
static FILE *output_file = NULL;

int main(int argc, char **argv) {
    int opt = 0;
    bool no_input_flag = true;
    bool h_flag = false;
    bool i_flag = false;
    bool o_flag = false;
    bool v_flag = false;
    char *in = NULL;
    char *out = NULL;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input_flag = false;
        switch (opt) {
        case 'i':
            i_flag = true;
            in = optarg;
            break;
        case 'o':
            o_flag = true;
            out = optarg;
            break;
        case 'v': v_flag = true; break;
        case 'h':
            i_flag = false;
            o_flag = false;
            v_flag = false;
            h_flag = true;
            break;
        }
    }
    if (h_flag == true || no_input_flag == true) {
        printf("SYNOPSIS\n");
        printf("  A Huffman encoder.\n");
        printf("  Compresses a file using the Huffman coding algorithm.\n\n");
        printf("USAGE\n");
        printf("  ./encode [-h] [-i infile] [-o outfile]\n\n");
        printf("OPTIONS\n");
        printf("  -h             Program usage and help.\n");
        printf("  -v             Print compression statistics.\n");
        printf("  -i infile      Input file to compress.\n");
        printf("  -o outfile     Ouput of compressed data.\n");
    }
    if (i_flag == false) {
        input_file = stdin;
    } else {
        input_file = fopen(in, "r");
    }
    if (o_flag == false) {
        output_file = stdout;
    } else {
        output_file = fopen(out, "w+");
    }
}
