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


// Classe Int

class Int
{
	public:

		Int();
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

		long long int toInt() const;

		~Int();

	private:

		int m_taille;
		uint8_t* m_x;
		bool m_positif;
		bool m_actif;

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

Int binom(int n, int p);
