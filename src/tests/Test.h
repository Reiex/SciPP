#pragma once

#include <iostream>
#include <string>

class Test
{
	public:

		Test(std::string const& title, std::string (*testFunction)(Test&));

		void addSubTest(std::string const& title, std::string (*testFunction)(Test&));

		std::string operator()(int level, int detail);

		~Test();

	private:

		void displayTitle(int difference) const;

		std::string m_title;

		std::string (*m_testFunction)(Test&);

		Test* m_nextSubTest;
		Test* m_nextTest;
};