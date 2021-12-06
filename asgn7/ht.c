#include "ht.h"
#include "node.h"
#include "bst.h"
#include "salts.h"
#include "speck.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t lookups;
//static uint32_t count = 0;
//static uint32_t height_sum = 0;
//static uint32_t size_sum = 0;
//the following struct defines the HashTable ADT
//this was given in the assignment 7 pdf
struct HashTable {
    uint64_t salt[2];
    uint32_t hsize;
    Node **trees;
    uint32_t count;
};

//This function is the constructor for a Hash Table.
//I based this function off of my pq.c from asgn 5
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->count = 0;
        ht->hsize = size;
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;
        ht->trees = (Node **) malloc(size * sizeof(Node *));
        if (ht->trees == NULL) {
            ht_delete(&ht);
        }
    }
    return ht;
}

//This function prints out the contents of a hash table.
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        if (ht->trees[i] != NULL) {
            bst_print(ht->trees[i]);
        }
    }
}

//This function is the destructor for a hash table.
void ht_delete(HashTable **ht) {
    if ((*ht)->trees != NULL) {
        for (uint32_t i = 0; i < (*ht)->hsize; i += 1) {
            if (&(*ht)->trees[i] != NULL) {
                node_delete(&(*ht)->trees[i]);
            }
        }
    }
    free(*ht);
    *ht = NULL;
}

//This function returns the hash table's size
uint32_t ht_size(HashTable *ht) {
    return ht->hsize;
}

//This function searches for a node in the hash table that contains oldspeak.
//If the node is found, the pointer to the node is returned else return NULL
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t bit;
    bit = hash(ht->salt, oldspeak) % ht->hsize;
    return bst_find(ht->trees[bit], oldspeak);
}

//This function inserts the specified oldspeak and its newspeak traslation into the hash table.
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index;
    index = hash(ht->salt, oldspeak) % ht->hsize;
    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
    //ht->count += 1;
    //height_sum += bst_height(ht->trees[index]);
    //size_sum += bst_height(ht->trees[index]);
}

//This function returns the number of non NULL binary search trees in the hash table
uint32_t ht_count(HashTable *ht) {
    //return ht->count;
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        if (ht->trees[i] != NULL) {
            ht->count += 1;
        }
    }
    return ht->count;
}

//This function returns the average binary search tree size which is the sum of the sizes of all bst's divided by the hash table count
double ht_avg_bst_size(HashTable *ht) {
    return (double) (bst_size(ht->trees[0]) / ht_count(ht));
    //return (double)(size_sum/ht_count(ht));
}

//This function returns the average binary search tree height which is the sum of the heights of all bst's divided by the hash table count
double ht_avg_bst_height(HashTable *ht) {
    return (double) (bst_height(ht->trees[0]) / ht_count(ht));
    //return (double)(height_sum/ht_count(ht));
}
