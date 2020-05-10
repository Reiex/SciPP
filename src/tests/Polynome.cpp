#include "main.h"


static std::string testInit(Test& test)
{
	test.addSubTest("Initialisation par defaut", [](Test& test)->std::string
	{
		Polynome<long double> x;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(0)")
			return "";
		else
			return "Resultat attendu: Polynome(0). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation par un entier", [](Test& test)->std::string
	{
		Polynome<long double> x(25);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(25)")
			return "";
		else
			return "Resultat attendu: Polynome(25). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation par T const&", [](Test& test)->std::string
	{
		Polynome<long double> x(25.5L);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(25.5)")
			return "";
		else
			return "Resultat attendu: Polynome(25.5). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation par liste d'initialisation", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8, 0, 3 });
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(1, 6, 1, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 1, 8, 0, 3). Resultat obtenu: " + stream.str() + ". ";
	});

	test.addSubTest("Initialisation par liste d'initialisation vide", [](Test& test)->std::string
	{
		Polynome<long double> x({ });
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(0)")
			return "";
		else
			return "Resultat attendu: Polynome(0). Resultat obtenu: " + stream.str() + ". ";
	});

	test.addSubTest("Initialisation par tableau C", [](Test& test)->std::string
	{
		long double tab[] = { 1, 6, 1, 8, 0, 3 };
		Polynome<long double> x(tab, 6);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(1, 6, 1, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 1, 8, 0, 3). Resultat obtenu: " + stream.str() + ". ";
	});

	return "";
}

static std::string testAddition(Test& test)
{
	test.addSubTest("Addition en place", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4 });
		x += y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(4, 7, 5, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(4, 7, 5, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Polynome(Polynome const&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4 }), z;
		z = x + y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(4, 7, 5, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(4, 7, 5, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Polynome&&(Polynome&&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4 }), z;
		z = std::move(x) + y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(4, 7, 5, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(4, 7, 5, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Polynome&&(Polynome const&, Polynome&&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4 }), z;
		z = x + std::move(y);
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(4, 7, 5, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(4, 7, 5, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Polynome&&(Polynome&&, Polynome&&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4 }), z;
		z = std::move(x) + std::move(y);
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(4, 7, 5, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(4, 7, 5, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

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

static std::string testModulo(Test& test)
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

static std::string testGeneraux(Test& test)
{
	test.addSubTest("Derivee", [](Test& test)->std::string
	{
		return "";
	});
	return "";
}

std::string mainPolynome(Test& test)
{
	test.addSubTest("Test des initialisations", &testInit);

	test.addSubTest("Test des additions", &testAddition);
	test.addSubTest("Test des soustractions", &testSoustraction);
	test.addSubTest("Test des multiplications", &testMultiplication);
	test.addSubTest("Test des divisions", &testDivision);
	test.addSubTest("Test des modulos", &testModulo);
	test.addSubTest("Test des plus et moins unaires", &testUnaires);

	test.addSubTest("Test des operateurs == et !=", &testEgalite);

	test.addSubTest("Test generaux", &testGeneraux);

	return "";
}
