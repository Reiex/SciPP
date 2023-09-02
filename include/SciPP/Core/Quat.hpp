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
	class Quat
	{
		public:

			constexpr Quat() = default;
			constexpr Quat(const TValue& value);
			constexpr Quat(const TValue& wValue, const TValue& xValue, const TValue& yValue, const TValue& zValue);
			constexpr Quat(const Quat<TValue>& q) = default;
			constexpr Quat(Quat<TValue>&& q) = default;

			constexpr Quat<TValue>& operator=(const Quat<TValue>& q) = default;
			constexpr Quat<TValue>& operator=(Quat<TValue>&& q) = default;

			constexpr Quat<TValue>& operator+=(const Quat<TValue>& q);
			constexpr Quat<TValue>& operator-=(const Quat<TValue>& q);
			constexpr Quat<TValue>& operator*=(const Quat<TValue>& q);
			constexpr Quat<TValue>& operator+=(const TValue& value);
			constexpr Quat<TValue>& operator-=(const TValue& value);
			constexpr Quat<TValue>& operator*=(const TValue& value);
			constexpr Quat<TValue>& operator/=(const TValue& value);

			constexpr bool operator==(const Quat<TValue>& q) const;
			constexpr bool operator!=(const Quat<TValue>& q) const;

			constexpr void setFromRotationAxisAngle(const TValue& xAxis, const TValue& yAxis, const TValue& zAxis, const TValue& angle);
			constexpr void getRotationAxisAngle(TValue& xAxis, TValue& yAxis, TValue& zAxis, TValue& angle) const;

			constexpr void setFromRotationMatrix(const TValue& r00, const TValue& r01, const TValue& r02, const TValue& r10, const TValue& r11, const TValue& r12, const TValue& r20, const TValue& r21, const TValue& r22);
			constexpr void getRotationMatrix(TValue& r00, TValue& r01, TValue& r02, TValue& r10, TValue& r11, TValue& r12, TValue& r20, TValue& r21, TValue& r22) const;

			constexpr void setFromUnitVectorRotation(const TValue& xFrom, const TValue& yFrom, const TValue& zFrom, const TValue& xTo, const TValue& yTo, const TValue& zTo);

			constexpr void inverse();
			constexpr void conjugate();
			constexpr TValue normSq() const;
			constexpr TValue norm() const;

			constexpr ~Quat() = default;

			TValue w;
			TValue x;
			TValue y;
			TValue z;

		private:

			static const TValue _zero;
			static const TValue _one;
	};

	template<typename TValue>
	constexpr Quat<TValue> operator+(const Quat<TValue>& p, const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator+(Quat<TValue>&& p, const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator+(const Quat<TValue>& p, Quat<TValue>&& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator+(Quat<TValue>&& p, Quat<TValue>&& q);

	template<typename TValue>
	constexpr Quat<TValue> operator+(const Quat<TValue>& q, const TValue& value);
	template<typename TValue>
	constexpr Quat<TValue>&& operator+(Quat<TValue>&& q, const TValue& value);
	template<typename TValue>
	constexpr Quat<TValue> operator+(const TValue& value, const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator+(const TValue& value, Quat<TValue>&& q);

	template<typename TValue>
	constexpr Quat<TValue> operator-(const Quat<TValue>& p, const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator-(Quat<TValue>&& p, const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator-(const Quat<TValue>& p, Quat<TValue>&& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator-(Quat<TValue>&& p, Quat<TValue>&& q);

	template<typename TValue>
	constexpr Quat<TValue> operator-(const Quat<TValue>& q, const TValue& value);
	template<typename TValue>
	constexpr Quat<TValue>&& operator-(Quat<TValue>&& q, const TValue& value);
	template<typename TValue>
	constexpr Quat<TValue> operator-(const TValue& value, const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator-(const TValue& value, Quat<TValue>&& q);

	template<typename TValue>
	constexpr Quat<TValue> operator*(const Quat<TValue>& p, const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue> operator*(Quat<TValue>&& p, const Quat<TValue>& q);

	template<typename TValue>
	constexpr Quat<TValue> operator*(const Quat<TValue>& q, const TValue& value);
	template<typename TValue>
	constexpr Quat<TValue>&& operator*(Quat<TValue>&& q, const TValue& value);
	template<typename TValue>
	constexpr Quat<TValue> operator*(const TValue& value, const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator*(const TValue& value, Quat<TValue>&& q);

	template<typename TValue>
	constexpr Quat<TValue> operator/(const Quat<TValue>& q, const TValue& value);
	template<typename TValue>
	constexpr Quat<TValue>&& operator/(Quat<TValue>&& q, const TValue& value);

	template<typename TValue>
	constexpr Quat<TValue> operator+(const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator+(Quat<TValue>&& q);

	template<typename TValue>
	constexpr Quat<TValue> operator-(const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue>&& operator-(Quat<TValue>&& q);

	template<typename TValue>
	constexpr Quat<TValue> inverse(const Quat<TValue>& q);
	template<typename TValue>
	constexpr Quat<TValue> conjugate(const Quat<TValue>& q);
}
