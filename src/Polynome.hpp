#pragma once

#include <iostream>
#include "Vecteur.hpp"

/*
	Les fonctions necessaires de Vecteur.

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
	T T::operator-()
	T T::operator+()
	bool operator==(T const&, T const&)
	bool operator!=(T const&, T const&)
*/
template<typename T> class Polynome
{
	public:

		Polynome();
		Polynome(int x);
		Polynome(T const& x);
		Polynome(T const* tab, int taille);

		T& operator[](int i);
		T const& operator[](int i) const;
		int degre() const;

		Polynome<T>& operator+=(Polynome<T> const& P);
		Polynome<T>& operator-=(Polynome<T> const& P);
		Polynome<T>& operator*=(Polynome<T> const& P);
		Polynome<T>& operator/=(Polynome<T> const& P);
		Polynome<T>& operator%=(Polynome<T> const& P);
		Polynome<T> operator-();
		Polynome<T> operator+();

		T operator()(T const& x) const;

	private:

		Vecteur<T> m_coeffs;
		int m_deg;
};


// Constructeurs

template<typename T> Polynome<T>::Polynome()
{
	m_coeffs = Vecteur<T>(1);
	m_deg = 0;
}

template<typename T> Polynome<T>::Polynome(int x)
{
	m_coeffs = Vecteur<T>(1);
	m_coeffs[0] = T(x);
	m_deg = 0;
}

template<typename T> Polynome<T>::Polynome(T const& x)
{
	m_coeffs = Vecteur<T>(1);
	m_coeffs[0] = x;
	m_deg = 0;
}

template<typename T> Polynome<T>::Polynome(T const* tab, int taille)
{
	m_deg = 0;
	T zero(0);
	for (int i(0); i < taille; i++)
		if (tab[i] != zero)
			m_deg = i;

	m_coeffs = Vecteur<T>(m_deg + 1);
	for (int i(0); i < m_deg + 1; i++)
		m_coeffs[i] = tab[i];
}


// Acces et modification de la structure

template<typename T> T& Polynome<T>::operator[](int i)
{
	if (i < 0 || i >= m_deg + 1)
		throw "L'indice est en dehors des limites.";

	return m_coeffs[i];
}

template<typename T> T const& Polynome<T>::operator[](int i) const
{
	if (i < 0 || i >= m_deg + 1)
		throw "L'indice est en dehors des limites.";

	return m_coeffs[i];
}

template<typename T> int Polynome<T>::degre() const
{
	return m_deg;
}


// Opérations

template<typename T> Polynome<T>& Polynome<T>::operator+=(Polynome<T> const& P)
{
	if (P.m_deg < m_deg)
	{
		for (int i(0); i < P.m_deg + 1; i++)
			m_coeffs[i] += P[i];
	}
	else if (P.m_deg == m_deg)
	{
		T zero(0);
		int deg(m_deg);
		while (P[deg] + m_coeffs[deg] == zero && deg > 0)
			deg--;

		m_coeffs.changerTaille(deg + 1);
		m_deg = deg;

		for (int i(0); i < m_deg + 1; i++)
			m_coeffs[i] += P[i];
	}
	else
	{
		m_coeffs.changerTaille(P.m_deg + 1);
		m_deg = P.m_deg;

		for (int i(0); i < m_deg + 1; i++)
			m_coeffs[i] += P[i];
	}

	return *this;
}

template<typename T> Polynome<T> operator+(Polynome<T> const& P, Polynome<T> const& Q)
{
	Polynome<T> R(P);
	R += Q;

	return R;
}

template<typename T> Polynome<T>& Polynome<T>::operator-=(Polynome<T> const& P)
{
	if (P.m_deg < m_deg)
	{
		for (int i(0); i < P.m_deg + 1; i++)
			m_coeffs[i] -= P[i];
	}
	else if (P.m_deg == m_deg)
	{
		T zero(0);
		int deg(m_deg);
		while (m_coeffs[deg] - P[deg] == zero && deg > 0)
			deg--;

		m_coeffs.changerTaille(deg + 1);
		m_deg = deg;

		for (int i(0); i < m_deg + 1; i++)
			m_coeffs[i] -= P[i];
	}
	else
	{
		m_coeffs.changerTaille(P.m_deg + 1);
		m_deg = P.m_deg;

		for (int i(0); i < m_deg + 1; i++)
			m_coeffs[i] -= P[i];
	}

	return *this;
}

template<typename T> Polynome<T> operator-(Polynome<T> const& P, Polynome<T> const& Q)
{
	Polynome<T> R(P);
	R -= Q;

	return R;
}

