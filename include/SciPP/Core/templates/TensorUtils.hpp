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
	constexpr TensorShapeIterator::TensorShapeIterator(const TensorShape* shape, bool end) :
		_shape(shape),
		_pos{ 0, nullptr }
	{
		assert(_shape);

		_pos.indices = new uint64_t[_shape->order];
		std::fill_n(_pos.indices, _shape->order, 0);

		if (end)
		{
			_pos.indices[0] = _shape->sizes[0];
			_pos.index = _shape->getElementCount();
		}
	}

	constexpr TensorShapeIterator::TensorShapeIterator(const TensorShapeIterator& iterator) :
		_shape(iterator._shape),
		_pos{ iterator._pos.index, nullptr }
	{
		_pos.indices = new uint64_t[_shape->order];
		std::copy_n(iterator._pos.indices, _shape->order, _pos.indices);
	}

	constexpr TensorShapeIterator::TensorShapeIterator(TensorShapeIterator&& iterator) :
		_shape(iterator._shape),
		_pos{ iterator._pos.index, iterator._pos.indices }
	{
		iterator._pos.indices = nullptr;
	}

	constexpr TensorShapeIterator& TensorShapeIterator::operator=(const TensorShapeIterator& iterator)
	{
		if (_shape->order != iterator._shape->order)
		{
			delete[] _pos.indices;
			_pos.indices = new uint64_t[iterator._shape->order];
		}

		_shape = iterator._shape;
		std::copy_n(iterator._pos.indices, _shape->order, _pos.indices);
		_pos.index = iterator._pos.index;

		return *this;
	}
	
	constexpr TensorShapeIterator& TensorShapeIterator::operator=(TensorShapeIterator&& iterator)
	{
		delete[] _pos.indices;

		_shape = iterator._shape;
		_pos.index = iterator._pos.index;
		_pos.indices = iterator._pos.indices;

		iterator._pos.indices = nullptr;

		return *this;
	}

	constexpr const TensorPosition& TensorShapeIterator::operator*() const
	{
		return _pos;
	}
	
	constexpr const TensorPosition* TensorShapeIterator::operator->() const
	{
		return &_pos;
	}

	constexpr TensorShapeIterator& TensorShapeIterator::operator++()
	{
		++_pos.index;

		uint64_t i = _shape->order - 1;
		for (; _pos.indices[i] == _shape->sizes[i] - 1 && i != 0; --i)
		{
			_pos.indices[i] = 0;
		}
		++_pos.indices[i];

		return *this;
	}

	constexpr bool TensorShapeIterator::operator==(const TensorShapeIterator& iterator) const
	{
		return _pos.index == iterator._pos.index && _shape == iterator._shape;
	}
	
	constexpr bool TensorShapeIterator::operator!=(const TensorShapeIterator& iterator) const
	{
		return _pos.index != iterator._pos.index || _shape != iterator._shape;
	}

	constexpr TensorShapeIterator::~TensorShapeIterator()
	{
		if (_pos.indices)
		{
			delete[] _pos.indices;
		}
	}

	constexpr uint64_t TensorShape::getIndex(const uint64_t* indices) const
	{
		for (uint64_t i = 0; i < order; ++i)
		{
			assert(indices[i] < sizes[i]);
		}

		uint64_t result = indices[0];
		for (uint64_t i = 1; i < order; ++i)
		{
			result = result * sizes[i] + indices[i];
		}

		return result;
	}

	constexpr uint64_t TensorShape::getIndex(const std::initializer_list<uint64_t>& indices) const
	{
		assert(indices.size() == order);
		return getIndex(indices.begin());
	}
	
	constexpr void TensorShape::getIndices(uint64_t index, uint64_t* indices) const
	{
		assert(index < getElementCount());

		uint64_t factor = getElementCount();
		for (uint64_t i = 0; i < order; ++i)
		{
			factor /= sizes[i];
			indices[i] = index / factor;
			index %= factor;
		}
	}
	
	constexpr uint64_t TensorShape::getElementCount() const
	{
		return std::accumulate(sizes, sizes + order, 1, std::multiplies<uint64_t>());
	}

	constexpr TensorShapeIterator TensorShape::begin() const
	{
		return TensorShapeIterator(this, false);
	}
	
	constexpr TensorShapeIterator TensorShape::end() const
	{
		return TensorShapeIterator(this, true);
	}
}
