#include "Int.hpp"


// Exceptions

const char* Int::ZeroDivisionException::what() const throw()
{
	return "Tentative de division par zero.";
}

const char* Int::IntTooBigException::what() const throw()
{
	return "Tentative de conversion d'un entier trop grand pour etre converti en long long int.";
}


// Constructeurs

Int::Int() :
	m_taille(1),
	m_x(new uint8_t[m_taille]),
	m_positif(true),
	m_actif(true)
{
	m_x[0] = 0;
}

Int::Int(long long int x)
{
	m_positif = (x >= 0);

	if (x < 0)
		x = -x;

	long long int y(x/256);
	m_taille = 1;
	while (y != 0)
	{
		y /= 256;
		m_taille += 1;
	}

	m_x = new uint8_t[m_taille];
	for (int i(0); i < m_taille; i++)
	{
		m_x[i] = x % 256;
		x /= 256;
	}

	m_actif = true;
}

Int::Int(Int const& x):
	m_positif(x.m_positif),
	m_taille(x.m_taille),
	m_x(new uint8_t[m_taille]),
	m_actif(x.m_actif)
{
	for (int i(0); i < m_taille; i++)
		m_x[i] = x.m_x[i];
}

Int::Int(Int&& x):
	m_positif(x.m_positif),
	m_taille(x.m_taille),
	m_x(x.m_x),
	m_actif(x.m_actif)
{
	x.m_actif = false;
}


// Copie et mouvement

Int& Int::operator=(Int const& x)
{
	delete[] m_x;

	m_positif = x.m_positif;
	m_taille = x.m_taille;

	m_x = new uint8_t[m_taille];
	for (int i(0); i < m_taille; i++)
		m_x[i] = x.m_x[i];

	m_actif = x.m_actif;

	return *this;
}

Int& Int::operator=(Int&& x)
{
	if (m_actif)
		delete[] m_x;

	m_positif = x.m_positif;
	m_taille = x.m_taille;
	m_x = x.m_x;
	m_actif = x.m_actif;

	x.m_actif = false;

	return *this;
}


// Operations

Int& Int::operator+=(Int const& x)
{
	if (m_positif == x.m_positif)
	{
		uint16_t buffer;
		int taille;
		uint8_t* oldX(m_x);

		// Determiner la taille de l'Int

		if (m_taille > x.m_taille)
		{
			int i(m_taille - 1);
			taille = m_taille;
			while (i >= x.m_taille && m_x[i] == 255)
				i--;

			if (i == x.m_taille - 1)
			{
				buffer = m_x[i] + x.m_x[i];
				while (buffer >= 255)
				{
					if (buffer >= 256)
					{
						taille = m_taille + 1;
						break;
					}

					i--;
					if (i < 0)
						break;
					else
						buffer = m_x[i] + x.m_x[i];
				}
			}
		}
		else if (m_taille < x.m_taille)
		{
			int i(x.m_taille - 1);
			taille = x.m_taille;
			while (i >= m_taille && x.m_x[i] == 255)
				i--;

			if (i == m_taille - 1)
			{
				buffer = m_x[i] + x.m_x[i];
				while (buffer >= 255)
				{
					if (buffer >= 256)
					{
						taille = m_taille + 1;
						break;
					}

					i--;
					if (i < 0)
						break;
					else
						buffer = m_x[i] + x.m_x[i];
				}
			}
		}
		else
		{
			int i(m_taille - 1);
			buffer = m_x[i] + x.m_x[i];
			taille = m_taille;
			while (buffer >= 255)
			{
				if (buffer >= 256)
				{
					taille = m_taille + 1;
					break;
				}
				
				i--;
				if (i < 0)
					break;
				else
					buffer = m_x[i] + x.m_x[i];
			}
		}

		// Allouer un nouvel espace memoire si necessaire

		if (taille != m_taille)
			m_x = new uint8_t[taille];

		// Faire la somme elle-meme

		buffer = 0;
		for (int i(0); i < taille; i++)
		{
			if (i < m_taille)
				buffer += oldX[i];
			if (i < x.m_taille)
				buffer += x.m_x[i];
			m_x[i] = buffer % 256;
			buffer >>= 8;
		}

		// Supprimer les espaces memoires inutilement alloues s'il y en a

		if (taille != m_taille)
		{
			m_taille = taille;
			delete[] oldX;
		}
	}
	else
	{
		m_positif = !m_positif;
		*this -= x;
		m_positif = !m_positif;
	}

	return *this;
}

