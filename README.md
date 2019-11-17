# SciPP - Bibliothèque scientifique en C++

## Description

SciPP est une petite bibliothèque scientifique développée en C++ avec la SFML.
Elle implémente entre autres un module de gestion d'entiers (big int), de gestion de matrices et de dessin scientifique.

## Compilation et execution d'un projet

SciPP est dépendant de la SFML, il faut donc l'installer au préalable.
``` sudo apt-get install libsfml-dev ```
Vous pouvez également regarder directement sur le site de la SFML: [https://www.sfml-dev.org](https://www.sfml-dev.org)

---

Pour l'instant la bibliothèque n'est pas encore prévue pour être exportée pour des projets autres que les exemples fournis.
Il faut donc recompiler la bibliothèque pour l'utiliser par ailleurs.
Il suffit pour cela de s'inspirer du Makefile présent dans le dépot qui permet de compiler l'exemple.
Les règles de compilation principales sont:
- `SciPP`: permet de compiler le projet
- `clean`: permet de supprimer les fichiers `.o` créés à la compilation

## Documentation du projet

A venir...
