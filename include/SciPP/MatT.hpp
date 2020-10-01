#pragma once

#include <SciPP/Mat.hpp>

namespace scp
{
    // Constructors

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>::Mat()
    {
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                _values[i][j] = 0;
    }

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>::Mat(int64_t x)
    {
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                if (i == j)
                    _values[i][j] = x;
                else
                    _values[i][j] = 0;
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>::Mat(const T& x)
    {
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                if (i == j)
                    _values[i][j] = x;
                else
                    _values[i][j] = 0;
    }

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>::Mat(const std::vector<T>& diag)
    {
        if (diag.size() != std::min(m, n))
            throw std::runtime_error(scippError("Cannot initialize Mat<" + std::to_string(m) + ", " + std::to_string(n) + "> with " + std::to_string(diag.size()) + " diagonal values"));

        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                if (i == j)
                    _values[i][j] = diag[i];
                else
                    _values[i][j] = 0;
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>::Mat(const std::vector<std::vector<T>>& values)
    {
        if (values.size() == 0)
            throw std::runtime_error(scippError("Cannot initialize Mat<" + std::to_string(m) + ", " + std::to_string(n) + "> with an empty vector"));

        if (values.size() != m || values[0].size() != n)
            throw std::runtime_error(scippError("Cannot initialize Mat<" + std::to_string(m) + ", " + std::to_string(n) + "> with " + std::to_string(values.size()) + "x" + std::to_string(values[0].size()) + " values"));

        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                _values[i][j] = values[i][j];
    }
    

    // Internal operators

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>& Mat<T, m, n>::operator+=(const Mat<T, m, n>& a)
    {
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                _values[i][j] += a._values[i][j];
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>& Mat<T, m, n>::operator-=(const Mat<T, m, n>& a)
    {
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                _values[i][j] -= a._values[i][j];
    }


    // Accessors
    
    template<typename T, uint64_t m, uint64_t n>
    Vec<T, n>& Mat<T, m, n>::operator[](uint64_t i)
    {
        if (i >= m)
            throw std::runtime_error(scippError("Cannot access index " + std::to_string(i) + " of Mat<" + std::to_string(m) + ", " + std::to_string(n) + ">."));
        
        return _values[i];
    }
    
    template<typename T, uint64_t m, uint64_t n>
    const Vec<T, n>& Mat<T, m, n>::operator[](uint64_t i) const
    {
        if (i >= m)
            throw std::runtime_error(scippError("Cannot access index " + std::to_string(i) + " of Mat<" + std::to_string(m) + ", " + std::to_string(n) + ">."));
        
        return _values[i];
    }

    // External operators

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator+(const Mat<T, m, n>& a, const Mat<T, m, n>& b)
    {
        Mat<T, m, n> c(a);
        c += b;

        return c;
    }

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(Mat<T, m, n>&& a, const Mat<T, m, n>& b)
    {
        a += b;

        return std::move(a);
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(const Mat<T, m, n>& a, Mat<T, m, n>&& b)
    {
        b += a;

        return std::move(b);
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(Mat<T, m, n>&& a, Mat<T, m, n>&& b)
    {
        a += b;

        return std::move(a);
    }
    

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator-(const Mat<T, m, n>& a, const Mat<T, m, n>& b)
    {
        Mat<T, m, n> c(a);
        c -= b;
        
        return c;
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(Mat<T, m, n>&& a, const Mat<T, m, n>& b)
    {
        a -= b;

        return std::move(a);
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(const Mat<T, m, n>& a, Mat<T, m, n>&& b)
    {
        b -= a;

        return -std::move(b);
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(Mat<T, m, n>&& a, Mat<T, m, n>&& b)
    {
        a -= b;

        return std::move(a);
    }
    

    template<typename T, uint64_t m, uint64_t n, uint64_t p>
    Mat<T, m, p> operator*(const Mat<T, m, n>& a, const Mat<T, n, p>& b)
    {
        Mat<T, m, p> c;
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < p; j++)
                for (uint64_t k(0); k < n; k++)
                    c[i][j] += a[i][k] * b[k][j];
        
        return c;
    }
    

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator-(const Mat<T, m, n>& a)
    {
        Mat<T, m, n> c;
        
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                c[i][j] = -a[i][j];
        
        return c;
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(Mat<T, m, n>&& a)
    {
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                a[i][j] = -a[i][j];
        
        return std::move(a);
    }
    

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator+(const Mat<T, m, n>& a)
    {
        return a;
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(Mat<T, m, n>&& a)
    {
        return std::move(a);
    }
    

    // Comparators

    template<typename T, uint64_t m, uint64_t n>
    bool operator==(const Mat<T, m, n>& a, const Mat<T, m, n>& b)
    {
        for (uint64_t i(0); i < m; i++)
            for (uint64_t j(0); j < n; j++)
                if (a[i][j] != b[i][j])
                    return false;

        return true;
    }
    
    template<typename T, uint64_t m, uint64_t n>
    bool operator!=(const Mat<T, m, n>& a, const Mat<T, m, n>& b)
    {
        return !(a == b);
    }
    

    // Display

    template<typename T, uint64_t m, uint64_t n>
    std::ostream& operator<<(std::ostream& stream, const Mat<T, m, n>& a)
    {
        stream << "(";
        for (uint64_t i(0); i < m; i++)
        {
            if (i != 0)
                stream << " ";
            for (uint64_t j(0); j < n; j++)
                if (j == n - 1)
                    stream << a[i][j];
                else
                    stream << a[i][j] << " ";
            if (i != m - 1)
                stream << std::endl;
        }
        stream << ")";

        return stream;
    }
    

    // Specific functions

    template<typename T, uint64_t m, uint64_t n, uint64_t p, uint64_t q>
    Mat<T, m, n> convolve(const Mat<T, m, n>& a, const Mat<T, p, q>& b, ConvolveMethod method)
    {
        if (p % 2 == 0 || q % 2 == 0)
            throw std::runtime_error(scippError("Cannot use Mat<" + std::to_string(p) + ", " + std::to_string(q) + "> as a convolution matrix."));

        Mat<T, m, n> c;

        for (uint64_t i(0); i < m; i++)
        {
            for (uint64_t j(0); j < n; j++)
            {
                for (uint64_t k(0); k < p; k++)
                {
                    for (uint64_t l(0); l < q; l++)
                    {
                        int64_t ox((int64_t)k - p / 2), oy((int64_t)l - q / 2);
                        T coeff;
                        if (method == ConvolveMethod::Periodic)
                        {
                            coeff = a[(i + ox) % m][(j + oy) % n];
                        }
                        else if (method == ConvolveMethod::Continuous)
                        {
                            if (i + ox > m - 1)
                                ox = m - 1 - i;
                            if (i + ox < 0)
                                ox = -(int)i;
                            if (j + oy > n - 1)
                                oy = n - 1 - j;
                            if (j + oy < 0)
                                oy = -(int)j;

                            coeff = a[i + ox][j + oy];
                        }
                        else if (method == ConvolveMethod::Zero)
                        {
                            if (i + ox > m - 1 || i + ox < 0 || j + oy > n - 1 || j + oy < 0)
                                coeff = 0;
                            else
                                coeff = a[i + ox][j + oy];
                        }
                        c[i][j] += coeff * b[k][l];
                    }
                }
            }
        }

        return c;
    }
    
    template<typename T, uint64_t n>
    Mat<T, n, n> inverse(const Mat<T, n, n>& a)
    {
        Mat<T, n, n> b(a), inv((int64_t) 1);

        for (uint64_t j(0); j < n; j++)
        {
            if (b[j][j] == 0)
            {
                for (uint64_t i(j + 1); i < n; i++)
                {
                    if (b[i][j] != 0)
                    {
                        inv[i] /= b[i][j];
                        b[i] /= b[i][j];
                        inv[j] += inv[i];
                        b[j] += b[i];
                        break;
                    }
                }

                if (b[j][j] == 0)
                    throw std::runtime_error(scippError("The matrix cannot be inverted."));
            }
            else
            {
                inv[j] /= b[j][j];
                b[j] /= b[j][j];
            }

            for (uint64_t i(j + 1); i < n; i++)
            {
                if (b[i][j] != 0)
                {
                    inv[i] -= Vec<T, n>(b[i][j]) * inv[j];
                    b[i] -= Vec<T, n>(b[i][j]) * b[j];
                }
            }
        }

        for (uint64_t j(n - 1); j != UINT64_MAX; j--)
        {
            for (uint64_t i(j - 1); i != UINT64_MAX; i--)
            {
                if (b[i][j] != 0)
                {
                    inv[i] -= Vec<T, n>(b[i][j]) * inv[j];
                    b[i] -= Vec<T, n>(b[i][j]) * b[j];
                }
            }
        }

        return inv;
    }
    
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, n, m> transpose(const Mat<T, m, n>& a)
    {
        Mat<T, n, m> b;
        for (uint64_t i(0); i < n; i++)
            for (uint64_t j(0); j < m; j++)
                b[i][j] = a[j][i];
        
        return b;
    }

    template<typename T, uint64_t n>
    T det(const Mat<T, n, n>& a)
    {
        Mat<T, n, n> b(a);

        for (uint64_t j(0); j < n; j++)
        {
            if (b[j][j] == 0)
            {
                for (uint64_t i(j + 1); i < n; i++)
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

            for (uint64_t i(j + 1); i < n; i++)
                b[i] -= Vec<T, n>(b[i][j] / b[j][j]) * b[j];
        }

        T prod(b[0][0]);
        for (uint64_t i(1); i < n; i++)
            prod *= b[i][i];

        return prod;
    }
}
