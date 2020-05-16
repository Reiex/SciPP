#include "Random.h"

uint16_t scp::randint()
{
	static uint64_t seed(0), a(1103515245), c(12345);

	if (seed == 0)
		seed = time(nullptr);

	uint64_t m(1);
	seed = (a * seed + c) % (m << 31);

	return seed >> 15;
}

long double scp::rand()
{
	uint64_t x(randint());
	x = (x << 16) + randint();
	x = (x << 16) + randint();
	x = (x << 16) + randint();

	return ((long double) x)/uint64_t(-1);
}

long double scp::normalRand(long double mean, long double sigma)
{
	long double a(rand()*2 - 1), b(rand()*2 - 1), w(a*a + b*b);
	while (w >= 1)
	{
		a = rand()*2 - 1;
		b = rand()*2 - 1;
		w = a*a + b*b;
	}

	return sigma * a * sqrt(-2*log(w)/w) + mean;
}
