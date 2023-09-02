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
	template<typename TBase = uint32_t, typename TBuffer = uint64_t>
	class BigInt
	{
		public:

			constexpr BigInt();
			constexpr BigInt(int64_t x);
			constexpr BigInt(const std::string& str);
			constexpr BigInt(const BigInt<TBase, TBuffer>& x) = default;
			constexpr BigInt(BigInt<TBase, TBuffer>&& x) = default;

			constexpr BigInt<TBase, TBuffer>& operator=(const BigInt<TBase, TBuffer>& x) = default;
			constexpr BigInt<TBase, TBuffer>& operator=(BigInt<TBase, TBuffer>&& x) = default;

			constexpr BigInt<TBase, TBuffer>& operator+=(const BigInt<TBase, TBuffer>& x);
			constexpr BigInt<TBase, TBuffer>& operator-=(const BigInt<TBase, TBuffer>& x);
			constexpr BigInt<TBase, TBuffer>& operator*=(const BigInt<TBase, TBuffer>& x);
			constexpr BigInt<TBase, TBuffer>& operator/=(const BigInt<TBase, TBuffer>& x);
			constexpr BigInt<TBase, TBuffer>& operator%=(const BigInt<TBase, TBuffer>& x);

			constexpr BigInt<TBase, TBuffer>& operator&=(const BigInt<TBase, TBuffer>& x);
			constexpr BigInt<TBase, TBuffer>& operator|=(const BigInt<TBase, TBuffer>& x);
			constexpr BigInt<TBase, TBuffer>& operator^=(const BigInt<TBase, TBuffer>& x);
			constexpr BigInt<TBase, TBuffer>& operator<<=(uint64_t x);
			constexpr BigInt<TBase, TBuffer>& operator>>=(uint64_t x);

			constexpr BigInt<TBase, TBuffer>& operator++();
			constexpr BigInt<TBase, TBuffer> operator++(int);
			constexpr BigInt<TBase, TBuffer>& operator--();
			constexpr BigInt<TBase, TBuffer> operator--(int);

			constexpr bool operator==(const BigInt<TBase, TBuffer>& x) const;
			constexpr bool operator!=(const BigInt<TBase, TBuffer>& x) const;
			constexpr bool operator<(const BigInt<TBase, TBuffer>& x) const;
			constexpr bool operator>(const BigInt<TBase, TBuffer>& x) const;
			constexpr bool operator<=(const BigInt<TBase, TBuffer>& x) const;
			constexpr bool operator>=(const BigInt<TBase, TBuffer>& x) const;

			constexpr int8_t compare(const BigInt<TBase, TBuffer>& x) const;
			constexpr void negate();

			constexpr std::string toString() const;
			constexpr int64_t toInt() const;

			constexpr uint64_t getBitSize() const;
			constexpr uint64_t getTrailingZeros() const;

			constexpr ~BigInt() = default;

		private:

			static constexpr TBuffer _baseBitSize = sizeof(TBase) * CHAR_BIT;
			static constexpr TBuffer _baseEnd = TBuffer(1) << _baseBitSize;
			static constexpr TBuffer _baseMax = _baseEnd - 1;
			static constexpr TBuffer _bufferLowFilter = _baseMax;
			static constexpr TBuffer _bufferHighFilter = ~_bufferLowFilter;

			std::vector<TBase> _values;
			bool _positive;

			template<typename TBase, typename TBuffer> friend constexpr std::ostream& operator<<(std::ostream& stream, const BigInt<TBase, TBuffer>& x);
			template<typename TBase, typename TBuffer> friend constexpr std::istream& operator>>(std::istream& stream, BigInt<TBase, TBuffer>& x);
	};

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator+(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator+(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(BigInt<TBase, TBuffer>&& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(int64_t x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator+(int64_t x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator-(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator-(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(BigInt<TBase, TBuffer>&& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(int64_t x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator-(int64_t x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator*(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator*(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(BigInt<TBase, TBuffer>&& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator*(int64_t x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator*(int64_t x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator/(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator/(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator/(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator/(BigInt<TBase, TBuffer>&& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator/(int64_t x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator%(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator%(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator%(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator%(BigInt<TBase, TBuffer>&& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator%(int64_t x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator+(const BigInt<TBase, TBuffer>& x);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator+(BigInt<TBase, TBuffer>&& x);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator-(const BigInt<TBase, TBuffer>& x);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator-(BigInt<TBase, TBuffer>&& x);


	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator&(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator&(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(BigInt<TBase, TBuffer>&& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator&(int64_t x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator&(int64_t x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator|(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator|(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(BigInt<TBase, TBuffer>&& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator|(int64_t x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator|(int64_t x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator^(const BigInt<TBase, TBuffer>& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(BigInt<TBase, TBuffer>&& x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(const BigInt<TBase, TBuffer>& x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(BigInt<TBase, TBuffer>&& x, BigInt<TBase, TBuffer>&& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator^(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(BigInt<TBase, TBuffer>&& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator^(int64_t x, BigInt<TBase, TBuffer>&& y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator^(int64_t x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator<<(const BigInt<TBase, TBuffer>& x, uint64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator<<(BigInt<TBase, TBuffer>&& x, uint64_t y);

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> operator>>(const BigInt<TBase, TBuffer>& x, uint64_t y);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer>&& operator>>(BigInt<TBase, TBuffer>&& x, uint64_t y);

	template<typename TBase, typename TBuffer>
	constexpr bool operator==(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator!=(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator>(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator<(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator>=(const BigInt<TBase, TBuffer>& x, int64_t y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator<=(const BigInt<TBase, TBuffer>& x, int64_t y);

	template<typename TBase, typename TBuffer>
	constexpr bool operator==(int64_t x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator!=(int64_t x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator>(int64_t x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator<(int64_t x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator>=(int64_t x, const BigInt<TBase, TBuffer>& y);
	template<typename TBase, typename TBuffer>
	constexpr bool operator<=(int64_t x, const BigInt<TBase, TBuffer>& y);

	template<typename TBase, typename TBuffer>
	constexpr std::ostream& operator<<(std::ostream& stream, const BigInt<TBase, TBuffer>& x);
	template<typename TBase, typename TBuffer>
	constexpr std::istream& operator>>(std::istream& stream, BigInt<TBase, TBuffer>& x);
}
