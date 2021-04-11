# C compiler with antlr4/c++

## Instructions

This minimal example shows how to build a basic C compiler using Antlr4 for C++. The only file the compiler can deal with is:

```
int main() {
   return n;
}
```
where `n` is a positive integer. 

## Changes after the presentation

We change our grammar to read the assignments differently then the expressions in order to be able to force the left side of an equals character to be the identifier of a variable, it can no longer be an expression (like a+b=2).


## Source Files
- `ifcc.g4` contains the grammar in antlr4 format
- `main.cpp` contains the C++ code to call the antlr4-generated parser on the  file name provided in the command line.
- `visitor.h` is a visitor of the parse tree that produces an assembly-language output
- `pre-visitor.h` is a visitor of the parse tree that attemps to detect problems such as undeclared or non initialized variables in the program

## Compilation scripts
- `Makefile` can be used to compile the parser. Libraries and include directories default to the values that work in the IF machines of rooms 208 and 219.
- `compile_ubuntu.sh` is a script that compiles the project in a different environment (a ubuntu where the antlr runtime had to be compiled manually).
- `compile_docker.sh` is a script to use if you are desperate. It compiles the project in a docker environment where antlr4 and its dependencies are properly installed.
- `fast_test.sh` is a script to make a fast test on a given .c file. To use it type sh fast_test.sh <cfile_name> and it will give you the return value of the program after being compile by ifcc

