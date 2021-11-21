CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)
OBJECT_FILES = numtheory.o rsa.o randstate.o

all: decrypt encrypt keygen

decrypt: $(OBJECT_FILES) decrypt.o
	$(CC) -o decrypt $(OBJECT_FILES) decrypt.o $(LFLAGS)

encrypt: $(OBJECT_FILES) encrypt.o
	$(CC) -o encrypt $(OBJECT_FILES) encrypt.o $(LFLAGS)

keygen: $(OBJECT_FILES) keygen.o
	$(CC) -o keygen $(OBJECT_FILES) keygen.o $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

format:
	clang-format -i style=file *.[ch]

clean:
	rm -f decrypt encrypt keygen *.o

scan-build: clean
	scan-build --use-cc=$(CC) make
