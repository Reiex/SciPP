#pragma once

/**
 * \file Matrice.hpp
 * \brief Ensemble des fonctions et classes permettant la manipulation de matrices mathématiques.
 * \author Reiex
 *
 * Pour une description plus détaillée, voir la description de la classe Matrice.
*/

#include <iostream>
#include <exception>
#include <complex>
#include <initializer_list>
#include <limits.h>
#include <SciPP/Vect.hpp>

namespace scp
{
	/**
	 * \class Matrice
	 * \brief Classe permettant de manipuler des matrices mathématiques.
	 *
	 * La classe Matrice est template et prend en argument template une classe T.
	 * L'espace dans lequel se place la matrice est l'espace de cette classe T.
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
	template<typename T> class Matrice
	{
	public:

		/** \brief Constructeur par défaut, initialise une matrice de taille nulle. */
		Matrice();
		/** \brief Initialise une matrice de m lignes et n colonnes avec `T()`. */
		Matrice(unsigned int m, unsigned int n);
		/** \brief Initialise une matrice avec une liste d'initialisation */
		Matrice(std::initializer_list<std::initializer_list<T>> tab);
		/** \brief Initialise une matrice de m lignes et n colonnes. Il faut donc que `tab` soit de taille m*n. */
		Matrice(T const* tab, unsigned int m, unsigned int n);
		Matrice(Matrice<T> const& M);
		Matrice(Matrice<T>&& M);

		Matrice<T>& operator=(Matrice<T> const& M);
		Matrice<T>& operator=(Matrice<T>&& M);

		Vect<T>& operator[](unsigned int i);
		Vect<T> const& operator[](unsigned int i) const;
		/** \brief Retourne un vecteur contenant deux éléments, le nombre de lignes et le nombre de colonnes. */
		Vect<unsigned int> const& size() const;

		Matrice<T>& operator+=(Matrice<T> const& M);
		Matrice<T>& operator-=(Matrice<T> const& M);
		Matrice<T>& operator*=(Matrice<T> const& M);
		Matrice<T>& operator*=(T const& x);
		Matrice<T>& operator/=(T const& x);

		/**
		 * \enum ConvolveMethod
		 * \brief Spécifie la méthode utilisée pour la gestion des bords de la matrice lors d'une convolution
		 */
		enum class ConvolveMethod {
			Periodic,  /**< La matrice est considérée comme periodique et est donc répétée. */
			Continuous,  /**< La matrice est prolongée par le dernier élément. */
			Zero  /**< La matrice est prolongée par des zeros. */
		};

		/** \brief Retourne le déterminant de la matrice. */
		T det() const;
		/** \brief Retourne l'inverse de la matrice. */
		Matrice<T> inv() const;
		/** \brief Retourne la transposée de la matrice. */
		Matrice<T> transpose() const;
		/** \brief Retourne l'application du filtre de convolution M sur la matrice */
		Matrice<T> convolved(Matrice<T> const& M, ConvolveMethod method = ConvolveMethod::Periodic) const;

		~Matrice();

	private:

		void liberer();

