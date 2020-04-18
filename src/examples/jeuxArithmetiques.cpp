#include "jeuxArithmetiques.h"

std::string neper(int n)
{
	// Calcul du nombre d'it�rations n�cessaires

	int k(0);
	Rationnel fact(2);
	Rationnel puiss(1, 10);
	puiss = expoRapide(puiss, n + 1);
	while (fact >= puiss)
	{
		k++;
		fact /= k;
	}

	// Calcul de la constante de neper

	fact = Rationnel(1);
	Rationnel s(1);
	for (int i(1); i < k; i++)
	{
		std::cout << "> Iteration " << i + 1 << "/" << k << std::endl;
		fact /= i;
		s += fact;
	}

	std::cout << std::endl;

	return decimales(s, n);
}

void fonctionLogistique()
{
	int w(1920), h(1017);

	Timeline::TAILLE_PLOT[0] = w;
	Timeline::TAILLE_PLOT[1] = h;

	int n(100000);
	Matrice<long double> f(w, h);
	Vect<double> bornes(2);
	bornes[0] = 2.8;
	bornes[1] = 4;

	for (int i(0); i < w; i++)
	{
		double x(0.5);
		double r(bornes[0] + (bornes[1] - bornes[0]) * i / w);
		for (int j(0); j < n; j++)
		{
			x = r * x * (1 - x);
			f[i][h - 1 - int(x * h)] += 1.0 / n;
		}

		double max(0);
		for (int j(0); j < h; j++)
		{
			max = f[i][j] > max ? f[i][j] : max;
		}
		for (int j(0); j < h; j++)
		{
			f[i][j] /= max;
		}
	}

	Timeline timeline;
	timeline.plot(f, 0, 1);
	Timeline::show();

	Timeline::resetPlotSize();
}

void mandelbrot(double xCentre, double yCentre, double zoom)
{
	int w(1920), h(1080);

	Timeline::TAILLE_PLOT[0] = w;
	Timeline::TAILLE_PLOT[1] = h;

	int n(200);
	Matrice<long double> f(w, h);
	Vect<double> bornes(4);
	bornes[0] = xCentre - 2.0/zoom;
	bornes[1] = xCentre + 2.0/zoom;
	bornes[2] = yCentre - 1.0/zoom;
	bornes[3] = yCentre + 1.0/zoom;

	for (int i(0); i < w; i++)
	{
		std::cout << 100 * double(i) / w << "%" << std::endl;
		for (int j(0); j < h; j++)
		{
			std::complex<double> c(bornes[0] + (bornes[1] - bornes[0]) * i / w, bornes[2] + (bornes[3] - bornes[2]) * j / h), z(0, 0);
			for (int k(0); k < n; k++)
			{
				z = z * z + c;
				if (std::abs(z) > 2)
				{
					z = 2;
					break;
				}
			}
			f[i][h - 1 - j] = std::abs(z) >= 2 ? 2: 0;
		}
	}

	Timeline timeline;
	timeline.plot(f, 0, 2);
	Timeline::show();

	Timeline::resetPlotSize();
}

Vect<Vect<int>> voisins(int x, int y, int w, int h)
{
	Vect<Vect<int>> voisinsPossibles(8);
	for (int i(0); i < 8; i++)
		voisinsPossibles[i] = Vect<int>(2);

	voisinsPossibles[0][0] = x + 1; voisinsPossibles[0][1] = y + 1;
	voisinsPossibles[1][0] = x + 1; voisinsPossibles[1][1] = y;
	voisinsPossibles[2][0] = x + 1; voisinsPossibles[2][1] = y - 1;
	voisinsPossibles[3][0] = x; voisinsPossibles[3][1] = y + 1;
	voisinsPossibles[4][0] = x; voisinsPossibles[4][1] = y - 1;
	voisinsPossibles[5][0] = x - 1; voisinsPossibles[5][1] = y + 1;
	voisinsPossibles[6][0] = x - 1; voisinsPossibles[6][1] = y;
	voisinsPossibles[7][0] = x - 1; voisinsPossibles[7][1] = y - 1;

	int nbVoisins(8);
	for (int i(0); i < 8; i++)
		if (voisinsPossibles[i][0] < 0 || voisinsPossibles[i][0] >= w || voisinsPossibles[i][1] < 0 || voisinsPossibles[i][1] >= h)
			nbVoisins--;

	Vect<Vect<int>> voisinsDefinitifs(nbVoisins);
	int j(0);
	for (int i(0); i < 8; i++)
		if (voisinsPossibles[i][0] >= 0 && voisinsPossibles[i][0] < w && voisinsPossibles[i][1] >= 0 && voisinsPossibles[i][1] < h)
		{
			voisinsDefinitifs[j] = voisinsPossibles[i];
			j++;
		}
	
	return voisinsDefinitifs;
}

void conway()
{
	int w(50), h(50), t(300), tR(10);
	Matrice<long double> M(w, h), N(w, h);

	// Initialisation

	int const wInit(40), hInit(10);
	long double tab[hInit][wInit] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
							         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
							         {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							         {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	
	for (int i(0); i < wInit; i++)
		for (int j(0); j < hInit; j++)
			M[i][j] = tab[j][i];

	// Jeu de la vie lui même

	Timeline timeline;
	timeline.plot(M, 0, 1);
	for (int dt(0); dt < t; dt++)
	{
		std::cout << "Iteration: " << dt << std::endl;
		for (int i(0); i < w; i++)
		{
			for (int j(0); j < h; j++)
			{
				Vect<Vect<int>> voisinage(voisins(i, j, w, h));
				int s(0);
				for (int k(0); k < voisinage.size(); k++)
					s += M[voisinage[k][0]][voisinage[k][1]];
				if (M[i][j] == 0 && s == 3)
					N[i][j] = 1;
				else if (M[i][j] == 1 && (s < 2 || s > 3))
					N[i][j] = 0;
				else
					N[i][j] = M[i][j];
			}
		}

		M = N;
		timeline.plot(M, 0, 1);
	}

	timeline.setFramerate(double(t)/tR + 1);
	Timeline::show();
}
