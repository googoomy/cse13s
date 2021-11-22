#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"
//#include <gmp.h>
#include <stdio.h>
#include <gmp.h>
#include <inttypes.h>
#include <stdlib.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
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
    while (mpz_cmp(n, r3) > 0 || mpz_cmp(n, r3) == 0) {
        //mpz_fdiv_q_ui(r, mpz_nbits, 2);
        pbits = nbits / 4 + gmp_urandomm_ui(state, nbits / 2);
        //mpz_fdiv_q_ui(r, mpz_nbits, 4);
        //mpz_add(r, pbits, r2);
        //mpz_set(pbits, r);
    }
    make_prime(p, pbits, iters);

    make_prime(q, nbits - pbits, iters);
    mpz_t totient;
    mpz_init(totient);
    mpz_sub_ui(r, p, 1);
    mpz_sub_ui(r2, q, 1);
    mpz_mul(totient, r, r2);
    while (true) {
        mpz_urandomb(e, state, nbits);
        gcd(r, e, totient);
        if (mpz_cmp_ui(r, 1) == 0) {
            break;
        }
    }
    //mpz_clear(pbits);
    mpz_clear(r2);
    mpz_clear(r);
    mpz_clear(r3);
    mpz_clear(totient);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    fscanf(pbfile, "%s\n", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t inverse_e;
    mpz_init(inverse_e);
    mpz_t totient;
    mpz_init(totient);
    mpz_t r;
    mpz_init(r);
    mpz_sub_ui(r, p, 1);
    mpz_t r2;
    mpz_init(r2);
    mpz_sub_ui(r2, q, 1);
    mpz_mul(totient, r, r2);
    mod_inverse(inverse_e, e, totient);
    mpz_set(d, inverse_e);
    mpz_clear(inverse_e);
    mpz_clear(totient);
    mpz_clear(r);
    mpz_clear(r2);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "Zx\n", n);
    gmp_fscanf(pvfile, "Zx\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    uint32_t k = (int) ((mpz_sizeinbase(n, 2) - 1) / 8);
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    block[0] = 0xFF;
    char buffer[100];
    mpz_t m;
    mpz_init(m);
    mpz_t c;
    mpz_init(c);

    uint32_t i = 1;
    while (true) {
        block[i] = fread(buffer, sizeof(uint8_t), k - 1, infile);
        //block[i] = buffer;
        mpz_import(m, i, 1, sizeof(block), 1, 0, block);
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile, "%Zx\n", c);
        i += 1;
        if (feof(infile)) {
            break;
        }
    }
    mpz_clear(m);
    mpz_clear(c);
    free(block);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    uint32_t k = (int) ((mpz_sizeinbase(n, 2) - 1) / 8);
    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    mpz_t c;
    mpz_init(c);
    mpz_t m;
    mpz_init(m);
    size_t i = 1;
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
    mpz_clear(m);
    mpz_clear(c);
    free(block);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

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
