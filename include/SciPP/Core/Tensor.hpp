///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Pélégrin Marius
//! \copyright The MIT License (MIT)
//! \date 2019-2024
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>

namespace scp
{
	template<typename TValue>
	class Tensor
	{
		public:

			// Construction, copy and move operations

			static constexpr Tensor<TValue>* createAroundMemory(uint64_t order, const uint64_t* sizes, TValue* memory);
			static constexpr Tensor<TValue>* createAroundMemory(const std::initializer_list<uint64_t>& sizes, TValue* memory);

			constexpr Tensor(uint64_t order, const uint64_t* sizes);
			constexpr Tensor(uint64_t order, const uint64_t* sizes, const TValue& value);
			constexpr Tensor(uint64_t order, const uint64_t* sizes, const TValue* values);
			constexpr Tensor(uint64_t order, const uint64_t* sizes, const std::initializer_list<TValue>& values);
			constexpr Tensor(const std::initializer_list<uint64_t>& sizes);
			constexpr Tensor(const std::initializer_list<uint64_t>& sizes, const TValue& value);
			constexpr Tensor(const std::initializer_list<uint64_t>& sizes, const TValue* values);
			constexpr Tensor(const std::initializer_list<uint64_t>& sizes, const std::initializer_list<TValue>& values);
			constexpr Tensor(const Tensor<TValue>& tensor);
			constexpr Tensor(Tensor<TValue>&& tensor);

			constexpr Tensor<TValue>& operator=(const Tensor<TValue>& tensor);
			constexpr Tensor<TValue>& operator=(Tensor<TValue>&& tensor);

			// Operators that modifies the tensor globally

			constexpr Tensor<TValue>& operator+=(const Tensor<TValue>& tensor);
			constexpr Tensor<TValue>& operator-=(const Tensor<TValue>& tensor);
			template<typename TScalar> constexpr Tensor<TValue>& operator*=(const TScalar& scalar);
			template<typename TScalar> constexpr Tensor<TValue>& operator/=(const TScalar& scalar);
			constexpr Tensor<TValue>& negate();

			constexpr void tensorProduct(const Tensor<TValue>& tensorA, const Tensor<TValue>& tensorB);
			constexpr void hadamardProduct(const Tensor<TValue>& tensor);
			constexpr void fft();
			constexpr void ifft();

			template<BorderBehaviour BBehaviour> constexpr void convolution(const Tensor<TValue>& kernel);

			// TODO: template<typename TScalar, InterpolationMethod MagMethod, CollapseMethod MinMethod> constexpr void resize(const Tensor<TValue>& tensor);
			template<typename TScalar, InterpolationMethod IMethod> constexpr void resize(const Tensor<TValue>& tensor);
			constexpr void contract(const Tensor<TValue>& tensor, uint64_t i, uint64_t j);

			// Other standard operators

			constexpr bool operator==(const Tensor<TValue>& tensor) const;
			constexpr bool operator!=(const Tensor<TValue>& tensor) const;

			constexpr TValue* begin();
			constexpr TValue* end();
			constexpr const TValue* begin() const;
			constexpr const TValue* end() const;
			constexpr const TValue* cbegin() const;
			constexpr const TValue* cend() const;

			// Computation-involving getters and setters

			template<BorderBehaviour BBehaviour> constexpr const TValue& getOutOfBound(const int64_t* indices) const;
			template<BorderBehaviour BBehaviour> constexpr const TValue& getOutOfBound(const std::initializer_list<int64_t>& indices) const;
			template<typename TScalar, InterpolationMethod IMethod> constexpr TValue getInterpolated(const TScalar* scalarIndices) const;
			template<typename TScalar, InterpolationMethod IMethod> constexpr TValue getInterpolated(const std::initializer_list<TScalar>& scalarIndices) const;

			// Computation-free getters and setters

