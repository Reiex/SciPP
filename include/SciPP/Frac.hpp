#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Frac.hpp
/// \brief Functions and classes for fractions manipulation.
/// \author Reiex
/// 
/// For a more detailed description, see class Frac and class Rational.
/// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SciPP/types.hpp>

namespace scp
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \class Frac
    /// \brief Class for fractions manipulations.
    /// 
    /// The class Frac is not only intended to be used with integers but can represent any algebraic fraction.
    /// For example, with T=Polynomial, the class represents a rational fraction.
    ///
    /// For representing rational numbers (arithmetic fraction) especially, see class Rational.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    class Frac
    {
        public:
        
            Frac();                            ///< Default constructor. Init the fraction to T(0)/T(1).
            Frac(int64_t x);                   ///< Init the fraction to T(x)/T(1).
            Frac(const T& x);                  ///< Init the fraction to x/T(1).
            Frac(const T& p, const T& q);      ///< Init the fraction p/q.
            Frac(const Frac<T>& a) = default;
            Frac(Frac<T>&& a) = default;

            Frac<T>& operator=(const Frac<T>& a) = default;
            Frac<T>& operator=(Frac<T>&& a) = default;

            Frac<T>& operator+=(const Frac<T>& a);
            Frac<T>& operator-=(const Frac<T>& a);
            Frac<T>& operator*=(const Frac<T>& a);
            Frac<T>& operator/=(const Frac<T>& a);

            const T& num() const;    ///< Returns the numerator of the fraction.
            const T& denom() const;  ///< Returns the denominator of the fraction.

            ~Frac() = default;

        private:

            void simplify();  ///< Reduces the fraction by dividing by gcd(_p, _q) and allowing only _p to be negative.

            T _p;
            T _q;
        
        template<typename U>
        friend Frac<U>&& operator-(Frac<U>&& a);
        template<typename U>
        friend Frac<U>&& operator+(Frac<U>&& a);
    };


    // External operators

    template<typename T>
    Frac<T> operator+(const Frac<T>& a, const Frac<T>& b);
    template<typename T>
    Frac<T>&& operator+(Frac<T>&& a, const Frac<T>& b);
    template<typename T>
    Frac<T>&& operator+(const Frac<T>& a, Frac<T>&& b);
    template<typename T>
    Frac<T>&& operator+(Frac<T>&& a, Frac<T>&& b);

    template<typename T>
    Frac<T> operator-(const Frac<T>& a, const Frac<T>& b);
    template<typename T>
    Frac<T>&& operator-(Frac<T>&& a, const Frac<T>& b);
    template<typename T>
    Frac<T>&& operator-(const Frac<T>& a, Frac<T>&& b);
    template<typename T>
    Frac<T>&& operator-(Frac<T>&& a, Frac<T>&& b);

    template<typename T>
    Frac<T> operator*(const Frac<T>& a, const Frac<T>& b);
    template<typename T>
    Frac<T>&& operator*(Frac<T>&& a, const Frac<T>& b);
    template<typename T>
    Frac<T>&& operator*(const Frac<T>& a, Frac<T>&& b);
    template<typename T>
    Frac<T>&& operator*(Frac<T>&& a, Frac<T>&& b);

    template<typename T>
    Frac<T> operator/(const Frac<T>& a, const Frac<T>& b);
    template<typename T>
    Frac<T>&& operator/(Frac<T>&& a, const Frac<T>& b);
    template<typename T>
    Frac<T>&& operator/(Frac<T>&& a, Frac<T>&& b);

    template<typename T>
    Frac<T> operator-(const Frac<T>& a);
    template<typename T>
    Frac<T>&& operator-(Frac<T>&& a);
    
    template<typename T>
    Frac<T> operator+(const Frac<T>& a);
    template<typename T>
    Frac<T>&& operator+(Frac<T>&& a);


    // Comparators

    template<typename T>
    bool operator==(const Frac<T>& a, const Frac<T>& b);
    template<typename T>
    bool operator!=(const Frac<T>& a, const Frac<T>& b);
    template<typename T>
    bool operator>(const Frac<T>& a, const Frac<T>& b);
    template<typename T>
    bool operator<(const Frac<T>& a, const Frac<T>& b);
    template<typename T>
    bool operator>=(const Frac<T>& a, const Frac<T>& b);
    template<typename T>
    bool operator<=(const Frac<T>& a, const Frac<T>& b);


    // Display

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Frac
    /// \brief Output stream operator for class Frac
    /// 
    /// Write the fraction into the stream with the format: `Numerator Denominator`.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Frac<T>& a);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Frac
    /// \brief Input stream operator for class Frac
    /// 
    /// The evaluated regular expression is: `T T`
    /// Where T is the regular expression accepted by the input stream for T.
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    std::istream& operator>>(std::istream& stream, Frac<T>& a);


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \class Rational
    /// \brief Class for rational numbers manipulation.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Rational: public Frac<Int>
    {
        public:

            Rational();                            ///< Default constructor. Init the rational to 0/1.
            Rational(int16_t x);                   ///< Init the rational to x/1.
            Rational(int32_t x);                   ///< Init the rational to x/1.
            Rational(int64_t x);                   ///< Init the rational to x/1.
            Rational(const Int& x);                ///< Init the rational to x/1.
            Rational(const Int& p, const Int& q);  ///< Init the rational to p/q.
            Rational(float x);                     ///< Init the rational to an approximation of x.
            Rational(double x);                    ///< Init the rational to an approximation of x.
            Rational(long double x);               ///< Init the rational to an approximation of x.
            Rational(const Frac<Int>& x);          ///< Init the rational to x.

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns a string with the integer part, a comma and the n first decimals of x.
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            std::string decimals(uint64_t n) const;
    };

    // Display

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Rationnel
    /// \brief Output stream operator for class Rational
    /// 
    /// If the rational is in the decimal set then it is fully written (ex: 3/4 is written 0.75) else the Frac format
    /// is kept.
    /// 
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::ostream& operator<<(std::ostream& stream, const Rational& x);
}

#include <SciPP/FracT.hpp>
