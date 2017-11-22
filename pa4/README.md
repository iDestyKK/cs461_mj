# Programming Assignment 4 (csem)

## About
`csem` (C SEMantic) is compiler program written to translate a subset of the C Programming Language into intermediate code.
It uses Bison (yacc) to interpret input.
The heart of the program is powered by the C Programming Language itself (how fitting).

## Synopsis
```
./csem < input_c
```

## Compiling
Just use `make`. It was supplied to us for the assignment. The source code files included are pretty much all of the y, c, and h files.

## Gradescripts
I decided to take some time out of my life to make some gradescripts to ensure my output matches the solution code's output.
There are a few shell scripts in this directory.
Here is what they all do:

### gen.sh
**Requirements:** `ref_csem, gradescript/input/*.txt, gradescript/output/`

This will generate the files in `gradescript/output/` using the solution executable `ref_csem` and all input C files in `gradescript/input/*.c`.

### gradeall.sh
**Requirements:** `csem, gradescript/input/*.txt, gradescript/output/*.txt`

This will check your solution code to make sure that it matches output with the solution code.
This script will work on machines without `ref_csem`, as the output of the program is already in `gradescript/output/`.

### check.sh
**Requirements:** `csem, a C file in "gradescript/input", and a C file of the same name in "gradescript/output"`
Assuming you have the gradescripts cached ia `gen.sh`, this is the fastest of all of the shell scripts. It accepts a C file in the `gradescript/input` directory as a parametre, and will pipe it into your code. Then it will diff the output of your program with the cached output in `gradescript/output` to check if it matches. It will then print `Matches!` or `Does not match!` depending on if your code works or not.
