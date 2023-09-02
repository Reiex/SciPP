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
	template<typename TInteger>
	constexpr Rational<TInteger>::Rational() : Frac<TInteger>()
	{
	}

	template<typename TInteger>
	constexpr Rational<TInteger>::Rational(double x) : Frac<TInteger>()
	{
		const uint64_t raw = *reinterpret_cast<uint64_t*>(&x);

		constexpr uint64_t signFilter = 0x8000000000000000;
		constexpr uint64_t exponentFilter = 0x7FF0000000000000;
		constexpr uint8_t exponentShift = 52;
		constexpr uint64_t mantissaFilter = 0x000FFFFFFFFFFFFF;
		constexpr uint64_t mantissaDivisor = 0x0010000000000000;

		bool negative = (raw & signFilter) != 0;
		uint64_t exponent = (raw & exponentFilter) >> exponentShift;
		uint64_t mantissa = (raw & mantissaFilter);

		_q = mantissaDivisor;
		_p = mantissaDivisor + mantissa;

		if (exponent < 1023)
		{
			_q <<= 1023 - exponent;
		}
		else if (exponent > 1023)
		{
			_p <<= exponent - 1023;
		}

		_simplify();
	}

	template<typename TInteger>
	constexpr Rational<TInteger>::Rational(const TInteger& x) : Frac<TInteger>(x)
	{
	}

	template<typename TInteger>
	constexpr Rational<TInteger>::Rational(const TInteger& p, const TInteger& q) : Frac<TInteger>(p, q)
	{
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator+=(const Rational<TInteger>& x)
	{
		return dynamic_cast<Rational<TInteger>&>(Frac<TInteger>::operator+=(x));
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator-=(const Rational<TInteger>& x)
	{
		return dynamic_cast<Rational<TInteger>&>(Frac<TInteger>::operator-=(x));
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator*=(const Rational<TInteger>& x)
	{
		return dynamic_cast<Rational<TInteger>&>(Frac<TInteger>::operator*=(x));
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator/=(const Rational<TInteger>& x)
	{
		return dynamic_cast<Rational<TInteger>&>(Frac<TInteger>::operator/=(x));
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator+=(const TInteger& x)
	{
		return dynamic_cast<Rational<TInteger>&>(Frac<TInteger>::operator+=(x));
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator-=(const TInteger& x)
	{
		return dynamic_cast<Rational<TInteger>&>(Frac<TInteger>::operator-=(x));
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator*=(const TInteger& x)
	{
		return dynamic_cast<Rational<TInteger>&>(Frac<TInteger>::operator*=(x));
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator/=(const TInteger& x)
	{
		return dynamic_cast<Rational<TInteger>&>(Frac<TInteger>::operator/=(x));
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator+=(double x)
	{
		if (std::floor(x) == x)
		{
			return operator+=(TInteger(x));
		}
		else
		{
			return operator+=(Rational<TInteger>(x));
		}
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator-=(double x)
	{
		if (std::floor(x) == x)
		{
			return operator-=(TInteger(x));
		}
		else
		{
			return operator-=(Rational<TInteger>(x));
		}
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator*=(double x)
	{
		if (std::floor(x) == x)
		{
			return operator*=(TInteger(x));
		}
		else
		{
			return operator*=(Rational<TInteger>(x));
		}
	}

	template<typename TInteger>
	constexpr Rational<TInteger>& Rational<TInteger>::operator/=(double x)
	{
		if (std::floor(x) == x)
		{
			return operator/=(TInteger(x));
		}
		else
		{
			return operator/=(Rational<TInteger>(x));
		}
	}

	template<typename TInteger>
	constexpr bool Rational<TInteger>::operator==(const Rational<TInteger>& x) const
	{
		return Frac<TInteger>::operator==(x);
	}

	template<typename TInteger>
	constexpr bool Rational<TInteger>::operator!=(const Rational<TInteger>& x) const
	{
		return Frac<TInteger>::operator!=(x);
	}

	template<typename TInteger>
	constexpr bool Rational<TInteger>::operator<(const Rational<TInteger>& x) const
	{
		return Frac<TInteger>::operator<(x);
	}

	template<typename TInteger>
	constexpr bool Rational<TInteger>::operator>(const Rational<TInteger>& x) const
	{
		return Frac<TInteger>::operator>(x);
	}

	template<typename TInteger>
	constexpr bool Rational<TInteger>::operator<=(const Rational<TInteger>& x) const
	{
		return Frac<TInteger>::operator<=(x);
	}

	template<typename TInteger>
	constexpr bool Rational<TInteger>::operator>=(const Rational<TInteger>& x) const
	{
		return Frac<TInteger>::operator>=(x);
	}

	template<typename TInteger>
	constexpr std::string Rational<TInteger>::decimals(uint64_t n) const
	{
		std::stringstream s;
		Rational<TInteger> y(*this);

		if (_p < _zero)
		{
			s << "-";
			y = -y;
		}
		
		s << (y._p / y._q);

		if (n > 0)
		{
			s << ".";
		}
		else
		{
			return s.str();
		}

		y -= (y._p / y._q);
		y *= scp::pow(TInteger(10), n);

		std::stringstream d;
		d << (y._p / y._q);
		s << std::string(n - d.str().size(), '0') << d.str();

		return s.str();
	}


	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const Rational<TInteger>& a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(a);
		c += b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a, const Rational<TInteger>& b)
	{
		a += b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(const Rational<TInteger>& a, Rational<TInteger>&& b)
	{
		b += a;
		return std::move(b);
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a, Rational<TInteger>&& b)
	{
		a += b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const Rational<TInteger>& a, const TInteger& b)
	{
		Rational<TInteger> c(a);
		c += b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a, const TInteger& b)
	{
		a += b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const TInteger& a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(b);
		c += a;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(const TInteger& a, Rational<TInteger>&& b)
	{
		b += a;
		return std::move(b);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const Rational<TInteger>& a, double b)
	{
		Rational<TInteger> c(a);
		c += b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a, double b)
	{
		a += b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator+(double a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(b);
		c += a;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(double a, Rational<TInteger>&& b)
	{
		b += a;
		return std::move(b);
	}
	
	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const Rational<TInteger>& a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(a);
		c -= b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a, const Rational<TInteger>& b)
	{
		a -= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(const Rational<TInteger>& a, Rational<TInteger>&& b)
	{
		b -= a;
		return -std::move(b);
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a, Rational<TInteger>&& b)
	{
		a -= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const Rational<TInteger>& a, const TInteger& b)
	{
		Rational<TInteger> c(a);
		c -= b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a, const TInteger& b)
	{
		a -= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const TInteger& a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(-b);
		c += a;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(const TInteger& a, Rational<TInteger>&& b)
	{
		b -= a;
		return -std::move(b);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const Rational<TInteger>& a, double b)
	{
		Rational<TInteger> c(a);
		c -= b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a, double b)
	{
		a -= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator-(double a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(-b);
		c += a;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(double a, Rational<TInteger>&& b)
	{
		b -= a;
		return -std::move(b);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator*(const Rational<TInteger>& a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(a);
		c *= b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(Rational<TInteger>&& a, const Rational<TInteger>& b)
	{
		a *= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(const Rational<TInteger>& a, Rational<TInteger>&& b)
	{
		b *= a;
		return std::move(b);
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(Rational<TInteger>&& a, Rational<TInteger>&& b)
	{
		a *= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator*(const Rational<TInteger>& a, const TInteger& b)
	{
		Rational<TInteger> c(a);
		c *= b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(Rational<TInteger>&& a, const TInteger& b)
	{
		a *= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator*(const TInteger& a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(b);
		c *= a;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(const TInteger& a, Rational<TInteger>&& b)
	{
		b *= a;
		return std::move(b);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator*(const Rational<TInteger>& a, double b)
	{
		Rational<TInteger> c(a);
		c *= b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(Rational<TInteger>&& a, double b)
	{
		a *= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator*(double a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(b);
		c *= a;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator*(double a, Rational<TInteger>&& b)
	{
		b *= a;
		return std::move(b);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator/(const Rational<TInteger>& a, const Rational<TInteger>& b)
	{
		Rational<TInteger> c(a);
		c /= b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator/(Rational<TInteger>&& a, const Rational<TInteger>& b)
	{
		a /= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator/(const Rational<TInteger>& a, double b)
	{
		Rational<TInteger> c(a);
		c /= b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator/(Rational<TInteger>&& a, double b)
	{
		a /= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator/(const Rational<TInteger>& a, const TInteger& b)
	{
		Rational<TInteger> c(a);
		c /= b;
		return c;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator/(Rational<TInteger>&& a, const TInteger& b)
	{
		a /= b;
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator-(const Rational<TInteger>& a)
	{
		Rational<TInteger> b(a);
		b.negate();
		return b;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator-(Rational<TInteger>&& a)
	{
		a.negate();
		return std::move(a);
	}

	template<typename TInteger>
	constexpr Rational<TInteger> operator+(const Rational<TInteger>& a)
	{
		return a;
	}

	template<typename TInteger>
	constexpr Rational<TInteger>&& operator+(Rational<TInteger>&& a)
	{
		return std::move(a);
	}
}
