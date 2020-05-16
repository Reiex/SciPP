#pragma once

#include <cstdint>
#include <time.h>
#include <math.h>

namespace scp
{
	uint16_t randint();
	long double rand();
	long double normalRand(long double mean=0.0, long double sigma=1.0);
}
