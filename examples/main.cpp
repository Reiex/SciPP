#include <iostream>
#include <SciPP/SciPP.hpp>

#include "Constants/Constants.hpp"
#include "FluidSimulation/FluidSimulation.hpp"
#include "ImageProcessing/ImageProcessing.hpp"
#include "Misc/Misc.hpp"
#include "MoleDyn/MoleDyn.hpp"

int main()
{
	/*
	
	TODO:
		- Graphs:
			- Check data structure
			- Typedefs "NodeId/EdgeId" instead of "uint64_t" everywhere
		- For matrix/vector operators, add "TMatrix/TVector&&" versions when possible...
	*/

	// std::cout << "Neper constant: e = " << neper(200).decimals(200) << std::endl;
	// std::cout << "Sqrt(2): " << squareRoot(2, 500).decimals(500) << std::endl;
	// std::cout << "Phi: " << ((1 + squareRoot(5, 500)) / 2).decimals(500) << std::endl;
	
	// plotLogisticMap("build/Logistic Map.png", 1920, 1080, 2.8f, 4.f, 100000);
	// eratosthenesSieve(1000);
	
	// plotDft("examples/assets/Lena.png", "build/Lena DFT.png");
	// edgesDoG("examples/assets/Lena.png", "build/Lena Edges DoG.png");
	
	// simuFluide2D("build/fluid/", 256, 256);
	// lennardJones2D("build/moledyn/", 200);

	return 0;
}
