#include "Matrice.hpp"

namespace scp
{
	Vect<std::complex<long double>> FFT(Vect<std::complex<long double>> const& v)
	{
		unsigned int n(v.size());
		Vect<std::complex<long double>> u(n);

		for (unsigned int k(0); k < n; k++)
			for (unsigned int i(0); i < n; i++)
				u[k] += v[i] * exp(std::complex<long double>(0, -2 * PI * k * i / n));

		return u;
	}

	Vect<std::complex<long double>> IFFT(Vect<std::complex<long double>> const& v)
	{
		unsigned int n(v.size());
		Vect<std::complex<long double>> u(v);

		for (unsigned int i(0); i < n; i++)
			u[i] = std::complex<long double>(u[i].real(), -u[i].imag());

		u = FFT(u);

		for (unsigned int i(0); i < n; i++)
			u[i] = std::complex<long double>(u[i].real(), -u[i].imag());

		return u / std::complex<long double>(n);
	}

	Matrice<std::complex<long double>> FFT(Matrice<std::complex<long double>> const& M)
	{
		unsigned int m(M.size()[0]), n(M.size()[1]);
		Matrice<std::complex<long double>> wM(m, m), wN(n, n);

		for (unsigned int i(0); i < m; i++)
			for (unsigned int j(0); j < m; j++)
				wM[i][j] = exp(std::complex<long double>(0, -2 * PI * i * j / m));

		for (unsigned int i(0); i < n; i++)
			for (unsigned int j(0); j < n; j++)
				wN[i][j] = exp(std::complex<long double>(0, -2 * PI * i * j / n));

		return wM * M * wN;
	}

	Matrice<std::complex<long double>> IFFT(Matrice<std::complex<long double>> const& M)
	{
		unsigned int m(M.size()[0]), n(M.size()[1]);
		Matrice<std::complex<long double>> N(M);

		for (unsigned int i(0); i < n; i++)
			for (unsigned int j(0); j < n; j++)
				N[i][j] = std::complex<long double>(N[i][j].real(), -N[i][j].imag());

		N = FFT(N);

		for (unsigned int i(0); i < n; i++)
			for (unsigned int j(0); j < n; j++)
				N[i][j] = std::complex<long double>(N[i][j].real(), -N[i][j].imag());

		return N / std::complex<long double>(m * n, 0);
	}

	static long double g(unsigned int N, unsigned int k, unsigned int i)
	{
		if (k == 0)
			return cos(PI * (i + 0.5) * k / N) / sqrt(N);
		else
			return sqrt(2.0 / N) * cos(PI * (i + 0.5) * k / N);
	}

	Vect<long double> DCT(Vect<long double> const& v)
	{
		unsigned int n(v.size());
		Vect<long double> u(n);

		for (unsigned int k(0); k < n; k++)
			for (unsigned int i(0); i < n; i++)
				u[k] += v[i] * g(n, k, i);

		return u;
	}

	Vect<long double> IDCT(Vect<long double> const& v)
	{
		unsigned int n(v.size());
		Vect<long double> u(n);


		for (unsigned int k(0); k < n; k++)
			for (unsigned int i(0); i < n; i++)
				u[k] += v[i] * g(n, i, k);

		return u;
	}

	static long double G(unsigned int N, unsigned int p, unsigned int q, unsigned int n, unsigned int m)
	{
		long double r(2 * cos(PI * p * (n + 0.5) / N) * cos(PI * q * (m + 0.5) / N) / N);

		if (p == 0)
			r /= sqrt(2);

		if (q == 0)
			r /= sqrt(2);

		return r;
	}

	Matrice<long double> DCT(Matrice<long double> const& M)
	{
		unsigned int n(M.size()[0]);
		Matrice<long double> N(n, n);

		for (unsigned int i(0); i < n; i++)
			for (unsigned int j(0); j < n; j++)
				for (unsigned int k(0); k < n; k++)
					for (unsigned int l(0); l < n; l++)
						N[i][j] += M[k][l] * G(n, i, j, k, l);

		return N;
	}

	Matrice<long double> IDCT(Matrice<long double> const& M)
	{
		unsigned int n(M.size()[0]);
		Matrice<long double> N(n, n);

		for (unsigned int i(0); i < n; i++)
			for (unsigned int j(0); j < n; j++)
				for (unsigned int k(0); k < n; k++)
					for (unsigned int l(0); l < n; l++)
						N[i][j] += M[k][l] * G(n, k, l, i, j);

		return N;
	}

	Matrice<long double> poissonSolveur(Matrice<long double> const& f, long double Lx, long double Ly)
	{
		// Conversion de f en matrice complexe

		int Nx(f.size()[1]), Ny(f.size()[0]);
		Matrice<std::complex<long double>> fHat(Ny, Nx);

		for (int i(0); i < Ny; i++)
			for (int j(0); j < Nx; j++)
				fHat[i][j] = f[i][j];

		// Calcul de la transformée de Fourier

		fHat = FFT(fHat);

		// Calcul des nombres d'ondes

		Vect<std::complex<long double>> kx(Nx), ky(Ny);
		for (int i(0); i < Nx; i++)
			if (i < (Nx + 1) / 2)
				kx[i] = std::complex<long double>(0, 2 * PI * i / Lx);
			else
				kx[i] = std::complex<long double>(0, 2 * PI * (Nx - i) / Lx);

		for (int i(0); i < Ny; i++)
			if (i < (Ny + 1) / 2)
				ky[i] = std::complex<long double>(0, 2 * PI * i / Ly);
			else
				ky[i] = std::complex<long double>(0, 2 * PI * (Ny - i) / Ly);

		// Calcul de la transformée de fourier du résultat

		for (int i(0); i < Ny; i++)
			for (int j(0); j < Nx; j++)
				if (i == 0 && j == 0)
					fHat[i][j] = 0;
				else
					fHat[i][j] /= (kx[j] * kx[j] + ky[i] * ky[i]);

		// Calcul de la matrice complexe du résultat par transformée inverse

		Matrice<std::complex<long double>> psiBar(IFFT(fHat));

		// Calcul du r�sultat

		Matrice<long double> psi(Ny, Nx);
		for (int i(0); i < Ny; i++)
			for (int j(0); j < Nx; j++)
				psi[i][j] = psiBar[i][j].real();

		return psi;
	}

	Vect<long double> cholesky(Matrice<long double> const& A, Vect<long double> const& B)
	{
		if (A.size()[0] != A.size()[1])
			throw "La matrice doit etre carree.";

		if (A.size()[0] != B.size())
			throw "Le vecteur doit etre de la meme taille que la matrice.";

		int n(B.size());

		Vect<long double> X(n);
		Matrice<long double> L(n, n);

		for (int j(0); j < n; j++)
		{
			L[j][j] = A[j][j];
			for (int k(0); k < j; k++)
				L[j][j] -= L[j][k];
			L[j][j] = sqrt(L[j][j]);

			for (int i(j + 1); i < n; i++)
			{
				L[i][j] = A[i][j];
				for (int k(0); k < j - 1; k++)
					L[i][j] -= L[i][k] * L[j][k];

				L[i][j] /= L[j][j];
			}
		}

		for (int i(0); i < n; i++)
		{
			X[i] = B[i];
			for (int k(0); k < i - 1; k++)
				X[i] -= L[i][k] * X[k];
			X[i] /= L[i][i];
		}

		for (int i(n - 1); i >= 0; i--)
		{
			for (int k(n - 1); k > i; k--)
				X[i] -= L[k][i] * X[k];
			X[i] /= L[i][i];
		}

		return X;
	}
}
