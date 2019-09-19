#include "SciPP.h"


// Fonctions spécifiques

std::string decimales(Fraction<Entier> const& x, int n)
{
	std::string chaine("");
	std::stringstream s;
	Fraction<Entier> y(x);

	s << (y.numerateur() / y.denominateur());

	if (n > 0)
		s << ".";
	else
		return s.str();
	
	y -= (y.numerateur() / y.denominateur());
	y *= expoRapide(Fraction<Entier>(10, 1), n);

	s << (y.numerateur() / y.denominateur());

	return s.str();
}

std::ostream& operator<<(std::ostream& stream, Fraction<Entier> const& x)
{
	if (x.denominateur() == 1)
	{
		stream << x.numerateur();
		return stream;
	}
	
	Entier d(x.denominateur());
	while (d % 2 == 0)
		d /= 2;
	while (d % 5 == 0)
		d /= 5;

	if (d == 1)
	{
		Entier r(x.numerateur());

		stream << r / x.denominateur() << ".";
		r %= x.denominateur();
		r *= 10;

		while (r != 0)
		{
			stream << r / x.denominateur();
			r %= x.denominateur();
			r *= 10;
		}
		
		return stream;
	}

	stream << x.numerateur() << "/" << x.denominateur();
	return stream;
}

Vecteur<std::complex<long double>> DFT(Vecteur<std::complex<long double>> const& v)
{
	int n(v.taille());
	Vecteur<std::complex<long double>> u(n);

	for (int k(0); k < n; k++)
		for (int i(0); i < n; i++)
			u[k] += v[i] * exp(std::complex<long double>(0, -2*PI*k*i/n));

	return u;
}

Vecteur<std::complex<long double>> IDFT(Vecteur<std::complex<long double>> const& v)
{
	int n(v.taille());
	Vecteur<std::complex<long double>> u(n);

	for (int k(0); k < n; k++)
		for (int i(0); i < n; i++)
			u[k] += v[i] * exp(std::complex<long double>(0, 2*PI*k*i / n));

	return u/std::complex<long double>(n);
}

Matrice<std::complex<long double>> DFT2D(Matrice<std::complex<long double>> const& M)
{
	int m(M.taille()[0]), n(M.taille()[1]);
	Matrice<std::complex<long double>> wM(m, m), wN(n, n);

	for (int i(0); i < m; i++)
		for (int j(0); j < m; j++)
			wM[i][j] = exp(std::complex<long double>(0, -2*PI*i*j/m));

	for (int i(0); i < n; i++)
		for (int j(0); j < n; j++)
			wN[i][j] = exp(std::complex<long double>(0, -2*PI*i*j/n));

	return wM * M * wN;
}

Matrice<std::complex<long double>> IDFT2D(Matrice<std::complex<long double>> const& M)
{
	int m(M.taille()[0]), n(M.taille()[1]);
	Matrice<std::complex<long double>> wM(m, m), wN(n, n);

	for (int i(0); i < m; i++)
		for (int j(0); j < m; j++)
			wM[i][j] = exp(std::complex<long double>(0, 2*PI*i*j/m));

	for (int i(0); i < n; i++)
		for (int j(0); j < n; j++)
			wN[i][j] = exp(std::complex<long double>(0, 2*PI*i*j/n));

	return wM * M * wN / std::complex<long double>(m*n, 0);
}

Matrice<long double> poissonSolveur(Matrice<long double> const& f, long double Lx, long double Ly)
{
	// Conversion de f en matrice complexe

	int Nx(f.taille()[1]), Ny(f.taille()[0]);
	Matrice<std::complex<long double>> fHat(Ny, Nx);

	for (int i(0); i < Ny; i++)
		for (int j(0); j < Nx; j++)
			fHat[i][j] = f[i][j];

	// Calcul de la transformée de Fourier

	fHat = DFT2D(fHat);

	// Calcul des nombres d'ondes

	Vecteur<std::complex<long double>> kx(Nx), ky(Ny);
	for (int i(0); i < Nx; i++)
		if (i < (Nx + 1) / 2)
			kx[i] = std::complex<long double>(0, 2*PI*i/Lx);
		else
			kx[i] = std::complex<long double>(0, 2*PI*(Nx - i)/Lx);

	for (int i(0); i < Ny; i++)
		if (i < (Ny + 1) / 2)
			ky[i] = std::complex<long double>(0, 2*PI*i/Ly);
		else
			ky[i] = std::complex<long double>(0, 2*PI*(Ny - i)/Ly);

	// Calcul de la transformée de fourier du résultat

	for (int i(0); i < Ny; i++)
		for (int j(0); j < Nx; j++)
			if (i == 0 && j == 0)
				fHat[i][j] = 0;
			else
				fHat[i][j] /= (kx[j] * kx[j] + ky[i] * ky[i]);

	// Calcul de la matrice complexe du résultat par transformée inverse

	Matrice<std::complex<long double>> psiBar(IDFT2D(fHat));

	// Calcul du résultat

	Matrice<long double> psi(Ny, Nx);
	for (int i(0); i < Ny; i++)
		for (int j(0); j < Nx; j++)
			psi[i][j] = psiBar[i][j].real();

	return psi;
}

Matrice<long double> cholesky(Matrice<long double> const& A)
{
	if (A.taille()[0] != A.taille()[1])
		throw "La matrice doit etre carree.";

	Matrice<long double> B(A.taille()[0], A.taille()[1]);

	int n(A.taille()[0]);
	for (int i(0); i < n; i++)
	{
		B[i][i] = A[i][i];

		for (int k(0); k < i; k++)
			B[i][i] -= B[i][k] * B[i][k];

		B[i][i] = sqrt(B[i][i]);

		for (int j(i + 1); j < n; j++)
		{
			B[j][i] = A[i][j];

			for (int k(0); k < i; k++)
				B[j][i] -= B[i][k] * B[j][k];

			B[j][i] /= B[i][i];
		}
	}

	return B;
}
