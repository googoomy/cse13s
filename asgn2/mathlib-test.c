#include "mathlib.h"
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define OPTIONS "haebmrvns"

int main(int argc, char **argv){
	int opt = 0;
	int no_input = true;
	int h_flag = false;
	int a_flag = false;
	int e_flag = false;
	int b_flag = false;
	int m_flag = false;
	int r_flag = false;
	int n_flag = false;

	while((opt = getopt(argc, argv, OPTIONS)) != -1){
		no_input = false;
		switch(opt){
			case 'h':
				h_flag = true; 
				break;
			case 'a':
				a_flag = true;
				break;
			case 'e':
				e_flag = true;
				break;
			case 'b':
				b_flag = true;
				break;
			case 'm':
				m_flag = true;
				break;
			case 'r':
				r_flag = true;
				break;
			case 'n':
				n_flag = true;
				break;
		}
	}

	if (e_flag){
		printf("testing e(): %16.15lf, num_terms: %d\n", e(), e_terms());
	}
	if (b_flag){
		printf("testing bbp():%16.15lf, num_terms: %d\n", pi_bbp(), pi_bbp_terms());
	}
	if (m_flag){
		printf("testing madhava(): %16.15lf, num_terms: %d\n", pi_madhava(),pi_madhava_terms()); 
	}
	if (r_flag){
		printf("testing euler(): %16.15lf, num_terns: %d\n", pi_euler(), pi_euler_terms());
	}
	if (n_flag){
		printf("testing sqrt_newton(4): %16.15f, sqrt_newton_iters: %d\n", sqrt_newton(4), sqrt_newton_iters());
	}

}
