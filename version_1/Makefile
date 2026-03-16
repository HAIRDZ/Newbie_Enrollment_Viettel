CC=gcc
CFLAGS=-Wall -Wextra -O2

all: my_morse testRunner

my_morse: src/myMorse.c
	$(CC) $(CFLAGS) -o my_morse src/myMorse.c

testRunner: test/testRunner.c
	$(CC) $(CFLAGS) -o testRunner test/testRunner.c

clean:
	rm -f my_morse testRunner output.txt tmp_input.txt
