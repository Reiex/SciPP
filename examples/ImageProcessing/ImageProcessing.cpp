#include "ImageProcessing.hpp"
#include "../stb_image/stb_image.h"
#include "../stb_image/stb_image_write.h"


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

	scp::Matrix<std::complex<float>> fr(w, h), fg(w, h), fb(w, h);
	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			fr[{i, j}] = std::complex<float>((float) image[index(w, h, i, j)] / 255.f, 0);
			fg[{i, j}] = std::complex<float>((float) image[index(w, h, i, j) + 1] / 255.f, 0);
			fb[{i, j}] = std::complex<float>((float) image[index(w, h, i, j) + 2] / 255.f, 0);
		}
	}

	fr.fft();
	fg.fft();
	fb.fft();
	
	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			image[index(w, h, i, j)] = 255 * std::min(std::abs(fr[{i, j}]) / 100.f, 1.f);
			image[index(w, h, i, j) + 1] = 255 * std::min(std::abs(fg[{i, j}]) / 100.f, 1.f);
			image[index(w, h, i, j) + 2] = 255 * std::min(std::abs(fb[{i, j}]) / 100.f, 1.f);
		}
	}

	stbi_write_png(dst.c_str(), w, h, 3, image, 3 * w);
}

void edgesDoG(const std::string& src, const std::string& dst)
{
	// Load image

	int w, h;
	uint8_t* image = stbi_load(src.c_str(), &w, &h, nullptr, 3);

	scp::Matrix<float> f(w, h);
	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			f[{i, j}] = 0.2126f * image[index(w, h, i, j)] / 255.f;
			f[{i, j}] += 0.7152f * image[index(w, h, i, j) + 1] / 255.f;
			f[{i, j}] += 0.0722f * image[index(w, h, i, j) + 2] / 255.f;
		}
	}

	// Apply difference of Gaussian

	float sigma(3.f), deltaSigma(1.f/sigma);
	float s(std::pow(sigma, 2)), ds(std::pow(sigma + deltaSigma, 2));
	scp::Matrix<float> dog(w, h), dogKernel(25, 25);
	for (uint64_t i(0); i < dogKernel.getSize(0); i++)
	{
		for (uint64_t j(0); j < dogKernel.getSize(1); j++)
		{
			float x = ((float) j) - dogKernel.getSize(1)/2;
			float y = ((float) i) - dogKernel.getSize(0)/2;
			dogKernel[{i, j}] = std::exp(-(x*x + y*y)/(2*ds))/ds - std::exp(-(x*x + y*y)/(2*s))/s;
		}
	}

	dog = f;
	dog.convolution<scp::BorderBehaviour::Continuous>(dogKernel);

	// Compute gradient

	float GxValues[9] = {
			-1, 0, 1,
			-2, 0, 2,
			-1, 0, 1
	};
	float GyValues[9] = {
			-1, -2, -1,
			 0,  0,  0,
			 1,  2,  1
	};

	scp::Matrix<float> Gx(w, h), Gy(w, h);
	scp::Matrix<float> GxKernel(3, 3), GyKernel(3, 3);
	std::copy_n(GxValues, 9, GxKernel.getData());
	std::copy_n(GyValues, 9, GyKernel.getData());
	
	Gx = f;
	Gx.convolution<scp::BorderBehaviour::Continuous>(GxKernel);
	Gy = f;
	Gy.convolution<scp::BorderBehaviour::Continuous>(GyKernel);

	// Compute edges

	float dogThreshold(0.02f), gradThreshold(0.1f);
	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			if (std::abs(dog[{i, j}]) < dogThreshold && pow(Gx[{i, j}], 2) + pow(Gy[{i, j}], 2) > gradThreshold)
				f[{i, j}] = 1.f;
			else
				f[{i, j}] = 0.f;
		}
	}

	// Write image

	for (uint64_t i(0); i < w; i++)
	{
		for (uint64_t j(0); j < h; j++)
		{
			image[index(w, h, i, j)] = 255 * f[{i, j}];
			image[index(w, h, i, j) + 1] = 255 * f[{i, j}];
			image[index(w, h, i, j) + 2] = 255 * f[{i, j}];
		}
	}

	stbi_write_png(dst.c_str(), w, h, 3, image, 3 * w);
}
