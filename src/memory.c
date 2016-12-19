#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>

#ifndef MEMORYSIZE
#define MEMORYSIZE (16 * 1024) /* Default 16K memory */
#endif

struct memory {
    struct cell *cells;
    size_t used, avail, mp;
};

struct cell {
    uint8_t value;
    size_t prev, next;
};

uint8_t *mem_value_ptr(struct memory const * const m)
{
    return &m->cells[m->mp].value;
}

void cell_init(struct cell * const c)
{
    c->value = 0;
    c->prev = SIZE_MAX;
    c->next = SIZE_MAX;
}

void mem_resize(struct memory * const m)
{
    m->avail += MEMORYSIZE;
    m->cells = realloc(m->cells, sizeof(*m->cells) * m->avail);

    for (size_t i = m->avail - MEMORYSIZE; i < m->avail; ++i)
        cell_init(&m->cells[i]);
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
    size_t idx = m->cells[m->mp].prev;

    if (idx == SIZE_MAX)
        idx = mem_newcell(m);

    m->cells[idx].next = m->mp;
    m->cells[m->mp].prev = idx;

    m->mp = idx;
}

void mem_next(struct memory * const m)
{
    size_t idx = m->cells[m->mp].next;

    if (idx == SIZE_MAX)
        idx = mem_newcell(m);

    m->cells[idx].prev = m->mp;
    m->cells[m->mp].next = idx;

    m->mp = idx;
}
