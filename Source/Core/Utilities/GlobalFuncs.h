#ifndef _RECON_GLOBALFUNCS_H_
#define _RECON_GLOBALFUNCS_H_

#include <cmath>
#include <type_traits>
#include <utility>

#if RECON_SSE_VERSION
#include <intrin.h>
#endif // RECON_SSE_VERSION

#define DEFINE_MAX_IMPL_SPECIALIZATION(classType, ...) \
	template<> __forceinline classType _MaxImpl(const classType& lhs, const classType& rhs) \
	{ \
		__VA_ARGS__ \
	}

template<typename _LType, typename... _RTypes>
typename std::common_type<_LType, _RTypes...>::type Max(_LType lhs, _RTypes... rhs);

#define DEFINE_MIN_IMPL_SPECIALIZATION(classType, ...) \
	template<> __forceinline classType _MinImpl(const classType& lhs, const classType& rhs) \
	{ \
		__VA_ARGS__ \
	}

template<typename _LType, typename... _RTypes>
typename std::common_type<_LType, _RTypes...>::type Min(_LType lhs, _RTypes... rhs);

template<typename Type>
Type Clamp(const Type& val, const Type& minVal, const Type& maxVal);

template<typename Type>
Type Saturate(const Type& val);

s8 Abs(const s8& iScalar);
s16 Abs(const s16& iScalar);
s32 Abs(const s32& iScalar);
s64 Abs(const s64& iScalar);
f32 Abs(const f32& fScalar);
f64 Abs(const f64& fScalar);

f32 Lerp(const f32& lhs, const f32& rhs, const f32& fLambda);
f64 Lerp(const f64& lhs, const f64& rhs, const f64& fLambda);

f32 Sqrt(const f32& fScalar);
f64 Sqrt(const f64& fScalar);

f32 SqrtSafe(const f32& fScalar, const f32& safeVal = 0.0f);
f64 SqrtSafe(const f64& fScalar, const f64& safeVal = 0.0);

f32 Sign(const f32& fScalar);
f64 Sign(const f64& fScalar);


// Trigonometry

f32 Sin(const f32& fRadians);
f64 Sin(const f64& fRadians);

f32 ASin(const f32& fRadians);
f64 ASin(const f64& fRadians);

f32 Cos(const f32& fRadians);
f64 Cos(const f64& fRadians);

f32 ACos(const f32& fRadians);
f64 ACos(const f64& fRadians);

f32 Tan(const f32& fRadians);
f64 Tan(const f64& fRadians);

f32 ATan(const f32& fRadians);
f64 ATan(const f64& fRadians);


// Misc

f32 Floor(const f32& fScalar);
f64 Floor(const f64& fScalar);

f32 Ceil(const f32& fScalar);
f64 Ceil(const f64& fScalar);

f32 Trunc(const f32& fScalar);
f64 Trunc(const f64& fScalar);

f32 Round(const f32& fScalar);
f64 Round(const f64& fScalar);

f32 Log2(const f32& fScalar);
f64 Log2(const f64& fScalar);

f32 Mad(const f32& fMul1, const f32& fMul2, const f32& fAdd);
f64 Mad(const f64& fMul1, const f64& fMul2, const f64& fAdd);

u32 GetNumBitsOn(u32 bits);
u32 GetNumBitsOn(u64 bits);

u32 GetNumBitsOff(u32 bits);
u32 GetNumBitsOff(u64 bits);

#include "GlobalFuncs.inl"

#endif // _RECON_GLOBALFUNCS_H_
