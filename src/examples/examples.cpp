#include <stdlib.h>
#include <iostream>
#include "../SciPP/SciPP.h"
#include "simuPhysique.h"
#include "jeuxArithmetiques.h"

int main()
{
	// std::cout << neper(100) << std::endl << std::endl; system("pause");
	// simuDispersionVorticite(100, 1000);
	simuFluide2D(64, 64, 5);
	// lancerInterpreteur();
	// simuBalle();
	// integrationFlot();
	// fonctionLogistique();
	// mandelbrot(-0.76, 0.1, 100); // mandelbrot(0.33, 0.552, 1000);
	// conway();
	// diffusionThermique(300, 300);
	// Int i(1000000000);  while (true) { if (isPrime(i)) std::cout << i << std::endl; i += 1; }
	// philipsWaves(128, 128, 30);

	return 0;
}
