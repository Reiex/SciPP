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
		std::cout << i << "/" << k << std::endl;
		p /= i;
		e += p;
	}


	return e.decimals(n);
}
