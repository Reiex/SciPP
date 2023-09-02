///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreDecl.hpp>

namespace scp
{
	template<typename TValue>
	const TValue Frac<TValue>::_zero(0);

	template<typename TValue>
	const TValue Frac<TValue>::_one(1);

	template<typename TValue>
	constexpr Frac<TValue>::Frac() :
		_p(_zero),
		_q(_one)
	{
	}

	template<typename TValue>
	constexpr Frac<TValue>::Frac(const TValue& x) :
		_p(x),
		_q(_one)
	{
	}

	template<typename TValue>
	constexpr Frac<TValue>::Frac(const TValue& p, const TValue& q) :
		_p(p),
		_q(q)
	{
		assert(q != _zero);
		_simplify();
	}

	template<typename TValue>
	constexpr Frac<TValue>& Frac<TValue>::operator+=(const Frac<TValue>& x)
	{
		const TValue p = _p * x._q + x._p * _q;
		const TValue q = _q * x._q;

		_p = p;
		_q = q;

		_simplify();

		return *this;
	}

	template<typename TValue>
	constexpr Frac<TValue>& Frac<TValue>::operator-=(const Frac<TValue>& x)
	{
		const TValue p = _p * x._q - x._p * _q;
		const TValue q = _q * x._q;

		_p = p;
		_q = q;

		_simplify();

		return *this;
	}

	template<typename TValue>
	constexpr Frac<TValue>& Frac<TValue>::operator*=(const Frac<TValue>& x)
	{
		_p *= x._p;
		_q *= x._q;

		_simplify();

		return *this;
	}

	template<typename TValue>
	constexpr Frac<TValue>& Frac<TValue>::operator/=(const Frac<TValue>& x)
	{
		const TValue p = _p * x._q;
		const TValue q = _q * x._p;

		_p = p;
		_q = q;

		_simplify();

		return *this;
	}

	template<typename TValue>
	constexpr Frac<TValue>& Frac<TValue>::operator+=(const TValue& x)
	{
		_p += x * _q;
		_simplify();
		return *this;
	}

	template<typename TValue>
	constexpr Frac<TValue>& Frac<TValue>::operator-=(const TValue& x)
	{
		_p -= x * _q;
		_simplify();
		return *this;
	}

	template<typename TValue>
	constexpr Frac<TValue>& Frac<TValue>::operator*=(const TValue& x)
	{
		_p *= x;
		_simplify();
		return *this;
	}

	template<typename TValue>
	constexpr Frac<TValue>& Frac<TValue>::operator/=(const TValue& x)
	{
		_q *= x;
		_simplify();
		return *this;
	}

	template<typename TValue>
	constexpr bool Frac<TValue>::operator==(const Frac<TValue>& x) const
	{
		return compare(x) == 0;
	}

	template<typename TValue>
	constexpr bool Frac<TValue>::operator!=(const Frac<TValue>& x) const
	{
		return compare(x) != 0;
	}

	template<typename TValue>
	constexpr bool Frac<TValue>::operator<(const Frac<TValue>& x) const
	{
		return compare(x) < 0;
	}

	template<typename TValue>
	constexpr bool Frac<TValue>::operator>(const Frac<TValue>& x) const
	{
		return compare(x) > 0;
	}

	template<typename TValue>
	constexpr bool Frac<TValue>::operator<=(const Frac<TValue>& x) const
	{
		return compare(x) <= 0;
	}

	template<typename TValue>
	constexpr bool Frac<TValue>::operator>=(const Frac<TValue>& x) const
	{
		return compare(x) >= 0;
	}

	template<typename TValue>
	constexpr int8_t Frac<TValue>::compare(const Frac<TValue>& x) const
	{
		if (_p == x._p && _q == x._q)
		{
			return 0;
		}

		const TValue a = _p * x._q;
		const TValue b = _q * x._p;

		if (a > b)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}

	template<typename TValue>
	constexpr void Frac<TValue>::negate()
	{
		_p = -_p;
	}

	template<typename TValue>
	constexpr const TValue& Frac<TValue>::getNumerator() const
	{
		return _p;
	}

	template<typename TValue>
	constexpr const TValue& Frac<TValue>::getDenominator() const
	{
		return _q;
	}

