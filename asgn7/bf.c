#include "bf.h"
#include "bv.h"
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
};

BloomFilter *bf_create(uint32_t size){
	BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
	bf->filter = bv_create(size);
	bf->primary[0] = SALT_PRIMARY_LO;
	bf->primary[1] = SALT_PRIMARY_HI;
	bf->secondary[0] = SALT_SECONDARY_LO;
	bf->secondary[1] = SALT_SECONDARY_HI;
	bf->tertiary[0] = SALT_TERTIARY_LO;
	bf->tertiary[1] = SALT_TERTIARY_HI;
}
