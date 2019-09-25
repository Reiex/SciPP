#pragma once

#include "SciPP.h"


class Point;

class Force
{
	public:

		Vecteur<double> operator()(Point p, double t, double dt);

	private:

		Vecteur<double> (*m_func)(Point, double, double);
};

class Point
{
	public:

		Point(double x, double y, double m);

	private:

		double m_x;
		double m_y;
		double m_m;
		double m_dx;
		double m_dy;
		std::vector<Force> m_forces;
};


void simuDispersionVorticite(int Nx = 100, int Nt = 500, long double kappa = 0.01, long double t_simu = 7.5);

void simuFluide2D(int Nx = 60, int Ny = 60, long double t_simu = 7.5, long double nu = 0.0001, long double rho = 30, long double delta = 0.05, long double Lx = 1, long double Ly = 1);
