#include <cstdlib>

#include "Constants/Constants.hpp"
#include "FluidSimulation/FluidSimulation.hpp"
#include "ImageProcessing/ImageProcessing.hpp"
#include "Misc/Misc.hpp"


int main()
{
    // std::cout << "Neper constant: e = " << neper(50) << std::endl;
    // std::cout << "Golden Ratio: phi = " << goldenRatio(50) << std::endl;

    // plotLogisticMap("build/Logistic Map.png", 1920, 1080, 2.8f, 4.f, 10000);
    // eratosthenesSieve(100);

    // plotDft("examples/assets/Lena.png", "build/Lena DFT.png");
    // edgesDoG("examples/assets/Lena.png", "build/Lena Edges DoG.png");

    simuFluide2D("build/fluid", 128, 128);

    return 0;
}