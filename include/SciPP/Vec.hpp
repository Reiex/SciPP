#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Vec.hpp
/// \brief Functions and classes for vectors manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Vec.
/// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SciPP/types.hpp>

namespace scp
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \class Vec
    /// \brief Class for vectors manipulations
    ///
    /// All the operators (+, -, *, /, %) defined on Vec are component-wise. For other operations, specific functions
    /// are written aside of the class like dot product, cross product...
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    class Vec
    {
        public:

            Vec() = delete;
            Vec(uint64_t count, int64_t value = 0);  ///< Init all the components of the vector with T(value).
            Vec(uint64_t count, const T& value);     ///< Init all the components of the vector with value.
            Vec(const std::vector<T>& values);       ///< Init the vec with the values.
            Vec(const Vec<T>& v) = default;
            Vec(Vec<T>&& v) = default;

            Vec<T>& operator=(const Vec<T>& v);
            Vec<T>& operator=(Vec<T>&& v);

            T& operator[](uint64_t i);
            const T& operator[](uint64_t i) const;
            
            Vec<T>& operator+=(const Vec<T>& v);
            Vec<T>& operator-=(const Vec<T>& v);
            Vec<T>& operator*=(const Vec<T>& v);
            Vec<T>& operator/=(const Vec<T>& v);
            Vec<T>& operator%=(const Vec<T>& v);

            const uint64_t n;  ///< Size of the vector.

            ~Vec() = default;

        private:

            std::vector<T> _values;
    };

    // External operators

    template<typename T>
    Vec<T> operator+(const Vec<T>& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator+(Vec<T>&& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator+(const Vec<T>& u, Vec<T>&& v);
    template<typename T>
    Vec<T>&& operator+(Vec<T>&& u, Vec<T>&& v);

    template<typename T>
    Vec<T> operator-(const Vec<T>& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator-(Vec<T>&& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator-(const Vec<T>& u, Vec<T>&& v);
    template<typename T>
    Vec<T>&& operator-(Vec<T>&& u, Vec<T>&& v);

    template<typename T>
    Vec<T> operator*(const Vec<T>& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator*(Vec<T>&& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator*(const Vec<T>& u, Vec<T>&& v);
    template<typename T>
    Vec<T>&& operator*(Vec<T>&& u, Vec<T>&& v);

    template<typename T>
    Vec<T> operator/(const Vec<T>& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator/(Vec<T>&& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator/(Vec<T>&& u, Vec<T>&& v);

    template<typename T>
    Vec<T> operator%(const Vec<T>& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator%(Vec<T>&& u, const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator%(Vec<T>&& u, Vec<T>&& v);

    template<typename T>
    Vec<T> operator-(const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator-(Vec<T>&& v);
    
    template<typename T>
    Vec<T> operator+(const Vec<T>& v);
    template<typename T>
    Vec<T>&& operator+(Vec<T>&& v);

    // Comparators

    template<typename T>
    bool operator==(const Vec<T>& u, const Vec<T>& v);
    template<typename T>
    bool operator!=(const Vec<T>& u, const Vec<T>& v);

    // Display

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Output stream operator for class Vec
    /// 
    /// Writes the vector under the format `x0 x1 ... xn` with `xi` and `...` the elements of the vector.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Vec<T>& v);

    // Specific functions

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Compute the minimum element of the vector using `operator<` between two elements of type `T`.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    T minElement(const Vec<T>& a);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Compute the maximum element of the vector using `operator>` between two elements of type `T`.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    T maxElement(const Vec<T>& a);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Dot product between two vectors
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    T dot(const Vec<T>& u, const Vec<T>& v);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Cross product between two 3-dimensional vectors
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Vec<T> cross(const Vec<T>& u, const Vec<T>& v);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Returns the square of the euclidian norm of a vector.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    T normSq(const Vec<T> v);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Returns the euclidian norm of a vector.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    T norm(const Vec<T> v);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \enum ConvolveMethod
    /// \brief Enumeration of the different conventions for behaviour of convolution at borders.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ConvolveMethod
    {
        Periodic,    ///< When going beyond the border, the matrix/vector is repeated.
        Continuous,  ///< When going beyond the border, the value at the border is kept.
        Zero         ///< When going beyond the border, the value kept is 0.
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Convolution product of `a` by `b`. For behaviour at vector borders, see ConvolveMethod
    /// 
    /// The convolution vector (`b`) is centered. It means the the coefficient `b[b.n/2 + 1]` is the one that applies
    /// on `a[0]` to compute the first coefficient of the result.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Vec<T> convolve(const Vec<T>& a, const Vec<T>& b, ConvolveMethod method = ConvolveMethod::Periodic);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Discrete Fourier Transform of a vector.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Vec<std::complex<T>> dft(const Vec<std::complex<T>>& f);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Inverse Discrete Fourier Transform of a vector.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Vec<std::complex<T>> idft(const Vec<std::complex<T>>& fh);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Discrete Cosine Transform of a vector. (Type II corrected)
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Vec<T> dct(const Vec<T>& f);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Inverse Discrete Cosine Transform of a vector. (Type II corrected)
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Vec<T> idct(const Vec<T>& fh);
}

#include <SciPP/VecT.hpp>
