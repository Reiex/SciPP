# Mise en place de SciPP

* [Installation des dépendances et téléchargement de SciPP](#dependances)
* [Utilisation de SciPP en lignes de commandes](#commandes)
* [Utilisation de SciPP avec Visual Studio](#visual-studio)
* [Tester SciPP](#tests)

## <a name="dependances"></a> Installation des dépendances et téléchargement de SciPP

SciPP est dépendant de la SFML, celle-ci doit donc être installée. Pour savoir comment l'installer, vous pouvez vous rendre sur [le site de la SFML](https://www.sfml-dev.org/). Pour le cas des distributions linux issues de Debian, l'installation se limite à l'execution de la commande:

```bash
sudo apt-get install libsfml-dev
```

SciPP quant à lui est disponible sur le dépot [Github](https://github.com/Reiex/SciPP). Il suffit donc de cloner le projet:

```bash
git clone git@github.com:Reiex/SciPP.git
```

## <a name="commandes"></a> Utilisation de SciPP en lignes de commandes

La bibliothèque possède une version compilée sous forme de librairie partagée. 
Pour l'utiliser rien de plus simple: il suffit d'extraire le sous-dossier `SciPP` du dossier `include` du dépot git et de le placer avec vos sources.
Ce dossier contient tout les headers de la bibliothèque ainsi que la version compilée dans un sous-dossier `bin`.
Ainsi, pour utiliser la bibliothèque il suffit d'insérer au début de vos sources la ligne:

```cpp
#include "SciPP/SciPP.h"
```

Vous pouvez ensuite compiler vos sources et construire directement un executable en le liant à la SFML et à la version compilée de SciPP. Par exemple avec g++:

```bash
g++ -o monProgramme.o -c monProgramme.cpp 
g++ monProgramme.o -o MonProgramme SciPP/bin/libSciPP.so -lsfml-graphics -lsfml-window -lsfml-system
```

Vous pouvez enfin executer votre programme comme n'importe quel autre executable avec la commande:
```bash
./MonProgramme
```

## <a name="visual-studio"></a> Utilisation de SciPP avec Visual Studio

Un exemple de solution `.sln` de visual studio est disponnible sur le git.

Cette solution contient trois projets:
* Le projet SciPP permet de compiler statiquement SciPP à partir de ses sources et de la SFML en supposant son répertoire d'installation dans `D:/Programmation/Cpp/SFML`.
* Le projet SciPPExamples permet de compiler un programme exemple utilisant SciPP (il ne nécessite plus l'utilisation des `.lib` de la SFML mais nécessite toujours ses headers).
* Le projet SciPPTests permet de compiler la base de tests de SciPP (il ne nécessite plus l'utilisation des `.lib` de la SFML mais nécessite toujours ses headers).

Une solution moins optimale est d'utiliser directement la version compilée statiquement obtenue à partir du projet SciPP: `include/SciPP/bin/SciPP.lib`.

## <a name="tests"></a> Tester SciPP

Une banque de tests est développée pour SciPP dans le sous-dossier `src/tests`. Pour lancer les tests, il suffit de lancer la commande
```bash
make check
```
