#include "simuPhysique.h"


// Simulations de fluides

// 1 Dimension

long double vitesseConv(long double x)
{
	return 0.4*(x-0.25);
}

long double phiInit(long double x)
{
	if (x < 0.25)
		return 0;
	else if (x < 0.375)
		return 2 * (x - 0.25);
	else if (x < 0.5)
		return 2 * (0.5 - x);
	else
		return 0;
}

void simuDispersionVorticite(int Nx, int Nt, long double kappa, long double t_simu)
{
	long double dx((long double)(1) / Nx), dt(t_simu / Nt);

	Matrice<long double> M(Nx, Nx), N(Nx, Nx), Phi(Nx, 1), Phi0(Nx, 1);
	
	long double c;
	for (int k(0); k < Nx; k++)
	{
		c = vitesseConv((k - 1)*dx);
		M[k][k] = 1 - (c*dt / dx)*(c*dt / dx);
		M[(k + 1) % Nx][k] = ((c*dt) / (2 * dx))*(1 + c * (dt / dx));
		M[k][(k + 1) % Nx] = ((c*dt) / (2 * dx))*(c*(dt / dx) - 1);

		N[k][k] = 1 + (2*kappa*dt) / (dx*dx);
		N[(k + 1) % Nx][k] = -(kappa*dt) / (dx*dx);
		N[k][(k + 1) % Nx] = -(kappa*dt) / (dx*dx);

		Phi[k][0] = phiInit((k - 1)*dx);
		Phi0[k][0] = phiInit((k - 1)*dx);
	}

	Vecteur<long double> x(Nx), y(Nx);
	for (int i(0); i < Nx; i++)
	{
		x[i] = i;
	}

	Matrice<long double> B(N.inv());
	for (int i(0); i < Nt; i++)
	{
		std::cout << 100 * (float(i) / Nt) << "%" << std::endl;
		Phi = B*(M*Phi);
		for (int j(0); j < Nx; j++)
		{
			y[j] = Phi[j][0];
		}
		plot(x, y);
	}

	show(int((long double)(1)/dt), true);
}

// 2 Dimensions

struct MatriceChainee
{
	Matrice<long double> matrice;
	MatriceChainee* suivante;
};

void solveur1D(Vecteur<long double>& W, Vecteur<long double> const& U, long double kappa, long double dl, long double dt)
{
	int Nl(U.taille());
	Matrice<long double> M(Nl, Nl), N(Nl, Nl);

	long double c;
	for (int k(0); k < Nl; k++)
	{
		c = U[k];
		M[k][k] = 1 - (c*dt / dl)*(c*dt / dl);
		M[(k + 1) % Nl][k] = ((c*dt) / (2 * dl))*(1 + c * (dt / dl));
		M[k][(k + 1) % Nl] = ((c*dt) / (2 * dl))*(c*(dt / dl) - 1);

		N[k][k] = 1 + (2 * kappa*dt) / (dl*dl);
		N[(k + 1) % Nl][k] = -(kappa*dt) / (dl*dl);
		N[k][(k + 1) % Nl] = -(kappa*dt) / (dl*dl);
	}

	W = N.inv()*(M*W);
}

void solveur2D(Matrice<long double>& W, Matrice<long double> const& Ux, Matrice<long double> const& Uy, long double kappa, long double dx, long double dy, long double dt)
{
	int Nx(W.taille()[1]), Ny(W.taille()[0]);

	for (int i(0); i < Ny; i++)
		solveur1D(W[i], Ux[i], kappa, dx, dt);

	for (int j(0); j < Nx; j++)
	{
		Vecteur<long double> Wy(Ny), Vy(Ny);
		for (int i(0); i < Ny; i++)
		{
			Wy[i] = W[i][j];
			Vy[i] = Uy[i][j];
		}
		solveur1D(Wy, Vy, kappa, dy, dt);

		for (int i(0); i < Ny; i++)
			W[i][j] = Wy[i];
	}
}

long double wInit(long double x, long double y, long double delta, long double rho)
{
	long double w(2 * PI*delta*cos(2 * PI*x));
	if (y <= 0.5)
		w -= rho/(cosh(rho*(y - 0.25))*cosh(rho*(y - 0.25)));
	else
		w += rho/(cosh(rho*(0.75 - y))*cosh(rho*(0.75 - y)));

	return w;
}

