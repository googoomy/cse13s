#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node Node;

/*
struct Node {
	//Pointer to left chile
	Node *left;
	//Pointer to right child
	Node *right;
	//Node's symbol
	uint8_t symbol;
	//frequency of symbol
	uint64_t frequency;	
};
*/

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

void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
}

Node *node_join(Node *left, Node *right) {
    Node *parent = node_create('$', left->frequency + right->frequency);
    parent->left = left;
    parent->right = right;
    return parent;
}

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
