#pragma once

/**
 * \file Frac.hpp
 * \author Reiex
 * \brief Ensemble des fonctions et classes permettant la manipulation de fractions (pas forcément entre deux entiers).
 * 
 * Pour une description plus détaillée, voir la description de la classe Frac.
 * 
*/

#include <iostream>
#include <string>
#include <sstream>
#include "Int.hpp"

/**
 * \class Frac
 * \brief Classe permettant de manipuler des fractions (pas forcéments entre deux entiers).
 * \author Reiex
 * 
 * La classe Frac est template et prend en argument template une classe T.
 * La fraction sera entre deux objets de cette classe T qui peut représenter une multitude d'objets
 * mathématiques différents. Les exemples les plus communs sont pour T de prendre des Int (on obtient
 * alors des nombres rationnels) ou de prendre des Polynome (on obtient alors des fractions rationnels).
 * 
 * La classe Frac implémente les opérations de bases communes à tout type de fraction, des classes
 * plus spécifiées héritent ensuite de cette classe pour ajouter des fonctionnalités plus spécifiques,
 * comme la conversion en long double pour les rationnels.
 * Ces classes filles sont:
 * - Rationnel
 * 
 * Voici les fonctions qui doivent être définies par la classe T:
 * - Constructeurs
 * 		- T(int)
 * 		- T(T const&)
 * - Comparaisons
 * 		- (bool)T==T
 * 		- (bool)T!=T
 * 		- (bool)T<T
 * 		- (bool)T>T
 * 		- (bool)T<=T
 * 		- (bool)T>=T
 * - Opérations
 * 		- (T)T*T
 * 		- (T)T/T
 * 		- (T)T+T
 * 		- (T)T-T
 * 		- (T)T%T
 * - Affichage
 *		- (ostream)ostream<<T
 * 
*/
template<typename T> class Frac
{
	public:

		/** \brief Constructeur par défaut, initialise la fraction à T(0)/T(1) */
		Frac();
		/** \brief Initialise la fraction à T(x)/T(1) */
		Frac(int x);
		/** \brief Initialise la fraction à T(x)/T(1) */
		Frac(T const& x);
		/** \brief Initialise la fraction à T(p)/T(q) */
		Frac(T const& p, T const& q);

		/** \brief Retour une référence constante vers le numérateur de la fraction */
		T const& numerateur() const;
		/** \brief Retour une référence constante vers le dénominateur de la fraction */
		T const& denominateur() const;

		Frac<T>& operator+=(Frac<T> const& a);
		Frac<T>& operator-=(Frac<T> const& a);
		Frac<T>& operator*=(Frac<T> const& a);
		Frac<T>& operator/=(Frac<T> const& a);
		Frac<T> operator-();
		Frac<T> operator+();

	private:

		void simplifier();

		T m_p;
		T m_q;
};


// Constructeurs

template<typename T> Frac<T>::Frac()
{
	m_p = T(0);
	m_q = T(1);
}

template<typename T> Frac<T>::Frac(int x)
{
	m_p = T(x);
	m_q = T(1);
}

template<typename T> Frac<T>::Frac(T const& x)
{
	m_p = x;
	m_q = T(1);
}

template<typename T> Frac<T>::Frac(T const& p, T const& q)
{
	if (q == T(0))
		throw "Division par zero.";

	m_p = p;
	m_q = q;
}


// Acces et modification de la structure

template<typename T> T const& Frac<T>::numerateur() const
{
	return m_p;
}

template<typename T> T const& Frac<T>::denominateur() const
{
	return m_q;
}


// Operations

template<typename T> Frac<T>& Frac<T>::operator+=(Frac<T> const& a)
{
	m_p = m_p * a.m_q + a.m_p*m_q;
	m_q *= a.m_q;

	simplifier();

	return *this;
}

template<typename T> Frac<T> operator+(Frac<T> const& a, Frac<T> const& b)
{
	Frac<T> c(a);
	c += b;

	return c;
}

template<typename T> Frac<T>& Frac<T>::operator-=(Frac<T> const& a)
{
	m_p = m_p * a.m_q - a.m_p*m_q;
	m_q *= a.m_q;

	simplifier();

	return *this;
}

