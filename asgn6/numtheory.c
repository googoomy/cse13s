#include "numtheory.h"
#include "randstate.h"
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//gmp functions were found from the gmplib.org's manual page

//this function computes the greatest common divisor between a and b and storing it in d
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t a_temp;
    mpz_t b_temp;
    mpz_t temp;
    mpz_t r;
    //initializing the variables
    mpz_init(a_temp);
    mpz_init(b_temp);
    mpz_init(temp);
    mpz_init(r);
    //setting the variables
    mpz_set(a_temp, a);
    mpz_set(b_temp, b);
    //this while loop pseudo code was given in the asgn6 pdf
    //the comparison is supposed to be while(b!=0) but mpz_cmp_ui returns a positive if it is greater and negative if it is less than so
    //i need a greater than 0 or less than 0
    while (mpz_cmp_ui(b_temp, 0) > 0 || mpz_cmp_ui(b_temp, 0) < 0) {
        //Set t to b
        mpz_set(temp, b_temp);
        //a mod b
        mpz_mod(r, a_temp, b_temp);
        //Set b to a mod b
        mpz_set(b_temp, r);
        //set a to t
        mpz_set(a_temp, temp);
    }
    //set d to a
    mpz_set(d, a_temp);
    //clear variables
    mpz_clear(a_temp);
    mpz_clear(b_temp);
    mpz_clear(temp);
    mpz_clear(r);
    return;
}

//this function computes the inverse i of a modulo n and if a mod inverse cant be found i will be set 0.
//this function's pseudocode wsa given in the asgn6 pdf
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r;
    mpz_t r_prime;
    mpz_t t;
    mpz_t t_prime;
    mpz_t q;
    mpz_t result;
    mpz_t result2;
    //initializing the variables
    mpz_init(r);
    mpz_init(r_prime);
    mpz_init(t);
    mpz_init(t_prime);
    mpz_init(q);
    mpz_init(result);
    mpz_init(result2);
    //setting the variables
    mpz_set(r, n);
    mpz_set(r_prime, a);
    mpz_set_ui(t, 0);
    mpz_set_ui(t_prime, 1);
    //same while loop conditions as gcd()
    while (mpz_cmp_ui(r_prime, 0) > 0 || mpz_cmp_ui(r_prime, 0) < 0) {
        //q = floor(r/r')
        mpz_fdiv_q(result, r, r_prime);
        mpz_set(q, result);
        //(r, r') = (r', r-q*r')
        mpz_mul(result, q, r_prime);
        mpz_sub(result2, r, result);
        mpz_set(r, r_prime);
        mpz_set(r_prime, result2);
        //(t, t') = (t', t-q*t')
        mpz_mul(result, q, t_prime);
        mpz_sub(result2, t, result);
        mpz_set(t, t_prime);
        mpz_set(t_prime, result2);
    }
    //if r > 1 no inverse
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set(i, 0);
    }
    //if t < 0 add n
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
        mpz_set(i, t);
    }
    //clear variables
    mpz_clear(r);
    mpz_clear(r_prime);
    mpz_clear(t);
    mpz_clear(t_prime);
    mpz_clear(q);
    mpz_clear(result);
    mpz_clear(result2);
    return;
}

//This function performs a fast modular exponentiation computing base raised to the exponent power modulo modulus and storing the computed result in out
//this function's psuedocode wss given in the asgn6 pdf
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    //initiailization and setting of the variables
    mpz_t p;
    mpz_init_set(p, base);
    mpz_t v;
    mpz_init_set_ui(v, 1);
    mpz_t d;
    mpz_init_set(d, exponent);
    mpz_t r;
    mpz_t r2;
    //while loop with conditions (d > 0)
    while (mpz_cmp_ui(d, 0) > 0) {
        //if d is odd
        mpz_mod_ui(r, d, 2);
        if (mpz_cmp_ui(r, 0) > 0) {
            //set v to (v*p) mod n
            mpz_mul(r, v, p);
            mpz_mod(r2, r, modulus);
            mpz_set(v, r2);
        }
        //set p to (p*p) mod n
        mpz_mul(r, p, p);
        mpz_mod(r2, r, modulus);
        mpz_set(p, r2);
        //set d to floor(d/2)
        mpz_fdiv_q_ui(r, d, 2);
        mpz_set(d, r);
    }
    //set out to v
    mpz_set(out, v);
    //clear variables
    mpz_clear(p);
    mpz_clear(v);
    mpz_clear(d);
    mpz_clear(r);
    mpz_clear(r2);
    return;
}