Int& Int::operator-=(Int const& x)
{
	if (m_positif == x.m_positif)
	{
		uint8_t* oldX(m_x);
		uint8_t* grand;
		uint8_t* petit;
		int grandeTaille, petiteTaille;

		if (*this == x)
		{
			delete[] m_x;
			m_taille = 1;
			m_x = new uint8_t[1];
			m_x[0] = 0;
			m_positif = true;

			return *this;
		}

		if ((m_positif && *this > x) || (!m_positif && *this < x))
		{
			grand = m_x;
			grandeTaille = m_taille;
			petit = x.m_x;
			petiteTaille = x.m_taille;
		}
		else
		{
			grand = x.m_x;
			grandeTaille = x.m_taille;
			petit = m_x;
			petiteTaille = m_taille;
			m_positif = !m_positif;
		}

		int taille(grandeTaille);
		if (grandeTaille == petiteTaille)
			while (grand[taille - 1] == petit[taille - 1] && taille > 1)
				taille--;

		m_x = new uint8_t[taille];

		for (int i(taille-1); i >= 0; i--)
		{
			m_x[i] = grand[i];
			if (i < petiteTaille)
			{
				if (grand[i] >= petit[i])
				{
					m_x[i] -= petit[i];
				}
				else
				{
					m_x[i] += 256 - petit[i];
					int j(1);
					while (m_x[i + j] == 0)
						j++;
					m_x[i + j]--;
					for (int k(1); k < j; k++)
						m_x[i + k] = 255;
				}
			}
		}

		if (m_x[taille - 1] == 0)
		{
			uint8_t* newX(new uint8_t[taille - 1]);
			for (int i(0); i < taille - 1; i++)
				newX[i] = m_x[i];

			delete[] m_x;

			m_x = newX;
			taille--;
		}

		m_taille = taille;
		delete[] oldX;
	}
	else
	{
		m_positif = !m_positif;
		*this += x;
		m_positif = !m_positif;
	}

	return *this;
}

Int& Int::operator*=(Int const& x)
{
	if (*this == 0 || x == 0)
	{
		delete[] m_x;
		m_taille = 1;
		m_x = new uint8_t[m_taille];
		m_x[0] = 0;
		m_positif = true;
	}
	else
	{
		uint16_t buffer;
		uint8_t* xTmp(new uint8_t[m_taille + x.m_taille]);
		for (int i(0); i < m_taille + x.m_taille; i++)
			xTmp[i] = 0;
		for (int i(0); i < m_taille; i++)
		{
			buffer = 0;
			for (int j(0); j < x.m_taille; j++)
			{
				buffer += m_x[i] * x.m_x[j];
				buffer += xTmp[i + j];
				xTmp[i + j] = buffer % 256;
				buffer >>= 8;
			}
			xTmp[i + x.m_taille] += buffer;
		}

		int taille(m_taille + x.m_taille);
		while (xTmp[taille - 1] == 0)
			taille--;

		delete[] m_x;
		m_x = new uint8_t[taille];
		m_taille = taille;
		m_positif = (m_positif == x.m_positif);
		for (int i(0); i < taille; i++)
			m_x[i] = xTmp[i];
		delete[] xTmp;
	}

	return *this;
}

int getNbBits(uint8_t x)
{
	int i(0);
	while (x != 0)
	{
		x >>= 1;
		i++;
	}

	return i;
}

