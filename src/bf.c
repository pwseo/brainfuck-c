#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

#include "tokenizer_bf.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s [FILE]\n", argv[0]);
        exit(0);
    }

    FILE *bfsrc = fopen(argv[1], "r");

    if (bfsrc == NULL) {
        fprintf(stderr, "Could not open '%s' for reading.\n", argv[1]);
        exit(1);
    }

    struct vm *vm = vm_new();

    vm_load(vm, bfsrc, tokenizer_bf);
    vm_execute(vm, stdin, stdout);
    vm_free(vm);
}
