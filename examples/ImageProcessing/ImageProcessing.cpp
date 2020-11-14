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
	// Load image

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

	// Apply difference of Gaussian

	float sigma(5.f), deltaSigma(1.f/sigma);
	float s(std::pow(sigma, 2)), ds(std::pow(sigma + deltaSigma, 2));
	scp::Mat<float> dog(w, h), dogKernel(51, 51);
	for (uint64_t i(0); dogKernel.m < 51; i++)
	{
		for (uint64_t j(0); j < dogKernel.n; j++)
		{
			float x = ((float) j) - 25.f;
			float y = ((float) i) - 25.f;
			dogKernel[i][j] = std::exp(-(x*x + y*y)/(2*ds))/ds - std::exp(-(x*x + y*y)/(2*s))/s;
		}
	}

	dog = scp::convolve(f, dogKernel, scp::ConvolveMethod::Continuous);

	// Compute gradient

	scp::Mat<float> Gx(w, h), Gy(w, h);
	scp::Mat<float> GxKernel({
			{-1, 0, 1},
			{-2, 0, 2},
			{-1, 0, 1}
		});
	scp::Mat<float> GyKernel({
			{-1, -2, -1},
			{ 0,  0,  0},
			{ 1,  2,  1}
		});
	
	Gx = scp::convolve(f, GxKernel, scp::ConvolveMethod::Continuous);
	Gy = scp::convolve(f, GyKernel, scp::ConvolveMethod::Continuous);

	// Compute edges

	float dogThreshold(0.005f), gradThreshold(0.1f);
	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			if (std::abs(dog[i][j]) < 0.005 && (pow(Gx[i][j], 2) + pow(Gy[i][j], 2)) > gradThreshold)
				f[i][j] = 1.f;
			else
				f[i][j] = 0.f;
		}
	}

	// Write image

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
