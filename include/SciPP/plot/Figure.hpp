#pragma once

#include <SciPP/types.hpp>

#include <SciPP/plot/ChartDataSet.hpp>

namespace scp
{
namespace plot
{
    class Figure
    {
        public:

            void plot(const std::vector<float>& x, const std::vector<float>& y, VisualizationMethod visualizationMethod = VisualizationMethod::Line2D, uint64_t chart = 0);
            void plot(const std::vector<std::array<float, 2>>& pos, const std::vector<float>& z, VisualizationMethod visualizationMethod = VisualizationMethod::HeightMap, uint64_t chart = 0);

            void show();

            std::vector<Chart>& getCharts();

        private:

            std::vector<Chart> _charts;
    };
}
}