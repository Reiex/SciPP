#include "Constants.hpp"


scp::Rational<> neper(uint64_t n)
{
	scp::BigInt<> lim = scp::pow(scp::BigInt<>(10), n + 1);
	uint64_t k = 2;
	scp::BigInt<> r = 2;
	scp::Rational<> e = 2;
	
	while (r < lim)
	{
		e += {1, r};
		++k;
		r *= k;
	}

	return e;
}

scp::Rational<> squareRoot(uint64_t x, uint64_t n)
{
	uint64_t y = 1;
	while (y*y < x)
	{
		++y;
	}

	scp::Rational<> result = { 2 * y + 1, 2 };
	scp::BigInt<> lim = scp::pow(scp::BigInt<>(10), n + 1);
	scp::BigInt<> eps = 2;
	while (eps < lim)
	{
		eps *= eps;
		result = (result*result + x) / (2 * result);
	}

	return result;
}
