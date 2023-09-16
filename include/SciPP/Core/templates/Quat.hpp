///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Pélégrin Marius
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreDecl.hpp>

namespace scp
{
	template<typename TValue>
	constexpr Quat<TValue>::Quat(const TValue& value) :
		w(value),
		x(_zero),
		y(_zero),
		z(_zero)
	{
	}

	template<typename TValue>
	constexpr Quat<TValue>::Quat(const TValue& wValue, const TValue& xValue, const TValue& yValue, const TValue& zValue) :
		w(wValue),
		x(xValue),
		y(yValue),
		z(zValue)
	{
	}

	template<typename TValue>
	constexpr Quat<TValue>& Quat<TValue>::operator+=(const Quat<TValue>& q)
	{
		w += q.w;
		x += q.x;
		y += q.y;
		z += q.z;

		return *this;
	}

	template<typename TValue>
	constexpr Quat<TValue>& Quat<TValue>::operator-=(const Quat<TValue>& q)
	{
		w -= q.w;
		x -= q.x;
		y -= q.y;
		z -= q.z;

		return *this;
	}

	template<typename TValue>
	constexpr Quat<TValue>& Quat<TValue>::operator*=(const Quat<TValue>& q)
	{
		const TValue a = w * q.w - x * q.x - y * q.y - z * q.z;
		const TValue b = w * q.x + x * q.w + y * q.z - z * q.y;
		const TValue c = w * q.y - x * q.z + y * q.w + z * q.x;
		const TValue d = w * q.z + x * q.y - y * q.x + z * q.w;

		w = a;
		x = b;
		y = c;
		z = d;

		return *this;
	}

	template<typename TValue>
	constexpr Quat<TValue>& Quat<TValue>::operator+=(const TValue& value)
	{
		w += value;
		return *this;
	}

	template<typename TValue>
	constexpr Quat<TValue>& Quat<TValue>::operator-=(const TValue& value)
	{
		w -= value;
		return *this;
	}

