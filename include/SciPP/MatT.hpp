#pragma once

#include <SciPP/Mat.hpp>

namespace scp
{
    // Constructors

    template<typename T>
    Mat<T>::Mat(uint64_t row, uint64_t col, int64_t x) :
        m(row),
        n(col),
        _values(m, Vec<T>(n, x))
    {
    }
    
    template<typename T>
    Mat<T>::Mat(uint64_t row, uint64_t col, const T& x) :
        m(row),
        n(col),
        _values(m, Vec<T>(n, x))
    {
    }
    
    template<typename T>
    Mat<T>::Mat(const std::vector<std::vector<T>>& values) :
        m(values.size()),
        n(values.size() == 0 ? 0 : values[0].size()),
        _values(m, Vec<T>(n, (int64_t) 0))
    {
        for (uint64_t i(0); i < _values.size(); i++)
        {
            assert(values[i].size() == n);
            _values[i] = Vec<T>(values[i]);
        }
    }

    template<typename T>
    Mat<T> Mat<T>::identity(uint64_t size, int64_t x)
    {
        Mat<T> a(size, size);
        for (uint64_t i(0); i < size; i++)
            a[i][i] = x;

        return a;
    }

    template<typename T>
    Mat<T> Mat<T>::identity(uint64_t size, const T& x)
    {
        Mat<T> a(size, size);
        for (uint64_t i(0); i < size; i++)
            a[i][i] = x;

        return a;
    }


    // Assignment operators

    template<typename T>
    Mat<T>& Mat<T>::operator=(const Mat<T>& a)
    {
        assert(m == a.m && n == a.n);
        _values = a._values;
        return *this;
    }

    template<typename T>
    Mat<T>& Mat<T>::operator=(Mat<T>&& a)
    {
        assert(m == a.m && n == a.n);
        _values = std::move(a._values);
        return *this;
    }


    // Accessors

    template<typename T>
    Vec<T>& Mat<T>::operator[](uint64_t i)
    {
        if (i >= m)
            throw std::out_of_range("Cannot access index " + std::to_string(i) + " of Mat of size {" + std::to_string(m) + ", " + std::to_string(n) + "}.");

        return _values[i];
    }

    template<typename T>
    const Vec<T>& Mat<T>::operator[](uint64_t i) const
    {
        if (i >= m)
            throw std::out_of_range("Cannot access index " + std::to_string(i) + " of Mat of size {" + std::to_string(m) + ", " + std::to_string(n) + "}.");

        return _values[i];
    }
    

    // Internal operators

    template<typename T>
    Mat<T>& Mat<T>::operator+=(const Mat<T>& a)
    {
        assert(m == a.m && n == a.n);

        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                _values[i][j] += a._values[i][j];
        
        return *this;
    }
    
    template<typename T>
    Mat<T>& Mat<T>::operator-=(const Mat<T>& a)
    {
        assert(m == a.m && n == a.n);

        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                _values[i][j] -= a._values[i][j];

        return *this;
    }

    template<typename T>
    Mat<T>& Mat<T>::operator*=(const T& x)
    {
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                _values[i][j] *= x;

        return *this;
    }

    template<typename T>
    Mat<T>& Mat<T>::operator/=(const T& x)
    {
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                _values[i][j] /= x;

        return *this;
    }


    // External operators

    template<typename T>
    Mat<T> operator+(const Mat<T>& a, const Mat<T>& b)
    {
        Mat<T> c(a);
        c += b;

        return c;
    }

    template<typename T>
    Mat<T>&& operator+(Mat<T>&& a, const Mat<T>& b)
    {
        a += b;

        return std::move(a);
    }
    
    template<typename T>
    Mat<T>&& operator+(const Mat<T>& a, Mat<T>&& b)
    {
        b += a;

        return std::move(b);
    }
    
    template<typename T>
    Mat<T>&& operator+(Mat<T>&& a, Mat<T>&& b)
    {
        a += b;

        return std::move(a);
    }
    

    template<typename T>
    Mat<T> operator-(const Mat<T>& a, const Mat<T>& b)
    {
        Mat<T> c(a);
        c -= b;
        
        return c;
    }
    
    template<typename T>
    Mat<T>&& operator-(Mat<T>&& a, const Mat<T>& b)
    {
        a -= b;

        return std::move(a);
    }
    
    template<typename T>
    Mat<T>&& operator-(const Mat<T>& a, Mat<T>&& b)
    {
        b -= a;

        return -std::move(b);
    }
    
