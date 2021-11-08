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
        printf("  A Huffman decoder.\n");
        printf("  Decompresses a file using the Huffman coding algorithm.\n\n");
        printf("USAGE\n");
        printf("  ./decode [-h] [-i infile] [-o outfile]\n\n");
        printf("OPTIONS\n");
        printf("  -h             Program usage and help.\n");
        printf("  -v             Print compression statistics.\n");
        printf("  -i infile      Input file to decompress.\n");
        printf("  -o outfile     Output of decompressed data.\n");
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
    //verify the magic number and print error if it doesnt match
    Header header;
    read(input_file, &header, sizeof(Header));
    if (header.magic != MAGIC) {
        fprintf(stderr, "%s", "Magic number does not match.");
        return 0;
    }
    //the permissions field in the header indicates the permissions that outfile should be set to. Set the permissions using fchmod()
    fchmod(output_file, header.permissions);
    //reconstruct the huffman tree with rebuild_tree()
    int nbytes = (int) header.tree_size;
    uint8_t tree_dump[nbytes];
    read_bytes(input_file, tree_dump, nbytes);
    Node *original_root = rebuild_tree(nbytes, tree_dump);
    //read infile one bit at a time using read_bit
    //uint8_t buff[BLOCK] = {0};
    Node *complete_tree = original_root;
    uint8_t bit = 0;
    uint64_t num_symbols = 0;
    while (num_symbols < header.file_size) {
        read_bit(input_file, &bit);
        if (bit == 0) {
            complete_tree = complete_tree->left;
        } else {
            complete_tree = complete_tree->right;
        }
        //if you find yourself at a leaf node, write the leaf node's symbol to outfile
        if (complete_tree->left == NULL && complete_tree->right == NULL) {
            write_bytes(output_file, &complete_tree->symbol, 1);
            complete_tree = original_root;
        }
    }
    //close infile and outfile
    delete_tree(&original_root);
    close(input_file);
    close(output_file);
}
