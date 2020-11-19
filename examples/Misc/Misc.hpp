#pragma once

#include <complex>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <SciPP/SciPP.hpp>

#include "../stb_image/stb_image.h"
#include "../stb_image/stb_image_write.h"

// Has nothing to do with SciPP, but I like it. Could be useful to test a plot module...
void plotLogisticMap(const std::string& filename, uint32_t w, uint32_t h, float a, float b, uint32_t n);
void eratosthenesSieve(uint64_t n);