CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm
OBJECT_FILES = sorting.o stats.o insert.o shell.o heap.o quick.o

all: sorting

#stats: stats.o
#	$(CC) $(CFLAGS) stats.o -o stats

#insert: insert.o stats.o
#	$(CC) $(CFLAGS) -o insert insert.o stats.o $(LFLAGS)

#heap: heap.o stats.o
#	$(CC) $(CFLAGS) -o heap heap.o stats.o $(LFLAGS)

#quick: quick.o stats.o
#	$(CC) $(CFLAGS) -o quick quick.o stats.o $(LFLAGS)

#shell: shell.o stats.o
#	$(CC) $(CFLAGS) -o shell shell.o stats.o $(LFLAGS)

sorting: $(OBJECT_FILES)
	$(CC) $(LFLAGS) -o sorting $(OBJECT_FILES)

#stats.o: stats.c stats.h
#	$(CC) $(CFLAGS) -c stats.c

#insert.o: insert.c insert.h stats.h
#	$(CC) $(CFLAGS) -c insert.c

#heap.o: heap.c heap.h stats.h
#	$(CC) $(CFLAGS) -c heap.c

#quick.o: quick.c quick.h stats.h
#	$(CC) $(CFLAGS) -c quick.c

#shell.o: shell.c shell.h stats.h
#	$(CC) $(CFLAGS) -c shell.c

#sorting.o: sorting.c stats.h insert.h shell.h heap.h quick.h
#	$(CC) $(CFLAGS) $(OBJECT_FILES) -o sorting.c

%.o: %.c
	$(CC) $(CFLAGS) -c $<

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f sorting *.o *.exe

scan-build: clean
	scan-build --use-cc=$(CC) make
