# Framework de tests

Ce dossier contient des scripts pour tester le compilateur ainsi qu'un ensemble de codes sources en C pouvant être testés.

## Prérequis

Docker doit être installé afin de pouvoir exécuter ces scripts. Le compilateur doit être présent dans le répertoire `../compiler/ifcc`. Les options et la location du compilateur peuvent être modifiées dans le script `pld-wrapper.sh`.

## Fichiers

`test.sh` est le fichier de base à lancer. Il appelle l'image Docker appropriée et exécute le script `pld-test.py`. Les résultats sont placés dans le nouveau répertoire `pld-test-outputs`.

Les tests sont dans le sous-dossier `tests`.

## Test results