#pragma once

#include <SciPP/types.hpp>

#include <SciPP/plot/ChartDataSet.hpp>

namespace scp
{
namespace plot
{
namespace dataset
{
    class DataSetPoints2D : public ChartDataSet
    {
        private:

            std::vector<float> _xValues;
            std::vector<float> _yValues;
    };
}
}
}
