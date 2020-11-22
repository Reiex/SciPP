#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Quaternion.hpp
/// \brief Functions and classes for quaternions manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Quaternion.
/// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SciPP/types.hpp>

namespace scp
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \class Quaternion
    /// \brief Class for quaternions manipulations
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct Quaternion
    {
        Quaternion();                                                                    ///< Default constructor. Init the quaternion to 0.
        Quaternion(int64_t x);                                                           ///< Init the quaternion to the real `T(x)`.
        Quaternion(const T& x);                                                          ///< Init the quaternion to the real `x`.
        Quaternion(const T& aValue, const T& bValue, const T& cValue, const T& dValue);  ///< Init the quaternion to `a + bi + cj + dk`.
        Quaternion(const std::array<T, 4> values);                                       ///< Init the quaternion with the 4 values `{a, b, c, d}` to `a + bi + cj + dk`.
        Quaternion(const Quaternion<T>& q) = default;
        Quaternion(Quaternion<T>&& q) = default;

        Quaternion<T>& operator=(const Quaternion<T>& q) = default;
        Quaternion<T>& operator=(Quaternion<T>&& q) = default;

        Quaternion<T>& operator+=(const Quaternion<T>& q);
        Quaternion<T>& operator-=(const Quaternion<T>& q);
        Quaternion<T>& operator*=(const Quaternion<T>& q);
        Quaternion<T>& operator/=(const T& x);

        ~Quaternion() = default;

        T a;
        T b;
        T c;
        T d;
    };

    // External operators

    template<typename T>
    Quaternion<T> operator+(const Quaternion<T>& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator+(Quaternion<T>&& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator+(const Quaternion<T>& p, Quaternion<T>&& q);
    template<typename T>
    Quaternion<T>&& operator+(Quaternion<T>&& p, Quaternion<T>&& q);

    template<typename T>
    Quaternion<T> operator-(const Quaternion<T>& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator-(const Quaternion<T>& p, Quaternion<T>&& q);
    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& p, Quaternion<T>&& q);

    template<typename T>
    Quaternion<T> operator*(const Quaternion<T>& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator*(Quaternion<T>&& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator*(Quaternion<T>&& p, Quaternion<T>&& q);

    template<typename T>
    Quaternion<T> operator/(const Quaternion<T>& q, const T& x);
    template<typename T>
    Quaternion<T>&& operator/(Quaternion<T>&& q, const T& x);

    template<typename T>
    Quaternion<T> operator-(const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& q);

    template<typename T>
    Quaternion<T> operator+(const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator+(Quaternion<T>&& q);

    // Comparators

    template<typename T>
    bool operator==(const Quaternion<T>& p, const Quaternion<T>& q);
    template<typename T>
    bool operator!=(const Quaternion<T>& p, const Quaternion<T>& q);

    // Display

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Quaternion
    /// \brief Output stream operator for class Quaternion
    /// 
    /// Writes the quaternion under the format `a b c d`.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& q);

    // Specific functions

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Quaternion
    /// \brief Returns the inverse of a quaternion.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    Quaternion<T> inverse(const Quaternion<T>& q);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Quaternion
    /// \brief Returns the square of the euclidian norm of a quaternion.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    T normSq(const Quaternion<T>& q);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Quaternion
    /// \brief Returns the euclidian norm of a quaternion.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    T norm(const Quaternion<T>& q);
}

#include <SciPP/QuaternionT.hpp>
