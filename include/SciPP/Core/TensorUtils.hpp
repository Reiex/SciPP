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
	enum class BorderBehaviour
	{
		Zero,
		Continuous,
		Periodic
	};

	enum class InterpolationMethod
	{
		Nearest,
		Linear,
		Cubic
	};

	// enum class CollapseMethod
	// {
	// 	Nearest,
	// 	Mean,
	// 	// TODO: Median
	// 	// TODO: Mode
	// };

	struct TensorPosition
	{
		uint64_t index;
		uint64_t* indices;
	};

	class TensorShapeIterator
	{
		public:

			constexpr TensorShapeIterator() = delete;
			constexpr TensorShapeIterator(const TensorShape* shape, bool end);
			constexpr TensorShapeIterator(const TensorShapeIterator& iterator);
			constexpr TensorShapeIterator(TensorShapeIterator&& iterator);

			constexpr TensorShapeIterator& operator=(const TensorShapeIterator& iterator);
			constexpr TensorShapeIterator& operator=(TensorShapeIterator&& iterator);

			constexpr const TensorPosition& operator*() const;
			constexpr const TensorPosition* operator->() const;

			constexpr TensorShapeIterator& operator++();

			constexpr bool operator==(const TensorShapeIterator& iterator) const;
			constexpr bool operator!=(const TensorShapeIterator& iterator) const;

			constexpr ~TensorShapeIterator();

		protected:

			const TensorShape* _shape;
			TensorPosition _pos;
	};

	struct TensorShape
	{
		uint64_t order;
		uint64_t* sizes;

		constexpr uint64_t getIndex(const uint64_t* indices) const;
		constexpr uint64_t getIndex(const std::initializer_list<uint64_t>& indices) const;
		constexpr void getIndices(uint64_t index, uint64_t* indices) const;
		constexpr uint64_t getElementCount() const;

		constexpr TensorShapeIterator begin() const;
		constexpr TensorShapeIterator end() const;
	};
}