	template<typename TValue>
	constexpr Quat<TValue>& Quat<TValue>::operator*=(const TValue& value)
	{
		w *= value;
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	template<typename TValue>
	constexpr Quat<TValue>& Quat<TValue>::operator/=(const TValue& value)
	{
		w /= value;
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	template<typename TValue>
	constexpr bool Quat<TValue>::operator==(const Quat<TValue>& q) const
	{
		return w = q.w && x = q.x && y = q.y && z = q.z;
	}

	template<typename TValue>
	constexpr bool Quat<TValue>::operator!=(const Quat<TValue>& q) const
	{
		return !(*this == q);
	}

	template<typename TValue>
	constexpr void Quat<TValue>::setFromRotationAxisAngle(const TValue& xAxis, const TValue& yAxis, const TValue& zAxis, const TValue& angle)
	{
		assert(std::abs(xAxis * xAxis + yAxis * yAxis + zAxis * zAxis - _one) < 1e-2f);

		const TValue halfAngle = angle / 2;
		const TValue sinHalfAngle = std::sin(halfAngle);

		w = std::cos(halfAngle);
		x = xAxis * sinHalfAngle;
		y = yAxis * sinHalfAngle;
		z = zAxis * sinHalfAngle;
	}

	template<typename TValue>
	constexpr void Quat<TValue>::getRotationAxisAngle(TValue& xAxis, TValue& yAxis, TValue& zAxis, TValue& angle) const
	{
		assert(std::abs(normSq() - _one) < 1e-2f);

		angle = std::acos(w) * 2;

		const TValue factor = std::sin(angle / 2);
		xAxis = x / factor;
		yAxis = y / factor;
		zAxis = z / factor;
	}

	template<typename TValue>
	constexpr void Quat<TValue>::setFromRotationMatrix(const TValue& r00, const TValue& r01, const TValue& r02, const TValue& r10, const TValue& r11, const TValue& r12, const TValue& r20, const TValue& r21, const TValue& r22)
	{
		const TValue trace = r00 + r11 + r22;

		if (trace > _zero)
		{
			const TValue s = 2 * std::sqrt(_one + trace);
			w = s / 4;
			x = (r21 - r12) / s;
			y = (r02 - r20) / s;
			z = (r10 - r01) / s;
		}
		else if (r00 > r11 && r00 > r22)
		{
			const TValue s = 2 * std::sqrt(_one + r00 - r11 - r22);
			w = (r21 - r12) / s;
			x = s / 4;
			y = (r01 + r10) / s;
			z = (r02 + r20) / s;
		}
		else if (r11 > r22)
		{
			const TValue s = 2 * std::sqrt(_one - r00 + r11 - r22);
			w = (r02 - r20) / s;
			x = (r01 + r10) / s;
			y = s / 4;
			z = (r12 + r21) / s;
		}
		else
		{
			const TValue s = 2 * std::sqrt(_one - r00 - r11 + r22);
			w = (r10 - r01) / s;
			x = (r02 + r20) / s;
			y = (r12 + r21) / s;
			z = s / 4;
		}
	}

	template<typename TValue>
	constexpr void Quat<TValue>::getRotationMatrix(TValue& r00, TValue& r01, TValue& r02, TValue& r10, TValue& r11, TValue& r12, TValue& r20, TValue& r21, TValue& r22) const
	{
		assert(std::abs(normSq() - _one) < 1e-2f);

		const TValue ww = w * w;
		const TValue xx = x * x;
		const TValue yy = y * y;
		const TValue zz = z * z;

		const TValue wx2 = 2 * w * x;
		const TValue wy2 = 2 * w * y;
		const TValue wz2 = 2 * w * z;
		const TValue xy2 = 2 * x * y;
		const TValue xz2 = 2 * x * z;
		const TValue yz2 = 2 * y * z;

		r00 = ww + xx - yy - zz;
		r01 = xy2 - wz2;
		r02 = wy2 + xz2;
		r10 = wz2 + xy2;
		r11 = ww - xx + yy - zz;
		r12 = yz2 - wx2;
		r20 = xz2 - wy2;
		r21 = wx2 + yz2;
		r22 = ww - xx - yy + zz;
	}

	template<typename TValue>
	constexpr void Quat<TValue>::setFromUnitVectorRotation(const TValue& xFrom, const TValue& yFrom, const TValue& zFrom, const TValue& xTo, const TValue& yTo, const TValue& zTo)
	{
		// TODO: Dutch angle and up vector

		assert(std::abs(xFrom * xFrom + yFrom * yFrom + zFrom * zFrom - _one) < 1e-2f);
		assert(std::abs(xTo * xTo + yTo * yTo + zTo * zTo - _one) < 1e-2f);

		const TValue xN = yFrom * zTo - yTo * zFrom;
		const TValue yN = zFrom * xTo - zTo * xFrom;
		const TValue zN = xFrom * yTo - xTo * yFrom;
		const TValue nLength = std::sqrt(xN * xN + yN * yN + zN * zN);

		// if vFrom is colinear to vTo

		if (nLength == _zero)
		{
			// if vFrom == vTo

			if (std::signbit(xFrom) == std::signbit(yFrom))
			{
				w = _one;
				x = _zero;
				y = _zero;
				z = _zero;
			}

			// if vFrom == -vTo

			else
			{
				// if vFrom == (1, 0, 0) and vTo == (-1, 0, 0)

				if (xFrom == _one)
				{
					w = _zero;
					x = _zero;
					y = _one;
					z = _zero;
				}

				// if vFrom is a random vector and vTo == -vFrom

				else
				{
					w = _zero;
					x = _one - xFrom * xFrom;
					y = -xFrom * yFrom;
					z = -xFrom * zFrom;
					const TValue invLength = _one / std::sqrt(x * x + y * y + z * z);
					x *= invLength;
					y *= invLength;
					z *= invLength;
				}
			}
		}

		// if vFrom and vTo are not related

		else
		{
			TValue angle = std::asin(nLength);
			const TValue dotFromTo = xFrom * xTo + yFrom * yTo + zFrom * zTo;
			if (dotFromTo < _zero)
			{
				angle = std::numbers::pi - angle;
			}

			const TValue nInvLength = _one / nLength;
			setFromRotationAxisAngle(xN * nInvLength, yN * nInvLength, zN * nInvLength, angle);
		}
	}

	template<typename TValue>
	constexpr void Quat<TValue>::inverse()
	{
		assert(w != _zero || x != _zero || y != _zero || z != _zero);

		const TValue length = normSq();
		w /= length;
		x = -x / length;
		y = -y / length;
		z = -z / length;
	}

	template<typename TValue>
	constexpr void Quat<TValue>::conjugate()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	template<typename TValue>
	constexpr TValue Quat<TValue>::normSq() const
	{
		return w * w + x * x + y * y + z * z;
	}

	template<typename TValue>
	constexpr TValue Quat<TValue>::norm() const
	{
		return std::sqrt(normSq());
	}


	template<typename TValue>
	constexpr Quat<TValue> operator+(const Quat<TValue>& p, const Quat<TValue>& q)
	{
		Quat<TValue> result(p);
		result += q;
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator+(Quat<TValue>&& p, const Quat<TValue>& q)
	{
		p += q;
		return std::move(p);
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator+(const Quat<TValue>& p, Quat<TValue>&& q)
	{
		q += p;
		return std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator+(Quat<TValue>&& p, Quat<TValue>&& q)
	{
		p += q;
		return std::move(p);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator+(const Quat<TValue>& q, const TValue& value)
	{
		Quat<TValue> result(q);
		result += value;
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator+(Quat<TValue>&& q, const TValue& value)
	{
		q += value;
		return std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator+(const TValue& value, const Quat<TValue>& q)
	{
		Quat<TValue> result(q);
		result += value;
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator+(const TValue& value, Quat<TValue>&& q)
	{
		q += value;
		return std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator-(const Quat<TValue>& p, const Quat<TValue>& q)
	{
		Quat<TValue> result(p);
		result -= q;
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator-(Quat<TValue>&& p, const Quat<TValue>& q)
	{
		p -= q;
		return std::move(p);
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator-(const Quat<TValue>& p, Quat<TValue>&& q)
	{
		q -= p;
		return -std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator-(Quat<TValue>&& p, Quat<TValue>&& q)
	{
		p -= q;
		return std::move(p);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator-(const Quat<TValue>& q, const TValue& value)
	{
		Quat<TValue> result(q);
		result -= value;
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator-(Quat<TValue>&& q, const TValue& value)
	{
		q -= value;
		return std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator-(const TValue& value, const Quat<TValue>& q)
	{
		Quat<TValue> result(q);
		result -= value;
		return -result;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator-(const TValue& value, Quat<TValue>&& q)
	{
		q -= value;
		return -std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator*(const Quat<TValue>& p, const Quat<TValue>& q)
	{
		Quat<TValue> result(p);
		result *= q;
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue> operator*(Quat<TValue>&& p, const Quat<TValue>& q)
	{
		p *= q;
		return std::move(p);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator*(const Quat<TValue>& q, const TValue& value)
	{
		Quat<TValue> result(q);
		result *= value;
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator*(Quat<TValue>&& q, const TValue& value)
	{
		q *= value;
		return std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator*(const TValue& value, const Quat<TValue>& q)
	{
		Quat<TValue> result(q);
		result *= value;
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator*(const TValue& value, Quat<TValue>&& q)
	{
		q *= value;
		return std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator/(const Quat<TValue>& q, const TValue& value)
	{
		Quat<TValue> result(q);
		result /= value;
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator/(Quat<TValue>&& q, const TValue& value)
	{
		q /= value;
		return std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator+(const Quat<TValue>& q)
	{
		return q;
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator+(Quat<TValue>&& q)
	{
		return std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue> operator-(const Quat<TValue>& q)
	{
		return { -q.w, -q.x, -q.y, -q.z };
	}

	template<typename TValue>
	constexpr Quat<TValue>&& operator-(Quat<TValue>&& q)
	{
		q.w = -q.w;
		q.x = -q.x;
		q.y = -q.y;
		q.z = -q.z;

		return std::move(q);
	}

	template<typename TValue>
	constexpr Quat<TValue> inverse(const Quat<TValue>& q)
	{
		Quat<TValue> result(q);
		result.inverse();
		return result;
	}

	template<typename TValue>
	constexpr Quat<TValue> conjugate(const Quat<TValue>& q)
	{
		Quat<TValue> result(q);
		result.conjugate();
		return result;
	}
}
