///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <complex>
#include <concepts>
#include <cstdint>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <map>
#include <numbers>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace scp
{
	template<typename T> concept CNumber = std::integral<T> || std::floating_point<T>;
	template<typename T> concept CComplex = requires { typename T::value_type; } && std::same_as<std::complex<typename T::value_type>, T>;

	template<typename T1, typename T2, typename R> concept CAddable = requires (T1 x1, T2 x2)
	{
		{ x1 + x2 } -> std::convertible_to<R>;
	};
	template<typename T1, typename T2, typename R> concept CSubstractable = requires (T1 x1, T2 x2)
	{
		{ x1 - x2 } -> std::convertible_to<R>;
	};
	template<typename T1, typename T2, typename R> concept CMultipliable = requires (T1 x1, T2 x2)
	{
		{ x1* x2 } -> std::convertible_to<R>;
	};
	template<typename T1, typename T2, typename R> concept CDivisible = requires (T1 x1, T2 x2)
	{
		{ x1 / x2 } -> std::convertible_to<R>;
	};

	template<typename T> concept CMonoid =
		CMultipliable<T, T, T>
		&& requires (T x)
	{
		x = 1;
	};
	template<typename T> concept CCommutativeMonoid =
		CAddable<T, T, T>
		&& requires (T x)
	{
		x = 0;
	};

	template<typename T> concept CGroup =
		CMonoid<T>
		&& CDivisible<T, T, T>;
	template<typename T> concept CCommutativeGroup =
		CCommutativeMonoid<T>
		&& CSubstractable<T, T, T>;

	template<typename T> concept CRing =
		CCommutativeGroup<T>
		&& CMonoid<T>;

	template<typename T> concept CField =
		CRing<T>
		&& CDivisible<T, T, T>;

	template<typename T, typename R> concept CModule =
		CCommutativeGroup<T>
		&& CRing<R>
		&& CMultipliable<T, R, T>
		&& CMultipliable<R, T, T>
		&& CDivisible<T, R, T>
		&& CDivisible<R, T, T>;

	template<typename T, typename F> concept CVectorSpace =
		CModule<T, F>
		&& CField<F>;

	template<typename T, typename F> concept CAlgebra =
		CVectorSpace<T, F>
		&& CMonoid<T>;
	template<typename T, typename F> concept CDivisionAlgebra =
		CVectorSpace<T, F>
		&& CGroup<T>;


	struct f32vec2; struct f32vec3; struct f32vec4;
	struct f64vec2; struct f64vec3; struct f64vec4;
	struct u8vec2; struct u8vec3; struct u8vec4;
	struct u16vec2; struct u16vec3; struct u16vec4;
	struct u32vec2; struct u32vec3; struct u32vec4;
	struct u64vec2; struct u64vec3; struct u64vec4;
	struct i8vec2; struct i8vec3; struct i8vec4;
	struct i16vec2; struct i16vec3; struct i16vec4;
	struct i32vec2; struct i32vec3; struct i32vec4;
	struct i64vec2; struct i64vec3; struct i64vec4;
	struct bvec2; struct bvec3; struct bvec4;
	template<typename T> concept CVec = requires { typename T::IsVec; };

	namespace _scp { template<typename TValue, uint8_t Row, uint8_t Col, typename TRow, typename TCol> class Mat; }
	using f32mat2x2 = _scp::Mat<float, 2, 2, f32vec2, f32vec2>; using f32mat2x3 = _scp::Mat<float, 2, 3, f32vec3, f32vec2>; using f32mat2x4 = _scp::Mat<float, 2, 4, f32vec4, f32vec2>;
	using f32mat3x2 = _scp::Mat<float, 3, 2, f32vec2, f32vec3>; using f32mat3x3 = _scp::Mat<float, 3, 3, f32vec3, f32vec3>; using f32mat3x4 = _scp::Mat<float, 3, 4, f32vec4, f32vec3>;
	using f32mat4x2 = _scp::Mat<float, 4, 2, f32vec2, f32vec4>; using f32mat4x3 = _scp::Mat<float, 4, 3, f32vec3, f32vec4>; using f32mat4x4 = _scp::Mat<float, 4, 4, f32vec4, f32vec4>;
	using f64mat2x2 = _scp::Mat<double, 2, 2, f64vec2, f64vec2>; using f64mat2x3 = _scp::Mat<double, 2, 3, f64vec3, f64vec2>; using f64mat2x4 = _scp::Mat<double, 2, 4, f64vec4, f64vec2>;
	using f64mat3x2 = _scp::Mat<double, 3, 2, f64vec2, f64vec3>; using f64mat3x3 = _scp::Mat<double, 3, 3, f64vec3, f64vec3>; using f64mat3x4 = _scp::Mat<double, 3, 4, f64vec4, f64vec3>;
	using f64mat4x2 = _scp::Mat<double, 4, 2, f64vec2, f64vec4>; using f64mat4x3 = _scp::Mat<double, 4, 3, f64vec3, f64vec4>; using f64mat4x4 = _scp::Mat<double, 4, 4, f64vec4, f64vec4>;
	template<typename T> concept CMat = requires { typename T::IsMat; typename T::ValueType; typename T::RowType; typename T::ColType; T::col; T::row; } && std::same_as<T, _scp::Mat<typename T::ValueType, T::row, T::col, typename T::RowType, typename T::ColType>>;

	template<typename TValue> class Quat;
	using f32quat = Quat<float>; using f64quat = Quat<double>;

	template<typename TBase, typename TBuffer> class BigInt;
	template<typename TValue> class Frac;
	template<typename TInteger> class Rational;


	struct TensorPosition;
	class TensorShapeIterator;
	struct TensorShape;
	enum class BorderBehaviour;
	enum class InterpolationMethod;
	template<typename T> concept CUntypedTensor = requires { typename T::IsTensor; };
	template<typename T> concept CUntypedMatrix = requires { typename T::Super; typename T::IsMatrix; } && CUntypedTensor<typename T::Super>;
	template<typename T> concept CUntypedVector = requires { typename T::Super; typename T::IsVector; } && CUntypedTensor<typename T::Super>;
	template<typename T, typename TValue> concept CTensor = CUntypedTensor<T> && std::same_as<TValue, typename T::ValueType>;
	template<typename T, typename TValue> concept CMatrix = CUntypedMatrix<T> && std::same_as<TValue, typename T::Super::ValueType>;
	template<typename T, typename TValue> concept CVector = CUntypedVector<T> && std::same_as<TValue, typename T::Super::ValueType>;

	template<typename TValue> class Tensor;
	template<typename TValue> class Matrix;
	template<typename TValue> class Vector;

	template<typename TValue> class SpTensor;
	template<typename TValue> class SpMatrix;
	template<typename TValue> class SpVector;


	template <typename TNode, typename TEdge> class Graph;
}
