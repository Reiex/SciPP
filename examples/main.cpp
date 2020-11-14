#include <cstdlib>

#include "Constants/Constants.hpp"
#include "ImageProcessing/ImageProcessing.hpp"
#include "Misc/Misc.hpp"


int main()
{
    std::cout << "Neper constant: e = " << neper(50) << std::endl;
    std::cout << "Golden Ratio: phi = " << goldenRatio(50) << std::endl;

    // plotLogisticMap("Logistic Map.png", 1920, 1080, 2.8f, 4.f, 10000);

    // plotDft("examples/assets/Lena.png", "Lena DFT.png");
    edgesDoG("examples/assets/Lena.png", "Lena Edges DoG.png");

    return 0;
}