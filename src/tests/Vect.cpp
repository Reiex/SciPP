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
		Int x(31415926536), y(-16180339887);
		x += y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "15235586649")
			return "";
		else
			return "Resultat attendu: 15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Int(Int const&, Int const&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-16180339887), z;
		z = x + y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "15235586649")
			return "";
		else
			return "Resultat attendu: 15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Int&&(Int&&, Int const&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-16180339887), z;
		z = std::move(x) + y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "15235586649")
			return "";
		else
			return "Resultat attendu: 15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Int&&(Int const&, Int&&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-16180339887), z;
		z = x + std::move(y);
		std::stringstream stream;
		stream << z;
		if (y.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "15235586649")
			return "";
		else
			return "Resultat attendu: 15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Addition externe Int&&(Int&&, Int&&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-16180339887), z;
		z = std::move(x) + std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "15235586649")
			return "";
		else
			return "Resultat attendu: 15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testSoustraction(Test& test)
{
	test.addSubTest("Soustraction en place", [](Test& test)->std::string
	{
		Int x(-31415926536), y(-16180339887);
		x -= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-15235586649")
			return "";
		else
			return "Resultat attendu: -15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe Int(Int const&, Int const&)", [](Test& test)->std::string
	{
		Int x(-31415926536), y(-16180339887), z;
		z = x - y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "-15235586649")
			return "";
		else
			return "Resultat attendu: -15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe Int&&(Int&&, Int const&)", [](Test& test)->std::string
	{
		Int x(-31415926536), y(-16180339887), z;
		z = std::move(x) - y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-15235586649")
			return "";
		else
			return "Resultat attendu: -15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe Int&&(Int const&, Int&&)", [](Test& test)->std::string
	{
		Int x(-31415926536), y(-16180339887), z;
		z = x - std::move(y);
		std::stringstream stream;
		stream << z;
		if (y.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-15235586649")
			return "";
		else
			return "Resultat attendu: -15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Soustraction externe Int&&(Int&&, Int&&)", [](Test& test)->std::string
	{
		Int x(-31415926536), y(-16180339887), z;
		z = std::move(x) - std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-15235586649")
			return "";
		else
			return "Resultat attendu: -15235586649. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testMultiplication(Test& test)
{
	test.addSubTest("Multiplication en place", [](Test& test)->std::string
	{
		Int x(31416), y(-1618);
		x *= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-50831088")
			return "";
		else
			return "Resultat attendu: -50831088. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Int(Int const&, Int const&)", [](Test& test)->std::string
	{
		Int x(31416), y(-1618), z;
		z = x * y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "-50831088")
			return "";
		else
			return "Resultat attendu: -50831088. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Int&&(Int&&, Int const&)", [](Test& test)->std::string
	{
		Int x(31416), y(-1618), z;
		z = std::move(x) * y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-50831088")
			return "";
		else
			return "Resultat attendu: -50831088. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Int&&(Int const&, Int&&)", [](Test& test)->std::string
	{
		Int x(31416), y(-1618), z;
		z = x * std::move(y);
		std::stringstream stream;
		stream << z;
		if (y.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-50831088")
			return "";
		else
			return "Resultat attendu: -50831088. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Multiplication externe Int&&(Int&&, Int&&)", [](Test& test)->std::string
	{
		Int x(31416), y(-1618), z;
		z = std::move(x) * std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-50831088")
			return "";
		else
			return "Resultat attendu: -50831088. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testDivision(Test& test)
{
	test.addSubTest("Division en place normale", [](Test& test)->std::string
	{
		Int x(31415926536), y(-1618);
		x /= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-19416518")
			return "";
		else
			return "Resultat attendu: -19416518. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Division par zero", [](Test& test)->std::string
	{
		try
		{
			Int x(31415926536);
			x /= 0;
			std::stringstream stream;
			stream << x;
			return "La division par zero a eu lieu. Valeur obtenue: " + stream.str() + ".";
		}
		catch (Int::ZeroDivisionException& e)
		{
			return "";
		}
	});

	test.addSubTest("Division externe Int(Int const&, Int const&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-1618), z;
		z = x / y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "-19416518")
			return "";
		else
			return "Resultat attendu: -19416518. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Division externe Int&&(Int&&, Int const&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-1618), z;
		z = std::move(x) / y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-19416518")
			return "";
		else
			return "Resultat attendu: -19416518. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Division externe Int&&(Int&&, Int&&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-1618), z;
		z = std::move(x) / std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-19416518")
			return "";
		else
			return "Resultat attendu: -19416518. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testModulo(Test& test)
{
	test.addSubTest("Modulo en place normal", [](Test& test)->std::string
	{
		Int x(31415926536), y(-1618);
		x %= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "412")
			return "";
		else
			return "Resultat attendu: 412. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Modulo par zero", [](Test& test)->std::string
	{
		try
		{
			Int x(31415926536);
			x %= 0;
			std::stringstream stream;
			stream << x;
			return "Le modulo par zero a eu lieu. Valeur obtenue: " + stream.str() + ".";
		}
		catch (Int::ZeroDivisionException& e)
		{
			return "";
		}
	});

	test.addSubTest("Modulo externe Int(Int const&, Int const&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-1618), z;
		z = x % y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "412")
			return "";
		else
			return "Resultat attendu: 412. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Modulo externe Int&&(Int&&, Int const&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-1618), z;
		z = std::move(x) % y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "412")
			return "";
		else
			return "Resultat attendu: 412. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Modulo externe Int&&(Int&&, Int&&)", [](Test& test)->std::string
	{
		Int x(31415926536), y(-1618), z;
		z = std::move(x) % std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "412")
			return "";
		else
			return "Resultat attendu: 412. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testUnaires(Test& test)
{
	test.addSubTest("Moins unaire par creation d'un nouvel Int", [](Test& test)->std::string
	{
		Int x(161803398874989), y;
		y = -x;
		std::stringstream stream;
		stream << y;
		if (stream.str() == "-161803398874989")
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Plus unaire par creation d'un nouvel Int", [](Test& test)->std::string
	{
		Int x(161803398874989), y;
		y = +x;
		std::stringstream stream;
		stream << y;
		if (stream.str() == "161803398874989")
			return "";
		else
			return "Resultat attendu: 161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Moins unaire par deplacement", [](Test& test)->std::string
	{
		Int x(161803398874989), y;
		y = -std::move(x);
		std::stringstream stream;
		stream << y;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-161803398874989")
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Plus unaire par deplacement", [](Test& test)->std::string
	{
		Int x(161803398874989), y;
		y = +std::move(x);
		std::stringstream stream;
		stream << y;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "161803398874989")
			return "";
		else
			return "Resultat attendu: 161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testEgalite(Test& test)
{
	test.addSubTest("Comparaisons entiers egaux", [](Test& test)->std::string
	{
		Int x(161803398874989), y(161803398874989);
		if (x == y)
			return "";
		else
			return "Le test d'egalite ne renvoie pas le resultat attendu.";
	});

	test.addSubTest("Comparaisons entiers egaux apres operations", [](Test& test)->std::string
	{
		Int x(161803398874989), y(161803398874989);
		x = (x + 3 % 50) * (x + 10) * (x - 12) * x / 7;
		y = (y + 3 % 50) * (y + 10) * (y - 12) * y / 7;
		if (x == y)
			return "";
		else
			return "Le test d'egalite ne renvoie pas le resultat attendu.";
	});

	test.addSubTest("Comparaisons entiers differents", [](Test& test)->std::string
	{
		Int x(161803398874989), y(-161803398874989);
		if (x != y)
			return "";
		else
			return "Le test d'egalite ne renvoie pas le resultat attendu.";
	});

	test.addSubTest("Comparaisons autour de zero", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(0), y(-x);
		if (!hasFailed && x != y)
		{
			hasFailed = true;
			return "Le test n°1 d'egalite ne renvoie pas le resultat attendu.";
		}

		x = -161803398874989;
		y = x - x;
		x -= x;
		if (!hasFailed && x != y)
		{
			hasFailed = true;
			return "Le test n°2 d'egalite ne renvoie pas le resultat attendu.";
		}

		x = -161803398874989;
		x -= x;
		y = 0;
		if (!hasFailed && x != y)
		{
			hasFailed = true;
			return "Le test n°3 d'egalite ne renvoie pas le resultat attendu.";
		}

		if (!hasFailed)
			return "";

	});

	return "";
}

static std::string testGeneraux(Test& test)
{
	test.addSubTest("Test aller-retour factorielle", [](Test& test)->std::string
	{
		Int x(1);
		for (int i(1); i < 300; i++)
			x *= i;

		for (unsigned long long int i(299); i > 0; i--)
			x /= i;

		std::stringstream stream;
		stream << x;
		if (stream.str() == "1")
			return "";
		else
			return "La valeur obtenue n'est pas celle attendue. Valeur attendue: 1. Valeur obtenue: " + stream.str();
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
