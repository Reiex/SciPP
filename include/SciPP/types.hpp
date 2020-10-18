#pragma once

#include <array>
#include <cmath>
#include <complex>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace scp
{
    std::string scippError(const std::string& error);

    class Int;
    template<typename T> class Quaternion;
    template<typename T> class Frac;
    class Rational;
    template<typename T, uint64_t n> class Vec;
    template<typename T> class Polynomial;
    template<typename T, uint64_t m, uint64_t n> class Mat;

    namespace plot
    {
        class Figure;
        class FigureObject;
        class Chart;
        class ChartWorldObject;
        class ChartDataSet;
        enum class VisualizationMethod;

        namespace dataset
        {
            class Points2D;
            class Line2D;
            class Points3D;
            class Line3D;
            class HeightMap;
            class HeatMap;
            class Isoline;
            class Vec2D2D;
            class ColorMap;
            class Vec3D2D;
            class IsoSurface;
            class DensityMap;
            class ColoredPoints;
            class Vec3D3D;
        }
    } 
}
