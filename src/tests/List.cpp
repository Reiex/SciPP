#include "main.h"

static std::string testInit(Test& test)
{
	test.addSubTest("Initialisation par defaut", [](Test& test)->std::string
	{
		List<int> l;
		std::stringstream stream;
		stream << l;
		if (stream.str() == "[]")
			return "";
		else
			return "Resultat attendu: []. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation par taille", [](Test& test)->std::string
	{
		List<int> l(5);
		std::stringstream stream;
		stream << l;
		if (stream.str() == "[0, 0, 0, 0, 0]")
			return "";
		else
			return "Resultat attendu: [0, 0, 0, 0, 0]. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation par liste d'initialisation", [](Test& test)->std::string
	{
		List<int> l({ 1, 6, 1, 8, 0, 3 });
		std::stringstream stream;
		stream << l;
		if (stream.str() == "[1, 6, 1, 8, 0, 3]")
			return "";
		else
			return "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Initialisation par tableau C", [](Test& test)->std::string
	{
		int tab[6] = { 1, 6, 1, 8, 0, 3 };
		List<int> l(tab, 6);
		std::stringstream stream;
		stream << l;
		if (stream.str() == "[1, 6, 1, 8, 0, 3]")
			return "";
		else
			return "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

static std::string testAffectation(Test& test)
{
	return "";
}

static std::string testConcatenation(Test& test)
{
	return "";
}

static std::string testEgalite(Test& test)
{
	return "";
}

static std::string testFonctionsSpecifiques(Test& test)
{
	return "";
}

static std::string testGeneraux(Test& test)
{
	return "";
}

std::string mainList(Test& test)
{
	test.addSubTest("Test des initialisations", &testInit);
	test.addSubTest("Test des affectations", &testAffectation);
	test.addSubTest("Test de la concatenation", &testConcatenation);
	test.addSubTest("Test des operateurs == et !=", &testEgalite);
	test.addSubTest("Test des fonctions spécifiques", &testFonctionsSpecifiques);
	test.addSubTest("Test generaux", &testGeneraux);

	return "";
}
