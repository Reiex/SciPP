#pragma once

/**
 * \file Vect.hpp
 * \brief Ensemble des fonctions et classes permettant la manipulation de vecteurs mathématiques.
 * \author Reiex
 * 
 * Pour une description plus détaillée, voir la description de la classe Vect.
*/

#include <iostream>
#include <initializer_list>
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
 * 		- (T)T\%T
 * 		- (T)T+T
 * 		- (T)T-T
 * - Affichage
 *		- (ostream)ostream<<T
*/
template<typename T> class Vect
{
	public:

		/** \brief Erreur renvoyée lors d'une tentative d'accès à un indice invalide du vecteur. */
		class IndexException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		/** \brief Erreur renvoyée lors d'une utilisation non valide d'un vecteur à cause de sa taille. */
		class SizeException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		/** \brief Constructeur par défaut, construit un vecteur de taille nulle. */
		Vect();
		Vect(Vect<T> const& v);
		Vect(Vect<T>&& v);
		/** \brief Initialise un vecteur avec `n` occurences de `T()` */
		Vect(unsigned int n);
		/** \brief Initialise un vecteur avec une liste d'initialisation */
		Vect(std::initializer_list<T> tab);
		/** \brief Initialise un vecteur avec les éléments de `tab`. Celui-ci doit contenir `taille` valeurs. */
		Vect(T const* tab, unsigned int taille);

		Vect<T>& operator=(Vect<T> const& v);
		Vect<T>& operator=(Vect<T>&& v);

		T& operator[](unsigned int i);
		T const& operator[](unsigned int i) const;
		/** \brief Retourne la taille du vecteur */
		unsigned int size() const;
		/**
		 * \deprecated Cette méthode devra être supprimée dès que de meilleurs conteneurs seront au point.
		 * \brief Change la taille du vecteur
		 * 
		 * - Si la nouvelle taille est supérieure à la première, les valeurs actuelles sont gardées au début du vecteur
		 * et la fin du vecteur est remplie de `T()`
		 * - Si la nouvelle taille est inférieure à la première, les valeurs sont tronquées.
		*/
		void changerTaille(unsigned int taille);

		Vect<T>& operator+=(Vect<T> const& v);
		Vect<T>& operator-=(Vect<T> const& v);
		Vect<T>& operator*=(T const& x);
		Vect<T>& operator/=(T const& x);
		Vect<T>& operator%=(T const& x);
		Vect<T> operator+();
		Vect<T> operator-();

		~Vect();

	private:

		void liberer();

		T* m_x;
		unsigned int m_n;
};


// Exceptions

template<typename T> const char* Vect<T>::IndexException::what() const throw()
{
	return "Tentative d'accès à un indice invalide du vecteur.";
}

template<typename T> const char* Vect<T>::SizeException::what() const throw()
{
	return "Utilisation non valide d'un vecteur à cause de sa taille.";
}


// Constructeurs

template<typename T> Vect<T>::Vect()
{
	m_n = 0;
	m_x = nullptr;
}

template<typename T> Vect<T>::Vect(Vect<T> const& v) : Vect<T>()
{
	*this = std::move(v);
}

template<typename T> Vect<T>::Vect(Vect<T>&& v) : Vect<T>()
{
	*this = std::move(v);
}

template<typename T> Vect<T>::Vect(unsigned int n) : Vect<T>()
{
	if (n > 0)
	{
		m_n = n;
		m_x = new T[m_n];

		for (int i(0); i < m_n; i++)
			m_x[i] = T();
	}
}

template<typename T> Vect<T>::Vect(std::initializer_list<T> tab) : Vect<T>()
{
	if (tab.size() > 0)
	{
		m_n = tab.size();
		m_x = new T[m_n];
		for (int i(0); i < m_n; i++)
			m_x[i] = tab.begin()[i];
	}
}

template<typename T> Vect<T>::Vect(T const* tab, unsigned int taille) : Vect<T>()
{
	if (taille > 0)
	{
		m_n = taille;
		m_x = new T[m_n];

		for (int i(0); i < m_n; i++)
			m_x[i] = tab[i];
	}
}


// Copie et mouvement

template<typename T> Vect<T>& Vect<T>::operator=(Vect<T> const& v)
{
	liberer();
	
	m_n = v.m_n;
	m_x = new T[m_n];
	for (int i(0); i < m_n; i++)
		m_x[i] = v[i];

	return *this;
}

template<typename T> Vect<T>& Vect<T>::operator=(Vect<T>&& v)
{
	liberer();

	m_x = v.m_x;
	m_n = v.m_n;

	v.m_x = nullptr;
	v.m_n = 0;

	return *this;
}


// Acces et modification de la structure

template<typename T> T& Vect<T>::operator[](unsigned int i)
{
	if (i >= m_n)
		throw IndexException();

	return m_x[i];
}

template<typename T> T const& Vect<T>::operator[](unsigned int i) const
{
	if (i >= m_n)
		throw IndexException();

	return m_x[i];
}

template<typename T> unsigned int Vect<T>::size() const
{
	return m_n;
}

