#include "huffman.h"
#include "io.h"
#include "node.h"
#include "code.h"
#include "defines.h"
#include "pq.h"
#include "stack.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

//This build tree function is based on the pseudocode provided by TA Eugene
Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *q = pq_create(ALPHABET);
    for (uint32_t i = 0; i < ALPHABET; i += 1) {
        Node *n = node_create(i, hist[i]);
        enqueue(q, n);
    }
    while (pq_size(q) >= 2) {
        Node *left;
        Node *right;
        Node *parent;
        dequeue(q, &left);
        dequeue(q, &right);
        parent = node_join(left, right);
        enqueue(q, parent);
    }
    Node *root;
    dequeue(q, &root);
    pq_delete(&q);
    return root;
}

//This build codes function is based on the pseudocode provided by TA Eugene
//static Code c = code_init();
void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    if (root != NULL) {
        //check if root is a leaf
        if (root->left == NULL && root->right == NULL) {
            table[root->symbol] = c;
        } else {
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            uint8_t popped_bit;
            code_pop_bit(&c, &popped_bit);
            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, &popped_bit);
        }
    }
}

void dump_tree(int outfile, Node *root) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            write_bytes(outfile, (uint8_t *) "L", 1);
            write_bytes(outfile, (uint8_t *) &root->symbol, 1);
        } else {
            dump_tree(outfile, root->left);
            dump_tree(outfile, root->right);
            write_bytes(outfile, (uint8_t *) "I", 1);
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    Stack *s = stack_create(MAX_TREE_SIZE);
    for (uint8_t i = 0; i < nbytes; i += 1) {
        if (tree_dump[i] == 'L') {
            i += 1;
            Node *n = node_create(tree_dump[i], 0);
            stack_push(s, n);
        } else {
            Node *left;
            Node *right;
            stack_pop(s, &left);
            stack_pop(s, &right);
            Node *parent = node_join(left, right);
            stack_push(s, parent);
        }
    }
    Node *root;
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}

void delete_tree(Node **root) {
    if ((*root)->left == NULL && (*root)->right == NULL) {
        node_delete(root);
    } else {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        node_delete(root);
    }
}
