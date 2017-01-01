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
            if (iptr->type == TOK_LEFT)
                iptr->type = TOK_MLEFT;
            if (iptr->type == TOK_RIGHT)
                iptr->type = TOK_MRIGHT;

            if (iptr->type == TOK_ADD || iptr->type == TOK_SUB || iptr->type == TOK_MLEFT || iptr->type == TOK_MRIGHT) {
                iptr->next = cursor->next;
                if (cursor->next)
                    cursor->next->prev = iptr;
            }
        }
    }
}
