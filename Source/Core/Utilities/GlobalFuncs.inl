
#define SIGNED_INT_BRANCHLESS_MAX(b) DEFINE_MAX_IMPL_SPECIALIZATION( s##b , \
																	 s##b diff = lhs - rhs; \
																	 return lhs - (diff & (diff >> (b - 1))); \
																   )

template<typename _LType, typename _RType>
__forceinline typename std::common_type<_LType, _RType>::type _MaxImpl(const _LType& lhs, const _RType& rhs)
{
	return (lhs > rhs) ? lhs : rhs;
}

SIGNED_INT_BRANCHLESS_MAX(8)
SIGNED_INT_BRANCHLESS_MAX(16)
SIGNED_INT_BRANCHLESS_MAX(32)
SIGNED_INT_BRANCHLESS_MAX(64)
#undef SIGNED_INT_BRANCHLESS_MAX

template<typename _Type>
__forceinline _Type _Max_Helper(const _Type& lhs)
{
	return lhs;
}

template<typename _LType, typename _RType, typename... _tOthers>
__forceinline typename std::common_type<_LType, _RType, _tOthers...>::type _Max_Helper(_LType lhs, _RType rhs, _tOthers... tOthers)
{
	return _Max_Helper(_MaxImpl(lhs, rhs), tOthers...);
}

template<typename _LType, typename... _RTypes>
__forceinline typename std::common_type<_LType, _RTypes...>::type Max(_LType lhs, _RTypes... rhs)
{
	return _Max_Helper(lhs, rhs...);
}


#define SIGNED_INT_BRANCHLESS_MIN(b) DEFINE_MIN_IMPL_SPECIALIZATION( s##b , \
																	 s##b diff = lhs - rhs; \
																	 return rhs + (diff & (diff >> (b - 1))); \
																   )

template<typename _LType, typename _RType>
__forceinline typename std::common_type<_LType, _RType>::type _MinImpl(const _LType& lhs, const _RType& rhs)
{
	return (lhs < rhs) ? lhs : rhs;
}

SIGNED_INT_BRANCHLESS_MIN(8)
SIGNED_INT_BRANCHLESS_MIN(16)
SIGNED_INT_BRANCHLESS_MIN(32)
SIGNED_INT_BRANCHLESS_MIN(64)
#undef SIGNED_INT_BRANCHLESS_MIN

template<typename _Type>
__forceinline _Type _Min_Helper(const _Type& lhs)
{
	return lhs;
}

template<typename _LType, typename _RType, typename... _tOthers>
__forceinline typename std::common_type<_LType, _RType, _tOthers...>::type _Min_Helper(_LType lhs, _RType rhs, _tOthers... tOthers)
{
	return _Min_Helper(_MinImpl(lhs, rhs), tOthers...);
}

template<typename _LType, typename... _RTypes>
__forceinline typename std::common_type<_LType, _RTypes...>::type Min(_LType lhs, _RTypes... rhs)
{
	return _Min_Helper(lhs, rhs...);
}


template<typename Type>
__forceinline Type Clamp(const Type& val, const Type& minVal, const Type& maxVal)
{
	return Max(Min(val, maxVal), minVal);
}

template<typename Type>
__forceinline Type Saturate(const Type& val)
{
	return Clamp(val, Type(0), Type(1));
}

__forceinline s8 Abs(const s8& iScalar)
{
	s8 s = iScalar >> 7;
	return (iScalar ^ s) - s;
}

__forceinline s16 Abs(const s16& iScalar)
{
	s16 s = iScalar >> 15;
	return (iScalar ^ s) - s;
}

__forceinline s32 Abs(const s32& iScalar)
{
	s32 s = iScalar >> 31;
	return (iScalar ^ s) - s;
}

__forceinline s64 Abs(const s64& iScalar)
{
	s64 s = iScalar >> 63;
	return (iScalar ^ s) - s;
}

__forceinline f32 Abs(const f32& fScalar)
{
	return fabsf(fScalar);
}

__forceinline f64 Abs(const f64& fScalar)
{
	return fabs(fScalar);
}

