#pragma once

/**
 * \file Int.hpp
 * \brief Ensemble des fonctions et classes permettant la manipulations d'entiers de taille variable.
 * \author Reiex
 * 
 * Pour une description plus détaillée, voir la description de la classe Int.
 * 
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
#include <exception>
#include <limits.h>

/**
 * \brief Calcule x puissance n pour n supérieur ou égale à 1.
 * 
 * Cette fonction étant template, on souhaite qu'elle utilise un minimum de contraintes sur sa classe
 * template T. Ajouter le cas n nul imposerait l'existence d'un constructeur T(1) et le cas n negatif
 * l'existence d'une opération de division (en plus de T(1)).
 * 
 * Ici, les seuls contraintes pour T sont d'avoir une multiplication et une addition internes.
 * 
*/
template<typename T> T expoRapide(T const& x, int n)
{
	if (n < 1)
		throw "Unexpected: n < 1";

	if (n == 1)
		return x;

	int k(n - 1);
	T r(x), p(x);

	while (k != 0)
	{
		if (k % 2 == 0)
		{
			p *= p;
			k /= 2;
		}
		else
		{
			r *= p;
			k -= 1;
		}
	}

	return r;
}

/**
 * \brief Calcule le PGCD (Plus Grand Commun Diviseur) de a et b.
 * 
 * Les contraintes sur T sont d'avoir un constructeur T(0), un test d'égalité interne, une comparaison
 * interne, un moins unaire et un modulo interne.
 * 
*/
template<typename T> T pgcd(T const& a, T const& b)
{
	T zero(0);
	if (a == zero || b == zero)
		return T(1);

	T u(a), v(b), r(u % v);

	while (r != zero)
	{
		u = v;
		v = r;
		r = u % v;
	}

	if (v < zero)
		v = -v;

	return v;
}

/**
 * \class Int
 * \brief Classe permettant de manipuler des Entiers de taille variable.
 * 
 * SciPP intègre une gestion d'entiers "big int" c'est à dire des entiers de taille variable. Cette
 * taille peut être aussi grande que l'on veut puisque la seule limitation est la mémoire RAM de la
 * machine.
 * Ainsi pour un entier utilisant 1Ko de RAM l'entier peut déjà atteindre \f$ 256^{1000} \simeq 10^{2408} \f$
 * 
*/
class Int
{
	public:

		/** \brief Constructeur par défaut, initialise l'entier à 0. */
		Int();
		/** \brief Initialise l'entier à x. */
		Int(long long int x);
		Int(Int const& x);
		Int(Int&& x);

		Int& operator=(Int const& x);
		Int& operator=(Int&& x);

		Int& operator+=(Int const& x);
		Int& operator-=(Int const& x);
		Int& operator*=(Int const& x);
		Int& operator/=(Int const& x);
		Int& operator%=(Int const& x);
		Int operator-() const;
		Int operator+() const;

		/**
		 * \brief Erreur renvoyée lors de la tentative de conversion d'un Int trop grand en un long long int
		*/
		class IntTooBigException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		/**
		 * \brief Retourne l'entier sous forme de chaine de caractères
		*/
		std::string toString() const;
		/** 
		 * \brief Retourne, si c'est possible, l'entier sous forme de long long int.
		 * 
		 * Si l'entier est trop grand (ou trop petit) pour être converti en long long int, la 
		 * fonction retournera un entier d'apparence aléatoire, il appartient au programmeur de
		 * vérifier si l'on peut convertir l'entier.
		 * 
		*/
		long long int toInt() const;
		/**
		 * \brief Indique si l'entier est activé ou non.
		 * 
		 * Un entier est désactivé s'il a été déplacé, en utilisant std::move par exemple.
		*/
		bool estActif() const;

		~Int();

	private:

		int m_taille;
		uint8_t* m_x;
		bool m_positif;
		bool m_actif;

	friend Int&& operator-(Int&& x);

	friend bool operator==(Int const& x, Int const& y);
	friend bool operator!=(Int const& x, Int const& y);
	friend bool operator>(Int const& x, Int const& y);
	friend bool operator<(Int const& x, Int const& y);
	friend bool operator>=(Int const& x, Int const& y);
	friend bool operator<=(Int const& x, Int const& y);

	friend std::ostream& operator<<(std::ostream& stream, Int const& x);
};


// Operations

Int operator+(Int const& x, Int const& y);
Int&& operator+(Int&& x, Int const& y);
Int&& operator+(Int const& x, Int&& y);
Int&& operator+(Int&& x, Int&& y);

Int operator-(Int const& x, Int const& y);
Int&& operator-(Int&& x, Int const& y);
Int&& operator-(Int const& x, Int&& y);
Int&& operator-(Int&& x, Int&& y);

Int operator*(Int const& x, Int const& y);
Int&& operator*(Int&& x, Int const& y);
Int&& operator*(Int const& x, Int&& y);
Int&& operator*(Int&& x, Int&& y);

Int operator/(Int const& x, Int const& y);
Int&& operator/(Int&& x, Int const& y);
Int&& operator/(Int&& x, Int&& y);

Int operator%(Int const& x, Int const& y);
Int&& operator%(Int&& x, Int const& y);
Int&& operator%(Int&& x, Int&& y);

Int&& operator-(Int&& x);
Int&& operator+(Int&& x);


// Comparaisons

bool operator==(Int const& x, Int const& y);
bool operator!=(Int const& x, Int const& y);
bool operator>(Int const& x, Int const& y);
bool operator<(Int const& x, Int const& y);
bool operator>=(Int const& x, Int const& y);
bool operator<=(Int const& x, Int const& y);


// Affichage

std::ostream& operator<<(std::ostream& stream, Int const& x);

// Autres

/**
 * \brief Calcule le coefficient binomial de deux entiers et le renvoie sous forme d'Int.
 * 
 * La conversion en Int ne se fait que sur la valeur de retour (et non pas en entrée) pour des
 * raisons pratiques. Cela peut être amené à changer, notemment avec une surcharge de cette
 * fonction.
*/
Int binom(long long int n, long long int p);
