#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <gmp.h>
#include <inttypes.h>
#include <stdlib.h>

//this function creates parts of a new rsa public key
//pseudocode given by the asgn 6 doc
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    //intialization
    uint64_t pbits;
    mpz_t r2;
    mpz_init(r2);
    mpz_t r;
    mpz_init(r);
    mpz_t r3;
    mpz_init(r3);
    mpz_ui_pow_ui(r3, 2, nbits);
    mpz_t mpz_nbits;
    mpz_init_set_ui(mpz_nbits, nbits);
    mpz_mul(n, p, q);
    //determine the num bits for p and q
    while (mpz_cmp(n, r3) > 0 || mpz_cmp(n, r3) == 0) {
        pbits = nbits / 4 + gmp_urandomm_ui(state, nbits / 2);
    }
    //make primes p and q
    make_prime(p, pbits, iters);
    make_prime(q, nbits - pbits, iters);
    //find the totient between p-1 and q-1
    mpz_t totient;
    mpz_init(totient);
    mpz_sub_ui(r, p, 1);
    mpz_sub_ui(r2, q, 1);
    mpz_mul(totient, r, r2);
    //loop and generate random numbers around nbits
    while (true) {
        mpz_urandomb(e, state, nbits);
        gcd(r, e, totient);
        if (mpz_cmp_ui(r, 1) == 0) {
            break;
        }
    }
    //clears;
    mpz_clear(r2);
    mpz_clear(r);
    mpz_clear(r3);
    mpz_clear(totient);
}

//this functionwrites rsa key to pbfile
//gmp_fprintf lines found in the documentation online
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username);
}

//this function reads a public rsa key from pbfile
//gmp_fscanf lines found in the documentation online
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);
}

//creates a new rsa private key d when given p and q and public exponent e
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    //initialization
    mpz_t inverse_e;
    mpz_init(inverse_e);
    mpz_t totient;
    mpz_init(totient);
    mpz_t r;
    mpz_init(r);
    //totient = (p-1)(q-1)
    mpz_sub_ui(r, p, 1);
    mpz_t r2;
    mpz_init(r2);
    mpz_sub_ui(r2, q, 1);
    mpz_mul(totient, r, r2);
    mod_inverse(inverse_e, e, totient);
    mpz_set(d, inverse_e);
    //clears
    mpz_clear(inverse_e);
    mpz_clear(totient);
    mpz_clear(r);
    mpz_clear(r2);
}

//this function writes a private rsa key to pvfile
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

//this function reads a private rsa key from pvfile
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "Zx\n", n);
    gmp_fscanf(pvfile, "Zx\n", d);
}

//performs rsa encryption using c = m^e (mod n)
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

//encrypts the contents of infile
//pseudocode given in the asgn6 pdf
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    //k = floor(log2(n)-1)/8)
    uint32_t k = (int) ((mpz_sizeinbase(n, 2) - 1) / 8);
    //block array
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    //set first element in array to 0xFF
    block[0] = 0xFF;
    char buffer[100];
    //initialization
    mpz_t m;
    mpz_init(m);
    mpz_t c;
    mpz_init(c);
    uint32_t i = 1;
    //loop through the file and encrypt
    while (true) {
        block[i] = fread(buffer, sizeof(uint8_t), k - 1, infile);
        mpz_import(m, i, 1, sizeof(block), 1, 0, block);
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile, "%Zx\n", c);
        i += 1;
        if (feof(infile)) {
            break;
        }
    }
    //clears and frees
    mpz_clear(m);
    mpz_clear(c);
    free(block);
}

//performs rsa decryption using m = c^d(mod n)
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

//decrypts the contents of infile
//pseudocode given from asgn 6 pdf
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    //block size is k = floor(log2(n)-1)/8)
    uint32_t k = (int) ((mpz_sizeinbase(n, 2) - 1) / 8);
    //block array
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    //intialization
    mpz_t c;
    mpz_init(c);
    mpz_t m;
    mpz_init(m);
    size_t i = 1;
    //loop throught the file and decrypt
    while (true) {
        gmp_fscanf(infile, "%Zx\n", c);
        mpz_export(block, &i, 1, sizeof(block), 1, 0, c);
        rsa_decrypt(m, c, d, n);
        gmp_fprintf(outfile, "%Zx\n", m);
        i += 1;
        if (feof(infile)) {
            break;
        }
    }
    //clears and frees
    mpz_clear(m);
    mpz_clear(c);
    free(block);
}

//this function performs rsa verification returning true if signature s is verified and false otherwise
void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

//this function performs rsa verification returning true if signature s is verified and false otherwise
//this function's pseudocode was given by TA Christian
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    }
    mpz_clear(t);
    return false;
}
