#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace scp
{
    std::string scippError(const std::string& error);

    class Int;
    template<typename T> struct Quaternion;
    template<typename T> class Frac;
    class Rational;
    template<typename T> class Polynomial;
    template<typename T> class Vec;
    enum class ConvolveMethod;
    template<typename T> class Mat; 
}
