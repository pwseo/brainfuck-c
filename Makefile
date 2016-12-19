CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c99

bf: src/bf.c src/stack.c src/memory.c src/vm.c src/tokenizer_bf.c	
	$(CC) $(CFLAGS) -Iinclude -o $@ $^