    template<typename T>
    Mat<T>&& operator-(Mat<T>&& a, Mat<T>&& b)
    {
        a -= b;

        return std::move(a);
    }
    
    namespace
    {
        template<typename T>
        void multiplyThread(Vec<T>& out, const Mat<T>& a, const Mat<T>& b, uint64_t i)
        {
            for (uint64_t j(0); j < b.n; j++)
                for (uint64_t k(0); k < a.n; k++)
                    out[j] += a[i][k] * b[k][j];
        }
    }

    template<typename T>
    Mat<T> operator*(const Mat<T>& a, const Mat<T>& b)
    {
        assert(a.n == b.m);

        std::vector<std::thread> threads(a.m);

        Mat<T> c(a.m, b.n);
        for (uint64_t i(0); i < a.m; i++)
            threads[i] = std::thread(multiplyThread<T>, std::ref(c[i]), std::ref(a), std::ref(b), i);

        for (uint64_t i(0); i < threads.size(); i++)
            threads[i].join();
        
        return c;
    }


    template<typename T>
    Vec<T> operator*(const Mat<T>& a, const Vec<T>& b)
    {
        assert(a.n == b.n);

        Vec<T> c(a.m);

        for (uint64_t i(0); i < a.m; i++)
            c[i] = dot(a[i], b);
        
        return c;
    }

    template<typename T>
    Vec<T> operator*(const Vec<T>& a, const Mat<T>& b)
    {
        assert(a.n == b.m);

        Vec<T> c(b.n);

        for (uint64_t i(0); i < b.n; i++)
            for (uint64_t j(0); j < b.m; j++)
                c[i] += b[j][i]*a[j];

        return c;
    }


    template<typename T>
    Mat<T> operator*(const Mat<T>& a, const T& x)
    {
        Mat<T> b(a);
        b *= x;

        return b;
    }

    template<typename T>
    Mat<T>&& operator*(Mat<T>&& a, const T& x)
    {
        a *= x;
        return std::move(a);
    }


    template<typename T>
    Mat<T> operator/(const Mat<T>& a, const T& x)
    {
        Mat<T> b(a);
        b /= x;

        return b;
    }

    template<typename T>
    Mat<T>&& operator/(Mat<T>&& a, const T& x)
    {
        a /= x;
        return std::move(a);
    }


    template<typename T>
    Mat<T> operator-(const Mat<T>& a)
    {
        Mat<T> c(a.m, a.n);
        
        for (uint64_t i(0); i < a.m; i++)
            for (uint64_t j(0); j < a.n; j++)
                c[i][j] = -a[i][j];
        
        return c;
    }
    
    template<typename T>
    Mat<T>&& operator-(Mat<T>&& a)
    {
        for (uint64_t i(0); i < a.m; i++)
            for (uint64_t j(0); j < a.n; j++)
                a[i][j] = -a[i][j];
        
        return std::move(a);
    }
    

    template<typename T>
    Mat<T> operator+(const Mat<T>& a)
    {
        return a;
    }
    
    template<typename T>
    Mat<T>&& operator+(Mat<T>&& a)
    {
        return std::move(a);
    }
    

    // Comparators

    template<typename T>
    bool operator==(const Mat<T>& a, const Mat<T>& b)
    {
        if (a.m != b.m || a.n != b.n)
            return false;

        for (uint64_t i(0); i < a.m; i++)
            for (uint64_t j(0); j < a.n; j++)
                if (a[i][j] != b[i][j])
                    return false;

        return true;
    }
    
    template<typename T>
    bool operator!=(const Mat<T>& a, const Mat<T>& b)
    {
        return !(a == b);
    }
    

