#include <stdlib.h>
#include <stdint.h>

#ifndef MEMORYSIZE
#define MEMORYSIZE (16 * 1024) /* Default 16K memory */
#endif

struct memory {
    struct cell *cells, *mp, *nextfree;
    size_t used, avail;
};

struct cell {
    uint8_t value;
    struct cell *prev, *next;
};

uint8_t *mem_value_ptr(struct memory const * const m)
{
    return &m->mp->value;
}

void cell_init(struct cell * const c)
{
    c->value = 0;
    c->prev = c->next = NULL;
}

void mem_resize(struct memory * const m)
{
    size_t oldcap = m->avail;

    m->avail = oldcap + MEMORYSIZE;
    m->cells = realloc(m->cells, sizeof(*m->cells) * m->avail);

    for (size_t i = oldcap; i < m->avail; ++i)
        cell_init(&m->cells[i]);
}


struct memory *mem_new(void)
{
    struct memory *m = malloc(sizeof(*m));

    m->cells = NULL;
    m->used = m->avail = 0;
    mem_resize(m);

    m->mp = m->cells;
    m->used += 1;
    m->nextfree = (m->mp + 1);

    return m;
}

void mem_free(struct memory *m)
{
    free(m->cells);
    free(m);
}

struct cell *mem_newcell(struct memory * const m)
{

    if (m->used == m->avail)
        mem_resize(m);

    m->used += 1;

    return m->nextfree++;
}

void mem_prev(struct memory * const m)
{
    if (m->mp->prev == NULL) {
        struct cell *new = mem_newcell(m);
        new->next = m->mp;
        m->mp->prev = new;
    }

    m->mp = m->mp->prev;
}

void mem_next(struct memory * const m)
{
    if (m->mp->next == NULL) {
        struct cell *new = mem_newcell(m);
        new->prev = m->mp;
        m->mp->next = new;
    }

    m->mp = m->mp->next;
}
