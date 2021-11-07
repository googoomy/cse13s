CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
OBJECT_FILES = code.o huffman.o io.o node.o pq.o stack.o

all: encode decode

encode: $(OBJECT_FILES) encode.o
	$(CC) -o encode $(OBJECT_FILES) encode.o

decode: $(OBJECT_FILES) decode.o
	$(CC) -o decode $(OBJECT_FILES) decode.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

format:
	clang-format -i style=file *.[ch]

clean:
	rm -f encode decode *.o

scan-build: clean
	scan-build --use-cc=$(CC) make
