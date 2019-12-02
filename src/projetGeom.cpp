#include "projetGeom.hpp"

void mainProjetGeom()
{
    // Question 2

    // >plotBezier();

    // Question 3

    /*
        Voir getSmoothDerivatives de Plot.cpp

        Le choix aux bords est ici de prendre la dérivée nulle.
    */

    // Question 4

	// plotHermite();

    /*
        On active le lissage avec espace avec c = 0, puis on peut faire varier c avec les flèches
        vers le haut ou le bas
    */

    // Question 6

    int n(33);
    Vect<long double> x(n), y(n);
    x[0] = -0.16; y[0] = 0.218;
    x[1] = 0.058; y[1] = 0.22;
    x[2] = 0.22; y[2] = 0.221667;
    x[3] = 0.28; y[3] = 0.203333;
    x[4] = 0.283333; y[4] = 0.166667;
    x[5] = 0.245; y[5] = 0.155;
    x[6] = 0.2; y[6] = 0.15;
    x[7] = 0.166667; y[7] = 0.13;
    x[8] = 0.173333; y[8] = 0.0383333;
    x[9] = 0.195; y[9] = -0.0666667;
    x[10] = 0.213333; y[10] = -0.0816667;
    x[11] = 0.231667; y[11] = -0.0733333;
    x[12] = 0.258333; y[12] = -0.0716667;
    x[13] = 0.258333; y[13] = -0.0983333;
    x[14] = 0.228333; y[14] = -0.126667;
    x[15] = 0.168333; y[15] = -0.133333;
    x[16] = 0.125; y[16] = -0.005;
    x[17] = 0.105; y[17] = 0.11;
    x[18] = 0.0916667; y[18] = 0.138333;
    x[19] = 0.0483333; y[19] = 0.151667;
    x[20] = 0.0183333; y[20] = 0.135;
    x[21] = 0.0133333; y[21] = 0.0816667;
    x[22] = 0.025; y[22] = -0.11;
    x[23] = 0.015; y[23] = -0.15;
    x[24] = -0.0216667; y[24] = -0.146667;
    x[25] = -0.0433333; y[25] = -0.0733333;
    x[26] = -0.055; y[26] = 0.10;
    x[27] = -0.0633333; y[27] = 0.141667;
    x[28] = -0.0933333; y[28] = 0.155;
    x[29] = -0.153333; y[29] = 0.156667;
    x[30] = -0.18; y[30] = 0.176667;
    x[31] = -0.181667; y[31] = 0.208333;
    x[32] = -0.16; y[32] = 0.218;

    Timeline timeline;
    Vect<Vect<long double>> derivees(getSmoothDerivatives(x, y, 0));
    Vect<Vect<long double>> courbe(getHermite(x, y, derivees[0], derivees[1], 10000));

    timeline.plot(x, y);
    timeline.plot(courbe[0], courbe[1]);
    timeline.setFramerate(1);
    Timeline::show();

    Vect<long double> c(getCourbure(courbe[0], courbe[1]));
    Vect<long double> t(courbe[0].taille() - 2);
    for (int i(0); i < courbe[0].taille() - 2; i++)
        t[i] = i;

    timeline = Timeline();
    timeline.plot(t, c);
    Timeline::show();

    // Question 7

	// plotLagrange();
}
