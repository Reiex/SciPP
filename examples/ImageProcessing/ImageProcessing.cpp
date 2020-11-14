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

void edgesDoG(const std::string& src, const std::string& dst)
{
	int w, h;
	uint8_t* image = stbi_load(src.c_str(), &w, &h, nullptr, 3);

	scp::Mat<float> f(w, h);
	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			f[i][j] = (float) image[index(w, h, i, j)] / 255.f;
			f[i][j] += (float) image[index(w, h, i, j)] / 255.f;
			f[i][j] += (float) image[index(w, h, i, j)] / 255.f;
			f[i][j] /= 3;
		}
	}

	float sigma(5.f), deltaSigma(1.f/sigma);
	float s(std::pow(sigma, 2)), ds(std::pow(sigma + deltaSigma, 2));
	scp::Mat<float> dog(51, 51);
	for (uint64_t i(0); i < 51; i++)
	{
		for (uint64_t j(0); j < 51; j++)
		{
			float x = ((float) j) - 25.f;
			float y = ((float) i) - 25.f;
			dog[i][j] = std::exp(-(x*x + y*y)/(2*ds))/ds - std::exp(-(x*x + y*y)/(2*s))/s;
		}
	}

	f = scp::convolve(f, dog, scp::ConvolveMethod::Continuous);

	float threshold(0.005f);
	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			f[i][j] = threshold / (f[i][j]*f[i][j] + threshold);
		}
	}

	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			image[index(w, h, i, j)] = 255 * f[i][j];
			image[index(w, h, i, j) + 1] = 255 * f[i][j];
			image[index(w, h, i, j) + 2] = 255 * f[i][j];
		}
	}

	stbi_write_png(dst.c_str(), w, h, 3, image, 3 * w);
}