template<typename T> Frac<T> operator-(Frac<T> const& a, Frac<T> const& b)
{
	Frac<T> c(a);
	c -= b;

	return c;
}

template<typename T> Frac<T>& Frac<T>::operator*=(Frac<T> const& a)
{
	m_p *= a.m_p;
	m_q *= a.m_q;

	simplifier();

	return *this;
}

template<typename T> Frac<T> operator*(Frac<T> const& a, Frac<T> const& b)
{
	Frac<T> c(a);
	c *= b;

	return c;
}

template<typename T> Frac<T>& Frac<T>::operator/=(Frac<T> const& a)
{
	m_p *= a.m_q;
	m_q *= a.m_p;

	simplifier();

	return *this;
}

template<typename T> Frac<T> operator/(Frac<T> const& a, Frac<T> const& b)
{
	Frac<T> c(a);
	c /= b;

	return c;
}

template<typename T> Frac<T> Frac<T>::operator-()
{
	return Frac<T>(-m_p, m_q);
}

template<typename T> Frac<T> Frac<T>::operator+()
{
	return Frac<T>(m_p, m_q);
}


// Comparaisons

template<typename T> bool operator==(Frac<T> const& a, Frac<T> const& b)
{
	return a.numerateur()*b.denominateur() == b.numerateur()*a.denominateur();
}

template<typename T> bool operator!=(Frac<T> const& a, Frac<T> const& b)
{
	return a.numerateur()*b.denominateur() != b.numerateur()*a.denominateur();
}

template<typename T> bool operator>(Frac<T> const& a, Frac<T> const& b)
{
	return a.numerateur()*b.denominateur() > b.numerateur()*a.denominateur();
}

template<typename T> bool operator<(Frac<T> const& a, Frac<T> const& b)
{
	return a.numerateur()*b.denominateur() < b.numerateur()*a.denominateur();
}

template<typename T> bool operator>=(Frac<T> const& a, Frac<T> const& b)
{
	return a.numerateur()*b.denominateur() >= b.numerateur()*a.denominateur();
}

template<typename T> bool operator<=(Frac<T> const& a, Frac<T> const& b)
{
	return a.numerateur()*b.denominateur() <= b.numerateur()*a.denominateur();
}


// Fonctions specifiques

template<typename T> void Frac<T>::simplifier()
{
	if (m_q < 0)
	{
		m_q = -m_q;
		m_p = -m_p;
	}

	T x;
	if (m_p < 0)
		x = pgcd(-m_p, m_q);
	else
		x = pgcd(m_p, m_q);

	m_p /= x;
	m_q /= x;
}


// Affichage

template<typename T> std::ostream& operator<<(std::ostream& stream, Frac<T> const& a)
{
	stream << "(" << a.numerateur() << "/" << a.denominateur() << ")";
	return stream;
}


// Rationnels

/** \brief Approche la valeur de \f$\pi\f$ */
long double const PI = 3.141592653589793238;
/** \brief Approche la valeur de \f$e\f$ */
long double const E = 2.718281828459045235;

/**
 * \class Rationnel
 * \brief Classe permettant de manipuler des nombres rationnels.
*/
class Rationnel: public Frac<Int>
{
	public:

		/** \brief Constructeur par défaut, initialise le nombre rationnel à 0 */
		Rationnel();
		/** \brief Initialise le nombre rationnel à x */
		Rationnel(int x);
		/** \brief Initialise le nombre rationnel à x */
		Rationnel(Int const& x);
		/** \brief Initialise le nombre rationnel à p/q */
		Rationnel(Int const& p, Int const& q);
		/** \brief Initialise le nombre à une fraction approchée de x */
		Rationnel(double x);
		Rationnel(Frac<Int> const& x);
};

/**
 * \brief Renvoie une chaine de caractères avec les n premières décimales de x.
 * 
 * Attention, la chaine de caractère n'est pas de taille n, parce qu'elle contient également
 * une virgule et la partie entière de x.
*/
std::string decimales(Rationnel const& x, int n);
std::ostream& operator<<(std::ostream& stream, Rationnel const& x);

