#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Matrice.hpp"
#include "Polynome.hpp"

class Timeline
{
	public:

		static int TAILLE_PLOT[];

		Timeline();

		void setFramerate(int framerate);
		void setColor(int r, int g, int b);

		void plot(long double x, long double y);
		void plot(Vecteur<long double> x, Vecteur<long double> y);
		void plot(Matrice<long double> M, long double min_z, long double max_z);

		static void show();

		~Timeline();

	private:

		static std::vector<Timeline*> timelineList;

		long double m_delay;
		std::vector<sf::VertexArray> m_courbes;
		std::vector<sf::Image> m_matrices;
		Vecteur<long double> m_border;
		bool m_borderSet;
		Vecteur<int> m_color;
};

void plotChampVect2D(Vecteur<double>(*f)(Vecteur<double>), Vecteur<double> coord);

void plotFlot2D(Vecteur<double>(*f)(Vecteur<double>), Vecteur<double> coord, int precision = 10000, double distCourbe = 100);

Vecteur<Vecteur<long double>> getBezier(Vecteur<long double> const& x, Vecteur<long double> const& y, int nbPoints = 1000);

void plotBezier(Vecteur<long double> const& x, Vecteur<long double> const& y);

Vecteur<Vecteur<long double>> getHermite(Vecteur<long double> const& x, Vecteur<long double> const& y, Vecteur<long double> const& mx, Vecteur<long double> const& my, int nbPoints = 1000);

void plotHermite(Vecteur<long double> const& x, Vecteur<long double> const& y, Vecteur<long double> const& mx, Vecteur<long double> const& my);
