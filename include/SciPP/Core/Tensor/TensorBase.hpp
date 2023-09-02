///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>

#pragma region scpTensorMacros

#define SCP_TENSOR_DECL(TensorName, This)																					\
																															\
public:																														\
																															\
	using IsTensor = bool;																									\
	using ValueType = TValue;																								\
																															\
	constexpr TensorName(uint64_t order, const uint64_t* sizes);															\
	constexpr TensorName(uint64_t order, const uint64_t* sizes, const TValue& value);										\
	constexpr TensorName(uint64_t order, const uint64_t* sizes, const TValue* values);										\
	constexpr TensorName(uint64_t order, const uint64_t* sizes, const std::initializer_list<TValue>& values);				\
	constexpr TensorName(const std::initializer_list<uint64_t>& sizes);														\
	constexpr TensorName(const std::initializer_list<uint64_t>& sizes, const TValue& value);								\
	constexpr TensorName(const std::initializer_list<uint64_t>& sizes, const TValue* values);								\
	constexpr TensorName(const std::initializer_list<uint64_t>& sizes, const std::initializer_list<TValue>& values);		\
	constexpr TensorName(const This& tensor);																				\
	constexpr TensorName(This&& tensor);																					\
	template<CTensor<TValue> TTensor> constexpr TensorName(const TTensor& tensor);											\
	template<CTensor<TValue> TTensor> constexpr TensorName(TTensor&& tensor);												\
																															\
	constexpr This& operator=(const This& tensor);																			\
	constexpr This& operator=(This&& tensor);																				\
	template<CTensor<TValue> TTensor> constexpr This& operator=(const TTensor& tensor);										\
	template<CTensor<TValue> TTensor> constexpr This& operator=(TTensor&& tensor);											\
																															\
	constexpr void createNew(uint64_t order, const uint64_t* sizes);														\
	constexpr void createNew(uint64_t order, const uint64_t* sizes, const TValue& value);									\
	constexpr void createNew(uint64_t order, const uint64_t* sizes, const TValue* values);									\
	constexpr void createNew(uint64_t order, const uint64_t* sizes, const std::initializer_list<TValue>& values);			\
	constexpr void createNew(const std::initializer_list<uint64_t>& sizes);													\
	constexpr void createNew(const std::initializer_list<uint64_t>& sizes, const TValue& value);							\
	constexpr void createNew(const std::initializer_list<uint64_t>& sizes, const TValue* values);							\
	constexpr void createNew(const std::initializer_list<uint64_t>& sizes, const std::initializer_list<TValue>& values);


#define SCP_TENSOR_DEF(TemplateDecl, TensorName, This)																			\
																																\
TemplateDecl																													\
constexpr This::TensorName(uint64_t order, const uint64_t* sizes) : This()														\
{																																\
	createNew(order, sizes);																									\
}																																\
																																\
TemplateDecl																													\
constexpr This::TensorName(uint64_t order, const uint64_t* sizes, const TValue& value) : This()									\
{																																\
	createNew(order, sizes, value);																								\
}																																\
																																\
TemplateDecl																													\
constexpr This::TensorName(uint64_t order, const uint64_t* sizes, const TValue* values) : This()								\
{																																\
	createNew(order, sizes, values);																							\
}																																\
																																\
TemplateDecl																													\
constexpr This::TensorName(uint64_t order, const uint64_t* sizes, const std::initializer_list<TValue>& values) : This()			\
{																																\
	createNew(order, sizes, values);																							\
}																																\
																																\
TemplateDecl																													\
constexpr This::TensorName(const std::initializer_list<uint64_t>& sizes) : This()												\
{																																\
	createNew(sizes);																											\
}																																\
																																\
TemplateDecl																													\
constexpr This::TensorName(const std::initializer_list<uint64_t>& sizes, const TValue& value) : This()							\
{																																\
	createNew(sizes, value);																									\
}																																\
																																\
TemplateDecl																													\
constexpr This::TensorName(const std::initializer_list<uint64_t>& sizes, const TValue* values) : This()							\
{																																\
	createNew(sizes, values);																									\
}																																\
																																\
TemplateDecl																													\
constexpr This::TensorName(const std::initializer_list<uint64_t>& sizes, const std::initializer_list<TValue>& values) : This()	\
{																																\
	createNew(sizes, values);																									\
}																																\
																																\
