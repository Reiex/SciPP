#pragma once

#include <SciPP/SciPP.hpp>

#include <cstdint>
#include <iostream>
#include <string>

// Has nothing to do with SciPP, but I like it. Could be useful to test a plot module...
void plotLogisticMap(const std::string& filename, uint32_t w, uint32_t h, float a, float b, uint32_t n);
void eratosthenesSieve(uint64_t n);