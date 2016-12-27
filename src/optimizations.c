#include "optimizations.h"

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
