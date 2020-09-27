#pragma once

#include <SciPP/Vec.hpp>

namespace scp
{
    // Constructors

    template<typename T, uint64_t n>
    Vec<T, n>::Vec()
    {
        for (uint64_t i(0); i < n; i++)
            _values[i] = 0;
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
    Vec<T, n>::Vec(const std::vector<T>& values)
    {
        if (values.size() != n)
            throw std::runtime_error(scippError("Cannot initialize Vec of size " + std::to_string(n) + " with " + std::to_string(values.size()) + " elements."));

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
    

    // Intern operators

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
    

    // Specific functions

    template<typename T, uint64_t n>
    uint64_t Vec<T, n>::size() const
    {
        return n;
    }


    // Extern operators

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
        w -= v;

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
    Vec<T, n> operator+(const Vec<T, n>& v)
    {
        return v;
    }

    template<typename T, uint64_t n>
    Vec<T, n>&& operator-(Vec<T, n>&& v)
    {
        for (uint64_t i(0); i < n; i++)
            v[i] = -v[i];
        
        return std::move(v);
    }

    template<typename T, uint64_t n>
    Vec<T, n>&& operator+(Vec<T, n>&& v)
    {
        return std::move(v);
    }


    // Specific operators
    
    template<typename T, uint64_t n>
    T dot(const Vec<T, n>& u, const Vec<T, n>& v)
    {
        T x;
        for (uint64_t i(0); i < n; i++)
            x += u[i] * v[i];
        
        return x;
    }
    
    template<typename T>
    Vec<T, 3> cross(const Vec<T, 3>& u, const Vec<T, 3>& v)
    {
        return Vec<T, 3>({u[1]*v[2] - u[2]*v[1], u[2]*v[0] - u[0]*v[2], u[0]*v[1] - u[1]*v[0]});
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
}
