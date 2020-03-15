#pragma once

#include <iostream>
#include <string>

void displayMainTitle(std::string const& title);
void displaySectionTitle(std::string const& title);
void pass(std::string const& message);
void fail(std::string const& message, std::string const& reason);

void mainInt();
void mainFrac();
void mainVect();
void mainPolynome();
void mainMatrice();