    // Display

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Mat<T>& a)
    {
        for (uint64_t i(0); i < a.m; i++)
        {
            for (uint64_t j(0); j < a.n; j++)
                if (j == a.n - 1)
                    stream << a[i][j];
                else
                    stream << a[i][j] << " ";
            if (i != a.m - 1)
                stream << std::endl;
        }

        return stream;
    }
    

    // Specific functions

    template<typename T>
    T minElement(const Mat<T>& a)
    {
        assert(a.m > 0 && a.n > 0);

        T* min = &a[0][0];
        for (uint64_t i(0); i < a.m; i++)
            for (uint64_t j(0); j < a.n; j++)
                if (a[i][j] < *min)
                    min = &a[i][j];
        
        return *min;
    }

    template<typename T>
    T maxElement(const Mat<T>& a)
    {
        assert(a.m > 0 && a.n > 0);

        T* max = &a[0][0];
        for (uint64_t i(0); i < a.m; i++)
            for (uint64_t j(0); j < a.n; j++)
                if (a[i][j] > *max)
                    max = &a[i][j];

        return *max;
    }


    template<typename T>
    Mat<T> inverse(const Mat<T>& a)
    {
        assert(a.m == a.n);

        Mat<T> b(a), inv(Mat<T>::identity(a.n));

        for (uint64_t j(0); j < a.n; j++)
        {
            if (b[j][j] == 0)
            {
                for (uint64_t i(j + 1); i < a.n; i++)
                {
                    if (b[i][j] != 0)
                    {
                        inv[i] /= Vec<T>(a.n, b[i][j]);
                        b[i] /= Vec<T>(a.n, b[i][j]);
                        inv[j] += inv[i];
                        b[j] += b[i];
                        break;
                    }
                }

                if (b[j][j] == 0)
                    throw std::runtime_error("The matrix cannot be inverted.");
            }
            else
            {
                inv[j] /= Vec<T>(a.n, b[j][j]);
                b[j] /= Vec<T>(a.n, b[j][j]);
            }

            for (uint64_t i(j + 1); i < a.n; i++)
            {
                if (b[i][j] != 0)
                {
                    inv[i] -= Vec<T>(a.n, b[i][j]) * inv[j];
                    b[i] -= Vec<T>(a.n, b[i][j]) * b[j];
                }
            }
        }

        for (uint64_t j(a.n - 1); j != UINT64_MAX; j--)
        {
            for (uint64_t i(j - 1); i != UINT64_MAX; i--)
            {
                if (b[i][j] != 0)
                {
                    inv[i] -= Vec<T>(a.n, b[i][j]) * inv[j];
                    b[i] -= Vec<T>(a.n, b[i][j]) * b[j];
                }
            }
        }

        return inv;
    }

    template<typename T>
    Mat<T> transpose(const Mat<T>& a)
    {
        Mat<T> b(a.n, a.m);
        for (uint64_t i(0); i < a.n; i++)
            for (uint64_t j(0); j < a.m; j++)
                b[i][j] = a[j][i];

        return b;
    }

    template<typename T>
    T det(const Mat<T>& a)
    {
        assert(a.m == a.n);

        Mat<T> b(a);

        for (uint64_t j(0); j < a.n; j++)
        {
            if (b[j][j] == 0)
            {
                for (uint64_t i(j + 1); i < a.n; i++)
                {
                    if (b[i][j] != 0)
                    {
                        b[j] += b[i];
                        break;
                    }
                }

                if (b[j][j] == 0)
                    return 0;
            }

            for (uint64_t i(j + 1); i < a.n; i++)
                b[i] -= Vec<T>(a.n, b[i][j] / b[j][j]) * b[j];
        }

        T prod(b[0][0]);
        for (uint64_t i(1); i < a.n; i++)
            prod *= b[i][i];

        return prod;
    }


    namespace
    {
        template<typename T>
        void convolveThread(Vec<T>& out, const Mat<T>& a, const Mat<T>& b, uint64_t i, ConvolveMethod method)
        {
            uint64_t m = a.m;
            uint64_t n = a.n;
            uint64_t p = b.m;
            uint64_t q = b.n;

            for (uint64_t j(0); j < n; j++)
            {
                for (uint64_t k(0); k < p; k++)
                {
                    for (uint64_t l(0); l < q; l++)
                    {
                        int64_t x = (int64_t)i + (int64_t)k - (int64_t)p/2;
                        int64_t y = (int64_t)j + (int64_t)l - (int64_t)q/2;
                        T coeff;
                        if (method == ConvolveMethod::Periodic)
                        {
                            if (x < 0) x += m;
                            if (y < 0) y += n;
                            if (x >= m) x -= m;
                            if (y >= n) y -= n;
                            coeff = a[x][y];
                        }
                        else if (method == ConvolveMethod::Continuous)
                        {
                            if (x < 0) x = 0;
                            if (y < 0) y = 0;
                            if (x >= m) x = m-1;
                            if (y >= n) y = n-1;
                            coeff = a[x][y];
                        }
                        else if (method == ConvolveMethod::Zero)
                        {
                            if (x < 0 || x >= m || y < 0 || y >= n)
                                coeff = 0;
                            else
                                coeff = a[x][y];
                        }
                        out[j] += coeff * b[k][l];
                    }
                }
            }
        }
    }

    template<typename T>
    Mat<T> convolve(const Mat<T>& a, const Mat<T>& b, ConvolveMethod method)
    {
        uint64_t m = a.m;
        uint64_t n = a.n;
        uint64_t p = b.m;
        uint64_t q = b.n;

        assert(p % 2 == 1 && q % 2 == 1);
        assert(p <= m && q <= n);

        Mat<T> c(m, n);

        std::vector<std::thread> threads(m);

        for (uint64_t i(0); i < m; i++)
            threads[i] = std::thread(convolveThread<T>, std::ref(c[i]), std::ref(a), std::ref(b), i, method);

        for (uint64_t i(0); i < threads.size(); i++)
            threads[i].join();

        return c;
    }
    
    template<typename T>
    Mat<T> hadamardProduct(const Mat<T>& a, const Mat<T>& b)
    {
        assert(a.m == b.m && a.n == b.n);

        Mat<T> c(a);

        for (uint64_t i(0); i < a.m; i++)
            for (uint64_t j(0); j < a.n; j++)
                c[i][j] *= b[i][j];

        return c;
    }


    template<typename T>
    Mat<std::complex<T>> dft(const Mat<std::complex<T>>& f)
    {
        Mat<std::complex<T>> wM(f.m, f.m);
        Mat<std::complex<T>> wN(f.n, f.n);

        for (uint64_t i(0); i < f.m; i++)
            for (uint64_t j(0); j < f.m; j++)
                wM[i][j] = std::exp(std::complex<T>(0, -2 * pi * i * j / f.m));

        for (uint64_t i(0); i < f.n; i++)
            for (uint64_t j(0); j < f.n; j++)
                wN[i][j] = std::exp(std::complex<T>(0, -2 * pi * i * j / f.n));

        return wM * f * wN;
    }

    template<typename T>
    Mat<std::complex<T>> idft(const Mat<std::complex<T>>& fh)
    {
        Mat<std::complex<T>> wM(fh.m, fh.m);
        Mat<std::complex<T>> wN(fh.n, fh.n);

        for (uint64_t i(0); i < fh.m; i++)
            for (uint64_t j(0); j < fh.m; j++)
                wM[i][j] = std::exp(std::complex<T>(0, 2 * pi * i * j / fh.m));

        for (uint64_t i(0); i < fh.n; i++)
            for (uint64_t j(0); j < fh.n; j++)
                wN[i][j] = std::exp(std::complex<T>(0, 2 * pi * i * j / fh.n));

        return wM * fh * wN / std::complex<T>(fh.m * fh.n, 0);
    }


    namespace
    {
        template<typename T>
        T dct2DBase(uint64_t M, uint64_t N, uint64_t p, uint64_t q, uint64_t m, uint64_t n)
        {
            T r(2 * std::cos(pi * p * (m + 0.5) / M) * std::cos(pi * q * (n + 0.5) / N));

            if (p == 0)
                r /= std::sqrt(2.0L);

            if (q == 0)
                r /= std::sqrt(2.0L);

            return r;
        }
    }
    
    template<typename T>
    Mat<T> dct(const Mat<T>& f)
    {
        Mat<T> wM(f.m, f.m);
        Mat<T> wN(f.n, f.n);

        for (uint64_t i(0); i < f.m; i++)
            for (uint64_t j(0); j < f.m; j++)
                if (i == 0)
                    wM[i][j] = 1.L;
                else
                    wM[i][j] = std::sqrt(2.f)*cos(pi*i*(j + 0.5)/f.m);

        for (uint64_t i(0); i < f.n; i++)
            for (uint64_t j(0); j < f.n; j++)
                if (j == 0)
                    wN[i][j] = 1.L;
                else
                    wN[i][j] = std::sqrt(2.f)*cos(pi*j*(i + 0.5)/f.n);

        return wM * f * wN;
    }
    
    template<typename T>
    Mat<T> idct(const Mat<T>& fh)
    {
        Mat<T> wM(fh.m, fh.m);
        Mat<T> wN(fh.n, fh.n);

        for (uint64_t i(0); i < fh.m; i++)
            for (uint64_t j(0); j < fh.m; j++)
                if (j == 0)
                    wM[i][j] = 1.L;
                else
                    wM[i][j] = std::sqrt(2.f)*cos(pi*j*(i + 0.5)/fh.m);

        for (uint64_t i(0); i < fh.n; i++)
            for (uint64_t j(0); j < fh.n; j++)
                if (i == 0)
                    wN[i][j] = 1.L / (fh.m*fh.n);
                else
                    wN[i][j] = std::sqrt(2.f)*cos(pi*i*(j + 0.5)/fh.n) / (fh.m*fh.n);

        return wM * fh * wN;
    }
}
