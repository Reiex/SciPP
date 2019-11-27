#pragma once

/**
 * \file Vect.hpp
 * \author Reiex
 * \brief Ensemble des fonctions et classes permettant la manipulation de vecteurs mathématiques.
 * 
 * Pour une description plus détaillée, voir la description de la classe Vect.
*/

#include <iostream>
#include "Frac.hpp"


/**
 * \class Vect
 * \brief Classe permettant de manipuler des vecteurs mathématiques.
 * 
 * La classe Vect est template et prend en argument template une classe T.
 * L'espace dans lequel se place le vecteur est l'espace de cette classe T.
 * 
 * Voici les fonctions qui doivent être définies par la classe T:
 * - Constructeurs
 * 		- T()
 * 		- T(int)
 * 		- T(T const&)
 * - Comparaisons
 * 		- (bool)T==T
 * 		- (bool)T!=T
 * - Opérations
 * 		- (T)T*T
 * 		- (T)T/T
 * 		- (T)T+T
 * 		- (T)T-T
 * - Affichage
 *		- (ostream)ostream<<T
*/
template<typename T> class Vect
{
	public:

		/** \brief Constructeur par défaut, la taille du vecteur vaut 0. */
		Vect();
		Vect(Vect<T> const& v);
		Vect(Vect<T>&& v);
		/** \brief Initialise un vecteur avec `n` occurences de `T()` */
		Vect(int n);
		/** \brief Initialise un vecteur avec les éléments de `tab`. Celui-ci doit contenir `taille` valeurs. */
		Vect(T const* tab, int taille);

		Vect<T>& operator=(Vect<T> const& v);
		Vect<T>& operator=(Vect<T>&& v);

		T& operator[](int i);
		T const& operator[](int i) const;
		/** \brief Retourne la taille du vecteur */
		int taille() const;
		/**
		 * \brief Change la taille du vecteur
		 * 
		 * - Si la nouvelle taille est supérieure à la première, les valeurs actuelles sont gardées au début du vecteur
		 * et la fin du vecteur est remplie de `T()`
		 * - Si la nouvelle taille est inférieure à la première, les valeurs sont tronquées.
		*/
		void changerTaille(int taille);

		Vect<T>& operator+=(Vect<T> const& v);
		Vect<T>& operator-=(Vect<T> const& v);
		Vect<T>& operator*=(T x);
		Vect<T>& operator/=(T x);

		~Vect();

	private:

		void liberer();
		void copier(Vect<T> const& v);

		T* m_x;
		int m_n;

		bool m_actif;
};


// Constructeurs

template<typename T> Vect<T>::Vect()
{
	m_n = 0;
	m_x = nullptr;

	m_actif = false;
}

template<typename T> Vect<T>::Vect(Vect<T> const& v)
{
	copier(v);

	m_actif = v.m_actif;
}

template<typename T> Vect<T>::Vect(Vect<T>&& v)
{
	m_x = v.m_x;
	m_n = v.m_n;

	m_actif = v.m_actif;
	v.m_actif = false;
}

template<typename T> Vect<T>::Vect(int n)
{
	if (n > 0)
	{
		m_n = n;
		m_x = new T[m_n];

		for (int i(0); i < m_n; i++)
			m_x[i] = T();

		m_actif = true;
	}
	else
	{
		m_n = 0;
		m_x = nullptr;

		m_actif = false;
	}
}

template<typename T> Vect<T>::Vect(T const* tab, int taille)
{
	if (taille > 0)
	{
		m_n = taille;
		m_x = new T[m_n];

		for (int i(0); i < m_n; i++)
			m_x[i] = tab[i];

		m_actif = true;
	}
	else
	{
		m_n = 0;
		m_x = nullptr;

		m_actif = false;
	}
}


// Copie et mouvement

template<typename T> void Vect<T>::copier(Vect<T> const& v)
{
	m_n = v.m_n;
	m_x = new T[m_n];
	for (int i(0); i < m_n; i++)
		m_x[i] = v[i];
}

template<typename T> Vect<T>& Vect<T>::operator=(Vect<T> const& v)
{
	liberer();
	copier(v);

	m_actif = v.m_actif;

	return *this;
}

