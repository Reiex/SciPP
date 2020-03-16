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
		if (x.estActif())
			fail("Initialisation par déplacement.", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		else if (stream.str() == "31415926535")
			pass("Initialisation par déplacement.");
		else
			fail("Initialisation par déplacement.", "Résultat attendu: 31415926535. Résultat obtenu: " + stream.str() + ".");
	}
}

void testAffectation()
{
	displaySectionTitle("Test des affectations");

	{
		Int x(-161803398874989), y;
		y = x;
		std::stringstream stream;
		stream << y;
		if (stream.str() == "-161803398874989")
			pass("Affectation par copie.");
		else
			fail("Affectation par copie.", "Résultat attendu: -161803398874989. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(-161803398874989), y;
		y = std::move(x);
		std::stringstream stream;
		stream << y;
		if (x.estActif())
			fail("Affectation par déplacement.", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		else if (stream.str() == "-161803398874989")
			pass("Affectation par déplacement.");
		else
			fail("Affectation par déplacement.", "Résultat attendu: -161803398874989. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(-161803398874989), y, z, t;
		t = z = y = x;
		std::stringstream stream;
		stream << t;
		if (stream.str() == "-161803398874989")
			pass("Affectation chainée par copie.");
		else
			fail("Affectation chainée par copie.", "Résultat attendu: -161803398874989. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(-161803398874989), y, z, t;
		t = std::move(z = y = x);
		std::stringstream stream;
		stream << t;
		if (!x.estActif() || !y.estActif())
			fail("Affectation chainée par déplacement et copie.", "Un déplacement inattendu a eu lieu.");
		if (z.estActif())
			fail("Affectation chainée par déplacement et copie.", "Le déplacement n'a pas eu lieu, un entier déplacé est toujours actif.");
		else if (stream.str() == "-161803398874989")
			pass("Affectation chainée par déplacement et copie.");
		else
			fail("Affectation chainée par déplacement et copie.", "Résultat attendu: -161803398874989. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x;
		x = -161803398874989;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-161803398874989")
			pass("Affectation par un entier immédiat.");
		else
			fail("Affectation par un entier immédiat.", "Résultat attendu: -161803398874989. Résultat obtenu: " + stream.str() + ".");
	}
}

void testAddition()
{
	displaySectionTitle("Test des additions");

	{
		Int x(31415926536), y(-16180339887);
		x += y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "15235586649")
			pass("Addition en place.");
		else
			fail("Addition en place.", "Résultat attendu: 15235586649. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-16180339887), z;
		z = x + y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "15235586649")
			pass("Addition externe Int(Int const&, Int const&).");
		else
			fail("Addition externe Int(Int const&, Int const&).", "Résultat attendu: 15235586649. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-16180339887), z;
		z = std::move(x) + y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Addition externe Int&&(Int&&, Int const&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "15235586649")
			pass("Addition externe Int&&(Int&&, Int const&).");
		else
			fail("Addition externe Int&&(Int&&, Int const&).", "Résultat attendu: 15235586649. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-16180339887), z;
		z = x + std::move(y);
		std::stringstream stream;
		stream << z;
		if (y.estActif())
			fail("Addition externe Int&&(Int const&, Int&&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "15235586649")
			pass("Addition externe Int&&(Int const&, Int&&).");
		else
			fail("Addition externe Int&&(Int const&, Int&&).", "Résultat attendu: 15235586649. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-16180339887), z;
		z = std::move(x) + std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Addition externe Int&&(Int&&, Int&&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "15235586649")
			pass("Addition externe Int&&(Int&&, Int&&).");
		else
			fail("Addition externe Int&&(Int&&, Int&&).", "Résultat attendu: 15235586649. Résultat obtenu: " + stream.str() + ".");
	}
}

void testSoustraction()
{
	displaySectionTitle("Test des soustractions");

	{
		Int x(-31415926536), y(-16180339887);
		x -= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-15235586649")
			pass("Soustraction en place.");
		else
			fail("Soustraction en place.", "Résultat attendu: -15235586649. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(-31415926536), y(-16180339887), z;
		z = x - y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "-15235586649")
			pass("Soustraction externe Int(Int const&, Int const&).");
		else
			fail("Soustraction externe Int(Int const&, Int const&).", "Résultat attendu: -15235586649. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(-31415926536), y(-16180339887), z;
		z = std::move(x) - y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Soustraction externe Int&&(Int&&, Int const&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "-15235586649")
			pass("Soustraction externe Int&&(Int&&, Int const&).");
		else
			fail("Soustraction externe Int&&(Int&&, Int const&).", "Résultat attendu: -15235586649. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(-31415926536), y(-16180339887), z;
		z = x - std::move(y);
		std::stringstream stream;
		stream << z;
		if (y.estActif())
			fail("Soustraction externe Int&&(Int const&, Int&&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "-15235586649")
			pass("Soustraction externe Int&&(Int const&, Int&&).");
		else
			fail("Soustraction externe Int&&(Int const&, Int&&).", "Résultat attendu: -15235586649. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(-31415926536), y(-16180339887), z;
		z = std::move(x) - std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Soustraction externe Int&&(Int&&, Int&&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "-15235586649")
			pass("Soustraction externe Int&&(Int&&, Int&&).");
		else
			fail("Soustraction externe Int&&(Int&&, Int&&).", "Résultat attendu: -15235586649. Résultat obtenu: " + stream.str() + ".");
	}
}

void testMultiplication()
{
	displaySectionTitle("Test des multiplications");

	{
		Int x(31416), y(-1618);
		x *= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-50831088")
			pass("Multiplication en place.");
		else
			fail("Multiplication en place.", "Résultat attendu: -50831088. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31416), y(-1618), z;
		z = x * y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "-50831088")
			pass("Multiplication externe Int(Int const&, Int const&).");
		else
			fail("Multiplication externe Int(Int const&, Int const&).", "Résultat attendu: -50831088. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31416), y(-1618), z;
		z = std::move(x) * y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Multiplication externe Int&&(Int&&, Int const&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "-50831088")
			pass("Multiplication externe Int&&(Int&&, Int const&).");
		else
			fail("Multiplication externe Int&&(Int&&, Int const&).", "Résultat attendu: -50831088. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31416), y(-1618), z;
		z = x * std::move(y);
		std::stringstream stream;
		stream << z;
		if (y.estActif())
			fail("Multiplication externe Int&&(Int const&, Int&&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "-50831088")
			pass("Multiplication externe Int&&(Int const&, Int&&).");
		else
			fail("Multiplication externe Int&&(Int const&, Int&&).", "Résultat attendu: -50831088. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31416), y(-1618), z;
		z = std::move(x) * std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Multiplication externe Int&&(Int&&, Int&&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "-50831088")
			pass("Multiplication externe Int&&(Int&&, Int&&).");
		else
			fail("Multiplication externe Int&&(Int&&, Int&&).", "Résultat attendu: -50831088. Résultat obtenu: " + stream.str() + ".");
	}
}

void testDivision()
{
	displaySectionTitle("Test des divisions");

	{
		Int x(31415926536), y(-1618);
		x /= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "-19416518")
			pass("Division en place.");
		else
			fail("Division en place.", "Résultat attendu: -19416518. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-1618), z;
		z = x / y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "-19416518")
			pass("Division externe Int(Int const&, Int const&).");
		else
			fail("Division externe Int(Int const&, Int const&).", "Résultat attendu: -19416518. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-1618), z;
		z = std::move(x) / y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Division externe Int&&(Int&&, Int const&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "-19416518")
			pass("Division externe Int&&(Int&&, Int const&).");
		else
			fail("Division externe Int&&(Int&&, Int const&).", "Résultat attendu: -19416518. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-1618), z;
		z = std::move(x) / std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Division externe Int&&(Int&&, Int&&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "-19416518")
			pass("Division externe Int&&(Int&&, Int&&).");
		else
			fail("Division externe Int&&(Int&&, Int&&).", "Résultat attendu: -19416518. Résultat obtenu: " + stream.str() + ".");
	}
}

void testModulo()
{
	displaySectionTitle("Test des modulos");

	{
		Int x(31415926536), y(-1618);
		x %= y;
		std::stringstream stream;
		stream << x;
		if (stream.str() == "412")
			pass("Division en place.");
		else
			fail("Division en place.", "Résultat attendu: 412. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-1618), z;
		z = x % y;
		std::stringstream stream;
		stream << z;
		if (stream.str() == "412")
			pass("Division externe Int(Int const&, Int const&).");
		else
			fail("Division externe Int(Int const&, Int const&).", "Résultat attendu: 412. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-1618), z;
		z = std::move(x) % y;
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Division externe Int&&(Int&&, Int const&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "412")
			pass("Division externe Int&&(Int&&, Int const&).");
		else
			fail("Division externe Int&&(Int&&, Int const&).", "Résultat attendu: 412. Résultat obtenu: " + stream.str() + ".");
	}

	{
		Int x(31415926536), y(-1618), z;
		z = std::move(x) % std::move(y);
		std::stringstream stream;
		stream << z;
		if (x.estActif())
			fail("Division externe Int&&(Int&&, Int&&).", "Le déplacement n'a pas eu lieu, l'entier de départ est toujours actif.");
		if (stream.str() == "412")
			pass("Division externe Int&&(Int&&, Int&&).");
		else
			fail("Division externe Int&&(Int&&, Int&&).", "Résultat attendu: 412. Résultat obtenu: " + stream.str() + ".");
	}
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
