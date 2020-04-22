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
#include <exception>
#include <SFML/Graphics.hpp>
#include "List.hpp"
#include "Matrice.hpp"
#include "Polynome.hpp"

class CurveStyle
{
    public:

        enum class LinkStyle {
            Hidden,
            Line
        };

        enum class MarkerStyle {
            Hidden,
            Circle
        };

        CurveStyle();
        CurveStyle(MarkerStyle markerStyle, LinkStyle linkStyle, Vect<int> const& color);

        Vect<int> const& getColor() const;
        LinkStyle getLinkStyle() const;
        MarkerStyle getMarkerStyle() const;

    private:

        Vect<int> m_color;
        LinkStyle m_linkStyle;
        MarkerStyle m_markerStyle;
};

class MatrixStyle
{
    public:

        enum DisplayStyle {
            Flat,
            Smooth
        };

        MatrixStyle();
        MatrixStyle(DisplayStyle displayStyle, Vect<int> const& color);

        Vect<int> const& getColor() const;
        DisplayStyle getDisplayStyle() const;

    private:

        Vect<int> m_color;
        DisplayStyle m_displayStyle;
};

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

		static int WINDOW_SIZE[];

		/** \brief Erreur renvoyée lors d'une tentative de plot d'une matrice alors que des courbes font déjà partie de la timeline. */
		class IllegalMatrixPlotException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

        /** \brief Erreur renvoyée lors d'une tentative de plot d'une courbe alors que des matrices font déjà partie de la timeline. */
		class IllegalCurvePlotException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

        /** \brief Erreur renvoyée lors d'une tentative de plot d'une courbe où le nombre de coordonnées selon x et selon y n'est pas le même. */
        class InvalidCurveException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

		/** \brief Constructeur par défaut d'une timeline. */
		Timeline();

		/** 
		 * \brief Permet de changer la fréquence d'actualisation de la timeline lors de l'affichage.
		 * 
		 * L'unité est l'image par seconde. Par défaut, une timeline affiche 24 courbes ou champs
		 * scalaires par seconde.
		*/
		void setFramerate(int framerate);

		void setCurveStyle(CurveStyle style);
        void setMatrixStyle(MatrixStyle style);

		/** \brief Ajoute une courbe composée d'un seul point affichée par la timeline. */
		void plot(long double x, long double y);
		/** \brief Ajoute une courbe affichée par la timeline. */
		void plot(List<long double> const& x, List<long double> const& y);
		/** \brief Ajouter un champ scalaire affiché par la timeline. */
		void plot(Matrice<long double> const& M);

		/** \brief Permet de lancer l'affichage de toutes les courbes. */
		static void show();
        /** \brief Réinitialise la taille de la fenêtre à sa taille par défaut */
        static void resetWindowSize();

		~Timeline();

	private:

        static Vect<long double> computeBorders();
        static Vect<long double> computeMatrixLimits();

        void display(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, Vect<long double> const& matrixLimits, long double time) const;

        void drawLineLinkCurve(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, List<long double> const& x, List<long double> const& y) const;

        void drawCircleMarkerCurve(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, List<long double> const& x, List<long double> const& y) const;

        void drawFlatMatrix(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, Vect<long double> const& matrixLimits, Matrice<long double> const& M) const;
        void drawSmoothMatrix(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, Vect<long double> const& matrixLimits, Matrice<long double> const& M) const;

		static List<Timeline*> m_timelineList;

        int m_framerate;
		List<Vect<List<long double>>> m_curves;
		List<Matrice<long double>> m_matrices;
        CurveStyle m_curveStyle;
        MatrixStyle m_matrixStyle;
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