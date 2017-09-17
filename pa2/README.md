# Programming Assignment 2 (HTML2LaTeX Converter)

## About
Takes an HTML file (basic one) and converts it into a .l file, which can be piped into `pdflatex` to generate a PDF file.
The purpose of the assignment is to get used to using Lex, as we will be using it for future assignments.

## Synopsis
```
./html2latex < input_html > output_l
```

## Compiling
Just use `make`.
It was supplied to us for the assignment.
The source code file is `html2latex.l`, which contains both C and Lex code.

## Gradescripts
I decided to take some time out of my life to make some gradescripts to ensure that my output matches the solution code's output.
There are **four** shell scripts in this directory. Here is what they all do:

### gen.sh
**Requirements:** `mj_html2latex, gradescript/input/*.html, gradescript/output/`

This will generate files in `gradescript/output/` using the solution executable `mj_html2latex` and all input HTML files in `gradescript/input/*.html`.

### gradeall.sh
**Requirements:** `html2latex, gradescript/input/*.html, gradescript/output/*.html`

This will check your solution code to make sure that it matches output with the solution code.
This script will work on machines without `mj_html2latex`, as the output of the program is already in `gradescript/output/`.

### gradeall2.sh
**Requirements:** `html2latex, mj_html2latex, gradescript/input/*.html`

This will check your solution code to make sure that it matches output with the solution code.
This script is different from `gradeall.sh` in that it requires `mj_html2latex`.
It will pipe a file from `gradescript/input/*.html` into both the solution and your code, and then diff their outputs to check.

### check.sh
**Requirements:** `html2latex, mj_html2latex, an html file`

This is the simplest of all of the shell scripts.
It accepts an html file as a parametre, and will pipe it into the solution and your code, then diff their outputs to check if they match.
It will then print out `Matches!` or `Does not match!` depending on if your code works or not.
