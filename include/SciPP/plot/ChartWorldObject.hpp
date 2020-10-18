#pragma once

#include <SciPP/types.hpp>

namespace scp
{
namespace plot
{
    class ChartWorldObject
    {
        public:

            virtual void draw(void* window);

        protected:

            float _xWorld;
            float _yWorld;
            float _zWorld;
            float _wWorld;
            float _hWorld;
            float _dWorld;
    };
}
}
