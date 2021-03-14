#include "SimAnim.hpp"

namespace simanim
{
	void createAnimation(const fs::path& path)
	{
		if (!fs::exists(path))
			fs::create_directories(path);

		std::ofstream file(path / "time.txt");
		file.close();
	}

	namespace
	{
		uint64_t index(uint32_t w, uint32_t h, uint32_t x, uint32_t y)
		{
			return 3*(y*w + x);
		}
	}

	void saveAnimationFrame(const fs::path& path, double t, const scp::Mat<double>& frame)
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

		std::string filename = (path / fs::path("frame" + std::to_string(frameCount) + ".txt")).string();
		std::ofstream frameFile(path / ("frame" + std::to_string(frameCount) + ".txt"));;
		frameFile << std::setprecision(15) << std::scientific << frame << std::endl;
		frameFile.close();
	}
}