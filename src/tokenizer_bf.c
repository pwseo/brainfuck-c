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
