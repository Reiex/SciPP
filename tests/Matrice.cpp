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

static std::string testAccesseurC(Test& test)
{
	test.addSubTest("Vect<T>& operator[](unsigned int i)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} });

			std::stringstream stream;
			stream << x[0][2];
			if (stream.str() != "3")
				result += "Resultat attendu: 3. Resultat obtenu: " + stream.str() + ".\n";

			stream.str("");
			try
			{
				stream << x[2][0];
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu: " + stream.str() + ".\n";
			}
			catch (char const* e) {}

			x[0][2] = 5;

			stream.str("");
			stream << x[0][2];
			if (stream.str() != "5")
				result += "Resultat attendu: 5. Resultat obtenu: " + stream.str() + ".\n";

			return result;
		});

	test.addSubTest("Vect<T> const& operator[](unsigned int i) const", [](Test& test)->std::string
		{
			std::string result;

			const Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} });

			std::stringstream stream;
			stream << x[0][2];
			if (stream.str() != "3")
				result += "Resultat attendu: 3. Resultat obtenu: " + stream.str() + ".\n";

			stream.str("");
			try
			{
				stream << x[2][0];
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu: " + stream.str() + ".\n";
			}
			catch (char const* e) {}

			return result;
		});

	return "";
}

static std::string testAffectation(Test& test)
{
	test.addSubTest("Matrice<T>& Matrice<T>::operator=(Matrice<T> const& M)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x(0, 0), y(0, 0);
			y = x;

			std::stringstream stream;
			stream << y;
			if (stream.str() != "()")
				result += "Copie matrice vide dans matrice vide:\nResultat attendu: (). Resultat obtenu: " + stream.str() + ".\n";

			x = Matrice<long double>({ { 1, 0 }, { 0, 1 } });
			y = Matrice<long double>(0, 0);
			y = x;

			stream.str("");
			stream << y;
			if (stream.str() != "(1 0\n 0 1)")
				result += "Copie matrice normale dans matrice vide:\nResultat attendu:\n(1 0\n 0 1)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ { 1, 0 }, { 0, 1 } });
			y = Matrice<long double>({ { 1, 2, 3 }, { 4, 5, 6 } });
			y = x;

			stream.str("");
			stream << y;
			if (stream.str() != "(1 0\n 0 1)")
				result += "Copie matrice normale dans matrice normale:\nResultat attendu:\n(1 0\n 0 1)\nResultat obtenu:\n" + stream.str() + "\n";

			y[0][0] = 5;

			stream.str("");
			stream << x[0][0];
			if (stream.str() != "1")
				result += "Changement apres copie - Matrice copiee:\nResultat attendu: 1. Resultat obtenu: " + stream.str() + ".\n";

			stream.str("");
			stream << y[0][0];
			if (stream.str() != "5")
				result += "Changement apres copie - Matrice destination:\nResultat attendu: 5. Resultat obtenu: " + stream.str() + ".\n";

			return result;
		});

	test.addSubTest("Matrice<T>& Matrice<T>::operator=(Matrice<T>&& M)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x(0, 0), y(0, 0);
			y = std::move(x);

			std::stringstream stream;
			stream << y;
			if (stream.str() != "()")
				result += "Deplacement matrice vide dans matrice vide:\nResultat attendu: (). Resultat obtenu: " + stream.str() + ".\n";

			x = Matrice<long double>({ { 1, 0 }, { 0, 1 } });
			y = Matrice<long double>(0, 0);
			y = std::move(x);

			stream.str("");
			stream << y;
			if (stream.str() != "(1 0\n 0 1)")
				result += "Deplacement matrice normale dans matrice vide:\nResultat attendu:\n(1 0\n 0 1)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ { 1, 0 }, { 0, 1 } });
			y = Matrice<long double>({ { 1, 2, 3 }, { 4, 5, 6 } });
			y = std::move(x);

			stream.str("");
			stream << y;
			if (stream.str() != "(1 0\n 0 1)")
				result += "Deplacement matrice normale dans matrice normale:\nResultat attendu:\n(1 0\n 0 1)\nResultat obtenu:\n" + stream.str() + "\n";

			stream.str("");
			stream << x;
			if (stream.str() != "()")
				result += "Suppression origine apres deplacement:\nResultat attendu: (). Resultat obtenu: " + stream.str() + ".";

			y[0][0] = 5;

			stream.str("");
			stream << y[0][0];
			if (stream.str() != "5")
				result += "Changement apres deplacement:\nResultat attendu: 5. Resultat obtenu: " + stream.str() + ".\n";

			return result;
		});

	return "";
}

