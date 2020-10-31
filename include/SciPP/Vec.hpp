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
    template<typename T, uint64_t n>
    class Vec
    {
        public:

            static const uint64_t N = n;  ///< Number of elements of the vector.

            Vec();                                ///< Default constructor. Init all the components of the vector with T(0).
            Vec(int64_t value);                   ///< Init all the components of the vector with T(value).
            Vec(const T& value);                  ///< Init all the components of the vector with value.
            Vec(const std::array<T, n>& values);  ///< Init the vec with the values.
            Vec(const Vec<T, n>& v) = default;
            Vec(Vec<T, n>&& v) = default;

            Vec<T, n>& operator=(const Vec<T, n>& v) = default;
            Vec<T, n>& operator=(Vec<T, n>&& v) = default;

            T& operator[](uint64_t i);
            const T& operator[](uint64_t i) const;
            
            Vec<T, n>& operator+=(const Vec<T, n>& v);
            Vec<T, n>& operator-=(const Vec<T, n>& v);
            Vec<T, n>& operator*=(const Vec<T, n>& v);
            Vec<T, n>& operator/=(const Vec<T, n>& v);
            Vec<T, n>& operator%=(const Vec<T, n>& v);

        private:

            T _values[n];
    };

    // External operators

    template<typename T, uint64_t n>
    Vec<T, n> operator+(const Vec<T, n>& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator+(Vec<T, n>&& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator+(const Vec<T, n>& u, Vec<T, n>&& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator+(Vec<T, n>&& u, Vec<T, n>&& v);

    template<typename T, uint64_t n>
    Vec<T, n> operator-(const Vec<T, n>& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator-(Vec<T, n>&& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator-(const Vec<T, n>& u, Vec<T, n>&& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator-(Vec<T, n>&& u, Vec<T, n>&& v);

    template<typename T, uint64_t n>
    Vec<T, n> operator*(const Vec<T, n>& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator*(Vec<T, n>&& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator*(const Vec<T, n>& u, Vec<T, n>&& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator*(Vec<T, n>&& u, Vec<T, n>&& v);

    template<typename T, uint64_t n>
    Vec<T, n> operator/(const Vec<T, n>& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator/(Vec<T, n>&& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator/(Vec<T, n>&& u, Vec<T, n>&& v);

    template<typename T, uint64_t n>
    Vec<T, n> operator%(const Vec<T, n>& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator%(Vec<T, n>&& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator%(Vec<T, n>&& u, Vec<T, n>&& v);

    template<typename T, uint64_t n>
    Vec<T, n> operator-(const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator-(Vec<T, n>&& v);
    
    template<typename T, uint64_t n>
    Vec<T, n> operator+(const Vec<T, n>& v);
    template<typename T, uint64_t n>
    Vec<T, n>&& operator+(Vec<T, n>&& v);

    // Comparators

    template<typename T, uint64_t n>
    bool operator==(const Vec<T, n>& u, const Vec<T, n>& v);
    template<typename T, uint64_t n>
    bool operator!=(const Vec<T, n>& u, const Vec<T, n>& v);

    // Display

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Output stream operator for class Vec
    /// 
    /// Writes the vector under the format `<x, x, x, ..., x>` with `x` the elements of the vector.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    std::ostream& operator<<(std::ostream& stream, const Vec<T, n>& v);

    // Specific functions

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Dot product between two vectors
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    T dot(const Vec<T, n>& u, const Vec<T, n>& v);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Cross product between two 3-dimensional vectors
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Vec<T, 3> cross(const Vec<T, 3>& u, const Vec<T, 3>& v);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Returns the square of the euclidian norm of a vector.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    T normSq(const Vec<T, n> v);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Returns the euclidian norm of a vector.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    T norm(const Vec<T, n> v);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Discrete Fourier Transform of a vector.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    Vec<std::complex<T>, n> dft(const Vec<std::complex<T>, n>& f);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Inverse Discrete Fourier Transform of a vector.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    Vec<std::complex<T>, n> idft(const Vec<std::complex<T>, n>& fh);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Discrete Cosine Transform of a vector. (Type II corrected)
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    Vec<T, n> dct(const Vec<T, n>& f);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Inverse Discrete Cosine Transform of a vector. (Type II corrected)
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    Vec<T, n> idct(const Vec<T, n>& fh);
}

#include <SciPP/VecT.hpp>
