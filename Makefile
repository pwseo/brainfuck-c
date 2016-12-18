CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c99

bf: bf.c stack.c memory.c vm.c tokenizer_bf.c	
	$(CC) $(CFLAGS) -o $@ $^
