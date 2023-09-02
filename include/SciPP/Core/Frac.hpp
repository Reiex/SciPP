///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>

namespace scp
{
	template<typename TValue>
	class Frac
	{
		public:
		
			constexpr Frac();
			constexpr Frac(const TValue& x);
			constexpr Frac(const TValue& p, const TValue& q);
			constexpr Frac(const Frac<TValue>& x) = default;
			constexpr Frac(Frac<TValue>&& x) = default;

			constexpr Frac<TValue>& operator=(const Frac<TValue>& x) = default;
			constexpr Frac<TValue>& operator=(Frac<TValue>&& x) = default;

			constexpr Frac<TValue>& operator+=(const Frac<TValue>& x);
			constexpr Frac<TValue>& operator-=(const Frac<TValue>& x);
			constexpr Frac<TValue>& operator*=(const Frac<TValue>& x);
			constexpr Frac<TValue>& operator/=(const Frac<TValue>& x);
			constexpr Frac<TValue>& operator+=(const TValue& x);
			constexpr Frac<TValue>& operator-=(const TValue& x);
			constexpr Frac<TValue>& operator*=(const TValue& x);
			constexpr Frac<TValue>& operator/=(const TValue& x);

			constexpr bool operator==(const Frac<TValue>& x) const;
			constexpr bool operator!=(const Frac<TValue>& x) const;
			constexpr bool operator<(const Frac<TValue>& x) const;
			constexpr bool operator>(const Frac<TValue>& x) const;
			constexpr bool operator<=(const Frac<TValue>& x) const;
			constexpr bool operator>=(const Frac<TValue>& x) const;

			constexpr int8_t compare(const Frac<TValue>& x) const;
			constexpr void negate();

			constexpr const TValue& getNumerator() const;
			constexpr const TValue& getDenominator() const;

			constexpr virtual ~Frac() = default;

		protected:

			constexpr void _simplify();

			static const TValue _zero;
			static const TValue _one;

			TValue _p;
			TValue _q;
	};

	template<typename TValue>
	constexpr Frac<TValue> operator+(const Frac<TValue>& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator+(Frac<TValue>&& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator+(const Frac<TValue>& a, Frac<TValue>&& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator+(Frac<TValue>&& a, Frac<TValue>&& b);

	template<typename TValue>
	constexpr Frac<TValue> operator+(const Frac<TValue>& a, const TValue& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator+(Frac<TValue>&& a, const TValue& b);
	template<typename TValue>
	constexpr Frac<TValue> operator+(const TValue& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator+(const TValue& a, Frac<TValue>&& b);

	template<typename TValue>
	constexpr Frac<TValue> operator-(const Frac<TValue>& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator-(Frac<TValue>&& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator-(const Frac<TValue>& a, Frac<TValue>&& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator-(Frac<TValue>&& a, Frac<TValue>&& b);

	template<typename TValue>
	constexpr Frac<TValue> operator-(const Frac<TValue>& a, const TValue& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator-(Frac<TValue>&& a, const TValue& b);
	template<typename TValue>
	constexpr Frac<TValue> operator-(const TValue& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator-(const TValue& a, Frac<TValue>&& b);

	template<typename TValue>
	constexpr Frac<TValue> operator*(const Frac<TValue>& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator*(Frac<TValue>&& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator*(const Frac<TValue>& a, Frac<TValue>&& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator*(Frac<TValue>&& a, Frac<TValue>&& b);

	template<typename TValue>
	constexpr Frac<TValue> operator*(const Frac<TValue>& a, const TValue& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator*(Frac<TValue>&& a, const TValue& b);
	template<typename TValue>
	constexpr Frac<TValue> operator*(const TValue& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator*(const TValue& a, Frac<TValue>&& b);

	template<typename TValue>
	constexpr Frac<TValue> operator/(const Frac<TValue>& a, const Frac<TValue>& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator/(Frac<TValue>&& a, const Frac<TValue>& b);

	template<typename TValue>
	constexpr Frac<TValue> operator/(const Frac<TValue>& a, const TValue& b);
	template<typename TValue>
	constexpr Frac<TValue>&& operator/(Frac<TValue>&& a, const TValue& b);

	template<typename TValue>
	constexpr Frac<TValue> operator+(const Frac<TValue>& a);
	template<typename TValue>
	constexpr Frac<TValue>&& operator+(Frac<TValue>&& a);

	template<typename TValue>
	constexpr Frac<TValue> operator-(const Frac<TValue>& a);
	template<typename TValue>
	constexpr Frac<TValue>&& operator-(Frac<TValue>&& a);
}
