///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SciPP/Core/CoreTypes.hpp>

#define SCP_VEC(vecName, vecSize, eltType)							\
struct vecName##vecSize												\
{																	\
	static_assert(vecSize == 2 || vecSize == 3 || vecSize == 4);	\
																	\
	using IsVec = bool;												\
	using ValueType = eltType;										\
																	\
	static constexpr uint8_t size = vecSize;						\
																	\
																	\
	SCP_VEC##vecSize##_CONSTRUCTORS(vecName, vecSize, eltType)		\
	SCP_##vecName##_INTERNAL_OP(vecName, vecSize, eltType)			\
	SCP_VEC##vecSize##_INTERNAL_FUNC(vecName, vecSize, eltType)		\
};																	\
																	\
SCP_##vecName##_EXTERNAL_OP(vecName, vecSize, eltType)				\
SCP_VEC_SPECIAL_FUNC(vecName, vecSize, eltType)


// Vec constructors

#define SCP_VEC2_CONSTRUCTORS(vecName, vecSize, eltType)																											\
eltType x, y;																																						\
constexpr vecName##2() = default; 																																	\
constexpr vecName##2(eltType value) : x(value), y(value) {} 																										\
constexpr vecName##2(eltType xValue, eltType yValue) : x(xValue), y(yValue) {}																						\

#define SCP_VEC3_CONSTRUCTORS(vecName, vecSize, eltType)																											\
eltType x, y, z;																																					\
constexpr vecName##3() = default;																																	\
constexpr vecName##3(eltType value) : x(value), y(value), z(value) {}																								\
constexpr vecName##3(eltType xValue, eltType yValue, eltType zValue) : x(xValue), y(yValue), z(zValue) {}															\
constexpr vecName##3(const vecName##2& v, eltType zValue) : x(v.x), y(v.y), z(zValue) {}																			\
constexpr vecName##3(eltType xValue, const vecName##2& v) : x(xValue), y(v.x), z(v.y) {}

#define SCP_VEC4_CONSTRUCTORS(vecName, vecSize, eltType)																											\
eltType x, y, z, w;																																					\
constexpr vecName##4() = default;																																	\
constexpr vecName##4(eltType value) : x(value), y(value), z(value), w(value) {}																						\
constexpr vecName##4(eltType xValue, eltType yValue, eltType zValue, eltType wValue) : x(xValue), y(yValue), z(zValue), w(wValue) {}								\
constexpr vecName##4(const vecName##2& v, eltType zValue, eltType wValue) : x(v.x), y(v.y), z(zValue), w(wValue) {}													\
constexpr vecName##4(eltType xValue, const vecName##2& v, eltType wValue) : x(xValue), y(v.x), z(v.y), w(wValue) {}													\
constexpr vecName##4(eltType xValue, eltType yValue, const vecName##2& v) : x(xValue), y(yValue), z(v.x), w(v.y) {}													\
constexpr vecName##4(const vecName##2& u, const vecName##2& v) : x(u.x), y(u.y), z(v.x), w(v.y) {}																	\
constexpr vecName##4(const vecName##3& v, eltType wValue) : x(v.x), y(v.y), z(v.z), w(wValue) {}																	\
constexpr vecName##4(eltType xValue, const vecName##3& v) : x(xValue), y(v.x), z(v.y), w(v.z) {}


// Vec internal operators

#define SCP_f32vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)

#define SCP_f64vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)

#define SCP_i8vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)		\
SCP_VEC##vecSize##_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_i16vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)		\
SCP_VEC##vecSize##_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_i32vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)		\
SCP_VEC##vecSize##_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_i64vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)		\
SCP_VEC##vecSize##_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_u8vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)		\
SCP_VEC##vecSize##_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_u16vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)		\
SCP_VEC##vecSize##_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_u32vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)		\
SCP_VEC##vecSize##_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_u64vec_INTERNAL_OP(vecName, vecSize, eltType)			\
SCP_VEC##vecSize##_INTERNAL_OP_ARITH(vecName, vecSize, eltType)		\
SCP_VEC##vecSize##_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_bvec_INTERNAL_OP(vecName, vecSize, eltType)


#define SCP_VEC2_INTERNAL_OP_ARITH(vecName, vecSize, eltType)													\
constexpr vecName##2& operator+=(const vecName##2& v) { x += v.x; y += v.y; return *this; }						\
constexpr vecName##2& operator-=(const vecName##2& v) { x -= v.x; y -= v.y; return *this; }						\
constexpr vecName##2& operator*=(const vecName##2& v) { x *= v.x; y *= v.y; return *this; }						\
constexpr vecName##2& operator/=(const vecName##2& v) { x /= v.x; y /= v.y; return *this; }

