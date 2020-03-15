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
	std::cout << "[PASSED] " << message << std::endl;
}

void fail(std::string const& message, std::string const& reason)
{
	std::cout << "[FAILED] " << message << std::endl << reason << std::endl << std::endl;
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