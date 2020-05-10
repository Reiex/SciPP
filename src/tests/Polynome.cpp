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
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4, 1, 5, 9 });
		x += y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<4, 7, 5, 9, 5, 12>")
			return "";
		else
			return "Resultat attendu: <4, 7, 5, 9, 5, 12>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Vect(Vect const&, Vect const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4, 1, 5, 9 }), z;
		z = x + y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "<4, 7, 5, 9, 5, 12>")
			return "";
		else
			return "Resultat attendu: <4, 7, 5, 9, 5, 12>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Vect&&(Vect&&, Vect const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4, 1, 5, 9 }), z;
		z = std::move(x) + y;
		std::stringstream stream;
		std::string r;
		stream << z;
		if (x.size() != 0)
			r += "Le deplacement n'a pas eu lieu, le vecteur de depart est toujours actif. ";
		else if (stream.str() != "<4, 7, 5, 9, 5, 12>")
			r += "Resultat attendu: <4, 7, 5, 9, 5, 12>. Resultat obtenu: " + stream.str() + ".";

		return r;
	});

	test.addSubTest("Addition externe Vect&&(Vect const&, Vect&&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4, 1, 5, 9 }), z;
		z = x + std::move(y);
		std::stringstream stream;
		std::string r;
		stream << z;
		if (y.size() != 0)
			r += "Le deplacement n'a pas eu lieu, le vecteur de depart est toujours actif. ";
		else if (stream.str() != "<4, 7, 5, 9, 5, 12>")
			r += "Resultat attendu: <4, 7, 5, 9, 5, 12>. Resultat obtenu: " + stream.str() + ".";

		return r;
	});

	test.addSubTest("Addition externe Vect&&(Vect&&, Vect&&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4, 1, 5, 9 }), z;
		z = std::move(x) + std::move(y);
		std::stringstream stream;
		std::string r;
		stream << z;
		if (x.size() != 0)
			r += "Le deplacement n'a pas eu lieu, le vecteur de depart est toujours actif. ";
		else if (stream.str() != "<4, 7, 5, 9, 5, 12>")
			r += "Resultat attendu: <4, 7, 5, 9, 5, 12>. Resultat obtenu: " + stream.str() + ".";

		return r;
	});

	return "";
}

static std::string testSoustraction(Test& test)
{
	test.addSubTest("Soustraction en place", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4, 1, 5, 9 });
		x -= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<-2, 5, -3, 7, -5, -6>")
			return "";
		else
			return "Resultat attendu: <-2, 5, -3, 7, -5, -6>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe Vect(Vect const&, Vect const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4, 1, 5, 9 }), z;
		z = x - y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "<-2, 5, -3, 7, -5, -6>")
			return "";
		else
			return "Resultat attendu: <-2, 5, -3, 7, -5, -6>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe Vect&&(Vect&&, Vect const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4, 1, 5, 9 }), z;
		z = std::move(x) - y;
		std::stringstream stream;
		std::string r;
		stream << z;
		if (x.size() != 0)
			r += "Le deplacement n'a pas eu lieu, le vecteur de depart est toujours actif. ";
		else if (stream.str() != "<-2, 5, -3, 7, -5, -6>")
			r += "Resultat attendu: <-2, 5, -3, 7, -5, -6>. Resultat obtenu: " + stream.str() + ".";

		return r;
	});

	test.addSubTest("Soustraction externe Vect&&(Vect&&, Vect&&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 3, 1, 4, 1, 5, 9 }), z;
		z = std::move(x) - std::move(y);
		std::stringstream stream;
		std::string r;
		stream << z;
		if (x.size() != 0)
			r += "Le deplacement n'a pas eu lieu, le vecteur de depart est toujours actif. ";
		else if (stream.str() != "<-2, 5, -3, 7, -5, -6>")
			r += "Resultat attendu: <-2, 5, -3, 7, -5, -6>. Resultat obtenu: " + stream.str() + ".";

		return r;
	});

	return "";
}

