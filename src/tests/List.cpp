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
	test.addSubTest("Affectation par copie", [](Test& test)->std::string
	{
		List<int> l({ 1, 6, 1, 8, 0, 3 }), m;
		m = l;
		std::stringstream stream;
		stream << m;
		if (stream.str() == "[1, 6, 1, 8, 0, 3]")
			return "";
		else
			return "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affectation par deplacement", [](Test& test)->std::string
	{
		List<int> l({ 1, 6, 1, 8, 0, 3 }), m;
		m = std::move(l);
		std::stringstream stream;
		std::string r;
		stream << m;
		if (l.size() != 0)
			r += "Le deplacement n'a pas eu lieu, la liste de depart est toujours active. ";
		if (stream.str() != "[1, 6, 1, 8, 0, 3]")
			r += "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ". ";

		return r;
	});

	test.addSubTest("Affectation chainee par copie", [](Test& test)->std::string
	{
		List<int> l({ 1, 6, 1, 8, 0, 3 }), m, n, o;
		o = n = m = l;
		std::stringstream stream;
		stream << o;
		if (stream.str() == "[1, 6, 1, 8, 0, 3]")
			return "";
		else
			return "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Affectation chainee par deplacement et copie", [](Test& test)->std::string
	{
		List<int> l({ 1, 6, 1, 8, 0, 3 }), m, n, o;
		o = std::move(n = m = l);
		std::stringstream stream;
		std::string r;
		stream << o;
		if (l.size() == 0 || m.size() == 0)
			r += "Un deplacement inattendu a eu lieu. ";
		if (n.size() != 0)
			r += "Le deplacement n'a pas eu lieu, un entier deplace est toujours actif. ";
		else if (stream.str() != "[1, 6, 1, 8, 0, 3]")
			r += "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ". ";

		return r;
	});

	return "";
}

static std::string testDestructeur(Test& test)
{
	return "";
}

static std::string testConcatenation(Test& test)
{
	test.addSubTest("Concatenation en place normale", [](Test& test)->std::string
	{
		List<int> l({ 1, 6, 1 }), m({ 8, 0, 3 });
		l += m;
		std::stringstream stream;
		stream << l;
		if (stream.str() == "[1, 6, 1, 8, 0, 3]")
			return "";
		else
			return "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Concatenation en place premier membre vide", [](Test& test)->std::string
	{
		List<int> l, m({ 1, 6, 1, 8, 0, 3 });
		l += m;
		std::stringstream stream;
		stream << l;
		if (stream.str() == "[1, 6, 1, 8, 0, 3]")
			return "";
		else
			return "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Concatenation en place deuxieme membre vide", [](Test& test)->std::string
	{
		List<int> l({ 1, 6, 1, 8, 0, 3 }), m;
		l += m;
		std::stringstream stream;
		stream << l;
		if (stream.str() == "[1, 6, 1, 8, 0, 3]")
			return "";
		else
			return "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Concatenation en place deux membres vides", [](Test& test)->std::string
	{
		List<int> l, m;
		l += m;
		std::stringstream stream;
		stream << l;
		if (stream.str() == "[]")
			return "";
		else
			return "Resultat attendu: []. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Concatenation externe", [](Test& test)->std::string
	{
		List<int> l({ 1, 6, 1 }), m({ 8, 0, 3 }), n;
		n = l + m;
		std::stringstream stream;
		stream << n;
		if (stream.str() == "[1, 6, 1, 8, 0, 3]")
			return "";
		else
			return "Resultat attendu: [1, 6, 1, 8, 0, 3]. Resultat obtenu: " + stream.str() + ".";
	});

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
	test.addSubTest("Ajout et suppression d'un grand nombre d'elements", [](Test& test)->std::string
	{
		List<int> l;
		for (int i(0); i < 4100; i++)
			l.append(i);

		for (int i(0); i < 4100; i++)
			l.remove(0);

		std::stringstream stream;
		stream << l;
		if (stream.str() == "[]")
			return "";
		else
			return "Resultat attendu: []. Resultat obtenu: " + stream.str() + ".";
	});

	test.addSubTest("Elements impairs", [](Test& test)->std::string
	{
		List<int> l;
		for (int i(0); i < 20; i++)
			l.append(i);

		for (int i(0); i < 10; i++)
			l.remove(i);

		std::stringstream stream;
		stream << l;
		if (stream.str() == "[1, 3, 5, 7, 9, 11, 13, 15, 17, 19]")
			return "";
		else
			return "Resultat attendu: [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]. Resultat obtenu: " + stream.str() + ".";
	});

	return "";
}

std::string mainList(Test& test)
{
	test.addSubTest("Test des initialisations", &testInit);
	test.addSubTest("Test des affectations", &testAffectation);
	test.addSubTest("Test du destructeur", &testDestructeur);

	test.addSubTest("Test de la concatenation", &testConcatenation);
	test.addSubTest("Test des operateurs == et !=", &testEgalite);
	test.addSubTest("Test des fonctions spécifiques", &testFonctionsSpecifiques);
	test.addSubTest("Test generaux", &testGeneraux);

	return "";
}