TemplateDecl																													\
constexpr This::TensorName(const This& tensor) : This()																			\
{																																\
	_copyFrom(tensor);																											\
}																																\
																																\
TemplateDecl																													\
constexpr This::TensorName(This&& tensor) : This()																				\
{																																\
	_moveFrom(std::forward<This>(tensor));																						\
}																																\
																																\
TemplateDecl																													\
template<CTensor<TValue> TTensor>																								\
constexpr This::TensorName(const TTensor& tensor) : This()																		\
{																																\
	_copyFrom(tensor);																											\
}																																\
																																\
TemplateDecl																													\
template<CTensor<TValue> TTensor>																								\
constexpr This::TensorName(TTensor&& tensor) : This()																			\
{																																\
	_moveFrom(std::forward<TTensor>(tensor));																					\
}																																\
																																\
TemplateDecl																													\
constexpr This& This::operator=(const This& tensor)																				\
{																																\
	_copyFrom(tensor);																											\
	return *this;																												\
}																																\
																																\
TemplateDecl																													\
constexpr This& This::operator=(This&& tensor)																					\
{																																\
	_moveFrom(std::forward<This>(tensor));																						\
	return *this;																												\
}																																\
																																\
TemplateDecl																													\
template<CTensor<TValue> TTensor>																								\
constexpr This& This::operator=(const TTensor& tensor)																			\
{																																\
	_copyFrom(tensor);																											\
	return *this;																												\
}																																\
																																\
TemplateDecl																													\
template<CTensor<TValue> TTensor>																								\
constexpr This& This::operator=(TTensor&& tensor)																				\
{																																\
	_moveFrom(std::forward<TTensor>(tensor));																					\
	return *this;																												\
}																																\
																																\
TemplateDecl																													\
constexpr void This::createNew(uint64_t order, const uint64_t* sizes)															\
{																																\
	assert(order != 0);																											\
	for (uint64_t i = 0; i < order; ++i)																						\
	{																															\
		assert(sizes[i] != 0);																									\
	}																															\
																																\
	if (order != getOrder() || !std::equal(sizes, sizes + order, getSizes()))													\
	{																															\
		_destroy();																												\
		_create(order, sizes);																									\
	}																															\
}																																\
																																\
TemplateDecl																													\
constexpr void This::createNew(uint64_t order, const uint64_t* sizes, const TValue& value)										\
{																																\
	createNew(order, sizes);																									\
	fill(value);																												\
}																																\
																																\
TemplateDecl																													\
constexpr void This::createNew(uint64_t order, const uint64_t* sizes, const TValue* values)										\
{																																\
	createNew(order, sizes);																									\
	copy(values);																												\
}																																\
																																\
TemplateDecl																													\
constexpr void This::createNew(uint64_t order, const uint64_t* sizes, const std::initializer_list<TValue>& values)				\
{																																\
	assert(values.size() == getElementCount());																					\
																																\
	createNew(order, sizes);																									\
	copy(values.begin());																										\
}																																\
																																\
TemplateDecl																													\
constexpr void This::createNew(const std::initializer_list<uint64_t>& sizes)													\
{																																\
	createNew(sizes.size(), sizes.begin());																						\
}																																\
																																\
TemplateDecl																													\
constexpr void This::createNew(const std::initializer_list<uint64_t>& sizes, const TValue& value)								\
{																																\
	createNew(sizes.size(), sizes.begin(), value);																				\
}																																\
																																\
TemplateDecl																													\
constexpr void This::createNew(const std::initializer_list<uint64_t>& sizes, const TValue* values)								\
{																																\
	createNew(sizes.size(), sizes.begin(), values);																				\
}																																\
																																\
TemplateDecl																													\
constexpr void This::createNew(const std::initializer_list<uint64_t>& sizes, const std::initializer_list<TValue>& values)		\
{																																\
	createNew(sizes.size(), sizes.begin(), values);																				\
}



#define SCP_MATRIX_DECL(MatrixName, This, TensorSuper)												\
																									\
