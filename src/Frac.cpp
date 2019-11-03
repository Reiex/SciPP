#include "Frac.hpp"


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

