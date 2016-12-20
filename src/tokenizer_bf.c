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

#include "tokenizer_bf.h"

enum token tokenizer_bf(FILE * const f)
{
    int c;
    
again:
    c = fgetc(f);

    if (c == EOF)
        return TOK_HALT;

    switch (c) {
        case '[': return TOK_LEFTB;
        case ']': return TOK_RIGHTB;
        case '+': return TOK_INC;
        case '-': return TOK_DEC;
        case ',': return TOK_GET;
        case '.': return TOK_PUT;
        case '<': return TOK_LEFT;
        case '>': return TOK_RIGHT;
        default:  goto again;
    }
}
