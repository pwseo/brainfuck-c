#ifndef _pwseo_stack_h
#define _pwseo_stack_h

#include <stdbool.h>
#include <stddef.h>     // needed for size_t

// Forward declaration
struct stack;

// Constructor and destructor
struct stack *stack_new(void);
void stack_free(struct stack *s);

// Getters and setters
void *stack_pop(struct stack * const s);
void *stack_peek(struct stack const * const s);
void stack_push(struct stack * const s, void *ptr);
bool stack_empty(struct stack const * const s);

#endif
