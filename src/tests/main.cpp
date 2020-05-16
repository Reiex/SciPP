#include "main.h"

int main()
{
	Test mainTest("TEST DE LA BIBLIOTHEQUE SCIPP", [](Test& test)->std::string {
		test.addSubTest("TEST DES ENTIERS", &mainInt);
		test.addSubTest("TEST DES FRACTIONS", &mainFrac);
		test.addSubTest("TEST DES VECTEURS", &mainVect);
		test.addSubTest("TEST DES POLYNOMES", &mainPolynome);
		test.addSubTest("TEST DES MATRICES", &mainMatrice);
		test.addSubTest("TEST DES LISTES", &mainList);
		return "";
	});

	mainTest(0, 3);

	std::cout << std::endl;

#ifdef SCP_TEST_PAUSE

	system("pause");

#endif

	return 0;
}