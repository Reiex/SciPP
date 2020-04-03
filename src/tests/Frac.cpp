#include "main.h"


static std::string testInit(Test& test)
{
	test.addSubTest("Initialisation par defaut", [](Test& test)->std::string
	{
		Frac<long long int> x;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(0/1)")
			return "";
		else
			return "Resultat attendu: (0/1). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation entier nul", [](Test& test)->std::string
	{
		Frac<long long int> x(0);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(0/1)")
			return "";
		else
			return "Resultat attendu: (0/1). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation entier positif", [](Test& test)->std::string
	{
		Frac<long long int> x(1618);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(1618/1)")
			return "";
		else
			return "Resultat attendu: (1618/1). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation entier negatif", [](Test& test)->std::string
	{
		Frac<long long int> x(-1618);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(-1618/1)")
			return "";
		else
			return "Resultat attendu: (-1618/1). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation T const&", [](Test& test)->std::string
	{
		Frac<long long int> x((long long int) 161803398874989);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(161803398874989/1)")
			return "";
		else
			return "Resultat attendu: (161803398874989/1). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation (T const&, T const&)", [](Test& test)->std::string
	{
		Frac<long long int> x(161803398874989, 31415926535);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(161803398874989/31415926535)")
			return "";
		else
			return "Resultat attendu: (161803398874989/31415926535). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation (T const&, T(0))", [](Test& test)->std::string
	{
		try
		{
			Frac<long long int> x(161803398874989, 0);
			return "La fraction a ete accepte avec 0 comme denominateur";
		}
		catch (Frac<long long int>::ZeroDivisionException& e)
		{
			return "";
		}
	});

	return "";
}

static std::string testSimplification(Test& test)
{
	test.addSubTest("Simplification (int > 0, int > 0)", [](Test& test)->std::string
	{
		Frac<long long int> x(11067, 5115);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(119/55)")
			return "";
		else
			return "Resultat attendu: (119/55). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Simplification (0, int > 0)", [](Test& test)->std::string
	{
		Frac<long long int> x(0, 5115);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(0/1)")
			return "";
		else
			return "Resultat attendu: (0/1). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Simplification (int < 0, int > 0)", [](Test& test)->std::string
	{
		Frac<long long int> x(-11067, 5115);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(-119/55)")
			return "";
		else
			return "Resultat attendu: (-119/55). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Simplification (int > 0, int < 0)", [](Test& test)->std::string
	{
		Frac<long long int> x(11067, -5115);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(-119/55)")
			return "";
		else
			return "Resultat attendu: (-119/55). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Simplification (int < 0, int < 0)", [](Test& test)->std::string
	{
		Frac<long long int> x(-11067, -5115);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(119/55)")
			return "";
		else
			return "Resultat attendu: (119/55). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testAddition(Test& test)
{
	test.addSubTest("Addition en place", [](Test& test)->std::string
	{
		Frac<long long int> x(231, 185), y(715, 399);
		x += y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(224444/73815)")
			return "";
		else
			return "Resultat attendu: (224444/73815). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe", [](Test& test)->std::string
	{
		Frac<long long int> x(231, 185), y(715, 399), z;
		z = x + y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "(224444/73815)")
			return "";
		else
			return "Resultat attendu: (224444/73815). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testSoustraction(Test& test)
{
	test.addSubTest("Soustraction en place", [](Test& test)->std::string
	{
		Frac<long long int> x(231, 185), y(715, 399);
		x -= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(-40106/73815)")
			return "";
		else
			return "Resultat attendu: (-40106/73815). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe", [](Test& test)->std::string
	{
		Frac<long long int> x(231, 185), y(715, 399), z;
		z = x - y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "(-40106/73815)")
			return "";
		else
			return "Resultat attendu: (-40106/73815). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testMultiplication(Test& test)
{
	test.addSubTest("Multiplication en place", [](Test& test)->std::string
	{
		Frac<long long int> x(231, 185), y(715, 399);
		x *= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(1573/703)")
			return "";
		else
			return "Resultat attendu: (1573/703). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe", [](Test& test)->std::string
	{
		Frac<long long int> x(231, 185), y(715, 399), z;
		z = x * y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "(1573/703)")
			return "";
		else
			return "Resultat attendu: (1573/703). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testDivision(Test& test)
{
	test.addSubTest("Division en place", [](Test& test)->std::string
	{
		Frac<long long int> x(231, 185), y(715, 399);
		x /= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "(8379/12025)")
			return "";
		else
			return "Resultat attendu: (8379/12025). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Division externe", [](Test& test)->std::string
	{
		Frac<long long int> x(231, 185), y(715, 399), z;
		z = x / y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "(8379/12025)")
			return "";
		else
			return "Resultat attendu: (8379/12025). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testUnaires(Test& test)
{
	test.addSubTest("Moins unaire", [](Test& test)->std::string
	{
		Frac<long long int> x(161803398874989, 31415926535), y;
		y = -x;
		std::stringstream stream;
		stream << y;
		if (stream.str() == "(-161803398874989/31415926535)")
			return "";
		else
			return "Resultat attendu: (-161803398874989/31415926535). Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Plus unaire", [](Test& test)->std::string
	{
		Frac<long long int> x(161803398874989, 31415926535), y;
		y = +x;
		std::stringstream stream;
		stream << y;
		if (stream.str() == "(161803398874989/31415926535)")
			return "";
		else
			return "Resultat attendu: (161803398874989/31415926535). Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testEgalite(Test& test)
{
	test.addSubTest("Egalite fractions egales", [](Test& test)->std::string
	{
		Frac<long long int> x(499, 500), y(499, 500);

		if (!(x == y))
			return "Le booleen renvoye n'est pas le bon";
		else
			return "";
	});

	test.addSubTest("Egalite fractions differentes", [](Test& test)->std::string
	{
		Frac<long long int> x(499, 500), y(498, 499);

		if (x == y)
			return "Le booleen renvoye n'est pas le bon";
		else
			return "";
	});

	test.addSubTest("Difference fractions egales", [](Test& test)->std::string
	{
		Frac<long long int> x(499, 500), y(499, 500);

		if (x != y)
			return "Le booleen renvoye n'est pas le bon";
		else
			return "";
	});

	test.addSubTest("Difference fractions differentes", [](Test& test)->std::string
	{
		Frac<long long int> x(499, 500), y(498, 499);

		if (!(x != y))
			return "Le booleen renvoye n'est pas le bon";
		else
			return "";
	});

	return "";
}

static std::string testComparaison(Test& test)
{
	test.addSubTest("Comparaison fractions egales", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Frac<long long int> x(499, 500), y(499, 500);
		std::string r("");

		if (!(x >= y))
			r += "La comparaison n°1 a echoue. ";
		if (!(y >= x))
			r += "La comparaison n°2 a echoue. ";
		if (!(x <= y))
			r += "La comparaison n°3 a echoue. ";
		if (!(y <= x))
			r += "La comparaison n°4 a echoue. ";

		return r;
	});

	test.addSubTest("Comparaison fractions differentes", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Frac<long long int> x(499, 500), y(498, 499);
		std::string r("");

		if (!(x >= y))
			r += "La comparaison n°1 a echoue. ";
		if (y >= x)
			r += "La comparaison n°2 a echoue. ";
		if (x <= y)
			r += "La comparaison n°3 a echoue. ";
		if (!(y <= x))
			r += "La comparaison n°4 a echoue. ";

		return r;
	});

	return "";
}

static std::string testComparaisonStricte(Test& test)
{
	test.addSubTest("Comparaison fractions egales", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Frac<long long int> x(499, 500), y(499, 500);
		std::string r("");

		if (x > y)
			r += "La comparaison n°1 a echoue. ";
		if (y > x)
			r += "La comparaison n°2 a echoue. ";
		if (x < y)
			r += "La comparaison n°3 a echoue. ";
		if (y < x)
			r += "La comparaison n°4 a echoue. ";

		return r;
	});

	test.addSubTest("Comparaison fractions differentes", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Frac<long long int> x(499, 500), y(498, 499);
		std::string r("");

		if (!(x > y))
			r += "La comparaison n°1 a echoue. ";
		if (y > x)
			r += "La comparaison n°2 a echoue. ";
		if (x < y)
			r += "La comparaison n°3 a echoue. ";
		if (!(y < x))
			r += "La comparaison n°4 a echoue. ";

		return r;
	});

	return "";
}

static std::string testRationnels(Test& test)
{
	test.addSubTest("Construction a partir d'un double", [](Test& test)->std::string
	{
		Rationnel x(3.141592653589793);
		std::string r("");
		if (x != Rationnel(3141592653589793, 1000000000000000))
			r += "Resultat attendu: (3141592653589793/1000000000000000). Resultat obtenu: (" + x.numerateur().toString() + ", " + x.denominateur().toString() + "). ";

		x = Rationnel(13325509.141592653589793);
		if (x != Rationnel(1332550914159265, 100000000))
			r += "Resultat attendu: (266510182831853/20000000). Resultat obtenu: (" + x.numerateur().toString() + ", " + x.denominateur().toString() + "). ";

		x = Rationnel(-13325509.141592653589793);
		if (x != Rationnel(-1332550914159265, 100000000))
			r += "Resultat attendu: (-266510182831853/20000000). Resultat obtenu: (" + x.numerateur().toString() + ", " + x.denominateur().toString() + "). ";

		return r;
	});

	return "";
}

static std::string testFonctionsRationnels(Test& test)
{
	test.addSubTest("Extraction des decimales - Nombre decimal", [](Test& test)->std::string
	{
		Rationnel x(3.1415926);
		std::string xString(decimales(x, 2)), r("");
		if (xString != "3.14")
			r += "La valeur obtenue n'est pas celle attendue. Valeur attendue: 3.14. Valeur obtenue: " + xString + ". ";

		xString = decimales(x, 20);
		if (xString != "3.14159260000000000000")
			r+= "La valeur obtenue n'est pas celle attendue. Valeur attendue: 3.14159260000000000000. Valeur obtenue: " + xString;

		return r;
	});

	test.addSubTest("Extraction des decimales - Nombre rationnel", [](Test& test)->std::string
	{
		Rationnel x(5, 7);
		std::string xString(decimales(x, 20));
		if (xString != "0.71428571428571428571")
			return "La valeur obtenue n'est pas celle attendue. Valeur attendue: 0.71428571428571428571. Valeur obtenue: " + xString;

		return "";
	});

	return "";
}

static std::string testGeneraux(Test& test)
{
	test.addSubTest("Factorielle", [](Test& test)->std::string
	{
		Rationnel x(1);
		for (int i(1); i < 300; i++)
			x *= Rationnel(i, 300 - i);

		std::stringstream stream;
		stream << x;
		if (stream.str() == "1")
			return "";
		else
			return "La valeur obtenue n'est pas celle attendue. Valeur attendue: 1. Valeur obtenue: " + stream.str();
	});

	return "";
}

std::string mainFrac(Test& test)
{
	test.addSubTest("Test des initialisations", &testInit);
	test.addSubTest("Test de la simplification des fractions", &testSimplification);

	test.addSubTest("Test des additions", &testAddition);
	test.addSubTest("Test des soustractions", &testSoustraction);
	test.addSubTest("Test des multiplications", &testMultiplication);
	test.addSubTest("Test des divisions", &testDivision);
	test.addSubTest("Test des plus et moins unaires", &testUnaires);

	test.addSubTest("Test des operateurs == et !=", &testEgalite);
	test.addSubTest("Test des operateurs <= et >=", &testComparaison);
	test.addSubTest("Test des operateurs < et >", &testComparaisonStricte);

	test.addSubTest("Test de la classe Rationnel", &testRationnels);
	test.addSubTest("Test des fonctions définies en meme temps que les rationnels", &testFonctionsRationnels);

	test.addSubTest("Test generaux", &testGeneraux);

	return "";
}
