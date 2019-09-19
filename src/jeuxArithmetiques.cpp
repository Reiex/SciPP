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