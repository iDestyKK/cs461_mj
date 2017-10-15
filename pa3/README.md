# Programming Assignment 3 (cexpr)

## About
This assignment is all about making an application that will solve math equations in the same fashion as C does it (hence the name "cexpr"). Takes any form of standard input, whether it be typed or by a file piping input in.

## Synopsis
```
./cexpr
./cexpr < input_txt
```

## Compiling
Just use `make`. It was supplied to us for the assignment. The source code files included are `ex.l`, `ex.y`, and `global.h`. Use wisely.

## Gradescripts
I decided to take some time out of my life to make some gradescripts to ensure my output matches the solution code's output. There are a few shell scripts in this directory. Here is what they all do:

### gen.sh
**Requirements:** `ref_cexpr, gradescript/input/*.txt, gradescript/output/`

This will generate files in `gradescript/output/` using the solution executable `ref_cexpr` and all input txt files in `gradescript/input/*.txt`.

### gradeall.sh
**Requirements:** `cexpr, gradescript/input/*.txt, gradescript/output/*.txt`

This will check your solution code to make sure that it matches output with the solution code.
This script will work on machines without `ref_cexpr`, as the output of the program is already in `gradescript/output/`.

### gradeall2.sh
**Requirements:** `cexpr, ref_cexpr, gradescript/input/*.txt`

This will check your solution code to make sure that it matches output with the solution code.
This script is different from `gradeall.sh` in that it requires `ref_cexpr`.
It will pipe a file from `gradescript/input/*.txt` into both the solution and your code, and then diff their outputs to check.

### check.sh
**Requirements:** `cexpr, a txt file in "gradescript/input" and a txt file of the same name in "gradescript/output"`

Assuming you have the gradescript outputs cached via `gen.sh`, this is the fastest of all shell scripts.
It accepts an txt file in the `gradescript/input` directory as a parametre, and will pipe it into your code, then diff it with the cached output to check if it matches match.
It will then print out `Matches!` or `Does not match!` depending on if your code works or not.

### check2.sh
**Requirements:** `cexpr, ref_cexpr, a txt file`

This is the simplest of all of the shell scripts.
It accepts an txt file as a parametre, and will pipe it into the solution and your code, then diff their outputs to check if they match.
It will then print out `Matches!` or `Does not match!` depending on if your code works or not.
