///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Marius Pélégrin
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>

namespace scp
{
	template<typename TValue>
	class Vector : public Tensor<TValue>
	{
		public:

			static constexpr Vector<TValue>* createAroundMemory(uint64_t size, TValue* memory);

			constexpr Vector(uint64_t size);
			constexpr Vector(uint64_t size, const TValue& value);
			constexpr Vector(uint64_t size, const TValue* values);
			constexpr Vector(const std::initializer_list<TValue>& values);
			constexpr Vector(const Vector<TValue>& vector);
			constexpr Vector(Vector<TValue>&& vector);

			constexpr Vector<TValue>& operator=(const Vector<TValue>& vector) = default;
			constexpr Vector<TValue>& operator=(Vector<TValue>&& vector) = default;

			constexpr void rightMatrixProduct(const Tensor<TValue>& vector, const Tensor<TValue>& matrix);
			constexpr void leftMatrixProduct(const Tensor<TValue>& matrix, const Tensor<TValue>& vector);

			constexpr ~Vector() = default;

		private:

			constexpr Vector() = default;

			using Tensor<TValue>::_zero;
			using Tensor<TValue>::_one;

			using Tensor<TValue>::_shape;
			using Tensor<TValue>::_length;
			using Tensor<TValue>::_values;
			using Tensor<TValue>::_owner;
	};

	template<typename TValue>
	constexpr Vector<TValue> operator+(const Vector<TValue>& vectorA, const Vector<TValue>& vectorB);
	template<typename TValue>
	constexpr Vector<TValue>&& operator+(Vector<TValue>&& vectorA, const Vector<TValue>& vectorB);
	template<typename TValue>
	constexpr Vector<TValue>&& operator+(const Vector<TValue>& vectorA, Vector<TValue>&& vectorB);
	template<typename TValue>
	constexpr Vector<TValue>&& operator+(Vector<TValue>&& vectorA, Vector<TValue>&& vectorB);

	template<typename TValue>
	constexpr Vector<TValue> operator-(const Vector<TValue>& vectorA, const Vector<TValue>& vectorB);
	template<typename TValue>
	constexpr Vector<TValue>&& operator-(Vector<TValue>&& vectorA, const Vector<TValue>& vectorB);
	template<typename TValue>
	constexpr Vector<TValue>&& operator-(const Vector<TValue>& vectorA, Vector<TValue>&& vectorB);
	template<typename TValue>
	constexpr Vector<TValue>&& operator-(Vector<TValue>&& vectorA, Vector<TValue>&& vectorB);

	template<typename TValue, typename TScalar>
	constexpr Vector<TValue> operator*(const Vector<TValue>& vector, const TScalar& scalar);
	template<typename TValue, typename TScalar>
	constexpr Vector<TValue>&& operator*(Vector<TValue>&& vector, const TScalar& scalar);
	template<typename TValue, typename TScalar>
	constexpr Vector<TValue> operator*(const TScalar& scalar, const Vector<TValue>& vector);
	template<typename TValue, typename TScalar>
	constexpr Vector<TValue>&& operator*(const TScalar& scalar, Vector<TValue>&& vector);

	template<typename TValue, typename TScalar>
	constexpr Vector<TValue> operator/(const Vector<TValue>& vector, const TScalar& scalar);
	template<typename TValue, typename TScalar>
	constexpr Vector<TValue>&& operator/(Vector<TValue>&& vector, const TScalar& scalar);

	template<typename TValue>
	constexpr Vector<TValue> operator-(const Vector<TValue>& vector);
	template<typename TValue>
	constexpr Vector<TValue>&& operator-(Vector<TValue>&& vector);

	template<typename TValue>
	constexpr Vector<TValue> operator+(const Vector<TValue>& vector);
	template<typename TValue>
	constexpr Vector<TValue>&& operator+(Vector<TValue>&& vector);

	template<typename TValue>
	Vector<TValue> operator*(const Vector<TValue>& vector, const Matrix<TValue>& matrix);
	template<typename TValue>
	Vector<TValue> operator*(const Matrix<TValue>& matrix, const Vector<TValue>& vector);
}