template<typename T> Polynome<T>& Polynome<T>::operator*=(Polynome<T> const& P)
{
	T zero(0);
	if (P.m_deg == 0 && P[0] == zero || m_deg == 0 && m_coeffs[0] == zero)
	{
		m_coeffs = Vecteur<T>(1);
		m_deg = 0;
	}
	else
	{
		Vecteur<T> prod(m_deg + P.m_deg + 1);
		m_coeffs.changerTaille(m_deg + P.m_deg + 1);

		for (int k(0); k < m_deg + P.m_deg + 1; k++)
		{
			for (int i(0); i < k + 1 && i < P.m_deg + 1; i++)
				prod[k] += m_coeffs[k - i] * P[i];
		}

		m_coeffs = prod;
		m_deg = m_deg + P.m_deg;
	}

	return *this;
}

template<typename T> Polynome<T> operator*(Polynome<T> const& P, Polynome<T> const& Q)
{
	Polynome<T> R(P);
	R *= Q;

	return R;
}

template<typename T> Polynome<T> operator*(Polynome<T> const& P, T const& x)
{
	return P * Polynome<T>(x);
}

template<typename T> Polynome<T> operator*(T const& x, Polynome<T> const& P)
{
	return Polynome<T>(x) * P;
}

template<typename T> Polynome<T>& Polynome<T>::operator/=(Polynome<T> const& P)
{
	if (P.m_deg > m_deg)
	{
		m_coeffs = Vecteur<T>(1);
		m_deg = 0;
	}
	else
	{
		Vecteur<T> coeffs(m_deg - P.m_deg + 1);
		m_deg -= P.m_deg;
		int k(P.m_deg);
		T a(P[P.m_deg]);

		for (int i(m_deg); i >= 0; i--)
		{
			coeffs[i] = m_coeffs[i + k] / a;

			for (int j(0); j < k + 1; j++)
				m_coeffs[i + j] -= coeffs[i] * P[j];
		}

		m_coeffs = coeffs;
	}

	return *this;
}

template<typename T> Polynome<T> operator/(Polynome<T> const& P, Polynome<T> const& Q)
{
	Polynome<T> R(P);
	R /= Q;

	return R;
}

template<typename T> Polynome<T>& Polynome<T>::operator%=(Polynome<T> const& P)
{
	if (P.m_deg <= m_deg)
	{
		int k(P.m_deg);
		T a(P[P.m_deg]), c(0);

		for (int i(m_deg - P.m_deg); i >= 0; i--)
		{
			c = m_coeffs[i + k] / a;

			for (int j(0); j < k + 1; j++)
				m_coeffs[i + j] -= c * P[j];
		}

		m_deg = 0;
		T zero(0);
		for (int i(0); i < m_coeffs.taille(); i++)
			if (m_coeffs[i] != zero)
				m_deg = i;

		m_coeffs.changerTaille(m_deg + 1);
	}

	return *this;
}

template<typename T> Polynome<T> operator%(Polynome<T> const& P, Polynome<T> const& Q)
{
	Polynome<T> R(P);
	R %= Q;

	return R;
}

template<typename T> Polynome<T> Polynome<T>::operator-()
{
	Polynome<T> P;
	P.m_deg = m_deg;
	P.m_coeffs = Vecteur<T>(m_deg + 1);

	for (int i(0); i < m_deg + 1; i++)
		P.m_coeffs[i] = -m_coeffs[i];

	return P;
}

template<typename T> Polynome<T> Polynome<T>::operator+()
{
	return Polynome<T>(*this);
}


// Comparaisons

template<typename T> bool operator==(Polynome<T> const& P, Polynome<T> const& Q)
{
	if (P.degre() != Q.degre())
		return false;

	for (int i(0); i < P.degre() + 1; i++)
		if (P[i] != Q[i])
			return false;

	return true;
}

template<typename T> bool operator!=(Polynome<T> const& P, Polynome<T> const& Q)
{
	return !(P == Q);
}


// Fonctions sp�cifiques

template<typename T> T Polynome<T>::operator()(T const& x) const
{
	T y(0);

	for (int i(m_deg); i >= 0; i--)
		y = x * y + m_coeffs[i];

	return y;
}


// Affichage

template<typename T> std::ostream& operator<<(std::ostream& stream, Polynome<T> const& P)
{
	stream << "Polynome(";
	for (int i(0); i < P.degre() + 1; i++)
		if (i == P.degre())
			stream << P[i];
		else
			stream << P[i] << " ";
	stream << ")";

	return stream;
}
