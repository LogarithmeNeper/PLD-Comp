# PLD-Comp
Repo pour le Projet Longue Durée Compilateur, INSA Lyon 2021.

# Instructions
## Compile
cd compiler 
sudo ./compile_ubuntu.sh 
<br>
OU 
<br>
cd compiler 
sudo ./compile_docker.sh

## Tests
cd tests
sudo ./test_if.sh
<br>
OU
<br>
cd tests
sudo ./test.sh

# Equipe de travail : 
- François CHAUBEAU
- Lola CREMER
- Pierre DUJARDIN
- Gary FOUGEROLLE
- Thibaut GILLAIN
- Pierre SIBUT-BOURDE

# Fonctionnalités
Notre compilateur permet de compiler un sous ensemble du langage C, voici une liste des fonctionnalités supportées par notre compilateur : <br>

- Déclaration de variables ("int", "char", "int64_t") : possible n'importe où dans le code.
- Possibilité d'initialisation de variables à la déclaration.
- Affectation d'une expression à une variable.
- Opérations arithméthiques : addition, multiplication, soustraction.
- Opérations bit à bit : AND, XOR, OR.
- Gestion des priorités entre les opérations et utilisation de parenthèse.
- Gestion d'exception statique : variable déjà déclarée, non déclarée, non initialisée.
- Gestion de la structure conditionnelle if... else ... avec des conditions de comparaison ("==", "!=", "<" ">")
- Gestion de boucle while avec les mêmes conditions de comparaison.
- Déclaration et appel de fonction personnelle de la forme "int function (int parameter)"


# Limites connues
Notre compilateur ne gère pas l'ensemble du langage C. Nous avons identifié quelques limites dont voici une liste non exhaustive : <br>

- Gestion de tableaux non implémentée.
- Opération unaires ("-" , "!", ...) non implémentée
- Pas de gestion de variable globale.
- Pas de possibilité d'avoir plusieurs return dans une fonction.
- Boucle for non implémentée.
- Pas de possibilité d'imbriquer des structures conditionnelles "if"
- Opérateurs logiques ||, &&, ! non implémentée.

 
## Changement après la présentation

Nous avons modifié notre grammaire pour que les affectations soient gérées en dehors des expressions pour pouvoir vérifier que l'élément à gauche du '=' soit toujours une variable et jamais une expression (a+b=2 est incorrect).
Nous avons également modifié notre gestion des fonctions. Il est possible d'initialiser une fonction avec plusieurs arguments de type int (ou aucun), en revanche on ne peux appeler que des fonctions à un argument entier. La gestion des fonctions reste limitée est entraine toujours des problèmes de changement de valeurs des arguments.