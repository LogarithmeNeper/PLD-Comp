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
- `Makefile` peut être utilisé pour compiler le parseur. Les librairies et includes par défaut sont ceux qui fonctionnent sur les machines des salles IF 208 et 219.
- `compile_ubuntu.sh` est un script qui compile le projet sur un environnement ubuntu.
- `compile_docker.sh` est un script qui permet de compiler le projet sur n'importe quelle distribution linux en se servant de docker.
- `fast_test.sh` est un script qui permet de faire un test rapide sur un fichier de test .c. Pour l'utiliser il faut taper sh fast_test.sh <cfile_name> et cela va donner la valeur de retour du programme compilé par ifcc puis exécuté.

