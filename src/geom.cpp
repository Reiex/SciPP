#include "geom.h"


// Courbes de Bézier

Polynome<long double> bernstein(int n, int i)
{
    long double tab[2] = {0, 1};
    long double coeff(binom(n, i));

	if (n == 0)
		return coeff;
	if (i == 0)
		return coeff * expoRapide(Polynome<long double>(1) - Polynome<long double>(tab, 2), n - i);
	if (i == n)
		return coeff * expoRapide(Polynome<long double>(tab, 2), i);

    return Polynome<long double>(coeff) * expoRapide(Polynome<long double>(tab, 2), i) * expoRapide(Polynome<long double>(1) - Polynome<long double>(tab, 2), n - i);
}

void bezier(Vecteur<long double> const& x, Vecteur<long double> const& y, bool contour)
{
    if (x.taille() != y.taille())
        throw "Les vecteurs x et y doivent être de même taille !";

    int n(x.taille());
    Polynome<long double> Bx, By;

    for (int i(0); i < n; i++)
    {
		Bx += Polynome<long double>(x[i]) * bernstein(n-1, i);
		By += Polynome<long double>(y[i]) * bernstein(n - 1, i);
    }

	int nbPoints(1000);
	Vecteur<long double> xCourbe(nbPoints), yCourbe(nbPoints);
	for (int i(0); i < nbPoints; i++)
	{
		xCourbe[i] = Bx(double(i) / nbPoints);
		yCourbe[i] = By(double(i) / nbPoints);
	}

	Timeline timelineA;
	timelineA.plot(xCourbe, yCourbe);
	if (contour)
	{
		Timeline timelineB;
		timelineB.plot(x, y);
		Timeline::show();
	}
	else
	{
		Timeline::show();
	}
	
}
