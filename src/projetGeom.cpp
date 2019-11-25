#include "projetGeom.hpp"

void mainProjetGeom()
{
    // Question 2

    plotBezier();

    // Question 3

    /*
        Voir getSmoothDerivatives de Plot.cpp

        Le choix aux bords est ici de prendre la dérivée nulle.
    */

    // Question 4

	plotHermite();

    /*
        On active le lissage avec espace avec c = 0, puis on peut faire varier c avec les flèches
        vers le haut ou le bas
    */

    // Question 6

    plotHermite();

    // Question 7

	plotLagrange();
}
