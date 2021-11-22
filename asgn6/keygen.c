#include <stdio.h>
#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

//these defines are from TA Christian
#define DEFAULT_PRIVKEY_NAME "rsa.priv"
#define DEFAULT_PUBKEY_NAME  "rsa.pub"
#define OPTIONS              "b:i:n:d:s:vh"

static FILE *private_key_file = NULL;
static FILE *public_key_file = NULL;

//keygen pseudocode was given in asgn 6 pdf
int main(int argc, char **argv) {
    int opt = 0;
    //flags
    bool no_input_flag = true;
    bool b_flag = false;
    bool i_flag = false;
    bool n_flag = false;
    bool d_flag = false;
    bool s_flag = false;
    bool v_flag = false;
    bool h_flag = false;
    //default bits is 256
    uint32_t b = 256;
    //default iterations is 50
    uint32_t i = 50;
    char *privk = NULL;
    char *pubk = NULL;
    //default seed is time(NULL)
    uint64_t seed = time(NULL);
    //parse command-line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input_flag = false;
        switch (opt) {
        case 'b':
            b_flag = true;
            b = strtoul(optarg, NULL, 10);
            break;
        case 'i':
            i_flag = true;
            i = strtoul(optarg, NULL, 10);
            break;
        case 'n':
            n_flag = true;
            pubk = optarg;
            break;
        case 'd':
            d_flag = true;
            privk = optarg;
            break;
        case 's':
            s_flag = true;
            seed = strtoul(optarg, NULL, 10);
            break;
        case 'v': v_flag = true; break;
        case 'h': h_flag = true; break;
        }
    }
    //if no input given or -h was typed display help
    if (h_flag == true || no_input_flag == true) {
        printf("SYNOPSIS\n");
        printf("   Generates an RSA public/private key pair.\n\n");
        printf("USAGE\n");
        printf("   ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n\n");
        printf("OPTIONS\n");
        printf("   -h              Display program help and usage.\n");
        printf("   -v              Display verbose program output.\n");
        printf("   -b bits         Minimum bits needed for public key n (default: 256).\n");
        printf("   -i confidence   Miller-Rabin iterations for testing primes (default: 50).\n");
        printf("   -n pbfile       Public key file (default: rsa.pub).\n");
        printf("   -d pvfile       Private key file (default: rsa.priv).\n");
        printf("   -s seed         Random seed for testing.\n");
        return 0;
    }
    //open public and private files
    if (n_flag == false) {
        public_key_file = fopen(DEFAULT_PUBKEY_NAME, "w+");
    } else {
        public_key_file = fopen(pubk, "w+");
    }
    //print error if file cant be opened
    if (public_key_file == NULL) {
        fprintf(stderr, "error opening public key file\n");
        return 1;
    }
    if (d_flag == false) {
        private_key_file = fopen(DEFAULT_PRIVKEY_NAME, "w+");
    } else {
        private_key_file = fopen(privk, "w+");
    }
    //print error if file cant be opened
    if (private_key_file == NULL) {
        fprintf(stderr, "error opening private key file\n");
        return 1;
    }
    //make sure the private key file permissions are set to 0600
    fchmod(fileno(private_key_file), (mode_t) 0600);
    //intialize random state
    randstate_init(seed);
    //initialization of mpz_t's
    mpz_t p;
    mpz_t q;
    mpz_t n;
    mpz_t e;
    mpz_init(e);
    mpz_init(n);
    mpz_init(p);
    mpz_init(q);
    //make the public and private key pairs
    rsa_make_pub(p, q, n, e, b, i);
    mpz_t d;
    mpz_init(d);
    rsa_make_priv(d, e, p, q);
    //get the current user's name
    char *username = getenv("USER");
    //convert username into mpz_t
    mpz_t user_name;
    mpz_init(user_name);
    mpz_set_str(user_name, username, 62);
    //compute the signature of the username
    mpz_t s;
    mpz_init(s);
    rsa_sign(s, user_name, d, n);
    //write the computed public and private key to their files
    rsa_write_pub(n, e, s, username, public_key_file);
    rsa_write_priv(n, d, private_key_file);
    //if the verbose flag is activated
    if (v_flag) {
        printf("%s\n", username);
        gmp_printf("%Zx\n", s);
        gmp_printf("%Zx\n", p);
        gmp_printf("%Zx\n", q);
        gmp_printf("%Zx\n", n);
        gmp_printf("%Zx\n", e);
        gmp_printf("%Zx\n", d);
    }
    //close files and clear mpz_t's
    fclose(private_key_file);
    fclose(public_key_file);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(user_name);
    mpz_clear(s);
}
