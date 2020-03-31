#include "Test.h"


Test::Test(std::string const& title, std::string (*testFunction)(Test&))
{
	m_title = title;
	m_testFunction = testFunction;

	m_nextSubTest = nullptr;
	m_nextTest = nullptr;
}

void Test::addSubTest(std::string const& title, std::string (*testFunction)(Test&))
{
	if (m_nextSubTest == nullptr)
	{
		m_nextSubTest = new Test(title, testFunction);
		return;
	}

	Test* current(m_nextSubTest);
	while (current->m_nextTest != nullptr)
		current = current->m_nextTest;
	current->m_nextTest = new Test(title, testFunction);
}

std::string Test::operator()(int level, int detail)
{
	if (level < detail)
		displayTitle(detail - level);

	std::string retour, add;

	retour = m_testFunction(*this);
	if (retour.size() > 0)
		retour += "\n";

	Test* current(m_nextSubTest);
	while (current != nullptr)
	{
		add = (*current)(level + 1, detail);
		if (add.size() > 0)
			retour += add + "\n";
		current = current->m_nextTest;
	}

	if (level == detail)
		if (retour.size() > 0)
			std::cout << "\e[0;31m[FAILED]\e[0m " << m_title << std::endl << retour;
		else
			std::cout << "\e[0;32m[PASSED]\e[0m " << m_title << std::endl;

	return retour;
}

Test::~Test()
{
	if (m_nextSubTest != nullptr)
	{
		Test* current(m_nextSubTest);
		while (current != nullptr)
		{
			Test* nextCurrent(current->m_nextTest);
			delete current;
			current = nextCurrent;
		}
	}
}

void Test::displayTitle(int difference) const
{
	int size(m_title.size() + 2), lineLength(80);
	if (difference == 1)
	{
		std::cout << std::endl << "\e[0;33m" << std::string((lineLength-size)/2 + size % 2, '-') << " " << m_title << " " << std::string((lineLength-size)/2, '-') << "\e[0m" << std::endl;
	}
	else if (difference == 2)
	{
		std::cout << std::endl << "\e[0;33m" << std::string((lineLength-size)/2 + size % 2, '#') << " " << m_title << " " << std::string((lineLength-size)/2, '#') << "\e[0m" << std::endl;
	}
	else
	{
		std::cout << "\e[0;33m" << "+" << std::string(78, '=') << "+" << std::endl;
		std::cout << "|" << std::string((lineLength-size)/2 + size % 2, ' ') << m_title << std::string((lineLength-size)/2, ' ') << "|" << std::endl;
		std::cout << "+" << std::string(78, '=') << "+" << "\e[0m" << std::endl << std::endl;
	}
}
