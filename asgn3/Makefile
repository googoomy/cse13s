CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: sorting

stats: stats.o
	$(CC) $(CFLAGS) -o stats stats.o

insert: insert.o
	$(CC) -o insert insert.o $(LFLAGS)

heap: heap.o
	$(CC) -o heap heap.o $(LFLAGS)

quick: quick.o
	$(CC) -o quick quick.o $(LFLAGS)

shell: shell.o
	$(CC) -o shell shell.o $(LFLAGS)

sorting: sorting.o insert.o heap.o quick.o shell.o
	$(CC) $(CFLAGS) sorting.o insert.o heap.o quick.o shell.o -o sorting $(LFLAGS)

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

insert.o: insert.c sorting.h
	$(CC) $(CFLAGS) -c insert.c

heap.o: heap.c sorting.h
	$(CC) $(CFLAGS) -c heap.c

quick.o: quick.c sorting.h
	$(CC) $(CFLAGS) -c quick.c

shell.o: shell.c sorting.h
	$(CC) $(CFLAGS) -c shell.c

sorting.o: sorting.c sorting.h
	$(CC) $(CFLAGS) -c sorting.c

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f *.o *.exe sorting

