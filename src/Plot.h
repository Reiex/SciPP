#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "SciPP.h"

struct Courbe
{
	sf::VertexArray* figure;
	long double min_x;
	long double max_x;
	long double min_y;
	long double max_y;
	Courbe* suivante;
};

void plot(Vecteur<long double> x, Vecteur<long double> y);

void plot(Matrice<long double> M, long double min_z, long double max_z);

void show(int framerate=24, bool animationCourbe=false);