public:																								\
																									\
	using IsMatrix = bool;																			\
	using Super = TensorSuper;																		\
	using ValueType = TValue;																		\
																									\
	constexpr MatrixName(uint64_t row, uint64_t col);												\
	constexpr MatrixName(uint64_t row, uint64_t col, const TValue& value);							\
	constexpr MatrixName(uint64_t row, uint64_t col, const TValue* values);							\
	constexpr MatrixName(uint64_t row, uint64_t col, const std::initializer_list<TValue>& values);	\
	constexpr MatrixName(const This& matrix);														\
	constexpr MatrixName(This&& matrix);															\
	template<CTensor<TValue> TTensor> constexpr MatrixName(const TTensor& tensor);					\
	template<CTensor<TValue> TTensor> constexpr MatrixName(TTensor&& tensor);						\
																									\
	constexpr This& operator=(const This& matrix);													\
	constexpr This& operator=(This&& matrix);														\
	template<CTensor<TValue> TTensor> constexpr This& operator=(const TTensor& tensor);				\
	template<CTensor<TValue> TTensor> constexpr This& operator=(TTensor&& tensor);


#define SCP_MATRIX_DEF(TemplateDecl, MatrixName, This)																				\
																																	\
TemplateDecl																														\
constexpr This::MatrixName(uint64_t row, uint64_t col) : Super({ row, col })														\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::MatrixName(uint64_t row, uint64_t col, const TValue& value) : Super({ row, col }, value)							\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::MatrixName(uint64_t row, uint64_t col, const TValue* values) : Super({ row, col }, values)							\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::MatrixName(uint64_t row, uint64_t col, const std::initializer_list<TValue>& values) : Super({ row, col }, values)	\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::MatrixName(const This& matrix) : Super(matrix)																		\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::MatrixName(This&& matrix) : Super(std::forward<This>(matrix))														\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
template<CTensor<TValue> TTensor>																									\
constexpr This::MatrixName(const TTensor& tensor) : Super(tensor)																	\
{																																	\
	assert(tensor.getOrder() == 2);																									\
}																																	\
																																	\
TemplateDecl																														\
template<CTensor<TValue> TTensor>																									\
constexpr This::MatrixName(TTensor&& tensor) : Super(std::forward<TTensor>(tensor))													\
{																																	\
	assert(tensor.getOrder() == 2);																									\
}																																	\
																																	\
TemplateDecl																														\
constexpr This& This::operator=(const This& matrix)																					\
{																																	\
	return dynamic_cast<This&>(Super::operator=(matrix));																			\
}																																	\
																																	\
TemplateDecl																														\
constexpr This& This::operator=(This&& matrix)																						\
{																																	\
	return dynamic_cast<This&>(Super::operator=(std::forward<This>(matrix)));														\
}																																	\
																																	\
TemplateDecl																														\
template<CTensor<TValue> TTensor>																									\
constexpr This& This::operator=(const TTensor& tensor)																				\
{																																	\
	assert(tensor.getOrder() == 2);																									\
	return dynamic_cast<This&>(Super::operator=(tensor));																			\
}																																	\
																																	\
TemplateDecl																														\
template<CTensor<TValue> TTensor>																									\
constexpr This& This::operator=(TTensor&& tensor)																					\
{																																	\
	assert(tensor.getOrder() == 2);																									\
	return dynamic_cast<This&>(Super::operator=(std::forward<TTensor>(tensor)));													\
}


#define SCP_VECTOR_DECL(VectorName, This, TensorSuper)												\
																									\
public:																								\
																									\
	using IsVector = bool;																			\
	using Super = TensorSuper;																		\
	using ValueType = TValue;																		\
																									\
	constexpr VectorName(uint64_t size);															\
	constexpr VectorName(uint64_t size, const TValue& value);										\
	constexpr VectorName(uint64_t size, const TValue* values);										\
	constexpr VectorName(const std::initializer_list<TValue>& values);								\
	constexpr VectorName(const This& vector);														\
	constexpr VectorName(This&& vector);															\
	template<CTensor<TValue> TTensor> constexpr VectorName(const TTensor& tensor);					\
	template<CTensor<TValue> TTensor> constexpr VectorName(TTensor&& tensor);						\
																									\
	constexpr This& operator=(const This& vector);													\
	constexpr This& operator=(This&& vector);														\
	template<CTensor<TValue> TTensor> constexpr This& operator=(const TTensor& tensor);				\
	template<CTensor<TValue> TTensor> constexpr This& operator=(TTensor&& tensor);


#define SCP_VECTOR_DEF(TemplateDecl, VectorName, This)																				\
																																	\
