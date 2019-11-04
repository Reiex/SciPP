#include "simuPhysique.h"


// Générale

Force::Force()
{
	m_func = nullptr;
}

void Force::setFunc(Vect<double>(*func)(Point))
{
	m_func = func;
}

Vect<double> Force::operator()(Point p)
{
	return (*m_func)(p);
}


Point::Point(double x, double y, double m)
{
	m_x = x;
	m_y = y;
	m_m = m;
	m_dx = 0;
	m_dy = 0;
	m_dm = 0;
	m_dt = 1;
}

void Point::ajouterForce(Force f)
{
	m_forces.push_back(f);
}

void Point::setVitesse(double vx, double vy)
{
	m_dx = vx * m_dt;
	m_dy = vy * m_dt;
}

void Point::setDt(double dt)
{
	m_dt = dt;
}

Vect<double> Point::getEtat() const
{
	Vect<double> etat(7);
	etat[0] = m_x;
	etat[1] = m_y;
	etat[2] = m_m;
	etat[3] = m_dx/m_dt;
	etat[4] = m_dy/m_dt;
	etat[5] = m_dm/m_dt;
	etat[6] = m_dt;

	return etat;
}

void Point::update()
{
	double aX(0), aY(0);
	for (int i(0); i < m_forces.size(); i++)
	{
		Vect<double> a(m_forces[i](*this));
		aX += a[0];
		aY += a[1];
	}

	aX /= m_m;
	aY /= m_m;

	m_dx += aX * m_dt * m_dt;
	m_dy += aY * m_dt * m_dt;
	m_x += m_dx;
	m_y += m_dy;
}


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

	Vect<long double> x(Nx), y(Nx);
	for (int i(0); i < Nx; i++)
	{
		x[i] = i;
	}

	Timeline timeline;
	Matrice<long double> B(N.inv());
	for (int i(0); i < Nt; i++)
	{
		std::cout << 100 * (float(i) / Nt) << "%" << std::endl;
		Phi = B*(M*Phi);
		for (int j(0); j < Nx; j++)
		{
			y[j] = Phi[j][0];
		}
		timeline.plot(x, y);
	}

	timeline.setFramerate(24);
	Timeline::show();
}

// 2 Dimensions

struct MatriceChainee
{
	Matrice<long double> matrice;
	MatriceChainee* suivante;
};

void solveur1D(Vect<long double>& W, Vect<long double> const& U, long double kappa, long double dl, long double dt)
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
		Vect<long double> Wy(Ny), Vy(Ny);
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

	Vect<std::complex<long double>> kx(Nx), ky(Ny);
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

	Timeline timeline;
	courante = premiere;
	int i(1);
	while (courante != nullptr)
	{
		std::cout << "> Calcul image " << i << "/" << iterations << std::endl;
		timeline.plot(courante->matrice, Wmin, Wmax);
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

	timeline.setFramerate(iterations/(t_simu*2));
	Timeline::show();
}


// Simulations mecaniques

Vect<double> gravite(Point p)
{
	Vect<double> force(2);
	force[1] = -9.81*p.getEtat()[2];

	return force;
}

Vect<double> chocElastique(Point p)
{
	double k(1000), gamma(0.005);

	Vect<double> force(2), etat(p.getEtat());
	double yp(etat[1]), ypp(etat[1]-etat[4]*etat[6]);

	yp = yp > 0 ? 0: yp;
	ypp = ypp > 0 ? 0: ypp;

	yp *= -1;
	ypp *= -1;

	yp *= sqrt(yp);
	ypp *= sqrt(ypp);

	force[1] = k*(yp + gamma*(yp - ypp)/etat[6]);

	return force;
}

void simuBalle(long double t, long double x, long double y, long double vx, long double vy)
{
	int n(10000);

	long double dt(t/n);

	Point p(x, y, 0.1);
	Force g, elastique;

	g.setFunc(gravite);
	elastique.setFunc(chocElastique);
	p.ajouterForce(g);
	p.ajouterForce(elastique);
	p.setVitesse(vx, vy);
	p.setDt(dt);

	Timeline timeline;
	for (int i(0); i < n; i++)
	{
		Vect<double> etat(p.getEtat());
		timeline.plot(etat[0], etat[1]);
		p.update();
	}
	
	timeline.setFramerate(1.0/dt);
	Timeline::show();
}


