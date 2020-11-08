#pragma once

#include <SciPP/misc.hpp>

namespace scp
{
    template<typename TBase, typename TPow>
    TBase expoSq(TBase const& x, TPow n)
    {
        if (n < 0)
            throw std::runtime_error("Cannot call expoSq with n < 0.");

        if (n == 0)
            return (int64_t) 1;

        if (n == 1)
            return x;

        TPow k(n - 1);
        TBase r(x), p(x);

        while (k != 0)
        {
            if (k % 2 == 0)
            {
                p *= p;
                k /= 2;
            }
            else
            {
                r *= p;
                k -= 1;
            }
        }

        return r;
    }
    
    template<typename T>
    T gcd(const T& a, const T& b)
    {
        if (a == 0 || b == 0)
            return 1;

        T u(a), v(b), r(u % v);

        while (r != 0)
        {
            u = v;
            v = r;
            r = u % v;
        }

        if (v < 0)
            return -v;
        
        return v;
    }
}
