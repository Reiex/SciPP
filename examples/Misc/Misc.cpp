#include "Misc.hpp"

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
