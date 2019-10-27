#pragma once

#include <iostream>
#include "Fraction.hpp"

/*
	T::T()
	T::T(int)
	T::operator=(T const&)
	ostream& operator<<(ostream&, T const&)
	T& T::operator+=(T const&)
	T operator+(T const&, T const&)
	T& T::operator-=(T const&)
	T operator-(T const&, T const&)
	T& T::operator*=(T const&)
	T operator*(T const&, T const&)
	T& T::operator/=(T const&)
	T operator/(T const&, T const&)
	bool operator==(T const&, T const&)
	bool operator!=(T const&, T const&)
*/
template<typename T> class Vecteur
{
	public:

		Vecteur();
		Vecteur(Vecteur<T> const& v);
		Vecteur(Vecteur<T>&& v);
		Vecteur(int n);
		Vecteur(T const* tab, int taille);

		Vecteur<T>& operator=(Vecteur<T> const& v);
		Vecteur<T>& operator=(Vecteur<T>&& v);

		T& operator[](int i);
		T const& operator[](int i) const;
		int taille() const;
		void changerTaille(int taille);

		Vecteur<T>& operator+=(Vecteur<T> const& v);
		Vecteur<T>& operator-=(Vecteur<T> const& v);
		Vecteur<T>& operator*=(T x);
		Vecteur<T>& operator/=(T x);

		~Vecteur();

	private:

		void liberer();
		void copier(Vecteur<T> const& v);

		T* m_x;
		int m_n;

		bool m_actif;
};


// Constructeurs

template<typename T> Vecteur<T>::Vecteur()
{
	m_n = 0;
	m_x = nullptr;

	m_actif = false;
}

template<typename T> Vecteur<T>::Vecteur(Vecteur<T> const& v)
{
	copier(v);

	m_actif = v.m_actif;
}

template<typename T> Vecteur<T>::Vecteur(Vecteur<T>&& v)
{
	m_x = v.m_x;
	m_n = v.m_n;

	m_actif = v.m_actif;
	v.m_actif = false;
}

template<typename T> Vecteur<T>::Vecteur(int n)
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

template<typename T> Vecteur<T>::Vecteur(T const* tab, int taille)
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

template<typename T> void Vecteur<T>::copier(Vecteur<T> const& v)
{
	m_n = v.m_n;
	m_x = new T[m_n];
	for (int i(0); i < m_n; i++)
		m_x[i] = v[i];
}

template<typename T> Vecteur<T>& Vecteur<T>::operator=(Vecteur<T> const& v)
{
	liberer();
	copier(v);

	m_actif = v.m_actif;

	return *this;
}

template<typename T> Vecteur<T>& Vecteur<T>::operator=(Vecteur<T>&& v)
{
	liberer();

	m_x = v.m_x;
	m_n = v.m_n;

	m_actif = v.m_actif;
	v.m_actif = false;

	return *this;
}


// Acces et modification de la structure

template<typename T> T& Vecteur<T>::operator[](int i)
{

	if (i < 0 || i >= m_n)
		throw "L'indice est en dehors des limites.";

	return m_x[i];
}

template<typename T> T const& Vecteur<T>::operator[](int i) const
{
	if (i < 0 || i >= m_n)
		throw "L'indice est en dehors des limites.";

	return m_x[i];
}

template<typename T> int Vecteur<T>::taille() const
{
	return m_n;
}

template<typename T> void Vecteur<T>::changerTaille(int taille)
{
	T* xTmp = m_x;

	m_x = new T[taille];
	for (int i(0); i < taille; i++)
		m_x[i] = i < m_n ? xTmp[i] : T();

	m_n = taille;

	delete[] xTmp;
}


// Op�rations

template<typename T> Vecteur<T>& Vecteur<T>::operator+=(Vecteur<T> const& v)
{
	if (m_n != v.m_n)
		throw "Les deux vecteurs doivent avoir la meme taille.";

	for (int i(0); i < m_n; i++)
		m_x[i] += v[i];

	return *this;
}

template<typename T> Vecteur<T> operator+(Vecteur<T> const& u, Vecteur<T> const& v)
{
	Vecteur<T> w(u);
	w += v;

	return w;
}

template<typename T> Vecteur<T>& Vecteur<T>::operator-=(Vecteur<T> const& v)
{
	if (m_n != v.m_n)
		throw "Les deux vecteurs doivent avoir la meme taille.";

	for (int i(0); i < m_n; i++)
		m_x[i] -= v[i];

	return *this;
}

template<typename T> Vecteur<T> operator-(Vecteur<T> const& u, Vecteur<T> const& v)
{
	Vecteur<T> w(u);
	w -= v;

	return w;
}

template<typename T> Vecteur<T>& Vecteur<T>::operator*=(T x)
{
	for (int i(0); i < m_n; i++)
		m_x[i] *= x;

	return *this;
}

template<typename T> Vecteur<T> operator*(Vecteur<T> const& v, T x)
{
	Vecteur<T> w(v);
	w *= x;

	return w;
}

template<typename T> Vecteur<T> operator*(T x, Vecteur<T> const& v)
{
	return v*x;
}

template<typename T> Vecteur<T>& Vecteur<T>::operator/=(T x)
{
	for (int i(0); i < m_n; i++)
		m_x[i] /= x;

	return *this;
}

template<typename T> Vecteur<T> operator/(Vecteur<T> const& v, T x)
{
	Vecteur<T> w(v);
	w /= x;

	return w;
}

template<typename T> T operator*(Vecteur<T> const& u, Vecteur<T> const& v)
{
	if (u.taille() != v.taille())
		throw "Les deux vecteurs doivent avoir la meme taille.";

	T x(0);
	for (int i(0); i < u.taille(); i++)
		x += u[i] * v[i];

	return x;
}

template<typename T> Vecteur<T> operator^(Vecteur<T> const& u, Vecteur<T> const& v)
{
	if (u.taille != 3 || v.taille != 3)
		throw "Les vecteurs doivent etre en dimension 3.";

	Vecteur<T> w(3);

	w[0] = u[1]*v[2] - u[2]*v[1];
	w[1] = u[2]*v[0] - u[0]*v[2];
	w[2] = u[0]*v[1] - u[1]*v[0];

	return w;
}


// Comparaisons

template<typename T> bool operator==(Vecteur<T> const& u, Vecteur<T> const& v)
{
	if (u.taille() != v.taille())
		return false;

	for (int i(0); i < u.taille(); i++)
		if (u[i] != v[i])
			return false;

	return true;
}

template<typename T> bool operator!=(Vecteur<T> const& u, Vecteur<T> const& v)
{
	return !(u == v);
}


// Affichage

template<typename T> std::ostream& operator<<(std::ostream& stream, Vecteur<T> const& v)
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

template<typename T> void Vecteur<T>::liberer()
{
	delete[] m_x;
}

template<typename T> Vecteur<T>::~Vecteur()
{
	if (m_actif)
		liberer();
}
