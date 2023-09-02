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
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>::BigInt() :
		_values(),
		_positive(true)
	{
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>::BigInt(int64_t x) :
		_positive(x >= 0)
	{
		if (!_positive)
		{
			x = -x;
		}

		while (x != 0)
		{
			_values.push_back(static_cast<TBase>(x & _bufferLowFilter));
			x >>= _baseBitSize;
		}
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>::BigInt(const std::string& str)
	{
		std::stringstream stream;
		stream << str;
		stream >> *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator+=(const BigInt<TBase, TBuffer>& x)
	{
		// If this == 0, return x

		if (_values.empty())
		{
			_values = x._values;
			_positive = x._positive;
			return *this;
		}

		// If x == 0, return this

		if (x._values.empty())
		{
			return *this;
		}

		// If this and x are not the same sign, perform a substraction

		if (_positive != x._positive)
		{
			_positive = !_positive;
			*this -= x;
			_positive = !_positive;
			return *this;
		}

		// Identifying the "biggest" number (the one with the most "digits")

		uint64_t sizeBig;
		uint64_t sizeSmall;
		const TBase* itBigBeg;
		const TBase* itSmallBeg;
		if (_values.size() >= x._values.size())
		{
			sizeBig = _values.size();
			sizeSmall = x._values.size();
			itBigBeg = _values.data();
			itSmallBeg = x._values.data();
		}
		else
		{
			sizeBig = x._values.size();
			sizeSmall = _values.size();
			itBigBeg = x._values.data();
			itSmallBeg = _values.data();
		}

		// Finding if an additional digit is necessary

		const TBase* itBig = itBigBeg + sizeBig - 1;
		const TBase* itSmall = itSmallBeg + sizeBig - 1;
		const TBase* itSmallEnd = itSmallBeg + sizeSmall - 1;
		while (itSmall != itSmallEnd && *itBig == _baseMax)
		{
			--itSmall;
			--itBig;
		}

		TBuffer buffer = _baseMax;
		uint64_t newSize = sizeBig;

		if (itSmall == itSmallEnd)
		{
			itSmallEnd = itSmallBeg - 1;
			while (itSmall != itSmallEnd && buffer == _baseMax)
			{
				buffer = static_cast<TBuffer>(*itSmall) + static_cast<TBuffer>(*itBig);
				if (buffer > _baseMax)
				{
					++newSize;
					break;
				}

				--itSmall;
				--itBig;
			}
		}

		// Compute the addition

		_values.resize(newSize, 0);
		itSmall = x._values.data();
		sizeSmall = x._values.size();

		itSmallEnd = itSmall + sizeSmall;

		TBase* itOut = _values.data();
		buffer = 0;
		while (itSmall != itSmallEnd)
		{
			buffer += static_cast<TBuffer>(*itSmall) + static_cast<TBuffer>(*itOut);
			*itOut = buffer & _bufferLowFilter;
			buffer >>= _baseBitSize;

			++itSmall;
			++itOut;
		}

		while (buffer != 0)
		{
			buffer += *itOut;
			*itOut = buffer & _bufferLowFilter;
			buffer >>= _baseBitSize;

			++itOut;
		}

		return *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator-=(const BigInt<TBase, TBuffer>& x)
	{
		// If this == x, return 0

		if (*this == x)
		{
			_values.clear();
			_positive = true;
			return *this;
		}

		// If this == 0, return -x

		if (_values.empty())
		{
			_values = x._values;
			_positive = !x._positive;
			return *this;
		}

		// If x == 0, return this

		if (x._values.empty())
		{
			return *this;
		}

		// If this and x are not the same sign, perform an addition

		if (_positive != x._positive)
		{
			_positive = !_positive;
			*this += x;
			_positive = !_positive;
			return *this;
		}

		// Identifying the biggest number in absolute value

		uint64_t sizeBig;
		uint64_t sizeSmall;
		const TBase* itBig;
		const TBase* itSmall;
		if ((_positive && *this > x) || (!_positive && *this < x))
		{
			sizeBig = _values.size();
			sizeSmall = x._values.size();
			itBig = _values.data();
			itSmall = x._values.data();
		}
		else
		{
			sizeBig = x._values.size();
			sizeSmall = _values.size();
			_values.resize(sizeBig, 0);
			itBig = x._values.data();
			itSmall = _values.data();
			_positive = !_positive;
		}

		// Perform the substraction

		TBase* itOut = _values.data();
		const TBase* itSmallEnd = itSmall + sizeSmall;
		TBase carry = 0;
		while (itSmall != itSmallEnd)
		{
			if (static_cast<TBuffer>(*itBig) >= static_cast<TBuffer>(*itSmall) + static_cast<TBuffer>(carry))
			{
				*itOut = *itBig - *itSmall - carry;
				carry = 0;
			}
			else
			{
				*itOut = static_cast<TBase>(static_cast<TBuffer>(*itBig) + _baseEnd - static_cast<TBuffer>(*itSmall) - static_cast<TBuffer>(carry));
				carry = 1;
			}

			++itSmall;
			++itBig;
			++itOut;
		}

		const TBase* const itOutEnd = _values.data() + _values.size();
		while (itOut != itOutEnd)
		{
			if (static_cast<TBuffer>(*itBig) >= static_cast<TBuffer>(carry))
			{
				*itOut = *itBig - carry;
				carry = 0;
			}
			else
			{
				*itOut = static_cast<TBase>(static_cast<TBuffer>(*itBig) + _baseEnd - static_cast<TBuffer>(carry));
				carry = 1;
			}

			++itBig;
			++itOut;
		}

		// Remove trailing 0s

		auto it = _values.cend();
		while (*(--it) == 0);

		_values.erase(it + 1, _values.end());

		return *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator*=(const BigInt<TBase, TBuffer>& x)
	{
		// If this == 0 or x == 0, return 0

		if (_values.empty() || x._values.empty())
		{
			_values.clear();
			_positive = true;
			return *this;
		}

		// Multiplication

		_positive = (_positive == x._positive);

		std::vector<TBase> newValues(_values.size() + x._values.size(), 0);

		TBase* itOut = newValues.data();
		for (const TBase& valueT : _values)
		{
			TBuffer buffer = 0;
			for (const TBase& valueX : x._values)
			{
				buffer += static_cast<TBuffer>(valueT) * static_cast<TBuffer>(valueX);
				buffer += static_cast<TBuffer>(*itOut);
				*itOut = buffer & _bufferLowFilter;
				buffer >>= _baseBitSize;
				++itOut;
			}

			*itOut = buffer;
			itOut -= x._values.size() - 1;
		}

		// Remove trailing 0s

		auto it = newValues.cend();
		while (*(--it) == 0);

		newValues.erase(it + 1, newValues.end());
		_values = newValues;

		return *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator/=(const BigInt<TBase, TBuffer>& x)
	{
		assert(!x._values.empty());

		// If |x| > |this|, return 0

		const bool positive = (_positive == x._positive);
		_positive = x._positive;
		if ((_positive && x > *this) || (!_positive && x < *this))
		{
			_values.clear();
			_positive = true;
			return *this;
		}

		// Perform the division

		_positive = positive;

		const uint64_t bitSizeT = getBitSize();
		const uint64_t bitSizeX = x.getBitSize();
		BigInt<TBase, TBuffer> y = x << (bitSizeT - bitSizeX);
		y._positive = _positive;
		BigInt<TBase, TBuffer> z = 0;
		uint64_t shift = 0;
		while (y >= x)
		{
			++shift;
			if (*this >= y)
			{
				*this -= y;
				z <<= shift;
				shift = 0;
				++z;
			}
			y >>= 1;
		}

		z <<= shift;

		*this = z;

		return *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator%=(const BigInt<TBase, TBuffer>& x)
	{
		assert(!x._values.empty());

		// If |x| > |this|, return this

		const bool positive = _positive;
		_positive = x._positive;
		if ((_positive && x > *this) || (!_positive && x < *this))
		{
			return *this;
		}

		// Perform the modulo

		_positive = positive;

		const uint64_t bitSizeT = getBitSize();
		const uint64_t bitSizeX = x.getBitSize();
		BigInt<TBase, TBuffer> y = x << (bitSizeT - bitSizeX);
		y._positive = _positive;

		while (y >= x)
		{
			if (*this >= y)
			{
				*this -= y;
			}
			y >>= 1;
		}

		return *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator&=(const BigInt<TBase, TBuffer>& x)
	{
		if (_values.empty())
		{
			return *this;
		}

		_positive = true;

		if (x._values.empty())
		{
			_values.empty();
			return *this;
		}

		auto itX = x._values.cbegin();
		auto it = _values.begin();
		auto itEnd = _values.cbegin() + std::min(_values.size(), x._values.size());
		while (it != itEnd)
		{
			*it &= *itX;

			++it;
			++itX;
		}

		itEnd = _values.cbegin();
		while (it != itEnd)
		{
			if (*(--it) != 0)
			{
				_values.erase(it + 1, _values.end());
				return *this;
			}
		}

		if (*it == 0)
		{
			_values.clear();
			return *this;
		}
		else
		{
			_values.erase(it + 1, _values.end());
			return *this;
		}
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator|=(const BigInt<TBase, TBuffer>& x)
	{
		_positive = true;

		_values.resize(std::max(_values.size(), x._values.size()));

		auto itX = x._values.cbegin();
		const auto itXEnd = x._values.cend();
		auto it = _values.begin();
		const auto itEnd = _values.cend();
		while (it != itEnd && itX != itXEnd)
		{
			*it |= *itX;

			++it;
			++itX;
		}

		return *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator^=(const BigInt<TBase, TBuffer>& x)
	{
		_positive = true;

		_values.resize(std::max(_values.size(), x._values.size()));

		auto itX = x._values.cbegin();
		const auto itXEnd = x._values.cend();
		auto it = _values.begin();
		const auto itEnd = _values.cend();
		while (it != itEnd && itX != itXEnd)
		{
			*it ^= *itX;

			++it;
			++itX;
		}

		itEnd = _values.cbegin();
		while (it != itEnd)
		{
			if (*(--it) != 0)
			{
				_values.erase(it + 1, _values.end());
				return *this;
			}
		}

		if (*it == 0)
		{
			_values.clear();
			return *this;
		}
		else
		{
			_values.erase(it + 1, _values.end());
			return *this;
		}
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator<<=(uint64_t x)
	{
		if (_values.empty())
		{
			return *this;
		}

		const uint64_t cellShift = x / _baseBitSize;
		const uint64_t shift = x % _baseBitSize;
		const uint64_t negShift = _baseBitSize - shift;

		_values.insert(_values.cbegin(), cellShift, 0);
		if (shift == 0)
		{
			return *this;
		}

		auto it = _values.begin() + cellShift;
		const auto itEnd = _values.cend();
		TBase buffer = 0, bufferNext = 0;
		while (it != itEnd)
		{
			bufferNext = *it >> negShift;
			*it = buffer | (*it << shift);
			buffer = bufferNext;
			++it;
		}

		if (buffer != 0)
		{
			_values.push_back(buffer);
		}

		return *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator>>=(uint64_t x)
	{
		if (_values.empty())
		{
			return *this;
		}

		const uint64_t cellShift = x / _baseBitSize;

		if (_values.size() <= cellShift)
		{
			_values.clear();
			_positive = true;
			return *this;
		}

		const uint64_t shift = x % _baseBitSize;
		const uint64_t negShift = _baseBitSize - shift;

		_values.erase(_values.cbegin(), _values.cbegin() + cellShift);
		if (shift == 0)
		{
			return *this;
		}


		auto it = _values.begin();
		auto itNext = it + 1;
		auto itEnd = _values.end() - 1;
		while (it != itEnd)
		{
			*it = (*it >> shift) | (*itNext << negShift);
			++it;
			++itNext;
		}

		*itEnd = *itEnd >> shift;
		if (*itEnd == 0)
		{
			_values.pop_back();
		}

		if (_values.empty())
		{
			_positive = true;
		}

		return *this;
	}
	
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator++()
	{
		if (!_positive)
		{
			_positive = true;
			--(*this);
			_positive = false;

			return *this;
		}

		if (_values.empty())
		{
			_values.push_back(1);
			return *this;
		}

		auto it = _values.begin();
		const auto itEnd = _values.cend();
		while (it != itEnd)
		{
			if (*it != _baseMax)
			{
				++(*it);
				break;
			}
			++it;
		}

		std::fill(_values.begin(), it, 0);

		return *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> BigInt<TBase, TBuffer>::operator++(int)
	{
		BigInt<TBase, TBuffer> copy(*this);

		++(*this);

		return copy;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>& BigInt<TBase, TBuffer>::operator--()
	{
		if (!_positive)
		{
			_positive = true;
			++(*this);
			_positive = false;

			return *this;
		}

		if (_values.empty())
		{
			_values.push_back(1);
			_positive = false;
			return *this;
		}

		auto it = _values.begin();
		const auto itEnd = _values.cend();
		while (it != itEnd)
		{
			if (*it != 0)
			{
				--(*it);
				break;
			}
			++it;
		}

		std::fill(_values.begin(), it, _baseMax);

		return *this;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> BigInt<TBase, TBuffer>::operator--(int)
	{
		BigInt<TBase, TBuffer> copy(*this);

		--(*this);

		return copy;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool BigInt<TBase, TBuffer>::operator==(const BigInt<TBase, TBuffer>& x) const
	{
		return compare(x) == 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool BigInt<TBase, TBuffer>::operator!=(const BigInt<TBase, TBuffer>& x) const
	{
		return compare(x) != 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool BigInt<TBase, TBuffer>::operator<(const BigInt<TBase, TBuffer>& x) const
	{
		return compare(x) < 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool BigInt<TBase, TBuffer>::operator>(const BigInt<TBase, TBuffer>& x) const
	{
		return compare(x) > 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool BigInt<TBase, TBuffer>::operator<=(const BigInt<TBase, TBuffer>& x) const
	{
		return compare(x) <= 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool BigInt<TBase, TBuffer>::operator>=(const BigInt<TBase, TBuffer>& x) const
	{
		return compare(x) >= 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr int8_t BigInt<TBase, TBuffer>::compare(const BigInt<TBase, TBuffer>& x) const
	{
		if (_positive && !x._positive)
		{
			return 1;
		}

		if (!_positive && x._positive)
		{
			return -1;
		}

		if (_values.size() > x._values.size())
		{
			if (_positive)
			{
				return 1;
			}

			return -1;
		}

		if (_values.size() < x._values.size())
		{
			if (_positive)
			{
				return -1;
			}

			return 1;
		}

		const TBase* it = _values.data() + _values.size() - 1;
		const TBase* itX = x._values.data() + x._values.size() - 1;
		const TBase* const itXEnd = x._values.data() - 1;
		while (itX != itXEnd)
		{
			if (*it != *itX)
			{
				if (*it > *itX)
				{
					return 1;
				}

				return -1;
			}

			--it;
			--itX;
		}

		return 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr void BigInt<TBase, TBuffer>::negate()
	{
		if (!_values.empty())
		{
			_positive = !_positive;
		}
	}

	template<typename TBase, typename TBuffer>
	constexpr std::string BigInt<TBase, TBuffer>::toString() const
	{
		if (_values.empty())
		{
			return "0";
		}

		std::string result;
		BigInt<TBase, TBuffer> x(*this);
		x._positive = true;
		while (!x._values.empty())
		{
			BigInt<TBase, TBuffer> z(x);
			z %= 10;
			if (z._values.empty())
			{
				result.push_back('0');
			}
			else
			{
				result.push_back(static_cast<char>(z._values[0]) + 48);
			}
			x /= 10;
		}

		if (!_positive)
		{
			result.push_back('-');
		}

		std::reverse(result.begin(), result.end());

		return result;
	}

	template<typename TBase, typename TBuffer>
	constexpr int64_t BigInt<TBase, TBuffer>::toInt() const
	{
		assert(*this <= INT64_MAX && *this >= INT64_MIN);

		int64_t x = 0;
		const TBase* it = _values.data() + _values.size() - 1;
		const TBase* const itEnd = _values.data() - 1;
		while (it != itEnd)
		{
			x <<= _baseBitSize;
			x |= *it;
			++it;
		}

		if (_positive)
		{
			return x;
		}
		else
		{
			return -x;
		}
	}

	namespace _scp
	{
		template<typename TBase>
		uint64_t getNbBits(TBase x)
		{
			uint64_t i = 0;
			while (x != 0)
			{
				x >>= 1;
				++i;
			}

			return i;
		}
	}

	template<typename TBase, typename TBuffer>
	constexpr uint64_t BigInt<TBase, TBuffer>::getBitSize() const
	{
		if (_values.empty())
		{
			return 0;
		}

		return (_values.size() - 1) * _baseBitSize + _scp::getNbBits(_values.back());
	}

	template<typename TBase, typename TBuffer>
	constexpr uint64_t BigInt<TBase, TBuffer>::getTrailingZeros() const
	{
		if (_values.empty())
		{
			return 0;
		}

		uint64_t n = 0;
		auto it = _values.cbegin();
		while (*it == 0)
		{
			n += _baseBitSize;
			++it;
		}

		TBase x = 1;
		while ((*it & x) == 0)
		{
			x = (x << 1) | 1;
			++n;
		}

		return n;
	}


	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator+(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z += y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y)
	{
		x += y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y)
	{
		y += x;
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y)
	{
		x += y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator+(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z += BigInt<TBase, TBuffer>(y);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(BigInt<TBase, TBuffer>&& x, int64_t y)
	{
		x += BigInt<TBase, TBuffer>(y);
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(int64_t x, BigInt<TBase, TBuffer>&& y)
	{
		y += BigInt<TBase, TBuffer>(x);
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator+(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(y);
		z += BigInt<TBase, TBuffer>(x);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator-(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z -= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y)
	{
		x -= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y)
	{
		y -= x;
		return -std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y)
	{
		x -= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator-(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z -= BigInt<TBase, TBuffer>(y);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(BigInt<TBase, TBuffer>&& x, int64_t y)
	{
		x -= BigInt<TBase, TBuffer>(y);
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(int64_t x, BigInt<TBase, TBuffer>&& y)
	{
		y -= BigInt<TBase, TBuffer>(x);
		return -std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator-(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(y);
		z -= BigInt<TBase, TBuffer>(x);
		return -z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator*(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z *= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y)
	{
		x *= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y)
	{
		y *= x;
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y)
	{
		x *= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator*(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z *= BigInt<TBase, TBuffer>(y);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(BigInt<TBase, TBuffer>&& x, int64_t y)
	{
		x *= BigInt<TBase, TBuffer>(y);
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(int64_t x, BigInt<TBase, TBuffer>&& y)
	{
		y *= BigInt<TBase, TBuffer>(x);
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator*(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(y);
		z *= BigInt<TBase, TBuffer>(x);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator/(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z /= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator/(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y)
	{
		x /= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator/(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z /= BigInt<TBase, TBuffer>(y);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator/(BigInt<TBase, TBuffer>&& x, int64_t y)
	{
		x /= BigInt<TBase, TBuffer>(y);
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator/(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z /= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator%(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z %= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator%(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y)
	{
		x %= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator%(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z %= BigInt<TBase, TBuffer>(y);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator%(BigInt<TBase, TBuffer>&& x, int64_t y)
	{
		x %= BigInt<TBase, TBuffer>(y);
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator%(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z %= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator+(const BigInt<TBase, TBuffer>& x)
	{
		return x;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(BigInt<TBase, TBuffer>&& x)
	{
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator-(const BigInt<TBase, TBuffer>& x)
	{
		BigInt<TBase, TBuffer> y(x);
		y.negate();
		return y;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(BigInt<TBase, TBuffer>&& x)
	{
		x.negate();
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator&(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z &= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y)
	{
		x &= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y)
	{
		y &= x;
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y)
	{
		x &= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator&(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z &= BigInt<TBase, TBuffer>(y);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(BigInt<TBase, TBuffer>&& x, int64_t y)
	{
		x &= BigInt<TBase, TBuffer>(y);
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(int64_t x, BigInt<TBase, TBuffer>&& y)
	{
		y &= BigInt<TBase, TBuffer>(x);
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator&(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(y);
		y &= BigInt<TBase, TBuffer>(x);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator|(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z |= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y)
	{
		x |= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y)
	{
		y |= x;
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y)
	{
		x |= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator|(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z |= BigInt<TBase, TBuffer>(y);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(BigInt<TBase, TBuffer>&& x, int64_t y)
	{
		x |= BigInt<TBase, TBuffer>(y);
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(int64_t x, BigInt<TBase, TBuffer>&& y)
	{
		y |= BigInt<TBase, TBuffer>(x);
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator|(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(y);
		y |= BigInt<TBase, TBuffer>(x);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator^(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(x);
		z ^= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y)
	{
		x ^= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y)
	{
		y ^= x;
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y)
	{
		x ^= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator^(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z ^= BigInt<TBase, TBuffer>(y);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(BigInt<TBase, TBuffer>&& x, int64_t y)
	{
		x ^= BigInt<TBase, TBuffer>(y);
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(int64_t x, BigInt<TBase, TBuffer>&& y)
	{
		y ^= BigInt<TBase, TBuffer>(x);
		return std::move(y);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator^(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		BigInt<TBase, TBuffer> z(y);
		y ^= BigInt<TBase, TBuffer>(x);
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator<<(const BigInt<TBase, TBuffer>& x, uint64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z <<= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator<<(BigInt<TBase, TBuffer>&& x, uint64_t y)
	{
		x <<= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator>>(const BigInt<TBase, TBuffer>& x, uint64_t y)
	{
		BigInt<TBase, TBuffer> z(x);
		z >>= y;
		return z;
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator>>(BigInt<TBase, TBuffer>&& x, uint64_t y)
	{
		x >>= y;
		return std::move(x);
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator==(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		return x.compare(y) == 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator!=(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		return x.compare(y) != 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator>(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		return x.compare(y) > 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator<(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		return x.compare(y) < 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator>=(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		return x.compare(y) >= 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator<=(const BigInt<TBase, TBuffer>& x, int64_t y)
	{
		return x.compare(y) <= 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator==(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		return y.compare(x) == 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator!=(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		return y.compare(x) != 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator>(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		return y.compare(x) <= 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator<(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		return y.compare(x) >= 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator>=(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		return y.compare(x) < 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr bool operator<=(int64_t x, const BigInt<TBase, TBuffer>& y)
	{
		return y.compare(x) > 0;
	}

	template<typename TBase, typename TBuffer>
	constexpr std::ostream& operator<<(std::ostream& stream, const BigInt<TBase, TBuffer>& x)
	{
		return stream << x.toString();
	}

	template<typename TBase, typename TBuffer>
	constexpr std::istream& operator>>(std::istream& stream, BigInt<TBase, TBuffer>& x)
	{
		x = 0;

		// Get spaces and other delimiter characters

		if (!stream)
		{
			return stream;
		}

		char c;
		stream.get(c);

		while (stream && ((c >= 9 && c <= 13) || c == ' '))
		{
			stream.get(c);
		}

		if (!stream)
		{
			return stream;
		}

		// Get '-' or '+'

		bool neg = false;
		if (c == 45 || c == 43)
		{
			if (c == 45)
			{
				neg = true;
			}
			stream.get(c);
		}

		// Get number itself

		if (!stream || c < 48 || c > 57)
		{
			stream.putback(c);
			if (neg)
			{
				stream.putback('-');
			}
			stream.setstate(std::ios::failbit);
			return stream;
		}

		x = 0;
		while (stream)
		{
			if (c >= 48 && c < 58)
			{
				x = 10 * x + BigInt<TBase, TBuffer>(static_cast<uint64_t>(c) - 48);
			}
			else
			{
				stream.putback(c);
				break;
			}
			stream.get(c);
		}

		if (neg)
		{
			x = -x;
		}

		return stream;
	}
}