static std::string testMultiplication(Test& test)
{
	test.addSubTest("Multiplication en place par un scalaire", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 });
		int y(3);
		x *= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<3, 18, 3, 24, 0, 9>")
			return "";
		else
			return "Resultat attendu: <3, 18, 3, 24, 0, 9>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Vect(Vect const&, T const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), z;
		int y(3);
		z = x * y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "<3, 18, 3, 24, 0, 9>")
			return "";
		else
			return "Resultat attendu: <3, 18, 3, 24, 0, 9>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Vect(T const&, Vect const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), z;
		int y(3);
		z = y * x;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "<3, 18, 3, 24, 0, 9>")
			return "";
		else
			return "Resultat attendu: <3, 18, 3, 24, 0, 9>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Vect&&(Vect&&, T const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), z;
		int y(3);
		z = std::move(x) * y;
		std::stringstream stream;
		std::string r;
		stream << z;
		if (stream.str() != "<3, 18, 3, 24, 0, 9>")
			r += "Resultat attendu: <3, 18, 3, 24, 0, 9>. Resultat obtenu: " + stream.str() + ". ";
		if (x.size() != 0)
			r += "Le deplacement n'a pas eu lieu. ";

		return r;
	});

	test.addSubTest("Multiplication externe Vect&&(T const&, Vect&&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), z;
		int y(3);
		z = y * std::move(x);
		std::stringstream stream;
		std::string r;
		stream << z;
		if (stream.str() != "<3, 18, 3, 24, 0, 9>")
			r += "Resultat attendu: <3, 18, 3, 24, 0, 9>. Resultat obtenu: " + stream.str() + ". ";
		if (x.size() != 0)
			r += "Le deplacement n'a pas eu lieu. ";

		return r;
	});

	return "";
}

static std::string testDivision(Test& test)
{
	test.addSubTest("Division en place par un scalaire", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 });
		int y(2);
		x /= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<0, 3, 0, 4, 0, 1>")
			return "";
		else
			return "Resultat attendu: <0, 3, 0, 4, 0, 1>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Division externe Vect(Vect const&, T const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), z;
		int y(2);
		z = x / y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "<0, 3, 0, 4, 0, 1>")
			return "";
		else
			return "Resultat attendu: <0, 3, 0, 4, 0, 1>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Division externe Vect&&(Vect&&, T const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), z;
		int y(2);
		z = std::move(x) / y;
		std::stringstream stream;
		std::string r;
		stream << z;
		if (stream.str() != "<0, 3, 0, 4, 0, 1>")
			r += "Resultat attendu: <0, 3, 0, 4, 0, 1>. Resultat obtenu: " + stream.str() + ". ";
		if (x.size() != 0)
			r += "Le deplacement n'a pas eu lieu. ";

		return r;
	});

	return "";
}

static std::string testModulo(Test& test)
{
	test.addSubTest("Modulo en place par un scalaire", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 });
		int y(5);
		x %= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<1, 1, 1, 3, 0, 3>")
			return "";
		else
			return "Resultat attendu: <1, 1, 1, 3, 0, 3>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Modulo externe Vect(Vect const&, T const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), z;
		int y(5);
		z = x % y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "<1, 1, 1, 3, 0, 3>")
			return "";
		else
			return "Resultat attendu: <1, 1, 1, 3, 0, 3>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Modulo externe Vect&&(Vect&&, T const&)", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), z;
		int y(5);
		z = std::move(x) % y;
		std::stringstream stream;
		std::string r;
		stream << z;
		if (stream.str() != "<1, 1, 1, 3, 0, 3>")
			r += "Resultat attendu: <1, 1, 1, 3, 0, 3>. Resultat obtenu: " + stream.str() + ". ";
		if (x.size() != 0)
			r += "Le deplacement n'a pas eu lieu. ";

		return r;
	});

	return "";
}

static std::string testUnaires(Test& test)
{
	test.addSubTest("Moins unaire", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y;
		y = -x;
		std::stringstream stream;
		stream << y;
		if (stream.str() == "<-1, -6, -1, -8, 0, -3>")
			return "";
		else
			return "Resultat attendu: <-1, -6, -1, -8, 0, -3>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Plus unaire", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y;
		y = +x;
		std::stringstream stream;
		stream << y;
		if (stream.str() == "<1, 6, 1, 8, 0, 3>")
			return "";
		else
			return "Resultat attendu: <1, 6, 1, 8, 0, 3>. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testEgalite(Test& test)
{
	test.addSubTest("Comparaisons vecteurs egaux", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 1, 6, 1, 8, 0, 3 });
		if (x == y)
			return "";
		else
			return "Le test d'egalite ne renvoie pas le resultat attendu.";
	});

	test.addSubTest("Comparaisons vecteurs differents", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y({ 1, 6, 1, 8, 0, 4 });
		if (x != y)
			return "";
		else
			return "Le test d'egalite ne renvoie pas le resultat attendu.";
	});

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
