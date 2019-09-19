#pragma once

#include <iostream>
#include <cstdint>


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


// Opérations

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
