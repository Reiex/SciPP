#include <stdlib.h>
#include <iostream>
#include "SciPP.h"
#include "simuPhysique.h"
#include "jeuxArithmetiques.h"


int main()
{
	// std::cout << neper(500) << std::endl << std::endl; system("pause");
	// simuDispersionVorticite();
	// simuFluide2D();
	// lancerInterpreteur();
	// simuBalle();
	long double x[4] = { 0, -1, 0.5, 1 }, y[4] = { 0, 1, 0.75, 0.5 }; plotBezier(Vecteur<long double>(x, 4), Vecteur<long double>(y, 4));
	// systemeD();
	// fonctionLogistique();
	// mandelbrot(-0.76, 0.1, 100); // mandelbrot(0.33, 0.552, 1000);

	return 0;
}
