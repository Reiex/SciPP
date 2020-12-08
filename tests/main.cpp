#include "main.hpp"

void printSection(const std::string& testName, const std::string& sectionName)
{
    std::cout << "\e[0;33m[ SECTION  ]\e[0m " << testName << ": " << sectionName << std::endl;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int exit_code = RUN_ALL_TESTS();
    return exit_code;
}

/*

TODO:

    Tests:

        - Séparer tests IDCT et DCT classe Vec
        - Séparer tests IDFT et DFT classe Mat
        - Séparer tests IDCT et DCT classe Mat

    SciPP:

        - Produit et division Vec-T
        - Operator++ Int
        - Supprimer parallelisme (Mat convolve et Mat-Mat product)

*/
