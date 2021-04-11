# Framework de tests

Ce dossier contient des scripts pour tester le compilateur ainsi qu'un ensemble de codes sources en C pouvant être testés.

## Prérequis

Docker doit être installé afin de pouvoir exécuter ces scripts. Le compilateur doit être présent dans le répertoire `../compiler/ifcc`. Les options et la location du compilateur peuvent être modifiées dans le script `pld-wrapper.sh`.

## Fichiers

`test.sh` est le fichier de base à lancer. Il appelle l'image Docker appropriée et exécute le script `pld-test.py`. Les résultats sont placés dans le nouveau répertoire `pld-test-outputs`.

Les tests sont dans le sous-dossier `tests`.

## Résultats des tests

### Déclaration et affectation

`2-12_affect_with_non_init_expr.c` : Si une variable non initialisée est appelée, notre compilateur comme gcc ont des comportements particuliers mais différents
`2-13_affectation_out_of_range.c` : Notre compilateur n'accepte pas l'affectation à un int d'une valeur supérieure au range d'un int et rejette donc le programme.
`2-14_declaration_global_var.c` : La gestion des variables globales n'est pas implémentée dans notre compilateur.
`2-15_affectation_global_var.c` : Idem.
`2-16_use_global_var.c` : Idem.

### Expressions

`3-4_div.c` : La division n'est pas implémentée dans notre compilateur.
`3-33_negative_number_affectation.c` : Le - unaire n'est pas implémenté dans notre compilateur.
`3-35_minus_variable.c` : Idem.

### Return

`4-3_no_return.c` : Notre compilateur génère de l'assembleur à partir du moment où il détecte un return à la fin de main() ; en l'absence de return, aucun assembleur n'est produit, alors que gcc retourne 0 par défaut.
`4-4_several_returns.c` : S'il y a plusieurs return dans main(), gcc s'arrête au premier alors que notre compilateur génère dans l'assembleur autant de fonctions main qu'il y a de return.
`4-7_return_several_things.c` : Si le return est suivi de plusieurs variables ou valeurs (ex : `return a, b;`), gcc retourne la dernière des valeurs tandis que notre compilateur rejette le programme.
`4-9_return_out_of_range.c` : Si la valeur de return est hors du range d'un int, notre compilateur rejette le programme (même problème que pour l'affectation hors du range).
`4-11_negative_return.c` : Le - unaire n'étant pas implémenté, notre compilateur n'accepte pas de valeur de retour négative.

### Fonctions

### If

`6-16_multi_return.c` : S'il y a un return dans le bloc if et un autre dans le bloc else, notre compilateur génère autant de main dans l'assembleur qu'il n'y a de return.
`6-18_if_nested_in_else.c` : L'imbrication des if n'est pas implémentée dans notre compilateur.
`6-20_three_if_all_false.c` : Idem.
`6-21_variable_reach.c` : Si une variable est déclarée dans un bloc if, notre compilateur permet de l'utiliser en dehors de la portée du if.
`6-23_condition_without_operator.c` : Notre compilateur ne permet de tester que des expressions contenant un opérateur logique, et pas d'expressions de type `if(2)`.
`6-24_false_condition_without_operator.c` : Idem.