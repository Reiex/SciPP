#pragma once

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <string>

#include <SciPP/SciPP.hpp>

#include "../stb_image/stb_image.h"
#include "../stb_image/stb_image_write.h"

namespace fs = std::filesystem;

namespace simanim
{
	void createAnimation(const fs::path& path);
	void saveAnimationFrame(const fs::path& path, double t, const scp::Mat<double>& frame);
}
