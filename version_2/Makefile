CC=gcc
CFLAGS=-Wall -Wextra -O2

all: my_morse testRunner

my_morse: main.o morseTree.o
	$(CC) $(CFLAGS) -o my_morse main.o morseTree.o

main.o: main.c morseTree.h
	$(CC) $(CFLAGS) -c main.c

morseTree.o: morseTree.c morseTree.h
	$(CC) $(CFLAGS) -c morseTree.c

testRunner: testRunner.c
	$(CC) $(CFLAGS) -o testRunner testRunner.c

clean:
	rm -f *.o my_morse testRunner output.txt tmp_input.txt
