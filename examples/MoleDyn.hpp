///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Pélégrin Marius
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/SciPP.hpp>

#include <cstdint>
#include <string>

void lennardJones2D(const std::string& name, uint64_t N, double tSimu = 1e-9, double L = 2e-8, double mass = 6.6335209e-26, double sigma = 3.405e-10, double epsilon = 119.8, double temperature = 10);
