#pragma once

#include "SciPP.h"


void simuDispersionVorticite(int Nx = 100, int Nt = 500, long double kappa = 0.01, long double t_simu = 7.5);

void simuFluide2D(int Nx = 60, int Ny = 60, long double t_simu = 7.5, long double nu = 0.0001, long double rho = 30, long double delta = 0.05, long double Lx = 1, long double Ly = 1);
