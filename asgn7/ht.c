#include "ht.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//the following struct defines the HashTable ADT
//this was given in the assignment 7 pdf
struct HashTable {
	uint64_t salt[2];
	uint32_t size;
	Node **trees;
};

//This function is the constructor for a Hash Table.
HashTable *ht_create(uint32_t size){
	HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
	ht->size = size;
	ht->salt[0] = SALT_HASHTABLE_LO;
	ht->salt[1] = SALT_HASHTABLE_HI;
}

void ht_delete(HashTable **ht){
	for(uint32_t i = 0; i < size; i += 1){
		node_delete(*ht->*trees[i]);
	}

}
