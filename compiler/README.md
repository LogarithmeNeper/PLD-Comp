# C compiler with antlr4/c++

## Changement après la présentation

Nous avons modifié notre grammaire pour que les affectations soient gérées en dehors des expressions pour pouvoir vérifier que l'élément à gauche du '=' soit toujours une variable et jamais une expression (a+b=2 est incorrect).
Nous avons également modifié notre gestion des fonctions. Il est possible d'initialiser une fonction avec plusieurs arguments de type int (ou aucun), en revanche on ne peux appeler que des fonctions à un argument entier.

## Fichiers source
- `ifcc.g4` contient la grammaire au format ANTLR4
- `main.cpp` est le point d'entrée C++ pour appeler le parser généré par antlr4 sur le fichier passé en paramètre dans la ligne de commande.
- `visitor.h` est le visiteur de l'arbre de parsing qui produit un langage assembleur en sortie.
- `pre-visitor.h` est un visiteur de l'arbre de parsing qui tente de détecter des problèmes tels que des varibles non déclarées ou non initialisées dans le programme.

## Compilation scripts
- `Makefile` can be used to compile the parser. Libraries and include directories default to the values that work in the IF machines of rooms 208 and 219.
- `compile_ubuntu.sh` is a script that compiles the project in a different environment (a ubuntu where the antlr runtime had to be compiled manually).
- `compile_docker.sh` is a script to use if you are desperate. It compiles the project in a docker environment where antlr4 and its dependencies are properly installed.
- `fast_test.sh` is a script to make a fast test on a given .c file. To use it type sh fast_test.sh <cfile_name> and it will give you the return value of the program after being compile by ifcc

