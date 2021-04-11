# C compiler with antlr4/c++

## Changement après la présentation

Nous avons modifié notre grammaire pour que les affectations soient gérées en dehors des expressions pour pouvoir vérifier que l'élément à gauche du '=' soit toujours une variable et jamais une expression (a+b=2 est incorrect).
Nous avons également modifié notre gestion des fonctions. Il est possible d'initialiser une fonction avec plusieurs arguments de type int (ou aucun), en revanche on ne peux appeler que des fonctions à un argument entier.

## Source Files
- `ifcc.g4` contains the grammar in antlr4 format
- `main.cpp` contains the C++ code to call the antlr4-generated parser on the  file name provided in the command line.
- `visitor.h` is a visitor of the parse tree that produces an assembly-language output
- `pre-visitor.h` is a visitor of the parse tree that attemps to detect problems such as undeclared or non initialized variables in the program

## Compilation scripts
- `Makefile` can be used to compile the parser. Libraries and include directories default to the values that work in the IF machines of rooms 208 and 219.
- `compile_ubuntu.sh` is a script that compiles the project in a different environment (a ubuntu where the antlr runtime had to be compiled manually).
- `compile_docker.sh` is a script to use if you are desperate. It compiles the project in a docker environment where antlr4 and its dependencies are properly installed.
- `fast_test.sh` is a script to use to test the program that is written in the `fast_test.c` file.

