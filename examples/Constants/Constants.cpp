#include "Constants.hpp"


std::string neper(uint64_t n)
{
	uint64_t k(1);
	scp::Rational a(10), b(1);
	a = scp::expoSq(a, n + 1) * scp::Rational(2, 5);
	while (b < a)
	{
		k += 1;
		b *= k;
	}

	scp::Rational e((int64_t) 1), p((int64_t) 1);
	for (uint64_t i(1); i < k; i++)
	{
		p /= i;
		e += p;
	}


	return e.decimals(n);
}

std::string goldenRatio(uint64_t n)
{
	scp::Rational a(1), b(2), m;
	scp::Rational eps = scp::expoSq(scp::Rational(1, 10), n+1);

	while (b - a > eps)
	{
		m = (a + b) / scp::Rational(2);
		if (m * m > m + scp::Rational(1))
			b = m;
		else
			a = m;
	}

	return a.decimals(n);
}
