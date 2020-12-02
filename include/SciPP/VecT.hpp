#pragma once

#include <SciPP/Vec.hpp>

namespace scp
{
    // Constructors

    template<typename T>
    Vec<T>::Vec(uint64_t count, int64_t value) :
        n(count),
        _values(count, value)
    {
    }

    template<typename T>
    Vec<T>::Vec(uint64_t count, const T& value) :
        n(count),
        _values(count, value)
    {
    }

    template<typename T>
    Vec<T>::Vec(const std::vector<T>& values) :
        n(values.size()),
        _values(values)
    {
    }


    // Assignment operators

    template<typename T>
    Vec<T>& Vec<T>::operator=(const Vec<T>& v)
    {
        assert(n == v.n);
        _values = v._values;
        return *this;
    }

    template<typename T>
    Vec<T>& Vec<T>::operator=(Vec<T>&& v)
    {
        assert(n == v.n);
        _values = std::move(v._values);
        return *this;
    }


    // Accessors

    template<typename T>
    T& Vec<T>::operator[](uint64_t i)
    {
        if (i >= n)
            throw std::out_of_range("Cannot access index " + std::to_string(i) + " of Vec of size " + std::to_string(n) + ".");
        
        return _values[i];
    }

    template<typename T>
    const T& Vec<T>::operator[](uint64_t i) const
    {
        if (i >= n)
            throw std::out_of_range("Cannot access index " + std::to_string(i) + " of Vec of size " + std::to_string(n) + ".");
        
        return _values[i];
    }
    

    // Internal operators

    template<typename T>
    Vec<T>& Vec<T>::operator+=(const Vec<T>& v)
    {
        assert(n == v.n);
        for (uint64_t i(0); i < n; i++)
            _values[i] += v._values[i];
        
        return *this;
    }
    
    template<typename T>
    Vec<T>& Vec<T>::operator-=(const Vec<T>& v)
    {
        assert(n == v.n);
        for (uint64_t i(0); i < n; i++)
            _values[i] -= v._values[i];
        
        return *this;
    }
    
    template<typename T>
    Vec<T>& Vec<T>::operator*=(const Vec<T>& v)
    {
        assert(n == v.n);
        for (uint64_t i(0); i < n; i++)
            _values[i] *= v._values[i];
        
        return *this;
    }
    
    template<typename T>
    Vec<T>& Vec<T>::operator/=(const Vec<T>& v)
    {
        assert(n == v.n);
        for (uint64_t i(0); i < n; i++)
            _values[i] /= v._values[i];
        
        return *this;
    }
    
    template<typename T>
    Vec<T>& Vec<T>::operator%=(const Vec<T>& v)
    {
        assert(n == v.n);
        for (uint64_t i(0); i < n; i++)
            _values[i] %= v._values[i];
        
        return *this;
    }
    

    // External operators

    template<typename T>
    Vec<T> operator+(const Vec<T>& u, const Vec<T>& v)
    {
        Vec<T> w(u);
        w += v;

        return w;
    }

    template<typename T>
    Vec<T>&& operator+(Vec<T>&& u, const Vec<T>& v)
    {
        u += v;
        return std::move(u);
    }
    
    template<typename T>
    Vec<T>&& operator+(const Vec<T>& u, Vec<T>&& v)
    {
        v += u;
        return std::move(v);
    }
    
    template<typename T>
    Vec<T>&& operator+(Vec<T>&& u, Vec<T>&& v)
    {
        u += v;
        return std::move(u);
    }
    

    template<typename T>
    Vec<T> operator-(const Vec<T>& u, const Vec<T>& v)
    {
        Vec<T> w(u);
        w -= v;

        return w;
    }
    
    template<typename T>
    Vec<T>&& operator-(Vec<T>&& u, const Vec<T>& v)
    {
        u -= v;
        return std::move(u);
    }
    
    template<typename T>
    Vec<T>&& operator-(const Vec<T>& u, Vec<T>&& v)
    {
        v -= u;
        return -std::move(v);
    }
    
    template<typename T>
    Vec<T>&& operator-(Vec<T>&& u, Vec<T>&& v)
    {
        u -= v;
        return std::move(u);
    }
    

    template<typename T>
    Vec<T> operator*(const Vec<T>& u, const Vec<T>& v)
    {
        Vec<T> w(u);
        w *= v;

        return w;
    }
    
    template<typename T>
    Vec<T>&& operator*(Vec<T>&& u, const Vec<T>& v)
    {
        u *= v;
        return std::move(u);
    }
    
    template<typename T>
    Vec<T>&& operator*(const Vec<T>& u, Vec<T>&& v)
    {
        v *= u;
        return std::move(v);
    }
    
    template<typename T>
    Vec<T>&& operator*(Vec<T>&& u, Vec<T>&& v)
    {
        u *= v;
        return std::move(u);
    }
    

    template<typename T>
    Vec<T> operator/(const Vec<T>& u, const Vec<T>& v)
    {
        Vec<T> w(u);
        w /= v;

        return w;
    }
    
    template<typename T>
    Vec<T>&& operator/(Vec<T>&& u, const Vec<T>& v)
    {
        u /= v;
        return std::move(u);
    }
    
    template<typename T>
    Vec<T>&& operator/(Vec<T>&& u, Vec<T>&& v)
    {
        u /= v;
        return std::move(u);
    }
    

    template<typename T>
    Vec<T> operator%(const Vec<T>& u, const Vec<T>& v)
    {
        Vec<T> w(u);
        w %= v;

        return w;
    }
    
