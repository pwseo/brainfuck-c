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
#include <string.h>
#include <stdint.h>

#ifndef MEMORYSIZE
#define MEMORYSIZE (32 * 1024) /* Default 32K memory */
#endif

struct memory {
    uint8_t *cells;
    size_t used, avail, mp;
};

struct cell {
    uint8_t value;
    size_t prev, next;
};

uint8_t *mem_value_ptr(struct memory const * const m)
{
    return &m->cells[m->mp];
}

void mem_resize(struct memory * const m)
{
    m->avail += MEMORYSIZE;
    m->cells = realloc(m->cells, sizeof(*m->cells) * m->avail);

    memset(&m->cells[m->avail - MEMORYSIZE], 0, MEMORYSIZE);
}


struct memory *mem_new(void)
{
    struct memory *m = malloc(sizeof *m);

    m->cells = NULL;
    m->used  = 0;
    m->avail = 0;

    mem_resize(m);

    m->mp = 0;
    m->used += 1;

    return m;
}

void mem_free(struct memory *m)
{
    free(m->cells);
    free(m);
}

size_t mem_newcell(struct memory * const m)
{
    if (m->used == m->avail)
        mem_resize(m);

    return m->used++;
}

uint8_t *mem_prev(struct memory * const m, const size_t n)
{
    if ((m->mp - (n-1)) > 0)
        return &m->cells[m->mp -= n];
    else
        return NULL;
}

uint8_t *mem_next(struct memory * const m, const size_t n)
{
    if ((m->mp + (n-1)) == m->avail - 1)
        mem_resize(m);

    return &m->cells[m->mp += n];
}
