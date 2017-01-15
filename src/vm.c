/*
 * Brainfuck interpreter written in C99
 * Copyright (C) 2016  A. Pedro Cunha
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    struct instruction *code, *ip;
};

struct vm *vm_new(void)
{
    struct vm *vm = calloc(1, sizeof *vm);

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
             struct instruction (*tokenizer)(FILE * const))
{
    vm->code = malloc(sizeof(*vm->code) * (1024 * 1024));
    struct instruction *iptr = vm->code,
                       *prev = NULL;

    for (struct instruction instr; (instr = tokenizer(f)).type != TOK_HALT; ++iptr) {
        *iptr = instr;
        iptr->prev = prev;
        if (prev != NULL)
            prev->next = iptr;
        prev = iptr;
    }

    iptr->type = TOK_HALT;
    prev->next = iptr;
}

static inline
void stepi(struct vm * const vm)
{
    vm->ip = vm->ip->next;
}

static inline
enum token itype(struct vm const * const vm)
{
    return vm->ip->type;
}

static inline
int iparam(struct vm const * const vm)
{
    return vm->ip->param;
}

void vm_execute(struct vm * const vm, FILE * const in, FILE * const out)
{
    vm->ip = vm->code;
    for (uint8_t *value = mem_value_ptr(vm->mem); itype(vm) != TOK_HALT; stepi(vm)) {

        switch (itype(vm)) {
            case TOK_LEFTB:
                if (*value != 0) {
                    stack_push(vm->loops, vm->ip);
                } else {
                    int i = 1;
                    while (i > 0) {
                        stepi(vm);
                        if (itype(vm) == TOK_LEFTB)  i += 1;
                        if (itype(vm) == TOK_RIGHTB) i -= 1;
                    }
                }
                break;

            case TOK_RIGHTB:
                if (*value == 0)
                    stack_pop(vm->loops);
                else
                    vm->ip = stack_peek(vm->loops);
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

            case TOK_ADD:
                *value += iparam(vm);
                break;

            case TOK_SUB:
                *value -= iparam(vm);
                break;

            case TOK_LEFT:
            case TOK_MLEFT:
                value = mem_prev(vm->mem, (*vm->ip).param);
                break;

            case TOK_RIGHT:
            case TOK_MRIGHT:
                value = mem_next(vm->mem, (*vm->ip).param);
                break;

            case TOK_PUT:
                fputc(*value, out);
                break;

            case TOK_ZERO:
                *value = 0;
                break;

            default:
                break;
        }
    }
}

void vm_optimize(struct vm * const vm, void (*func)(struct instruction * const))
{
    func(vm->code);
}
