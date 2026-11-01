CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -g
LIB     = stack.c queue.c applications.c
HDR     = stack.h queue.h applications.h

all: demo tests

demo: main.c $(LIB) $(HDR)
	$(CC) $(CFLAGS) -o demo main.c $(LIB)

tests: tests.c $(LIB) $(HDR)
	$(CC) $(CFLAGS) -o tests tests.c $(LIB)

test: tests
	./tests

run: demo
	./demo

# Rebuild the tests with AddressSanitizer + UBSan to catch leaks and memory errors
check:
	$(CC) $(CFLAGS) -fsanitize=address,undefined -o tests_san tests.c $(LIB)
	./tests_san
	rm -f tests_san

clean:
	rm -f demo tests tests_san

.PHONY: all test run check clean