__forceinline f32 Lerp(const f32& lhs, const f32& rhs, const f32& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline f64 Lerp(const f64& lhs, const f64& rhs, const f64& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline f32 Sqrt(const f32& fScalar)
{
	return sqrtf(fScalar);
}

__forceinline f64 Sqrt(const f64& fScalar)
{
	return sqrt(fScalar);
}

__forceinline f32 SqrtSafe(const f32& fScalar, const f32& safeVal /*= 0.0f*/)
{
	return fScalar != 0.0f ? Sqrt(fScalar) : safeVal;
}

__forceinline f64 SqrtSafe(const f64& fScalar, const f64& safeVal /*= 0.0*/)
{
	return fScalar != 0.0 ? Sqrt(fScalar) : safeVal;
}

__forceinline f32 Sign(const f32& fScalar)
{
	union { f32 fOut; s32 iOut; }; \
	iOut = fScalar != 0.0f ? ((*reinterpret_cast<const s32*>(&fScalar) & 0x80000000) | 0x3F800000) : 0; \
	return fOut;
}

__forceinline f64 Sign(const f64& fScalar)
{
	union { f64 fOut; s64 iOut; }; \
	iOut = fScalar != 0.0f ? ((*reinterpret_cast<const s64*>(&fScalar) & (s64)0x8000000000000000) | (s64)0x3FF0000000000000) : 0; \
	return fOut;
}

// Trigonometry

__forceinline f32 Sin(const f32& fRadians)
{
	return sinf(fRadians);
}

__forceinline f64 Sin(const f64& fRadians)
{
	return sin(fRadians);
}

__forceinline f32 ASin(const f32& fRadians)
{
	return asinf(fRadians);
}

__forceinline f64 ASin(const f64& fRadians)
{
	return asin(fRadians);
}

__forceinline f32 Cos(const f32& fRadians)
{
	return cosf(fRadians);
}

__forceinline f64 Cos(const f64& fRadians)
{
	return cos(fRadians);
}

__forceinline f32 ACos(const f32& fRadians)
{
	return acosf(fRadians);
}

__forceinline f64 ACos(const f64& fRadians)
{
	return acos(fRadians);
}

__forceinline f32 Tan(const f32& fRadians)
{
	return tanf(fRadians);
}

__forceinline f64 Tan(const f64& fRadians)
{
	return tan(fRadians);
}

__forceinline f32 ATan(const f32& fRadians)
{
	return atanf(fRadians);
}

__forceinline f64 ATan(const f64& fRadians)
{
	return atan(fRadians);
}


// Misc

__forceinline f32 Floor(const f32& fScalar)
{
	return floorf(fScalar);
}

__forceinline f64 Floor(const f64& fScalar)
{
	return floor(fScalar);
}

__forceinline f32 Ceil(const f32& fScalar)
{
	return ceilf(fScalar);
}

__forceinline f64 Ceil(const f64& fScalar)
{
	return ceil(fScalar);
}

__forceinline f32 Trunc(const f32& fScalar)
{
	return truncf(fScalar);
}

__forceinline f64 Trunc(const f64& fScalar)
{
	return trunc(fScalar);
}

__forceinline f32 Round(const f32& fScalar)
{
	return roundf(fScalar);
}

__forceinline f64 Round(const f64& fScalar)
{
	return round(fScalar);
}

__forceinline f32 Log2(const f32& fScalar)
{
	return log2f(fScalar);
}

__forceinline f64 Log2(const f64& fScalar)
{
	return log2(fScalar);
}

__forceinline f32 Mad(const f32& fMul1, const f32& fMul2, const f32& fAdd)
{
	return fmaf(fMul1, fMul2, fAdd);
}

__forceinline f64 Mad(const f64& fMul1, const f64& fMul2, const f64& fAdd)
{
	return fma(fMul1, fMul2, fAdd);
}

inline u32 GetNumBitsOn(u32 bits)
{
#if RECON_SSE_VERSION
	return _mm_popcnt_u32(bits);
#else
	bits = bits - ((bits >> 1) & 0x55555555);
	bits = (bits & 0x33333333 + ((bits >> 2) & 0x33333333));
	return ((bits + (bits >> 4) & 0xF0F0F0F0) * 0x10101010) >> 24;
#endif // RECON_SSE_VERSION
}

inline u32 GetNumBitsOn(u64 bits)
{
#if RECON_SSE_VERSION && 0
	return (u32)_mm_popcnt_u64(bits);
#else
	bits = bits - ((bits >> 1) & 0x5555555555555555ui64);
	bits = (bits & 0x3333333333333333ui64 + ((bits >> 2) & 0x3333333333333333ui64));
	return (u32)(((bits + (bits >> 4) & 0xF0F0F0F0F0F0F0F0ui64) * 0x1010101010101010ui64) >> 56);
#endif // RECON_SSE_VERSION
}

__forceinline u32 GetNumBitsOff(u32 bits)
{
	return 32 - GetNumBitsOn(bits);
}

__forceinline u32 GetNumBitsOff(u64 bits)
{
	return 64 - GetNumBitsOn(bits);
}
