#pragma once

#include <SciPP/Vec.hpp>

namespace scp
{
    // Constructors

    template<typename T, uint64_t n>
    Vec<T, n>::Vec()
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] = int64_t(0);
    }

    template<typename T, uint64_t n>
    Vec<T, n>::Vec(int64_t value)
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] = value;
    }

    template<typename T, uint64_t n>
    Vec<T, n>::Vec(const T& value)
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] = value;
    }

    template<typename T, uint64_t n>
    Vec<T, n>::Vec(const std::array<T, n>& values)
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] = values[i];
    }


    // Accessors

    template<typename T, uint64_t n>
    T& Vec<T, n>::operator[](uint64_t i)
    {
        if (i >= n)
            throw std::runtime_error(scippError("Cannot access index " + std::to_string(i) + " of Vec of size " + std::to_string(n) + "."));
        
        return _values[i];
    }

    template<typename T, uint64_t n>
    const T& Vec<T, n>::operator[](uint64_t i) const
    {
        if (i >= n)
            throw std::runtime_error(scippError("Cannot access index " + std::to_string(i) + " of Vec of size " + std::to_string(n) + "."));
        
        return _values[i];
    }
    

    // Internal operators

    template<typename T, uint64_t n>
    Vec<T, n>& Vec<T, n>::operator+=(const Vec<T, n>& v)
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] += v._values[i];
        
        return *this;
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>& Vec<T, n>::operator-=(const Vec<T, n>& v)
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] -= v._values[i];
        
        return *this;
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>& Vec<T, n>::operator*=(const Vec<T, n>& v)
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] *= v._values[i];
        
        return *this;
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>& Vec<T, n>::operator/=(const Vec<T, n>& v)
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] /= v._values[i];
        
        return *this;
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>& Vec<T, n>::operator%=(const Vec<T, n>& v)
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] %= v._values[i];
        
        return *this;
    }
    

    // External operators

    template<typename T, uint64_t n>
    Vec<T, n> operator+(const Vec<T, n>& u, const Vec<T, n>& v)
    {
        Vec<T, n> w(u);
        w += v;

        return w;
    }

    template<typename T, uint64_t n>
    Vec<T, n>&& operator+(Vec<T, n>&& u, const Vec<T, n>& v)
    {
        u += v;
        return std::move(u);
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator+(const Vec<T, n>& u, Vec<T, n>&& v)
    {
        v += u;
        return std::move(v);
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator+(Vec<T, n>&& u, Vec<T, n>&& v)
    {
        u += v;
        return std::move(u);
    }
    

    template<typename T, uint64_t n>
    Vec<T, n> operator-(const Vec<T, n>& u, const Vec<T, n>& v)
    {
        Vec<T, n> w(u);
        w -= v;

        return w;
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator-(Vec<T, n>&& u, const Vec<T, n>& v)
    {
        u -= v;
        return std::move(u);
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator-(const Vec<T, n>& u, Vec<T, n>&& v)
    {
        v -= u;
        return -std::move(v);
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator-(Vec<T, n>&& u, Vec<T, n>&& v)
    {
        u -= v;
        return std::move(u);
    }
    

    template<typename T, uint64_t n>
    Vec<T, n> operator*(const Vec<T, n>& u, const Vec<T, n>& v)
    {
        Vec<T, n> w(u);
        w *= v;

        return w;
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator*(Vec<T, n>&& u, const Vec<T, n>& v)
    {
        u *= v;
        return std::move(u);
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator*(const Vec<T, n>& u, Vec<T, n>&& v)
    {
        v *= u;
        return std::move(v);
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator*(Vec<T, n>&& u, Vec<T, n>&& v)
    {
        u *= v;
        return std::move(u);
    }
    

    template<typename T, uint64_t n>
    Vec<T, n> operator/(const Vec<T, n>& u, const Vec<T, n>& v)
    {
        Vec<T, n> w(u);
        w /= v;

        return w;
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator/(Vec<T, n>&& u, const Vec<T, n>& v)
    {
        u /= v;
        return std::move(u);
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator/(Vec<T, n>&& u, Vec<T, n>&& v)
    {
        u /= v;
        return std::move(u);
    }
    

    template<typename T, uint64_t n>
    Vec<T, n> operator%(const Vec<T, n>& u, const Vec<T, n>& v)
    {
        Vec<T, n> w(u);
        w %= v;

        return w;
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator%(Vec<T, n>&& u, const Vec<T, n>& v)
    {
        u %= v;
        return std::move(u);
    }
    
    template<typename T, uint64_t n>
    Vec<T, n>&& operator%(Vec<T, n>&& u, Vec<T, n>&& v)
    {
        u %= v;
        return std::move(u);
    }


    template<typename T, uint64_t n>
    Vec<T, n> operator-(const Vec<T, n>& v)
    {
        Vec<T, n> u;
        for (uint64_t i(0); i < n; i++)
            u[i] = -v[i];
        
        return u;
    }

    template<typename T, uint64_t n>
    Vec<T, n>&& operator-(Vec<T, n>&& v)
    {
        for (uint64_t i(0); i < n; i++)
            v[i] = -v[i];
        
        return std::move(v);
    }


    template<typename T, uint64_t n>
    Vec<T, n> operator+(const Vec<T, n>& v)
    {
        return v;
    }

    template<typename T, uint64_t n>
    Vec<T, n>&& operator+(Vec<T, n>&& v)
    {
        return std::move(v);
    }


    // Comparators
    
    template<typename T, uint64_t n>
    bool operator==(const Vec<T, n>& u, const Vec<T, n>& v)
    {
        for (uint64_t i(0); i < n; i++)
            if (u[i] != v[i])
                return false;
        
        return true;
    }
    
    template<typename T, uint64_t n>
    bool operator!=(const Vec<T, n>& u, const Vec<T, n>& v)
    {
        return !(u == v);
    }


    // Display
    
    template<typename T, uint64_t n>
    std::ostream& operator<<(std::ostream& stream, const Vec<T, n>& v)
    {
        stream << "<";
        for (uint64_t i(0); i < n; i++)
            if (i == n - 1)
                stream << v[i];
            else
                stream << v[i] << ", ";
        stream << ">";

        return stream;
    }


    // Specific functions
    
    template<typename T, uint64_t n>
    T dot(const Vec<T, n>& u, const Vec<T, n>& v)
    {
        T x(0);
        for (uint64_t i(0); i < n; i++)
            x += u[i] * v[i];
        
        return x;
    }
    
    template<typename T>
    Vec<T, 3> cross(const Vec<T, 3>& u, const Vec<T, 3>& v)
    {
        return Vec<T, 3>({u[1]*v[2] - u[2]*v[1], u[2]*v[0] - u[0]*v[2], u[0]*v[1] - u[1]*v[0]});
    }

    template<typename T, uint64_t n>
    T normSq(const Vec<T, n> v)
    {
        return dot(v, v);
    }

    template<typename T, uint64_t n>
    T norm(const Vec<T, n> v)
    {
        return std::sqrt(normSq(v));
    }

    template<typename T, uint64_t n>
    Vec<std::complex<T>, n> dft(const Vec<std::complex<T>, n>& f)
    {
        Vec<std::complex<T>, n> fh;

        for (uint64_t k(0); k < n; k++)
            for (uint64_t i(0); i < n; i++)
                fh[k] += f[i] * std::exp(std::complex<T>(0, -2 * pi * k * i / n));

        return fh;
    }
    
    template<typename T, uint64_t n>
    Vec<std::complex<T>, n> idft(const Vec<std::complex<T>, n>& fh)
    {
        Vec<std::complex<T>, n> f;

        for (uint64_t i(0); i < n; i++)
            f[i] = std::conj(fh[i]);

        f = dft(f);

        for (uint64_t i(0); i < n; i++)
            f[i] = std::conj(f[i]);

        return f / Vec<std::complex<T>, n>(std::complex<T>(n));
    }

    namespace
    {
        template<typename T>
        T dctBase(uint64_t n, uint64_t k, uint64_t i)
        {
            if (k == 0)
                return std::cos(pi * (i + 0.5L) * k / n) / std::sqrt(n);
            else
                return std::sqrt(2.0 / n) * std::cos(pi * (i + 0.5) * k / n);
        }
    }
    
    template<typename T, uint64_t n>
    Vec<T, n> dct(const Vec<T, n>& f)
    {
		Vec<T, n> fh;

		for (uint64_t k(0); k < n; k++)
			for (uint64_t i(0); i < n; i++)
				fh[k] += f[i] * dctBase<T>(n, k, i);

		return fh;
    }
    
    template<typename T, uint64_t n>
    Vec<T, n> idct(const Vec<T, n>& fh)
    {
        Vec<T, n> f;

        for (uint64_t k(0); k < n; k++)
            for (uint64_t i(0); i < n; i++)
                f[k] += fh[i] * dctBase<T>(n, i, k);

        return f;
    }
}
