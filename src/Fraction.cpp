#include "Fraction.hpp"


std::string decimales(Fraction<Entier> const& x, int n)
{
	std::string chaine("");
	std::stringstream s;
	Fraction<Entier> y(x);

	s << (y.numerateur() / y.denominateur());

	if (n > 0)
		s << ".";
	else
		return s.str();
	
	y -= (y.numerateur() / y.denominateur());
	y *= expoRapide(Fraction<Entier>(10, 1), n);

	s << (y.numerateur() / y.denominateur());

	return s.str();
}

std::ostream& operator<<(std::ostream& stream, Fraction<Entier> const& x)
{
	if (x.denominateur() == 1)
	{
		stream << x.numerateur();
		return stream;
	}
	
	Entier d(x.denominateur());
	while (d % 2 == 0)
		d /= 2;
	while (d % 5 == 0)
		d /= 5;

	if (d == 1)
	{
		Entier r(x.numerateur());

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

