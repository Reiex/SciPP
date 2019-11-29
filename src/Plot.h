#pragma once

/**
 * \file Plot.h
 * \brief Ensemble des fonctions et classes permettant l'affichage de données à l'écran.
 * \author Reiex
 * 
 * Pour les affichages les plus basiques - courbes simples ou animées - la classe Timeline
 * a été mise en place. Plus de détails sont disponnibles dans la description de cette classe.
 * 
 * Pour les affichages plus complexes - affichage de champs scalaires, de champs vectoriels,
 * affichages avec interractions avec l'utilisateur - des fonctions plus spécifiques ont été
 * mises en place.
*/

#include <string>
#include <SFML/Graphics.hpp>
#include "Matrice.hpp"
#include "Polynome.hpp"

/**
 * \class Timeline
 * \brief Classe permettant la manipulation et l'affichages de courbes simples ou animées.
 * 
 * La classe Timeline représente, comme son nom l'indique, une ligne temporelle.
 * C'est en fait une suite de courbes qui seront affichées les unes à la suite des autres.
*/
class Timeline
{
	public:

		static int TAILLE_PLOT[];

		Timeline();

		void setFramerate(int framerate);
		void setColor(int r, int g, int b);

		void plot(long double x, long double y);
		void plot(Vect<long double> x, Vect<long double> y);
		void plot(Matrice<long double> M, long double min_z, long double max_z);

		static void show();

		~Timeline();

	private:

		static std::vector<Timeline*> timelineList;

		long double m_delay;
		std::vector<sf::VertexArray> m_courbes;
		std::vector<sf::Image> m_matrices;
		Vect<long double> m_border;
		bool m_borderSet;
		Vect<int> m_color;
};

void plotChampVect2D(Vect<double>(*f)(Vect<double>), Vect<double> coord);
void plotFlot2D(Vect<double>(*f)(Vect<double>), Vect<double> coord, int precision = 10000, double distCourbe = 100);

Vect<Vect<long double>> getBezier(Vect<long double> const& x, Vect<long double> const& y, int nbPoints = 1000);
Vect<Vect<long double>> plotBezier(Vect<long double> const& x = Vect<long double>(0), Vect<long double> const& y = Vect<long double>(0));

Vect<Vect<long double>> getHermite(Vect<long double> const& x, Vect<long double> const& y, Vect<long double> const& mx, Vect<long double> const& my, int nbPoints = 1000);
Vect<Vect<long double>> plotHermite(Vect<long double> const& x = Vect<long double>(0), Vect<long double> const& y = Vect<long double>(0), Vect<long double> const& mx = Vect<long double>(0), Vect<long double> const& my = Vect<long double>(0));
Vect<Vect<long double>> getSmoothDerivatives(Vect<long double> const& x, Vect<long double> const& y, long double c);

Vect<Vect<long double>> getLagrange(Vect<long double> const& x, Vect<long double> const& y, int nbPoints = 1000);
Vect<Vect<long double>> plotLagrange(Vect<long double> const& x = Vect<long double>(0), Vect<long double> const& y = Vect<long double>(0));