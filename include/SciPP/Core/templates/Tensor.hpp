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
	namespace _scp
	{
		template<typename TValue, typename TScalar>
		constexpr TValue lerp(const Tensor<TValue>& tensor, const uint64_t& order, const uint64_t* sizes, uint64_t* indices, const TScalar* coeffs, uint64_t n)
		{
			if (n == order)
			{
				return tensor.get(indices);
			}

			static constexpr TScalar zero = 0;
			static constexpr TScalar one = 1;

			const TScalar& t = coeffs[n];
			uint64_t& index = indices[n];

			if (index == sizes[n] - 1 || t == zero)
			{
				return lerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
			}
			else if (t == one)
			{
				++index;
				const TValue x = lerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
				--index;
				return x;
			}
			else
			{
				const TValue x = lerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
				++index;
				const TValue y = lerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
				--index;

				return t * y + (one - t) * x;
			}
		}

		template<typename TValue, typename TScalar>
		constexpr TValue cerp(const Tensor<TValue>& tensor, const uint64_t& order, const uint64_t* sizes, uint64_t* indices, const TScalar* coeffs, uint64_t n)
		{
			if (n == order)
			{
				return tensor.get(indices);
			}

			static constexpr TScalar zero = 0;
			static constexpr TScalar one = 1;

			const TScalar& t = coeffs[n];
			uint64_t& index = indices[n];

			if (t == zero)
			{
				return cerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
			}
			else if (t == one)
			{
				++index;
				const TValue x = cerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
				--index;
				return x;
			}
			else
			{
				const TValue x1 = cerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
				--index;
				const TValue x0 = index == UINT64_MAX ? x1 : cerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
				index += 2;
				const TValue x2 = index == sizes[n] ? x1 : cerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
				TValue x3 = x2;
				if (index != sizes[n])
				{
					++index;
					x3 = index == sizes[n] ? x2 : cerp<TValue>(tensor, order, sizes, indices, coeffs, n + 1);
					--index;
				}
				--index;

				const TScalar tSq = t * t;
				const TScalar tCu = tSq * t;

				const TScalar a = 2 * tSq - tCu - t;
				const TScalar b = 3 * tCu - 5 * tSq + t + one;
				const TScalar c = 4 * tSq - 3 * tCu;
				const TScalar d = tCu - tSq;

				if constexpr (std::integral<TValue>)
				{
					return std::clamp<TScalar>(x0 * a + x1 * b + x2 * c + x3 * d, std::numeric_limits<TValue>::min(), std::numeric_limits<TValue>::max());
				}
				else
				{
					return x3 * a + x2 * b + x1 * c + x0 * d;
				}
			}
		}
	}

	template<typename TValue>
	constexpr Tensor<TValue>* Tensor<TValue>::createAroundMemory(uint64_t order, const uint64_t* sizes, TValue* memory)
	{
		assert(order != 0);
		assert(std::find(sizes, sizes + order, 0) == sizes + order);
		assert(memory);

		Tensor<TValue>* tensor = new Tensor<TValue>();

		tensor->_shape.order = order;
		tensor->_shape.sizes = new uint64_t[order];
		tensor->_length = std::accumulate(sizes, sizes + order, 1, std::multiplies<uint64_t>());
		tensor->_values = memory;
		tensor->_owner = false;

		std::copy_n(sizes, order, tensor->_shape.sizes);

		return tensor;
	}

	template<typename TValue>
	constexpr Tensor<TValue>* Tensor<TValue>::createAroundMemory(const std::initializer_list<uint64_t>& sizes, TValue* memory)
	{
		return createAroundMemory(sizes.size(), sizes.begin(), memory);
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor() :
		_shape{ 0, nullptr },
		_length(0),
		_values(nullptr),
		_owner(true)
	{
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(uint64_t order, const uint64_t* sizes) :
		_shape{ order, new uint64_t[order] },
		_length(std::accumulate(sizes, sizes + order, 1, std::multiplies<uint64_t>())),
		_values(new TValue[_length]),
		_owner(true)
	{
		assert(order != 0);
		assert(std::find(sizes, sizes + order, 0) == sizes + order);

		std::copy_n(sizes, _shape.order, _shape.sizes);
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(uint64_t order, const uint64_t* sizes, const TValue& value) : Tensor<TValue>(order, sizes)
	{
		std::fill_n(_values, _length, value);
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(uint64_t order, const uint64_t* sizes, const TValue* values) : Tensor<TValue>(order, sizes)
	{
		std::copy_n(values, _length, _values);
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(uint64_t order, const uint64_t* sizes, const std::initializer_list<TValue>& values) : Tensor<TValue>(order, sizes)
	{
		assert(values.size() == _length);

		std::copy_n(values.begin(), _length, _values);
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(const std::initializer_list<uint64_t>& sizes) : Tensor<TValue>(sizes.size(), sizes.begin())
	{
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(const std::initializer_list<uint64_t>& sizes, const TValue& value) : Tensor<TValue>(sizes.size(), sizes.begin(), value)
	{
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(const std::initializer_list<uint64_t>& sizes, const TValue* values) : Tensor<TValue>(sizes.size(), sizes.begin(), values)
	{
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(const std::initializer_list<uint64_t>& sizes, const std::initializer_list<TValue>& values) : Tensor<TValue>(sizes.size(), sizes.begin(), values)
	{
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(const Tensor<TValue>& tensor) :
		_shape{ tensor._shape.order, new uint64_t[tensor._shape.order] },
		_length(tensor._length),
		_values(new TValue[tensor._length]),
		_owner(true)
	{
		std::copy_n(tensor._shape.sizes, tensor._shape.order, _shape.sizes);
		std::copy_n(tensor._values, _length, _values);
	}

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor(Tensor<TValue>&& tensor) :
		_shape(tensor._shape),
		_length(tensor._length),
		_values(tensor._values),
		_owner(tensor._owner)
	{
		tensor._values = nullptr;
	}

	template<typename TValue>
	constexpr Tensor<TValue>& Tensor<TValue>::operator=(const Tensor<TValue>& tensor)
	{
		if (_shape.order != tensor._shape.order || _length != tensor._length)
		{
			assert(_owner);

			delete[] _shape.sizes;
			delete[] _values;

			_shape.order = tensor._shape.order;
			_length = std::accumulate(tensor._shape.sizes, tensor._shape.sizes + tensor._shape.order, 1, std::multiplies<uint64_t>());
			_shape.sizes = new uint64_t[_shape.order];
			_values = new TValue[_length];
			_owner = true;

			std::copy_n(tensor._shape.sizes, _shape.order, _shape.sizes);
		}
		else if (!std::equal(_shape.sizes, _shape.sizes + _shape.order, tensor._shape.sizes))
		{
			std::copy_n(tensor._shape.sizes, _shape.order, _shape.sizes);
		}

		std::copy_n(tensor._values, _length, _values);

		return *this;
	}

	template<typename TValue>
	constexpr Tensor<TValue>& Tensor<TValue>::operator=(Tensor<TValue>&& tensor)
	{
		if (!_owner || !tensor._owner)
		{
			return operator=(reinterpret_cast<const Tensor<TValue>&>(tensor));
		}

		delete[] _shape.sizes;
		delete[] _values;

		_shape.order = tensor._shape.order;
		_length = tensor._length;
		_shape.sizes = tensor._shape.sizes;
		_values = tensor._values;
		_owner = tensor._owner;
		
		tensor._values = nullptr;

		return *this;
	}

	template<typename TValue>
	constexpr Tensor<TValue>& Tensor<TValue>::operator+=(const Tensor<TValue>& tensor)
	{
		assert(_shape.order == tensor._shape.order);
		assert(std::equal(_shape.sizes, _shape.sizes + _shape.order, tensor._shape.sizes));

		TValue* values = _values;
		TValue* tensorValues = tensor._values;
		const TValue* const valuesEnd = _values + _length;
		
		for (; values != valuesEnd; ++values, ++tensorValues)
		{
			*values += *tensorValues;
		}

		return *this;
	}

	template<typename TValue>
	constexpr Tensor<TValue>& Tensor<TValue>::operator-=(const Tensor<TValue>& tensor)
	{
		assert(_shape.order == tensor._shape.order);
		assert(std::equal(_shape.sizes, _shape.sizes + _shape.order, tensor._shape.sizes));

		TValue* values = _values;
		TValue* tensorValues = tensor._values;
		const TValue* const valuesEnd = _values + _length;

		for (; values != valuesEnd; ++values, ++tensorValues)
		{
			*values -= *tensorValues;
		}

		return *this;
	}

	template<typename TValue>
	template<typename TScalar>
	constexpr Tensor<TValue>& Tensor<TValue>::operator*=(const TScalar& scalar)
	{
		TValue* values = _values;
		const TValue* const valuesEnd = _values + _length;

		for (; values != valuesEnd; ++values)
		{
			*values *= scalar;
		}

		return *this;
	}

	template<typename TValue>
	template<typename TScalar>
	constexpr Tensor<TValue>& Tensor<TValue>::operator/=(const TScalar& scalar)
	{
		TValue* values = _values;
		const TValue* const valuesEnd = _values + _length;

		for (; values != valuesEnd; ++values)
		{
			*values /= scalar;
		}

		return *this;
	}

	template<typename TValue>
	constexpr Tensor<TValue>& Tensor<TValue>::negate()
	{
		TValue* values = _values;
		const TValue* const valuesEnd = _values + _length;

		for (; values != valuesEnd; ++values)
		{
			*values = -(*values);
		}

		return *this;
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::tensorProduct(const Tensor<TValue>& tensorA, const Tensor<TValue>& tensorB)
	{
		assert(tensorA._shape.order + tensorB._shape.order == _shape.order);
		assert(std::equal(tensorA._shape.sizes, tensorA._shape.sizes + tensorA._shape.order, _shape.sizes));
		assert(std::equal(tensorB._shape.sizes, tensorB._shape.sizes + tensorB._shape.order, _shape.sizes + tensorA._shape.order));

		const uint64_t lengthA = tensorA._length;

		TValue* values = _values;

		const TValue* valuesA = tensorA._values;
		const TValue* const valuesAEnd = valuesA + tensorA._length;

		const TValue* valuesB = tensorB._values;
		const TValue* const valuesBEnd = valuesB + tensorB._length;

		for (; valuesA != valuesAEnd; ++valuesA)
		{
			valuesB = tensorB._values;
			for (; valuesB != valuesBEnd; ++valuesB, ++values)
			{
				*values = (*valuesA) * (*valuesB);
			}
		}
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::hadamardProduct(const Tensor<TValue>& tensor)
	{
		assert(_shape.order == tensor._shape.order);
		assert(std::equal(_shape.sizes, _shape.sizes + _shape.order, tensor._shape.sizes));

		TValue* values = _values;
		TValue* tensorValues = tensor._values;
		const TValue* const valuesEnd = _values + _length;

		for (; values != valuesEnd; ++values, ++tensorValues)
		{
			*values *= *tensorValues;
		}

		return *this;
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::fft()
	{
		if constexpr (CComplex<TValue>)
		{
			TValue** bases = new TValue*[_shape.order];
			for (uint64_t i = 0; i < _shape.order; ++i)
			{
				bases[i] = new TValue[_shape.sizes[i]];

				TValue x = std::exp(TValue(0, -2 * std::numbers::pi / _shape.sizes[i]));
				bases[i][0] = 1;
				for (uint64_t j = 1; j < _shape.sizes[i]; ++j)
				{
					bases[i][j] = x * bases[i][j - 1];
				}
			}

			_ndCooleyTukey(_values, _shape.order, bases);

			for (uint64_t i = 0; i < _shape.order; ++i)
			{
				delete[] bases[i];
			}
			delete[] bases;
		}
		else
		{
			assert(false);
		}
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::ifft()
	{
		if constexpr (CComplex<TValue>)
		{
			TValue** bases = new TValue * [_shape.order];
			for (uint64_t i = 0; i < _shape.order; ++i)
			{
				bases[i] = new TValue[_shape.sizes[i]];

				TValue x = std::exp(TValue(0, 2 * std::numbers::pi / _shape.sizes[i]));
				bases[i][0] = 1;
				for (uint64_t j = 1; j < _shape.sizes[i]; ++j)
				{
					bases[i][j] = x * bases[i][j - 1];
				}
			}

			_ndCooleyTukey(_values, _shape.order, bases);

			for (uint64_t i = 0; i < _shape.order; ++i)
			{
				delete[] bases[i];
			}
			delete[] bases;

			*this /= TValue(_length);
		}
		else
		{
			assert(false);
		}
	}

	template<typename TValue>
	template<BorderBehaviour BBehaviour>
	constexpr void Tensor<TValue>::convolution(const Tensor<TValue>& kernel)
	{
		assert(_shape.order == kernel._shape.order);
		
		// Do a copy of *this
		Tensor<TValue> tensor(*this);
		
		// Check that the kernel's sizes are odd
		for (uint64_t i = 0; i < _shape.order; i++)
		{
			assert(kernel._shape.sizes[i] & 1);
			assert(kernel._shape.sizes[i] <= _shape.sizes[i]);
		}
		
		// Compute offset (to center the kernel)
		int64_t* offset = reinterpret_cast<int64_t*>(alloca(_shape.order * sizeof(int64_t)));
		for (uint64_t i = 0; i < _shape.order; i++)
		{
			offset[i] = static_cast<int64_t>(kernel._shape.sizes[i] / 2);
		}
		
		// For each element of the original tensor
		int64_t* offsetedIndices = reinterpret_cast<int64_t*>(alloca(_shape.order * sizeof(int64_t)));
		for (const TensorPosition& pos : _shape)
		{
			TValue value = 0;
		
			// For each element of the kernel
			for (const TensorPosition& kernelPos : kernel._shape)
			{
				bool setToZero = false;
		
				int64_t* itOffsetedIndices = offsetedIndices;
				const uint64_t* itSizes = _shape.sizes;
				const int64_t* itOffset = offset;
				const uint64_t* itIndices = pos.indices;
				const uint64_t* itKernelIndices = kernelPos.indices;
		
				// Compute the corresponding indices to poll
				for (uint64_t k = 0; k < _shape.order; ++k, ++itKernelIndices, ++itOffsetedIndices, ++itSizes, ++itOffset, ++itIndices)
				{
					*itOffsetedIndices = static_cast<int64_t>(*itIndices) + *itOffset - static_cast<int64_t>(*itKernelIndices);
		
					if constexpr (BBehaviour == BorderBehaviour::Zero)
					{
						if (*itOffsetedIndices < 0 || *itOffsetedIndices >= *itSizes)
						{
							setToZero = true;
							break;
						}
					}
					else if constexpr (BBehaviour == BorderBehaviour::Continuous)
					{
						*itOffsetedIndices = std::clamp<int64_t>(*itOffsetedIndices, 0, *itSizes - 1);
					}
					else if constexpr (BBehaviour == BorderBehaviour::Periodic)
					{
						*itOffsetedIndices = (*itOffsetedIndices + *itSizes) % *itSizes;
					}
				}
		
				// Add the product to the result
				if (!setToZero)
				{
					value += tensor.get(reinterpret_cast<uint64_t*>(offsetedIndices)) * kernel.get(kernelPos.index);
				}
			}
		
			_values[pos.index] = value;
		}
	}

	template<typename TValue>
	template<typename TScalar, InterpolationMethod MagMethod, CollapseMethod MinMethod>
	constexpr void Tensor<TValue>::resize(const Tensor<TValue>& tensor)
	{
		assert(_shape.order == tensor._shape.order);
		
		uint64_t* indices = reinterpret_cast<uint64_t*>(alloca(_shape.order * sizeof(uint64_t)));
		TScalar* coeffs = reinterpret_cast<TScalar*>(alloca(_shape.order * sizeof(TScalar)));

		TScalar* sizesRatio = reinterpret_cast<TScalar*>(alloca(_shape.order * sizeof(TScalar)));
		for (uint64_t i = 0; i < _shape.order; ++i)
		{
			sizesRatio[i] = static_cast<TScalar>(tensor._shape.sizes[i] - 1) / (_shape.sizes[i] - 1);
		}
		
		for (const TensorPosition& pos : _shape)
		{
			for (uint64_t i = 0; i < _shape.order; ++i)
			{
				coeffs[i] = pos.indices[i] * sizesRatio[i];
				indices[i] = static_cast<uint64_t>(coeffs[i]);
				coeffs[i] -= indices[i];
			}
		
			if constexpr (MagMethod == InterpolationMethod::Nearest)
			{
				_values[pos.index] = tensor.get(indices);
			}
			else if constexpr (MagMethod == InterpolationMethod::Linear)
			{
				_values[pos.index] = _scp::lerp<TValue>(tensor, tensor._shape.order, tensor._shape.sizes, indices, coeffs, 0);
			}
			else if constexpr (MagMethod == InterpolationMethod::Cubic)
			{
				_values[pos.index] = _scp::cerp<TValue>(tensor, tensor._shape.order, tensor._shape.sizes, indices, coeffs, 0);
			}
		}
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::contract(const Tensor<TValue>& tensor, uint64_t i, uint64_t j)
	{
		assert(tensor._shape.order > 2);
		assert(_shape.order == tensor._shape.order - 2);
		assert(i != j);
		assert(i < tensor._shape.order);
		assert(j < tensor._shape.order);
		assert(tensor._shape.sizes[i] == tensor._shape.sizes[j]);

		if (i > j)
		{
			std::swap(i, j);
		}

		assert(i == 0 || std::equal(_shape.sizes, _shape.sizes + i, tensor._shape.sizes));
		assert(j == i + 1 || std::equal(_shape.sizes + i, _shape.sizes + j - 1, tensor._shape.sizes + i + 1));
		assert(j == tensor._shape.order - 1 || std::equal(_shape.sizes + j - 1, _shape.sizes + _shape.order, tensor._shape.sizes + j + 1));
		
		uint64_t* indices = reinterpret_cast<uint64_t*>(alloca(_shape.order * sizeof(uint64_t)));
		for (const TensorPosition& pos : _shape)
		{
			if (i != 0)
			{
				std::copy(pos.indices, pos.indices + i, indices);
			}
			if (i != j - 1)
			{
				std::copy(pos.indices + i, pos.indices + j - 1, indices + i + 1);
			}
			if (j != _shape.order - 1)
			{
				std::copy(pos.indices + j - 1, pos.indices + _shape.order, indices + j + 1);
			}
		
			_values[pos.index] = 0;
			for (uint64_t k = 0; k < tensor._shape.sizes[i]; ++k)
			{
				indices[i] = k;
				indices[j] = k;
				_values[pos.index] += tensor.get(indices);
			}
		}
	}

	template<typename TValue>
	constexpr bool Tensor<TValue>::operator==(const Tensor<TValue>& tensor) const
	{
		return (
			_shape.order == tensor._shape.order
			&& std::equal(_shape.sizes, _shape.sizes + _shape.order, tensor._shape.sizes)
			&& std::equal(_values, _values + _length, tensor._values)
		);
	}

	template<typename TValue>
	constexpr bool Tensor<TValue>::operator!=(const Tensor<TValue>& tensor) const
	{
		return !operator==(tensor);
	}

	template<typename TValue>
	constexpr TValue* Tensor<TValue>::begin()
	{
		return _values;
	}

	template<typename TValue>
	constexpr TValue* Tensor<TValue>::end()
	{
		return _values + _length;
	}

	template<typename TValue>
	constexpr const TValue* Tensor<TValue>::begin() const
	{
		return _values;
	}

	template<typename TValue>
	constexpr const TValue* Tensor<TValue>::end() const
	{
		return _values + _length;
	}

	template<typename TValue>
	constexpr const TValue* Tensor<TValue>::cbegin() const
	{
		return _values;
	}

	template<typename TValue>
	constexpr const TValue* Tensor<TValue>::cend() const
	{
		return _values + _length;
	}

	template<typename TValue>
	template<BorderBehaviour BBehaviour>
	constexpr const TValue& Tensor<TValue>::getOutOfBound(const int64_t* indices) const
	{
		if constexpr (BBehaviour == BorderBehaviour::Zero)
		{
			static constexpr TValue zero = 0;

			for (uint64_t i = 0; i < _shape.order; ++i)
			{
				if (indices[i] < 0 || indices[i] >= _shape.sizes[i])
				{
					return zero;
				}
			}

			return get(reinterpret_cast<const uint64_t*>(indices));
		}
		else if constexpr (BBehaviour == BorderBehaviour::Continuous)
		{
			uint64_t* realIndices = reinterpret_cast<uint64_t*>(alloca(sizeof(uint64_t) * _shape.order));

			for (uint64_t i = 0; i < _shape.order; ++i)
			{
				realIndices[i] = indices[i] & -(indices[i] > 0);
				realIndices[i] = (realIndices[i] | -(realIndices[i] >= _shape.sizes[i])) & ((_shape.sizes[i] - 1) | -(realIndices[i] < _shape.sizes[i]));
			}

			return get(realIndices);
		}
		else if constexpr (BBehaviour == BorderBehaviour::Periodic)
		{
			uint64_t* realIndices = reinterpret_cast<uint64_t*>(alloca(sizeof(uint64_t) * _shape.order));

			for (uint64_t i = 0; i < _shape.order; ++i)
			{
				if (indices[i] < 0)
				{
					realIndices[i] = (indices[i] % _shape.sizes[i]) + _shape.sizes[i];
				}
				else if (indices[i] >= _shape.sizes[i])
				{
					realIndices[i] = indices[i] % _shape.sizes[i];
				}
				else
				{
					realIndices[i] = indices[i];
				}
			}

			return get(realIndices);
		}
	}

	template<typename TValue>
	template<BorderBehaviour BBehaviour>
	constexpr const TValue& Tensor<TValue>::getOutOfBound(const std::initializer_list<int64_t>& indices) const
	{
		assert(indices.size() == _shape.order);
		return getOutOfBound<BBehaviour>(indices.begin());
	}

	template<typename TValue>
	template<typename TScalar, InterpolationMethod IMethod>
	constexpr TValue Tensor<TValue>::getInterpolated(const TScalar* scalarIndices) const
	{
		// TODO: Handle different border behaviours ?

		uint64_t* indices = reinterpret_cast<uint64_t*>(alloca(_shape.order * sizeof(uint64_t)));
		TScalar* coeffs = reinterpret_cast<TScalar*>(alloca(_shape.order * sizeof(TScalar)));

		for (uint64_t i = 0; i < _shape.order; ++i)
		{
			if (scalarIndices[i] < 0)
			{
				indices[i] = 0;
				coeffs[i] = 0;
			}
			else if (scalarIndices[i] >= _shape.sizes[i])
			{
				indices[i] = _shape.sizes[i] - 1;
				coeffs[i] = 0;
			}
			else
			{
				indices[i] = static_cast<uint64_t>(scalarIndices[i]);
				coeffs[i] = scalarIndices[i] - indices[i];
			}
		}

		if constexpr (IMethod == InterpolationMethod::Nearest)
		{
			return get(indices);
		}
		else if constexpr (IMethod == InterpolationMethod::Linear)
		{
			return _scp::lerp<TValue>(*this, _shape.order, _shape.sizes, indices, coeffs, 0);
		}
		else if constexpr (IMethod == InterpolationMethod::Cubic)
		{
			return _scp::cerp<TValue>(*this, _shape.order, _shape.sizes, indices, coeffs, 0);
		}
	}

	template<typename TValue>
	template<typename TScalar, InterpolationMethod IMethod>
	constexpr TValue Tensor<TValue>::getInterpolated(const std::initializer_list<TScalar>& scalarIndices) const
	{
		assert(scalarIndices.size() == _shape.order);
		return getInterpolated<TScalar, IMethod>(scalarIndices.begin());
	}

	template<typename TValue>
	constexpr TValue& Tensor<TValue>::operator[](uint64_t index)
	{
		assert(index < _length);
		return _values[index];
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::operator[](uint64_t index) const
	{
		assert(index < _length);
		return _values[index];
	}

	template<typename TValue>
	constexpr TValue& Tensor<TValue>::operator[](const std::initializer_list<uint64_t>& indices)
	{
		assert(_shape.getIndex(indices.begin()) < _length);
		return _values[_shape.getIndex(indices.begin())];
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::operator[](const std::initializer_list<uint64_t>& indices) const
	{
		assert(_shape.getIndex(indices.begin()) < _length);
		return _values[_shape.getIndex(indices.begin())];
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::get(uint64_t index) const
	{
		assert(index < _length);
		return _values[index];
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::get(const uint64_t* indices) const
	{
		assert(_shape.getIndex(indices) < _length);
		return _values[_shape.getIndex(indices)];
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::get(const std::initializer_list<uint64_t>& indices) const
	{
		assert(_shape.getIndex(indices.begin()) < _length);
		return _values[_shape.getIndex(indices.begin())];
	}

	template<typename TValue>
	constexpr TValue& Tensor<TValue>::get(uint64_t index)
	{
		assert(index < _length);
		return _values[index];
	}

	template<typename TValue>
	constexpr TValue& Tensor<TValue>::get(const uint64_t* indices)
	{
		assert(_shape.getIndex(indices) < _length);
		return _values[_shape.getIndex(indices)];
	}

	template<typename TValue>
	constexpr TValue& Tensor<TValue>::get(const std::initializer_list<uint64_t>& indices)
	{
		assert(_shape.getIndex(indices.begin()) < _length);
		return _values[_shape.getIndex(indices.begin())];
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::set(uint64_t index, const TValue& value)
	{
		assert(index < _length);
		_values[index] = value;
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::set(const uint64_t* indices, const TValue& value)
	{
		assert(_shape.getIndex(indices) < _length);
		_values[_shape.getIndex(indices)] = value;
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::set(const std::initializer_list<uint64_t>& indices, const TValue& value)
	{
		assert(_shape.getIndex(indices.begin()) < _length);
		_values[_shape.getIndex(indices.begin())] = value;
	}

	template<typename TValue>
	constexpr const TensorShape& Tensor<TValue>::getShape() const
	{
		return _shape;
	}

	template<typename TValue>
	constexpr uint64_t Tensor<TValue>::getOrder() const
	{
		return _shape.order;
	}

	template<typename TValue>
	constexpr const uint64_t* Tensor<TValue>::getSizes() const
	{
		return _shape.sizes;
	}

	template<typename TValue>
	constexpr uint64_t Tensor<TValue>::getSize(uint64_t i) const
	{
		assert(i < _shape.order);
		return _shape.sizes[i];
	}

	template<typename TValue>
	constexpr uint64_t Tensor<TValue>::getElementCount() const
	{
		return _length;
	}

	template<typename TValue>
	constexpr TValue* Tensor<TValue>::getData()
	{
		return _values;
	}

	template<typename TValue>
	constexpr const TValue* Tensor<TValue>::getData() const
	{
		return _values;
	}

	template<typename TValue>
	constexpr Tensor<TValue>::~Tensor()
	{
		if (_values)
		{
			if (_owner)
			{
				delete[] _values;
			}

			delete[] _shape.sizes;
		}
	}

	namespace _scp
	{
		constexpr uint64_t reverse(uint64_t n, uint8_t bitCount)
		{
			constexpr uint8_t lookup[256] = {
				0b00000000, 0b10000000, 0b01000000, 0b11000000, 0b00100000, 0b10100000, 0b01100000, 0b11100000,
				0b00010000, 0b10010000, 0b01010000, 0b11010000, 0b00110000, 0b10110000, 0b01110000, 0b11110000,
				0b00001000, 0b10001000, 0b01001000, 0b11001000, 0b00101000, 0b10101000, 0b01101000, 0b11101000,
				0b00011000, 0b10011000, 0b01011000, 0b11011000, 0b00111000, 0b10111000, 0b01111000, 0b11111000,
				0b00000100, 0b10000100, 0b01000100, 0b11000100, 0b00100100, 0b10100100, 0b01100100, 0b11100100,
				0b00010100, 0b10010100, 0b01010100, 0b11010100, 0b00110100, 0b10110100, 0b01110100, 0b11110100,
				0b00001100, 0b10001100, 0b01001100, 0b11001100, 0b00101100, 0b10101100, 0b01101100, 0b11101100,
				0b00011100, 0b10011100, 0b01011100, 0b11011100, 0b00111100, 0b10111100, 0b01111100, 0b11111100,
				0b00000010, 0b10000010, 0b01000010, 0b11000010, 0b00100010, 0b10100010, 0b01100010, 0b11100010,
				0b00010010, 0b10010010, 0b01010010, 0b11010010, 0b00110010, 0b10110010, 0b01110010, 0b11110010,
				0b00001010, 0b10001010, 0b01001010, 0b11001010, 0b00101010, 0b10101010, 0b01101010, 0b11101010,
				0b00011010, 0b10011010, 0b01011010, 0b11011010, 0b00111010, 0b10111010, 0b01111010, 0b11111010,
				0b00000110, 0b10000110, 0b01000110, 0b11000110, 0b00100110, 0b10100110, 0b01100110, 0b11100110,
				0b00010110, 0b10010110, 0b01010110, 0b11010110, 0b00110110, 0b10110110, 0b01110110, 0b11110110,
				0b00001110, 0b10001110, 0b01001110, 0b11001110, 0b00101110, 0b10101110, 0b01101110, 0b11101110,
				0b00011110, 0b10011110, 0b01011110, 0b11011110, 0b00111110, 0b10111110, 0b01111110, 0b11111110,
				0b00000001, 0b10000001, 0b01000001, 0b11000001, 0b00100001, 0b10100001, 0b01100001, 0b11100001,
				0b00010001, 0b10010001, 0b01010001, 0b11010001, 0b00110001, 0b10110001, 0b01110001, 0b11110001,
				0b00001001, 0b10001001, 0b01001001, 0b11001001, 0b00101001, 0b10101001, 0b01101001, 0b11101001,
				0b00011001, 0b10011001, 0b01011001, 0b11011001, 0b00111001, 0b10111001, 0b01111001, 0b11111001,
				0b00000101, 0b10000101, 0b01000101, 0b11000101, 0b00100101, 0b10100101, 0b01100101, 0b11100101,
				0b00010101, 0b10010101, 0b01010101, 0b11010101, 0b00110101, 0b10110101, 0b01110101, 0b11110101,
				0b00001101, 0b10001101, 0b01001101, 0b11001101, 0b00101101, 0b10101101, 0b01101101, 0b11101101,
				0b00011101, 0b10011101, 0b01011101, 0b11011101, 0b00111101, 0b10111101, 0b01111101, 0b11111101,
				0b00000011, 0b10000011, 0b01000011, 0b11000011, 0b00100011, 0b10100011, 0b01100011, 0b11100011,
				0b00010011, 0b10010011, 0b01010011, 0b11010011, 0b00110011, 0b10110011, 0b01110011, 0b11110011,
				0b00001011, 0b10001011, 0b01001011, 0b11001011, 0b00101011, 0b10101011, 0b01101011, 0b11101011,
				0b00011011, 0b10011011, 0b01011011, 0b11011011, 0b00111011, 0b10111011, 0b01111011, 0b11111011,
				0b00000111, 0b10000111, 0b01000111, 0b11000111, 0b00100111, 0b10100111, 0b01100111, 0b11100111,
				0b00010111, 0b10010111, 0b01010111, 0b11010111, 0b00110111, 0b10110111, 0b01110111, 0b11110111,
				0b00001111, 0b10001111, 0b01001111, 0b11001111, 0b00101111, 0b10101111, 0b01101111, 0b11101111,
				0b00011111, 0b10011111, 0b01011111, 0b11011111, 0b00111111, 0b10111111, 0b01111111, 0b11111111,
			};

			uint64_t result = lookup[n & 0xFF];
			if (bitCount > 8)
			{
				result = (result << 8) | lookup[(n >>= 8) & 0xFF];
				if (bitCount > 16)
				{
					result = (result << 8) | lookup[(n >>= 8) & 0xFF];
					if (bitCount > 24)
					{
						result = (result << 8) | lookup[(n >>= 8) & 0xFF];
						if (bitCount > 32)
						{
							result = (result << 8) | lookup[(n >>= 8) & 0xFF];
							if (bitCount > 40)
							{
								result = (result << 8) | lookup[(n >>= 8) & 0xFF];
								if (bitCount > 48)
								{
									result = (result << 8) | lookup[(n >>= 8) & 0xFF];
									if (bitCount > 56)
									{
										result = (result << 8) | lookup[(n >>= 8) & 0xFF];
									}
								}
							}
						}
					}
				}
			}
			return result >> ((64 - bitCount) % 8);
		}
	
		template<typename TValue>
		constexpr void bitReversal(TValue* beg, uint64_t stride, uint64_t size, uint8_t bitCount)
		{
			TValue* it = beg + stride;
			for (uint64_t i = 1; i < size; ++i, it += stride)
			{
				uint64_t r = reverse(i, bitCount);
				if (r > i)
				{
					std::swap(*it, *(beg + r * stride));
				}
			}
		}

		template<typename TValue>
		constexpr void cooleyTukeyRadix2(TValue* beg, uint64_t stride, const TValue* base, uint64_t baseStride, uint64_t size)
		{
			if (size == 2)
			{
				TValue& x0 = *beg;
				TValue& x1 = *(beg + stride);
				const TValue tmp = x0;
				x0 += *base * x1;
				x1 = tmp + *(base + baseStride) * x1;
			}
			else
			{
				size >>= 1;
				baseStride <<= 1;

				cooleyTukeyRadix2(beg, stride, base, baseStride, size);
				cooleyTukeyRadix2(beg + size * stride, stride, base, baseStride, size);

				baseStride >>= 1;

				TValue* it = beg;
				TValue* it2 = it + size * stride;
				const TValue* const itEnd = it2;
				for (; it != itEnd; it += stride, it2 += stride, base += baseStride)
				{
					TValue tmp = *base * *it2;
					*it2 = *it - tmp;
					*it += tmp;
				}
			}
		}

		template<typename TValue>
		constexpr void cooleyTukey(TValue* beg, uint64_t stride, const TValue* base, uint64_t baseStride, uint64_t size, std::pair<uint64_t, uint64_t>* factors, uint64_t factorCount)
		{
			if (size == 1)
			{
				return;
			}

			// TODO: https://en.wikipedia.org/wiki/Rader%27s_FFT_algorithm
			// if (factorCount == 1 && factors->second == 1)
			// {
			// }

			// Compute best radix and remove it from factors

			const uint64_t radix = factors->first;

			--factors->second;
			if (factors->second == 0)
			{
				++factors;
				--factorCount;
			}

			// Re-order elements according to radix

			const uint64_t subSize = size / radix;

			std::vector<bool> visited(size, false);
			visited[0] = true;
			visited[size - 1] = true;

			uint64_t n = 0;
			uint64_t preced, next;
			while (n != size)
			{
				if (visited[n])
				{
					++n;
					continue;
				}

				TValue tmp = *(beg + n * stride);
				visited[n] = true;

				preced = n;
				next = preced / subSize + (preced % subSize) * radix;

				while (next != n)
				{
					*(beg + preced * stride) = *(beg + next * stride);
					visited[next] = true;

					preced = next;
					next = preced / subSize + (preced % subSize) * radix;
				}

				*(beg + preced * stride) = tmp;
			}

			// Run algorithm on sub-ranges

			size = subSize;
			baseStride *= radix;

			for (uint64_t i = 0; i < radix; ++i)
			{
				cooleyTukey(beg + i * size * stride, stride, base, baseStride, size, factors, factorCount);
			}

			baseStride /= radix;
			const uint64_t realSize = size * radix;

			// Put back the factor

			if (factors->first != radix)
			{
				--factors;
				++factorCount;
			}
			++factors->second;

			// Merge sub-ranges

			const uint64_t rangeOffset = size * stride;
				
			std::vector<TValue> tmp(radix);
			TValue* it = beg;
			for (uint64_t i = 0; i < size; ++i, it += stride)
			{
				for (uint64_t j = 0; j < radix; ++j, it += rangeOffset)
				{
					tmp[j] = *it;
				}
				it -= radix * rangeOffset;

				uint64_t coeff = i;
				for (uint64_t j = 0; j < radix; ++j, it += rangeOffset, coeff += size)
				{
					*it = 0;
					for (uint64_t k = 0; k < radix; ++k)
					{
						*it += tmp[k] * *(base + ((k * coeff) % realSize) * baseStride);
					}
				}
				it -= radix * rangeOffset;
			}
		}
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::_ndCooleyTukey(TValue* beg, uint64_t order, const TValue* const* bases)
	{
		const uint64_t& size = *(_shape.sizes + _shape.order - order);
		
		const uint64_t subLength = std::accumulate(_shape.sizes + _shape.order - order + 1, _shape.sizes + _shape.order, 1, std::multiplies<uint64_t>());
		
		if (order > 1)
		{
			for (uint64_t i = 0; i < size; ++i)
			{
				_ndCooleyTukey(beg + i * subLength, order - 1, bases);
			}
		}

		if (size > 1)
		{
			const TValue* base = bases[_shape.order - order];

			if ((size & (size - 1)) == 0)
			{
				for (uint64_t i = 0; i < subLength; ++i)
				{
					_scp::bitReversal(beg + i, subLength, size, std::log2(size));
					_scp::cooleyTukeyRadix2(beg + i, subLength, base, 1, size);
				}
			}
			else
			{
				std::vector<std::pair<uint64_t, uint64_t>> factors, factorsCopy;
				primeFactors(size, factors);

				for (uint64_t i = 0; i < subLength; ++i)
				{
					factorsCopy = factors;
					_scp::cooleyTukey(beg + i, subLength, base, 1, size, factorsCopy.data(), factorsCopy.size());
				}
			}
		}
	}


	template<typename TValue>
	constexpr Tensor<TValue> operator+(const Tensor<TValue>& tensorA, const Tensor<TValue>& tensorB)
	{
		Tensor<TValue> tensorC(tensorA);
		tensorC += tensorB;
		return tensorC;
	}

	template<typename TValue>
	constexpr Tensor<TValue>&& operator+(Tensor<TValue>&& tensorA, const Tensor<TValue>& tensorB)
	{
		tensorA += tensorB;
		return std::forward(tensorA);
	}

	template<typename TValue>
	constexpr Tensor<TValue>&& operator+(const Tensor<TValue>& tensorA, Tensor<TValue>&& tensorB)
	{
		tensorB += tensorA;
		return std::forward(tensorB);
	}

	template<typename TValue>
	constexpr Tensor<TValue>&& operator+(Tensor<TValue>&& tensorA, Tensor<TValue>&& tensorB)
	{
		tensorA += tensorB;
		return std::forward(tensorA);
	}

	template<typename TValue>
	constexpr Tensor<TValue> operator-(const Tensor<TValue>& tensorA, const Tensor<TValue>& tensorB)
	{
		Tensor<TValue> tensorC(tensorA);
		tensorC -= tensorB;
		return tensorC;
	}

	template<typename TValue>
	constexpr Tensor<TValue>&& operator-(Tensor<TValue>&& tensorA, const Tensor<TValue>& tensorB)
	{
		tensorA -= tensorB;
		return std::forward(tensorA);
	}

	template<typename TValue>
	constexpr Tensor<TValue>&& operator-(const Tensor<TValue>& tensorA, Tensor<TValue>&& tensorB)
	{
		tensorB -= tensorA;
		tensorB.negate();
		return std::forward(tensorB);
	}

	template<typename TValue>
	constexpr Tensor<TValue>&& operator-(Tensor<TValue>&& tensorA, Tensor<TValue>&& tensorB)
	{
		tensorA -= tensorB;
		return std::forward(tensorA);
	}

	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue> operator*(const Tensor<TValue>& tensor, const TScalar& scalar)
	{
		Tensor<TValue> copy(tensor);
		copy *= scalar;
		return copy;
	}

	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue>&& operator*(Tensor<TValue>&& tensor, const TScalar& scalar)
	{
		tensor *= scalar;
		return std::forward(tensor);
	}

	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue> operator*(const TScalar& scalar, const Tensor<TValue>& tensor)
	{
		Tensor<TValue> copy(tensor);
		copy *= scalar;
		return copy;
	}

	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue>&& operator*(const TScalar& scalar, Tensor<TValue>&& tensor)
	{
		tensor *= scalar;
		return std::forward(tensor);
	}

	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue> operator/(const Tensor<TValue>& tensor, const TScalar& scalar)
	{
		Tensor<TValue> copy(tensor);
		copy /= scalar;
		return copy;
	}

	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue>&& operator/(Tensor<TValue>&& tensor, const TScalar& scalar)
	{
		tensor /= scalar;
		return std::forward(tensor);
	}

	template<typename TValue>
	constexpr Tensor<TValue> operator-(const Tensor<TValue>& tensor)
	{
		Tensor<TValue> copy(tensor);
		copy.negate();
		return copy;
	}

	template<typename TValue>
	constexpr Tensor<TValue>&& operator-(Tensor<TValue>&& tensor)
	{
		tensor.negate();
		return std::forward(tensor);
	}

	template<typename TValue>
	constexpr Tensor<TValue> operator+(const Tensor<TValue>& tensor)
	{
		return tensor;
	}

	template<typename TValue>
	constexpr Tensor<TValue>&& operator+(Tensor<TValue>&& tensor)
	{
		return std::forward(tensor);
	}
}
