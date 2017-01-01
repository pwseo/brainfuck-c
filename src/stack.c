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

#include "stack.h"
#include <stdlib.h>

#ifndef STACKSIZE
#define STACKSIZE 1024
#endif

struct stack {
    void **items;
    size_t size, capacity;
};


void *stack_pop(struct stack * const s)
{
    return s->items[--s->size];
}

void *stack_peek(struct stack const * const s)
{
    return s->items[s->size - 1];
}

void stack_push(struct stack * const s, void *ptr)
{
    s->items[s->size++] = ptr;
}

bool stack_empty(struct stack const * const s)
{
    return s->size == 0;
}

void stack_free(struct stack *s)
{
    free(s->items);
    free(s);
}

struct stack *stack_new(void)
{
    struct stack *s = malloc(sizeof *s);

    s->capacity = STACKSIZE;
    s->items = malloc(s->capacity * sizeof *s->items);
    s->size = 0;

    return s;
}
