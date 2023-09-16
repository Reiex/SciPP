///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Pélégrin Marius
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FluidSimulation.hpp"
#include "SimAnim.hpp"


namespace 
{
	double wInit(double x, double y, double delta, double rho)
	{
		double w = 2 * std::numbers::pi * delta * cos(2 * std::numbers::pi * x);
		if (y <= 0.5)
		{
			w -= rho / (std::cosh(rho * (y - 0.25)) * std::cosh(rho * (y - 0.25)));
		}
		else
		{
			w += rho / (std::cosh(rho * (0.75 - y)) * std::cosh(rho * (0.75 - y)));
		}

		return w;
	}

	double curl2D(scp::Matrix<double>& W, const scp::Matrix<double>& Ux, const scp::Matrix<double>& Uy, double kappa, double dx, double dy, double dt)
	{
		const uint64_t Nx(W.getSize(1)), Ny(W.getSize(0));
		uint64_t i;

		static double dtUsed = 0.0;
		static scp::Matrix<double> Kx(Nx, Nx, 0.0), Ky(Ny, Ny, 0.0);

		bool dtChanged = false;
		if (dt > dtUsed * 1.2)
		{
			if (dtUsed == 0.0)
				dtUsed = dt;
			else
				dtUsed *= 1.2;
			dtChanged = true;
		}
		else while (dt < dtUsed)
		{
			dtUsed /= 1.2;
			dtChanged = true;
		}

		if (dtChanged)
		{
			for (i = 0; i < Nx; i++)
			{
				Kx[{i, i}] = 1 + (2 * kappa * dtUsed) / (dx * dx);
				Kx[{(i + 1) % Nx, i}] = -(kappa * dtUsed) / (dx * dx);
				Kx[{i, (i + 1) % Nx}] = -(kappa * dtUsed) / (dx * dx);
			}
			Kx.inverse();

			for (i = 0; i < Ny; i++)
			{
				Ky[{i, i}] = 1 + (2 * kappa * dtUsed) / (dy * dy);
				Ky[{(i + 1) % Ny, i}] = -(kappa * dtUsed) / (dy * dy);
				Ky[{i, (i + 1) % Ny}] = -(kappa * dtUsed) / (dy * dy);
			}
			Ky.inverse();
		}

		double c;

		{
			scp::Vector<double> WCopy(Nx), WCopyCopy(Nx);
			for (i = 0; i < Ny; i++)
			{
				for (uint64_t k = 0; k < Nx; ++k)
				{
					c = Ux[{i, k}] * dtUsed / dx;
					WCopy[k] = (1.0 - c * c) * W[{i, k}] + (c / 2) * (c - 1) * W[{ i, (k + 1) % Nx }];
					c = Ux[{ i, (Nx + k - 1) % Nx }] * dtUsed / dx;
					WCopy[k] += (c / 2) * (1 + c) * W[{i, (Nx + k - 1) % Nx}];
				}

				WCopy = Kx * WCopy;
				for (uint64_t k = 0; k < Nx; ++k)
				{
					W[{i, k}] = WCopy[k];
				}
			}
		}

		{
			scp::Vector<double> WCopy(Ny), WCopyCopy(Ny);
			for (i = 0; i < Nx; i++)
			{
				for (uint64_t k = 0; k < Ny; ++k)
				{
					c = Uy[{k, i}] * dtUsed / dy;
					WCopy[k] = (1.0 - c * c) * W[{k, i}] + (c / 2) * (c - 1) * W[{(k + 1) % Ny, i}];
					c = Uy[{(Ny + k - 1) % Ny, i}] * dtUsed / dy;
					WCopy[k] += (c / 2) * (1 + c) * W[{(Ny + k - 1) % Ny, i}];
				}

				WCopy = Ky * WCopy;
				for (uint64_t k = 0; k < Ny; ++k)
				{
					W[{k, i}] = WCopy[k];
				}
			}
		}

		return dtUsed;
	}

