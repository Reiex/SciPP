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
	test.addSubTest("Addition en place deg(*this) > deg(P)", [](Test& test)->std::string
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

	test.addSubTest("Addition en place deg(*this) < deg(P)", [](Test& test)->std::string
	{
		Polynome<long double> x({ 3, 1, 4 }), y({ 1, 6, 1, 8, 0, 3 });
		x += y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(4, 7, 5, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(4, 7, 5, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition en place deg(*this) == deg(P)", [](Test& test)->std::string
	{
		Polynome<long double> x({ 3, 1, 4, 1, 5, 9 }), y({ 1, 6, 1, 8, 0, 3 });
		x += y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(4, 7, 5, 9, 5, 12)")
			return "";
		else
			return "Resultat attendu: Polynome(4, 7, 5, 9, 5, 12). Resultat obtenu: " + stream.str() + ".";
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
	test.addSubTest("Soustraction en place deg(*this) > deg(P)", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4 });
		x -= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(-2, 5, -3, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(-2, 5, -3, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction en place deg(*this) < deg(P)", [](Test& test)->std::string
	{
		Polynome<long double> x({ 3, 1, 4 }), y({ 1, 6, 1, 8, 0, 3 });
		x -= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(2, -5, 3, -8, 0, -3)")
			return "";
		else
			return "Resultat attendu: Polynome(2, -5, 3, -8, 0, -3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction en place deg(*this) == deg(P)", [](Test& test)->std::string
	{
		Polynome<long double> x({ 3, 1, 4, 1, 5, 9 }), y({ 1, 6, 1, 8, 0, 3 });
		x -= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(2, -5, 3, -7, 5, 6)")
			return "";
		else
			return "Resultat attendu: Polynome(2, -5, 3, -7, 5, 6). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe Polynome(Polynome const&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4 }), z;
		z = x - y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(-2, 5, -3, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(-2, 5, -3, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe Polynome&&(Polynome&&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4 }), z;
		z = std::move(x) - y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(-2, 5, -3, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(-2, 5, -3, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe Polynome&&(Polynome&&, Polynome&&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4 }), z;
		z = std::move(x) - std::move(y);
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(-2, 5, -3, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(-2, 5, -3, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testMultiplication(Test& test)
{
	test.addSubTest("Multiplication en place normale", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8, 0, 3 }), y({ 1, 0, 1 });
		x *= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(1, 6, 2, 14, 1, 11, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 2, 14, 1, 11, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication en place par 0", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8, 0, 3 }), y(0);
		x *= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(0)")
			return "";
		else
			return "Resultat attendu: Polynome(0). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Polynome(Polynome const&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 1, 0, 1 }), z;
		z = x * y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(1, 6, 2, 14, 1, 11, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 2, 14, 1, 11, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Polynome&&(Polynome&&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 1, 0, 1 }), z;
		z = std::move(x) * y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(1, 6, 2, 14, 1, 11, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 2, 14, 1, 11, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Polynome&&(Polynome const&, Polynome&&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 1, 0, 1 }), z;
		z = x * std::move(y);
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(1, 6, 2, 14, 1, 11, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 2, 14, 1, 11, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Polynome&&(Polynome&&, Polynome&&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 1, 0, 1 }), z;
		z = std::move(x) * std::move(y);
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(1, 6, 2, 14, 1, 11, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 2, 14, 1, 11, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testDivision(Test& test)
{
	test.addSubTest("Division en place", [](Test& test)->std::string
	{
		Polynome<long double> x({ 3, 8, 2, 14, 1, 11, 0, 3 }), y({ 1, 0, 1 });
		x /= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(1, 6, 1, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 1, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Division externe Polynome(Polynome const&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 3, 8, 2, 14, 1, 11, 0, 3 }), y({ 1, 0, 1 }), z;
		z = x / y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(1, 6, 1, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 1, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Division externe Polynome&&(Polynome&&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 3, 8, 2, 14, 1, 11, 0, 3 }), y({ 1, 0, 1 }), z;
		z = std::move(x) / y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(1, 6, 1, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 1, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Division externe Polynome&&(Polynome&&, Polynome&&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 3, 8, 2, 14, 1, 11, 0, 3 }), y({ 1, 0, 1 }), z;
		z = std::move(x) / std::move(y);
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(1, 6, 1, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 1, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testModulo(Test& test)
{
	test.addSubTest("Modulo en place", [](Test& test)->std::string
	{
		Polynome<long double> x({ 3, 0, 2, 14, 1, 11, 0, 3 }), y({ 1, 0, 1 });
		x %= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(2, -6)")
			return "";
		else
			return "Resultat attendu: Polynome(2, -6). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Modulo externe Polynome(Polynome const&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 3, 0, 2, 14, 1, 11, 0, 3 }), y({ 1, 0, 1 }), z;
		z = x % y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(2, -6)")
			return "";
		else
			return "Resultat attendu: Polynome(2, -6). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Modulo externe Polynome&&(Polynome&&, Polynome const&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 3, 0, 2, 14, 1, 11, 0, 3 }), y({ 1, 0, 1 }), z;
		z = std::move(x) % y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(2, -6)")
			return "";
		else
			return "Resultat attendu: Polynome(2, -6). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Modulo externe Polynome&&(Polynome&&, Polynome&&)", [](Test& test)->std::string
	{
		Polynome<int> x({ 3, 0, 2, 14, 1, 11, 0, 3 }), y({ 1, 0, 1 }), z;
		z = std::move(x) % std::move(y);
		std::stringstream stream;
		stream << z;
		if (stream.str() == "Polynome(2, -6)")
			return "";
		else
			return "Resultat attendu: Polynome(2, -6). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testUnaires(Test& test)
{
	test.addSubTest("Plus unaire", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8, 0, 3 });
		x = +x;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(1, 6, 1, 8, 0, 3)")
			return "";
		else
			return "Resultat attendu: Polynome(1, 6, 1, 8, 0, 3). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Moins unaire", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8 });
		x = -x;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(-1, -6, -1, -8)")
			return "";
		else
			return "Resultat attendu: Polynome(-1, -6, -1, -8). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testEgalite(Test& test)
{
	test.addSubTest("Comparaison vecteurs egaux", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8, 0, 3 }), y({ 1, 6, 1, 8, 0, 3 });
		if (x == y)
			return "";
		else
			return "Le test d'egalite ne renvoie pas le resultat attendu.";
	});

	test.addSubTest("Comparaison vecteurs differents", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8, 0, 3 }), y({ 1, 6, 1, 8 });
		if (x != y)
			return "";
		else
			return "Le test d'egalite ne renvoie pas le resultat attendu.";
	});

	return "";
}

static std::string testGeneraux(Test& test)
{
	test.addSubTest("Derivee normale", [](Test& test)->std::string
	{
		Polynome<long double> x({ 1, 6, 1, 8, 0, 3 });
		x = x.derivee();
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(6, 2, 24, 0, 15)")
			return "";
		else
			return "Resultat attendu: Polynome(6, 2, 24, 0, 15). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Derivee polynome nul", [](Test& test)->std::string
	{
		Polynome<long double> x({ });
		x = x.derivee();
		std::stringstream stream;
		stream << x;
		if (stream.str() == "Polynome(0)")
			return "";
		else
			return "Resultat attendu: Polynome(0). Resultat obtenu: " + stream.str() + ".";
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
