#pragma once

#include <SciPP/SciPP.hpp>

#include <cstdint>
#include <iostream>
#include <string>

void simuFluide2D(const std::string& name, uint64_t Nx, uint64_t Ny, double tSimu = 7.5, double nu = 0.0001, double rho = 30, double delta = 0.05, double Lx = 1.0, double Ly = 1.0);
