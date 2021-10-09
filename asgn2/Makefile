CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: mathlib-test

e: e.o
	$(CC) -o e e.o $(LFLAGS)

mathlib-test: mathlib-test.o e.o
	$(CC) $(CFLAGS) mathlib-test.o e.o -o mathlib-test

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c

format:
	clang-format -i -style-file *.c *.h

clean:
	rm -f e_test *.o *.exe
