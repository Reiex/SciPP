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
	namespace _scp
	{
		template<typename TBase, typename TPow>
		concept HasStdPow = requires (TBase x, TPow n) { std::pow(x, n); };
	}
	template<typename TBase, typename TPow>
	constexpr TBase pow(const TBase& x, const TPow& n);
	template<typename TBase, _scp::HasStdPow<TBase> TPow>
	constexpr auto pow(const TBase& x, const TPow& n) -> decltype(std::pow(x, n));

	template<typename TValue>
	constexpr TValue fact(const TValue& n);

	template<typename TValue>
	constexpr TValue gcd(const TValue& a, const TValue& b);
	template<std::integral TIntegralA, std::integral TIntegralB>
	constexpr std::common_type_t<TIntegralA, TIntegralB> gcd(const TIntegralA& a, const TIntegralB& b);
	template<std::integral TIntegral>
	constexpr TIntegral gcd(const TIntegral& a, const TIntegral& b);
	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> gcd(const BigInt<TBase, TBuffer>& a, const BigInt<TBase, TBuffer>& b);

	template<typename TValue>
	constexpr TValue lcm(const TValue& a, const TValue& b);
	template<std::integral TIntegralA, std::integral TIntegralB>
	constexpr std::common_type_t<TIntegralA, TIntegralB> lcm(const TIntegralA& a, const TIntegralB& b);
	template<std::integral TIntegral>
	constexpr TIntegral lcm(const TIntegral& a, const TIntegral& b);

	template<typename T>
	constexpr T binom(const T& n, const T& p);

	template<typename T>
	constexpr bool isPrime(const T& n);

	template<typename T>
	constexpr void primeFactors(T n, std::vector<std::pair<T, uint64_t>>& factors);

	template<typename T>
	constexpr std::vector<T> divisors(const T& n);
}
