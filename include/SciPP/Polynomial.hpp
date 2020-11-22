#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Polynomial.hpp
/// \brief Functions and classes for polynomials manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Polynomial.
/// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <SciPP/types.hpp>

namespace scp
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \class Polynomial
    /// \brief Class for polynomials manipulations
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    class Polynomial
    {
        public:

            static const Polynomial X;

            Polynomial();                                  ///< Default constructor. Init the polynomial to [T(0)].
            Polynomial(int64_t x);                         ///< Init the polynomial to [T(x)].
            Polynomial(const T& x);                        ///< Init the polynomial to [x].
            Polynomial(const std::vector<T>& values);      ///< Init the polynomial with the values. The index is the exponent.
            Polynomial(const Polynomial<T>& p) = default;
            Polynomial(Polynomial<T>&& p) = default;

            Polynomial<T>& operator=(const Polynomial<T>& p) = default;
            Polynomial<T>& operator=(Polynomial<T>&& p) = default;

            T& operator[](uint64_t i);               ///< Get the coefficient in front of X^i.
            const T& operator[](uint64_t i) const;  ///< Get the coefficient in front of X^i.

            Polynomial<T>& operator+=(const Polynomial<T>& p);
            Polynomial<T>& operator-=(const Polynomial<T>& p);
            Polynomial<T>& operator*=(const Polynomial<T>& p);
            Polynomial<T>& operator/=(const Polynomial<T>& p);
            Polynomial<T>& operator%=(const Polynomial<T>& p);

            T operator()(const T& x) const;  ///< Compute the polynomial at x.

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns the degree of the polynomial.
            ///
            /// If the polynomial is 0, the degree is 0.
            ///
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            uint64_t degree() const;
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns the derivative of the polynomial.
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            Polynomial<T> derivative() const;
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns the primitive of the polynomial.
            ///
            /// The integration constant is c.
            ///
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            Polynomial<T> primitive(T const& c = 0) const;

            ~Polynomial() = default;

        private:

            void reduce() const;

            mutable std::vector<T> _coeffs;

        template<typename U>
        friend Polynomial<U>&& operator-(Polynomial<U>&& p);
        template<typename U>
        friend Polynomial<U>&& operator+(Polynomial<U>&& p);
    };

    // Operators

    template<typename T>
    Polynomial<T> operator+(const Polynomial<T>& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator+(Polynomial<T>&& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator+(const Polynomial<T>& p, Polynomial<T>&& q);
    template<typename T>
    Polynomial<T>&& operator+(Polynomial<T>&& p, Polynomial<T>&& q);

    template<typename T>
    Polynomial<T> operator-(const Polynomial<T>& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator-(Polynomial<T>&& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator-(const Polynomial<T>& p, Polynomial<T>&& q);
    template<typename T>
    Polynomial<T>&& operator-(Polynomial<T>&& p, Polynomial<T>&& q);

    template<typename T>
    Polynomial<T> operator*(const Polynomial<T>& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator*(Polynomial<T>&& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator*(const Polynomial<T>& p, Polynomial<T>&& q);
    template<typename T>
    Polynomial<T>&& operator*(Polynomial<T>&& p, Polynomial<T>&& q);

    template<typename T>
    Polynomial<T> operator/(const Polynomial<T>& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator/(Polynomial<T>&& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator/(Polynomial<T>&& p, Polynomial<T>&& q);

    template<typename T>
    Polynomial<T> operator%(const Polynomial<T>& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator%(Polynomial<T>&& p, const Polynomial<T>& q);
    template<typename T>
    Polynomial<T>&& operator%(Polynomial<T>&& p, Polynomial<T>&& q);

    template<typename T>
    Polynomial<T> operator-(const Polynomial<T>& p);
    template<typename T>
    Polynomial<T>&& operator-(Polynomial<T>&& p);
    
    template<typename T>
    Polynomial<T> operator+(const Polynomial<T>& p);
    template<typename T>
    Polynomial<T>&& operator+(Polynomial<T>&& p);

    // Comparators

    template<typename T>
    bool operator==(const Polynomial<T>& p, const Polynomial<T>& q);
    template<typename T>
    bool operator!=(const Polynomial<T>& p, const Polynomial<T>& q);

    // Display

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Vec
    /// \brief Output stream operator for class Polynomial
    /// 
    /// Writes the polynomial under the format `x0 x1 ... xn` with `xi` and `...` the coefficients of the polynomial in
    /// order of crescent exponent.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& p);
}

#include <SciPP/PolynomialT.hpp>
