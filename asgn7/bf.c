#include "bf.h"
#include "bv.h"
#include "salts.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t count = 0;

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
};

//The constructor for a Bloom Filter. The primary, secondary, and tertiary salts that should be used are provided in salts.h
BloomFilter *bf_create(uint32_t size){
	BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
	bf->filter = bv_create(size);
	bf->primary[0] = SALT_PRIMARY_LO;
	bf->primary[1] = SALT_PRIMARY_HI;
	bf->secondary[0] = SALT_SECONDARY_LO;
	bf->secondary[1] = SALT_SECONDARY_HI;
	bf->tertiary[0] = SALT_TERTIARY_LO;
	bf->tertiary[1] = SALT_TERTIARY_HI;
	return bf;
}

//The destructor for a Bloom Filter. 
void bf_delete(BloomFilter **bf){
	if(*bf && (*bf)->filter){
		bv_delete((*bf)->filter);
		free(*bf);
		*bf = NULL;
	}
}

//returns the size of the Bloom Filter
uint32_t bf_size(BloomFilter *bf){
	return bv_length(bf->filter);
}

//This function takes oldspeak and insertes it into the Bloom filter.
void bf_insert(BloomFilter *bf, char *oldspeak){
	uint32_t bit;
	bit = hash(primary, oldspeak);
	bv_set_bit(bf->filter, bit);
	bit = hash(secondary, oldspeak);
	bv_set_bit(bf->filter, bit);
	bit = hash(tertiary, oldspeak);
	bv_set_bit(bf->filter, bit);
	count += 1;
}

//This function probes the Bloom Filter for oldspeak. If all bits at the indices are set, return true, else return false.
bool bf_probe(BloomFilter *bf, char *oldspeak){
	uint32_t bit;
	bool all_three_set = false;
	bit = hash(primary, oldspeak);
	bool is_primary_set = bv_get_bit(bf->filter, bit);
	bit = hash(secondary, oldspeak);
	bool is_secondary_set = bv_get_bit(bf->filter, bit);
	bit = hash(tertiary, oldspeak);
	bool is_tertiary_set = bv_get_bit(bf->filter, bit);
	if(is_primary_set == true && is_secondary_set == true && is_tertiary_set == true){
		all_three_set = true;
	}
	return all_three_set;
}

//This function returns the number of set bits in the Bloom filter.
uint32_t bf_count(BloomFilter *bf){
	return count;
}

void bf_print(BLoomFilter *bf);