// Simulations de systemes dynamiques


Vect<double> fEquilibreRotation(Vect<double> x)
{
	double omega = 2;
	double mu = 2;
	double a = -0.1;

	Vect<double> xp(2);
	xp[0] = -omega*x[1] + mu*x[0] + a*x[0]*(x[0]*x[0] + x[1]*x[1]);
	xp[1] = omega*x[0] + mu*x[1] + a*x[1]*(x[0]*x[0] + x[1]*x[1]);

	return xp;
}

Vect<double> fProiesPredateurs(Vect<double> x)
{
	double alpha = 0.5;
	double lambda = 0.5;

	Vect<double> xp(2);
	xp[0] = x[0]*(1-x[1]-lambda*x[0]);
	xp[1] = alpha*x[1]*(x[0]-1);

	return xp;
}

Vect<double> fPendule(Vect<double> x)
{
	double nu(1);

	Vect<double> xp(2);
	xp[0] = x[1];
	xp[1] = -sin(x[0]) - nu*x[1];

	return xp;
}

void systemeD()
{
	Vect<double> coord(4);

	// Equilibre rotation

	// coord[0] = -10; coord[1] = 10; coord[2] = -10; coord[3] = 10;
	// plotFlot2D(fEquilibreRotation, coord, 100000, 100);

	// Proies prédateurs

	// coord[0] = 0; coord[1] = 3; coord[2] = 0; coord[3] = 3;
	// plotFlot2D(fProiesPredateurs, coord, 500, 10);

	// Pendule

	coord[0] = -10; coord[1] = 10; coord[2] = -2; coord[3] = 2;
	plotFlot2D(fPendule, coord, 100, 50);
}


// Equation de la chaleur


double uInit(double x, double y)
{
	double pi(3.1415926);
	double r(0), d((x - 0.5)*(x - 0.5) + (y - 0.5)*(y-0.5));

	r += 5*exp(-50*std::abs(0.2 - d));

	return r;
}

void dispertionChaleur2D(int Nx, int Ny, double t_simu)
{
	double dx(1.0/Nx), dy(1.0/Ny), Umin(uInit(0, 0)), Umax(uInit(0, 0));
	double nu(0.1);

	Matrice<long double> U(Nx, Ny);

	for (int i(0); i < Nx; i++)
	{
		for (int j(0); j < Ny; j++)
		{
			U[i][j] = uInit(double(i)/(Nx - 1), double(j)/(Ny - 1));
			Umin = U[i][j] < Umin ? U[i][j]: Umin;
			Umax = U[i][j] > Umax ? U[i][j]: Umax;
		}
	}

	Timeline timeline;
	timeline.plot(U, Umin, Umax);
	long double t(0);
	int nbIterations(0), nbImages(0);
	Matrice<long double> Up(Nx, Ny);
	while (t < t_simu)
	{
		double max(0);
		for (int i(0); i < Nx; i++)
		{
			for (int j(0); j < Ny; j++)
			{
				Up[i][j] = (U[i > 0 ? i-1 : Nx - 1][j] - 2*U[i][j] + U[i < Nx - 1 ? i+1: 0][j])/(dx*dx) + (U[i][j > 0 ? j-1 : Ny - 1] - 2*U[i][j] + U[i][j < Ny - 1 ? j+1: 0])/(dy*dy);
				Up[i][j] *= nu;
				if (Up[i][j] > max || Up[i][j] < -max)
				{
					max = Up[i][j] > 0 ? Up[i][j]: -Up[i][j];
				}
			}
		}

		long double dt(5*(dx*dx + dy*dy)/(max*nu));
		U += Up*dt;
		t += dt;
		if (t > double(nbImages + 1)/2400)
		{
			nbImages += 1;
			timeline.plot(U, Umin, Umax);
			std::cout << max << ", " << t << ", " << dt << std::endl;
		}
		nbIterations++;
	}

	std::cout << nbImages << std::endl;

	timeline.setFramerate(24);
	Timeline::show();
}
