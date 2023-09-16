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
	constexpr Matrix<TValue>* Matrix<TValue>::createAroundMemory(uint64_t row, uint64_t col, TValue* memory)
	{
		assert(row != 0 && col != 0);
		assert(memory);

		Matrix<TValue>* matrix = new Matrix<TValue>();

		matrix->_shape.order = 2;
		matrix->_length = row * col;
		matrix->_shape.sizes = new uint64_t[2];
		matrix->_values = memory;
		matrix->_owner = false;

		matrix->_shape.sizes[0] = row;
		matrix->_shape.sizes[1] = col;

		return matrix;
	}

	template<typename TValue>
	constexpr Matrix<TValue>::Matrix(uint64_t row, uint64_t col) : Tensor<TValue>({ row, col })
	{
	}

	template<typename TValue>
	constexpr Matrix<TValue>::Matrix(uint64_t row, uint64_t col, const TValue& value) : Tensor<TValue>({ row, col }, value)
	{
	}

	template<typename TValue>
	constexpr Matrix<TValue>::Matrix(uint64_t row, uint64_t col, const TValue* values) : Tensor<TValue>({ row, col }, values)
	{
	}

	template<typename TValue>
	constexpr Matrix<TValue>::Matrix(uint64_t row, uint64_t col, const std::initializer_list<TValue>& values) : Tensor<TValue>({ row, col }, values)
	{
	}

	template<typename TValue>
	constexpr Matrix<TValue>::Matrix(const Matrix<TValue>& matrix) : Tensor<TValue>(matrix)
	{
	}

	template<typename TValue>
	constexpr Matrix<TValue>::Matrix(Matrix<TValue>&& matrix) : Tensor<TValue>(dynamic_cast<Tensor<TValue>&&>(matrix))
	{
	}

	template<typename TValue>
	constexpr void Matrix<TValue>::matrixProduct(const Tensor<TValue>& matrixA, const Tensor<TValue>& matrixB)
	{
		assert(matrixA._shape.order == 2);
		assert(matrixB._shape.order == 2);
		assert(matrixA._shape.sizes[1] == matrixB._shape.sizes[0]);
		assert(matrixA._shape.sizes[0] == _shape.sizes[0]);
		assert(matrixB._shape.sizes[1] == _shape.sizes[1]);

		const uint64_t& size = matrixB._shape.sizes[0];

		TValue* values = _values;
		const TValue* valuesA = matrixA._values;
		const TValue* valuesB = matrixB._values;

		for (uint64_t i = 0; i < _shape.sizes[0]; ++i)
		{
			for (uint64_t j = 0; j < _shape.sizes[1]; ++j, ++values)
			{
				*values = 0;

				for (uint64_t k = 0; k < size; ++k, ++valuesA, valuesB += _shape.sizes[1])
				{
					*values += (*valuesA) * (*valuesB);
				}

				valuesA -= size;
				valuesB -= matrixB._length - 1;
			}

			valuesA += size;
			valuesB -= _shape.sizes[1];
		}
	}

	template<typename TValue>
	constexpr void Matrix<TValue>::transpose()
	{
		if (_shape.sizes[0] == _shape.sizes[1])
		{
			const uint64_t& size = _shape.sizes[0];

			TValue* itA = _values;
			TValue* itB = _values;

			for (uint64_t j = 0; j < size; ++j)
			{
				itA += j + 1;
				itB += (j + 1) * size;

				for (uint64_t i = j + 1; i < size; ++i, ++itA, itB += size)
				{
					std::swap(*itA, *itB);
				}

				itB -= _length - 1;
			}
		}
		else
		{
			bool* visited = new bool[_length];
			std::fill_n(visited, _length, false);
			visited[0] = true;
			visited[_length - 1] = true;

			uint64_t n = 0;
			uint64_t i, j;
			TValue tmp;
			while (n != _length)
			{
				if (visited[n])
				{
					++n;
					continue;
				}

				tmp = _values[n];
				visited[n] = true;

				i = n;
				j = (i % _shape.sizes[0]) * _shape.sizes[1] + i / _shape.sizes[0];

				while (j != n)
				{
					_values[i] = _values[j];
					visited[j] = true;

					i = j;
					j = (i % _shape.sizes[0]) * _shape.sizes[1] + i / _shape.sizes[0];
				}

				_values[i] = tmp;
			}

			std::swap(_shape.sizes[0], _shape.sizes[1]);

			delete[] visited;
		}
	}

	template<typename TValue>
	constexpr void Matrix<TValue>::inverse()
	{
		assert(_shape.sizes[0] == _shape.sizes[1]);

		const uint64_t size = _shape.sizes[0];
		Matrix<TValue> copy(*this);

		TValue* it = nullptr;
		TValue* copyIt = nullptr;
		TValue* otherIt = nullptr;
		TValue* copyOtherIt = nullptr;
		const TValue* itEnd = nullptr;
		const TValue* copyItEnd = nullptr;
		const TValue* otherItEnd = nullptr;
		const TValue* copyOtherItEnd = nullptr;

		std::fill_n(_values, _length, _zero);

		it = _values;
		itEnd = it + _length + size;
		for (; it != itEnd; it += size + 1)
		{
			*it = _one;
		}

		it = _values;
		itEnd = it + size;
		copyIt = copy._values;
		copyItEnd = copyIt + size;
		for (uint64_t j = 0; j < size; ++j, it += size + 1, itEnd += size, copyIt += size + 1, copyItEnd += size)
		{
			const TValue pivot = *copyIt;

			if (pivot == _zero)
			{
				otherIt = it + size;
				otherItEnd = itEnd + size;
				copyOtherIt = copyIt + size;
				copyOtherItEnd = copyItEnd + size;
				for (uint64_t i = j + 1; i < size; ++i, otherIt += size, otherItEnd += size, copyOtherIt += size, copyOtherItEnd += size)
				{
					const TValue value = *copyOtherIt;
					if (value != _zero)
					{
						std::transform<const TValue*>(it, itEnd, otherIt, it, [&](const TValue& x, const TValue& y) { return x + y / value; });
						std::transform<const TValue*>(copyIt, copyItEnd, copyOtherIt, copyIt, [&](const TValue& x, const TValue& y) { return x + y / value; });

						break;
					}
				}

				if (*copyIt == _zero)
				{
					throw std::runtime_error("The matrix cannot be inverted.");
				}
			}
			else if (pivot != _one)
			{
				std::transform<const TValue*>(it, itEnd, it, [&](const TValue& x) { return x / pivot; });
				std::transform<const TValue*>(copyIt, copyItEnd, copyIt, [&](const TValue& x) { return x / pivot; });
			}

			otherIt = it + size;
			otherItEnd = itEnd + size;
			copyOtherIt = copyIt + size;
			copyOtherItEnd = copyItEnd + size;
			for (uint64_t i = j + 1; i < size; ++i, otherIt += size, otherItEnd += size, copyOtherIt += size, copyOtherItEnd += size)
			{
				const TValue value = *copyOtherIt;
				if (value != _zero)
				{
					std::transform<const TValue*>(otherIt, otherItEnd, it, otherIt, [&](const TValue& x, const TValue& y) { return x - y * value; });
					std::transform<const TValue*>(copyOtherIt, copyOtherItEnd, copyIt, copyOtherIt, [&](const TValue& x, const TValue& y) { return x - y * value; });
				}
			}
		}

		it = _values + (size - 1) * size;
		itEnd = it + size;
		copyIt = copy._values + (size - 1) * size;
		copyItEnd = copyIt + size;
		for (uint64_t j = size - 1; j != UINT64_MAX; --j, it -= size, itEnd -= size, copyIt -= size, copyItEnd -= size)
		{
			otherIt = it - size;
			otherItEnd = it;
			copyOtherIt = copyIt - size;
			copyOtherItEnd = copyIt;
			for (uint64_t i = j - 1; i != UINT64_MAX; --i, otherIt -= size, otherItEnd -= size, copyOtherIt -= size, copyOtherItEnd -= size)
			{
				const TValue value = *(copyOtherIt + j);
				if (value != _zero)
				{
					std::transform<const TValue*>(otherIt, otherItEnd, it, otherIt, [&](const TValue& x, const TValue& y) { return x - y * value; });
					std::transform<const TValue*>(copyOtherIt, copyOtherItEnd, copyIt, copyOtherIt, [&](const TValue& x, const TValue& y) { return x - y * value; });
				}
			}
		}
	}

	template<typename TValue>
	constexpr TValue Matrix<TValue>::determinant() const
	{
		assert(_shape.sizes[0] == _shape.sizes[1]);

		TValue det = _one;

		const uint64_t size = _shape.sizes[0];
		Matrix<TValue> copy(*this);

		TValue* it = nullptr;
		TValue* otherIt = nullptr;
		const TValue* itEnd = nullptr;
		const TValue* otherItEnd = nullptr;

		it = copy._values;
		itEnd = it + size;
		for (uint64_t j = 0; j < size; ++j, it += size + 1, itEnd += size)
		{
			const TValue pivot = *it;

			if (pivot == _zero)
			{
				otherIt = it + size;
				otherItEnd = itEnd + size;
				for (uint64_t i = j + 1; i < size; ++i, otherIt += size, otherItEnd += size)
				{
					const TValue value = *otherIt;
					if (value != _zero)
					{
						std::transform<const TValue*>(it, itEnd, otherIt, it, [&](const TValue& x, const TValue& y) { return x + y / value; });
						break;
					}
				}

				if (*it == _zero)
				{
					return _zero;
				}
			}
			else if (pivot != _one)
			{
				det /= pivot;
				std::transform<const TValue*>(it, itEnd, it, [&](const TValue& x) { return x / pivot; });
			}

			otherIt = it + size;
			otherItEnd = itEnd + size;
			for (uint64_t i = j + 1; i < size; ++i, otherIt += size, otherItEnd += size)
			{
				const TValue value = *otherIt;
				if (value != _zero)
				{
					std::transform<const TValue*>(otherIt, otherItEnd, it, otherIt, [&](const TValue& x, const TValue& y) { return x - y * value; });
				}
			}
		}

		it = copy._values;
		itEnd = it + _length + size;
		for (; it != itEnd; it += size + 1)
		{
			det *= *it;
		}

		return det;
	}


	template<typename TValue>
	constexpr Matrix<TValue> operator+(const Matrix<TValue>& matrixA, const Matrix<TValue>& matrixB)
	{
		Matrix<TValue> matrixC(matrixA);
		matrixC += matrixB;
		return matrixC;
	}

	template<typename TValue>
	constexpr Matrix<TValue>&& operator+(Matrix<TValue>&& matrixA, const Matrix<TValue>& matrixB)
	{
		matrixA += matrixB;
		return std::forward(matrixA);
	}

	template<typename TValue>
	constexpr Matrix<TValue>&& operator+(const Matrix<TValue>& matrixA, Matrix<TValue>&& matrixB)
	{
		matrixB += matrixA;
		return std::forward(matrixB);
	}

	template<typename TValue>
	constexpr Matrix<TValue>&& operator+(Matrix<TValue>&& matrixA, Matrix<TValue>&& matrixB)
	{
		matrixA += matrixB;
		return std::forward(matrixA);
	}

	template<typename TValue>
	constexpr Matrix<TValue> operator-(const Matrix<TValue>& matrixA, const Matrix<TValue>& matrixB)
	{
		Matrix<TValue> matrixC(matrixA);
		matrixC -= matrixB;
		return matrixC;
	}

	template<typename TValue>
	constexpr Matrix<TValue>&& operator-(Matrix<TValue>&& matrixA, const Matrix<TValue>& matrixB)
	{
		matrixA -= matrixB;
		return std::forward(matrixA);
	}

	template<typename TValue>
	constexpr Matrix<TValue>&& operator-(const Matrix<TValue>& matrixA, Matrix<TValue>&& matrixB)
	{
		matrixB -= matrixA;
		matrixB.negate();
		return std::forward(matrixB);
	}

	template<typename TValue>
	constexpr Matrix<TValue>&& operator-(Matrix<TValue>&& matrixA, Matrix<TValue>&& matrixB)
	{
		matrixA -= matrixB;
		return std::forward(matrixA);
	}

	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue> operator*(const Matrix<TValue>& matrix, const TScalar& scalar)
	{
		Matrix<TValue> copy(matrix);
		copy *= scalar;
		return copy;
	}

	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue>&& operator*(Matrix<TValue>&& matrix, const TScalar& scalar)
	{
		matrix *= scalar;
		return std::forward(matrix);
	}

	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue> operator*(const TScalar& scalar, const Matrix<TValue>& matrix)
	{
		Matrix<TValue> copy(matrix);
		copy *= scalar;
		return copy;
	}

	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue>&& operator*(const TScalar& scalar, Matrix<TValue>&& matrix)
	{
		matrix *= scalar;
		return std::forward(matrix);
	}

	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue> operator/(const Matrix<TValue>& matrix, const TScalar& scalar)
	{
		Matrix<TValue> copy(matrix);
		copy /= scalar;
		return copy;
	}

	template<typename TValue, typename TScalar>
	constexpr Matrix<TValue>&& operator/(Matrix<TValue>&& matrix, const TScalar& scalar)
	{
		matrix /= scalar;
		return std::forward(matrix);
	}

	template<typename TValue>
	constexpr Matrix<TValue> operator-(const Matrix<TValue>& matrix)
	{
		Matrix<TValue> copy(matrix);
		copy.negate();
		return copy;
	}

	template<typename TValue>
	constexpr Matrix<TValue>&& operator-(Matrix<TValue>&& matrix)
	{
		matrix.negate();
		return std::forward(matrix);
	}

	template<typename TValue>
	constexpr Matrix<TValue> operator+(const Matrix<TValue>& matrix)
	{
		return matrix;
	}

	template<typename TValue>
	constexpr Matrix<TValue>&& operator+(Matrix<TValue>&& matrix)
	{
		return std::forward(matrix);
	}

	template<typename TValue>
	Matrix<TValue> operator*(const Matrix<TValue>& matrixA, const Matrix<TValue>& matrixB)
	{
		Matrix<TValue> matrixC(matrixA.getSize(0), matrixB.getSize(1));
		matrixC.matrixProduct(matrixA, matrixB);
		return matrixC;
	}
}
