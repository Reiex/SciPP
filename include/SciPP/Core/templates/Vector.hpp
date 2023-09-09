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
	constexpr Vector<TValue>* Vector<TValue>::createAroundMemory(uint64_t size, TValue* memory)
	{
		assert(size != 0);
		assert(memory);

		Vector<TValue>* vector = new Vector<TValue>();

		vector->_shape.order = 1;
		vector->_length = size;
		vector->_shape.sizes = new uint64_t[1];
		vector->_values = memory;
		vector->_owner = false;

		vector->_shape.sizes[0] = size;

		return vector;
	}

	template<typename TValue>
	constexpr Vector<TValue>::Vector(uint64_t size) : Tensor<TValue>(1, &size)
	{
	}

	template<typename TValue>
	constexpr Vector<TValue>::Vector(uint64_t size, const TValue& value) : Tensor<TValue>(1, &size, value)
	{
	}

	template<typename TValue>
	constexpr Vector<TValue>::Vector(uint64_t size, const TValue* values) : Tensor<TValue>(1, &size, values)
	{
	}

	template<typename TValue>
	constexpr Vector<TValue>::Vector(const std::initializer_list<TValue>& values) : Tensor<TValue>(1, values.size(), values.begin())
	{
	}

	template<typename TValue>
	constexpr Vector<TValue>::Vector(const Vector<TValue>& vector) : Tensor<TValue>(vector)
	{
	}

	template<typename TValue>
	constexpr Vector<TValue>::Vector(Vector<TValue>&& vector) : Tensor<TValue>(dynamic_cast<Tensor<TValue>&&>(vector))
	{
	}

	template<typename TValue>
	constexpr void Vector<TValue>::rightMatrixProduct(const Tensor<TValue>& vector, const Tensor<TValue>& matrix)
	{
		assert(vector._shape.order == 1);
		assert(matrix._shape.order == 2);
		assert(matrix._shape.sizes[0] == vector._shape.sizes[0]);
		assert(matrix._shape.sizes[1] == _shape.sizes[0]);

		std::fill_n(_values, _length, 0);

		TValue* values = _values;
		const TValue* vectorValues = vector._values;
		const TValue* matrixValues = matrix._values;

		const TValue* const valuesEnd = values + _length;
		const TValue* const vectorValuesEnd = vectorValues + vector._length;
		
		for (; vectorValues != vectorValuesEnd; ++vectorValues)
		{
			for (; values != valuesEnd; ++values, ++matrixValues)
			{
				*values += (*vectorValues) * (*matrixValues);
			}

			values -= _length;
		}
	}

	template<typename TValue>
	constexpr void Vector<TValue>::leftMatrixProduct(const Tensor<TValue>& matrix, const Tensor<TValue>& vector)
	{
		assert(vector._shape.order == 1);
		assert(matrix._shape.order == 2);
		assert(matrix._shape.sizes[0] == _shape.sizes[0]);
		assert(matrix._shape.sizes[1] == vector._shape.sizes[0]);

		TValue* values = _values;
		const TValue* vectorValues = vector._values;
		const TValue* matrixValues = matrix._values;

		const TValue* const valuesEnd = values + _length;
		const TValue* const vectorValuesEnd = vectorValues + vector._length;

		for (; values != valuesEnd; ++values)
		{
			*values = 0;

			for (; vectorValues != vectorValuesEnd; ++vectorValues, ++matrixValues)
			{
				*values += (*vectorValues) * (*matrixValues);
			}

			vectorValues -= vector._length;
		}
	}


	template<typename TValue>
	constexpr Vector<TValue> operator+(const Vector<TValue>& vectorA, const Vector<TValue>& vectorB)
	{
		Vector<TValue> vectorC(vectorA);
		vectorC += vectorB;
		return vectorC;
	}

	template<typename TValue>
	constexpr Vector<TValue>&& operator+(Vector<TValue>&& vectorA, const Vector<TValue>& vectorB)
	{
		vectorA += vectorB;
		return std::forward(vectorA);
	}

	template<typename TValue>
	constexpr Vector<TValue>&& operator+(const Vector<TValue>& vectorA, Vector<TValue>&& vectorB)
	{
		vectorB += vectorA;
		return std::forward(vectorB);
	}

	template<typename TValue>
	constexpr Vector<TValue>&& operator+(Vector<TValue>&& vectorA, Vector<TValue>&& vectorB)
	{
		vectorA += vectorB;
		return std::forward(vectorA);
	}

	template<typename TValue>
	constexpr Vector<TValue> operator-(const Vector<TValue>& vectorA, const Vector<TValue>& vectorB)
	{
		Vector<TValue> vectorC(vectorA);
		vectorC -= vectorB;
		return vectorC;
	}

	template<typename TValue>
	constexpr Vector<TValue>&& operator-(Vector<TValue>&& vectorA, const Vector<TValue>& vectorB)
	{
		vectorA -= vectorB;
		return std::forward(vectorA);
	}

	template<typename TValue>
	constexpr Vector<TValue>&& operator-(const Vector<TValue>& vectorA, Vector<TValue>&& vectorB)
	{
		vectorB -= vectorA;
		vectorB.negate();
		return std::forward(vectorB);
	}

	template<typename TValue>
	constexpr Vector<TValue>&& operator-(Vector<TValue>&& vectorA, Vector<TValue>&& vectorB)
	{
		vectorA -= vectorB;
		return std::forward(vectorA);
	}

	template<typename TValue, typename TScalar>
	constexpr Vector<TValue> operator*(const Vector<TValue>& vector, const TScalar& scalar)
	{
		Vector<TValue> copy(vector);
		copy *= scalar;
		return copy;
	}

	template<typename TValue, typename TScalar>
	constexpr Vector<TValue>&& operator*(Vector<TValue>&& vector, const TScalar& scalar)
	{
		vector *= scalar;
		return std::forward(vector);
	}

	template<typename TValue, typename TScalar>
	constexpr Vector<TValue> operator*(const TScalar& scalar, const Vector<TValue>& vector)
	{
		Vector<TValue> copy(vector);
		copy *= scalar;
		return copy;
	}

	template<typename TValue, typename TScalar>
	constexpr Vector<TValue>&& operator*(const TScalar& scalar, Vector<TValue>&& vector)
	{
		vector *= scalar;
		return std::forward(vector);
	}

	template<typename TValue, typename TScalar>
	constexpr Vector<TValue> operator/(const Vector<TValue>& vector, const TScalar& scalar)
	{
		Vector<TValue> copy(vector);
		copy /= scalar;
		return copy;
	}

	template<typename TValue, typename TScalar>
	constexpr Vector<TValue>&& operator/(Vector<TValue>&& vector, const TScalar& scalar)
	{
		vector /= scalar;
		return std::forward(vector);
	}

	template<typename TValue>
	constexpr Vector<TValue> operator-(const Vector<TValue>& vector)
	{
		Vector<TValue> copy(vector);
		copy.negate();
		return copy;
	}

	template<typename TValue>
	constexpr Vector<TValue>&& operator-(Vector<TValue>&& vector)
	{
		vector.negate();
		return std::forward(vector);
	}

	template<typename TValue>
	constexpr Vector<TValue> operator+(const Vector<TValue>& vector)
	{
		return vector;
	}

	template<typename TValue>
	constexpr Vector<TValue>&& operator+(Vector<TValue>&& vector)
	{
		return std::forward(vector);
	}

	template<typename TValue>
	Vector<TValue> operator*(const Vector<TValue>& vector, const Matrix<TValue>& matrix)
	{
		Vector<TValue> result(matrix.getSize(1));
		result.rightMatrixProduct(vector, matrix);
		return result;
	}

	template<typename TValue>
	Vector<TValue> operator*(const Matrix<TValue>& matrix, const Vector<TValue>& vector)
	{
		Vector<TValue> result(matrix.getSize(0));
		result.leftMatrixProduct(matrix, vector);
		return result;
	}
}
