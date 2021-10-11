#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "haebmrvns"

int main(int argc, char **argv) {
    //CITE:flags from TA CHRISTIAN
    int opt = 0;
    //flags to see which programs are intended to be ran by the user
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
    //CITE:while loop from DARRELL LONG
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = false;
        switch (opt) {
        case 'h': h_flag = true; break;
        case 'a':
            a_flag = true;
            e_flag = true;
            b_flag = true;
            m_flag = true;
            r_flag = true;
            v_flag = true;
            n_flag = true;
            break;
        case 'e': e_flag = true; break;
        case 'b': b_flag = true; break;
        case 'm': m_flag = true; break;
        case 'r': r_flag = true; break;
        case 'v': v_flag = true; break;
        case 'n': n_flag = true; break;
        case 's': s_flag = true; break;
        }
    }
    if (h_flag) {
        //help will describe how to use this program and wont run any tests.
        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvnsh]\n\n");
        printf("OPTIONS\n");
        printf("  -a   Runs all tests.\n");
        printf("  -e   Runs e test.\n");
        printf("  -b   Runs BBP pi test.\n");
        printf("  -m   Runs Madhava pi test.\n");
        printf("  -r   Runs Euler pi test.\n");
        printf("  -v   Runs Viete pi test.\n");
        printf("  -n   Runs Newton square root tests.\n");
        printf("  -s   Print verbose statistics.\n");
        printf("  -h   Display program synopsis and usage.\n");
        e_flag = false;
        r_flag = false;
        b_flag = false;
        m_flag = false;
        v_flag = false;
        n_flag = false;
    }
    if (e_flag) {
        double diff = absolute(e() - M_E);
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, diff);
        if (s_flag) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    if (r_flag) {
        double diff = absolute(pi_euler() - M_PI);
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, diff);
        if (s_flag) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    if (b_flag) {
        double diff = absolute(pi_bbp() - M_PI);
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI, diff);
        if (s_flag) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    if (m_flag) {
        double m = pi_madhava();
        double diff = absolute(m - M_PI);
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", m, M_PI, diff);
        if (s_flag) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    if (v_flag) {
        double diff = absolute(pi_viete() - M_PI);
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI, diff);
        if (s_flag) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    if (n_flag) {
        double diff = 0;
        for (double i = 0; i <= 10; i += 0.1) {
            diff = absolute(sqrt_newton(i) - sqrt(i));
            printf("sqrt_newton(%1.6lf) = %16.15lf, sqrt(%1.6lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), diff);
            if (s_flag) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }
}
