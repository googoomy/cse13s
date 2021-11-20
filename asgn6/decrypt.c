#include "rsa.h"
#include <gmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_PRIVKEY_NAME "rsa.priv"
#define OPTIONS "i:o:n:vh"

static FILE *input_file = NULL;
static FILE *output_file = NULL;
static FILE *private_key_file = NULL;

int main(int argc, char **argv){
	int opt = 0;
	bool no_input_flag = true;
	bool i_flag = false;
	bool o_flag = false;
	bool n_flag = false;
	bool v_flag = false;
	bool h_flag = false;
	char *in = NULL;
	char *out = NULL;	
	char *privk = NULL;
	while((opt = getopt(argc, argv, OPTIONS)) != -1){
		no_input_flag = false;
		switch(opt){
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
				privk = optarg;
				break;
			case 'v':
				v_flag = true;
				break;
			case 'h':
				h_flag = true;
				break;
			default:
				return EXIT_FAILURE;	
		}
	}
	if(h_flag == true || no_input_flag == true){
		printf("SYNOPSIS\n");
		printf("   Decrypts data using RSA decryption.\n");
		printf("   Encrypted data is encrypted by the encrypt program.\n\n");
		printf("USAGE\n");
		printf("   ./decrypt [-hv] [-i infile] [-o outfile] -n privkey\n\n");
		printf("OPTIONS\n");
		printf("   -h              Display program help and usage.\n");
		printf("   -v              Display verbose program output.\n");
		printf("   -i infile       Input file of data to decrypt (default: stdin).\n");
		printf("   -o outfile      Output file for decrypted data (default: stdout).\n");
		printf("   -n pvfile       Private key file (default: rsa.priv).\n");
		return 0;
	}
	if(i_flag == false){
		input_file = stdin;
	}else{
		input_file = fopen(in, "r");
	}
	if(o_flag == false){
		output_file = stdout;
	}else{
		output_file = fopen(out, "w+");
	}
	if(n_flag == false){
		private_key_file = DEFAULT_PRIVKEY_NAME;
	}else{
		private_key_file = fopen(privk, "r");
	}

	mpz_t n;
	mpz_t d;
	mpz_init(n);
	mpz_init(d);
	rsa_read_priv(n, d, private_key_file);
	if(v_flag){
		printf("%Zx\n", n);
	}
	rsa_decrypt_file(input_file, output_file, n, d);
	fclose(output_file);
	fclose(input_file);
	fclose(private_key_file);
	mpz_clear(n);
	mpz_clear(d);
}
