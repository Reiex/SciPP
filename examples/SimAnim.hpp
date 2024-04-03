///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Pélégrin Marius
//! \copyright The MIT License (MIT)
//! \date 2019-2024
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/SciPP.hpp>

#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

namespace simanim
{
	void createAnimation(const fs::path& path, uint64_t frameWidth, uint64_t frameHeight);
	void saveAnimationFrame(const fs::path& path, double t, const scp::Matrix<double>& frame);
}
