#ifndef _pwseo_memory_h
#define _pwseo_memory_h

#include "stdint.h"

struct memory;

struct memory *mem_new(void);
void mem_free(struct memory *mem);

void mem_prev(struct memory * const mem);
void mem_next(struct memory * const mem);

uint8_t *mem_value_ptr(struct memory const * const mem);

#endif
