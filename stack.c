#include "stack.h"
#include <stdlib.h>

#ifndef STACKSIZE
#define STACKSIZE 1024
#endif

struct stack {
    void **items;
    size_t size, capacity;
};


void *stack_pop(struct stack * const s) {
    return s->items[--s->size];
}

void *stack_peek(struct stack const * const s) {
    return s->items[s->size - 1];
}

void stack_push(struct stack * const s, void *ptr) {
    s->items[s->size++] = ptr;
}

bool stack_empty(struct stack const * const s) {
    return s->size == 0;
}

void stack_free(struct stack *s) {
    free(s->items);
    free(s);
}

struct stack *stack_new(void) {
    struct stack *s = malloc(sizeof(*s));

    s->capacity = STACKSIZE;
    s->items = malloc(sizeof(*s->items) * s->capacity);
    s->size = 0;

    return s;
}