Int& Int::operator/=(Int const& x)
{
	if (x == 0)
		throw ZeroDivisionException();

	int tailleBits((m_taille - 1)* 8 + getNbBits(m_x[m_taille - 1]));
	int xTailleBits((x.m_taille - 1)* 8 + getNbBits(x.m_x[x.m_taille - 1]));

	if (xTailleBits > tailleBits || *this == 0)
	{
		delete[] m_x;
		m_taille = 1;
		m_x = new uint8_t[m_taille];
		m_x[0] = 0;
		m_positif = true;

		return *this;
	}

	int taille((tailleBits - xTailleBits + 1)/8 + ((tailleBits - xTailleBits + 1) % 8 != 0));
	uint8_t* newX(new uint8_t[taille]);
	for (int i(0); i < taille; i++)
		newX[i] = 0;

	for (int i(tailleBits - xTailleBits); i >= 0; i--)
	{
		bool soustrairePossible(true);
		uint8_t bitA, bitB;
		int k;
		if (i != tailleBits - xTailleBits && (m_x[(i + xTailleBits) >> 3] >> ((i + xTailleBits) % 8)) % 2)
		{
			soustrairePossible = true;
		}
		else
		{
			for (int j(xTailleBits - 1); j >= 0; j--)
			{
				bitA = (x.m_x[j >> 3] >> (j % 8)) % 2;
				bitB = (m_x[(i + j) >> 3] >> ((i + j) % 8)) % 2;

				if (bitA < bitB)
				{
					soustrairePossible = true;
					break;
				}
				else if (bitA > bitB)
				{
					soustrairePossible = false;
					break;
				}
			}
		}

		if (soustrairePossible)
		{
			for (int j(xTailleBits - 1); j >= 0; j--)
			{
				k = i + j;
				bitA = (x.m_x[j >> 3] >> (j % 8)) % 2;
				bitB = (m_x[k >> 3] >> (k % 8)) % 2;
				if (bitA && bitB)
					m_x[k >> 3] -= 1 << (k % 8);
				else if (bitA && !bitB)
				{
					int l(1);
					while (!((m_x[(k + l) >> 3] >> ((k + l) % 8)) % 2))
						l++;
					m_x[(k + l) >> 3] -= 1 << ((k + l) % 8);
					l--;
					while (l >= 0)
					{
						m_x[(k + l) >> 3] += 1 << ((k + l) % 8);
						l--;
					}
				}
			}

			newX[i >> 3] += 1 << (i % 8);
		}
	}

	delete[] m_x;
	m_x = newX;
	m_taille = taille;
	m_positif = (m_positif == x.m_positif);

	return *this;
}

Int& Int::operator%=(Int const& x)
{
	*this -= (*this / x) * x;
	return *this;
}

Int Int::operator-() const
{
	Int x(*this);

	if (m_taille != 1 || m_x[0] != 0)
		x.m_positif = !m_positif;

	return x;
}

Int Int::operator+() const
{
	return Int(*this);
}


// Fonctions specifiques

std::string Int::toString() const
{
	std::stringstream stream;
	stream << *this;

	return stream.str();
}

long long int Int::toInt() const
{
	int t(sizeof(long long int));

	if (*this > LLONG_MAX || *this < LLONG_MIN)
		throw IntTooBigException();

	long long int x(0);

	for (int i(m_taille - 1); i >= 0; i--)
	{
		x = x << 8;
		x += m_x[i];
	}

	if (!m_positif)
		x = -x;

	return x;
}

bool Int::estActif() const
{
	return m_actif;
}


// Destructeur

Int::~Int()
{
	if (m_actif)
	{
		delete[] m_x;
	}
}


/*  
	------------------------------------------------------------------------
	-------------------- FONCTIONS EXTERNES A LA CLASSE --------------------
	------------------------------------------------------------------------
*/


// Operations

Int operator+(Int const& x, Int const& y)
{
	Int z(x);
	z += y;
	return z;
}

Int&& operator+(Int&& x, Int const& y)
{
	x += y;
	return std::move(x);
}

Int&& operator+(Int const& x, Int&& y)
{
	y += x;
	return std::move(y);
}

