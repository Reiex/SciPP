#include "ImageProcessing.hpp"

namespace
{
	uint64_t index(uint32_t w, uint32_t h, uint32_t x, uint32_t y)
	{
		return 3 * (y * w + x);
	}
}

void plotDft(const std::string& src, const std::string& dst)
{
	int w, h;
	uint8_t* image = stbi_load(src.c_str(), &w, &h, nullptr, 3);

	scp::Mat<std::complex<float>> fr(w, h), fg(w, h), fb(w, h);
	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			fr[i][j] = std::complex<float>((float) image[index(w, h, i, j)] / 255.f, 0);
			fg[i][j] = std::complex<float>((float) image[index(w, h, i, j) + 1] / 255.f, 0);
			fb[i][j] = std::complex<float>((float) image[index(w, h, i, j) + 2] / 255.f, 0);
		}
	}

	fr = dft(fr);
	fg = dft(fg);
	fb = dft(fb);
	
	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			image[index(w, h, i, j)] = 255 * std::min(std::abs(fr[i][j]) / 100.f, 1.f);
			image[index(w, h, i, j) + 1] = 255 * std::min(std::abs(fg[i][j]) / 100.f, 1.f);
			image[index(w, h, i, j) + 2] = 255 * std::min(std::abs(fb[i][j]) / 100.f, 1.f);
		}
	}

	stbi_write_png(dst.c_str(), w, h, 3, image, 3 * w);
}
