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
