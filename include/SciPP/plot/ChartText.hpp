#pragma once

#include <SciPP/types.hpp>

#include <SciPP/plot/FigureObject.hpp>

namespace scp
{
namespace plot
{
    class ChartText : public FigureObject
    {
        private:

            std::string _text;
    };
}
}
