#James Gu
#jjgu
#Fall 2021
#Assignment 2: A Little Slice of Pi

##DESCRIPTION OF PROGRAM: This program is a series of ways on how to estimate e or pi. Computers can only do simple operations of multiplicaiton, division, addition, and subtraction, so this program explores how to use these simple operations to find something so abstract such as pi. These methods involve summations usually to approximate such values. What the reader will find in here is the approximation of e using the Taylor Series and the apporximation of pi using the Madhava series, Euler's solution, Bailey-Borwein-plouffe formula, and Viete's formula, as well as Newton-Raphson method of finding square roots.

###BUILD OF THE PROGRAM: this program needs the following:bbp.c, e.c, euler.c, madhava.c, mathlib-test.c, mathlib.h, newton.c, viete.c, Makefile, README.md, DESIGN.pdf, and WRITEUP.pdf

####HOW TO RUN THE PROGRAM:To run this program the user should first ask for the help function and to do so they need to type in make and then ./mathlib-test h. They will be given a list of commands they are allowed to do which include -a for all tests, -e for e approximation, -b for bailey-Borwein pi, -m for Madhava pi, -r for Euler sequence pi, -v for Viete pi, -n for Newton-Raphson square root, -s to ask for how many terms it took for a test, and -h to ask for help.
