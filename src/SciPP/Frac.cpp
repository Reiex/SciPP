#include <SciPP/SciPP.hpp>

namespace scp
{
	// Constructors

	Rational::Rational() : Frac<Int>()
	{
	}

	Rational::Rational(int16_t x) : Rational((int64_t)x)
	{
	}

	Rational::Rational(int32_t x) : Rational((int64_t)x)
	{
	}

	Rational::Rational(int64_t x) : Frac<Int>(x)
	{
	}

	Rational::Rational(const Int& x) : Frac<Int>(x)
	{
	}

	Rational::Rational(const Int& p, const Int& q) : Frac<Int>(p, q)
	{
	}

	Rational::Rational(float x) : Rational((long double) x)
	{
	}

	Rational::Rational(double x) : Rational((long double) x)
	{
	}

	Rational::Rational(long double x)
	{
		if (x == 0)
			*this = (int64_t) 0;

		Int num(0), denom(1), mult(1);
		bool neg(x < 0);

		if (neg)
			x = -x;

		while (x >= 10)
		{
			x /= 10;
			mult *= 10;
		}

		while (x < 1)
		{
			x *= 10;
			denom *= 10;
		}

		for (int i(0); i < 16; i++)
		{
			if (x < 1)
			{
				x *= 10;
				denom *= 10;
			}

			num = 10 * num + int(x - int(x / 10) * 10);
			x = x - int(x - int(x / 10) * 10);
		}

		*this = Rational((1 - 2 * neg) * num * mult, denom);
	}

	Rational::Rational(Frac<Int> const& x) : Frac<Int>(x.num(), x.denom())
	{
	}


	// Specific methods

	std::string Rational::decimals(uint64_t n) const
	{
		std::stringstream s;
		Frac<Int> y(num(), denom());

		if (num() < 0)
		{
			s << "-";
			y = -y;
		}

		s << (y.num() / y.denom());

		if (n > 0)
			s << ".";
		else
			return s.str();

		y -= (y.num() / y.denom());
		y *= expoSq(Frac<Int>(10, 1), n);

		std::stringstream d;
		d << (y.num() / y.denom());
		s << std::string(n - d.str().size(), '0') << d.str();

		return s.str();
	}


	// Display

	std::ostream& operator<<(std::ostream& stream, const Rational& x)
	{
		if (x.denom() == 1)
		{
			stream << x.num();
			return stream;
		}

		Int d(x.denom());
		while (d % 2 == 0)
			d /= 2;
		while (d % 5 == 0)
			d /= 5;

		if (d == 1)
		{
			Int r(x.num());

			if (r < 0 && x.denom() > -r)
			{
				r = -r;
				stream << "-";
			}

			stream << r / x.denom() << ".";
			r %= x.denom();
			r *= 10;

			while (r != 0)
			{
				stream << r / x.denom();
				r %= x.denom();
				r *= 10;
			}

			return stream;
		}

		stream << x.num() << " " << x.denom();
		return stream;
	}
}
