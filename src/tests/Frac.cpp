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
	test.addSubTest("Division en place", [](Test& test)->std::string
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

static std::string testComparaison(Test& test)
{
	test.addSubTest("Comparaisons entiers differents de meme signe", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(161803398874989), y(31415926536);

		if (!hasFailed && !(x >= y))
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && y >= x)
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	test.addSubTest("Comparaisons entiers differents de signes differents", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(-161803398874989), y(31415926536);

		if (!hasFailed && !(y >= x))
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && x >= y)
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	test.addSubTest("Comparaisons entiers egaux positifs", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(161803398874989), y(161803398874989);

		if (!hasFailed && !(y >= x))
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && !(x >= y))
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	test.addSubTest("Comparaisons entiers egaux negatifs", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(-161803398874989), y(-161803398874989);

		if (!hasFailed && !(y >= x))
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && !(x >= y))
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	test.addSubTest("Comparaisons autour de zero", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(0), y(-x);

		if (!hasFailed && !(y >= x))
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && !(x >= y))
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		x = -161803398874989;
		y = x - x;
		x -= x;

		if (!hasFailed && !(y >= x))
		{
			hasFailed = true;
			return "La comparaison n°3 a echoue.";
		}

		if (!hasFailed && !(x >= y))
		{
			hasFailed = true;
			return "La comparaison n°4 a echoue.";
		}

		x = -161803398874989;
		x -= x;
		y = 0;

		if (!hasFailed && !(y >= x))
		{
			hasFailed = true;
			return "La comparaison n°5 a echoue.";
		}

		if (!hasFailed && !(x >= y))
		{
			hasFailed = true;
			return "La comparaison n°6 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	return "";
}

static std::string testComparaisonStricte(Test& test)
{
	test.addSubTest("Comparaisons entiers differents de meme signe", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(161803398874989), y(31415926536);

		if (!hasFailed && !(x > y))
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && y > x)
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	test.addSubTest("Comparaisons entiers differents de signes differents", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(-161803398874989), y(31415926536);

		if (!hasFailed && !(y > x))
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && x > y)
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	test.addSubTest("Comparaisons entiers egaux positifs", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(161803398874989), y(161803398874989);

		if (!hasFailed && y > x)
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && x > y)
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	test.addSubTest("Comparaisons entiers egaux negatifs", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(-161803398874989), y(-161803398874989);

		if (!hasFailed && y > x)
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && x > y)
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	test.addSubTest("Comparaisons autour de zero", [](Test& test)->std::string
	{
		bool hasFailed(false);

		Int x(0), y(-x);

		if (!hasFailed && y > x)
		{
			hasFailed = true;
			return "La comparaison n°1 a echoue.";
		}

		if (!hasFailed && x > y)
		{
			hasFailed = true;
			return "La comparaison n°2 a echoue.";
		}

		x = -161803398874989;
		y = x - x;
		x -= x;

		if (!hasFailed && y > x)
		{
			hasFailed = true;
			return "La comparaison n°3 a echoue.";
		}

		if (!hasFailed && x > y)
		{
			hasFailed = true;
			return "La comparaison n°4 a echoue.";
		}

		x = -161803398874989;
		x -= x;
		y = 0;

		if (!hasFailed && y > x)
		{
			hasFailed = true;
			return "La comparaison n°5 a echoue.";
		}

		if (!hasFailed && x > y)
		{
			hasFailed = true;
			return "La comparaison n°6 a echoue.";
		}

		if (!hasFailed)
			return "";
	});

	return "";
}

static std::string testFlux(Test& test)
{
	test.addSubTest("Affichage de 0", [](Test& test)->std::string
	{
		Int x(0);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "0")
			return "";
		else
			return "Resultat attendu: 0. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affichage de -0", [](Test& test)->std::string
	{
		Int x(0);
		std::stringstream stream;
		stream << -x;
		if (stream.str() == "0")
			return "";
		else
			return "Resultat attendu: 0. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affichage d'entiers positifs", [](Test& test)->std::string
	{
		Int x(161803398874989);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "161803398874989")
			return "";
		else
			return "Resultat attendu: 161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affichage d'entiers negatifs", [](Test& test)->std::string
	{
		Int x(-161803398874989);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-161803398874989")
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testRationnels(Test& test)
{
	return "";
}

static std::string testFonctionsRationnels(Test& test)
{
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

	test.addSubTest("Test des operations sur les flux", &testFlux);

	test.addSubTest("Test de la classe Rationnel", &testRationnels);
	test.addSubTest("Test des fonctions définies en même temps que les rationnels", &testFonctionsRationnels);

	test.addSubTest("Test generaux", &testGeneraux);

	return "";
}
