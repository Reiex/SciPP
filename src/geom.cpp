#include "geom.h"


// Courbes de Bézier

Polynome<long double> bernstein(int n, int i)
{
    long double tab[2] = {0, 1};
    long double coeff(binom(n, i));
    return Polynome<long double>(coeff)*expoRapide(Polynome<long double>(tab, 2), i)*expoRapide(Polynome<long double>(1) - Polynome<long double>(tab, 2), n - i);
}

void bezier(Vecteur<long double> const& x, Vecteur<long double> const& y)
{
    if (x.taille() != y.taille())
        throw "Les vecteurs x et y doivent être de même taille !";

    int n(x.taille());
    Polynome<long double> Bx, By;

    for (int i(0); i < n; i++)
    {

    }
}
