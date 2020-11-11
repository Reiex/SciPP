#include <cstdlib>

#include "Constants/Constants.hpp"


int main()
{
    std::cout << "Neper constant: e = " << neper(50) << std::endl;
    std::cout << "Golden Ratio: phi = " << goldenRatio(50) << std::endl;

    system("pause");

    return 0;
}