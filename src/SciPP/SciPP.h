#pragma once

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
 *  SciPP est dépendant de la SFML, il faut donc l'installer au préalable.
 * 
 * `sudo apt-get install libsfml-dev`
 * 
 * Vous pouvez également regarder directement sur le site de la SFML: [https://www.sfml-dev.org](https://www.sfml-dev.org)
 * 
 * ---
 * 
 * Pour l'instant la bibliothèque ne possède pas de version compilée exportable, il faut donc la compiler soit même pour l'utiliser.
 * Il suffit pour cela de s'inspirer du Makefile présent dans le dépot qui permet de compiler le code exemple.
 * Les règles de compilation principales sont:
 * 	- `SciPP`: permet de compiler le projet
 * 	- `clean`: permet de supprimer les fichiers `.o` créés à la compilation
 * 
 * 
 * ---
 * 
 * Il suffit ensuite d'executer le fichier généré:
 * 
 * `./SciPP`
 * 
 * 
*/
