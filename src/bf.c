#include <stdio.h>
#include "vm.h"

#include "tokenizer_bf.h"

int main(void)
{
    struct vm *vm = vm_new();

    vm_load(vm, stdin, tokenizer_bf);
    vm_execute(vm, stdin, stdout);
    vm_free(vm);
}
