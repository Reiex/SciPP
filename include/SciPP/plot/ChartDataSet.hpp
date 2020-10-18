#pragma once

#include <SciPP/types.hpp>

#include <SciPP/plot/ChartWorldObject.hpp>

namespace scp
{
namespace plot
{
    class ChartDataSet : public ChartWorldObject
    {
        public:

            VisualizationMethod method;
    };

    enum class VisualizationMethod
    {
        // {Dimension of the value}:{Dimension of the position of the value}

        Undefined,

        // 1:1 | 0:2
        Points2D,
        Line2D,

        // 1:2 | 0:3
        Points3D,
        Line3D,

        // 1:2
        HeightMap,
        HeatMap,
        Isoline,

        // 2:2
        Vec2D2D,

        // 3:2
        ColorMap,
        Vec3D2D,

        // 1:3
        IsoSurface,
        DensityMap,

        // 3:3
        ColoredPoints,
        Vec3D3D
    };
}
}