    template<typename T>
    Vec<T>&& operator%(Vec<T>&& u, const Vec<T>& v)
    {
        u %= v;
        return std::move(u);
    }
    
    template<typename T>
    Vec<T>&& operator%(Vec<T>&& u, Vec<T>&& v)
    {
        u %= v;
        return std::move(u);
    }


    template<typename T>
    Vec<T> operator-(const Vec<T>& v)
    {
        Vec<T> u(v.n);
        for (uint64_t i(0); i < v.n; i++)
            u[i] = -v[i];
        
        return u;
    }

    template<typename T>
    Vec<T>&& operator-(Vec<T>&& v)
    {
        for (uint64_t i(0); i < v.n; i++)
            v[i] = -v[i];
        
        return std::move(v);
    }


    template<typename T>
    Vec<T> operator+(const Vec<T>& v)
    {
        return v;
    }

    template<typename T>
    Vec<T>&& operator+(Vec<T>&& v)
    {
        return std::move(v);
    }


    // Comparators
    
    template<typename T>
    bool operator==(const Vec<T>& u, const Vec<T>& v)
    {
        if (u.n != v.n)
            return false;

        for (uint64_t i(0); i < u.n; i++)
            if (u[i] != v[i])
                return false;
        
        return true;
    }
    
    template<typename T>
    bool operator!=(const Vec<T>& u, const Vec<T>& v)
    {
        return !(u == v);
    }


    // Display
    
    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Vec<T>& v)
    {
        for (uint64_t i(0); i < v.n; i++)
            if (i == v.n - 1)
                stream << v[i];
            else
                stream << v[i] << " ";

        return stream;
    }


    // Specific functions

    template<typename T>
    T minElement(const Vec<T>& a)
    {
        assert(a.n > 0);

        const T* min = &a[0];
        for (uint64_t i(0); i < a.n; i++)
                if (a[i] < *min)
                    min = &a[i];

        return *min;
    }

    template<typename T>
    T maxElement(const Vec<T>& a)
    {
        assert(a.n > 0);

        const T* max = &a[0];
        for (uint64_t i(0); i < a.n; i++)
                if (a[i] > * max)
                    max = &a[i];

        return *max;
    }

    
    template<typename T>
    T dot(const Vec<T>& u, const Vec<T>& v)
    {
        assert(u.n == v.n);
        T x(0);
        for (uint64_t i(0); i < u.n; i++)
            x += u[i] * v[i];
        
        return x;
    }
    
    template<typename T>
    Vec<T> cross(const Vec<T>& u, const Vec<T>& v)
    {
        assert(u.n == 3 && v.n == 3);
        return Vec<T>({u[1]*v[2] - u[2]*v[1], u[2]*v[0] - u[0]*v[2], u[0]*v[1] - u[1]*v[0]});
    }

    template<typename T>
    T normSq(const Vec<T> v)
    {
        return dot(v, v);
    }

    template<typename T>
    T norm(const Vec<T> v)
    {
        return std::sqrt(normSq(v));
    }


    template<typename T>
    Vec<T> convolve(const Vec<T>& a, const Vec<T>& b, ConvolveMethod method)
    {
        assert(b.n % 2 == 1);

        Vec<T> c(a.n);

        for (uint64_t i(0); i < a.n; i++)
        {
            for (uint64_t j(0); j < b.n; j++)
            {
                int64_t k = (int64_t)i + (int64_t)j - (int64_t)b.n / 2;
                T coeff;
                if (method == ConvolveMethod::Periodic)
                {
                    if (k < 0) k += a.n;
                    if (k >= a.n) k -= a.n;
                    coeff = a[k];
                }
                else if (method == ConvolveMethod::Continuous)
                {
                    if (k < 0) k = 0;
                    if (k >= a.n) k = a.n - 1;
                    coeff = a[k];
                }
                else if (method == ConvolveMethod::Zero)
                {
                    if (k < 0 || k >= a.n)
                        coeff = 0;
                    else
                        coeff = a[k];
                }
                c[i] += coeff * b[j];
            }
        }

        return c;
    }


    template<typename T>
    Vec<std::complex<T>> dft(const Vec<std::complex<T>>& f)
    {
        Vec<std::complex<T>> fh(f.n);

        for (uint64_t k(0); k < f.n; k++)
            for (uint64_t i(0); i < f.n; i++)
                fh[k] += f[i] * std::exp(std::complex<T>(0, -2 * pi * k * i / f.n));

        return fh;
    }
    
    template<typename T>
    Vec<std::complex<T>> idft(const Vec<std::complex<T>>& fh)
    {
        Vec<std::complex<T>> f(fh.n);

        for (uint64_t i(0); i < fh.n; i++)
            f[i] = std::conj(fh[i]);

        f = dft(f);

        for (uint64_t i(0); i < fh.n; i++)
            f[i] = std::conj(f[i]);

        return f / Vec<std::complex<T>>(fh.n, std::complex<T>(fh.n));
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
    
    template<typename T>
    Vec<T> dct(const Vec<T>& f)
    {
		Vec<T> fh(f.n);

		for (uint64_t k(0); k < f.n; k++)
			for (uint64_t i(0); i < f.n; i++)
				fh[k] += f[i] * dctBase<T>(f.n, k, i);

		return fh;
    }
    
    template<typename T>
    Vec<T> idct(const Vec<T>& fh)
    {
        Vec<T> f(fh.n);

        for (uint64_t k(0); k < fh.n; k++)
            for (uint64_t i(0); i < fh.n; i++)
                f[k] += fh[i] * dctBase<T>(fh.n, i, k);

        return f;
    }
}
