#include "bf.h"
#include "bv.h"
#include "speck.h"
#include "salts.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//the following struct defines the BloomFilter ADT
//this was given in the assignment 7 pdf
struct BloomFilter {
    //Primary hash function salt.
    uint64_t primary[2];
    //Secondary hash function salt.
    uint64_t secondary[2];
    //Tertiary hash function salt.
    uint64_t tertiary[2];
    BitVector *filter;
    uint32_t count;
};

//The constructor for a Bloom Filter. The primary, secondary, and tertiary salts that should be used are provided in salts.h
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    bf->filter = bv_create(size);
    bf->count = 0;
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;
    return bf;
}

//The destructor for a Bloom Filter.
void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
}

//returns the size of the Bloom Filter
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

//This function takes oldspeak and insertes it into the Bloom filter.
void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t bit;
    bit = hash(bf->primary, oldspeak) % bf_size(bf);
    //if the bit is already 1 then dont increase the count
    if (!bv_get_bit(bf->filter, bit)) {
        bf->count += 1;
    }
    //set the bit to 1
    bv_set_bit(bf->filter, bit);
    bit = hash(bf->secondary, oldspeak) % bf_size(bf);
    if (!bv_get_bit(bf->filter, bit)) {
        bf->count += 1;
    }
    bv_set_bit(bf->filter, bit);
    bit = hash(bf->tertiary, oldspeak) % bf_size(bf);
    if (!bv_get_bit(bf->filter, bit)) {
        bf->count += 1;
    }
    bv_set_bit(bf->filter, bit);
}

//This function probes the Bloom Filter for oldspeak. If all bits at the indices are set, return true, else return false.
//This implementation is based off of TA Eugene's pseudocode
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t index1 = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t index2 = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t index3 = hash(bf->tertiary, oldspeak) % bf_size(bf);
    if (bv_get_bit(bf->filter, index1) == true && bv_get_bit(bf->filter, index2) == true
        && bv_get_bit(bf->filter, index3) == true) {
        return true;
    }
    return false;
}

//This function returns the number of set bits in the Bloom filter.
uint32_t bf_count(BloomFilter *bf) {
    return bf->count;
}

//This function prints out the bloomfilter
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
