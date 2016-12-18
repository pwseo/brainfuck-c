#ifndef _pwseo_vm_h
#define _pwseo_vm_h

#include "token.h"

struct vm;

struct vm *vm_new(void);
void vm_load(struct vm * const vm, FILE * const stream, enum token (*tokenizer)(FILE * const f));
void vm_execute(struct vm * const vm, FILE * const istream, FILE * const ostream);
void vm_free(struct vm * vm);

#endif
