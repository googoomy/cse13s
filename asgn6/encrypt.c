#include "rsa.h"
#include <gmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_PUBKEY_NAME "rsa.pub"
#define OPTIONS             "i:o:n:vh"

static FILE *input_file = NULL;
static FILE *output_file = NULL;
static FILE *public_key_file = NULL;

int main(int argc, char **argv) {
    int opt = 0;
    bool no_input_flag = true;
    bool i_flag = false;
    bool o_flag = false;
    bool n_flag = false;
    bool v_flag = false;
    bool h_flag = false;
    char *in = NULL;
    char *out = NULL;
    char *pubk = NULL;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input_flag = false;
        switch (opt) {
        case 'i':
            i_flag = true;
            in = optarg;
            break;
        case 'o':
            o_flag = true;
            out = optarg;
            break;
        case 'n':
            n_flag = true;
            pubk = optarg;
            break;
        case 'v': v_flag = true; break;
        case 'h': h_flag = true; break;
        default: return EXIT_FAILURE;
        }
    }
    if (h_flag == true || no_input_flag == true) {
        printf("SYNOPSIS\n");
        printf("   Encrypts data using RSA encryption.\n");
        printf("   Encrypted data is decrypted by the decrypt program.\n\n");
        printf("USAGE\n");
        printf("   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey\n\n");
        printf("OPTIONS\n");
        printf("   -h              Display program help and usage.\n");
        printf("   -v              Display verbose program output.\n");
        printf("   -i infile       Input file of data to encrypt (default: stdin).\n");
        printf("   -o outfile      Output file for encrypted data (default: stdout).\n");
        printf("   -n pbfile       Public key file (default: rsa.pub).\n");
        return 0;
    }
    if (i_flag == false) {
        input_file = stdin;
    } else {
        input_file = fopen(in, "r");
    }
    if (o_flag == false) {
        output_file = stdout;
    } else {
        output_file = fopen(out, "w+");
    }
    if (n_flag == false) {
        public_key_file = fopen(DEFAULT_PUBKEY_NAME, "r");
    } else {
        public_key_file = fopen(pubk, "r");
    }
    if (public_key_file == NULL) {
        fprintf(stderr, "error opening file\n");
        return 1;
    }
    mpz_t n;
    mpz_t e;
    mpz_t s;
    char username[100];
    mpz_init(n);
    mpz_init(e);
    mpz_init(s);
    rsa_read_pub(n, e, s, username, public_key_file);
    if (v_flag) {
        printf("%s\n", username);
        gmp_printf("%Zx\n", s);
        gmp_printf("%Zx\n", n);
        gmp_printf("%Zx\n", e);
    }
    mpz_t user_name;
    mpz_init(user_name);
    mpz_set_str(user_name, username, 62);
    rsa_verify(user_name, s, e, n);
    rsa_encrypt_file(input_file, output_file, n, e);
    fclose(output_file);
    fclose(input_file);
    fclose(public_key_file);
    mpz_clear(user_name);
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(s);
}
