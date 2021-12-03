#include "bst.h"
#include "node.h"
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Node *bst_create(void){
	return NULL;
}

void bst_delete(Node **root){

}

uint32_t bst_height(Node *root){

}

uint32_t bst_size(Node *root){

}

Node *bst_find(Node *root, char *oldspeak){

}

//This function inserts a new node containing the specified oldspeak and newspeak into the binary search tree rooted at root.
//The pseudocode for this function was given by TA Eugene
Node *bst_insert(Node *root, char *oldspeak, char *newspeak){
	if(root == NULL){
		return node_create(oldspeak, newspeak);
	}
	if(strcmp(root->oldspeak, oldspeak) > 0){
		root->left = bst_insert(root->left, oldspeak, newspeak);
	}else if(strcmp(root->oldspeak, oldspeak) < 0){
		root->right = bst_insert(root->right, oldspeak, newspeak);
	}else{
		return root;
	}
}

void bst_print(Node *root){

}