void poissonCurlSolveur(Matrice<long double> const& W, Matrice<long double>& Ux, Matrice<long double>& Uy, long double Lx, long double Ly)
{
	int Nx(W.taille()[1]), Ny(W.taille()[0]);
	Matrice<std::complex<long double>> WHat(Ny, Nx);

	for (int i(0); i < Ny; i++)
		for (int j(0); j < Nx; j++)
			WHat[i][j] = W[i][j];

	WHat = DFT2D(WHat);

	Vecteur<std::complex<long double>> kx(Nx), ky(Ny);
	for (int i(0); i < Nx; i++)
		if (i < (Nx + 1) / 2)
			kx[i] = std::complex<long double>(0, 2 * PI*i / Lx);
		else
			kx[i] = std::complex<long double>(0, 2 * PI*(Nx - i) / Lx);

	for (int i(0); i < Ny; i++)
		if (i < (Ny + 1) / 2)
			ky[i] = std::complex<long double>(0, 2 * PI*i / Ly);
		else
			ky[i] = std::complex<long double>(0, 2 * PI*(Ny - i) / Ly);

	Matrice<std::complex<long double>> UxHat(Ny, Nx), UyHat(Ny, Nx);

	for (int i(0); i < Ny; i++)
	{
		for (int j(0); j < Nx; j++)
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
		

	Matrice<std::complex<long double>> UxBar(IDFT2D(UxHat));
	Matrice<std::complex<long double>> UyBar(IDFT2D(UyHat));

	for (int i(0); i < Ny; i++)
	{
		for (int j(0); j < Nx; j++)
		{
			Ux[i][j] = UxBar[i][j].imag();
			Uy[i][j] = UyBar[i][j].imag();
		}
	}
}

long double calculDt(Matrice<long double> const& U, long double dl)
{
	long double Umax(0);
	for (int i(0); i < U.taille()[0]; i++)
		for (int j(0); j < U.taille()[1]; j++)
			if ((U[i][j] > 0 ? U[i][j] : -U[i][j]) > Umax)
				Umax = (U[i][j] > 0 ? U[i][j] : -U[i][j]);
	return dl / Umax;
}

void simuFluide2D(int Nx, int Ny, long double t_simu, long double nu, long double rho, long double delta, long double Lx, long double Ly)
{
	long double kappa(nu / rho), dx(Lx / Nx), dy(Ly / Ny);
	Matrice<long double> Ux(Ny, Nx), Uy(Ny, Nx), W(Ny, Nx);

	for (long double i(0); i < Ny; i++)
		for (long double j(0); j < Nx; j++)
			W[i][j] = wInit(j / Nx, i / Ny, delta, rho);

	long double t(0), dtx, dty, dt;
	long double iterations(0);
	MatriceChainee *premiere, *derniere;
	premiere = new MatriceChainee;
	premiere->matrice = W;
	premiere->suivante = nullptr;
	derniere = premiere;

	while (t < t_simu)
	{
		iterations++;
		std::cout << "> Iteration " << iterations << " a t=" << t << std::endl;

		poissonCurlSolveur(W, Ux, Uy, Lx, Ly);

		dtx = calculDt(Ux, dx);
		dty = calculDt(Uy, dy);
		dt = dtx < dty ? dtx : dty;

		solveur2D(W, Ux, Uy, kappa, dx, dy, dt);

		derniere->suivante = new MatriceChainee;
		derniere = derniere->suivante;
		derniere->matrice = W;
		derniere->suivante = nullptr;

		t += dt;
	}
	iterations++;

	std::cout << std::endl << "## Simulation terminée, mise en place de l'affichage..." << std::endl;

	long double Wmin(premiere->matrice[0][0]), Wmax(Wmin);
	MatriceChainee* courante(premiere);
	while (courante != nullptr)
	{
		for (int i(0); i < Ny; i++)
			for (int j(0); j < Nx; j++)
				if (courante->matrice[i][j] > Wmax)
					Wmax = courante->matrice[i][j];
				else if (courante->matrice[i][j] < Wmin)
					Wmin = courante->matrice[i][j];

		courante = courante->suivante;
	}

	courante = premiere;
	int i(1);
	while (courante != nullptr)
	{
		std::cout << "> Calcul image " << i << "/" << iterations << std::endl;
		plot(courante->matrice, Wmin, Wmax);
		courante = courante->suivante;
		i++;
	}

	courante = premiere;
	MatriceChainee* tmp;
	while (courante != nullptr)
	{
		tmp = courante->suivante;
		delete courante;
		courante = tmp;
	}

	show(int((iterations + 1) / (t_simu * 2)));
}

