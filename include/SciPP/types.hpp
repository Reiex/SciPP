#pragma once

#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace scp
{
    class Int;

    template<typename T> class Frac;
    class Rational;

    template<typename T, uint64_t n> class Vec;

    template<typename T> class Polynomial;

    template<typename T, uint64_t n, uint64_t m> class Mat;
}
