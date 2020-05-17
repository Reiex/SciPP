#pragma once

#include <cstdint>
#include <time.h>
#include <math.h>

namespace scp
{
	uint16_t randInt(uint16_t min=0, uint16_t max=-1);
	long double randDouble(long double min=0.0, long double max=1.0);
	long double normalRand(long double mean=0.0, long double sigma=1.0);
}
