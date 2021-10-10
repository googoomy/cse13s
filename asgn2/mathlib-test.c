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
	int v_flag = false;
	int n_flag = false;
	int s_flag = false;

	while((opt = getopt(argc, argv, OPTIONS)) != -1){
		no_input = false;
		switch(opt){
			case 'h':
				h_flag = true; 
				break;
			case 'a':
				a_flag = true;
				e_flag = true;
				b_flag = true;
				m_flag = true;
				r_flag = true;
				v_flag = true;
				n_flag = true;
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
			case 'v':
				v_flag = true;
				break;
			case 'n':
				n_flag = true;
				break;
			case 's':
				s_flag = true;
				break;
		}
	}

	if (e_flag){
		double diff = absolute(e()-M_E);
		printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, diff);
		if(s_flag){
			printf("e() terms = %d\n", e_terms());
		}	
	}
	if (r_flag){
		double diff = absolute(pi_euler()-M_PI);
		printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, diff);
		if(s_flag){
			printf("pi_euler() terms = %d\n", pi_euler_terms());	
		}	
	}
	if (b_flag){
		double diff = absolute(pi_bbp()-M_PI);
		printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI, diff);
		if(s_flag){
			printf("pi_bbp() terms = %d\n", pi_bbp_terms());	
		}			
	}
	if (m_flag){
		double diff = absolute(pi_madhava()-M_PI);
		printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI, diff);
		if(s_flag){
			printf("pi_madhava() terms = %d\n", pi_madhava_terms());	
		}	
	}
	if (v_flag){
		double diff = absolute(pi_viete()-M_PI);
		printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI, diff);
		if(s_flag){
			printf("pi_viete() terms = %d\n", pi_viete_factors());	
		}	
	}
	if (n_flag){
		double diff = 0;
		double result = 0;
		for(double i = 0; i <= 10; i += 0.1){
			result = sqrt(i);
			diff = absolute(sqrt_newton(i)-result);
			printf("sqrt_newton(%16.6lf) = %16.15lf, sqrt(%16.6lf) = %16.15lf, diff = %16.15lf\n", i, sqrt_newton(i), i, result, diff);
			if(s_flag){
				printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
			}
		}

		//printf("testing sqrt_newton(4): %16.15f, sqrt_newton_iters: %d\n", sqrt_newton(4), sqrt_newton_iters());
	}

}
