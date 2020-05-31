#include "main.h"

static std::string testInit(Test& test)
{
	test.addSubTest("Initialisation par defaut", [](Test& test)->std::string
	{
		Vect<int> x;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<>")
			return "";
		else
			return "Resultat attendu: <>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation taille nulle", [](Test& test)->std::string
	{
		Vect<int> x(0);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<>")
			return "";
		else
			return "Resultat attendu: <>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation taille normale", [](Test& test)->std::string
	{
		Vect<int> x(10);
		std::stringstream stream;
		std::string r;
		stream << x;
		if (stream.str() != "<0, 0, 0, 0, 0, 0, 0, 0, 0, 0>")
			r += "Resultat attendu: <0, 0, 0, 0, 0, 0, 0, 0, 0, 0>. Resultat obtenu: " + stream.str() + ". ";
		
		if (x.size() != 10)
			r += "Taille anormale. Resultat attendu: 10. Resultat obtenu: " + std::to_string(x.size()) + ". ";

		return r;
	});

	test.addSubTest("Initialisation par copie", [](Test& test)->std::string
	{
		Vect<int> x(3), y(x);
		std::stringstream stream;
		stream << y;
		if (stream.str() == "<0, 0, 0>")
			return "";
		else
			return "Resultat attendu: <0, 0, 0>. Resultat obtenu: " + stream.str() + ". ";
	});

	test.addSubTest("Initialisation par deplacement", [](Test& test)->std::string
	{
		Vect<int> x(3), y(std::move(x));
		std::stringstream stream;
		std::string r;
		stream << y;
		if (stream.str() != "<0, 0, 0>")
			r += "Resultat de y attendu: <0, 0, 0>. Resultat obtenu: " + stream.str() + ". ";
		if (x.size() != 0)
			r += "Le vecteur d'origine n'a pas ete deplace. ";

		return r;
	});

	test.addSubTest("Initialisation par liste d'initialisation vide", [](Test& test)->std::string
	{
		Vect<int> x({ });
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<>")
			return "";
		else
			return "Resultat attendu: <>. Resultat obtenu: " + stream.str() + ". ";
	});

	test.addSubTest("Initialisation par liste d'initialisation normale", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 2, 3, 4, 5 });
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<1, 2, 3, 4, 5>")
			return "";
		else
			return "Resultat attendu: <1, 2, 3, 4, 5>. Resultat obtenu: " + stream.str() + ". ";
	});

	test.addSubTest("Initialisation par tableau C", [](Test& test)->std::string
	{
		int tab[5] = { 1, 2, 3, 4, 5 };
		Vect<int> x(tab, 5);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "<1, 2, 3, 4, 5>")
			return "";
		else
			return "Resultat attendu: <1, 2, 3, 4, 5>. Resultat obtenu: " + stream.str() + ". ";
	});

	return "";
}

static std::string testAffectation(Test& test)
{
	test.addSubTest("Affectation par copie", [](Test& test)->std::string
	{
		Vect<int> x({1, 6, 1, 8, 0, 3}), y;
		y = x;
		std::stringstream stream;
		stream << y;
		if (stream.str() == "<1, 6, 1, 8, 0, 3>")
			return "";
		else
			return "Resultat attendu: <1, 6, 1, 8, 0, 3>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affectation par deplacement", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y;
		y = std::move(x);
		std::stringstream stream;
		std::string r;
		stream << y;
		if (stream.str() != "<1, 6, 1, 8, 0, 3>")
			r += "Resultat attendu: <1, 6, 1, 8, 0, 3>. Resultat obtenu: " + stream.str() + ". ";
		if (x.size() != 0)
			r += "Le vecteur d'origine n'a pas ete deplace. ";

		return r;
	});

	test.addSubTest("Affectation chainee par copie", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y, z, t;
		t = z = y = x;
		std::stringstream stream;
		stream << t;
		if (stream.str() == "<1, 6, 1, 8, 0, 3>")
			return "";
		else
			return "Resultat attendu: <1, 6, 1, 8, 0, 3>. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affectation chainee par deplacement et copie", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 6, 1, 8, 0, 3 }), y, z, t;
		t = std::move(z = y = x);
		std::stringstream stream;
		std::string r;
		stream << t;
		if (x.size() == 0 || y.size() == 0)
			r += "Un deplacement inattendu a eu lieu. ";
		if (z.size() != 0)
			r += "Le deplacement n'a pas eu lieu, un entier deplace est toujours actif. ";
		else if (stream.str() != "<1, 6, 1, 8, 0, 3>")
			r += "Resultat attendu: <1, 6, 1, 8, 0, 3>. Resultat obtenu: " + stream.str() + ". ";

		return r;
	});

	return "";
}

static std::string testDestructeur(Test& test)
{
	test.addSubTest("Destruction d'un vecteur simple", [](Test& test)->std::string
	{
		Vect<int>* x(new Vect<int>({1, 6, 1, 8, 0, 3}));
		delete x;
		return "";
	});

	test.addSubTest("Destruction d'un vecteur cree par copie et de son original", [](Test& test)->std::string
	{
		Vect<int> *x(new Vect<int>({ 1, 6, 1, 8, 0, 3 })), *y(new Vect<int>(*x));
		delete x;
		delete y;
		return "";
	});

	test.addSubTest("Destruction d'un vecteur cree par deplacement et de son original", [](Test& test)->std::string
	{
		Vect<int> *x(new Vect<int>({ 1, 6, 1, 8, 0, 3 })), *y(new Vect<int>(std::move(*x)));
		delete x;
		delete y;
		return "";
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
	test.addSubTest("Produit scalaire", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 1, 0, 1, 1, 0, 1 }), y({ 1, 0, -1, 0, 1, 0, -1 });
		int z(x * y);
		if (z == 1)
			return "";
		else
			return "Resultat attendu: 1. Resultat obtenu: " + std::to_string(z) + ". ";
	});

	test.addSubTest("Produit vectoriel", [](Test& test)->std::string
	{
		Vect<int> x({ 1, 0, 0}), y({ 0, 1, 0 }), z(x^y);
		std::stringstream stream;
		stream << z;
		if (stream.str() == "<0, 0, 1>")
			return "";
		else
			return "Resultat attendu: <0, 0, 1>. Resultat obtenu: " + stream.str() + ". ";
	});

	return "";
}

std::string mainVect(Test& test)
{
	test.addSubTest("Test des initialisations", &testInit);
	test.addSubTest("Test des affectations", &testAffectation);
	test.addSubTest("Test du destructeur", &testDestructeur);

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
