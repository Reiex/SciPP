#pragma once

#include <SciPP/types.hpp>
#include <SciPP/Mat.hpp>

namespace scp
{
    class Figure
    {
        public:

            void plot(const std::vector<float>& x, const std::vector<float>& y, ChartDataSet::VisualizationMethod visualizationMethod = ChartDataSet::VisualizationMethod::Line2D, uint64_t chart = 0);
            void plot(const std::vector<std::array<float, 2>>& pos, const std::vector<float>& z, ChartDataSet::VisualizationMethod visualizationMethod = ChartDataSet::VisualizationMethod::Line2D, uint64_t chart = 0);

            void show();

            std::vector<Chart>& getCharts();

        private:

            std::vector<Chart> _charts;
    };

    class FigureObject
    {
        public:

            virtual void draw();

        protected:

            uint64_t _xFigure;
            uint64_t _yFigure;
            uint64_t _wFigure;
            uint64_t _hFigure;
            bool _visible;
            bool _autoPosition;
    };

    class Chart: public FigureObject
    {
        public:

            Chart();

            void addDataSet(const ChartDataSet& dataSet);

            // Comment appliquer un axe à un dataset ?

            void setTitle(std::string title);
            void setBoundaries(uint64_t x, uint64_t y, uint64_t w, uint64_t h);

        private:

            ChartText _title;

            FigureObject _chartWorldBoundaries;

            Mat<float, 4, 4> _view;
            Mat<float, 4, 4> _proj;

            std::vector<std::unique_ptr<ChartDataSet>> _data;
            std::vector<ChartAxis> _axes;
            std::vector<std::vector<uint64_t>> _dataToAxes;
    };

    class ChartText: public FigureObject
    {
        private:

            std::string _text;
    };

    class ChartWorldObject
    {
        private:
        
            float _xWorld;
            float _yWorld;
            float _zWorld;
            float _wWorld;
            float _hWorld;
            float _dWorld;
    };

    class ChartAxis: public ChartWorldObject
    {
        public:

            virtual void draw();

        private:
        
            float _min;
            float _max;
            uint8_t _graduations;
    };

    class ChartDataSet: public ChartWorldObject
    {
        public:

            enum class VisualizationMethod
            {
                // {Dimension of the value}:{Dimension of the position of the value}
                
                Undefined,

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
                ColoredPoints3D,
                Vec3D3D
            };

        private:

            uint64_t _positionDim;
            uint64_t _valueDim;

            std::vector<float> _positions;
            std::vector<float> _values;

            VisualizationMethod _type;
    };

    class DataSetPoints2D: public ChartDataSet
    {
    };
}
