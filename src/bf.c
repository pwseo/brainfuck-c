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

#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

#include "tokenizer_bf.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s [FILE]\n", argv[0]);
        exit(0);
    }

    FILE *bfsrc = fopen(argv[1], "r");

    if (bfsrc == NULL) {
        fprintf(stderr, "Could not open '%s' for reading.\n", argv[1]);
        exit(1);
    }

    struct vm *vm = vm_new();

    vm_load(vm, bfsrc, tokenizer_bf);
    vm_execute(vm, stdin, stdout);
    vm_free(vm);
}
