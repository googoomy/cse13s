CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm
OBJECT_FILES = ht.o bst.o node.o bv.o bf.o parser.o speck.o

all: banhammer

banhammer: $(OBJECT_FILES)
	$(CC) $(LFLAGS) -o tsp $(OBJECT_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f banhammer *.o

scan-build: clean
	scan-build --use-cc=$(CC) make


