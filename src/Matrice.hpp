#pragma once

#include <iostream>
#include <complex>
#include "Vect.hpp"

/*
	Les fonctions necessaires de Vect.

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
template<typename T> class Matrice
{
	public:

		Matrice();
		Matrice(int m, int n);
		Matrice(Matrice<T> const& M);
		Matrice(Matrice<T>&& M);
		Matrice(T const* tab, int m, int n);

		Matrice<T>& operator=(Matrice<T> const& M);
		Matrice<T>& operator=(Matrice<T>&& M);

		Vect<T>& operator[](int i);
		Vect<T> const& operator[](int i) const;
		Vect<int> const& taille() const;
		void changerTaille(int m, int n);

		Matrice<T>& operator+=(Matrice<T> const& M);
		Matrice<T>& operator-=(Matrice<T> const& M);
		Matrice<T>& operator*=(Matrice<T> const& M);
		Matrice<T>& operator*=(T const& x);
		Matrice<T>& operator/=(T const& x);

		T det() const;
		Matrice<T> inv() const;
		Matrice<T> transpose() const;

		~Matrice();

	private:

		void liberer();
		void copier(Matrice<T> const& M);

		Vect<T>* m_lignes;
		Vect<int> m_taille;

		bool m_actif;
};


// Constructeurs

template<typename T> Matrice<T>::Matrice()
{
	m_lignes = nullptr;
	m_taille = Vect<int>(2);
	m_taille[0] = 0;
	m_taille[1] = 0;

	m_actif = false;
}

template<typename T> Matrice<T>::Matrice(int m, int n)
{
	if (m > 0 && n > 0)
	{
		m_taille = Vect<int>(2);
		m_taille[0] = m;
		m_taille[1] = n;

		m_lignes = new Vect<T>[m];
		for (int i(0); i < m; i++)
			m_lignes[i] = Vect<T>(n);

		m_actif = true;
	}
	else
	{
		m_lignes = nullptr;
		m_taille = Vect<int>(2);
		m_taille[0] = 0;
		m_taille[1] = 0;

		m_actif = false;
	}
}

template<typename T> Matrice<T>::Matrice(Matrice<T> const& M)
{
	copier(M);

	m_actif = M.m_actif;
}

template<typename T> Matrice<T>::Matrice(Matrice<T>&& M)
{
	m_taille = M.m_taille;
	m_lignes = M.m_lignes;

	m_actif = M.m_actif;
	M.m_actif = false;
}

template<typename T> Matrice<T>::Matrice(T const* tab, int m, int n)
{
	if (m > 0 && n > 0)
	{
		m_taille = Vect<int>(2);
		m_taille[0] = m;
		m_taille[1] = n;

		m_lignes = new Vect<T>[m];
		for (int i(0); i < m; i++)
		{
			m_lignes[i] = Vect<T>(n);
			for (int j(0); j < n; j++)
				m_lignes[i][j] = tab[i*n + j];
		}

		m_actif = true;
	}
	else
	{
		m_lignes = nullptr;
		m_taille = Vect<int>(2);
		m_taille[0] = 0;
		m_taille[1] = 0;

		m_actif = false;
	}
}


// Copie et mouvement

template<typename T> void Matrice<T>::copier(Matrice<T> const& M)
{
	m_taille = M.m_taille;
	m_lignes = new Vect<T>[m_taille[0]];
	for (int i(0); i < m_taille[0]; i++)
		m_lignes[i] = M.m_lignes[i];
}

template<typename T> Matrice<T>& Matrice<T>::operator=(Matrice<T> const& M)
{
	liberer();
	copier(M);

	m_actif = M.m_actif;

	return *this;
}

template<typename T> Matrice<T>& Matrice<T>::operator=(Matrice<T>&& M)
{
	liberer();

	m_taille = M.m_taille;
	m_lignes = M.m_lignes;

	m_actif = M.m_actif;
	M.m_actif = false;

	return *this;
}


// Acces et modification de la structure

template<typename T> Vect<T>& Matrice<T>::operator[](int i)
{
	if (i < 0 || i >= m_taille[0])
		throw "L'indice est en dehors des limites.";

	return m_lignes[i];
}

template<typename T> Vect<T> const& Matrice<T>::operator[](int i) const
{
	if (i < 0 || i >= m_taille[0])
		throw "L'indice est en dehors des limites.";

	return m_lignes[i];
}

template<typename T> Vect<int> const& Matrice<T>::taille() const
{
	return m_taille;
}

template<typename T> void Matrice<T>::changerTaille(int m, int n)
{
	Vect<T>* lignesTmp = m_lignes;

	m_lignes = new Vect<T>[m];
	for (int i(0); i < m; i++)
	{
		if (i < m_taille[0])
		{
			m_lignes[i] = lignesTmp[i];
			m_lignes[i].changerTaille(n);
		}
		else
		{
			m_lignes[i] = Vect<T>(n);
		}
	}

	m_taille[0] = m;
	m_taille[1] = n;

	delete[] lignesTmp;
}


// Op�rations

template<typename T> Matrice<T>& Matrice<T>::operator+=(Matrice<T> const& M)
{
	if (M.m_taille[0] != m_taille[0] || M.m_taille[1] != m_taille[1])
		throw "Les matrices doivent etre de la meme taille.";

	for (int i(0); i < m_taille[0]; i++)
		for (int j(0); j < m_taille[1]; j++)
			m_lignes[i][j] += M.m_lignes[i][j];

	return *this;
}

template<typename T> Matrice<T> operator+(Matrice<T> const& M, Matrice<T> const& N)
{
	Matrice<T> R(M);
	R += N;

	return R;
}

template<typename T> Matrice<T>& Matrice<T>::operator-=(Matrice<T> const& M)
{
	if (M.m_taille[0] != m_taille[0] || M.m_taille[1] != m_taille[1])
		throw "Les matrices doivent etre de la meme taille.";

	for (int i(0); i < m_taille[0]; i++)
		for (int j(0); j < m_taille[1]; j++)
			m_lignes[i][j] -= M.m_lignes[i][j];

	return *this;
}

template<typename T> Matrice<T> operator-(Matrice<T> const& M, Matrice<T> const& N)
{
	Matrice<T> R(M);
	R -= N;

	return R;
}

template<typename T> Matrice<T>& Matrice<T>::operator*=(Matrice<T> const& M)
{
	if (m_taille[1] != M.m_taille[0])
		throw "Les tailles des matrices doivent se correspondre.";

	Vect<T>* lignes(m_lignes);

	int m(m_taille[0]), n(m_taille[1]), p(M.m_taille[1]);

	m_taille[1] = p;
	m_lignes = new Vect<T>[m];
	for (int i(0); i < m; i++)
	{
		m_lignes[i] = Vect<T>(p);
		for (int j(0); j < p; j++)
		{
			T x(0);
			for (int k(0); k < n; k++)
				x += lignes[i][k] * M[k][j];
			m_lignes[i][j] = x;
		}
	}

	delete[] lignes;

	return *this;
}

template<typename T> Matrice<T> operator*(Matrice<T> const& M, Matrice<T> const& N)
{
	Matrice<T> R(M);
	R *= N;

	return R;
}

template<typename T> Vect<T> operator*(Matrice<T> const& M, Vect<T> const& v)
{
	if (M.taille()[1] != v.taille())
		throw "Les tailles sont incompatibles";

	Vect<T> u(M.taille()[0]);
	for (int i(0); i < M.taille()[0]; i++)
		for (int k(0); k < M.taille()[1]; k++)
			u[i] += M[i][k] * v[k];

	return u;
}

template<typename T> Matrice<T>& Matrice<T>::operator*=(T const& x)
{
	for (int i(0); i < m_taille[0]; i++)
		for (int j(0); j < m_taille[1]; j++)
			m_lignes[i][j] *= x;

	return *this;
}

template<typename T> Matrice<T> operator*(Matrice<T> const& M, T const& x)
{
	Matrice<T> N(M);
	N *= x;

	return N;
}

template<typename T> Matrice<T> operator*(T const& x, Matrice<T> const& M)
{
	return M * x;
}

template<typename T> Matrice<T>& Matrice<T>::operator/=(T const& x)
{
	for (int i(0); i < m_taille[0]; i++)
		for (int j(0); j < m_taille[1]; j++)
			m_lignes[i][j] /= x;

	return *this;
}

template<typename T> Matrice<T> operator/(Matrice<T> const& M, T const& x)
{
	Matrice<T> N(M);
	N /= x;

	return N;
}


// Comparaisons

template<typename T> bool operator==(Matrice<T> const& M, Matrice<T> const& N)
{
	if (M.taille()[0] != N.taille()[0] || M.taille()[1] != N.taille()[1])
		return false;

	for (int i(0); i < M.taille()[0]; i++)
		for (int j(0); j < M.taille()[1]; j++)
			if (M[i][j] != N[i][j])
				return false;

	return true;
}

template<typename T> bool operator!=(Matrice<T> const& M, Matrice<T> const& N)
{
	return !(M == N);
}


// Fonctions sp�cifiques

template<typename T> T Matrice<T>::det() const
{
	if (m_taille[0] != m_taille[1] || m_taille[0] < 1)
		throw "La matrice doit etre carree et de taille n >= 1.";

	int n(m_taille[0]);
	Matrice<T> M(*this);
	T zero(0);

	for (int j(0); j < n; j++)
	{
		if (M[j][j] == zero)
		{
			for (int i(j+1); i < n; i++)
			{
				if (M[i][j] != zero)
				{
					M[j] += M[i];
					break;
				}
			}

			if (M[j][j] == zero)
				return zero;
		}

		for (int i(j + 1); i < n; i++)
			M[i] -= (M[i][j] / M[j][j]) * M[j];
	}

	T prod(M[0][0]);
	for (int i(1); i < n; i++)
		prod *= M[i][i];

	return prod;
}

template<typename T> Matrice<T> Matrice<T>::inv() const
{
	if (m_taille[0] != m_taille[1] || m_taille[0] < 1)
		throw "La matrice doit etre carree et de taille n >= 1.";

	int n(m_taille[0]);
	Matrice<T> M(*this), I(n, n);
	T zero(0);

	for (int i(0); i < n; i++)
		I[i][i] = 1;

	for (int j(0); j < n; j++)
	{
		if (M[j][j] == zero)
		{
			for (int i(j + 1); i < n; i++)
			{
				if (M[i][j] != zero)
				{
					I[i] /= M[i][j];
					M[i] /= M[i][j];
					I[j] += I[i];
					M[j] += M[i];
					break;
				}
			}

			if (M[j][j] == zero)
				throw "La matrice n'est pas inversible.";
		}
		else
		{
			I[j] /= M[j][j];
			M[j] /= M[j][j];
		}

		for (int i(j + 1); i < n; i++)
		{
			if (M[i][j] != zero)
			{
				I[i] -= M[i][j] * I[j];
				M[i] -= M[i][j] * M[j];
			}
		}
	}

	for (int j(n - 1); j >= 0; j--)
	{
		for (int i(j - 1); i >= 0; i--)
		{
			if (M[i][j] != zero)
			{
				I[i] -= M[i][j] * I[j];
				M[i] -= M[i][j] * M[j];
			}
		}
	}

	return I;
}

template<typename T> Matrice<T> Matrice<T>::transpose() const
{
	Matrice<T> M(m_taille[1], m_taille[0]);

	for (int i(0); i < m_taille[0]; i++)
		for (int j(0); j < m_taille[1]; j++)
			M[j][i] = m_lignes[i][j];

	return M;
}


// Affichage

template<typename T> std::ostream& operator<<(std::ostream& stream, Matrice<T> const& M)
{
	stream << "(";
	for (int i(0); i < M.taille()[0]; i++)
		if (i == 0)
			stream << M[i] << std::endl;
		else if (i == M.taille()[0] - 1)
			stream << " " << M[i];
		else
			stream << " " << M[i] << std::endl;
	stream << ")";

	return stream;
}


// Destructeur

template<typename T> void Matrice<T>::liberer()
{
	delete[] m_lignes;
}

template<typename T> Matrice<T>::~Matrice()
{
	if (m_actif)
		liberer();
}


// Autres

Vect<std::complex<long double>> DFT(Vect<std::complex<long double>> const& v);
Vect<std::complex<long double>> IDFT(Vect<std::complex<long double>> const& v);
Matrice<std::complex<long double>> DFT2D(Matrice<std::complex<long double>> const& M);
Matrice<std::complex<long double>> IDFT2D(Matrice<std::complex<long double>> const& M);
Matrice<long double> poissonSolveur(Matrice<long double> const& f, long double Lx, long double Ly);
Matrice<long double> cholesky(Matrice<long double> const& A);