#define SCP_VEC3_INTERNAL_OP_ARITH(vecName, vecSize, eltType)													\
constexpr vecName##3& operator+=(const vecName##3& v) { x += v.x; y += v.y; z += v.z; return *this; }			\
constexpr vecName##3& operator-=(const vecName##3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }			\
constexpr vecName##3& operator*=(const vecName##3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }			\
constexpr vecName##3& operator/=(const vecName##3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

#define SCP_VEC4_INTERNAL_OP_ARITH(vecName, vecSize, eltType)													\
constexpr vecName##4& operator+=(const vecName##4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }	\
constexpr vecName##4& operator-=(const vecName##4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }	\
constexpr vecName##4& operator*=(const vecName##4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }	\
constexpr vecName##4& operator/=(const vecName##4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }


#define SCP_VEC2_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)															\
constexpr vecName##2& operator|=(const vecName##2& v) { x |= v.x; y |= v.y; return *this; }								\
constexpr vecName##2& operator&=(const vecName##2& v) { x &= v.x; y &= v.y; return *this; }								\
constexpr vecName##2& operator^=(const vecName##2& v) { x ^= v.x; y ^= v.y; return *this; }								\
constexpr vecName##2& operator>>=(const vecName##2& v) { x >>= v.x; y >>= v.y; return *this; }							\
constexpr vecName##2& operator<<=(const vecName##2& v) { x <<= v.x; y <<= v.y; return *this; }

#define SCP_VEC3_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)															\
constexpr vecName##3& operator|=(const vecName##3& v) { x |= v.x; y |= v.y; z |= v.z; return *this; }					\
constexpr vecName##3& operator&=(const vecName##3& v) { x &= v.x; y &= v.y; z &= v.z; return *this; }					\
constexpr vecName##3& operator^=(const vecName##3& v) { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }					\
constexpr vecName##3& operator>>=(const vecName##3& v) { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }				\
constexpr vecName##3& operator<<=(const vecName##3& v) { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }

#define SCP_VEC4_INTERNAL_OP_BITWISE(vecName, vecSize, eltType)															\
constexpr vecName##4& operator|=(const vecName##4& v) { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }			\
constexpr vecName##4& operator&=(const vecName##4& v) { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }			\
constexpr vecName##4& operator^=(const vecName##4& v) { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }			\
constexpr vecName##4& operator>>=(const vecName##4& v) { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }	\
constexpr vecName##4& operator<<=(const vecName##4& v) { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }


// Vec accessors

