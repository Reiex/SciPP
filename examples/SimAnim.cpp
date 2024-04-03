///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Pélégrin Marius
//! \copyright The MIT License (MIT)
//! \date 2019-2024
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SimAnim.hpp"

#include <fstream>

namespace simanim
{
	void createAnimation(const fs::path& path, uint64_t frameWidth, uint64_t frameHeight)
	{
		if (!fs::exists(path))
			fs::create_directories(path);

		std::ofstream file(path / "time.txt");
		file << frameWidth << " " << frameHeight << std::endl;
		file.close();
	}

	namespace
	{
		uint64_t index(uint32_t w, uint32_t h, uint32_t x, uint32_t y)
		{
			return 3*(y*w + x);
		}
	}

	void saveAnimationFrame(const fs::path& path, double t, const scp::Matrix<double>& frame)
	{
		std::fstream timeFile(path / "time.txt");

		std::string line;
		int frameCount = 0;
		while (std::getline(timeFile, line))
			frameCount++;
		timeFile.clear();
		timeFile.seekg(0);
		timeFile.seekg(0, std::ios::end);
		timeFile << std::setprecision(15) << std::scientific << t << std::endl;

		std::ofstream frameFile(path / ("frame" + std::to_string(frameCount) + ".bin"), std::ios::binary);
		std::vector<double> data(frame.getSize(0) * frame.getSize(1));
		for (uint64_t i(0); i < frame.getSize(0); i++)
			for (uint64_t j(0); j < frame.getSize(1); j++)
				data[i * frame.getSize(1) + j] = frame[{i, j}];
		frameFile.write((char*) data.data(), data.size()*8);
		frameFile.close();
	}
}