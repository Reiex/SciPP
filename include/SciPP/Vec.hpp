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

            Vec();                              ///< Default constructor. Init all the components of the vector with T(0).
            Vec(int64_t value);                 ///< Init all the components of the vector with T(value).
            Vec(const T& value);                ///< Init all the components of the vector with value.
            Vec(const std::vector<T>& values);  ///< Init the vec with the values. Values must be the size of the vector.
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

            uint64_t size() const;  ///< Returns the size of the vector.

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
    /// \brief Output stream operator for class Rational
    /// 
    /// Writes the vector under the format `<x, x, x, ..., x>` with `x` the elements of the vector.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, uint64_t n>
    std::ostream& operator<<(std::ostream& stream, const Vec<T, n>& v);

    // Specific functions

    template<typename T, uint64_t n>
    T dot(const Vec<T, n>& u, const Vec<T, n>& v);
    template<typename T>
    Vec<T, 3> cross(const Vec<T, 3>& u, const Vec<T, 3>& v);
}

#include <SciPP/VecT.hpp>