	template<typename TValue>
	constexpr void Frac<TValue>::_simplify()
	{
		if (_q < 0)
		{
			_q = -_q;
			_p = -_p;
		}

		if (_p == 0)
		{
			_q = 1;
			return;
		}

		TValue x(gcd(_p, _q));
		if (x != _one)
		{
			_p /= x;
			_q /= x;
		}
	}


	template<typename TValue>
	constexpr Frac<TValue> operator+(const Frac<TValue>& a, const Frac<TValue>& b)
	{
		Frac<TValue> c(a);
		c += b;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator+(Frac<TValue>&& a, const Frac<TValue>& b)
	{
		a += b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator+(const Frac<TValue>& a, Frac<TValue>&& b)
	{
		b += a;
		return std::move(b);
	}
	
	template<typename TValue>
	constexpr Frac<TValue>&& operator+(Frac<TValue>&& a, Frac<TValue>&& b)
	{
		a += b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator+(const Frac<TValue>& a, const TValue& b)
	{
		Frac<TValue> c(a);
		c += b;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator+(Frac<TValue>&& a, const TValue& b)
	{
		a += b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator+(const TValue& a, const Frac<TValue>& b)
	{
		Frac<TValue> c(b);
		c += a;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator+(const TValue& a, Frac<TValue>&& b)
	{
		b += a;
		return std::move(b);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator-(const Frac<TValue>& a, const Frac<TValue>& b)
	{
		Frac<TValue> c(a);
		c -= b;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator-(Frac<TValue>&& a, const Frac<TValue>& b)
	{
		a -= b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator-(const Frac<TValue>& a, Frac<TValue>&& b)
	{
		b -= a;
		return -std::move(b);
	}
	
	template<typename TValue>
	constexpr Frac<TValue>&& operator-(Frac<TValue>&& a, Frac<TValue>&& b)
	{
		a -= b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator-(const Frac<TValue>& a, const TValue& b)
	{
		Frac<TValue> c(a);
		c -= b;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator-(Frac<TValue>&& a, const TValue& b)
	{
		a -= b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator-(const TValue& a, const Frac<TValue>& b)
	{
		Frac<TValue> c(-b);
		c += a;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator-(const TValue& a, Frac<TValue>&& b)
	{
		b -= a;
		return -std::move(b);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator*(const Frac<TValue>& a, const Frac<TValue>& b)
	{
		Frac<TValue> c(a);
		c *= b;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator*(Frac<TValue>&& a, const Frac<TValue>& b)
	{
		a *= b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator*(const Frac<TValue>& a, Frac<TValue>&& b)
	{
		b *= a;
		return std::move(b);
	}
	
	template<typename TValue>
	constexpr Frac<TValue>&& operator*(Frac<TValue>&& a, Frac<TValue>&& b)
	{
		a *= b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator*(const Frac<TValue>& a, const TValue& b)
	{
		Frac<TValue> c(a);
		c *= b;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator*(Frac<TValue>&& a, const TValue& b)
	{
		a *= b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator*(const TValue& a, const Frac<TValue>& b)
	{
		Frac<TValue> c(b);
		c *= a;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator*(const TValue& a, Frac<TValue>&& b)
	{
		b *= a;
		return std::move(b);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator/(const Frac<TValue>& a, const Frac<TValue>& b)
	{
		Frac<TValue> c(a);
		c /= b;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator/(Frac<TValue>&& a, const Frac<TValue>& b)
	{
		a /= b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator/(const Frac<TValue>& a, const TValue& b)
	{
		Frac<TValue> c(a);
		c /= b;
		return c;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator/(Frac<TValue>&& a, const TValue& b)
	{
		a /= b;
		return std::move(a);
	}

	template<typename TValue>
	constexpr Frac<TValue> operator+(const Frac<TValue>& a)
	{
		return a;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator+(Frac<TValue>&& a)
	{
		return std::move(a);
	}
	
	template<typename TValue>
	constexpr Frac<TValue> operator-(const Frac<TValue>& a)
	{
		Frac<TValue> b(a);
		b.negate();
		return b;
	}

	template<typename TValue>
	constexpr Frac<TValue>&& operator-(Frac<TValue>&& a)
	{
		a.negate();
		return std::move(a);
	}
}