static std::string testDestructeur(Test& test)
{
	test.addSubTest("Destruction d'une matrice vide", [](Test& test)->std::string
		{
			Matrice<long double>* x(new Matrice<long double>());
			delete x;
			return "";
		});

	test.addSubTest("Destruction d'une matrice normale", [](Test& test)->std::string
		{
			Matrice<long double>* x(new Matrice<long double>(5, 3));
			delete x;
			return "";
		});

	test.addSubTest("Destruction d'une matrice copie", [](Test& test)->std::string
		{
			Matrice<long double> *x(new Matrice<long double>(5, 3)), *y(new Matrice<long double>());
			*y = *x;
			delete y;
			delete x;
			return "";
		});

	test.addSubTest("Destruction d'une matrice deplace", [](Test& test)->std::string
		{
			Matrice<long double> *x(new Matrice<long double>(5, 3)), *y(new Matrice<long double>());
			*y = std::move(*x);
			delete y;
			delete x;
			return "";
		});

	return "";
}

static std::string testAddition(Test& test)
{
	test.addSubTest("Matrice<T>& operator+=(Matrice<T> const& M)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} }), y({ {-7, 8, -9}, {10, -11, 12} });
			x += y;

			std::stringstream stream;
			stream << x;
			if (stream.str() != "(-6 10 -6\n 14 -6 18)")
				result += "Resultat attendu:\n(-6 10 -6\n 14 -6 18)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ {1, 2, 3}, {4, 5, 6} });
			y = Matrice<long double>();

			stream.str("");
			try
			{
				x += y;
				stream << x;
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu:\n" + stream.str() + "\n";
			}
			catch (char const* e) {}

			return result;
		});

	test.addSubTest("Matrice<T> operator+(Matrice<T> const& M, Matrice<T> const& N)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} }), y({ {-7, 8, -9}, {10, -11, 12} }), z;
			z = x + y;

			std::stringstream stream;
			stream << z;
			if (stream.str() != "(-6 10 -6\n 14 -6 18)")
				result += "Resultat attendu:\n(-6 10 -6\n 14 -6 18)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ {1, 2, 3}, {4, 5, 6} });
			y = Matrice<long double>();

			stream.str("");
			try
			{
				z = x + y;
				stream << z;
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu:\n" + stream.str() + "\n";
			}
			catch (char const* e) {}

			return result;
		});

	test.addSubTest("Matrice<T>&& operator+(Matrice<T>&& M, Matrice<T> const& N)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} }), y({ {-7, 8, -9}, {10, -11, 12} }), z;
			z = std::move(x) + y;

			std::stringstream stream;
			stream << z;
			if (stream.str() != "(-6 10 -6\n 14 -6 18)")
				result += "Resultat attendu:\n(-6 10 -6\n 14 -6 18)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ {1, 2, 3}, {4, 5, 6} });
			y = Matrice<long double>();

			stream.str("");
			try
			{
				z = std::move(x) + y;
				stream << z;
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu:\n" + stream.str() + "\n";
			}
			catch (char const* e) {}

			return result;
		});

	test.addSubTest("Matrice<T>&& operator+(Matrice<T> const& M, Matrice<T>&& N)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} }), y({ {-7, 8, -9}, {10, -11, 12} }), z;
			z = x + std::move(y);

			std::stringstream stream;
			stream << z;
			if (stream.str() != "(-6 10 -6\n 14 -6 18)")
				result += "Resultat attendu:\n(-6 10 -6\n 14 -6 18)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ {1, 2, 3}, {4, 5, 6} });
			y = Matrice<long double>();

			stream.str("");
			try
			{
				z = x + std::move(y);
				stream << z;
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu:\n" + stream.str() + "\n";
			}
			catch (char const* e) {}

			return result;
		});

	test.addSubTest("Matrice<T>&& operator+(Matrice<T>&& M, Matrice<T>&& N)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} }), y({ {-7, 8, -9}, {10, -11, 12} }), z;
			z = std::move(x) + std::move(y);

			std::stringstream stream;
			stream << z;
			if (stream.str() != "(-6 10 -6\n 14 -6 18)")
				result += "Resultat attendu:\n(-6 10 -6\n 14 -6 18)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ {1, 2, 3}, {4, 5, 6} });
			y = Matrice<long double>();

			stream.str("");
			try
			{
				z = std::move(x) + std::move(y);
				stream << z;
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu:\n" + stream.str() + "\n";
			}
			catch (char const* e) {}

			return result;
		});

	return "";
}

