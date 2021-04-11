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
- `ifcc.g4` contient la grammaire au format ANTLR4
- `main.cpp` est le point d'entrée C++ pour appeler le parser généré par antlr4 sur le fichier passé en paramètre dans la ligne de commande.
- `visitor.h` est le visiteur de l'arbre de parsing qui produit un langage assembleur en sortie.
- `pre-visitor.h` est un visiteur de l'arbre de parsing qui tente de détecter des problèmes tels que des varibles non déclarées ou non initialisées dans le programme.

## Compilation scripts
- `Makefile` can be used to compile the parser. Libraries and include directories default to the values that work in the IF machines of rooms 208 and 219.
- `compile_ubuntu.sh` is a script that compiles the project in a different environment (a ubuntu where the antlr runtime had to be compiled manually).
- `compile_docker.sh` is a script to use if you are desperate. It compiles the project in a docker environment where antlr4 and its dependencies are properly installed.
- `fast_test.sh` is a script to make a fast test on a given .c file. To use it type sh fast_test.sh <cfile_name> and it will give you the return value of the program after being compile by ifcc

