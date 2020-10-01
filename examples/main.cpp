#include <SciPP/SciPP.hpp>
#include <math.h>

int main()
{
    scp::Quaternion<double> x(0, 3, 0, -1), y(2, 0, 1, 1);
    std::cout << x*scp::inverse(x) << std::endl;

    return 0;
}