//this function conducts the miller-rabin primality test to indicate whether or not n is prime using iters number of miller-rabin iterations.
bool is_prime(mpz_t n, uint64_t iters) {
    if (mpz_cmp_ui(n, 1)) {
        return false;
    }
    if (mpz_cmp_ui(n, 2)) {
        return true;
    }
    if (mpz_cmp_ui(n, 3)) {
        return true;
    }
    if (mpz_cmp_ui(n, 4)) {
        return false;
    }
    mpz_t result;
    mpz_t result2;
    mpz_t result3;
    mpz_init(result3);
    mpz_init(result2);
    mpz_init(result);
    mpz_mod_ui(result, n, 2);
    if (mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(result, 0) == 0) {
        mpz_clear(result);
        mpz_clear(result2);
        mpz_clear(result3);
        return false;
    }
    mpz_t r;
    mpz_init(r);
    mpz_sub_ui(r, n, 1);
    mpz_t s;
    mpz_init(s);
    mpz_set_ui(s, 0);
    uint32_t int_s = 0;
    mpz_set_ui(result, 2);
    mpz_t base;
    mpz_init_set_ui(base, 2);
    while (true) {
        mpz_pow_ui(result2, base, int_s);
        mpz_mul(result3, result2, r);
        mpz_add_ui(result, result3, 1);
        if (mpz_cmp(n, result) == 0) {
            break;
        }
        mpz_fdiv_q_ui(result, r, 2);
        mpz_set(r, result);
        mpz_add_ui(result, s, 1);
        mpz_set(s, result);
        int_s += 1;
    }
    bool return_bool = true;
    for (uint64_t i = 1; i < iters; i += 1) {
        mpz_t n_rand;
        mpz_init(n_rand);
        mpz_sub_ui(n_rand, n, 4);
        mpz_t a;
        mpz_init(a);
        mpz_urandomm(result, state, n_rand);
        mpz_set(a, result);
        mpz_add_ui(result, a, 2);
        mpz_set(a, result);
        mpz_t y;
        pow_mod(y, a, r, n);
        mpz_sub_ui(result, n, 1);
        if ((mpz_cmp_ui(y, 1) < 0 || mpz_cmp_ui(y, 1) > 0)
            && (mpz_cmp(y, result) < 0 || mpz_cmp(y, result) > 0)) {
            mpz_t j;
            mpz_init_set_ui(j, 1);
            mpz_sub_ui(result2, s, 1);
            while ((mpz_cmp(j, result2) < 0 || mpz_cmp(j, result2) == 0)
                   && (mpz_cmp(y, result) < 0 || mpz_cmp(y, result) > 0)) {
                pow_mod(result3, y, base, n);
                mpz_set(y, result3);
                if (mpz_cmp_ui(y, 1) == 0) {
                    return_bool = false;
                    mpz_clear(j);
                    mpz_clear(a);
                    mpz_clear(y);
                    mpz_clear(n_rand);
                    break;
                }
                mpz_add_ui(result3, j, 1);
                mpz_set(j, result3);
            }
            if (mpz_cmp(y, result) < 0 || mpz_cmp(y, result) > 0) {
                return_bool = false;
            }
        }
    }
    mpz_clear(base);
    mpz_clear(result);
    mpz_clear(result2);
    mpz_clear(result3);
    mpz_clear(s);
    mpz_clear(r);
    return return_bool;
}

//this function generates a new prime number stored in p. the generated prime should be at least bits number of bits long.
//the primality of the generated number should be tested using is_prime() with iters iterations
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t prime;
    mpz_init(prime);
    //while(!is_prime(prime, iters) || mpz_cmp_ui(prime, bits) < 0){
    while (true) {
        mpz_t r;
        mpz_init(r);
        mpz_urandomb(r, state, bits);
        mpz_set(prime, r);
        if (is_prime(prime, iters) && mpz_cmp_ui(prime, bits) > 0) {
            mpz_clear(r);
            break;
        }
    }
    mpz_set(p, prime);
    mpz_clear(prime);
    return;
}
