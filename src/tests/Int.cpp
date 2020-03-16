#include "main.h"

void testInit()
{
	displaySectionTitle("Test des initialisations");

	{
		Int x;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "0")
			pass("Initialisation par défaut.");
		else
			fail("Initialisation par défaut.", "Résultat attendu: 0. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(0);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "0")
			pass("Initialisation entier nul.");
		else
			fail("Initialisation nulle.", "Résultat attendu: 0. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(161803398874989);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "161803398874989")
			pass("Initialisation entier positif.");
		else
			fail("Initialisation positive.", "Résultat attendu: 161803398874989. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(-161803398874989);
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-161803398874989")
			pass("Initialisation entier négatif.");
		else
			fail("Initialisation négative.", "Résultat attendu: -161803398874989. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926535), y(x);
		std::stringstream stream;
		stream << y;
		if (stream.str() == "31415926535")
			pass("Initialisation par copie.");
		else
			fail("Initialisation par copie.", "Résultat attendu: 31415926535. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926535), y(std::move(x));
		std::stringstream stream;
		stream << y;
		if (stream.str() == "31415926535")
			pass("Initialisation par déplacement.");
		else
			fail("Initialisation par déplacement.", "Résultat attendu: 31415926535. Résultat obtenu: " + stream.str() + ".");
	}
}

void testAffectation()
{
	displaySectionTitle("Test des affectations");
}

void testAddition()
{
	displaySectionTitle("Test des additions");
}

void testSoustraction()
{
	displaySectionTitle("Test des soustractions");
}

void testMultiplication()
{
	displaySectionTitle("Test des multiplications");
}

void testDivision()
{
	displaySectionTitle("Test des divisions");
}

void testModulo()
{
	displaySectionTitle("Test des modulos");
}

void testUnaires()
{
	displaySectionTitle("Test des plus et moins unaires");
}

void testConversionInt()
{
	displaySectionTitle("Test de la methode Int::toInt()");
}

void testEgalite()
{
	displaySectionTitle("Test des opérateurs == et !=");
}

void testComparaison()
{
	displaySectionTitle("Test des opérateurs <= et >=");
}

void testComparaisonStricte()
{
	displaySectionTitle("Test des opérateurs < et >");
}

void testFlux()
{
	displaySectionTitle("Test des opérations sur les flux");
}

void testDestructeur()
{
	displaySectionTitle("Test du destructeur");
}

void mainInt()
{
	displayMainTitle("TEST DES ENTIERS");

	testInit();
	testAffectation();

	testAddition();
	testSoustraction();
	testMultiplication();
	testDivision();
	testModulo();
	testUnaires();

	testConversionInt();

	testEgalite();
	testComparaison();
	testComparaisonStricte();

	testFlux();

	testDestructeur();
}
