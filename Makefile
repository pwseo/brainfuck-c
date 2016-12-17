CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c99

bf: bf.c stack.c
	$(CC) $(CFLAGS) -o $@ $^
