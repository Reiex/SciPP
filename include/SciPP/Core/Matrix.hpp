///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Pélégrin Marius
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>

namespace scp
{
	template<typename TValue>
	class Matrix : public Tensor<TValue>
	{
		public:

			static constexpr Matrix<TValue>* createAroundMemory(uint64_t row, uint64_t col, TValue* memory);

			constexpr Matrix(uint64_t row, uint64_t col);
			constexpr Matrix(uint64_t row, uint64_t col, const TValue& value);
			constexpr Matrix(uint64_t row, uint64_t col, const TValue* values);
			constexpr Matrix(uint64_t row, uint64_t col, const std::initializer_list<TValue>& values);
			constexpr Matrix(const Matrix<TValue>& matrix);
			constexpr Matrix(Matrix<TValue>&& matrix);

			constexpr Matrix<TValue>& operator=(const Matrix<TValue>& matrix) = default;
			constexpr Matrix<TValue>& operator=(Matrix<TValue>&& matrix) = default;

			constexpr void matrixProduct(const Tensor<TValue>& matrixA, const Tensor<TValue>& matrixB);
			
			constexpr void transpose();
			
			constexpr void inverse();
			// TODO: cholesky, LDL, LU, QR, Polar, etc....

			constexpr TValue determinant() const;

			constexpr ~Matrix() = default;

		private:

			constexpr Matrix() = default;

			using Tensor<TValue>::_zero;
			using Tensor<TValue>::_one;

			using Tensor<TValue>::_shape;
			using Tensor<TValue>::_length;
			using Tensor<TValue>::_values;
			using Tensor<TValue>::_owner;
	};

	template<typename TValue>
	constexpr Matrix<TValue> operator+(const Matrix<TValue>& matrixA, const Matrix<TValue>& matrixB);
	template<typename TValue>
	constexpr Matrix<TValue>&& operator+(Matrix<TValue>&& matrixA, const Matrix<TValue>& matrixB);
	template<typename TValue>
	constexpr Matrix<TValue>&& operator+(const Matrix<TValue>& matrixA, Matrix<TValue>&& matrixB);
	template<typename TValue>
	constexpr Matrix<TValue>&& operator+(Matrix<TValue>&& matrixA, Matrix<TValue>&& matrixB);
	
	template<typename TValue>
	constexpr Matrix<TValue> operator-(const Matrix<TValue>& matrixA, const Matrix<TValue>& matrixB);
	template<typename TValue>
	constexpr Matrix<TValue>&& operator-(Matrix<TValue>&& matrixA, const Matrix<TValue>& matrixB);
	template<typename TValue>
	constexpr Matrix<TValue>&& operator-(const Matrix<TValue>& matrixA, Matrix<TValue>&& matrixB);
	template<typename TValue>
	constexpr Matrix<TValue>&& operator-(Matrix<TValue>&& matrixA, Matrix<TValue>&& matrixB);
	
	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue> operator*(const Matrix<TValue>& matrix, const TScalar& scalar);
	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue>&& operator*(Matrix<TValue>&& matrix, const TScalar& scalar);
	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue> operator*(const TScalar& scalar, const Matrix<TValue>& matrix);
	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue>&& operator*(const TScalar& scalar, Matrix<TValue>&& matrix);
	
	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue> operator/(const Matrix<TValue>& matrix, const TScalar& scalar);
	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue>&& operator/(Matrix<TValue>&& matrix, const TScalar& scalar);
	
	template<typename TValue>
	constexpr Matrix<TValue> operator-(const Matrix<TValue>& matrix);
	template<typename TValue>
	constexpr Matrix<TValue>&& operator-(Matrix<TValue>&& matrix);
	
	template<typename TValue>
	constexpr Matrix<TValue> operator+(const Matrix<TValue>& matrix);
	template<typename TValue>
	constexpr Matrix<TValue>&& operator+(Matrix<TValue>&& matrix);
	
	template<typename TValue>
	Matrix<TValue> operator*(const Matrix<TValue>& matrixA, const Matrix<TValue>& matrixB);
}
