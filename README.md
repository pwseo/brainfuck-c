# Brainfuck interpreter

A simple brainfuck interpreter written in C99.

## Usage

    bf [FILE]

## Technical details

After reading the brainfuck source code the interpreter will convert it
to an internal representation which is easier to optimize.

Currently, the following optimizations are applied:

- Loops `[+]` or `[-]` directly set current value to zero
- Consecutive `+`, `-`, `<` or `>` are collapsed to single instructions
  that do the equivalent arithmetic / memory operations
