#pragma once

#include <string>
#include <sstream>
#include <complex>


// Templates sp�cifiques

/*
	T::T(T const&)
	T& T::operator*(T const&, T const&)
*/
template<typename T> T expoRapide(T const& x, int n)
{
	if (n < 1)
		throw "n doit etre superieur a 1.";

	if (n == 1)
		return x;

	int k(n - 1);
	T r(x), p(x);

	while (k != 0)
	{
		if (k % 2 == 0)
		{
			p *= p;
			k /= 2;
		}
		else
		{
			r *= p;
			k -= 1;
		}
	}

	return r;
}

/*
	T::T(int)
	T::T(T const&)
	T operator%(T const&, T const&)
	bool operator==(T const&, T const&)
	bool operator!=(T const&, T const&)
*/
template<typename T> T pgcd(T const& a, T const& b)
{
	T zero(0);
	if (a == zero || b == zero)
		return T(1);

	T u(a), v(b), r(u % v);

	while (r != zero)
	{
		u = v;
		v = r;
		r = u % v;
	}

	return v;
}


// Inclusions

#include "Entier.h"
#include "Fraction.hpp"
#include "Liste.hpp"
#include "Vecteur.hpp"
#include "Polynome.hpp"
#include "Matrice.hpp"
#include "Plot.h"
#include "Interpreteur.h"


// Constantes

long double const PI = 3.141592653589793;
long double const E = 2.7182818284590452;


// Fonctions spécifiques

long long int binom(int n, int p);

std::string decimales(Fraction<Entier> const& x, int n);
std::ostream& operator<<(std::ostream& stream, Fraction<Entier> const& x);

Vecteur<std::complex<long double>> DFT(Vecteur<std::complex<long double>> const& v);
Vecteur<std::complex<long double>> IDFT(Vecteur<std::complex<long double>> const& v);
Matrice<std::complex<long double>> DFT2D(Matrice<std::complex<long double>> const& M);
Matrice<std::complex<long double>> IDFT2D(Matrice<std::complex<long double>> const& M);
Matrice<long double> poissonSolveur(Matrice<long double> const& f, long double Lx, long double Ly);
Matrice<long double> cholesky(Matrice<long double> const& A);