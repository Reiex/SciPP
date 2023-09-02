#include "Misc.hpp"
#include "../stb_image/stb_image_write.h"


namespace
{
	uint64_t index(uint32_t w, uint32_t h, uint32_t x, uint32_t y)
	{
		return 3 * (y * w + x);
	}
}

void plotLogisticMap(const std::string& filename, uint32_t w, uint32_t h, float a, float b, uint32_t n)
{
	std::vector<uint8_t> image(3*w*h, 0);

	for (uint32_t i(0); i < w; i++)
	{
		float x(0.5f);
		float r(a + i*(b-a)/w);
		std::vector<float> column(h, 0);
		for (int j(0); j < n; j++)
		{
			x = r * x * (1.f - x);
			column[h - 1 - int(x * h)] += 1.f / n;
		}

		float max(0.f);
		for (int j(0); j < h; j++)
			max = column[j] > max ? column[j] : max;
		for (int j(0); j < h; j++)
		{
			float t = column[j] / max;
			image[index(w, h, i, j)] = 255 * t;
			image[index(w, h, i, j) + 1] = image[index(w, h, i, j)];
			image[index(w, h, i, j) + 2] = image[index(w, h, i, j)];
		}
	}

	stbi_write_png(filename.c_str(), w, h, 3, image.data(), 3*w);
}

void eratosthenesSieve(uint64_t n)
{
	std::vector<uint64_t> primes;
	primes.push_back(2);
	std::cout << 2 << " ";

	for (uint64_t i(3); i < n; i += 2)
	{
		uint64_t j(0);
		bool primePossible(true);
		while (primes[j]*primes[j] <= i && primePossible)
		{
			primePossible = ((i % primes[j]) != 0);
			j++;
		}

		if (primePossible)
		{
			primes.push_back(i);
			std::cout << i << " ";
		}
	}

	std::cout << std::endl;
}
