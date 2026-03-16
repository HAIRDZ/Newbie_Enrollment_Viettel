CC=gcc
CFLAGS=-Wall -Wextra

TARGET=myMorse
SRC=myMorse.c

TEST=testRunner
TESTSRC=testRunner.c

all: $(TARGET) $(TEST)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

$(TEST):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(TEST)

test: all
	./$(TEST)

clean:
	rm -f $(TARGET) $(TEST) output.txt test_input.txt test_morse.txt invalid.txt
