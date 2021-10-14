#James Gu
#jjgu
#Fall 2021
#Assignment 2: A Little Slice of pi
##DESRIPTION OF PROGRAM: This program is a series of ways on how to estimate e or pi. Computers can only do simple operations of multiplication, division, addition, and subtraction, so this program explores how to use these simple operations to find something so abstract such as e or pi. These methods involve summations usually to approximate such values. What the reader will find in here is the approximation of e using Taylor series, the apporximation of pi using Madhava, Euler, Bailey-Borwein-Plouffe formula, Viete's formula, and Newton-Raphson method of square roots
###BUILD OF THE PROGRAM: this program needs the following: bbp.c, e.c, euler.c, madhava.c, mathlib-test.c, mathlib.h, newton.c, viete.c, Makefile, README.md, DESIGN.pdf, and WRITEUP.pdf
####HOW TO RUN THE PROGRAM: To run this program the user should first ask for the help function and to do so they need to type in make and then ./mathlib-test -h. They will be given a list of commands they can type instead of -h which includes -a for all tests, -e for e approximation, -b for Bailey-Borwein pi, -m for madhava pi, -r for Euler sequence pi, -v for Viete pi, -n for /newton-Raphson square root, -s to ask for how many terms for a test, and -h to ask for help again.