			constexpr TValue& operator[](uint64_t index);
			constexpr const TValue& operator[](uint64_t index) const;
			constexpr TValue& operator[](const std::initializer_list<uint64_t>& indices);
			constexpr const TValue& operator[](const std::initializer_list<uint64_t>& indices) const;

			constexpr const TValue& get(uint64_t index) const;
			constexpr const TValue& get(const uint64_t* indices) const;
			constexpr const TValue& get(const std::initializer_list<uint64_t>& indices) const;
			constexpr TValue& get(uint64_t index);
			constexpr TValue& get(const uint64_t* indices);
			constexpr TValue& get(const std::initializer_list<uint64_t>& indices);
			constexpr void set(uint64_t index, const TValue& value);
			constexpr void set(const uint64_t* indices, const TValue& value);
			constexpr void set(const std::initializer_list<uint64_t>& indices, const TValue& value);

			constexpr const TensorShape& getShape() const;
			constexpr uint64_t getOrder() const;
			constexpr const uint64_t* getSizes() const;
			constexpr uint64_t getSize(uint64_t i) const;
			constexpr uint64_t getElementCount() const;
			constexpr TValue* getData();
			constexpr const TValue* getData() const;

			// Destructor

			constexpr virtual ~Tensor();

		protected:

			constexpr Tensor();

			constexpr void _ndCooleyTukey(TValue* beg, uint64_t order, const TValue* const* bases);

			static constexpr TValue _zero = 0;
			static constexpr TValue _one = 1;
			
			TensorShape _shape;
			uint64_t _length;
			TValue* _values;

			bool _owner;

		friend class Matrix<TValue>;
		friend class Vector<TValue>;
	};

	template<typename TValue>
	constexpr Tensor<TValue> operator+(const Tensor<TValue>& tensorA, const Tensor<TValue>& tensorB);
	template<typename TValue>
	constexpr Tensor<TValue>&& operator+(Tensor<TValue>&& tensorA, const Tensor<TValue>& tensorB);
	template<typename TValue>
	constexpr Tensor<TValue>&& operator+(const Tensor<TValue>& tensorA, Tensor<TValue>&& tensorB);
	template<typename TValue>
	constexpr Tensor<TValue>&& operator+(Tensor<TValue>&& tensorA, Tensor<TValue>&& tensorB);
	
	template<typename TValue>
	constexpr Tensor<TValue> operator-(const Tensor<TValue>& tensorA, const Tensor<TValue>& tensorB);
	template<typename TValue>
	constexpr Tensor<TValue>&& operator-(Tensor<TValue>&& tensorA, const Tensor<TValue>& tensorB);
	template<typename TValue>
	constexpr Tensor<TValue>&& operator-(const Tensor<TValue>& tensorA, Tensor<TValue>&& tensorB);
	template<typename TValue>
	constexpr Tensor<TValue>&& operator-(Tensor<TValue>&& tensorA, Tensor<TValue>&& tensorB);
	
	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue> operator*(const Tensor<TValue>& tensor, const TScalar& scalar);
	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue>&& operator*(Tensor<TValue>&& tensor, const TScalar& scalar);
	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue> operator*(const TScalar& scalar, const Tensor<TValue>& tensor);
	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue>&& operator*(const TScalar& scalar, Tensor<TValue>&& tensor);
	
	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue> operator/(const Tensor<TValue>& tensor, const TScalar& scalar);
	template<typename TValue, typename TScalar>
	constexpr Tensor<TValue>&& operator/(Tensor<TValue>&& tensor, const TScalar& scalar);
	
	template<typename TValue>
	constexpr Tensor<TValue> operator-(const Tensor<TValue>& tensor);
	template<typename TValue>
	constexpr Tensor<TValue>&& operator-(Tensor<TValue>&& tensor);
	
	template<typename TValue>
	constexpr Tensor<TValue> operator+(const Tensor<TValue>& tensor);
	template<typename TValue>
	constexpr Tensor<TValue>&& operator+(Tensor<TValue>&& tensor);
}
