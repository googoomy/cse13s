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
#include <sys/stat.h>

#define OPTIONS "hi:o:v"

static int input_file = 0;
static int output_file = 0;

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
        return 0;
    }
    if (i_flag == false) {
        input_file = STDIN_FILENO;
    } else {
        input_file = open(in, O_RDONLY);
    }
    if (o_flag == false) {
        output_file = STDOUT_FILENO;
    } else {
        output_file = open(out, O_WRONLY | O_CREAT);
    }

    uint8_t buf[BLOCK] = { 0 };
    uint32_t count = 0;
    int byte = 0;
    uint64_t *histogram = (uint64_t *) calloc(ALPHABET, sizeof(uint64_t));
    //increment element 0 and element 255 by 1 so at the very minimum the histogram will have two elements present
    histogram[0] += 1;
    histogram[255] += 1;
    //construct the histogram while also keeping track of how many unique characters there are
    while ((byte = read(input_file, buf, BLOCK)) > 0) {
        for (int i = 0; i < byte; i += 1) {
            histogram[buf[i]] += 1;
            if (histogram[buf[i]] == 1) {
                count += 1;
            }
        }
    }

    //construct the huffman tree with the histogram
    Node *huffman_tree_root = build_tree(histogram);
    //construct a code table by traversing the huffman tree
    Code table[ALPHABET];
    build_codes(huffman_tree_root, table);
    //construct a header
    Header header;
    header.magic = MAGIC;
    struct stat sbuf;
    fstat(input_file, &sbuf);
    fchmod(output_file, sbuf.st_mode);
    header.permissions = sbuf.st_mode;
    header.tree_size = (3 * count) - 1;
    header.file_size = sbuf.st_size;
    //write the constructed header to outfile
    write_bytes(output_file, (uint8_t *) &header, sizeof(Header));
    //write the constructed huffman tree to outfile using dump_tree()
    dump_tree(output_file, huffman_tree_root);
    //starting at the beginning of infile, write the corresponding code for each symbol
    //to outfile with write_code(). when finished with all the symbols, make sure to flush
    //any remaining buffered codes with flush_codes()
    //go back to the beginning of the input_file:
    lseek(input_file, 0, SEEK_SET);
    uint8_t buff[BLOCK] = { 0 };
    uint32_t bytes = 0;
    while ((bytes = read_bytes(input_file, buff, BLOCK)) > 0) {
        for (uint32_t i = 0; i < bytes; i += 1) {
            write_code(output_file, &table[buff[i]]);
        }
    }
    flush_codes(output_file);
    free(histogram);
    delete_tree(&huffman_tree_root);
    //close infile and outfile
    close(output_file);
    close(input_file);
}
