CC=gcc
CFLAGS=-Wall -Wextra

TARGET=my_morse
SRC=myMorse.c

TEST=test_runner
TESTSRC=test_runner.c

all: $(TARGET) $(TEST)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

$(TEST):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(TEST)

test: all
	./$(TEST)

clean:
	rm -f $(TARGET) $(TEST) output.txt test_input.txt test_morse.txt invalid.txt
