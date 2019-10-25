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
	// plotBezier(Vecteur<long double>(0), Vecteur<long double>(0));
	// systemeD();
	// fonctionLogistique();
	// mandelbrot(-0.76, 0.1, 100); // mandelbrot(0.33, 0.552, 1000);
	// dispertionChaleur2D(100, 100, 0.1);

	Timeline timeline;
	Vecteur<long double> x(3), y(3), mx(3), my(3);
	x[0] = 0; y[0] = 1;
	x[1] = 1; y[1] = -1;
	x[2] = 3; y[2] = -2;
	mx[0] = 2; my[0] = 2;
	mx[1] = -10; my[1] = 0;
	mx[2] = -10; my[2] = 0;

	Vecteur<Vecteur<long double>> courbe(getHermite(x, y, mx, my));

	timeline.plot(courbe[0], courbe[1]);

	Timeline::show();

	return 0;
}
