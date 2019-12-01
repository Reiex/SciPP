# SciPP - Bibliothèque scientifique en C++

## Description

SciPP est une petite bibliothèque scientifique développée en C++ avec la SFML.
Elle implémente entre autres un module de gestion d'entiers (big int), de gestion de matrices et de dessin scientifique.

## Compilation et execution d'un projet

### Installation des dépendances

SciPP est dépendant de la SFML, il faut donc l'installer au préalable.

`sudo apt-get install libsfml-dev`

Vous pouvez également regarder directement sur le site de la SFML: [https://www.sfml-dev.org](https://www.sfml-dev.org)

### Compilation

La bibliothèque possède désormais une version compilée exportable. Pour l'utiliser rien de plus simple. Il suffit d'extraire le dossier `SciPP` du dossier `include` du dépot git
et de le placer avec vos sources.
Ce dossier contient tout les headers de la bibliothèque ainsi qu'une version compilée dans un sous-dossier `bin`.
Ainsi, pour utiliser la bibliothèque il suffit d'insérer au début de vos sources la ligne:
```cpp
#include "SciPP/SciPP.h"
```

Vous pouvez ensuite compiler vos sources et construire directement un executable. Par exemple avec g++:
```shell
g++ -o monProgramme.o -c monProgramme.cpp 
g++ monProgramme.o -o MonProgramme SciPP/bin/SciPP.a -lsfml-graphics -lsfml-window -lsfml-system
```

### Execution

Il suffit ensuite d'executer le fichier généré:

`./MonProgramme`

## Documentation du projet

Cette bibliothèque possède deux documentations. La première, générée avec Doxygen, se base sur des commentaires du code. La seconde est celle que vous lisez actuellement, composée de README au format markdown.

La documentation Doxygen doit être générée par l'utilisateur, pour cela rien de plus simple, il suffit d'installer puis de lancer Doxygen:
```shell
sudo apt-get install doxygen graphviz
make doxy
```

**Avancement:**
- La documentation doxygen est en cours d'écriture
- La documentation README viendra ensuite