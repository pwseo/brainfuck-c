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

#ifndef _pwseo_memory_h
#define _pwseo_memory_h

#include "stdint.h"

struct memory;

struct memory *mem_new(void);
void mem_free(struct memory *mem);

uint8_t *mem_prev(struct memory * const mem, const size_t n);
uint8_t *mem_next(struct memory * const mem, const size_t n);

uint8_t *mem_value_ptr(struct memory const * const mem);

#endif
