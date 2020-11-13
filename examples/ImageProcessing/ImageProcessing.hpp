#pragma once

#include <complex>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include <SciPP/SciPP.hpp>

#include "../stb_image/stb_image.h"
#include "../stb_image/stb_image_write.h"

void plotDft(const std::string& src, const std::string& dst);
