#include "main.h"


static std::string testInit(Test& test)
{
	test.addSubTest("Matrice<T>()", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x;

			std::stringstream stream;
			stream << x;
			if (stream.str() != "()")
				result += "Resultat attendu: (). Resultat obtenu: " + stream.str() + ".\n";
			
			return result;
		});

	test.addSubTest("Matrice<T>(unsigned int m, unsigned int n)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x(0, 1);

			std::stringstream stream;
			stream << x;
			if (stream.str() != "()")
				result += "Resultat attendu: (). Resultat obtenu: " + stream.str() + ".\n";

			x = Matrice<long double>(1, 0);

			stream.str("");
			stream << x;
			if (stream.str() != "()")
				result += "Resultat attendu: (). Resultat obtenu: " + stream.str() + ".\n";

			x = Matrice<long double>(2, 2);

			stream.str("");
			stream << x;
			if (stream.str() != "(0 0\n 0 0)")
				result += "Resultat attendu:\n(0 0\n 0 0)\nResultat obtenu:\n" + stream.str() + "\n";

			return result;
		});

	test.addSubTest("Matrice<T>(std::initializer_list<std::initializer_list<T>> tab)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({{}});

			std::stringstream stream;
			stream << x;
			if (stream.str() != "()")
				result += "Resultat attendu: (). Resultat obtenu: " + stream.str() + ".\n";

			x = Matrice<long double>({ { 1, 0 }, { 0, 1 } });

			stream.str("");
			stream << x;
			if (stream.str() != "(1 0\n 0 1)")
				result += "Resultat attendu:\n(1 0\n 0 1)\nResultat obtenu:\n" + stream.str() + "\n";

			try
			{
				x = Matrice<long double>({ { 1, 0, 2 }, { 0, 1 } });

				stream.str("");
				stream << x;
				result += "Erreur attendue. Aucune erreur detectée.\nMatrice obtenue:\n" + stream.str() + "\n";
			}
			catch (std::out_of_range const& e) {}

			return result;
		});

	test.addSubTest("Matrice<T>(T const* tab, unsigned int m, unsigned int n)", [](Test& test)->std::string
		{
			std::string result;

			long double tab[] = { 0, 1, 2, 3, 4 };
			Matrice<long double> x(tab, 0, 1);

			std::stringstream stream;
			stream << x;
			if (stream.str() != "()")
				result += "Resultat attendu: (). Resultat obtenu: " + stream.str() + ".\n";

			x = Matrice<long double>(tab, 1, 0);

			stream.str("");
			stream << x;
			if (stream.str() != "()")
				result += "Resultat attendu: (). Resultat obtenu: " + stream.str() + ".\n";

			x = Matrice<long double>(tab, 2, 2);

			stream.str("");
			stream << x;
			if (stream.str() != "(0 1\n 2 3)")
				result += "Resultat attendu:\n(0 1\n 2 3)\nResultat obtenu:\n" + stream.str() + "\n";

			return result;
		});

	return "";
}

static std::string testAddition(Test& test)
{
	return "";
}

static std::string testSoustraction(Test& test)
{
	return "";
}

static std::string testMultiplication(Test& test)
{
	return "";
}

static std::string testDivision(Test& test)
{
	return "";
}

static std::string testUnaires(Test& test)
{
	return "";
}

static std::string testEgalite(Test& test)
{
	return "";
}

static std::string testFonctionsMatrices(Test& test)
{
	return "";
}

static std::string testGeneraux(Test& test)
{
	return "";
}

std::string mainMatrice(Test& test)
{
	test.addSubTest("Test des initialisations", &testInit);

	test.addSubTest("Test des additions", &testAddition);
	test.addSubTest("Test des soustractions", &testSoustraction);
	test.addSubTest("Test des multiplications", &testMultiplication);
	test.addSubTest("Test des divisions", &testDivision);
	test.addSubTest("Test des plus et moins unaires", &testUnaires);

	test.addSubTest("Test des operateurs == et !=", &testEgalite);

	test.addSubTest("Test des fonctions specifiques aux matrices", &testFonctionsMatrices);

	test.addSubTest("Test generaux", &testGeneraux);

	return "";
}
