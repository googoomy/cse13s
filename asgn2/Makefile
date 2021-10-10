CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: mathlib-test

e: e.o
	$(CC) -o e e.o $(LFLAGS)

newton: newton.o
	$(CC) -o newton newton.o $(LFLAGS)

madhava: madhava.o
	$(CC) -o madhava madhava.o $(LFLAGS)

euler: euler.o
	$(CC) -o euler euler.o $(LFLAGS)

bbp: bbp.o
	$(CC) -o bbp bbp.o $(LFLAGS)

viete: viete.o
	$(CC) -o viete viete.o $(LFLAGS)

mathlib-test: mathlib-test.o e.o newton.o madhava.o euler.o bbp.o viete.o
	$(CC) $(CFLAGS) mathlib-test.o e.o newton.o madhava.o euler.o bbp.o viete.o -o mathlib-test $(LFLAGS)

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

newton.o: newton.c mathlib.h
	$(CC) $(CFLAGS) -c newton.c

madhava.o: madhava.c mathlib.h
	$(CC) $(CFLAGS) -c madhava.c

euler.o: euler.c mathlib.h
	$(CC) $(CFLAGS) -c euler.c

bbp.o: bbp.c mathlib.h
	$(CC) $(CFLAGS) -c bbp.c

viete.o: viete.c mathlib.h
	$(CC) $(CFLAGS) -c viete.c

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f *.o *.exe
