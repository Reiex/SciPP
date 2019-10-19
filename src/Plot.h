#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "SciPP.h"

class Timeline
{
	public:

		Timeline();

		void setFramerate(int framerate);

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
};

void plotChampVect2D(Vecteur<double>(*f)(Vecteur<double>), Vecteur<double> coord);

void plotFlot2D(Vecteur<double>(*f)(Vecteur<double>), Vecteur<double> coord, int precision = 10000, double distCourbe = 100);
