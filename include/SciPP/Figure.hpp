#pragma once

#include <SciPP/types.hpp>

namespace scp
{
    class Figure
    {
        public:

        private:

            std::string _title;

            std::vector<Chart> _charts;
    };

    class Chart
    {
        public:

        private:

            std::string _title;

            std::vector<ChartDataSet> _data;

            std::array<Axis, 3> _axes;

            bool _autoPosition;
            std::array<uint64_t, 4> _coord;
    };

    class Axis
    {
        public:

        private:
        
            double _min;
            double _max;
    };

    class ChartDataSet
    {
        public:

            enum class Visualization
            {
                // 1:1
                Points2D,
                Line2D,

                // 1:2
                Points3D,
                Line3D,
                Patch,
                Heatmap,
                Isoline,

                // 2:2
                Vec2D2D,

                // 3:2
                Colors2D,
                Vec3D2D,

                // 1:3
                IsoSurface,
                Cloud,

                // 3:3
                Colors3D,
                Vec3D3D
            };

        private:

            uint64_t _valueDim;
            uint64_t _positionDim;

            std::vector<uint64_t> _counts;

            std::vector<double> _data;

            Visualization _type;
    };
}