static std::string testSoustraction(Test& test)
{
	test.addSubTest("Matrice<T>& operator-=(Matrice<T> const& M)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} }), y({ {-7, 8, -9}, {10, -11, 12} });
			x -= y;

			std::stringstream stream;
			stream << x;
			if (stream.str() != "(8 -6 12\n -6 16 -6)")
				result += "Resultat attendu:\n(8 -6 12\n -6 16 -6)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ {1, 2, 3}, {4, 5, 6} });
			y = Matrice<long double>();

			stream.str("");
			try
			{
				x -= y;
				stream << x;
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu:\n" + stream.str() + "\n";
			}
			catch (char const* e) {}

			return result;
		});

	test.addSubTest("Matrice<T> operator-(Matrice<T> const& M, Matrice<T> const& N)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} }), y({ {-7, 8, -9}, {10, -11, 12} }), z;
			z = x - y;

			std::stringstream stream;
			stream << z;
			if (stream.str() != "(8 -6 12\n -6 16 -6)")
				result += "Resultat attendu:\n(8 -6 12\n -6 16 -6)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ {1, 2, 3}, {4, 5, 6} });
			y = Matrice<long double>();

			stream.str("");
			try
			{
				z = x - y;
				stream << z;
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu:\n" + stream.str() + "\n";
			}
			catch (char const* e) {}

			return result;
		});

	test.addSubTest("Matrice<T>&& operator-(Matrice<T>&& M, Matrice<T> const& N)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} }), y({ {-7, 8, -9}, {10, -11, 12} }), z;
			z = std::move(x) - y;

			std::stringstream stream;
			stream << z;
			if (stream.str() != "(8 -6 12\n -6 16 -6)")
				result += "Resultat attendu:\n(8 -6 12\n -6 16 -6)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ {1, 2, 3}, {4, 5, 6} });
			y = Matrice<long double>();

			stream.str("");
			try
			{
				z = std::move(x) - y;
				stream << z;
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu:\n" + stream.str() + "\n";
			}
			catch (char const* e) {}

			return result;
		});

	test.addSubTest("Matrice<T>&& operator-(Matrice<T>&& M, Matrice<T>&& N)", [](Test& test)->std::string
		{
			std::string result;

			Matrice<long double> x({ {1, 2, 3}, {4, 5, 6} }), y({ {-7, 8, -9}, {10, -11, 12} }), z;
			z = std::move(x) - std::move(y);

			std::stringstream stream;
			stream << z;
			if (stream.str() != "(8 -6 12\n -6 16 -6)")
				result += "Resultat attendu:\n(8 -6 12\n -6 16 -6)\nResultat obtenu:\n" + stream.str() + "\n";

			x = Matrice<long double>({ {1, 2, 3}, {4, 5, 6} });
			y = Matrice<long double>();

			stream.str("");
			try
			{
				z = std::move(x) - std::move(y);
				stream << z;
				result += "Erreur attendue. Aucune erreur detectee. Resultat obtenu:\n" + stream.str() + "\n";
			}
			catch (char const* e) {}

			return result;
		});

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
	test.addSubTest("Test de l'operateur []", &testAccesseurC);
	test.addSubTest("Test des affectations", &testAffectation);
	test.addSubTest("Test du destructeur", &testDestructeur);

	test.addSubTest("Test des additions", &testAddition);
	test.addSubTest("Test des soustractions", &testSoustraction);
	test.addSubTest("Test des multiplications", &testMultiplication);
	test.addSubTest("Test des divisions", &testDivision);

	test.addSubTest("Test des operateurs == et !=", &testEgalite);

	test.addSubTest("Test des fonctions specifiques aux matrices", &testFonctionsMatrices);

	test.addSubTest("Test generaux", &testGeneraux);

	return "";
}
