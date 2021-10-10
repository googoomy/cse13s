CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: mathlib-test

e: e.o
	$(CC) -o e e.o $(LFLAGS)
newton: newton.o
	$(CC) -o newton newton.o $(LFLAGS)

mathlib-test: mathlib-test.o e.o newton.c
	$(CC) $(CFLAGS) mathlib-test.o e.o newton.c -o mathlib-test

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

newton.o: newton.c mathlib.h
	$(CC) $(CFLAGS) -c newton.c

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c

format:
	clang-format -i -style-file *.c *.h

clean:
	rm -f e_test *.o *.exe
