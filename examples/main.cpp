#include <cstdlib>

#include "Constants/Constants.hpp"


int main()
{
    // std::cout << neper(50) << std::endl;
    // std::cout << goldenRatio(10) << std::endl;

    // 6949403065 4294967296, 3474701533 2147483648
    scp::Rational a(6949403065, 4294967296);
    scp::Rational b(3474701533, 2147483648);

    std::cout << a << " " << b << std::endl;
    std::cout << a + b << std::endl;

    system("pause");

    return 0;
}