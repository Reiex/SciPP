#pragma once

#include <string>
#include <sstream>
#include <complex>

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


// Fonctions specifiques

std::string decimales(Fraction<Entier> const& x, int n);
std::ostream& operator<<(std::ostream& stream, Fraction<Entier> const& x);

Vecteur<std::complex<long double>> DFT(Vecteur<std::complex<long double>> const& v);
Vecteur<std::complex<long double>> IDFT(Vecteur<std::complex<long double>> const& v);
Matrice<std::complex<long double>> DFT2D(Matrice<std::complex<long double>> const& M);
Matrice<std::complex<long double>> IDFT2D(Matrice<std::complex<long double>> const& M);
Matrice<long double> poissonSolveur(Matrice<long double> const& f, long double Lx, long double Ly);
Matrice<long double> cholesky(Matrice<long double> const& A);