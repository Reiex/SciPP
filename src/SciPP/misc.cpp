#include <SciPP/SciPP.hpp>

namespace scp
{
    std::string scippError(const std::string& error)
    {
        return "<SciPP Error> " + error;
    }
}