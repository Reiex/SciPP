#pragma once

/**
 * \file simuPhysique.h
 * \brief Fichier d'exemples d'applications de la bibliothèque SciPP à la simulation de phénomènes physiques
 * 
 * Ce fichier est à but didactique et implémente quelques fonctions utilisant la bibliothèque SciPP
 * pour montrer son utilisation dans le cadre de la simulation de phénomènes physiques divers.
*/

#include "../SciPP/SciPP.h"


class Point;

class Force
{
	public:

		Force();
		void setFunc(Vect<double>(*func)(Point));
		Vect<double> operator()(Point p);

	private:

		Vect<double> (*m_func)(Point);
};

class Point
{
	public:

		Point(double x, double y, double m);

		void ajouterForce(Force f);
		void setVitesse(double vx, double vy);
		void setDt(double dt);
		Vect<double> getEtat() const;

		void update();

	private:

		double m_x;
		double m_y;
		double m_m;
		double m_dx;
		double m_dy;
		double m_dm;
		double m_dt;
		std::vector<Force> m_forces;
};


void simuDispersionVorticite(int Nx = 100, int Nt = 500, long double kappa = 0.01, long double t_simu = 7.5);

void simuFluide2D(int Nx = 60, int Ny = 60, long double t_simu = 7.5, long double nu = 0.0001, long double rho = 30, long double delta = 0.05, long double Lx = 1, long double Ly = 1);

void simuBalle(long double t = 10, long double x = 0, long double y = 10, long double vx = 0, long double vy = 0);

void integrationFlot();

void dispertionChaleur2D(int Nx, int Ny, double t_simu);
