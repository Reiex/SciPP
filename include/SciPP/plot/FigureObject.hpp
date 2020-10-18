#pragma once

#include <SciPP/types.hpp>

namespace scp
{
namespace plot
{
    class FigureObject
    {
        public:

            virtual void draw(void* window);

        protected:

            uint64_t _xFigure;
            uint64_t _yFigure;
            uint64_t _wFigure;
            uint64_t _hFigure;
            bool _visible;
            bool _autoPosition;
    };
}
}