		Vect<T>* m_lignes;
		Vect<unsigned int> m_taille;
	};


	// Constructeurs

	template<typename T> Matrice<T>::Matrice()
	{
		m_lignes = nullptr;
		m_taille = Vect<unsigned int>(2);
	}

	template<typename T> Matrice<T>::Matrice(unsigned int m, unsigned int n) : Matrice<T>()
	{
		if (m > 0 && n > 0)
		{
			m_taille = Vect<unsigned int>(2);
			m_taille[0] = m;
			m_taille[1] = n;

			m_lignes = new Vect<T>[m];
			for (unsigned int i(0); i < m; i++)
				m_lignes[i] = Vect<T>(n);
		}
	}

	template<typename T> Matrice<T>::Matrice(std::initializer_list<std::initializer_list<T>> tab) : Matrice<T>()
	{
		if (tab.size() == 0)
			return;

		if (tab.begin()[0].size() > 0)
		{
			m_taille = Vect<unsigned int>(2);
			m_taille[0] = tab.size();
			m_taille[1] = tab.begin()[0].size();

			m_lignes = new Vect<T>[m_taille[0]];
			for (unsigned int i(0); i < m_taille[0]; i++)
			{
				if (tab.begin()[i].size() != m_taille[1])
				{
					std::string error;
					error = "Invalid matrix size. Detected size: " + std::to_string(m_taille[0]) + "x" + std::to_string(m_taille[1]) + ".\n";
					error = "But row " + std::to_string(i) + " has size " + std::to_string(tab.begin()[i].size()) + ".";
					throw std::out_of_range(error);
				}

				m_lignes[i] = Vect<T>(m_taille[1]);
				for (unsigned int j(0); j < m_taille[1]; j++)
					m_lignes[i][j] = tab.begin()[i].begin()[j];
			}
		}
	}

	template<typename T> Matrice<T>::Matrice(T const* tab, unsigned int m, unsigned int n) : Matrice<T>()
	{
		if (m > 0 && n > 0)
		{
			m_taille = Vect<unsigned int>(2);
			m_taille[0] = m;
			m_taille[1] = n;

			m_lignes = new Vect<T>[m];
			for (unsigned int i(0); i < m; i++)
			{
				m_lignes[i] = Vect<T>(n);
				for (unsigned int j(0); j < n; j++)
					m_lignes[i][j] = tab[i * n + j];
			}
		}
	}

	template<typename T> Matrice<T>::Matrice(Matrice<T> const& M) : Matrice<T>()
	{
		*this = M;
	}

	template<typename T> Matrice<T>::Matrice(Matrice<T>&& M) : Matrice<T>()
	{
		*this = std::move(M);
	}


	// Copie et mouvement

	template<typename T> Matrice<T>& Matrice<T>::operator=(Matrice<T> const& M)
	{
		liberer();

		m_taille = M.m_taille;
		m_lignes = new Vect<T>[m_taille[0]];
		for (unsigned int i(0); i < m_taille[0]; i++)
			m_lignes[i] = M.m_lignes[i];

		return *this;
	}

	template<typename T> Matrice<T>& Matrice<T>::operator=(Matrice<T>&& M)
	{
		liberer();

		m_taille = M.m_taille;
		m_lignes = M.m_lignes;

		M.m_taille = Vect<unsigned int>(2);
		M.m_lignes = nullptr;

		return *this;
	}


	// Acces et modification de la structure

	template<typename T> Vect<T>& Matrice<T>::operator[](unsigned int i)
	{
		if (i >= m_taille[0])
			throw "L'indice est en dehors des limites.";

		return m_lignes[i];
	}

	template<typename T> Vect<T> const& Matrice<T>::operator[](unsigned int i) const
	{
		if (i >= m_taille[0])
			throw "L'indice est en dehors des limites.";

		return m_lignes[i];
	}

	template<typename T> Vect<unsigned int> const& Matrice<T>::size() const
	{
		return m_taille;
	}


	// Opérations

	template<typename T> Matrice<T>& Matrice<T>::operator+=(Matrice<T> const& M)
	{
		if (M.m_taille[0] != m_taille[0] || M.m_taille[1] != m_taille[1])
			throw "Les matrices doivent etre de la meme taille.";

		for (unsigned int i(0); i < m_taille[0]; i++)
			for (unsigned int j(0); j < m_taille[1]; j++)
				m_lignes[i][j] += M.m_lignes[i][j];

		return *this;
	}

	template<typename T> Matrice<T> operator+(Matrice<T> const& M, Matrice<T> const& N)
	{
		Matrice<T> R(M);
		R += N;

		return R;
	}

	template<typename T> Matrice<T>&& operator+(Matrice<T>&& M, Matrice<T> const& N)
	{
		M += N;
		return std::move(M);
	}

	template<typename T> Matrice<T>&& operator+(Matrice<T> const& M, Matrice<T>&& N)
	{
		N += M;
		return std::move(N);
	}

	template<typename T> Matrice<T>&& operator+(Matrice<T>&& M, Matrice<T>&& N)
	{
		M += N;
		return std::move(M);
	}


	template<typename T> Matrice<T>& Matrice<T>::operator-=(Matrice<T> const& M)
	{
		if (M.m_taille[0] != m_taille[0] || M.m_taille[1] != m_taille[1])
			throw "Les matrices doivent etre de la meme taille.";

		for (unsigned int i(0); i < m_taille[0]; i++)
			for (unsigned int j(0); j < m_taille[1]; j++)
				m_lignes[i][j] -= M.m_lignes[i][j];

		return *this;
	}

	template<typename T> Matrice<T> operator-(Matrice<T> const& M, Matrice<T> const& N)
	{
		Matrice<T> R(M);
		R -= N;

		return R;
	}

	template<typename T> Matrice<T>&& operator-(Matrice<T>&& M, Matrice<T> const& N)
	{
		M -= N;
		return std::move(M);
	}

	template<typename T> Matrice<T>&& operator-(Matrice<T>&& M, Matrice<T>&& N)
	{
		M -= N;
		return std::move(M);
	}


	template<typename T> Matrice<T>& Matrice<T>::operator*=(Matrice<T> const& M)
	{
		if (m_taille[1] != M.m_taille[0])
			throw "Les tailles des matrices doivent se correspondre.";

		Vect<T>* lignes(m_lignes);

		int m(m_taille[0]), n(m_taille[1]), p(M.m_taille[1]);

		m_taille[1] = p;
		m_lignes = new Vect<T>[m];
		for (unsigned int i(0); i < m; i++)
		{
			m_lignes[i] = Vect<T>(p);
			for (unsigned int j(0); j < p; j++)
			{
				T x(0);
				for (unsigned int k(0); k < n; k++)
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
		if (M.size()[1] != v.size())
			throw "Les tailles sont incompatibles";

		Vect<T> u(M.size()[0]);
		for (unsigned int i(0); i < M.size()[0]; i++)
			for (unsigned int k(0); k < M.size()[1]; k++)
				u[i] += M[i][k] * v[k];

		return u;
	}

	template<typename T> Vect<T> operator*(Vect<T> const& v, Matrice<T> const& M)
	{
		if (M.size()[0] != v.size())
			throw "Les tailles sont incompatibles";

		Vect<T> u(M.size()[1]);
		for (unsigned int j(0); j < M.size()[1]; j++)
			for (unsigned int k(0); k < M.size()[0]; k++)
				u[j] += M[k][j] * v[k];

		return u;
	}


	template<typename T> Matrice<T>& Matrice<T>::operator*=(T const& x)
	{
		for (unsigned int i(0); i < m_taille[0]; i++)
			for (unsigned int j(0); j < m_taille[1]; j++)
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
		for (unsigned int i(0); i < m_taille[0]; i++)
			for (unsigned int j(0); j < m_taille[1]; j++)
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
		if (M.size()[0] != N.size()[0] || M.size()[1] != N.size()[1])
			return false;

		for (unsigned int i(0); i < M.size()[0]; i++)
			for (unsigned int j(0); j < M.size()[1]; j++)
				if (M[i][j] != N[i][j])
					return false;

		return true;
	}

	template<typename T> bool operator!=(Matrice<T> const& M, Matrice<T> const& N)
	{
		return !(M == N);
	}


	// Fonctions spécifiques

	template<typename T> T Matrice<T>::det() const
	{
		if (m_taille[0] != m_taille[1] || m_taille[0] < 1)
			throw "La matrice doit etre carree et de taille n >= 1.";

		unsigned int n(m_taille[0]);
		Matrice<T> M(*this);
		T zero(0);

		for (unsigned int j(0); j < n; j++)
		{
			if (M[j][j] == zero)
			{
				for (unsigned int i(j + 1); i < n; i++)
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

			for (unsigned int i(j + 1); i < n; i++)
				M[i] -= (M[i][j] / M[j][j]) * M[j];
		}

		T prod(M[0][0]);
		for (unsigned int i(1); i < n; i++)
			prod *= M[i][i];

		return prod;
	}

	template<typename T> Matrice<T> Matrice<T>::inv() const
	{
		if (m_taille[0] != m_taille[1] || m_taille[0] < 1)
			throw "La matrice doit etre carree et de taille n >= 1.";

		unsigned int n(m_taille[0]);
		Matrice<T> M(*this), I(n, n);
		T zero(0);

		for (unsigned int i(0); i < n; i++)
			I[i][i] = 1;

		for (unsigned int j(0); j < n; j++)
		{
			if (M[j][j] == zero)
			{
				for (unsigned int i(j + 1); i < n; i++)
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

			for (unsigned int i(j + 1); i < n; i++)
			{
				if (M[i][j] != zero)
				{
					I[i] -= M[i][j] * I[j];
					M[i] -= M[i][j] * M[j];
				}
			}
		}

		for (unsigned int j(n - 1); j != UINT_MAX; j--)
		{
			for (unsigned int i(j - 1); i != UINT_MAX; i--)
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

		for (unsigned int i(0); i < m_taille[0]; i++)
			for (unsigned int j(0); j < m_taille[1]; j++)
				M[j][i] = m_lignes[i][j];

		return M;
	}

	template<typename T> Matrice<T> Matrice<T>::convolved(Matrice<T> const& M, ConvolveMethod method) const
	{
		unsigned int m(m_taille[0]), n(m_taille[1]), z(M.m_taille[0]), t(M.m_taille[1]);

		if (z % 2 == 0 || t % 2 == 0)
			throw "Les tailles sont incompatibles";

		Matrice<T> R(m_taille[0], m_taille[1]);

		for (unsigned int i(0); i < m; i++)
		{
			for (unsigned int j(0); j < n; j++)
			{
				R[i][j] = 0;
				for (unsigned int k(0); k < z; k++)
				{
					for (unsigned int l(0); l < t; l++)
					{
						int ox((int)k - z / 2), oy((int)l - t / 2);
						T I;
						if (method == ConvolveMethod::Periodic)
						{
							I = m_lignes[(i + ox) % m][(j + oy) % n];
						}
						else if (method == ConvolveMethod::Continuous)
						{
							if (i + ox > m - 1)
								ox = m - 1 - i;
							if (i + ox < 0)
								ox = -(int)i;
							if (j + oy > n - 1)
								oy = n - 1 - j;
							if (j + oy < 0)
								oy = -(int)j;

							I = m_lignes[i + ox][j + oy];
						}
						else if (method == ConvolveMethod::Zero)
						{
							if (i + ox > m - 1 || i + ox < 0 || j + oy > n - 1 || j + oy < 0)
								I = 0;
							else
								I = m_lignes[i + ox][j + oy];
						}
						R[i][j] += I * M[k][l];
					}
				}
			}
		}

		return R;
	}


	// Affichage

	template<typename T> std::ostream& operator<<(std::ostream& stream, Matrice<T> const& M)
	{
		stream << "(";
		for (unsigned int i(0); i < M.size()[0]; i++)
		{
			if (i != 0)
				stream << " ";
			for (unsigned int j(0); j < M.size()[1]; j++)
				if (j == M.size()[1] - 1)
					stream << M[i][j];
				else
					stream << M[i][j] << " ";
			if (i != M.size()[0] - 1)
				stream << std::endl;
		}
		stream << ")";

		return stream;
	}


	// Destructeur

	template<typename T> void Matrice<T>::liberer()
	{
		if (m_lignes != nullptr)
			delete[] m_lignes;

		m_lignes = nullptr;
		m_taille = Vect<unsigned int>(2);
	}

	template<typename T> Matrice<T>::~Matrice()
	{
		liberer();
	}


	// Autres

	/**
	 * \relates Vect
	 * \brief Transformée de Fourier discrète d'un vecteur.
	 */
	Vect<std::complex<long double>> FFT(Vect<std::complex<long double>> const& v);
	/**
	 * \relates Vect
	 * \brief Transformée de Fourier discrète inverse d'un vecteur.
	 */
	Vect<std::complex<long double>> IFFT(Vect<std::complex<long double>> const& v);
	/**
	 * \relates Matrice
	 * \brief Transformée de Fourier discrète d'une matrice.
	 */
	Matrice<std::complex<long double>> FFT(Matrice<std::complex<long double>> const& M);
	/**
	 * \relates Matrice
	 * \brief Transformée de Fourier discrète inverse d'une matrice.
	 */
	Matrice<std::complex<long double>> IFFT(Matrice<std::complex<long double>> const& M);


	/**
	 * \relates Vect
	 * \brief Transformée de cosinus discrète (Type II corrigée) d'un vecteur.
	 */
	Vect<long double> DCT(Vect<long double> const& v);
	/**
	 * \relates Vect
	 * \brief Transformée inverse de cosinus discrète (Type II corrigée) d'un vecteur.
	 */
	Vect<long double> IDCT(Vect<long double> const& v);
	/**
	 * \relates Matrice
	 * \brief Transformée de cosinus discrète (Type II corrigée) d'une matrice.
	 */
	Matrice<long double> DCT(Matrice<long double> const& M);
	/**
	 * \relates Matrice
	 * \brief Transformée inverse de cosinus discrète (Type II corrigée) d'une matrice.
	 */
	Matrice<long double> IDCT(Matrice<long double> const& M);


	/**
	 * \relates Matrice
	 * \brief Résout l'équation \f$\Delta u = f \f$ en passant dans le domaine fréquentiel.
	 */
	Matrice<long double> poissonSolveur(Matrice<long double> const& f, long double Lx, long double Ly);
	/**
	 * \relates Matrice
	 * \brief Retourne un vecteur \f$X\f$ tel que \f$AX = B\f$ en utilisant la décomposition de Cholesky
	 *
	 * Attention, il appartient à l'utilisateur de vérifier que la matrice \f$A\f$ est symétrique positive.
	 */
	Vect<long double> cholesky(Matrice<long double> const& A, Vect<long double> const& B);
}
