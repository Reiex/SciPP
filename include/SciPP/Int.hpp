#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file Int.hpp
/// \brief Functions and classes for big integers manipulations.
/// \author Reiex
/// 
/// For a more detailed description, see class Int.
/// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SciPP/types.hpp>

namespace scp
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \class Int
    /// \brief Class for big integers manipulations
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Int
    {
        public:

            Int();                        ///< Default constructor. Init the integer to 0.
            Int(int64_t x);               ///< Init the integer to x.
            Int(const Int& x) = default;
            Int(Int&& x) = default;

            Int& operator=(const Int& x) = default;
            Int& operator=(Int&& x) = default;

            Int& operator+=(const Int& x);
            Int& operator-=(const Int& x);
            Int& operator*=(const Int& x);
            Int& operator/=(const Int& x);
            Int& operator%=(const Int& x);

            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns the string corresponding to the integer.
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            std::string toString() const;
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Returns, if possible, the integer with the type int64_t.
            /// 
            /// If the integer is too big (or too small) to be converted to int64_t, then the function throws an error.
            ///
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            int64_t toInt() const;
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Changes the sign of the integer, true for positive, false for negative.
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            void setSign(bool sign);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// \brief Get the sign of the integer, true for positive, false for negative.
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            bool getSign() const;

            ~Int() = default;

        private:

            std::vector<uint32_t> _values;
            bool _sign;

            friend bool operator==(const Int& x, const Int& y);
            friend bool operator!=(const Int& x, const Int& y);
            friend bool operator>(const Int& x, const Int& y);
            friend bool operator<(const Int& x, const Int& y);
            friend bool operator>=(const Int& x, const Int& y);
            friend bool operator<=(const Int& x, const Int& y);

            friend std::ostream& operator<<(std::ostream& stream, const Int& x);
            friend std::istream& operator>>(std::istream& stream, Int& x);
    };


    // External operators

    Int operator+(const Int& x, const Int& y);
    Int&& operator+(Int&& x, const Int& y);
    Int&& operator+(const Int& x, Int&& y);
    Int&& operator+(Int&& x, Int&& y);

    Int operator-(const Int& x, const Int& y);
    Int&& operator-(Int&& x, const Int& y);
    Int&& operator-(const Int& x, Int&& y);
    Int&& operator-(Int&& x, Int&& y);

    Int operator*(const Int& x, const Int& y);
    Int&& operator*(Int&& x, const Int& y);
    Int&& operator*(const Int& x, Int&& y);
    Int&& operator*(Int&& x, Int&& y);

    Int operator/(const Int& x, const Int& y);
    Int&& operator/(Int&& x, const Int& y);
    Int&& operator/(Int&& x, Int&& y);

    Int operator%(const Int& x, const Int& y);
    Int&& operator%(Int&& x, const Int& y);
    Int&& operator%(Int&& x, Int&& y);

    Int operator-(const Int& x);
    Int&& operator-(Int&& x);
    
    Int operator+(const Int& x);
    Int&& operator+(Int&& x);


    // Comparators

    bool operator==(const Int& x, const Int& y);
    bool operator!=(const Int& x, const Int& y);
    bool operator>(const Int& x, const Int& y);
    bool operator<(const Int& x, const Int& y);
    bool operator>=(const Int& x, const Int& y);
    bool operator<=(const Int& x, const Int& y);


    // Display

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Int
    /// \brief Output stream operator for class Int
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::ostream& operator<<(std::ostream& stream, const Int& x);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \relates Int
    /// \brief Input stream operator for class Int
    /// 
    /// The evaluated regular expression is: `-?[0-9]+.`
    /// The operator does not consume the last character
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::istream& operator>>(std::istream& stream, Int& x);


    // Specific functions

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Computes the binomial coefficient of n and p.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Int binom(const Int& n, const Int& p);
}