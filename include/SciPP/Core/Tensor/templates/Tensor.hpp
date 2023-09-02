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
	SCP_TENSOR_DEF(template<typename TValue>, Tensor, Tensor<TValue>)

	template<typename TValue>
	constexpr Tensor<TValue>::Tensor() :
		_order(0),
		_length(0),
		_sizes(nullptr),
		_values(nullptr),
		_owner(true)
	{
	}

	template<typename TValue>
	constexpr Tensor<TValue>* Tensor<TValue>::createAroundMemory(uint64_t order, const uint64_t* sizes, TValue* memory)
	{
		assert(order != 0);
		assert(std::find(sizes, sizes + order, 0) == sizes + order);
		assert(memory);

		Tensor<TValue>* tensor = new Tensor<TValue>();

		tensor->_order = order;

		tensor->_length = std::accumulate(sizes, sizes + order, 1, std::multiplies<uint64_t>());

		tensor->_sizes = new uint64_t[order];
		std::copy_n(sizes, order, tensor->_sizes);

		tensor->_values = memory;

		tensor->_owner = false;

		return tensor;
	}

	template<typename TValue>
	constexpr Tensor<TValue>* Tensor<TValue>::createAroundMemory(const std::initializer_list<uint64_t>& sizes, TValue* memory)
	{
		return createAroundMemory(sizes.size(), sizes.begin(), memory);
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::fill(const TValue& value)
	{
		std::fill_n(_values, _length, value);
	}

	template<typename TValue>
	template<std::input_iterator TInput>
	constexpr void Tensor<TValue>::copy(TInput it)
	{
		std::copy_n(it, _length, _values);
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::transform(const std::function<TValue(const TValue&)>& unaryOp)
	{
		std::transform(_values, _values + _length, _values, unaryOp);
	}

	template<typename TValue>
	template<std::input_iterator TInput>
	constexpr void Tensor<TValue>::transform(TInput it, const std::function<TValue(const TValue&, const typename std::iterator_traits<TInput>::value_type&)>& binaryOp)
	{
		std::transform(_values, _values + _length, it, _values, binaryOp);
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr Tensor<TValue>& Tensor<TValue>::operator+=(const TTensor& tensor)
	{
		assert(_order == tensor.getOrder());
		assert(std::equal(_sizes, _sizes + _order, tensor.getSizes()));

		transform(tensor.begin(), std::plus<TValue>());
		return *this;
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr Tensor<TValue>& Tensor<TValue>::operator-=(const TTensor& tensor)
	{
		assert(_order == tensor.getOrder());
		assert(std::equal(_sizes, _sizes + _order, tensor.getSizes()));

		transform(tensor.begin(), std::minus<TValue>());
		return *this;
	}

	template<typename TValue>
	template<typename TScalar>
	constexpr Tensor<TValue>& Tensor<TValue>::operator*=(const TScalar& scalar)
	{
		transform([&](const TValue& x) { return x * scalar; });
		return *this;
	}

	template<typename TValue>
	template<typename TScalar>
	constexpr Tensor<TValue>& Tensor<TValue>::operator/=(const TScalar& scalar)
	{
		transform([&](const TValue& x) { return x / scalar; });
		return *this;
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::negate()
	{
		transform(std::negate<TValue>());
	}

	template<typename TValue>
	template<CTensor<TValue> TTensorA, CTensor<TValue> TTensorB>
	constexpr void Tensor<TValue>::tensorProduct(const TTensorA& tensorA, const TTensorB& tensorB)
	{
		const uint64_t orderA = tensorA.getOrder();
		const uint64_t orderB = tensorB.getOrder();
		const uint64_t* sizesA = tensorA.getSizes();
		const uint64_t* sizesB = tensorB.getSizes();

		assert(orderA + orderB == _order);
		assert(std::equal(sizesA, sizesA + orderA, _sizes));
		assert(std::equal(sizesB, sizesB + orderB, _sizes + orderA));

		const uint64_t length = tensorA.getElementCount();

		TValue* it = _values;
		for (uint64_t i = 0, j = 0, k = 0; i < _length; ++i, ++k, ++it)
		{
			if (k == length)
			{
				k = 0;
				++j;
			}

			*it = tensorA.get(j) * tensorB.get(k);
		}
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr void Tensor<TValue>::hadamardProduct(const TTensor& tensor)
	{
		assert(_order == tensor.getOrder());
		assert(std::equal(_sizes, _sizes + _order, tensor.getSizes()));

		transform(tensor.begin(), std::multiplies<TValue>());
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::fft()
	{
		if constexpr (CComplex<TValue>)
		{
			TValue** bases = new TValue*[_order];
			for (uint64_t i = 0; i < _order; ++i)
			{
				bases[i] = new TValue[_sizes[i]];

				TValue x = std::exp(TValue(0, -2 * std::numbers::pi / _sizes[i]));
				bases[i][0] = 1;
				for (uint64_t j = 1; j < _sizes[i]; ++j)
				{
					bases[i][j] = x * bases[i][j - 1];
				}
			}

			_ndCooleyTukey(_values, _order, bases);

			for (uint64_t i = 0; i < _order; ++i)
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
			TValue** bases = new TValue * [_order];
			for (uint64_t i = 0; i < _order; ++i)
			{
				bases[i] = new TValue[_sizes[i]];

				TValue x = std::exp(TValue(0, 2 * std::numbers::pi / _sizes[i]));
				bases[i][0] = 1;
				for (uint64_t j = 1; j < _sizes[i]; ++j)
				{
					bases[i][j] = x * bases[i][j - 1];
				}
			}

			_ndCooleyTukey(_values, _order, bases);

			for (uint64_t i = 0; i < _order; ++i)
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
	template<BorderBehaviour BBehaviour, CTensor<TValue> TTensor>
	constexpr void Tensor<TValue>::convolution(const TTensor& kernel)
	{
		assert(_order == kernel.getOrder());
		
		const TensorShape shape{ _order, _sizes };
		const TensorShape kernelShape{ kernel.getOrder(), kernel.getSizes() };
		
		// Do a copy of *this
		Tensor<TValue> tensor(*this);
		
		// Check that the kernel's sizes are odd
		for (uint64_t i = 0; i < _order; i++)
		{
			assert(kernelShape.sizes[i] % 2 == 1);
			assert(kernelShape.sizes[i] <= _sizes[i]);
		}
		
		// Compute offset (to center the kernel)
		int64_t* offset = reinterpret_cast<int64_t*>(alloca(_order * sizeof(int64_t)));
		for (uint64_t i = 0; i < _order; i++)
		{
			offset[i] = static_cast<int64_t>(kernelShape.sizes[i] / 2);
		}
		
		// For each element of the original tensor
		int64_t* offsetedIndices = reinterpret_cast<int64_t*>(alloca(_order * sizeof(int64_t)));
		for (const TensorPosition& pos : shape)
		{
			TValue value = 0;
		
			// For each element of the kernel
			for (const TensorPosition& kernelPos : kernelShape)
			{
				bool setToZero = false;
		
				int64_t* itOffsetedIndices = offsetedIndices;
				const uint64_t* itSizes = _sizes;
				const int64_t* itOffset = offset;
				const uint64_t* itIndices = pos.indices;
				const uint64_t* itKernelIndices = kernelPos.indices;
		
				// Compute the corresponding indices to poll
				for (uint64_t k = 0; k < _order; ++k, ++itKernelIndices, ++itOffsetedIndices, ++itSizes, ++itOffset, ++itIndices)
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

	namespace _scp
	{
		template<typename TValue, CTensor<TValue> TTensor, typename TScalar>
		constexpr TValue lerp(const TTensor& tensor, const uint64_t& order, const uint64_t* sizes, uint64_t* indices, const TScalar* coeffs, uint64_t n)
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

		template<typename TValue, CTensor<TValue> TTensor, typename TScalar>
		constexpr TValue cerp(const TTensor& tensor, const uint64_t& order, const uint64_t* sizes, uint64_t* indices, const TScalar* coeffs, uint64_t n)
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
	template<typename TScalar, InterpolationMethod IMethod, CTensor<TValue> TTensor>
	constexpr void Tensor<TValue>::interpolation(const TTensor& tensor)
	{
		const TensorShape shape{ _order, _sizes };
		const TensorShape tensorShape{ tensor.getOrder(), tensor.getSizes() };
		
		assert(shape.order == tensorShape.order);
		
		uint64_t* indices = reinterpret_cast<uint64_t*>(alloca(_order * sizeof(uint64_t)));
		TScalar* coeffs = reinterpret_cast<TScalar*>(alloca(_order * sizeof(TScalar)));

		TScalar* sizesRatio = reinterpret_cast<TScalar*>(alloca(_order * sizeof(TScalar)));
		for (uint64_t i = 0; i < _order; ++i)
		{
			sizesRatio[i] = static_cast<TScalar>(tensorShape.sizes[i] - 1) / (_sizes[i] - 1);
		}
		
		for (const TensorPosition& pos : shape)
		{
			for (uint64_t i = 0; i < _order; ++i)
			{
				coeffs[i] = pos.indices[i] * sizesRatio[i];
				indices[i] = static_cast<uint64_t>(coeffs[i]);
				coeffs[i] -= indices[i];
			}
		
			if constexpr (IMethod == InterpolationMethod::Nearest)
			{
				_values[pos.index] = tensor.get(indices);
			}
			else if constexpr (IMethod == InterpolationMethod::Linear)
			{
				_values[pos.index] = _scp::lerp<TValue>(tensor, tensorShape.order, tensorShape.sizes, indices, coeffs, 0);
			}
			else if constexpr (IMethod == InterpolationMethod::Cubic)
			{
				_values[pos.index] = _scp::cerp<TValue>(tensor, tensorShape.order, tensorShape.sizes, indices, coeffs, 0);
			}
		}
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr void Tensor<TValue>::tensorContraction(const TTensor& tensor, uint64_t i, uint64_t j)
	{
		const TensorShape shape{ _order, _sizes };
		const TensorShape tensorShape{ tensor.getOrder(), tensor.getSizes() };

		assert(tensorShape.order > 2);
		assert(_order == tensorShape.order - 2);
		assert(i != j);
		assert(i < tensorShape.order);
		assert(j < tensorShape.order);
		assert(tensorShape.sizes[i] == tensorShape.sizes[j]);

		if (i > j)
		{
			std::swap(i, j);
		}

		assert(i == 0 || std::equal(_sizes, _sizes + i, tensorShape.sizes));
		assert(j == i + 1 || std::equal(_sizes + i, _sizes + j - 1, tensorShape.sizes + i + 1));
		assert(j == tensorShape.order - 1 || std::equal(_sizes + j - 1, _sizes + _order, tensorShape.sizes + j + 1));
		
		uint64_t* indices = reinterpret_cast<uint64_t*>(alloca(shape.order * sizeof(uint64_t)));
		for (const TensorPosition& pos : shape)
		{
			if (i != 0)
			{
				std::copy(pos.indices, pos.indices + i, indices);
			}
			if (i != j - 1)
			{
				std::copy(pos.indices + i, pos.indices + j - 1, indices + i + 1);
			}
			if (j != shape.order - 1)
			{
				std::copy(pos.indices + j - 1, pos.indices + _order, indices + j + 1);
			}
		
			_values[pos.index] = 0;
			for (uint64_t k = 0; k < tensorShape.sizes[i]; ++k)
			{
				indices[i] = k;
				indices[j] = k;
				_values[pos.index] += tensor.get(indices);
			}
		}
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr bool Tensor<TValue>::operator==(const TTensor& tensor) const
	{
		if (_order != tensor.getOrder())
		{
			return false;
		}

		if (!std::equal(_sizes, _sizes + _order, tensor.getSizes()))
		{
			return false;
		}

		return std::equal(_values, _values + _length, tensor.begin());
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr bool Tensor<TValue>::operator!=(const TTensor& tensor) const
	{
		return !operator==(tensor);
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr TValue Tensor<TValue>::innerProduct(const TTensor& tensor) const
	{
		assert(_order == tensor.getOrder());
		assert(std::equal(_sizes, _sizes + _order, tensor.getSizes()));

		return std::inner_product(_values, _values + _length, tensor.begin(), TValue(0));
	}

	template<typename TValue>
	constexpr TValue Tensor<TValue>::norm() const
	{
		return std::inner_product(_values, _values + _length, _values, TValue(0));
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::minElement(const std::function<bool(const TValue&, const TValue&)>& compare) const
	{
		return *std::min_element(_values, _values + _length, compare);
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::maxElement(const std::function<bool(const TValue&, const TValue&)>& compare) const
	{
		return *std::max_element(_values, _values + _length, compare);
	}

	template<typename TValue>
	template<BorderBehaviour BBehaviour>
	constexpr const TValue& Tensor<TValue>::getOutOfBound(const int64_t* indices) const
	{
		if constexpr (BBehaviour == BorderBehaviour::Zero)
		{
			static constexpr TValue zero = 0;

			for (uint64_t i = 0; i < _order; ++i)
			{
				if (indices[i] < 0 || indices[i] >= _sizes[i])
				{
					return zero;
				}
			}

			return get(reinterpret_cast<const uint64_t*>(indices));
		}
		else if constexpr (BBehaviour == BorderBehaviour::Continuous)
		{
			uint64_t* realIndices = reinterpret_cast<uint64_t*>(alloca(sizeof(uint64_t) * _order));

			for (uint64_t i = 0; i < _order; ++i)
			{
				realIndices[i] = indices[i] & -(indices[i] > 0);
				realIndices[i] = (realIndices[i] | -(realIndices[i] >= _sizes[i])) & ((_sizes[i] - 1) | -(realIndices[i] < _sizes[i]));
			}

			return get(realIndices);
		}
		else if constexpr (BBehaviour == BorderBehaviour::Periodic)
		{
			uint64_t* realIndices = reinterpret_cast<uint64_t*>(alloca(sizeof(uint64_t) * _order));

			for (uint64_t i = 0; i < _order; ++i)
			{
				if (indices[i] < 0)
				{
					realIndices[i] = (indices[i] % _sizes[i]) + _sizes[i];
				}
				else if (indices[i] >= _sizes[i])
				{
					realIndices[i] = indices[i] % _sizes[i];
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
		assert(indices.size() == _order);
		return getOutOfBound<BBehaviour>(indices.begin());
	}

	template<typename TValue>
	template<typename TScalar, InterpolationMethod IMethod>
	constexpr TValue Tensor<TValue>::getInterpolated(const TScalar* scalarIndices) const
	{
		// TODO: Handle different border behaviours ?

		uint64_t* indices = reinterpret_cast<uint64_t*>(alloca(_order * sizeof(uint64_t)));
		TScalar* coeffs = reinterpret_cast<TScalar*>(alloca(_order * sizeof(TScalar)));

		for (uint64_t i = 0; i < _order; ++i)
		{
			if (scalarIndices[i] < 0)
			{
				indices[i] = 0;
				coeffs[i] = 0;
			}
			else if (scalarIndices[i] >= _sizes[i])
			{
				indices[i] = _sizes[i] - 1;
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
			return _scp::lerp<TValue>(*this, _order, _sizes, indices, coeffs, 0);
		}
		else if constexpr (IMethod == InterpolationMethod::Cubic)
		{
			return _scp::cerp<TValue>(*this, _order, _sizes, indices, coeffs, 0);
		}
	}

	template<typename TValue>
	template<typename TScalar, InterpolationMethod IMethod>
	constexpr TValue Tensor<TValue>::getInterpolated(const std::initializer_list<TScalar>& scalarIndices) const
	{
		assert(scalarIndices.size() == _order);
		return getInterpolated<TScalar, IMethod>(scalarIndices.begin());
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
	constexpr const TValue& Tensor<TValue>::get(uint64_t index) const
	{
		assert(index < _length);
		return _values[index];
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::get(const uint64_t* indices) const
	{
		const TensorShape shape{ _order, _sizes };
		assert(shape.getIndex(indices) < _length);
		return _values[shape.getIndex(indices)];
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::get(const std::initializer_list<uint64_t>& indices) const
	{
		const TensorShape shape{ _order, _sizes };
		assert(shape.getIndex(indices.begin()) < _length);
		return _values[shape.getIndex(indices.begin())];
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::set(uint64_t index, const TValue& value)
	{
		(*this)[index] = value;
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::set(const uint64_t* indices, const TValue& value)
	{
		const TensorShape shape{ _order, _sizes };
		assert(shape.getIndex(indices) < _length);
		_values[shape.getIndex(indices)] = value;
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::set(const std::initializer_list<uint64_t>& indices, const TValue& value)
	{
		(*this)[indices] = value;
	}

	template<typename TValue>
	constexpr uint64_t Tensor<TValue>::getOrder() const
	{
		return _order;
	}

	template<typename TValue>
	constexpr const uint64_t* Tensor<TValue>::getSizes() const
	{
		return _sizes;
	}

	template<typename TValue>
	constexpr uint64_t Tensor<TValue>::getSize(uint64_t i) const
	{
		assert(i < _order);
		return _sizes[i];
	}

	template<typename TValue>
	constexpr uint64_t Tensor<TValue>::getElementCount() const
	{
		return _length;
	}

	template<typename TValue>
	constexpr TValue& Tensor<TValue>::operator[](uint64_t index)
	{
		assert(index < _length);
		return _values[index];
	}

	template<typename TValue>
	constexpr TValue& Tensor<TValue>::operator[](const std::initializer_list<uint64_t>& indices)
	{
		const TensorShape shape{ _order, _sizes };
		assert(shape.getIndex(indices.begin()) < _length);
		return _values[shape.getIndex(indices.begin())];
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::operator[](uint64_t index) const
	{
		assert(index < _length);
		return _values[index];
	}

	template<typename TValue>
	constexpr const TValue& Tensor<TValue>::operator[](const std::initializer_list<uint64_t>& indices) const
	{
		const TensorShape shape{ _order, _sizes };
		assert(shape.getIndex(indices.begin()) < _length);
		return _values[shape.getIndex(indices.begin())];
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
		const TensorShape shape{ _order, _sizes };
		assert(shape.getIndex(indices) < _length);
		return _values[shape.getIndex(indices)];
	}

	template<typename TValue>
	constexpr TValue& Tensor<TValue>::get(const std::initializer_list<uint64_t>& indices)
	{
		const TensorShape shape{ _order, _sizes };
		assert(shape.getIndex(indices.begin()) < _length);
		return _values[shape.getIndex(indices.begin())];
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
		_destroy();
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::_create(uint64_t order, const uint64_t* sizes)
	{
		assert(order != 0);
		assert(std::find(sizes, sizes + order, 0) == sizes + order);

		_order = order;

		_length = std::accumulate(sizes, sizes + order, 1, std::multiplies<uint64_t>());

		_sizes = new uint64_t[_order];
		std::copy_n(sizes, _order, _sizes);

		_values = new TValue[_length];

		_owner = true;
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr void Tensor<TValue>::_copyFrom(const TTensor& tensor)
	{
		const uint64_t tensorOrder = tensor.getOrder();
		const uint64_t* tensorSizes = tensor.getSizes();

		if (_order != tensorOrder || !std::equal(_sizes, _sizes + _order, tensorSizes))
		{
			_destroy();
			_create(tensorOrder, tensorSizes);
		}

		std::copy_n(tensor.begin(), _length, _values);
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr void Tensor<TValue>::_moveFrom(TTensor&& tensor)
	{
		if constexpr (!std::derived_from<TTensor, Tensor<TValue>>)
		{
			_copyFrom(tensor);
			return;
		}

		if (!_owner || !tensor._owner)
		{
			_copyFrom(tensor);
			return;
		}

		_destroy();

		_order = tensor._order;
		_length = tensor._length;
		_sizes = tensor._sizes;
		_values = tensor._values;

		tensor._values = nullptr;
	}

	template<typename TValue>
	constexpr void Tensor<TValue>::_destroy()
	{
		if (_values)
		{
			if (_owner)
			{
				delete[] _values;
			}

			delete[] _sizes;
		}

		_order = 0;
		_length = 0;
		_sizes = nullptr;
		_values = nullptr;
		_owner = true;
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
		const uint64_t& size = *(_sizes + _order - order);
		
		const uint64_t subLength = std::accumulate(_sizes + _order - order + 1, _sizes + _order, 1, std::multiplies<uint64_t>());
		
		if (order > 1)
		{
			for (uint64_t i = 0; i < size; ++i)
			{
				_ndCooleyTukey(beg + i * subLength, order - 1, bases);
			}
		}

		if (size > 1)
		{
			const TValue* base = bases[_order - order];

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


	SCP_MATRIX_DEF(template<typename TValue>, Matrix, Matrix<TValue>)

	template<typename TValue>
	constexpr Matrix<TValue>* Matrix<TValue>::createAroundMemory(uint64_t row, uint64_t col, TValue* memory)
	{
		assert(row != 0 && col != 0);
		assert(memory);

		Matrix<TValue>* matrix = new Matrix<TValue>();

		matrix->_order = 2;

		matrix->_length = row * col;

		matrix->_sizes = new uint64_t[2];
		matrix->_sizes[0] = row;
		matrix->_sizes[1] = col;

		matrix->_values = memory;

		matrix->_owner = false;

		return matrix;
	}

	template<typename TValue>
	template<CTensor<TValue> TTensorA, CTensor<TValue> TTensorB>
	constexpr void Matrix<TValue>::matrixProduct(const TTensorA& matrixA, const TTensorB& matrixB)
	{
		const uint64_t* sizesA = matrixA.getSizes();
		const uint64_t* sizesB = matrixB.getSizes();

		assert(matrixA.getOrder() == 2);
		assert(matrixB.getOrder() == 2);
		assert(sizesA[1] == sizesB[0]);
		assert(sizesA[0] == _sizes[0]);
		assert(sizesB[1] == _sizes[1]);

		TValue* it = _values;
		uint64_t a, b;
		for (uint64_t i = 0; i < _length; ++i, ++it)
		{
			*it = 0;

			b = i % sizesA[0];
			a = i - b;
			for (uint64_t k = 0; k < sizesA[1]; ++k, ++a, b += sizesB[1])
			{
				*it += matrixA.get(a) * matrixB.get(b);
			}
		}
	}

	template<typename TValue>
	constexpr void Matrix<TValue>::transpose()
	{
		if (_sizes[0] == _sizes[1])
		{
			const uint64_t& size = _sizes[0];

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
			std::vector<bool> visited(_length, false);
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
				j = (i % _sizes[0]) * _sizes[1] + i / _sizes[0];

				while (j != n)
				{
					_values[i] = _values[j];
					visited[j] = true;

					i = j;
					j = (i % _sizes[0]) * _sizes[1] + i / _sizes[0];
				}

				_values[i] = tmp;
			}

			std::swap(_sizes[0], _sizes[1]);
		}
	}

	template<typename TValue>
	constexpr void Matrix<TValue>::inverse()
	{
		assert(_sizes[0] == _sizes[1]);

		static constexpr TValue _zero = 0;
		static constexpr TValue _one = 1;

		const uint64_t size = _sizes[0];
		Matrix<ValueType> copy(*this);

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
		assert(_sizes[0] == _sizes[1]);

		static constexpr TValue _zero = 0;
		static constexpr TValue _one = 1;

		TValue det = _one;

		const uint64_t size = _sizes[0];
		Matrix<ValueType> copy(*this);

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


	SCP_VECTOR_DEF(template<typename TValue>, Vector, Vector<TValue>)

	template<typename TValue>
	constexpr Vector<TValue>* Vector<TValue>::createAroundMemory(uint64_t size, TValue* memory)
	{
		assert(size != 0);
		assert(memory);

		Vector<TValue>* vector = new Vector<TValue>();

		vector->_order = 2;

		vector->_length = size;

		vector->_sizes = new uint64_t[1];
		vector->_sizes[0] = size;

		vector->_values = memory;

		vector->_owner = false;

		return vector;
	}

	template<typename TValue>
	template<CTensor<TValue> TTensorA, CTensor<TValue> TTensorB>
	constexpr void Vector<TValue>::rightMatrixProduct(const TTensorA& vector, const TTensorB& matrix) const
	{
		assert(vector.getOrder() == 1);
		assert(matrix.getOrder() == 2);
		assert(matrix.getSize(0) == vector.getSize(0));
		assert(matrix.getSize(1) == _length);

		std::fill_n(_values, _length, 0);

		const uint64_t n = matrix.getElementCount();

		uint64_t j = 0;
		const TValue* x = &vector.get(j);

		TValue* it = _values;
		const TValue* const itEnd = it + _length;
		for (uint64_t i = 0; i < n; ++i, ++it)
		{
			if (it == itEnd)
			{
				it = _values;
				x = &vector.get(++j);
			}

			*it += *x * matrix.get(i);
		}
	}

	template<typename TValue>
	template<CTensor<TValue> TTensorA, CTensor<TValue> TTensorB>
	constexpr void Vector<TValue>::leftMatrixProduct(const TTensorA& matrix, const TTensorB& vector) const
	{
		assert(vector.getOrder() == 1);
		assert(matrix.getOrder() == 2);
		assert(matrix.getSize(0) == _length);
		assert(matrix.getSize(1) == vector.getSize(0));

		const uint64_t m = vector.getSize(0);
		const uint64_t n = matrix.getElementCount();

		uint64_t j = 0;
		TValue* it = _values;
		*it = 0;
		for (uint64_t i = 0, j = 0; i < n; ++i, ++j)
		{
			if (j == m)
			{
				j = 0;
				++it;
				*it = 0;
			}

			*it += matrix.get(i) * vector.get(j);
		}
	}

	template<typename TValue>
	template<CTensor<TValue> TTensor>
	constexpr void Vector<TValue>::crossProduct(const TTensor& vector)
	{
		assert(_length == 3);
		assert(vector.getOrder() == 1);
		assert(vector.getSize(0) == 3);
		
		const TValue xA = _values[0];
		const TValue yA = _values[1];
		const TValue zA = _values[2];
		
		const TValue& xB = vector.get(0ULL);
		const TValue& yB = vector.get(1ULL);
		const TValue& zB = vector.get(2ULL);
		
		_values[0] = yA * zB - zA * yB;
		_values[1] = zA * xB - xA * zB;
		_values[2] = xA * yB - yA * xB;
	}
}
