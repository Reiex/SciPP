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

/**
 * \brief Affiche le champ vectoriel `f` dans le cadre défini par `coord`
 * 
 * `coord` doit être un vecteur de 4 nombres représentant le coin supérieur gauche, la largeur
 * et la hauteur du cadre d'affichage.
*/
void plotChampVect2D(Vect<double>(*f)(Vect<double>), Vect<double> coord);
/**
 * \brief Affiche et lance une interraction avec le champ vectoriel `f` en le considérant comme le flot d'une fonction.
 * 
 * On considère l'équation:
 * \f[ x' = f(x) \f]
 * 
 * Cette fonction affiche le champ vectoriel `f` et pour une condition initiale \f$x_0\f$ indiquée
 * par un clic, affiche une approximation de la fonction \f$x\f$.
 * 
 * - `coord` a ici le même rôle que dans plotChampVect2D.
 * - `precision` est inversement proportionnel à la taille du "pas" effectué par l'integrateur au moment
 * de l'approximation de \f$x\f$.
 * - `distCourbe` indique la longueur de la courbe d'approximation calculée. Le seul moyen d'avoir une
 * courbe de longueur inférieure est de trouver un point d'équilibre du champ vectoriel.
*/
void plotFlot2D(Vect<double>(*f)(Vect<double>), Vect<double> coord, int precision = 10000, double distCourbe = 100);

/**
 * \brief Retourne la courbe de Bézier associée au polygone de contrôle décrit en argument.
 * 
 * Le vecteur retourné est de taille 2: il contient la liste des abscisses des points de la courbe
 * et la liste des ordonnées des points de la courbe.
*/
Vect<Vect<long double>> getBezier(Vect<long double> const& x, Vect<long double> const& y, int nbPoints = 1000);
/**
 * \brief Permet de créer dynamiquement une courbe de Bézier.
 * 
 * Pour une courbe de Bézier initiale de points de contrôle (x, y), cette fonction permet de
 * dessiner une courbe de Bézier dynamiquement avec la souris.
 * On peut zoomer/dézoomer avec la molette et placer un point de contrôle avec un clic.
 * 
 * La fonctione retourne ensuite un vecteur de taille 4 contenant dans l'ordre:
 * - La liste des abscisses des points de la courbe
 * - La liste des ordonnées des points de la courbe
 * - La liste des abscisses des points de contrôle de la courbe
 * - La liste des ordonnées des points de contrôle de la courbe
*/
Vect<Vect<long double>> plotBezier(Vect<long double> const& x = Vect<long double>(0), Vect<long double> const& y = Vect<long double>(0));

/**
 * \brief Cette fonction est identique à getBezier() mais pour une courbe de Hermite.
 * 
 * `mx` et `my` désignent la dérivée de la courbe aux points de contrôle.
*/
Vect<Vect<long double>> getHermite(Vect<long double> const& x, Vect<long double> const& y, Vect<long double> const& mx, Vect<long double> const& my, int nbPoints = 1000);
/**
 * \brief Permet de créer dynamiquement une courbe de Hermite.
 * 
 * Pour une courbe de Hermite initiales de points de contrôle et dérivées aux points de contrôle
 * (x, y, mx, my), cette fonction permet de dessiner une courbe de Hermite dynamiquement avec la souris.
 * On peut zoomer/dézoomer avec la molette, placer un point de contrôle avec un clic et déterminer
 * une dérivée en déplaçant les points rouges avec la souris.
 * 
 * On peut également lisser les dérivées automatiquement en appuyant sur la barre espace puis modifier
 * le paramètre de lissage avec les fleches directionnelles verticales.
 * Le lissage utilisé est celui de getSmoothDerivatives(), les fleches directionnelles permettant
 * d'augmenter ou de diminuer c de 0,1.
 * 
 * La fonction retourne ensuite un vecteur de taille 6 contenant dans l'ordre:
 * - La liste des abscisses des points de la courbe
 * - La liste des ordonnées des points de la courbe
 * - La liste des abscisses des points de contrôle de la courbe
 * - La liste des ordonnées des points de contrôle de la courbe
 * - La liste des abscisses des dérivées aux points de contrôle de la courbe
 * - La liste des ordonnées des dérivées aux points de contrôle de la courbe
*/
Vect<Vect<long double>> plotHermite(Vect<long double> const& x = Vect<long double>(0), Vect<long double> const& y = Vect<long double>(0), Vect<long double> const& mx = Vect<long double>(0), Vect<long double> const& my = Vect<long double>(0));
/**
 * \brief Permet de lisser une courbe de Hermite en calculant des dérivées adéquates aux points de contrôles.
 * 
 * Le lissage choisi est le suivant:
 * - Si le point de contrôle est à une extremité, la dérivée est posée nulle.
 * - Sinon, pour \f$P_k\f$ le k-ieme point de contrôle:
 * \f[ m_k = (1-c)(P_{k+1} - P_{k-1}) \f]
 * 
 * Cette fonction retourne un vecteur contenant:
 * - La liste des abscisses des dérivées aux points de contrôle de la courbe
 * - La liste des ordonnées des dérivées aux points de contrôle de la courbe
*/
Vect<Vect<long double>> getSmoothDerivatives(Vect<long double> const& x, Vect<long double> const& y, long double c);

/** \brief Cette fonction est identique à getBezier() mais pour une interpolation de Lagrange */
Vect<Vect<long double>> getLagrange(Vect<long double> const& x, Vect<long double> const& y, int nbPoints = 1000);
/** \brief Cette fonction est identique à plotBezier() mais pour une interpolation de Lagrange */
Vect<Vect<long double>> plotLagrange(Vect<long double> const& x = Vect<long double>(0), Vect<long double> const& y = Vect<long double>(0));

/**
 * \brief Retourne une courbe approchée de la fonction de courbure de la courbe (x, y).
 * 
 * On suppose pour cela que le pas de temps entre deux points de la courbe passée en paramètres
 * est constant.
 * 
 * De plus la courbure calculée n'est que proportionnelle à la courbure réelle.
 * Pour obtenir la courbure réelle, il faut en effet diviser le résultat obtenu par le pas de temps
 * mis au carré.
*/
Vect<long double> getCourbure(Vect<long double> const& x, Vect<long double> const& y);