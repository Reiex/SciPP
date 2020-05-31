#pragma once

#include <string>
#include <sstream>
#include <limits.h>
#include <iostream>
#include <SciPP/SciPP.hpp>
#include "Test.h"

using namespace scp;


std::string mainInt(Test& test);
std::string mainFrac(Test& test);
std::string mainVect(Test& test);
std::string mainPolynome(Test& test);
std::string mainMatrice(Test& test);
std::string mainList(Test& test);
