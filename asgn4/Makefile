CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm
OBJECT_FILES = graph.o stack.o path.o tsp.o

all: tsp

tsp: $(OBJECT_FILES)
	$(CC) $(LFLAGS) -o tsp $(OBJECT_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f tsp *.o *.exe

scan-build: clean
	scan-build --use-cc=$(CC) make
