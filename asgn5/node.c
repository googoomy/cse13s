#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node Node;

//constructor for node
//pseudocode given by TA Christian
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->left = NULL;
        n->right = NULL;
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

//destructor for node
void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
}

//joins a left and right child to form a parent node
//pseudocode was given by TA Christian
Node *node_join(Node *left, Node *right) {
    Node *parent = node_create('$', left->frequency + right->frequency);
    parent->left = left;
    parent->right = right;
    return parent;
}

//prints node
void node_print(Node *n) {
    printf("%" PRIx8, n->symbol);
    if (n->left != NULL) {
        printf("%" PRIx8, n->left->symbol);
    }
    if (n->right != NULL) {
        printf("%" PRIx8, n->right->symbol);
    }
    printf("%" PRIu64, n->frequency);
}
