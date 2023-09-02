///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>

namespace scp
{
	// template<typename TValue>
	// class SpTensor : public TensorBase<TValue>
	// {
	// 	SCP_TENSOR_TENSOR_DECL(SpTensor, SpTensor<TValue>, TensorBase<TValue>)
	// 
	// 	public:
	// 
	// 		// TODO: Overrides
	// 
	// 		constexpr virtual const TValue& get(uint64_t index) const override final;
	// 		constexpr virtual const TValue& get(const uint64_t* indices) const override final;
	// 		constexpr virtual const TValue& get(const std::initializer_list<uint64_t>& indices) const override final;
	// 		constexpr virtual void set(uint64_t index, const TValue& value) override final;
	// 		constexpr virtual void set(const uint64_t* indices, const TValue& value) override final;
	// 		constexpr virtual void set(const std::initializer_list<uint64_t>& indices, const TValue& value) override final;
	// 
	// 		constexpr virtual uint64_t getOrder() const override final;
	// 		constexpr virtual const uint64_t* getSizes() const override final;
	// 		constexpr virtual uint64_t getSize(uint64_t i) const override final;
	// 		constexpr virtual uint64_t getElementCount() const override final;
	// 
	// 		constexpr ~SpTensor();
	// 
	// 	protected:
	// 
	// 		constexpr SpTensor();
	// 
	// 		constexpr virtual void create(uint64_t order, const uint64_t* sizes) override final;
	// 		constexpr virtual void copyFrom(const TensorBase<TValue>& tensor) override final;
	// 		constexpr virtual void moveFrom(TensorBase<TValue>&& tensor) override final;
	// 		constexpr virtual void destroy() override final;
	// 
	// 		std::map<uint64_t, TValue> _values;
	// 
	// 		uint64_t _order;
	// 		uint64_t* _sizes;
	// 		uint64_t _length;
	// };
	// 
	// // TODO: template<typename TValue>
	// // TODO: constexpr TValue* begin(const Tensor<TValue>& tensor);
	// // TODO: template<typename TValue>
	// // TODO: constexpr TValue* end(const Tensor<TValue>& tensor);
	// 
	// 
	// template<typename TValue>
	// class SpMatrix : public MatrixBase<SpTensor<TValue>>
	// {
	// 	SCP_TENSOR_MATRIX_DECL(SpMatrix, SpMatrix<TValue>, MatrixBase<Tensor<TValue>>)
	// 
	// 	public:
	// 
	// 		// TODO: Overrides
	// 
	// 		constexpr virtual ~SpMatrix() = default;
	// };
	// 
	// 
	// template<typename TValue>
	// class SpVector : public VectorBase<SpTensor<TValue>>
	// {
	// 	SCP_TENSOR_VECTOR_DECL(SpVector, SpVector<TValue>, VectorBase<Tensor<TValue>>)
	// 
	// 	public:
	// 
	// 		// TODO: Overrides
	// 
	// 		constexpr virtual ~SpVector() = default;
	// };
	// 
	// template<typename TValue>
	// SpVector<TValue> operator*(const SpVector<TValue>& vector, const SpMatrix<TValue>& matrix);
}
