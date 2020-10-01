#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Mat.hpp
/// \brief Functions and classes for matrices manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Mat.
/// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <SciPP/types.hpp>

namespace scp
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \class Mat
    /// \brief Class for matrices manipulations.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t m, uint64_t n = m>
    class Mat
    {
        public:

            static const uint64_t M = m;  ///< Number of lines of the matrix.
            static const uint64_t N = n;  ///< Number of columns of the matrix.

            Mat();                                           ///< Default constructor. Init the matrix to 0.
            Mat(int64_t x);                                  ///< Init the matrix to `x * identity`.
            Mat(const T& x);                                 ///< Init the matrix to `x * identity`.
            Mat(const std::vector<T>& diag);                 ///< Init the matrix with its diagonal values. `diag` must be of size `std::min(m, n)`.
            Mat(const std::vector<std::vector<T>>& values);  ///< Init the matrix directly. `values` must be of size `m` and each element of values must be of size `n`.
            Mat(const Mat<T, m, n>& a) = default;
            Mat(Mat<T, m, n>&& a) = default;

            Mat<T, m, n>& operator=(const Mat<T, m, n>& a) = default;
            Mat<T, m, n>& operator=(Mat<T, m, n>&& a) = default;

            Mat<T, m, n>& operator+=(const Mat<T, m, n>& a);
            Mat<T, m, n>& operator-=(const Mat<T, m, n>& a);

            Vec<T, n>& operator[](uint64_t i);
            const Vec<T, n>& operator[](uint64_t i) const;

        private:

            Vec<T, n> _values[m];
    };

    // External operators

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator+(const Mat<T, m, n>& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(Mat<T, m, n>&& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(const Mat<T, m, n>& a, Mat<T, m, n>&& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(Mat<T, m, n>&& a, Mat<T, m, n>&& b);

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator-(const Mat<T, m, n>& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(Mat<T, m, n>&& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(const Mat<T, m, n>& a, Mat<T, m, n>&& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(Mat<T, m, n>&& a, Mat<T, m, n>&& b);

    template<typename T, uint64_t m, uint64_t n, uint64_t p>
    Mat<T, m, p> operator*(const Mat<T, m, n>& a, const Mat<T, n, p>& b);

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator-(const Mat<T, m, n>& a);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(Mat<T, m, n>&& a);

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator+(const Mat<T, m, n>& a);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(Mat<T, m, n>&& a);

    // Comparators

    template<typename T, uint64_t m, uint64_t n>
    bool operator==(const Mat<T, m, n>& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    bool operator!=(const Mat<T, m, n>& a, const Mat<T, m, n>& b);

    // Display

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Output stream operator for class Mat
    /// 
    /// Write the matrix into the stream with the format:
    /// `(x00 ... x0n
    ///   ... ... ...
    ///   xm0 ... xmn)`
    ///
    /// With `xij` and `...` the elements of the matrix.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t m, uint64_t n>
    std::ostream& operator<<(std::ostream& stream, const Mat<T, m, n>& a);

    // Specific functions

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \enum ConvolveMethod
    /// \brief Enumeration of the different conventions for behaviour of convolution at matrix borders.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ConvolveMethod
    {
        Periodic,    ///< When going beyond the matrix border, the matrix is repeated.
        Continuous,  ///< When going beyond the matrix border, the value at the border is kept.
        Zero         ///< When going beyond the matrix border, the value kept is 0.
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \relates ConvolveMethod
    /// \brief Convolution product of a by b. For behaviour at matrix borders, see ConvolveMethod
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t m, uint64_t n, uint64_t p, uint64_t q>
    Mat<T, m, n> convolve(const Mat<T, m, n>& a, const Mat<T, p, q>& b, ConvolveMethod method = ConvolveMethod::Periodic);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Compute the inverse of the matrix. If the matrix has no inverse, an error is thrown.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    Mat<T, n, n> inverse(const Mat<T, n, n>& a);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Returns the transpose of the matrix.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, n, m> transpose(const Mat<T, m, n>& a);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Compute the determinant of the matrix.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    T det(const Mat<T, n, n>& a);
}

#include <SciPP/MatT.hpp>
