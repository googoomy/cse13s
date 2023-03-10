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

static FILE *badspeak_file;
static FILE *newspeak_file;
//initialize externs
uint64_t lookups = 0;
uint64_t branches = 0;

int main(int argc, char **argv) {
    int opt = 0;
    bool h_flag = false;
    bool t_flag = false;
    bool f_flag = false;
    bool s_flag = false;
    char *badspeak = "badspeak.txt";
    char *newspeak = "newspeak.txt";
    uint32_t ht_size = HASH_TABLE_DEFAULT_SIZE;
    uint32_t bf_size = BLOOM_FILTER_DEFAULT_SIZE;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't':
            t_flag = true;
            ht_size = strtoul(optarg, NULL, 10);
            break;
        case 'f':
            f_flag = true;
            bf_size = strtoul(optarg, NULL, 10);
            break;
        case 's': s_flag = true; break;
        case 'h': h_flag = true; break;
        }
    }
    //if help is initiated
    if (h_flag) {
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
    //Initialize bf and ht
    BloomFilter *bloom = bf_create(bf_size);
    HashTable *hasht = ht_create(ht_size);
    //Read in a list of badspeak words with fscanf()
    badspeak_file = fopen(badspeak, "r");
    newspeak_file = fopen(newspeak, "r");
    //char buffer[1024];
    while (!feof(badspeak_file)) {
        char *curr_badspeak = "";
        fscanf(badspeak_file, "%s\n", curr_badspeak);
        bf_insert(bloom, curr_badspeak);
        ht_insert(hasht, curr_badspeak, NULL);
    }
    //Read in a list of oldspeak and newspeak pairs with scanf()
    while (!feof(newspeak_file)) {
        char *curr_oldspeak = "";
        char *curr_newspeak = "";
        fscanf(newspeak_file, "%s %s\n", curr_oldspeak, curr_newspeak);
        bf_insert(bloom, curr_oldspeak);
        ht_insert(hasht, curr_oldspeak, curr_newspeak);
    }

    Node *thoughtcrime_bst = bst_create();
    Node *rightspeak_bst = bst_create();

    //compile regex
    regex_t re;
    if (regcomp(&re, WORD_REGEX_STRING, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }
    char *word;
    while ((word = next_word(stdin, &re)) != NULL) {
        //read in the  words
        if (bf_probe(bloom, word) == true) {
            //if ht contains the word and the word doesnt have a newspeak translation
            if (ht_lookup(hasht, word) != NULL && ht_lookup(hasht, word)->newspeak == NULL) {
                bst_insert(thoughtcrime_bst, word, NULL);
                branches += 1;
                lookups += 2;
            }
            //if ht contains the word and the word does have a newspeak translation
            if (ht_lookup(hasht, word) != NULL && ht_lookup(hasht, word)->newspeak != NULL) {
                bst_insert(rightspeak_bst, word, ht_lookup(hasht, word)->newspeak);
                branches += 1;
                lookups += 2;
            }
        }
    }
    //uint32_t bbfsize = bf_size(bloom);
    //uint32_t hhtsize = ht_size(hasht);
    if (s_flag) {
        fprintf(stdout, "Average BST size: %.6lf", ht_avg_bst_size(hasht));
        fprintf(stdout, "Average BST height: %.6lf", ht_avg_bst_height(hasht));
        fprintf(stdout, "Average branches traversed: %.6lf", (double) (branches / lookups));
        //fprintf(stdout, "Hash table load: %.6lf", (double) (100 * (ht_count(hasht) / hhtsize)));
        //fprintf(stdout, "Bloom filter load: %.6lf", (double) (100 * (bf_count(bloom) / bbfsize)));
    }
    //mixspeak
    if (thoughtcrime_bst != NULL && rightspeak_bst != NULL) {
        printf("%s", mixspeak_message);
        bst_print(thoughtcrime_bst);
        bst_print(rightspeak_bst);
    }
    //badspeak
    if (thoughtcrime_bst != NULL && rightspeak_bst == NULL) {
        printf("%s", badspeak_message);
        bst_print(thoughtcrime_bst);
    }

    //goodspeak
    if (thoughtcrime_bst == NULL && rightspeak_bst != NULL) {
        printf("%s", goodspeak_message);
        bst_print(rightspeak_bst);
    }

    //clear and free
    bst_delete(&thoughtcrime_bst);
    bst_delete(&rightspeak_bst);
    bf_delete(&bloom);
    ht_delete(&hasht);
    clear_words();
    regfree(&re);
    fclose(badspeak_file);
    fclose(newspeak_file);
}
