#pragma once

#include <iostream>
#include <cstdint>


// Templates necessaires

template<typename T> T expoRapide(T const& x, int n)
{
	if (n < 1)
		throw "n doit etre superieur a 1.";

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

	return v;
}


// Classe Entier

class Entier
{
	public:

		Entier();
		Entier(long long int x);
		Entier(Entier const& x);
		Entier(Entier&& x);

		Entier& operator=(Entier const& x);
		Entier& operator=(Entier&& x);

		Entier& operator+=(Entier const& x);
		Entier& operator-=(Entier const& x);
		Entier& operator*=(Entier const& x);
		Entier& operator/=(Entier const& x);
		Entier& operator%=(Entier const& x);
		Entier operator-() const;
		Entier operator+() const;

		long long int toInt() const;

		~Entier();

	private:

		int m_taille;
		uint8_t* m_x;
		bool m_positif;
		bool m_actif;

	friend bool operator==(Entier const& x, Entier const& y);
	friend bool operator!=(Entier const& x, Entier const& y);
	friend bool operator>(Entier const& x, Entier const& y);
	friend bool operator<(Entier const& x, Entier const& y);
	friend bool operator>=(Entier const& x, Entier const& y);
	friend bool operator<=(Entier const& x, Entier const& y);

	friend std::ostream& operator<<(std::ostream& stream, Entier const& x);
};


// Operations

Entier operator+(Entier const& x, Entier const& y);
Entier&& operator+(Entier&& x, Entier const& y);
Entier&& operator+(Entier const& x, Entier&& y);
Entier&& operator+(Entier&& x, Entier&& y);

Entier operator-(Entier const& x, Entier const& y);
Entier&& operator-(Entier&& x, Entier const& y);
Entier&& operator-(Entier const& x, Entier&& y);
Entier&& operator-(Entier&& x, Entier&& y);

Entier operator*(Entier const& x, Entier const& y);
Entier&& operator*(Entier&& x, Entier const& y);
Entier&& operator*(Entier const& x, Entier&& y);
Entier&& operator*(Entier&& x, Entier&& y);

Entier operator/(Entier const& x, Entier const& y);
Entier&& operator/(Entier&& x, Entier const& y);
Entier&& operator/(Entier&& x, Entier&& y);

Entier operator%(Entier const& x, Entier const& y);
Entier&& operator%(Entier&& x, Entier const& y);
Entier&& operator%(Entier&& x, Entier&& y);


// Comparaisons

bool operator==(Entier const& x, Entier const& y);
bool operator!=(Entier const& x, Entier const& y);
bool operator>(Entier const& x, Entier const& y);
bool operator<(Entier const& x, Entier const& y);
bool operator>=(Entier const& x, Entier const& y);
bool operator<=(Entier const& x, Entier const& y);


// Affichage

std::ostream& operator<<(std::ostream& stream, Entier const& x);

// Autres

Entier binom(int n, int p);
