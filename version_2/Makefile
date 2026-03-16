CC=gcc
CFLAGS=-Wall -Wextra -O2 -Iinclude

SRC=src/main.c src/morseTree.c
OBJ=main.o morseTree.o

all: my_morse testRunner

my_morse: $(OBJ)
	$(CC) $(CFLAGS) -o my_morse $(OBJ)

main.o: src/main.c include/morseTree.h
	$(CC) $(CFLAGS) -c src/main.c

morseTree.o: src/morseTree.c include/morseTree.h
	$(CC) $(CFLAGS) -c src/morseTree.c

testRunner: test/testRunner.c
	$(CC) $(CFLAGS) -o testRunner test/testRunner.c

clean:
	rm -f *.o my_morse testRunner
