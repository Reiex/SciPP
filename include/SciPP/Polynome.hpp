#pragma once

/**
 * \file Polynome.hpp
 * \brief Ensemble des fonctions et classes permettant la manipulation de polynomes.
 * \author Reiex
 *
 * Pour une description plus détaillée, voir la description de la classe Polynome.
*/

#include <iostream>
#include <initializer_list>
#include "Vect.hpp"

namespace scp
{
	/**
	 * \class Polynome
	 * \brief Classe permettant de manipuler des polynome.
	 *
	 * La classe Polynomr est template et prend en argument template une classe T.
	 * L'espace des coefficients du polynome est l'espace de cette classe T.
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
	 * 		- (T)T%T
	 * - Affichage
	 *		- (ostream)ostream<<T
	*/
	template<typename T> class Polynome
	{
	public:

		/** \brief Constructeur par défaut, initialise le polynome à T(0). */
		Polynome();
		/** \brief Initialise le polynome à la constante T(x). */
		Polynome(int x);
		/** \brief Initialise le polynome à la constante x. */
		Polynome(T const& x);
		/** \brief Initialise le polynome à partir d'une liste d'initialisation avec `tab[i]` le coefficient devant \f$x^i\f$. */
		Polynome(std::initializer_list<T> tab);
		/** \brief Initialise le polynome à partir de `tab` avec `tab[i]` le coefficient devant \f$x^i\f$. */
		Polynome(T const* tab, int taille);

		T& operator[](int i);
		T const& operator[](int i) const;
		/** \brief Retourne le degré du polynome, le degré vaut 0 si le polynome est nul */
		int degre() const;

		Polynome<T>& operator+=(Polynome<T> const& P);
		Polynome<T>& operator-=(Polynome<T> const& P);
		Polynome<T>& operator*=(Polynome<T> const& P);
		Polynome<T>& operator/=(Polynome<T> const& P);
		Polynome<T>& operator%=(Polynome<T> const& P);
		Polynome<T> operator-();
		Polynome<T> operator+();

		/** \brief Calcul le polynome appliqué à la valeur x.*/
		T operator()(T const& x) const;
		/** \brief Retourne la dérivée du polynome. */
		Polynome<T> derivee() const;

	private:

		Vect<T> m_coeffs;
		int m_deg;
	};


	// Constructeurs

	template<typename T> Polynome<T>::Polynome()
	{
		m_coeffs = Vect<T>(1);
		m_deg = 0;
	}

	template<typename T> Polynome<T>::Polynome(int x)
	{
		m_coeffs = Vect<T>(1);
		m_coeffs[0] = T(x);
		m_deg = 0;
	}

	template<typename T> Polynome<T>::Polynome(T const& x)
	{
		m_coeffs = Vect<T>(1);
		m_coeffs[0] = x;
		m_deg = 0;
	}

	template<typename T> Polynome<T>::Polynome(std::initializer_list<T> tab)
	{
		m_deg = 0;
		T zero(0);
		for (int i(0); i < tab.size(); i++)
			if (tab.begin()[i] != zero)
				m_deg = i;

		m_coeffs = Vect<T>(m_deg + 1);
		if (tab.size() != 0)
			for (int i(0); i < m_deg + 1; i++)
				m_coeffs[i] = tab.begin()[i];
	}

	template<typename T> Polynome<T>::Polynome(T const* tab, int taille)
	{
		m_deg = 0;
		T zero(0);
		for (int i(0); i < taille; i++)
			if (tab[i] != zero)
				m_deg = i;

		m_coeffs = Vect<T>(m_deg + 1);
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
			m_coeffs = Vect<T>(1);
			m_deg = 0;
		}
		else
		{
			Vect<T> prod(m_deg + P.m_deg + 1);
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
			m_coeffs = Vect<T>(1);
			m_deg = 0;
		}
		else
		{
			Vect<T> coeffs(m_deg - P.m_deg + 1);
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
			for (int i(0); i < m_coeffs.size(); i++)
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
		P.m_coeffs = Vect<T>(m_deg + 1);

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


	// Fonctions spécifiques

	template<typename T> T Polynome<T>::operator()(T const& x) const
	{
		T y(0);

		for (int i(m_deg); i >= 0; i--)
			y = x * y + m_coeffs[i];

		return y;
	}

	template<typename T> Polynome<T> Polynome<T>::derivee() const
	{
		Polynome<T> P(*this);

		if (P.m_deg == 0)
		{
			P[0] = 0;
		}
		else
		{
			for (int i(0); i < P.m_coeffs.size() - 1; i++)
				P[i] = P[i + 1];
			P.m_coeffs.changerTaille(P.m_coeffs.size() - 1);
			P.m_deg--;
		}

		return P;
	}


	// Affichage

	template<typename T> std::ostream& operator<<(std::ostream& stream, Polynome<T> const& P)
	{
		stream << "Polynome(";
		for (int i(0); i < P.degre() + 1; i++)
			if (i == P.degre())
				stream << P[i];
			else
				stream << P[i] << ", ";
		stream << ")";

		return stream;
	}
}
