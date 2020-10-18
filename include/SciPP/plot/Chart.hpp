#pragma once

#include <SciPP/types.hpp>

#include <SciPP/Mat.hpp>
#include <SciPP/plot/FigureObject.hpp>

namespace scp
{
namespace plot
{
    class Chart : public FigureObject
    {
        public:

            Chart();

            void addDataSet(const ChartDataSet& dataSet);

            void setBoundaries(uint64_t x, uint64_t y, uint64_t w, uint64_t h);

        private:

            FigureObject _worldBoundaries;

            Mat<float, 4, 4> _view;
            Mat<float, 4, 4> _proj;

            std::vector<ChartDataSet*> _data;
    };
}
}
