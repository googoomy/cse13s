//these includes were given by TA Christian
#include "bf.h"
#include "bst.h"
#include "ht.h"
#include "messages.h"
#include "parser.h"
#include <regex.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//these defines except WORD_REGEX_STRING were given by TA Christian
//valid options for the program
#define OPTIONS "ht:f:s"
//2^16
#define HASH_TABLE_DEFAULT_SIZE 65536
//2^20
#define BLOOM_FILTER_DEFAULT_SIZE 1048576
//the hyphen part was from Eugene's 11/30/21 section
//the apostrophe part is the same as the hyphen part but with ' instead of - and the third section is for the rest of regular words
#define WORD_REGEX_STRING "(([a-zA-Z+-)+[a-zA-Z]+)|(([a-zA-Z]+')+[a-zA-Z]+)|([a-zA-Z]+)"

int main(int argc, char **argv) {
    int opt = 0;
    bool no_input_flag = true;
    bool h_flag = false;
    bool t_flag = false;
    bool f_flag = false;
    bool s_flag = false;
    uint32_t ht_size = HASH_TABLE_DEFAULT_SIZE;
    uint32_t bf_size = BLOOM_FILTER_DEFAULT_SIZE;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input_flag = false;
        switch (opt) {
        case 't':
            t_flag = true;
            ht_size = stroul(optarg, NULL, 10);
            break;
        case 'f':
            f_flag = true;
            bf_size = stroul(optarg, NULL, 10);
            break;
        case 's': s_flag = true; break;
        case 'h': h_flag = true; break;
        }
    }

    if (h_flag || no_input_flag) {
        printf("SYNOPSIS\n");
        printf("  A word filtering program for the GPRSC.\n");
        printf("  Filters out and reports bad words parsed from stdin.\n\n");
        printf("USAGE\n");
        printf("  ./banhammer [-hs] [-t size] [-f size]\n\n");
        printf("OPTIONS\n");
        printf("  -h           Program usage and help.\n");
        printf("  -s           Print program statistics.\n");
        printf("  -t size      Specify hash table size (default: 2^16).\n");
        printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
        return 0;
    }
}
