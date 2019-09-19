#pragma once

#include <iostream>
#include "SciPP.h"

/*
	Les fonctions nécessaires de Vecteur.

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
template<typename T> class Fraction
{
	public:

		Fraction();
		Fraction(int x);
		Fraction(T const& x);
		Fraction(T const& p, T const& q);

		T numerateur() const;
		T denominateur() const;

		Fraction<T>& operator+=(Fraction<T> const& a);
		Fraction<T>& operator-=(Fraction<T> const& a);
		Fraction<T>& operator*=(Fraction<T> const& a);
		Fraction<T>& operator/=(Fraction<T> const& a);
		Fraction<T> operator-();
		Fraction<T> operator+();

	private:

		void simplifier();

		T m_p;
		T m_q;
};


// Constructeurs

template<typename T> Fraction<T>::Fraction()
{
	m_p = T(0);
	m_q = T(1);
}

template<typename T> Fraction<T>::Fraction(int x)
{
	m_p = T(x);
	m_q = T(1);
}

template<typename T> Fraction<T>::Fraction(T const& x)
{
	m_p = x;
	m_q = T(1);
}

template<typename T> Fraction<T>::Fraction(T const& p, T const& q)
{
	if (q == T(0))
		throw "Division par zero.";

	m_p = p;
	m_q = q;
}


// Acces et modification de la structure

template<typename T> T Fraction<T>::numerateur() const
{
	return m_p;
}

template<typename T> T Fraction<T>::denominateur() const
{
	return m_q;
}


// Opérations

template<typename T> Fraction<T>& Fraction<T>::operator+=(Fraction<T> const& a)
{
	m_p = m_p * a.m_q + a.m_p*m_q;
	m_q *= a.m_q;

	simplifier();

	return *this;
}

template<typename T> Fraction<T> operator+(Fraction<T> const& a, Fraction<T> const& b)
{
	Fraction<T> c(a);
	c += b;

	return c;
}

template<typename T> Fraction<T>& Fraction<T>::operator-=(Fraction<T> const& a)
{
	m_p = m_p * a.m_q - a.m_p*m_q;
	m_q *= a.m_q;

	simplifier();

	return *this;
}

template<typename T> Fraction<T> operator-(Fraction<T> const& a, Fraction<T> const& b)
{
	Fraction<T> c(a);
	c -= b;

	return c;
}

template<typename T> Fraction<T>& Fraction<T>::operator*=(Fraction<T> const& a)
{
	m_p *= a.m_p;
	m_q *= a.m_q;

	simplifier();

	return *this;
}

template<typename T> Fraction<T> operator*(Fraction<T> const& a, Fraction<T> const& b)
{
	Fraction<T> c(a);
	c *= b;

	return c;
}

template<typename T> Fraction<T>& Fraction<T>::operator/=(Fraction<T> const& a)
{
	m_p *= a.m_q;
	m_q *= a.m_p;

	simplifier();

	return *this;
}

template<typename T> Fraction<T> operator/(Fraction<T> const& a, Fraction<T> const& b)
{
	Fraction<T> c(a);
	c /= b;

	return c;
}

template<typename T> Fraction<T> Fraction<T>::operator-()
{
	return Fraction<T>(-m_p, m_q);
}

template<typename T> Fraction<T> Fraction<T>::operator+()
{
	return Fraction<T>(m_p, m_q);
}


// Comparaisons

template<typename T> bool operator==(Fraction<T> const& a, Fraction<T> const& b)
{
	return a.numerateur()*b.denominateur() == b.numerateur()*a.denominateur();
}

template<typename T> bool operator!=(Fraction<T> const& a, Fraction<T> const& b)
{
	return a.numerateur()*b.denominateur() != b.numerateur()*a.denominateur();
}

template<typename T> bool operator>(Fraction<T> const& a, Fraction<T> const& b)
{
	return a.numerateur()*b.denominateur() > b.numerateur()*a.denominateur();
}

template<typename T> bool operator<(Fraction<T> const& a, Fraction<T> const& b)
{
	return a.numerateur()*b.denominateur() < b.numerateur()*a.denominateur();
}

template<typename T> bool operator>=(Fraction<T> const& a, Fraction<T> const& b)
{
	return a.numerateur()*b.denominateur() >= b.numerateur()*a.denominateur();
}

template<typename T> bool operator<=(Fraction<T> const& a, Fraction<T> const& b)
{
	return a.numerateur()*b.denominateur() <= b.numerateur()*a.denominateur();
}


// Fonctions spécifiques

template<typename T> void Fraction<T>::simplifier()
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

template<typename T> std::ostream& operator<<(std::ostream& stream, Fraction<T> const& a)
{
	stream << "(" << a.numerateur() << "/" << a.denominateur() << ")";
	return stream;
}
