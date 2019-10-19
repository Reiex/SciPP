#include "jeuxArithmetiques.h"

std::string neper(int n)
{
	// Calcul du nombre d'itérations nécessaires

	int k(0);
	Fraction<Entier> fact(2);
	Fraction<Entier> puiss(1, 10);
	puiss = expoRapide(puiss, n + 1);
	while (fact >= puiss)
	{
		k++;
		fact /= k;
	}

	// Calcul de la constante de neper

	fact = Fraction<Entier>(1);
	Fraction<Entier> s(1);
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
	Vecteur<double> bornes(2);
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

	Timeline::TAILLE_PLOT[0] = 600;
	Timeline::TAILLE_PLOT[1] = 600;
}
