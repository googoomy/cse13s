#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"
#include <gmp.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters){
	mpz_t p;
	mpz_init(p);
	mpz_t pbits;
	mpz_init(pbits);
	mpz_t r2;
	mpz_init(r2);
	mpz_t r;
	mpz_init(r);
	mpz_t r3;
	mpz_init(r3);
	mpz_ui_pow_ui(r3, 2, nbits);
	while(mpz_cmp(n, r3) > 0 || mpz_cmp(n, r3) == 0){
		mpz_fdiv_ui(r, nbits, 2);
		mpz_urandomm(pbits, state, r);
		mpz_fdiv_ui(r, nbits, 4);
		mpz_add(r, pbits, r2);
		mpz_set(pbits, r);
	}
	make_prime(p, pbits, iters);
	mpz_t q;
	mpz_init(q);
	make_prime(q, nbits-pbits, iters);
	mpz_t totient;
	mpz_init(totient);
	mpz_sub_ui(r, p, 1);
	mpz_sub_ui(r2, q, 1);
	mpz_mul(totient, r, r2);
	while(true){
		mpz_urandomb(e, state, nbits);
		gcd(r, e, totient);
		if(mpz_comp_ui(r, 1) == 0){
			break;
		}
	}
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile){
	
}
