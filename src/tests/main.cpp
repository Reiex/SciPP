#include "main.h"

void displayMainTitle(std::string const& title)
{
	std::cout << std::endl << "######## " << title << " ########" << std::endl << std::endl;
}

void displaySectionTitle(std::string const& title)
{
	std::cout << std::endl << "-------- " << title << " --------" << std::endl;
}

void pass(std::string const& message)
{
	std::cout << "\033[0;32m[PASSED]\033[0m " << message << std::endl;
}

void fail(std::string const& message, std::string const& reason)
{
	std::cout << "\033[0;31m[FAILED]\033[0m " << message << std::endl << reason << std::endl << std::endl;
}

int main()
{
	mainInt();
	mainFrac();
	mainVect();
	mainPolynome();
	mainMatrice();

	std::cout << std::endl << std::endl;
	system("pause");

	return 0;
}