template<typename T> Vect<T>& Vect<T>::operator=(Vect<T>&& v)
{
	liberer();

	m_x = v.m_x;
	m_n = v.m_n;

	m_actif = v.m_actif;
	v.m_actif = false;

	return *this;
}


// Acces et modification de la structure

template<typename T> T& Vect<T>::operator[](int i)
{

	if (i < 0 || i >= m_n)
		throw "L'indice est en dehors des limites.";

	return m_x[i];
}

template<typename T> T const& Vect<T>::operator[](int i) const
{
	if (i < 0 || i >= m_n)
		throw "L'indice est en dehors des limites.";

	return m_x[i];
}

template<typename T> int Vect<T>::taille() const
{
	return m_n;
}

template<typename T> void Vect<T>::changerTaille(int taille)
{
	T* xTmp = m_x;

	m_x = new T[taille];
	for (int i(0); i < taille; i++)
		m_x[i] = i < m_n ? xTmp[i] : T();

	m_n = taille;

	delete[] xTmp;
}


// Opérations

template<typename T> Vect<T>& Vect<T>::operator+=(Vect<T> const& v)
{
	if (m_n != v.m_n)
		throw "Les deux Vects doivent avoir la meme taille.";

	for (int i(0); i < m_n; i++)
		m_x[i] += v[i];

	return *this;
}

template<typename T> Vect<T> operator+(Vect<T> const& u, Vect<T> const& v)
{
	Vect<T> w(u);
	w += v;

	return w;
}

template<typename T> Vect<T>& Vect<T>::operator-=(Vect<T> const& v)
{
	if (m_n != v.m_n)
		throw "Les deux Vects doivent avoir la meme taille.";

	for (int i(0); i < m_n; i++)
		m_x[i] -= v[i];

	return *this;
}

template<typename T> Vect<T> operator-(Vect<T> const& u, Vect<T> const& v)
{
	Vect<T> w(u);
	w -= v;

	return w;
}

template<typename T> Vect<T>& Vect<T>::operator*=(T x)
{
	for (int i(0); i < m_n; i++)
		m_x[i] *= x;

	return *this;
}

template<typename T> Vect<T> operator*(Vect<T> const& v, T x)
{
	Vect<T> w(v);
	w *= x;

	return w;
}

template<typename T> Vect<T> operator*(T x, Vect<T> const& v)
{
	return v*x;
}

template<typename T> Vect<T>& Vect<T>::operator/=(T x)
{
	for (int i(0); i < m_n; i++)
		m_x[i] /= x;

	return *this;
}

template<typename T> Vect<T> operator/(Vect<T> const& v, T x)
{
	Vect<T> w(v);
	w /= x;

	return w;
}

template<typename T> T operator*(Vect<T> const& u, Vect<T> const& v)
{
	if (u.taille() != v.taille())
		throw "Les deux Vects doivent avoir la meme taille.";

	T x(0);
	for (int i(0); i < u.taille(); i++)
		x += u[i] * v[i];

	return x;
}

template<typename T> Vect<T> operator^(Vect<T> const& u, Vect<T> const& v)
{
	if (u.taille != 3 || v.taille != 3)
		throw "Les Vects doivent etre en dimension 3.";

	Vect<T> w(3);

	w[0] = u[1]*v[2] - u[2]*v[1];
	w[1] = u[2]*v[0] - u[0]*v[2];
	w[2] = u[0]*v[1] - u[1]*v[0];

	return w;
}


// Comparaisons

template<typename T> bool operator==(Vect<T> const& u, Vect<T> const& v)
{
	if (u.taille() != v.taille())
		return false;

	for (int i(0); i < u.taille(); i++)
		if (u[i] != v[i])
			return false;

	return true;
}

template<typename T> bool operator!=(Vect<T> const& u, Vect<T> const& v)
{
	return !(u == v);
}


// Affichage

template<typename T> std::ostream& operator<<(std::ostream& stream, Vect<T> const& v)
{
	stream << "(";
	for (int i(0); i < v.taille(); i++)
		if (i == v.taille() - 1)
			stream << v[i];
		else
			stream << v[i] << " ";
	stream << ")";

	return stream;
}


// Destructeur

template<typename T> void Vect<T>::liberer()
{
	delete[] m_x;
}

template<typename T> Vect<T>::~Vect()
{
	if (m_actif)
		liberer();
}
