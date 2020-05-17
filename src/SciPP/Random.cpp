#include "Random.h"

uint16_t scp::randInt(uint16_t min, uint16_t max)
{
	static uint64_t seed(0), a(1103515245), c(12345);

	if (seed == 0)
		seed = time(nullptr);

	uint64_t m(1);
	seed = (a * seed + c) % (m << 31);

	return min + (seed >> 15) % (max - min);
}

long double scp::randDouble(long double min, long double max)
{
	uint64_t x(randInt());
	x = (x << 16) + randInt();
	x = (x << 16) + randInt();
	x = (x << 16) + randInt();

	return min + ((long double)x/uint64_t(-1))*(max - min);
}

long double scp::normalRand(long double mean, long double sigma)
{
	long double a(randDouble(-1, 1)), b(randDouble(-1, 1)), w(a*a + b*b);
	while (w >= 1)
	{
		a = randDouble(-1, 1);
		b = randDouble(-1, 1);
		w = a*a + b*b;
	}

	return sigma * a * sqrt(-2*log(w)/w) + mean;
}
