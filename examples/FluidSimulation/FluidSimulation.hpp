#pragma once

#include <complex>
#include <cstdint>
#include <cmath>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <SciPP/SciPP.hpp>

#include "../stb_image/stb_image.h"
#include "../stb_image/stb_image_write.h"

void simuFluide2D(const std::string& name, uint64_t Nx, uint64_t Ny, double t_simu = 7.5, double nu = 0.0001, double rho = 30, double delta = 0.05, double Lx = 1.0, double Ly = 1.0);
