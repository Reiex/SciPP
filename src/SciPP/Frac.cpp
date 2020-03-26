#include "Frac.hpp"


Rationnel::Rationnel() : Frac<Int>()
{
}

Rationnel::Rationnel(int x) : Frac<Int>(x)
{
}

Rationnel::Rationnel(Int const& x) : Frac<Int>(x)
{
}

Rationnel::Rationnel(Int const& p, Int const& q) : Frac<Int>(p, q)
{
}

Rationnel::Rationnel(double x)
{
	if (x == 0)
		*this = 0;

	Int num(0), denom(1);
	bool neg(x < 0);

	if (neg)
		x = -x;

	while (x < 1)
	{
		x *= 10;
		denom *= 10;
	}

	for (int i(0); i < 20; i++)
	{
		if (x < 1)
		{
			x *= 10;
			denom *= 10;
		}

		num = 10*num + int(x - int(x/10)*10);
		x = x - int(x - int(x/10)*10);
	}

	*this = Rationnel(num, denom);
}

Rationnel::Rationnel(Frac<Int> const& x) : Frac<Int>(x.numerateur(), x.denominateur())
{
}

std::string decimales(Rationnel const& x, int n)
{
	std::string chaine("");
	std::stringstream s;
	Frac<Int> y(x);

	s << (y.numerateur() / y.denominateur());

	if (n > 0)
		s << ".";
	else
		return s.str();
	
	y -= (y.numerateur() / y.denominateur());
	y *= expoRapide(Frac<Int>(10, 1), n);

	s << (y.numerateur() / y.denominateur());

	return s.str();
}

std::ostream& operator<<(std::ostream& stream, Rationnel const& x)
{
	if (x.denominateur() == 1)
	{
		stream << x.numerateur();
		return stream;
	}
	
	Int d(x.denominateur());
	while (d % 2 == 0)
		d /= 2;
	while (d % 5 == 0)
		d /= 5;

	if (d == 1)
	{
		Int r(x.numerateur());

		stream << r / x.denominateur() << ".";
		r %= x.denominateur();
		r *= 10;

		while (r != 0)
		{
			stream << r / x.denominateur();
			r %= x.denominateur();
			r *= 10;
		}
		
		return stream;
	}

	stream << x.numerateur() << "/" << x.denominateur();
	return stream;
}
