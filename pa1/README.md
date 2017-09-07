# Programming Assignment 1 (NFA2DFA Converter)

## About
Converts an NFA (in a specially formatted text file) into a DFA. The application does not accept any arguments, but it reads from stdin and writes to stdout. The converting process revolves around e-closure and move algorithms to navigate around the NFA and make states based on epsilon transitions.

## Synopsis
```
./nfa2dfa < nfa_file > dfa_file
```

## Compiling
Use the makefile that comes with the project. Both the "c" and "cpp" variants come with their own Makefile for you to use. You must call "make clean" if the executable exists before calling "make" again.

## Libraries
This program uses some functions in my "Handy" library to make my life a little easier. Even though it's a C library, it still works in C++. :)
