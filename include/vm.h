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

#ifndef _pwseo_vm_h
#define _pwseo_vm_h

#include "token.h"

struct vm;

struct vm *vm_new(void);
void vm_load(struct vm * const vm, FILE * const stream, struct instruction (*tokenizer)(FILE * const f));
void vm_optimize(struct vm * const vm, void (*f)(struct instruction * const));
void vm_execute(struct vm * const vm, FILE * const istream, FILE * const ostream);
void vm_free(struct vm * vm);

#endif