Int&& operator+(Int&& x, Int&& y)
{
	x += y;
	return std::move(x);
}


Int operator-(Int const& x, Int const& y)
{
	Int z(x);
	z -= y;
	return z;
}

Int&& operator-(Int&& x, Int const& y)
{
	x -= y;
	return std::move(x);
}

Int&& operator-(Int const& x, Int&& y)
{
	y -= x;
	return -std::move(y);
}

Int&& operator-(Int&& x, Int&& y)
{
	x -= y;
	return std::move(x);
}


Int operator*(Int const& x, Int const& y)
{
	Int z(x);
	z *= y;
	return z;
}

Int&& operator*(Int&& x, Int const& y)
{
	x *= y;
	return std::move(x);
}

Int&& operator*(Int const& x, Int&& y)
{
	y *= x;
	return std::move(y);
}

Int&& operator*(Int&& x, Int&& y)
{
	x *= y;
	return std::move(x);
}


Int operator/(Int const& x, Int const& y)
{
	Int z(x);
	z /= y;
	return z;
}

Int&& operator/(Int&& x, Int const& y)
{
	x /= y;
	return std::move(x);
}

Int&& operator/(Int&& x, Int&& y)
{
	x /= y;
	return std::move(x);
}


Int operator%(Int const& x, Int const& y)
{
	Int z(x);
	z %= y;
	return z;
}

Int&& operator%(Int&& x, Int const& y)
{
	x %= y;
	return std::move(x);
}

Int&& operator%(Int&& x, Int&& y)
{
	x %= y;
	return std::move(x);
}


Int&& operator-(Int&& x)
{
	if (x.m_taille != 1 || x.m_x[0] != 0)
		x.m_positif = !x.m_positif;

	return std::move(x);
}

Int&& operator+(Int&& x)
{
	return std::move(x);
}


// Comparaisons

bool operator==(Int const& x, Int const& y)
{
	if (x.m_taille != y.m_taille)
		return false;

	if (x.m_positif != y.m_positif)
		return false;

	for (int i(x.m_taille - 1); i >= 0; i--)
		if (x.m_x[i] != y.m_x[i])
			return false;

	return true;
}

bool operator!=(Int const& x, Int const& y)
{
	return !(x == y);
}

bool operator>(Int const& x, Int const& y)
{
	if (x.m_positif != y.m_positif)
		return x.m_positif;

	if (x.m_taille != y.m_taille)
		return (x.m_positif == (x.m_taille > y.m_taille));

	for (int i(x.m_taille - 1); i >= 0; i--)
		if (x.m_x[i] != y.m_x[i])
			return (x.m_positif == (x.m_x[i] > y.m_x[i]));

	return false;
}

bool operator<(Int const& x, Int const& y)
{
	return !(x >= y);
}

bool operator>=(Int const& x, Int const& y)
{
	if (x.m_positif != y.m_positif)
		return x.m_positif;

	if (x.m_taille != y.m_taille)
		return (x.m_positif == (x.m_taille > y.m_taille));

	for (int i(x.m_taille - 1); i >= 0; i--)
		if (x.m_x[i] != y.m_x[i])
			return (x.m_positif == (x.m_x[i] > y.m_x[i]));

	return true;
}

bool operator<=(Int const& x, Int const& y)
{
	return !(x > y);
}


// Affichage

std::ostream& operator<<(std::ostream& stream, Int const& x)
{
	if (x == 0)
	{
		stream << "0";
		return stream;
	}

	Int p(1), y(x);
	if (x < 0)
	{
		stream << "-";
		y = -x;
	}

	while (p <= y)
		p *= 10;
	p /= 10;
	while (p > 0)
	{
		stream << int((y / p).m_x[0]);
		y %= p;
		p /= 10;
	}

	return stream;
}


// Autres

Int binom(long long int n, long long int p)
{
	if (p > n || p < 0)
		return 0;

	Int num(1), denom(1);

	for (long long int i(0); i < p; i++)
	{
		num *= n-i;
		denom *= p-i;
	}

	return num/denom;
}
