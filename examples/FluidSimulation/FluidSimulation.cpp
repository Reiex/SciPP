#include "FluidSimulation.hpp"

namespace
{
	void curlSolver1D(scp::Vec<double>& W, const scp::Vec<double>& U, double kappa, double dl, double dt)
	{
		scp::Mat<double> M(U.n, U.n), N(U.n, U.n);

		double c;
		for (uint64_t k(0); k < U.n; k++)
		{
			c = U[k];
			M[k][k] = 1 - (c * dt / dl) * (c * dt / dl);
			M[(k + 1) % U.n][k] = ((c * dt) / (2 * dl)) * (1 + c * (dt / dl));
			M[k][(k + 1) % U.n] = ((c * dt) / (2 * dl)) * (c * (dt / dl) - 1);

			N[k][k] = 1 + (2 * kappa * dt) / (dl * dl);
			N[(k + 1) % U.n][k] = -(kappa * dt) / (dl * dl);
			N[k][(k + 1) % U.n] = -(kappa * dt) / (dl * dl);
		}

		W = scp::inverse(N) * (M * W);
	}

	void curlSolver2D(scp::Mat<double>& W, const scp::Mat<double>& Ux, const scp::Mat<double>& Uy, double kappa, double dx, double dy, double dt)
	{
		uint64_t Nx(W.n), Ny(W.m);
		int i;

		#pragma omp parallel for
		for (i = 0; i < Ny; i++)
			curlSolver1D(W[i], Ux[i], kappa, dx, dt);

		scp::Mat<double> Wt(scp::transpose(W));
		scp::Mat<double> Uyt(scp::transpose(Uy));
		
		#pragma omp parallel for
		for (i = 0; i < Ny; i++)
			curlSolver1D(Wt[i], Uyt[i], kappa, dy, dt);

		W = scp::transpose(Wt);
	}

	double wInit(double x, double y, double delta, double rho)
	{
		double w(2 * scp::pi * delta * cos(2 * scp::pi * x));
		if (y <= 0.5)
			w -= rho / (std::cosh(rho * (y - 0.25)) * std::cosh(rho * (y - 0.25)));
		else
			w += rho / (std::cosh(rho * (0.75 - y)) * std::cosh(rho * (0.75 - y)));

		return w;
	}

	void poissonCurlSolver(const scp::Mat<double>& W, scp::Mat<double>& Ux, scp::Mat<double>& Uy, double Lx, double Ly)
	{
		uint64_t Nx(W.n), Ny(W.m);
		scp::Mat<std::complex<double>> WHat(Ny, Nx);

		for (uint64_t i(0); i < Ny; i++)
			for (uint64_t j(0); j < Nx; j++)
				WHat[i][j] = W[i][j];

		WHat = scp::dft(WHat);

		scp::Vec<std::complex<double>> kx(Nx), ky(Ny);
		for (uint64_t i(0); i < Nx; i++)
			if (i < (Nx + 1) / 2)
				kx[i] = std::complex<double>(0, 2 * scp::pi * i / Lx);
			else
				kx[i] = std::complex<double>(0, 2 * scp::pi * (Nx - i) / Lx);

		for (uint64_t i(0); i < Ny; i++)
			if (i < (Ny + 1) / 2)
				ky[i] = std::complex<double>(0, 2 * scp::pi * i / Ly);
			else
				ky[i] = std::complex<double>(0, 2 * scp::pi * (Ny - i) / Ly);

		scp::Mat<std::complex<double>> UxHat(Ny, Nx), UyHat(Ny, Nx);

		for (uint64_t i(0); i < Ny; i++)
		{
			for (uint64_t j(0); j < Nx; j++)
			{
				if (i == 0 && j == 0)
				{
					UxHat[i][j] = 0;
					UyHat[i][j] = 0;
				}
				else
				{
					UxHat[i][j] = -WHat[i][j] * ky[i] / (kx[j] * kx[j] + ky[i] * ky[i]);
					UyHat[i][j] = WHat[i][j] * kx[j] / (kx[j] * kx[j] + ky[i] * ky[i]);
				}
			}
		}


		scp::Mat<std::complex<double>> UxBar(scp::idft(UxHat));
		scp::Mat<std::complex<double>> UyBar(scp::idft(UyHat));

		for (uint64_t i(0); i < Ny; i++)
		{
			for (uint64_t j(0); j < Nx; j++)
			{
				Ux[i][j] = UxBar[i][j].imag();
				Uy[i][j] = UyBar[i][j].imag();
			}
		}
	}

	double computeDt(const scp::Mat<double>& U, double dl)
	{
		double Umax(0);
		for (uint64_t i(0); i < U.m; i++)
			for (uint64_t j(0); j < U.n; j++)
				if ((U[i][j] > 0 ? U[i][j] : -U[i][j]) > Umax)
					Umax = (U[i][j] > 0 ? U[i][j] : -U[i][j]);
		return dl / Umax;
	}
}


void simuFluide2D(const std::string& name, uint64_t Nx, uint64_t Ny, double t_simu, double nu, double rho, double delta, double Lx, double Ly)
{
	double kappa(nu / rho), dx(Lx / Nx), dy(Ly / Ny);
	scp::Mat<double> Ux(Ny, Nx), Uy(Ny, Nx), W(Ny, Nx);

	for (double i(0); i < Ny; i++)
		for (double j(0); j < Nx; j++)
			W[i][j] = wInit(j / Nx, i / Ny, delta, rho);

	double t(0), dtx, dty, dt;
	uint64_t iterations(0);

	simanim::createAnimation(name);
	std::thread saveThread(simanim::saveAnimationFrame, fs::path(name), t, std::ref(W));
	while (t < t_simu)
	{
		iterations++;
		std::cout << "> Iteration " << iterations << " a t=" << t << std::endl;

		poissonCurlSolver(W, Ux, Uy, Lx, Ly);

		dtx = computeDt(Ux, dx);
		dty = computeDt(Uy, dy);
		dt = std::min(dtx, dty);

		saveThread.join();
		curlSolver2D(W, Ux, Uy, kappa, dx, dy, dt);
		saveThread = std::thread(simanim::saveAnimationFrame, fs::path(name), t, std::ref(W));

		t += dt;
	}

	saveThread.join();
}