template<typename T> void Vect<T>::changerTaille(unsigned int taille)
{
	if (taille == 0)
	{
		liberer();
		return;
	}

	T* xTmp = m_x;

	m_x = new T[taille];
	for (int i(0); i < taille; i++)
		m_x[i] = i < m_n ? xTmp[i] : T();

	if (xTmp != nullptr)
		delete[] xTmp;

	m_n = taille;
}


// Opérations

template<typename T> Vect<T>& Vect<T>::operator+=(Vect<T> const& v)
{
	if (m_n != v.m_n)
		throw SizeException();

	for (int i(0); i < m_n; i++)
		m_x[i] += v[i];

	return *this;
}

template<typename T> Vect<T> Vect<T>::operator+()
{
	return *this;
}

template<typename T> Vect<T> operator+(Vect<T> const& u, Vect<T> const& v)
{
	Vect<T> w(u);
	w += v;

	return w;
}

template<typename T> Vect<T>&& operator+(Vect<T>&& u, Vect<T> const& v)
{
	u += v;
	return std::move(u);
}

template<typename T> Vect<T>&& operator+(Vect<T> const& u, Vect<T>&& v)
{
	v += u;
	return std::move(v);
}

template<typename T> Vect<T>&& operator+(Vect<T>&& u, Vect<T>&& v)
{
	u += v;
	return std::move(u);
}


template<typename T> Vect<T>& Vect<T>::operator-=(Vect<T> const& v)
{
	if (m_n != v.m_n)
		throw SizeException();

	for (int i(0); i < m_n; i++)
		m_x[i] -= v[i];

	return *this;
}

template<typename T> Vect<T> Vect<T>::operator-()
{
	Vect<T> v(*this);

	for (int i(0); i < m_n; i++)
		v.m_x[i] = -v.m_x[i];

	return v;
}

template<typename T> Vect<T> operator-(Vect<T> const& u, Vect<T> const& v)
{
	Vect<T> w(u);
	w -= v;

	return w;
}

template<typename T> Vect<T>&& operator-(Vect<T>&& u, Vect<T> const& v)
{
	u -= v;
	return std::move(u);
}

template<typename T> Vect<T>&& operator-(Vect<T>&& u, Vect<T>&& v)
{
	u -= v;
	return std::move(u);
}


template<typename T> Vect<T>& Vect<T>::operator*=(T const& x)
{
	for (int i(0); i < m_n; i++)
		m_x[i] *= x;

	return *this;
}

template<typename T> Vect<T> operator*(Vect<T> const& v, T const& x)
{
	Vect<T> w(v);
	w *= x;

	return w;
}

template<typename T> Vect<T> operator*(T const& x, Vect<T> const& v)
{
	return v*x;
}

template<typename T> Vect<T>&& operator*(Vect<T>&& v, T const& x)
{
	v *= x;
	return std::move(v);
}

template<typename T> Vect<T>&& operator*(T const& x, Vect<T>&& v)
{
	return std::move(v) * x;
}


template<typename T> Vect<T>& Vect<T>::operator/=(T const& x)
{
	for (int i(0); i < m_n; i++)
		m_x[i] /= x;

	return *this;
}

template<typename T> Vect<T> operator/(Vect<T> const& v, T const& x)
{
	Vect<T> w(v);
	w /= x;

	return w;
}

template<typename T> Vect<T>&& operator/(Vect<T>&& v, T const& x)
{
	v /= x;
	return std::move(v);
}


template<typename T> Vect<T>& Vect<T>::operator%=(T const& x)
{
	for (int i(0); i < m_n; i++)
		m_x[i] %= x;

	return *this;
}

template<typename T> Vect<T> operator%(Vect<T> const& v, T const& x)
{
	Vect<T> w(v);
	w %= x;

	return w;
}

template<typename T> Vect<T>&& operator%(Vect<T>&& v, T const& x)
{
	v %= x;
	return std::move(v);
}


template<typename T> T operator*(Vect<T> const& u, Vect<T> const& v)
{
	if (u.size() != v.size())
		throw typename Vect<T>::SizeException();

	T x(0);
	for (int i(0); i < u.size(); i++)
		x += u[i] * v[i];

	return x;
}

template<typename T> Vect<T> operator^(Vect<T> const& u, Vect<T> const& v)
{
	if (u.size() != 3 || v.size() != 3)
		throw typename Vect<T>::SizeException();

	Vect<T> w(3);

	w[0] = u[1]*v[2] - u[2]*v[1];
	w[1] = u[2]*v[0] - u[0]*v[2];
	w[2] = u[0]*v[1] - u[1]*v[0];

	return w;
}


// Comparaisons

template<typename T> bool operator==(Vect<T> const& u, Vect<T> const& v)
{
	if (u.size() != v.size())
		return false;

	for (int i(0); i < u.size(); i++)
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
	stream << "<";
	for (int i(0); i < v.size(); i++)
		if (i == v.size() - 1)
			stream << v[i];
		else
			stream << v[i] << ", ";
	stream << ">";

	return stream;
}


// Destructeur

template<typename T> void Vect<T>::liberer()
{
	if (m_x != nullptr)
		delete[] m_x;

	m_x = nullptr;
	m_n = 0;
}

template<typename T> Vect<T>::~Vect()
{
	liberer();
}