	void velocityFromCurl(const scp::Matrix<double>& W, scp::Matrix<double>& Ux, scp::Matrix<double>& Uy, double Lx, double Ly)
	{
		const uint64_t Nx = W.getSize(1);
		const uint64_t Ny = W.getSize(0);
		const uint64_t N = Nx * Ny;

		scp::Matrix<std::complex<double>> WHat(Ny, Nx);
		std::copy(W.cbegin(), W.cend(), WHat.begin());
		WHat.fft();

		scp::Vector<std::complex<double>> kx(Nx), ky(Ny);
		for (uint64_t i = 0; i < Nx; ++i)
		{
			if (i < (Nx + 1) / 2)
			{
				kx[i] = std::complex<double>(0, 2 * std::numbers::pi * i / Lx);
			}
			else
			{
				kx[i] = std::complex<double>(0, 2 * std::numbers::pi * (Nx - i) / Lx);
			}
		}

		for (uint64_t i = 0; i < Ny; ++i)
		{
			if (i < (Ny + 1) / 2)
			{
				ky[i] = std::complex<double>(0, 2 * std::numbers::pi * i / Ly);
			}
			else
			{
				ky[i] = std::complex<double>(0, 2 * std::numbers::pi * (Ny - i) / Ly);
			}
		}

		scp::Matrix<std::complex<double>> UxHat(Ny, Nx), UyHat(Ny, Nx);

		for (uint64_t i(0); i < Ny; i++)
		{
			for (uint64_t j(0); j < Nx; j++)
			{
				if (i == 0 && j == 0)
				{
					UxHat[{i, j}] = 0;
					UyHat[{i, j}] = 0;
				}
				else
				{
					UxHat[{i, j}] = -WHat[{i, j}] * ky[i] / (kx[j] * kx[j] + ky[i] * ky[i]);
					UyHat[{i, j}] = WHat[{i, j}] * kx[j] / (kx[j] * kx[j] + ky[i] * ky[i]);
				}
			}
		}

		UxHat.ifft();
		UyHat.ifft();

		for (uint64_t i = 0; i < Ny; ++i)
		{
			for (uint64_t j = 0; j < Nx; ++j)
			{
				Ux[{i, j}] = UxHat[{i, j}].imag();
				Uy[{i, j}] = UyHat[{i, j}].imag();
			}
		}
	}
}

void simuFluide2D(const std::string& name, uint64_t Nx, uint64_t Ny, double tSimu, double nu, double rho, double delta, double Lx, double Ly)
{
	double dx = Lx / Nx;
	double dy = Ly / Ny;
	double kappa = nu / rho;
	scp::Matrix<double> Ux(Ny, Nx, 0.0);
	scp::Matrix<double> Uy(Ny, Nx, 0.0);
	scp::Matrix<double> W(Ny, Nx);

	for (uint64_t i = 0, n = 0; i < Ny; ++i)
	{
		for (uint64_t j = 0; j < Nx; ++j, ++n)
		{
			W[n] = wInit((j + 0.5) / Nx, (i + 0.5) / Ny, delta, rho);
		}
	}

	double t(0), dtx, dty, dt;
	uint64_t iterations = 0;

	simanim::createAnimation(name, Nx, Ny);
	std::thread saveThread(simanim::saveAnimationFrame, fs::path(name), t, std::ref(W));
	while (t < tSimu)
	{
		iterations++;
		std::cout << "> Iteration " << iterations << " a t=" << t << std::endl;

		velocityFromCurl(W, Ux, Uy, Lx, Ly);

		dtx = dx / std::abs(*std::max_element(Ux.begin(), Ux.end(), [](double x, double y) { return std::abs(x) < std::abs(y); }));
		dty = dy / std::abs(*std::max_element(Uy.begin(), Uy.end(), [](double x, double y) { return std::abs(x) < std::abs(y); }));
		dt = std::min(dtx, dty);

		saveThread.join();
		dt = curl2D(W, Ux, Uy, kappa, dx, dy, dt);
		saveThread = std::thread(simanim::saveAnimationFrame, fs::path(name), t, std::ref(W));

		t += dt;
	}

	saveThread.join();
}
