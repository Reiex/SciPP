# SciPP - Bibliothèque scientifique en C++

## Description

SciPP est une petite bibliothèque scientifique développée en C++ avec la SFML.
Elle implémente entre autres un module de gestion d'entiers (big int), de gestion de matrices et de dessin scientifique.

## Compilation et execution d'un projet

SciPP est dépendant de la SFML, il faut donc l'installer au préalable.

`sudo apt-get install libsfml-dev`

Vous pouvez également regarder directement sur le site de la SFML: [https://www.sfml-dev.org](https://www.sfml-dev.org)

---

Pour l'instant la bibliothèque ne possède pas de version compilée exportable, il faut donc la compiler soit même pour l'utiliser.
Il suffit pour cela de s'inspirer du Makefile présent dans le dépot qui permet de compiler le code exemple.
Les règles de compilation principales sont:
- `SciPP`: permet de compiler le projet
- `clean`: permet de supprimer les fichiers `.o` créés à la compilation


---

Il suffit ensuite d'executer le fichier généré:

`./SciPP`

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