#include "main.h"

int main()
{
	Test mainTest("TEST DE LA BIBLIOTHEQUE SCIPP", [](Test& test)->std::string {
		test.addSubTest("TEST DES ENTIERS", &mainInt);
		test.addSubTest("TEST DES FRACTIONS", &mainFrac);
		test.addSubTest("TEST DES VECTEURS", &mainVect);
		test.addSubTest("TEST DES POLYNOMES", &mainPolynome);
		test.addSubTest("TEST DES MATRICES", &mainMatrice);
		return "";
	});

	mainTest(0, 3);

	return 0;
}