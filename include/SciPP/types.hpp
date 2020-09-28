#pragma once

#include <cmath>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace scp
{
    std::string scippError(const std::string& error);

    class Int;

    template<typename T> class Frac;
    class Rational;

    template<typename T, uint64_t n> class Vec;

    template<typename T> class Polynomial;

    template<typename T, uint64_t m, uint64_t n> class Mat;

    // Pour continuer

    template<typename T> class Quaternion;
}
