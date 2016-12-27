#include "optimizations.h"
#include <stdio.h>

void clearloops(struct instruction * const code)
{
    for (struct instruction *iptr = code; iptr->type != TOK_HALT; iptr = iptr->next) {
        if ((iptr && iptr->type == TOK_LEFTB)           &&
            (iptr->next && (iptr->next->type == TOK_DEC || iptr->next->type == TOK_INC)) &&
            (iptr->next->next && iptr->next->next->type == TOK_RIGHTB)) {
            iptr->type = TOK_ZERO;
            iptr->next = iptr->next->next->next;
            iptr->next->prev = iptr;
        }
    }
}

void compress(struct instruction * const code)
{
    for (struct instruction *iptr = code; iptr && iptr->type != TOK_HALT; iptr = iptr->next) {
        struct instruction *cursor = iptr;

        while (cursor->next && (cursor->next->type == iptr->type)) {
            iptr->param += 1;
            cursor = cursor->next;
        }

        if (iptr->param > 1) {
            if (iptr->type == TOK_INC)
                iptr->type = TOK_ADD;
            if (iptr->type == TOK_DEC)
                iptr->type = TOK_SUB;
            if (iptr->type == TOK_ADD || iptr->type == TOK_SUB) {
                iptr->next = cursor->next;
                if (cursor->next)
                    cursor->next->prev = iptr;
            }
        }
    }
}
