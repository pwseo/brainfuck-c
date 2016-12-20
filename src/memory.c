#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <stdio.h>

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
    struct memory *m = malloc(sizeof(*m));

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

void mem_prev(struct memory * const m)
{
    if (m->mp > 0) {
        m->mp -= 1;
    } else {
        fprintf(stderr, "Access violation: tried to access negative memory address.\n");
        exit(2);
    }
}

void mem_next(struct memory * const m)
{
    if (m->mp == m->avail - 1)
        mem_resize(m);

    m->mp += 1;
}
