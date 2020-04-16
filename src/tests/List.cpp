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

	return "";
}

std::string mainList(Test& test)
{
	test.addSubTest("Test des initialisations", &testInit);

	/*
		test.addSubTest("Test de la simplification des fractions", nullptr);

		test.addSubTest("Test des additions", nullptr);
		test.addSubTest("Test des soustractions", nullptr);
		test.addSubTest("Test des multiplications", nullptr);
		test.addSubTest("Test des divisions", nullptr);
		test.addSubTest("Test des plus et moins unaires", nullptr);

		test.addSubTest("Test des operateurs == et !=", nullptr);
		test.addSubTest("Test des operateurs <= et >=", nullptr);
		test.addSubTest("Test des operateurs < et >", nullptr);

		test.addSubTest("Test de la classe Rationnel", nullptr);
		test.addSubTest("Test des fonctions définies en meme temps que les rationnels", nullptr);

		test.addSubTest("Test generaux", nullptr);
	*/

	return "";
}
