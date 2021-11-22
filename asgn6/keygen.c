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

#define OPTIONS "b:i:n:d:s:vh"

static FILE *private_key_file = NULL;
static FILE *public_key_file = NULL;

int main(int argc, char **argv) {
    int opt = 0;
    bool no_input_flag = true;
    bool b_flag = false;
    bool i_flag = false;
    bool n_flag = false;
    bool d_flag = false;
    bool s_flag = false;
    bool v_flag = false;
    bool h_flag = false;
    uint32_t b = 256;
    uint32_t i = 50;
    char *privk = NULL;
    char *pubk = NULL;
    uint32_t seed = time(NULL);
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input_flag = false;
        switch (opt) {
        case 'b':
            b_flag = true;
            b = optarg;
            break;
        case 'i':
            i_flag = true;
            i = optarg;
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
            seed = optarg;
            break;
        case 'v': v_flag = true; break;
        case 'h': h_flag = true; break;
        }
    }
}
