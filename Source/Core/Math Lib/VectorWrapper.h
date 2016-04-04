#ifndef _RECON_VECTORWRAPPER_H_
#define _RECON_VECTORWRAPPER_H_

#include "MathDeclarations.h"

#if RECON_SSE_VERSION

#define RECON_SSE_VECTOR_INTRIN (0)
#define RECON_ARM_VECTOR_INTRIN (0)
#define RECON_PPC_VECTOR_INTRIN (0)

#if (defined(__i386) || defined(__i386__) || defined(_M_IX86) || defined(__X86_) || \
	 defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__) || defined(_M_AMD64) || defined(__M_X64))
	#undef RECON_SSE_VECTOR_INTRIN
	#define RECON_SSE_VECTOR_INTRIN (1)
#elif (defined(_M_ARM))
	#undef RECON_ARM_VECTOR_INTRIN
	#define RECON_ARM_VECTOR_INTRIN (1)
#elif (defined(_ARCH_PPC) || defined(__powerpc) || defined(__powerpc__) || defined(__ppc__) || defined(__PPC__))
	#undef RECON_PPC_VECTOR_INTRIN
	#define RECON_PPC_VECTOR_INTRIN (1)
#else
	#error "Unknow Vector128 Intrin Type!"
#endif // RECON_CPU_XXX

#include <intrin.h>

#if RECON_SSE_VECTOR_INTRIN
typedef __m128 Vector128;
#elif RECON_ARM_VECTOR_INTRIN
typedef __n128 Vector128;
#elif RECON_PPC_VECTOR_INTRIN

#endif // 

typedef Vector128& Vector128_Ref;
typedef const Vector128& Vector128_ConstRef;

#if RECON_OS_64BIT
	typedef Vector128 Vector128_In;
#else
	typedef Vector128_ConstRef Vector128_In;
#endif

typedef Vector128 Vector128_Out;

typedef Vector128& Vector128_InOut;

// Initialization Operations:

template<u32 val>
Vector128_Out RECON_VEC_CALLCONV VectorSetConstant();

template<u32 val0, u32 val1, u32 val2, u32 val3>
Vector128_Out RECON_VEC_CALLCONV VectorSetConstant();

Vector128_Out RECON_VEC_CALLCONV VectorSet(const f32& fVal);

Vector128_Out RECON_VEC_CALLCONV VectorSet(const f32& fX, const f32& fY, const f32& fZ, const f32& fW);

Vector128_Out RECON_VEC_CALLCONV VectorSet(const s32& iVal);

Vector128_Out RECON_VEC_CALLCONV VectorSet(const s32& iX, const s32& iY, const s32& iZ, const s32& iW);

// Used to load Aligned Data
Vector128_Out RECON_VEC_CALLCONV VectorLoad(const f32* const alignedFloat4Ptr);

// Used to load Unaligned Data
Vector128_Out RECON_VEC_CALLCONV VectorLoadU(const f32* const unalignedFloat4Ptr);

// Used to store in Aligned Data
void RECON_VEC_CALLCONV VectorStore(Vector128_In vec, f32* alignedFloat4Ptr);

// Used to store in Unaligned Data
void RECON_VEC_CALLCONV VectorStoreU(Vector128_In vec, f32* unalignedFloat4Ptr);

template<VecElem index>
f32 RECON_VEC_CALLCONV VectorExtractFloat(Vector128_In vec);

template<VecElem index>
s32 RECON_VEC_CALLCONV VectorExtractS32(Vector128_In vec);


// Permute Operations:

template<VecElem splat>
Vector128_Out RECON_VEC_CALLCONV VectorSplat(Vector128_In vec);

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
Vector128_Out RECON_VEC_CALLCONV VectorPermute(Vector128_In vec);

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
Vector128_Out RECON_VEC_CALLCONV VectorPermute(Vector128_In lhs, Vector128_In rhs);


// Conversion Operations:

Vector128_Out RECON_VEC_CALLCONV VectorS32ToF32(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorF32ToS32(Vector128_In vec);


// Arithmetic Operations: 

Vector128_Out RECON_VEC_CALLCONV VectorAdd(Vector128_In lhs, Vector128_In rhs);
//Vector128_Out operator+(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorAddS32(Vector128_In lhs, Vector128_In rhs);

// Operates in the following manner:
// {lhs.x+lhs.y, lhs.z+lhs.w, rhs.x+rhs.y, rhs.z+rhs.w}
Vector128_Out RECON_VEC_CALLCONV VectorHAdd(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorSubtract(Vector128_In lhs, Vector128_In rhs);
//Vector128_Out operator-(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorSubtractS32(Vector128_In lhs, Vector128_In rhs);

// Operates in the following manner:
// {lhs.x-lhs.y, lhs.z-lhs.w, rhs.x-rhs.y, rhs.z-rhs.w}
Vector128_Out RECON_VEC_CALLCONV VectorHSub(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorMultiply(Vector128_In lhs, Vector128_In rhs);
//Vector128_Out operator*(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorMad(Vector128_In vecMul1, Vector128_In vecMul2, Vector128_In vecAdd);

Vector128_Out RECON_VEC_CALLCONV VectorMultiplyS32(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorDivide(Vector128_In lhs, Vector128_In rhs);
//Vector128_Out operator/(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorNegate(Vector128_In vec);
//Vector128_Out operator-(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorNegateS32(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorAbs(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorAbsS32(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorInverse(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorSqrt(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorInvSqrt(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorRecip(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorFloor(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorCeil(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorTrunc(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorRound(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorSign(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorLog2(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorExp2(Vector128_In vec);


// Trigonometry Operations:

Vector128_Out RECON_VEC_CALLCONV VectorSin(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorASin(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorCos(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorACos(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorTan(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorATan(Vector128_In vec);

// NOTE: Performs Sin/Cos of Vec.x
// Returns: Vector128(Sin(), Cos(), Sin(), Cos());
Vector128_Out RECON_VEC_CALLCONV VectorSinCos(Vector128_In vec);


// Logical Operations:

Vector128_Out RECON_VEC_CALLCONV VectorAnd(Vector128_In lhs, Vector128_In rhs);
//Vector128_Out operator&(Vector128_In lhs, Vector128_In rhs);

// rhs is Negated Before the And so: result = lhs & ~rhs;
Vector128_Out RECON_VEC_CALLCONV VectorAndNot(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorNot(Vector128_In vec);
//Vector128_Out operator~(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorOr(Vector128_In lhs, Vector128_In rhs);
//Vector128_Out operator|(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorXOr(Vector128_In lhs, Vector128_In rhs);
//Vector128_Out operator^(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorLeftShift(Vector128_In vec, s32 nCount);
//Vector128_Out operator<<(Vector128_In vec, s32 nCount);

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
Vector128_Out RECON_VEC_CALLCONV VectorLeftShift4(Vector128_In vec, Vector128_In shiftCount);

Vector128_Out RECON_VEC_CALLCONV VectorRightShift(Vector128_In vec, s32 nCount);
//Vector128_Out operator>>(Vector128_In vec, s32 nCount);

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
Vector128_Out RECON_VEC_CALLCONV VectorRightShift4(Vector128_In vec, Vector128_In shiftCount);


// Comparison Functions:

// Floating Point Comparisons:

#define VEC_CMP_DECLBASE(name)	Vector128_Out RECON_VEC_CALLCONV Vector##name (Vector128_In lhs, Vector128_In rhs);

#define VEC_CMP_DECL(name) bool RECON_VEC_CALLCONV Vector##name (Vector128_In lhs, Vector128_In rhs);
#define VEC_CMP_DECL1(name) VEC_CMP_DECL( name##X )
#define VEC_CMP_DECL2(name) VEC_CMP_DECL( name##XY )
#define VEC_CMP_DECL3(name) VEC_CMP_DECL( name##XYZ )
#define VEC_CMP_DECL4(name) VEC_CMP_DECL( name##XYZW )

#define VEC_CMP_DECL_ALL(name)  \
			VEC_CMP_DECLBASE(name) \
			VEC_CMP_DECL1(name) \
			VEC_CMP_DECL2(name) \
			VEC_CMP_DECL3(name) \
			VEC_CMP_DECL4(name)

VEC_CMP_DECL_ALL(IsEqual);
VEC_CMP_DECL_ALL(IsNotEqual);
VEC_CMP_DECL_ALL(IsGreaterThan);
VEC_CMP_DECL_ALL(IsGreaterThanOrEqual);
VEC_CMP_DECL_ALL(IsLessThan);
VEC_CMP_DECL_ALL(IsLessThanOrEqual);


// Integer Comparisons:

VEC_CMP_DECL_ALL(IsEqualS32);
VEC_CMP_DECL_ALL(IsGreaterThanS32);
VEC_CMP_DECL_ALL(IsLessThanS32);
VEC_CMP_DECL_ALL(IsNotEqualS32);
VEC_CMP_DECL_ALL(IsGreaterThanOrEqualS32);
VEC_CMP_DECL_ALL(IsLessThanOrEqualS32);

#undef VEC_CMP_DECL_ALL
#undef VEC_CMP_DECL4
#undef VEC_CMP_DECL3
#undef VEC_CMP_DECL2
#undef VEC_CMP_DECL1
#undef VEC_CMP_DECL
#undef VEC_CMP_DECLBASE


// Misc Operations:

Vector128_Out RECON_VEC_CALLCONV VectorInvert_NewtonRaphsonRefinement(Vector128_In vec);
Vector128_Out RECON_VEC_CALLCONV VectorInvertSqrt_NewtonRaphsonRefinement(Vector128_In vec);

s32 RECON_VEC_CALLCONV VectorMoveMask(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorMin(Vector128_In lhs, Vector128_In rhs);
Vector128_Out RECON_VEC_CALLCONV VectorMinS32(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorMax(Vector128_In lhs, Vector128_In rhs);
Vector128_Out RECON_VEC_CALLCONV VectorMaxS32(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorClamp(Vector128_In val, Vector128_In minVal, Vector128_In maxVal);
Vector128_Out RECON_VEC_CALLCONV VectorClampS32(Vector128_In val, Vector128_In minVal, Vector128_In maxVal);

Vector128_Out RECON_VEC_CALLCONV VectorSelectTF(Vector128_In condition, Vector128_In ifTrue, Vector128_In ifFalse);

Vector128_Out RECON_VEC_CALLCONV VectorMinComponentV2(Vector128_In vec);
Vector128_Out RECON_VEC_CALLCONV VectorMinComponentV3(Vector128_In vec);
Vector128_Out RECON_VEC_CALLCONV VectorMinComponentV4(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorMaxComponentV2(Vector128_In vec);
Vector128_Out RECON_VEC_CALLCONV VectorMaxComponentV3(Vector128_In vec);
Vector128_Out RECON_VEC_CALLCONV VectorMaxComponentV4(Vector128_In vec);

Vector128_Out RECON_VEC_CALLCONV VectorBitscanForward(Vector128_In vec);

// Fills Out Bottom Half Of The Vector128
Vector128_Out RECON_VEC_CALLCONV VectorF32ToF16(Vector128_In vec);

// Packs Both Vectors Into The Output
Vector128_Out RECON_VEC_CALLCONV VectorF32ToF16(Vector128_In lowerHalf4, Vector128_In upperHalf4);

Vector128_Out RECON_VEC_CALLCONV VectorF16ToF32(Vector128_In vec);

void RECON_VEC_CALLCONV VectorF16ToF32(Vector128_In packedVec, Vector128_InOut lowerFloat4, Vector128_InOut upperFloat4);


// Vector128 Math Operations:

Vector128_Out RECON_VEC_CALLCONV VectorCrossProduct(Vector128_In lhs, Vector128_In rhs);

Vector128_Out RECON_VEC_CALLCONV VectorDotV2(Vector128_In lhs, Vector128_In rhs);
Vector128_Out RECON_VEC_CALLCONV VectorDotV3(Vector128_In lhs, Vector128_In rhs);
Vector128_Out RECON_VEC_CALLCONV VectorDotV4(Vector128_In lhs, Vector128_In rhs);

#include "VectorWrapper.inl"

#endif // RECON_SSE_VERSION

#endif // _RECON_VECTORWRAPPER_H_