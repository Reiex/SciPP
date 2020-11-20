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
    template<typename T>
    class Mat
    {
        public:

            Mat() = delete;
            Mat(uint64_t row, uint64_t col, int64_t x = 0);    ///< Init the matrix with `T(x)` everywhere.
            Mat(uint64_t row, uint64_t col, const T& x);       ///< Init the matrix with `x` everywhere.
            Mat(const std::vector<std::vector<T>>& values);    ///< Init the matrix directly.
            Mat(const Mat<T>& a) = default;
            Mat(Mat<T>&& a) = default;

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns the identity matrix multiplied by `T(x)`.
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            static Mat<T> identity(uint64_t size, int64_t x = 1);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns the identity matrix multiplied by `x`.
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            static Mat<T> identity(uint64_t size, const T& x);

            Mat<T>& operator=(const Mat<T>& a);
            Mat<T>& operator=(Mat<T>&& a);

            Vec<T>& operator[](uint64_t i);
            const Vec<T>& operator[](uint64_t i) const;

            Mat<T>& operator+=(const Mat<T>& a);
            Mat<T>& operator-=(const Mat<T>& a);
            Mat<T>& operator*=(const T& x);
            Mat<T>& operator/=(const T& x);

            const uint64_t m;  ///< Number of rows of the matrix.
            const uint64_t n;  ///< Number of columns of the matrix.

        private:

            std::vector<Vec<T>> _values;
    };

    // External operators

    template<typename T>
    Mat<T> operator+(const Mat<T>& a, const Mat<T>& b);
    template<typename T>
    Mat<T>&& operator+(Mat<T>&& a, const Mat<T>& b);
    template<typename T>
    Mat<T>&& operator+(const Mat<T>& a, Mat<T>&& b);
    template<typename T>
    Mat<T>&& operator+(Mat<T>&& a, Mat<T>&& b);

    template<typename T>
    Mat<T> operator-(const Mat<T>& a, const Mat<T>& b);
    template<typename T>
    Mat<T>&& operator-(Mat<T>&& a, const Mat<T>& b);
    template<typename T>
    Mat<T>&& operator-(const Mat<T>& a, Mat<T>&& b);
    template<typename T>
    Mat<T>&& operator-(Mat<T>&& a, Mat<T>&& b);

    template<typename T>
    Mat<T> operator*(const Mat<T>& a, const Mat<T>& b);

    template<typename T>
    Vec<T> operator*(const Mat<T>& a, const Vec<T>& b);
    template<typename T>
    Vec<T> operator*(const Vec<T>& a, const Mat<T>& b);

    template<typename T>
    Mat<T> operator*(const Mat<T>& a, const T& x);
    template<typename T>
    Mat<T>&& operator*(Mat<T>&& a, const T& x);

    template<typename T>
    Mat<T> operator/(const Mat<T>& a, const T& x);
    template<typename T>
    Mat<T>&& operator/(Mat<T>&& a, const T& x);

    template<typename T>
    Mat<T> operator-(const Mat<T>& a);
    template<typename T>
    Mat<T>&& operator-(Mat<T>&& a);

    template<typename T>
    Mat<T> operator+(const Mat<T>& a);
    template<typename T>
    Mat<T>&& operator+(Mat<T>&& a);

    // Comparators

    template<typename T>
    bool operator==(const Mat<T>& a, const Mat<T>& b);
    template<typename T>
    bool operator!=(const Mat<T>& a, const Mat<T>& b);

    // Display

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Output stream operator for class Mat
    /// 
    /// Write the matrix into the stream with the format:
    /// `x00 ... x0n
    ///  ... ... ...
    ///  xm0 ... xmn`
    ///
    /// With `xij` and `...` the elements of the matrix.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Mat<T>& a);

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
    template<typename T>
    Mat<T> convolve(const Mat<T>& a, const Mat<T>& b, ConvolveMethod method = ConvolveMethod::Periodic);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Compute the inverse of the matrix. If the matrix has no inverse, an error is thrown.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Mat<T> inverse(const Mat<T>& a);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Returns the transpose of the matrix.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Mat<T> transpose(const Mat<T>& a);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Compute the determinant of the matrix.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    T det(const Mat<T>& a);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Discrete Fourier Transform of a matrix.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Mat<std::complex<T>> dft(const Mat<std::complex<T>>& f);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Inverse Discrete Fourier Transform of a matrix.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Mat<std::complex<T>> idft(const Mat<std::complex<T>>& fh);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Discrete Cosine Transform of a matrix. (Type II corrected)
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Mat<T> dct(const Mat<T>& f);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Mat
    /// \brief Inverse Discrete Cosine Transform of a matrix. (Type II corrected)
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Mat<T> idct(const Mat<T>& fh);
}

#include <SciPP/MatT.hpp>
