#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "Int.hpp"

/*
	Les fonctions necessaires de Vect.

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
	T T::operator-()
	T T::operator+()
	bool operator==(T const&, T const&)
	bool operator!=(T const&, T const&)
	bool operator>(T const&, T const&)
	bool operator<(T const&, T const&)
	bool operator>=(T const&, T const&)
	bool operator<=(T const&, T const&)
*/
template<typename T> class Frac
{
	public:

		Frac();
		Frac(int x);
		Frac(T const& x);
		Frac(T const& p, T const& q);

		T numerateur() const;
		T denominateur() const;

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

template<typename T> T Frac<T>::numerateur() const
{
	return m_p;
}

template<typename T> T Frac<T>::denominateur() const
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

typedef Frac<Int> Rationnel;

long double const PI = 3.141592653589793;
long double const E = 2.7182818284590452;

std::string decimales(Rationnel const& x, int n);
std::ostream& operator<<(std::ostream& stream, Rationnel const& x);
