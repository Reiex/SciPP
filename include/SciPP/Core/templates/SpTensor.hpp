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
	// SCP_TENSOR_TENSOR_DEF(template<typename TValue>, SpTensor, SpTensor<TValue>)
	// 
	// template<typename TValue>
	// constexpr SpTensor<TValue>::SpTensor() :
	// 	_values(),
	// 	_order(0),
	// 	_sizes(nullptr),
	// 	_length(0)
	// {
	// }
	// 
	// template<typename TValue>
	// constexpr const TValue& SpTensor<TValue>::get(uint64_t index) const
	// {
	// 	assert(index < _length);
	// 
	// 	auto it = _values.find(index);
	// 	if (it != _values.end())
	// 	{
	// 		return it->second;
	// 	}
	// 	else
	// 	{
	// 		return _zero;
	// 	}
	// }
	// 
	// template<typename TValue>
	// constexpr const TValue& SpTensor<TValue>::get(const uint64_t* indices) const
	// {
	// 	const TensorShape shape{ _order, _sizes };
	// 
	// 	assert(shape.getIndex(indices) < _length);
	// 
	// 	auto it = _values.find(shape.getIndex(indices));
	// 	if (it != _values.end())
	// 	{
	// 		return it->second;
	// 	}
	// 	else
	// 	{
	// 		return _zero;
	// 	}
	// }
	// 
	// template<typename TValue>
	// constexpr const TValue& SpTensor<TValue>::get(const std::initializer_list<uint64_t>& indices) const
	// {
	// 	const TensorShape shape{ _order, _sizes };
	// 
	// 	assert(indices.size() == _order);
	// 	assert(shape.getIndex(indices.begin()) < _length);
	// 
	// 	auto it = _values.find(shape.getIndex(indices.begin()));
	// 	if (it != _values.end())
	// 	{
	// 		return it->second;
	// 	}
	// 	else
	// 	{
	// 		return _zero;
	// 	}
	// }
	// 
	// template<typename TValue>
	// constexpr void SpTensor<TValue>::set(uint64_t index, const TValue& value)
	// {
	// 	assert(index < _length);
	// 
	// 	auto it = _values.find(index);
	// 	if (it != _values.end())
	// 	{
	// 		if (value != _zero)
	// 		{
	// 			it->second = value;
	// 		}
	// 		else
	// 		{
	// 			_values.erase(it);
	// 		}
	// 	}
	// 	else if (value != _zero)
	// 	{
	// 		_values.insert({ index, value });
	// 	}
	// }
	// 
	// template<typename TValue>
	// constexpr void SpTensor<TValue>::set(const uint64_t* indices, const TValue& value)
	// {
	// 	const TensorShape shape{ _order, _sizes };
	// 
	// 	const uint64_t index = shape.getIndex(indices);
	// 	assert(index < _length);
	// 
	// 	auto it = _values.find(index);
	// 	if (it != _values.end())
	// 	{
	// 		if (value != _zero)
	// 		{
	// 			it->second = value;
	// 		}
	// 		else
	// 		{
	// 			_values.erase(it);
	// 		}
	// 	}
	// 	else if (value != _zero)
	// 	{
	// 		_values.insert({ index, value });
	// 	}
	// }
	// 
	// template<typename TValue>
	// constexpr void SpTensor<TValue>::set(const std::initializer_list<uint64_t>& indices, const TValue& value)
	// {
	// 	const TensorShape shape{ _order, _sizes };
	// 
	// 	assert(indices.size() == _order);
	// 	const uint64_t index = shape.getIndex(indices.begin());
	// 	assert(index < _length);
	// 
	// 	auto it = _values.find(index);
	// 	if (it != _values.end())
	// 	{
	// 		if (value != _zero)
	// 		{
	// 			it->second = value;
	// 		}
	// 		else
	// 		{
	// 			_values.erase(it);
	// 		}
	// 	}
	// 	else if (value != _zero)
	// 	{
	// 		_values.insert({ index, value });
	// 	}
	// }
	// 
	// template<typename TValue>
	// constexpr uint64_t SpTensor<TValue>::getOrder() const
	// {
	// 	return _order;
	// }
	// 
	// template<typename TValue>
	// constexpr const uint64_t* SpTensor<TValue>::getSizes() const
	// {
	// 	return _sizes;
	// }
	// 
	// template<typename TValue>
	// constexpr uint64_t SpTensor<TValue>::getSize(uint64_t i) const
	// {
	// 	return _sizes[i];
	// }
	// 
	// template<typename TValue>
	// constexpr uint64_t SpTensor<TValue>::getElementCount() const
	// {
	// 	return _length;
	// }
	// 
	// template<typename TValue>
	// constexpr SpTensor<TValue>::~SpTensor()
	// {
	// 	destroy();
	// }
	// 
	// template<typename TValue>
	// constexpr void SpTensor<TValue>::create(uint64_t order, const uint64_t* sizes)
	// {
	// 	assert(order != 0);
	// 	assert(std::find(sizes, sizes + order, 0) == sizes + order);
	// 
	// 	_order = order;
	// 
	// 	_sizes = new uint64_t[_order];
	// 	std::copy_n(sizes, _order, _sizes);
	// 
	// 	_length = std::accumulate(_sizes, _sizes + _order, 1, std::multiplies<uint64_t>());
	// }
	// 
	// template<typename TValue>
	// constexpr void SpTensor<TValue>::copyFrom(const TensorBase<TValue>& tensor)
	// {
	// 	const SpTensor<TValue>* spTensor = dynamic_cast<const SpTensor<TValue>*>(&tensor);
	// 	if (spTensor)
	// 	{
	// 		if (_order != spTensor->_order || !std::equal(_sizes, _sizes + _order, spTensor->_sizes))
	// 		{
	// 			destroy();
	// 			create(spTensor->_order, spTensor->_sizes);
	// 		}
	// 
	// 		_values = spTensor->_values;
	// 	}
	// 	else
	// 	{
	// 		Super::copyFrom(tensor);
	// 	}
	// }
	// 
	// template<typename TValue>
	// constexpr void SpTensor<TValue>::moveFrom(TensorBase<TValue>&& tensor)
	// {
	// 	SpTensor<TValue>* spTensor = dynamic_cast<SpTensor<TValue>*>(&tensor);
	// 	if (spTensor)
	// 	{
	// 		destroy();
	// 
	// 		_values = std::move(spTensor->_values);
	// 
	// 		_order = spTensor->_order;
	// 		_sizes = spTensor->_sizes;
	// 		_length = spTensor->_length;
	// 
	// 		spTensor->_sizes = nullptr;
	// 	}
	// 	else
	// 	{
	// 		Super::moveFrom(std::forward<TensorBase<TValue>>(tensor));
	// 	}
	// }
	// 
	// template<typename TValue>
	// constexpr void SpTensor<TValue>::destroy()
	// {
	// 	if (_sizes)
	// 	{
	// 		_values.clear();
	// 		delete[] _sizes;
	// 	}
	// 
	// 	_order = 0;
	// 	_sizes = nullptr;
	// 	_length = 0;
	// }
	// 
	// 
	// SCP_TENSOR_MATRIX_DEF(template<typename TValue>, SpMatrix, SpMatrix<TValue>)
	// 
	// 
	// SCP_TENSOR_VECTOR_DEF(template<typename TValue>, SpVector, SpVector<TValue>)
}
