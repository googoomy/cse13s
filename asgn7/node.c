#include "node.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is the constructor for node
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        char *old_copy = strdup(oldspeak);
        if (newspeak != NULL) {
            char *new_copy = strdup(newspeak);
            n->newspeak = new_copy;
        } else {
            n->newspeak = NULL;
        }
        n->oldspeak = old_copy;
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}

//This function is the destructor for node
void node_delete(Node **n) {
    if (*n) {
        free((*n)->oldspeak);
        if ((*n)->newspeak) {
            free((*n)->newspeak);
        }
        free(*n);
        *n = NULL;
    }
}

//This function prints out the node
void node_print(Node *n) {
    if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    if (n->oldspeak != NULL && n->newspeak == NULL) {
        printf("%s\n", n->oldspeak);
    }
}