TemplateDecl																														\
constexpr This::VectorName(uint64_t size) : Super(1, &size)																			\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::VectorName(uint64_t size, const TValue& value) : Super(1, &size, value)												\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::VectorName(uint64_t size, const TValue* values) : Super(1, &size, values)											\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::VectorName(const std::initializer_list<TValue>& values) : Super({ values.size() }, values.begin())					\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::VectorName(const This& vector) : Super(vector)																		\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
constexpr This::VectorName(This&& vector) : Super(std::forward<This>(vector))														\
{																																	\
}																																	\
																																	\
TemplateDecl																														\
template<CTensor<TValue> TTensor>																									\
constexpr This::VectorName(const TTensor& tensor) : Super(tensor)																	\
{																																	\
	assert(tensor.getOrder() == 1);																									\
}																																	\
																																	\
TemplateDecl																														\
template<CTensor<TValue> TTensor>																									\
constexpr This::VectorName(TTensor&& tensor) : Super(std::forward<TTensor>(tensor))													\
{																																	\
	assert(tensor.getOrder() == 1);																									\
}																																	\
																																	\
TemplateDecl																														\
constexpr This& This::operator=(const This& vector)																					\
{																																	\
	return dynamic_cast<This&>(Super::operator=(vector));																			\
}																																	\
																																	\
TemplateDecl																														\
constexpr This& This::operator=(This&& vector)																						\
{																																	\
	return dynamic_cast<This&>(Super::operator=(std::forward<This>(vector)));														\
}																																	\
																																	\
TemplateDecl																														\
template<CTensor<TValue> TTensor>																									\
constexpr This& This::operator=(const TTensor& tensor)																				\
{																																	\
	assert(tensor.getOrder() == 1);																									\
	return dynamic_cast<This&>(Super::operator=(tensor));																			\
}																																	\
																																	\
TemplateDecl																														\
template<CTensor<TValue> TTensor>																									\
constexpr This& This::operator=(TTensor&& tensor)																					\
{																																	\
	assert(tensor.getOrder() == 1);																									\
	return dynamic_cast<This&>(Super::operator=(std::forward<TTensor>(tensor)));													\
}

#pragma endregion

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

	struct TensorPosition
	{
		uint64_t* indices;
		uint64_t index;
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
		const uint64_t* sizes;

		constexpr uint64_t getIndex(const uint64_t* indices) const;
		constexpr uint64_t getIndex(const std::initializer_list<uint64_t>& indices) const;
		constexpr void getIndices(uint64_t index, uint64_t* indices) const;
		constexpr uint64_t getElementCount() const;

		constexpr TensorShapeIterator begin() const;
		constexpr TensorShapeIterator end() const;
	};

	template<CUntypedTensor TTensor>
	constexpr TTensor operator+(const TTensor& a, const TTensor& b);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator+(TTensor&& a, const TTensor& b);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator+(const TTensor& a, TTensor&& b);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator+(TTensor&& a, TTensor&& b);
	
	template<CUntypedTensor TTensor>
	constexpr TTensor operator-(const TTensor& a, const TTensor& b);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator-(TTensor&& a, const TTensor& b);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator-(const TTensor& a, TTensor&& b);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator-(TTensor&& a, TTensor&& b);
	
	template<CUntypedTensor TTensor>
	constexpr TTensor operator*(const TTensor& tensor, const typename TTensor::ValueType& value);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator*(TTensor&& tensor, const typename TTensor::ValueType& value);
	template<CUntypedTensor TTensor>
	constexpr TTensor operator*(const typename TTensor::ValueType& value, const TTensor& tensor);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator*(const typename TTensor::ValueType& value, TTensor&& tensor);
	
	template<CUntypedTensor TTensor>
	constexpr TTensor operator/(const TTensor& tensor, const typename TTensor::ValueType& value);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator/(TTensor&& tensor, const typename TTensor::ValueType& value);
	
	template<CUntypedTensor TTensor>
	constexpr TTensor operator-(const TTensor& a);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator-(TTensor&& a);
	
	template<CUntypedTensor TTensor>
	constexpr TTensor operator+(const TTensor& a);
	template<CUntypedTensor TTensor>
	constexpr TTensor&& operator+(TTensor&& a);

	template<CUntypedMatrix TMatrix>
	TMatrix operator*(const TMatrix& a, const TMatrix& b);

	template<CUntypedVector TVector, CUntypedMatrix TMatrix>
	TVector operator*(const TVector& vector, const TMatrix& matrix);
	template<CUntypedMatrix TMatrix, CUntypedVector TVector>
	TVector operator*(const TMatrix& matrix, const TVector& vector);
}
