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
	template<typename TBase, typename TPow>
	constexpr TBase pow(const TBase& x, const TPow& n)
	{
		if (n < 0)
		{
			throw std::runtime_error("Cannot call pow with n < 0.");
		}

		if (n == 0)
		{
			return 1;
		}

		if (n == 1)
		{
			return x;
		}

		TPow k(n - 1);
		TBase r(x), p(x);

		while (k != 0)
		{
			if (k % 2 == 0)
			{
				p *= p;
				k >>= 1;
			}
			else
			{
				r *= p;
				--k;
			}
		}

		return r;
	}

	template<typename TBase, _scp::HasStdPow<TBase> TPow>
	constexpr auto pow(const TBase& x, const TPow& n) -> decltype(std::pow(x, n))
	{
		return std::pow(x, n);
	}
	
	template<typename TValue>
	constexpr TValue fact(const TValue& n)
	{
		if (n == 0)
		{
			return 1;
		}

		return n * fact(n - 1);
	}

	template<typename TValue>
	constexpr TValue gcd(const TValue& a, const TValue& b)
	{
		if (a == 0)
		{
			return b;
		}

		if (b == 0)
		{
			return a;
		}

		TValue u(a), v(b), r(u % v);

		while (r != 0)
		{
			u = v;
			v = r;
			r = u % v;
		}

		if (v < 0)
		{
			return -v;
		}
		
		return v;
	}

	template<std::integral TIntegralA, std::integral TIntegralB>
	constexpr std::common_type_t<TIntegralA, TIntegralB> gcd(const TIntegralA& a, const TIntegralB& b)
	{
		return std::gcd(a, b);
	}

	template<std::integral TIntegral>
	constexpr TIntegral gcd(const TIntegral& a, const TIntegral& b)
	{
		return std::gcd(a, b);
	}

	template<typename TBase, typename TBuffer>
	constexpr BigInt<TBase, TBuffer> gcd(const BigInt<TBase, TBuffer>& a, const BigInt<TBase, TBuffer>& b)
	{
		if (a == 0)
		{
			return b;
		}
		else if (b == 0)
		{
			return a;
		}

		BigInt<TBase, TBuffer> u = a, v = b;
		uint64_t i = u.getTrailingZeros();
		u >>= i;
		uint64_t j = v.getTrailingZeros();
		v >>= j;
		uint64_t k = std::min(i, j);

		while (true)
		{
			if (u > v)
			{
				u -= v;
				if (u == 0)
				{
					return v << k;
				}
				u >>= u.getTrailingZeros();
			}
			else
			{
				v -= u;
				if (v == 0)
				{
					return u << k;
				}
				v >>= v.getTrailingZeros();
			}
		}
	}

	template<typename TValue>
	constexpr TValue lcm(const TValue& a, const TValue& b)
	{
		TValue r((a * b) / gcd(a, b));

		if (r < 0)
		{
			return -r;
		}

		return r;
	}

	template<std::integral TIntegralA, std::integral TIntegralB>
	constexpr std::common_type_t<TIntegralA, TIntegralB> lcm(const TIntegralA& a, const TIntegralB& b)
	{
		return std::lcm(a, b);
	}

	template<std::integral TIntegral>
	constexpr TIntegral lcm(const TIntegral& a, const TIntegral& b)
	{
		return std::lcm(a, b);
	}

	template<typename T>
	constexpr T binom(const T& n, const T& p)
	{
		if (p > n || p < 0)
		{
			return 0;
		}

		T num = 1, denom = 1;

		for (T i = 0; i < p; ++i)
		{
			num *= n - i;
			denom *= p - i;
		}

		return num / denom;
	}

	template<typename T>
	constexpr bool isPrime(const T& n)
	{
		if (n <= 2)
		{
			return n == 2;
		}

		for (T i = 3; i * i <= n; i += 2)
		{
			if (n % i == 0)
			{
				return false;
			}
		}

		return true;
	}

	template<typename T>
	constexpr void primeFactors(T n, std::vector<std::pair<T, uint64_t>>& factors)
	{
		factors.clear();

		uint64_t j = 0;
		while (n % 2 == 0)
		{
			++j;
			n >>= 1;
		}

		if (j != 0)
		{
			factors.push_back({ 2, j });
		}

		for (T i = 3; i * i <= n; i += 2)
		{
			j = 0;
			while (n % i == 0)
			{
				++j;
				n /= i;
			}

			if (j != 0)
			{
				factors.push_back({ i, j });
			}
		}

		if (n != 1)
		{
			factors.push_back({ n, 1 });
		}
	}

	template<typename T>
	constexpr std::vector<T> divisors(const T& n)
	{
		if (n == 0)
		{
			return {};
		}

		T copy(n);
		if constexpr (std::is_signed<T>::value)
		{
			if (copy < 0)
			{
				copy = -copy;
			}
		}

		if (copy == 1)
		{
			return { 1 };
		}

		std::vector<T> divisors;
		for (T i = 1; i*i <= copy; ++i)
		{
			if (copy % i == 0)
			{
				divisors.push_back(i);
			}
		}

		int64_t i = divisors.size() - 1;
		if (divisors.back() * divisors.back() == copy)
		{
			--i;
		}

		for (; i >= 0; --i)
		{
			divisors.push_back(copy / divisors[i]);
		}

		return divisors;
	}
}
