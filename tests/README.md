# Framework de tests

Ce dossier contient des scripts pour tester le compilateur ainsi qu'un ensemble de codes sources en C pouvant être testés.

## Prérequis

Docker doit être installé afin de pouvoir exécuter ces scripts. Le compilateur doit être présent dans le répertoire `../compiler/ifcc`. Les options et la location du compilateur peuvent être modifiées dans le script `pld-wrapper.sh`.

## Fichiers

`test.sh` est le fichier de base à lancer. Il appelle l'image Docker appropriée et exécute le script `pld-test.py`. Les résultats sont placés dans le nouveau répertoire `pld-test-outputs`.

Les tests sont dans le sous-dossier `tests`.

## Résultats des tests

### Déclaration et affectation

`2-12_affect_with_non_init_expr.c` : si une variable non initialisée est appelée A COMPLETER
`2-13_affectation_out_of_range.c` : notre compilateur n'accepte pas l'affectation à un int d'une valeur supérieure au range d'un int et rejette donc le programme.
`2-14_declaration_global_var.c` : la gestion des variables globales n'est pas implémentée dans notre compilateur
`2-15_affectation_global_var.c` : idem
`2-16_use_global_var.c` : idem

### Expressions

`3-4_div.c` : la division n'est pas implémentée dans notre compilateur