#include "bst.h"
#include "node.h"
#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t branches;
//This function is the constructor for bst
Node *bst_create(void) {
    return NULL;
}

//This function is the deconstructor for bst
////This implementation is based off of the pseudocode provided by TA Christian
void bst_delete(Node **root) {
    if ((*root)->left != NULL) {
        bst_delete(&(*root)->left);
    }
    if ((*root)->right != NULL) {
        bst_delete(&(*root)->right);
    }
    node_delete(root);
}

//This function returns the height of the binary search tree rooted at root.
//This implementation is based off of the pseudocode provided by TA Christian
uint32_t bst_height(Node *root) {
    uint32_t height = 0;
    if (root == NULL) {
        return 0;
    } else {
        if (bst_height(root->right) > bst_height(root->left)) {
            return bst_height(root->right) + 1;
        } else {
            return bst_height(root->left) + 1;
        }
        //height += 1;
    }
    return height;
}

//This function returns the size of the binary search tree rooted at root.
//This implementation is based off of the pseudocode provided by TA Christian
uint32_t bst_size(Node *root) {
    uint32_t size = 0;
    if (root == NULL) {
        return 0;
    } else {
        size += bst_size(root->left);
        size += bst_size(root->right);
        size += 1;
    }
    return size;
}

//This function searches for a node containing oldspeak in the bst rooted at root
//This implementation is based on the implementation of bst_insert below
Node *bst_find(Node *root, char *oldspeak) {
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(root->oldspeak, oldspeak) > 0) {
        return bst_find(root->left, oldspeak);
    } else if (strcmp(root->oldspeak, oldspeak) < 0) {
        return bst_find(root->right, oldspeak);
    } else {
        return root;
    }
}

//This function inserts a new node containing the specified oldspeak and newspeak into the binary search tree rooted at root.
//The pseudocode for this function was given by TA Eugene
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root == NULL) {
        return node_create(oldspeak, newspeak);
    }
    if (strcmp(root->oldspeak, oldspeak) > 0) {
        return root->left = bst_insert(root->left, oldspeak, newspeak);
    } else if (strcmp(root->oldspeak, oldspeak) < 0) {
        return root->right = bst_insert(root->right, oldspeak, newspeak);
    } else {
        return root;
    }
}

//This function prints out the bst
//This implementation is based off of the inorder_print() from page 8 of the Lecture 18 Slides
void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}
