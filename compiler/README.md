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
- `Makefile` peut être utilisé pour compiler le parseur. Les librairies et includes par défaut sont ceux qui fonctionnent sur les machines des salles IF 208 et 219.
- `compile_ubuntu.sh` est un script qui compile le projet sur un environnement ubuntu.
- `compile_docker.sh` est un script qui permet de compiler le projet sur n'importe quelle distribution linux en se servant de docker.
- `fast_test.sh` est un script qui permet de faire un test rapide sur un fichier de test .c. Pour l'utiliser il faut taper sh fast_test.sh <cfile_name> et cela va donner la valeur de retour du programme compilé par ifcc puis exécuté.

