///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>
#include <SciPP/Core/Frac.hpp>
#include <SciPP/Core/BigInt.hpp>

namespace scp
{
	template<typename TInteger = BigInt<>>
	class Rational : public Frac<TInteger>
	{
		public:

			constexpr Rational();
			constexpr Rational(double x);
			constexpr Rational(const TInteger& x);
			constexpr Rational(const TInteger& p, const TInteger& q);
			constexpr Rational(const Rational<TInteger>& x) = default;
			constexpr Rational(Rational<TInteger>&& x) = default;

			constexpr Rational<TInteger>& operator=(const Rational<TInteger>& x) = default;
			constexpr Rational<TInteger>& operator=(Rational<TInteger>&& x) = default;

			constexpr Rational<TInteger>& operator+=(const Rational<TInteger>& x);
			constexpr Rational<TInteger>& operator-=(const Rational<TInteger>& x);
			constexpr Rational<TInteger>& operator*=(const Rational<TInteger>& x);
			constexpr Rational<TInteger>& operator/=(const Rational<TInteger>& x);
			constexpr Rational<TInteger>& operator+=(const TInteger& x);
			constexpr Rational<TInteger>& operator-=(const TInteger& x);
			constexpr Rational<TInteger>& operator*=(const TInteger& x);
			constexpr Rational<TInteger>& operator/=(const TInteger& x);
			constexpr Rational<TInteger>& operator+=(double x);
			constexpr Rational<TInteger>& operator-=(double x);
			constexpr Rational<TInteger>& operator*=(double x);
			constexpr Rational<TInteger>& operator/=(double x);

			constexpr bool operator==(const Rational<TInteger>& x) const;
			constexpr bool operator!=(const Rational<TInteger>& x) const;
			constexpr bool operator<(const Rational<TInteger>& x) const;
			constexpr bool operator>(const Rational<TInteger>& x) const;
			constexpr bool operator<=(const Rational<TInteger>& x) const;
			constexpr bool operator>=(const Rational<TInteger>& x) const;

			constexpr std::string decimals(uint64_t n) const;

			constexpr virtual ~Rational() = default;

		private:

			using Frac<TInteger>::_simplify;

			using Frac<TInteger>::_zero;
			using Frac<TInteger>::_one;

			using Frac<TInteger>::_p;
			using Frac<TInteger>::_q;
	};

	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const Rational<TInteger>& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(const Rational<TInteger>& a, Rational<TInteger>&& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a, Rational<TInteger>&& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const Rational<TInteger>& a, const TInteger& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a, const TInteger& b);
	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const TInteger& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(const TInteger& a, Rational<TInteger>&& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const Rational<TInteger>& a, double b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a, double b);
	template<typename TInteger>
	constexpr Rational<TInteger> operator+(double a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(double a, Rational<TInteger>&& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const Rational<TInteger>& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(const Rational<TInteger>& a, Rational<TInteger>&& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a, Rational<TInteger>&& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const Rational<TInteger>& a, const TInteger& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a, const TInteger& b);
	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const TInteger& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(const TInteger& a, Rational<TInteger>&& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const Rational<TInteger>& a, double b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a, double b);
	template<typename TInteger>
	constexpr Rational<TInteger> operator-(double a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(double a, Rational<TInteger>&& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator*(const Rational<TInteger>& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(Rational<TInteger>&& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(const Rational<TInteger>& a, Rational<TInteger>&& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(Rational<TInteger>&& a, Rational<TInteger>&& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator*(const Rational<TInteger>& a, const TInteger& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(Rational<TInteger>&& a, const TInteger& b);
	template<typename TInteger>
	constexpr Rational<TInteger> operator*(const TInteger& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(const TInteger& a, Rational<TInteger>&& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator*(const Rational<TInteger>& a, double b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(Rational<TInteger>&& a, double b);
	template<typename TInteger>
	constexpr Rational<TInteger> operator*(double a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(double a, Rational<TInteger>&& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator/(const Rational<TInteger>& a, const Rational<TInteger>& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator/(Rational<TInteger>&& a, const Rational<TInteger>& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator/(const Rational<TInteger>& a, const TInteger& b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator/(Rational<TInteger>&& a, const TInteger& b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator/(const Rational<TInteger>& a, double b);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator/(Rational<TInteger>&& a, double b);

	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const Rational<TInteger>& a);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a);

	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const Rational<TInteger>& a);
	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a);
}
