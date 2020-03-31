#include "main.h"

std::string testInit(Test& test)
{
	test.addSubTest("Initialisation par defaut", [](Test& test)->std::string
	{
		Int x;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "0")
			return "";
		else
			return "Resultat attendu: 0. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation entier nul", [](Test& test)->std::string
	{
		Int x(0);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "0")
			return "";
		else
			return "Resultat attendu: 0. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation entier positif", [](Test& test)->std::string
	{
		Int x(161803398874989);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "161803398874989")
			return "";
		else
			return "Resultat attendu: 161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation entier negatif", [](Test& test)->std::string
	{
		Int x(-161803398874989);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-161803398874989")
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation par copie", [](Test& test)->std::string
	{
		Int x(31415926535), y(x);
		std::stringstream stream;
		stream << y;
		if (stream.str() == "31415926535")
			return "";
		else
			return "Resultat attendu: 31415926535. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation par deplacement", [](Test& test)->std::string
	{
		Int x(31415926535), y(std::move(x));
		std::stringstream stream;
		stream << y;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "31415926535")
			return "";
		else
			return "Resultat attendu: 31415926535. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

std::string testAffectation(Test& test)
{
	test.addSubTest("Affectation par copie", [](Test& test)->std::string
	{
		Int x(-161803398874989), y;
		y = x;
		std::stringstream stream;
		stream << y;
		if (stream.str() == "-161803398874989")
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affectation par deplacement", [](Test& test)->std::string
	{
		Int x(-161803398874989), y;
		y = std::move(x);
		std::stringstream stream;
		stream << y;
		if (x.estActif())
			return "Le deplacement n'a pas eu lieu, l'entier de depart est toujours actif.";
		else if (stream.str() == "-161803398874989")
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affectation chainee par copie", [](Test& test)->std::string
	{
		Int x(-161803398874989), y, z, t;
		t = z = y = x;
		std::stringstream stream;
		stream << t;
		if (stream.str() == "-161803398874989")
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affectation chainee par deplacement et copie", [](Test& test)->std::string
	{
		Int x(-161803398874989), y, z, t;
		t = std::move(z = y = x);
		std::stringstream stream;
		stream << t;
		if (!x.estActif() || !y.estActif())
			return "Un deplacement inattendu a eu lieu.";
		if (z.estActif())
			return "Le deplacement n'a pas eu lieu, un entier deplace est toujours actif.";
		else if (stream.str() == "-161803398874989")
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affectation par un entier immediat", [](Test& test)->std::string
	{
		Int x;
		x = -161803398874989;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-161803398874989")
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

std::string testAddition(Test& test)
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

std::string testSoustraction(Test& test)
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

std::string testMultiplication(Test& test)
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

std::string testDivision(Test& test)
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

std::string testModulo(Test& test)
{
	test.addSubTest("Modulo en place", [](Test& test)->std::string
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

std::string testUnaires(Test& test)
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

std::string testConversionInt(Test& test)
{
	test.addSubTest("Conversion entier positif", [](Test& test)->std::string
	{
		Int x(161803398874989);
		if (x.toInt() == 161803398874989)
			return "";
		else
			return "Resultat attendu: 161803398874989. Resultat obtenu: " + std::to_string(x.toInt()) + ".";
	});

	test.addSubTest("Conversion entier negatif", [](Test& test)->std::string
	{
		Int x(-161803398874989);
		if (x.toInt() == -161803398874989)
			return "";
		else
			return "Resultat attendu: -161803398874989. Resultat obtenu: " + std::to_string(x.toInt()) + ".";
	});

	test.addSubTest("Conversion entier nul", [](Test& test)->std::string
	{
		Int x(0);
		if (x.toInt() == 0)
			return "";
		else
			return "Resultat attendu: 0. Resultat obtenu: " + std::to_string(x.toInt()) + ".";
	});

	test.addSubTest("Conversion entier maximal", [](Test& test)->std::string
	{
		Int x(LLONG_MAX);
		if (x.toInt() == LLONG_MAX)
			return "";
		else
			return "Resultat attendu: " + std::to_string(LLONG_MAX) + ". Resultat obtenu: " + std::to_string(x.toInt()) + ".";
	});

	test.addSubTest("Conversion entier minimal", [](Test& test)->std::string
	{
		Int x(LLONG_MIN);
		if (x.toInt() == LLONG_MIN)
			return "";
		else
			return "Resultat attendu: " + std::to_string(LLONG_MIN) + ". Resultat obtenu: " + std::to_string(x.toInt()) + ".";
	});

	test.addSubTest("Conversion entier minimal trop grand", [](Test& test)->std::string
	{
		Int x(LLONG_MAX);
		x += 1;
		try
		{
			x.toInt();
			return "L'entier minimal trop grand a ete converti en un Int: " + std::to_string(x.toInt()) + ".";
		}
		catch (Int::IntTooBigException& e)
		{
			return "";
		}
	});

	test.addSubTest("Conversion entier maximal trop petit", [](Test& test)->std::string
	{
		Int x(LLONG_MIN);
		x -= 1;
		try
		{
			x.toInt();
			return "L'entier maximal trop petit a ete converti en un Int: " + std::to_string(x.toInt()) + ".";
		}
		catch (Int::IntTooBigException& e)
		{
			return "";
		}
	});

	test.addSubTest("Conversion entier trop grand", [](Test& test)->std::string
	{
		Int x(LLONG_MAX);
		x = (x + 2) * (x + 5) * (x + 12);
		try
		{
			x.toInt();
			return "Un entier trop grand a ete converti en un Int: " + std::to_string(x.toInt()) + ".";
		}
		catch (Int::IntTooBigException& e)
		{
			return "";
		}
	});

	test.addSubTest("Conversion entier trop petit", [](Test& test)->std::string
	{
		Int x(LLONG_MIN);
		x = (x + 2) * (x + 5) * (x + 12);
		try
		{
			x.toInt();
			return "Un entier trop petit a ete converti en un Int: " + std::to_string(x.toInt()) + ".";
		}
		catch (Int::IntTooBigException& e)
		{
			return "";
		}
	});

	return "";
}

std::string testEgalite(Test& test)
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

std::string testComparaison(Test& test)
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

std::string testComparaisonStricte(Test& test)
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

std::string testFlux(Test& test)
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

std::string testDestructeur(Test& test)
{
	test.addSubTest("Destruction d'un entier simple", [](Test& test)->std::string
	{
		Int* x(new Int(161803398874989));
		delete x;
		return "";
	});

	test.addSubTest("Destruction d'un entier cree par copie et de son original", [](Test& test)->std::string
	{
		Int* x(new Int(161803398874989)), *y(new Int(*x));
		delete x;
		delete y;
		return "";
	});

	test.addSubTest("Destruction d'un entier cree par deplacement et de son original", [](Test& test)->std::string
	{
		Int* x(new Int(161803398874989)), *y(new Int(std::move(*x)));
		delete x;
		delete y;
		return "";
	});

	return "";
}

std::string testFonctionsInt(Test& test)
{
	test.addSubTest("Test expoRapide simple", [](Test& test)->std::string
	{
		int x(expoRapide(2, 16));
		if (x == 65536)
			return "";
		else
			return "Resultat attendu: 65536. Resultat obtenu: " + std::to_string(x) + ".";
	});

	test.addSubTest("Test expoRapide negatif", [](Test& test)->std::string
	{
		int x(expoRapide(-2, 11));
		if (x == -2048)
			return "";
		else
			return "Resultat attendu: -2048. Resultat obtenu: " + std::to_string(x) + ".";
	});

	test.addSubTest("Test expoRapide exposant nul", [](Test& test)->std::string
	{
		double x;
		try
		{
			x = expoRapide(2.0, -10);
			return "L'exposant nul a ete accepte par la fonction expoRapide. Resultat obtenu: " + std::to_string(x);
		}
		catch (char const* e)
		{
			if (e == "Unexpected: n < 1")
				return "";
			else
				return "L'erreur retournee n'est pas la bonne. Erreur retournee: " + std::string(e);
		}
	});

	test.addSubTest("Test PGCD simple", [](Test& test)->std::string
	{
		int x(pgcd(2755, 10353));
		if (x == 29)
			return "";
		else
			return "Resultat attendu: 29. Resultat obtenu: " + std::to_string(x) + ".";
	});

	test.addSubTest("Test PGCD negatif", [](Test& test)->std::string
	{
		int x(pgcd(-2755, 10353));
		if (x == 29)
			return "";
		else
			return "Resultat attendu: 29. Resultat obtenu: " + std::to_string(x) + ".";
	});

	test.addSubTest("Test PGCD double negatif", [](Test& test)->std::string
	{
		int x(pgcd(-2755, -10353));
		if (x == 29)
			return "";
		else
			return "Resultat attendu: 29. Resultat obtenu: " + std::to_string(x) + ".";
	});

	test.addSubTest("Test PGCD nul", [](Test& test)->std::string
	{
		int x(pgcd(0, 10353));
		if (x == 1)
			return "";
		else
			return "Resultat attendu: 1. Resultat obtenu: " + std::to_string(x) + ".";
	});

	test.addSubTest("Test binom simple", [](Test& test)->std::string
	{
		Int x(binom(20, 15));
		if (x == 15504)
			return "";
		else
			return "Resultat attendu: 15504. Resultat obtenu: " + x.toString() + ".";
	});

	test.addSubTest("Test binom p negatif", [](Test& test)->std::string
	{
		Int x(binom(20, -1));
		if (x == 0)
			return "";
		else
			return "Resultat attendu: 0. Resultat obtenu: " + x.toString() + ".";
	});

	test.addSubTest("Test binom p trop grand", [](Test& test)->std::string
	{
		Int x(binom(20, 21));
		if (x == 0)
			return "";
		else
			return "Resultat attendu: 0. Resultat obtenu: " + x.toString() + ".";
	});

	test.addSubTest("Test binom (0, 0)", [](Test& test)->std::string
	{
		Int x(binom(0, 0));
		if (x == 1)
			return "";
		else
			return "Resultat attendu: 1. Resultat obtenu: " + x.toString() + ".";
	});

	return "";
}

std::string testGeneraux(Test& test)
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

std::string mainInt(Test& test)
{
	test.addSubTest("Test des initialisations", &testInit);
	test.addSubTest("Test des affectations", &testAffectation);

	test.addSubTest("Test des additions", &testAddition);
	test.addSubTest("Test des soustractions", &testSoustraction);
	test.addSubTest("Test des multiplications", &testMultiplication);
	test.addSubTest("Test des divisions", &testDivision);
	test.addSubTest("Test des modulos", &testModulo);
	test.addSubTest("Test des plus et moins unaires", &testUnaires);

	test.addSubTest("Test de la methode Int::toInt()", &testConversionInt);

	test.addSubTest("Test des operateurs == et !=", &testEgalite);
	test.addSubTest("Test des operateurs <= et >=", &testComparaison);
	test.addSubTest("Test des operateurs < et >", &testComparaisonStricte);

	test.addSubTest("Test des operations sur les flux", &testFlux);

	test.addSubTest("Test du destructeur", &testDestructeur);

	test.addSubTest("Test des fonctions definies en meme temps que les Int", &testFonctionsInt);

	test.addSubTest("Test generaux", &testGeneraux);

	return "";
}
