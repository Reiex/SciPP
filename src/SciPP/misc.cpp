#include <SciPP/SciPP.hpp>

namespace scp
{
    std::string scippError(const std::string& error)
    {
        return "<SciPP Error> " + error;
    }

    Int binom(const Int& n, const Int& p)
    {
        if (p > n || p < 0)
            return 0;

        Int num(1), denom(1);

        for (Int i(0); i < p; i += 1)
        {
            num *= n - i;
            denom *= p - i;
        }

        return num / denom;
    }
}