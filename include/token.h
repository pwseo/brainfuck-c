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

#ifndef _pwseo_token_h
#define _pwseo_token_h

enum token {
    TOK_INC, TOK_DEC,
    TOK_LEFT, TOK_RIGHT,
    TOK_LEFTB, TOK_RIGHTB,
    TOK_GET, TOK_PUT,

    TOK_HALT,
    TOK_ADD, TOK_SUB,
    TOK_MLEFT, TOK_MRIGHT,
    TOK_ZERO,

    TOK_COMMENT,
};

struct instruction {
    enum token type;
    int param;
    struct instruction *prev, *next;
};

#endif
