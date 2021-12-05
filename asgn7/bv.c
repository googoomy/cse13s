#include "bv.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//the following struct defines the bit vector ADT
//this was given in the assignment 7 pdf
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

//This function is the constructor for bit vector.
BitVector *bv_create(uint32_t length) {
    //BitVector *bv = (BitVector *) calloc(length, sizeof(BitVector));
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    //if there is insufficient memory, return NULL
    if (bv == NULL) {
        return NULL;
    }
    bv->length = length;
    //trying to do ceiling of length/8 but without importing math.h
    uint32_t ceiling_of_vector_size = (length + 8 - 1) / 8;
    uint8_t(bv->vector)[ceiling_of_vector_size] = { 0 };
    return *bv;
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < sizeof(bv->vector); i += 1) {
        printf("%" PRIu8 "\n", bv->vector[i]);
    }
}

//This function is the destructor for bit vector.
void bv_delete(BitVector **bv) {
    if (*bv) {
        free(*bv);
        *bv = NULL;
    }
}

//This function returns the length of a bit vector
uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

//This function sets the ith bit in the bit vector to 1. It returns trrue if it was successful and false if not.
//This function is based off of my code_set_bit function in code.c in assignment 5
bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i < length) {
        bv->vector[i / 8] = 1;
        return true;
    }
    return false;
}

//this function clears the ith bit in the bit vector to 0. It returns true if it was successful and false if not.
//This function is based off of my code_clr_bit function in code.c in assignment 5
bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i < length) {
        bv->vector[i / 8] = 0;
        return true;
    }
    return false;
}

//This function returns the ith bit in the bit vector. if the ith bit is out of range or 0 return false. If the ith bit is 1 return true.
bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i < length) {
        if (bv->vector[i / 8] == 0) {
            return false;
        }
        return true;
    }
    return false;
}
