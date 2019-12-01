#pragma once

/**
 * \file Plot.h
 * \brief Ensemble des fonctions et classes permettant l'affichage de données à l'écran.
 * \author Reiex
 * 
 * Pour les affichages les plus basiques - courbes simples ou animées, champs scalaires - la classe
 * Timeline a été mise en place. Plus de détails sont disponnibles dans la description de cette
 * classe.
 * 
 * Pour les affichages plus complexes - affichage de champs vectoriels, affichages avec interractions
 * avec l'utilisateur - des fonctions plus spécifiques ont été mises en place.
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
 * 
 * Chaque timeline a une frequence d'actualisation indépendante et boucle sur ses courbes affichées.
 * C'est donc à l'utilisateur de bien manipuler la fréquence d'actualisation et les courbes
 * enregistrées pour afficher l'animation désirée.
 * 
 * Il faut de plus savoir que l'affichage de champs scalaires et de courbes est exclusif dans une
 * même timeline. Il est donc possible d'afficher une courbe animée dans une timeline en même
 * temps qu'un champs scalaire dans une autre timeline, mais il est impossible d'afficher dans
 * une même timeline une courbe puis un champs scalaire.
 * 
 * Enfin, plusieurs champs scalaires ne peuvent pas être affichés en même temps. Une seule timeline
 * doit donc contenir des champs scalaires.
*/
class Timeline
{
	public:

		static int TAILLE_PLOT[];

		/** \brief Constructeur par défaut d'une timeline. */
		Timeline();

		/** 
		 * \brief Permet de changer la fréquence d'actualisation de la timeline lors de l'affichage.
		 * 
		 * L'unité est l'image par seconde. Par défaut, une timeline affiche 24 courbes ou champs
		 * scalaires par seconde.
		*/
		void setFramerate(int framerate);
		/** \brief Permet de modifier la couleur de la courbe affichée (ne s'applique pas pour les champs scalaires). */
		void setColor(int r, int g, int b);

		/**
		 * \brief Ajoute un point aux courbes affichées par la timeline.
		 * 
		 * Un point seul, pour être affiché lisiblement, doit avoir une épaisseur. Par défaut,
		 * utiliser Timeline::plot(Vect<long double> x, Vect<long double> y) utilise des vertex
		 * qui n'ont donc pas d'épaisseur.
		 * Cette fonction affiche un disque de rayon 3 pixels à la place.
		*/
		void plot(long double x, long double y);
		/** \brief Ajoute une courbe affichée par la timeline. */
		void plot(Vect<long double> x, Vect<long double> y);
		/**
		 * \brief Ajouter un champ scalaire affiché par la timeline.
		 * 
		 * Les couleurs des pixels dans le champs scalaire seront calculées en considérant
		 * que `min_z` et `max_z` sont les valeurs minimales et maximales de la matrice M.
		*/
		void plot(Matrice<long double> M, long double min_z, long double max_z);

		/** \brief Permet de lancer l'affichage de toutes les courbes. */
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