#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "vm.h"
#include "memory.h"
#include "stack.h"
#include "token.h"

struct vm {
    struct stack  *loops;
    struct memory *mem;
    enum token *code, *ip;
};

struct vm *vm_new(void)
{
    struct vm *vm = calloc(1, sizeof(*vm));

    vm->loops = stack_new();
    vm->mem = mem_new();

    return vm;
}

void vm_free(struct vm *vm)
{
    stack_free(vm->loops);
    mem_free(vm->mem);

    free(vm->code);

    free(vm);
}

void vm_load(struct vm * const vm, FILE * const f,
             enum token (*tokenizer)(FILE * const))
{
    vm->code = malloc(sizeof(*vm->code) * (1024 * 1024));
    enum token *iptr = vm->code;

    for (enum token tok; (tok = tokenizer(f)) != TOK_HALT; ++iptr)
        *iptr = tok;

    *iptr = TOK_HALT;
}

void vm_execute(struct vm * const vm, FILE * const in, FILE * const out)
{
    vm->ip = vm->code;
    for (uint8_t *value; *vm->ip != TOK_HALT; ++vm->ip) {
        value = mem_value_ptr(vm->mem);

        switch (*vm->ip) {
            case TOK_LEFTB:
                if (*value != 0) {
                    stack_push(vm->loops, vm->ip);
                } else {
                    int i = 1;
                    while (i > 0) {
                        ++vm->ip;
                        if (*vm->ip == TOK_LEFTB)  i += 1;
                        if (*vm->ip == TOK_RIGHTB) i -= 1;
                    }
                }
                break;

            case TOK_RIGHTB:
                if (*value == 0)
                    stack_pop(vm->loops);
                else
                    vm->ip = stack_peek(vm->loops);
                break;

            case TOK_LEFT:
                mem_prev(vm->mem);
                break;

            case TOK_RIGHT:
                mem_next(vm->mem);
                break;

            case TOK_INC:
                *value += 1;
                break;

            case TOK_DEC:
                *value -= 1;
                break;

            case TOK_GET:
                *value = fgetc(in);
                break;

            case TOK_PUT:
                fputc(*value, out);
                break;
            default:
                break;
        }
    }
}