#define SCP_VEC2_INTERNAL_FUNC(vecName, vecSize, eltType)																										\
constexpr bool operator==(const vecName##2& v) const { return x == v.x && y == v.y; }																			\
constexpr bool operator!=(const vecName##2& v) const { return x != v.x || y != v.y; }																			\
constexpr eltType& operator[](uint8_t i) { assert(i < 2); switch (i) { case 0: return x; default: return y; } }													\
constexpr const eltType& operator[](uint8_t i) const { assert(i < 2); switch (i) { case 0: return x; default: return y; } }

#define SCP_VEC3_INTERNAL_FUNC(vecName, vecSize, eltType)																										\
constexpr bool operator==(const vecName##3& v) const { return x == v.x && y == v.y && z == v.z; }																\
constexpr bool operator!=(const vecName##3& v) const { return x != v.x || y != v.y || z != v.z; }																\
constexpr eltType& operator[](uint8_t i) { assert(i < 3); switch (i) { case 0: return x; case 1: return y; default: return z; } }								\
constexpr const eltType& operator[](uint8_t i) const { assert(i < 3); switch (i) { case 0: return x; case 1: return y; default: return z; } }					\
inline vecName##2& xy() { return *reinterpret_cast<vecName##2*>(&x); }																							\
inline const vecName##2& xy() const { return *reinterpret_cast<const vecName##2*>(&x); }																		\
inline vecName##2& yz() { return *reinterpret_cast<vecName##2*>(&y); }																							\
inline const vecName##2& yz() const { return *reinterpret_cast<const vecName##2*>(&y); }

#define SCP_VEC4_INTERNAL_FUNC(vecName, vecSize, eltType)																										\
constexpr bool operator==(const vecName##4& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }													\
constexpr bool operator!=(const vecName##4& v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }													\
constexpr eltType& operator[](uint8_t i) { assert(i < 4); switch (i) { case 0: return x; case 1: return y; case 2: return z; default: return w; } }				\
constexpr const eltType& operator[](uint8_t i) const { assert(i < 4); switch (i) { case 0: return x; case 1: return y; case 2: return z; default: return w; } }	\
inline vecName##2& xy() { return *reinterpret_cast<vecName##2*>(&x); }																							\
inline const vecName##2& xy() const { return *reinterpret_cast<const vecName##2*>(&x); }																		\
inline vecName##2& yz() { return *reinterpret_cast<vecName##2*>(&y); }																							\
inline const vecName##2& yz() const { return *reinterpret_cast<const vecName##2*>(&y); }																		\
inline vecName##2& zw() { return *reinterpret_cast<vecName##2*>(&z); }																							\
inline const vecName##2& zw() const { return *reinterpret_cast<const vecName##2*>(&z); }																		\
inline vecName##3& xyz() { return *reinterpret_cast<vecName##3*>(&x); }																							\
inline const vecName##3& xyz() const { return *reinterpret_cast<const vecName##3*>(&x); }																		\
inline vecName##3& yzw() { return *reinterpret_cast<vecName##3*>(&y); }																							\
inline const vecName##3& yzw() const { return *reinterpret_cast<const vecName##3*>(&y); }


// Vec external operators

#define SCP_f32vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)

#define SCP_f64vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)

#define SCP_i8vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)	\
SCP_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_i16vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)	\
SCP_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_i32vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)	\
SCP_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_i64vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC##vecSize##_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)	\
SCP_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_u8vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_u16vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_u32vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_u64vec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)				\
SCP_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)

#define SCP_bvec_EXTERNAL_OP(vecName, vecSize, eltType) 			\
SCP_VEC##vecSize##_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)


#define SCP_VEC_EXTERNAL_OP_U_ARITH(vecName, vecSize, eltType)																				\
constexpr vecName##vecSize operator+(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w += v; }	\
constexpr vecName##vecSize operator-(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w -= v; }	\
constexpr vecName##vecSize operator*(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w *= v; }	\
constexpr vecName##vecSize operator/(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w /= v; }	\
																																			\
constexpr vecName##vecSize operator+(const vecName##vecSize##& u, eltType x) { vecName##vecSize v(u); return v += x; }						\
constexpr vecName##vecSize operator-(const vecName##vecSize##& u, eltType x) { vecName##vecSize v(u); return v -= x; }						\
constexpr vecName##vecSize operator*(const vecName##vecSize##& u, eltType x) { vecName##vecSize v(u); return v *= x; }						\
constexpr vecName##vecSize operator/(const vecName##vecSize##& u, eltType x) { vecName##vecSize v(u); return v /= x; }						\
																																			\
constexpr vecName##vecSize operator+(eltType x, const vecName##vecSize##& u) { vecName##vecSize v(u); return v += x; }						\
constexpr vecName##vecSize operator-(eltType x, const vecName##vecSize##& u) { vecName##vecSize v(x); return v -= u; }						\
constexpr vecName##vecSize operator*(eltType x, const vecName##vecSize##& u) { vecName##vecSize v(u); return v *= x; }						\
constexpr vecName##vecSize operator/(eltType x, const vecName##vecSize##& u) { vecName##vecSize v(x); return v /= u; }


#define SCP_VEC2_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)									\
constexpr vecName##2 operator+(const vecName##2##& u) { return u; }								\
constexpr vecName##2 operator-(const vecName##2##& u) { return { -u.x, -u.y }; }

#define SCP_VEC3_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)									\
constexpr vecName##3 operator+(const vecName##3##& u) { return u; }								\
constexpr vecName##3 operator-(const vecName##3##& u) { return { -u.x, -u.y, -u.z }; }

#define SCP_VEC4_EXTERNAL_OP_S_ARITH(vecName, vecSize, eltType)									\
constexpr vecName##4 operator+(const vecName##4##& u) { return u; }								\
constexpr vecName##4 operator-(const vecName##4##& u) { return { -u.x, -u.y, -u.z, -u.w }; }


#define SCP_VEC_EXTERNAL_OP_BITWISE(vecName, vecSize, eltType)																					\
constexpr vecName##vecSize operator|(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w |= v; }		\
constexpr vecName##vecSize operator&(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w &= v; }		\
constexpr vecName##vecSize operator^(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w ^= v; }		\
constexpr vecName##vecSize operator>>(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w >>= v; }		\
constexpr vecName##vecSize operator<<(const vecName##vecSize##& u, const vecName##vecSize##& v) { vecName##vecSize w(u); return w <<= v; }


#define SCP_VEC2_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)																					\
constexpr vecName##2 operator||(const vecName##2##& u, const vecName##2##& v) { return { u.x || v.x, u.y || v.y }; }							\
constexpr vecName##2 operator&&(const vecName##2##& u, const vecName##2##& v) { return { u.x && v.x, u.y && v.y }; }							\
																																				\
constexpr vecName##2 operator||(const vecName##2##& u, eltType x) { return { u.x || x, u.y || x }; }											\
constexpr vecName##2 operator&&(const vecName##2##& u, eltType x) { return { u.x && x, u.y && x }; }											\
																																				\
constexpr vecName##2 operator||(eltType x, const vecName##2##& u) { return { x || u.x, x || u.y }; }											\
constexpr vecName##2 operator&&(eltType x, const vecName##2##& u) { return { x && u.x, x && u.y }; }

#define SCP_VEC3_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)																					\
constexpr vecName##3 operator||(const vecName##3##& u, const vecName##3##& v) { return { u.x || v.x, u.y || v.y, u.z || v.z }; }				\
constexpr vecName##3 operator&&(const vecName##3##& u, const vecName##3##& v) { return { u.x && v.x, u.y && v.y, u.z && v.z }; }				\
																																				\
constexpr vecName##3 operator||(const vecName##3##& u, eltType x) { return { u.x || x, u.y || x, u.z || x }; }									\
constexpr vecName##3 operator&&(const vecName##3##& u, eltType x) { return { u.x && x, u.y && x, u.z && x }; }									\
																																				\
constexpr vecName##3 operator||(eltType x, const vecName##3##& u) { return { x || u.x, x || u.y, x || u.z }; }									\
constexpr vecName##3 operator&&(eltType x, const vecName##3##& u) { return { x && u.x, x && u.y, x && u.z }; }

#define SCP_VEC4_EXTERNAL_OP_LOGIC(vecName, vecSize, eltType)																					\
constexpr vecName##4 operator||(const vecName##4##& u, const vecName##4##& v) { return { u.x || v.x, u.y || v.y, u.z || v.z, u.w || v.w }; }	\
constexpr vecName##4 operator&&(const vecName##4##& u, const vecName##4##& v) { return { u.x && v.x, u.y && v.y, u.z && v.z, u.w && v.w }; }	\
																																				\
constexpr vecName##4 operator||(const vecName##4##& u, eltType x) { return { u.x || x, u.y || x, u.z || x, u.w || x }; }						\
constexpr vecName##4 operator&&(const vecName##4##& u, eltType x) { return { u.x && x, u.y && x, u.z && x, u.w && x }; }						\
																																				\
constexpr vecName##4 operator||(eltType x, const vecName##4##& u) { return { x || u.x, x || u.y, x || u.z, x || u.w }; }						\
constexpr vecName##4 operator&&(eltType x, const vecName##4##& u) { return { x && u.x, x && u.y, x && u.z, x && u.w }; }


// Vec special functions

#define SCP_VEC_SPECIAL_FUNC(vecName, vecSize, eltType)		\
SCP_##vecName##_SPECIAL_FUNC(vecName, vecSize, eltType)

#define SCP_f32vec_SPECIAL_FUNC(vecName, vecSize, eltType)	\
SCP_VEC##vecSize##_REAL_FUNC(vecName, vecSize, eltType)		\
SCP_VEC_REAL_FUNC(vecName, vecSize, eltType)

#define SCP_f64vec_SPECIAL_FUNC(vecName, vecSize, eltType)	\
SCP_VEC##vecSize##_REAL_FUNC(vecName, vecSize, eltType)		\
SCP_VEC_REAL_FUNC(vecName, vecSize, eltType)

#define SCP_i8vec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SCP_i16vec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SCP_i32vec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SCP_i64vec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SCP_u8vec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SCP_u16vec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SCP_u32vec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SCP_u64vec_SPECIAL_FUNC(vecName, vecSize, eltType)
#define SCP_bvec_SPECIAL_FUNC(vecName, vecSize, eltType)

#define SCP_VEC_REAL_FUNC(vecName, vecSize, eltType)																															\
constexpr vecName##vecSize radians(const vecName##vecSize& u) { return u * std::numbers::pi / eltType(180); }																	\
constexpr vecName##vecSize degrees(const vecName##vecSize& u) { return u * eltType(180) / std::numbers::pi; }																	\
inline vecName##vecSize inversesqrt(const vecName##vecSize& u) { return eltType(1) / sqrt(u); }																					\
inline vecName##vecSize fract(const vecName##vecSize& u) { return u - floor(u); }																								\
inline vecName##vecSize mod(const vecName##vecSize& u, const vecName##vecSize& v) { return u - v * floor(u / v); }																\
inline vecName##vecSize mod(const vecName##vecSize& u, eltType x) { return u - x * floor(u / x); }																				\
inline eltType length(const vecName##vecSize##& u) { return std::sqrt(dot(u, u)); }																								\
inline eltType distance(const vecName##vecSize##& u, const vecName##vecSize##& v) { return length(v - u); }																		\
inline vecName##vecSize normalize(const vecName##vecSize##& u) { return u / length(u); }																						\
constexpr vecName##vecSize faceforward(const vecName##vecSize##& n, const vecName##vecSize##& i, const vecName##vecSize##& nRef) { return dot(nRef, i) < eltType(0) ? n : -n; }	\
constexpr vecName##vecSize reflect(const vecName##vecSize##& i, const vecName##vecSize##& n) { return i - eltType(2) * dot(n, i) * n; }											\
inline vecName##vecSize refract(const vecName##vecSize##& i, const vecName##vecSize##& n, eltType eta)																			\
{																																												\
	const eltType d = dot(n, i);																																				\
	const eltType k = eltType(1) - eta * eta * (eltType(1) - d * d);																											\
	return k < eltType(0) ? eltType(0) : eta * i - (eta * d + std::sqrt(k)) * n;																								\
}

/* abs, sign, roundEven, modf, min, max, 145+ */

#define SCP_VEC2_REAL_FUNC(vecName, vecSize, eltType)																														\
inline vecName##2 sin(const vecName##2& u) { return { std::sin(u.x), std::sin(u.y) }; }																						\
inline vecName##2 cos(const vecName##2& u) { return { std::cos(u.x), std::cos(u.y) }; }																						\
inline vecName##2 tan(const vecName##2& u) { return { std::tan(u.x), std::tan(u.y) }; }																						\
inline vecName##2 asin(const vecName##2& u) { return { std::asin(u.x), std::asin(u.y) }; }																					\
inline vecName##2 acos(const vecName##2& u) { return { std::acos(u.x), std::acos(u.y) }; }																					\
inline vecName##2 atan(const vecName##2& y, const vecName##2& x) { return { std::atan2(y.x, x.x), std::atan2(y.y, x.y) }; }													\
inline vecName##2 atan(const vecName##2& u) { return { std::atan(u.x), std::atan(u.y) }; }																					\
inline vecName##2 sinh(const vecName##2& u) { return { std::sinh(u.x), std::sinh(u.y) }; }																					\
inline vecName##2 cosh(const vecName##2& u) { return { std::cosh(u.x), std::cosh(u.y) }; }																					\
inline vecName##2 tanh(const vecName##2& u) { return { std::tanh(u.x), std::tanh(u.y) }; }																					\
inline vecName##2 asinh(const vecName##2& u) { return { std::asinh(u.x), std::asinh(u.y) }; }																				\
inline vecName##2 acosh(const vecName##2& u) { return { std::acosh(u.x), std::acosh(u.y) }; }																				\
inline vecName##2 atanh(const vecName##2& u) { return { std::atanh(u.x), std::atanh(u.y) }; }																				\
inline vecName##2 pow(const vecName##2& u, const vecName##2& p) { return { std::pow(u.x, p.x), std::pow(u.y, p.y) }; }														\
inline vecName##2 exp(const vecName##2& u) { return { std::exp(u.x), std::exp(u.y) }; }																						\
inline vecName##2 log(const vecName##2& u) { return { std::log(u.x), std::log(u.y) }; }																						\
inline vecName##2 exp2(const vecName##2& u) { return { std::exp2(u.x), std::exp2(u.y) }; }																					\
inline vecName##2 log2(const vecName##2& u) { return { std::log2(u.x), std::log2(u.y) }; }																					\
inline vecName##2 sqrt(const vecName##2& u) { return { std::sqrt(u.x), std::sqrt(u.y) }; }																					\
inline vecName##2 floor(const vecName##2& u) { return { std::floor(u.x), std::floor(u.y) }; }																				\
inline vecName##2 trunc(const vecName##2& u) { return { std::trunc(u.x), std::trunc(u.y) }; }																				\
inline vecName##2 round(const vecName##2& u) { return { std::round(u.x), std::round(u.y) }; }																				\
inline vecName##2 ceil(const vecName##2& u) { return { std::ceil(u.x), std::ceil(u.y) }; }																					\
constexpr eltType dot(const vecName##2& u, const vecName##2& v) { return u.x * v.x + u.y * v.y; }

#define SCP_VEC3_REAL_FUNC(vecName, vecSize, eltType)																														\
inline vecName##3 sin(const vecName##3& u) { return { std::sin(u.x), std::sin(u.y), std::sin(u.z) }; }																		\
inline vecName##3 cos(const vecName##3& u) { return { std::cos(u.x), std::cos(u.y), std::cos(u.z) }; }																		\
inline vecName##3 tan(const vecName##3& u) { return { std::tan(u.x), std::tan(u.y), std::tan(u.z) }; }																		\
inline vecName##3 asin(const vecName##3& u) { return { std::asin(u.x), std::asin(u.y), std::asin(u.z) }; }																	\
inline vecName##3 acos(const vecName##3& u) { return { std::acos(u.x), std::acos(u.y), std::acos(u.z) }; }																	\
inline vecName##3 atan(const vecName##3& y, const vecName##3& x) { return { std::atan2(y.x, x.x), std::atan2(y.y, x.y), std::atan2(y.z, x.z) }; }							\
inline vecName##3 atan(const vecName##3& u) { return { std::atan(u.x), std::atan(u.y), std::atan(u.z) }; }																	\
inline vecName##3 sinh(const vecName##3& u) { return { std::sinh(u.x), std::sinh(u.y), std::sinh(u.z) }; }																	\
inline vecName##3 cosh(const vecName##3& u) { return { std::cosh(u.x), std::cosh(u.y), std::cosh(u.z) }; }																	\
inline vecName##3 tanh(const vecName##3& u) { return { std::tanh(u.x), std::tanh(u.y), std::tanh(u.z) }; }																	\
inline vecName##3 asinh(const vecName##3& u) { return { std::asinh(u.x), std::asinh(u.y), std::asinh(u.z) }; }																\
inline vecName##3 acosh(const vecName##3& u) { return { std::acosh(u.x), std::acosh(u.y), std::acosh(u.z) }; }																\
inline vecName##3 atanh(const vecName##3& u) { return { std::atanh(u.x), std::atanh(u.y), std::atanh(u.z) }; }																\
inline vecName##3 pow(const vecName##3& u, const vecName##3& p) { return { std::pow(u.x, p.x), std::pow(u.y, p.y), std::pow(u.z, p.z) }; }									\
inline vecName##3 exp(const vecName##3& u) { return { std::exp(u.x), std::exp(u.y), std::exp(u.z) }; }																		\
inline vecName##3 log(const vecName##3& u) { return { std::log(u.x), std::log(u.y), std::log(u.z) }; }																		\
inline vecName##3 exp2(const vecName##3& u) { return { std::exp2(u.x), std::exp2(u.y), std::exp2(u.z) }; }																	\
inline vecName##3 log2(const vecName##3& u) { return { std::log2(u.x), std::log2(u.y), std::log2(u.z) }; }																	\
inline vecName##3 sqrt(const vecName##3& u) { return { std::sqrt(u.x), std::sqrt(u.y), std::sqrt(u.z) }; }																	\
inline vecName##3 floor(const vecName##3& u) { return { std::floor(u.x), std::floor(u.y), std::floor(u.z) }; }																\
inline vecName##3 trunc(const vecName##3& u) { return { std::trunc(u.x), std::trunc(u.y), std::trunc(u.z) }; }																\
inline vecName##3 round(const vecName##3& u) { return { std::round(u.x), std::round(u.y), std::round(u.z) }; }																\
inline vecName##3 ceil(const vecName##3& u) { return { std::ceil(u.x), std::ceil(u.y), std::ceil(u.z) }; }																	\
constexpr eltType dot(const vecName##3& u, const vecName##3& v) { return u.x * v.x + u.y * v.y + u.z * v.z; }																\
constexpr vecName##3 cross(const vecName##3& u, const vecName##3& v) { return { u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x }; }

#define SCP_VEC4_REAL_FUNC(vecName, vecSize, eltType)																														\
inline vecName##4 sin(const vecName##4& u) { return { std::sin(u.x), std::sin(u.y), std::sin(u.z), std::sin(u.w) }; }														\
inline vecName##4 cos(const vecName##4& u) { return { std::cos(u.x), std::cos(u.y), std::cos(u.z), std::cos(u.w) }; }														\
inline vecName##4 tan(const vecName##4& u) { return { std::tan(u.x), std::tan(u.y), std::tan(u.z), std::tan(u.w) }; }														\
inline vecName##4 asin(const vecName##4& u) { return { std::asin(u.x), std::asin(u.y), std::asin(u.z), std::asin(u.w) }; }													\
inline vecName##4 acos(const vecName##4& u) { return { std::acos(u.x), std::acos(u.y), std::acos(u.z), std::acos(u.w) }; }													\
inline vecName##4 atan(const vecName##4& y, const vecName##4& x) { return { std::atan2(y.x, x.x), std::atan2(y.y, x.y), std::atan2(y.z, x.z), std::atan2(y.w, x.w) }; }		\
inline vecName##4 atan(const vecName##4& u) { return { std::atan(u.x), std::atan(u.y), std::atan(u.z), std::atan(u.w) }; }													\
inline vecName##4 sinh(const vecName##4& u) { return { std::sinh(u.x), std::sinh(u.y), std::sinh(u.z), std::sinh(u.w) }; }													\
inline vecName##4 cosh(const vecName##4& u) { return { std::cosh(u.x), std::cosh(u.y), std::cosh(u.z), std::cosh(u.w) }; }													\
inline vecName##4 tanh(const vecName##4& u) { return { std::tanh(u.x), std::tanh(u.y), std::tanh(u.z), std::tanh(u.w) }; }													\
inline vecName##4 asinh(const vecName##4& u) { return { std::asinh(u.x), std::asinh(u.y), std::asinh(u.z), std::asinh(u.w) }; }												\
inline vecName##4 acosh(const vecName##4& u) { return { std::acosh(u.x), std::acosh(u.y), std::acosh(u.z), std::acosh(u.w) }; }												\
inline vecName##4 atanh(const vecName##4& u) { return { std::atanh(u.x), std::atanh(u.y), std::atanh(u.z), std::atanh(u.w) }; }												\
inline vecName##4 pow(const vecName##4& u, const vecName##4& p) { return { std::pow(u.x, p.x), std::pow(u.y, p.y), std::pow(u.z, p.z), std::pow(u.w, p.w) }; }				\
inline vecName##4 exp(const vecName##4& u) { return { std::exp(u.x), std::exp(u.y), std::exp(u.z), std::exp(u.w) }; }														\
inline vecName##4 log(const vecName##4& u) { return { std::log(u.x), std::log(u.y), std::log(u.z), std::log(u.w) }; }														\
inline vecName##4 exp2(const vecName##4& u) { return { std::exp2(u.x), std::exp2(u.y), std::exp2(u.z), std::exp2(u.w) }; }													\
inline vecName##4 log2(const vecName##4& u) { return { std::log2(u.x), std::log2(u.y), std::log2(u.z), std::log2(u.w) }; }													\
inline vecName##4 sqrt(const vecName##4& u) { return { std::sqrt(u.x), std::sqrt(u.y), std::sqrt(u.z), std::sqrt(u.w) }; }													\
inline vecName##4 floor(const vecName##4& u) { return { std::floor(u.x), std::floor(u.y), std::floor(u.z), std::floor(u.w) }; }												\
inline vecName##4 trunc(const vecName##4& u) { return { std::trunc(u.x), std::trunc(u.y), std::trunc(u.z), std::trunc(u.w) }; }												\
inline vecName##4 round(const vecName##4& u) { return { std::round(u.x), std::round(u.y), std::round(u.z), std::round(u.w) }; }												\
inline vecName##4 ceil(const vecName##4& u) { return { std::ceil(u.x), std::ceil(u.y), std::ceil(u.z), std::ceil(u.w)}; }													\
constexpr eltType dot(const vecName##4& u, const vecName##4& v) { return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w; }


namespace scp
{
	#pragma pack(push, 1)

	SCP_VEC(f32vec, 2, float);
	SCP_VEC(f32vec, 3, float);
	SCP_VEC(f32vec, 4, float);
	
	SCP_VEC(f64vec, 2, double);
	SCP_VEC(f64vec, 3, double);
	SCP_VEC(f64vec, 4, double);
	
	SCP_VEC(i8vec, 2, int8_t);
	SCP_VEC(i8vec, 3, int8_t);
	SCP_VEC(i8vec, 4, int8_t);
	
	SCP_VEC(i16vec, 2, int16_t);
	SCP_VEC(i16vec, 3, int16_t);
	SCP_VEC(i16vec, 4, int16_t);
	
	SCP_VEC(i32vec, 2, int32_t);
	SCP_VEC(i32vec, 3, int32_t);
	SCP_VEC(i32vec, 4, int32_t);
	
	SCP_VEC(i64vec, 2, int64_t);
	SCP_VEC(i64vec, 3, int64_t);
	SCP_VEC(i64vec, 4, int64_t);
	
	SCP_VEC(u8vec, 2, uint8_t);
	SCP_VEC(u8vec, 3, uint8_t);
	SCP_VEC(u8vec, 4, uint8_t);
	
	SCP_VEC(u16vec, 2, uint16_t);
	SCP_VEC(u16vec, 3, uint16_t);
	SCP_VEC(u16vec, 4, uint16_t);
	
	SCP_VEC(u32vec, 2, uint32_t);
	SCP_VEC(u32vec, 3, uint32_t);
	SCP_VEC(u32vec, 4, uint32_t);
	
	SCP_VEC(u64vec, 2, uint64_t);
	SCP_VEC(u64vec, 3, uint64_t);
	SCP_VEC(u64vec, 4, uint64_t);
	
	SCP_VEC(bvec, 2, bool);
	SCP_VEC(bvec, 3, bool);
	SCP_VEC(bvec, 4, bool);

	#pragma pack(pop)
}


#undef SCP_VEC
#undef SCP_VEC2_CONSTRUCTORS
#undef SCP_VEC3_CONSTRUCTORS
#undef SCP_VEC4_CONSTRUCTORS
#undef SCP_f32vec_INTERNAL_OP
#undef SCP_f64vec_INTERNAL_OP
#undef SCP_i8vec_INTERNAL_OP
#undef SCP_i16vec_INTERNAL_OP
#undef SCP_i32vec_INTERNAL_OP
#undef SCP_i64vec_INTERNAL_OP
#undef SCP_u8vec_INTERNAL_OP
#undef SCP_u16vec_INTERNAL_OP
#undef SCP_u32vec_INTERNAL_OP
#undef SCP_u64vec_INTERNAL_OP
#undef SCP_bvec_INTERNAL_OP
#undef SCP_VEC2_INTERNAL_OP_ARITH
#undef SCP_VEC3_INTERNAL_OP_ARITH
#undef SCP_VEC4_INTERNAL_OP_ARITH
#undef SCP_VEC2_INTERNAL_OP_BITWISE
#undef SCP_VEC3_INTERNAL_OP_BITWISE
#undef SCP_VEC4_INTERNAL_OP_BITWISE
#undef SCP_VEC2_INTERNAL_FUNC
#undef SCP_VEC3_INTERNAL_FUNC
#undef SCP_VEC4_INTERNAL_FUNC
#undef SCP_f32vec_EXTERNAL_OP
#undef SCP_f64vec_EXTERNAL_OP
#undef SCP_i8vec_EXTERNAL_OP
#undef SCP_i16vec_EXTERNAL_OP
#undef SCP_i32vec_EXTERNAL_OP
#undef SCP_i64vec_EXTERNAL_OP
#undef SCP_u8vec_EXTERNAL_OP
#undef SCP_u16vec_EXTERNAL_OP
#undef SCP_u32vec_EXTERNAL_OP
#undef SCP_u64vec_EXTERNAL_OP
#undef SCP_bvec_EXTERNAL_OP
#undef SCP_VEC_EXTERNAL_OP_U_ARITH
#undef SCP_VEC2_EXTERNAL_OP_S_ARITH
#undef SCP_VEC3_EXTERNAL_OP_S_ARITH
#undef SCP_VEC4_EXTERNAL_OP_S_ARITH
#undef SCP_VEC_EXTERNAL_OP_BITWISE
#undef SCP_VEC2_EXTERNAL_OP_LOGIC
#undef SCP_VEC3_EXTERNAL_OP_LOGIC
#undef SCP_VEC4_EXTERNAL_OP_LOGIC
#undef SCP_VEC_SPECIAL_FUNC
#undef SCP_f32vec_SPECIAL_FUNC
#undef SCP_f64vec_SPECIAL_FUNC
#undef SCP_i8vec_SPECIAL_FUNC
#undef SCP_i16vec_SPECIAL_FUNC
#undef SCP_i32vec_SPECIAL_FUNC
#undef SCP_i64vec_SPECIAL_FUNC
#undef SCP_u8vec_SPECIAL_FUNC
#undef SCP_u16vec_SPECIAL_FUNC
#undef SCP_u32vec_SPECIAL_FUNC
#undef SCP_u64vec_SPECIAL_FUNC
#undef SCP_bvec_SPECIAL_FUNC
#undef SCP_VEC_REAL_FUNC
#undef SCP_VEC2_REAL_FUNC
#undef SCP_VEC3_REAL_FUNC
#undef SCP_VEC4_REAL_FUNC
