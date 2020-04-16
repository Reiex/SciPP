#pragma once

/**
 * \file SciPP.h
 * \brief Fichier d'inclusion, c'est ce fichier qui doit ête inclus pour importer la bibliothèque SciPP.
*/

#include "List.hpp"
#include "Int.hpp"
#include "Frac.hpp"
#include "Liste.hpp"
#include "Vect.hpp"
#include "Polynome.hpp"
#include "Matrice.hpp"
#include "Plot.h"
#include "Interpreteur.h"

/**
 * \mainpage Documentation de SciPP
 * 
 * \section intro_sec Introduction
 * 
 * SciPP est une petite bibliothèque scientifique développée en C++ avec la SFML.
 * Elle implémente entre autres un module de gestion d'entiers (big int), de gestion de matrices et de dessin scientifique.
 *  
 * \section install_sec Utilisation de SciPP
 *  
 * ### Installation des dépendances
 * 
 * SciPP est dépendant de la SFML, il faut donc l'installer au préalable.
 * 
 * `sudo apt-get install libsfml-dev`
 * 
 * Vous pouvez également regarder directement sur le site de la SFML: [https://www.sfml-dev.org](https://www.sfml-dev.org)
 * 
 * ### Compilation
 * 
 * La bibliothèque possède désormais une version compilée exportable. Pour l'utiliser rien de plus simple: il suffit d'extraire le sous-dossier `SciPP` du dossier `include` du dépot git
 * et de le placer avec vos sources.
 * Ce dossier contient tout les headers de la bibliothèque ainsi qu'une version compilée dans un sous-dossier `bin`.
 * Ainsi, pour utiliser la bibliothèque il suffit d'insérer au début de vos sources la ligne:
 * ```cpp
 * #include "SciPP/SciPP.h"
 * ```
 * 
 * Vous pouvez ensuite compiler vos sources et construire directement un executable. Par exemple avec g++:
 * ```shell
 * g++ -o monProgramme.o -c monProgramme.cpp 
 * g++ monProgramme.o -o MonProgramme SciPP/bin/SciPP.a -lsfml-graphics -lsfml-window -lsfml-system
 * ```
 * 
 * ### Execution
 * 
 * Il suffit ensuite d'executer le fichier généré:
 * 
 * `./MonProgramme`
*/
