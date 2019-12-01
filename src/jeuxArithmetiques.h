#pragma once

/**
 * \file jeuxArithmetiques.h
 * \brief Fichier d'exemples d'applications de la bibliothèque SciPP à l'arithmétique
 * 
 * Ce fichier est à but didactique et implémente quelques fonctions utilisant la bibliothèque SciPP
 * pour montrer son utilisation dans le cadre de calculs arithmétiques.
*/

#include <iostream>
#include <sstream>
#include "SciPP.h"

std::string neper(int n);

void fonctionLogistique();

void mandelbrot(double xCentre, double yCentre, double zoom);

void conway();
