#include <stdlib.h>
#include <iostream>
#include "../SciPP/SciPP.h"
#include "simuPhysique.h"
#include "jeuxArithmetiques.h"


int main()
{
	// std::cout << neper(100) << std::endl << std::endl; system("pause");
	// simuDispersionVorticite(100, 1000);
	simuFluide2D(150, 150, 5);
	// lancerInterpreteur();
	// simuBalle();
	// integrationFlot();
	// fonctionLogistique();
	// mandelbrot(-0.76, 0.1, 100); // mandelbrot(0.33, 0.552, 1000);
	// dispertionChaleur2D(100, 100, 0.1);
	// conway();

	return 0;
}
