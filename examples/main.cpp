#include <SciPP/SciPP.hpp>
#include <math.h>

int main()
{
    scp::Mat<double, 3, 3> x(std::vector<std::vector<double>>({{1, 0, 1}, {0, 1, 1}, {0, 0, 1}}));

    scp::inverse(x);

    std::cout << x << std::endl;

    return 0;
}