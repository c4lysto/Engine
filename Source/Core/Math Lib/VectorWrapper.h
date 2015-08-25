#ifndef VECTORWRAPPER_H
#define VECTORWRAPPER_H

#include "MathDeclarations.h"

#if SSE_AVAILABLE

#include <xmmintrin.h>
#include <intrin.h>

typedef __m128 Vector;
typedef Vector& Vector_Ref;
typedef const Vector& Vector_ConstRef;

#if RECON_OS_64BIT
	typedef Vector Vector_In;
#else
	typedef Vector_ConstRef Vector_In;
#endif

typedef Vector Vector_Out;

// Initialization Operations:

template<u32 val>
Vector_Out RECON_VEC_CALLCONV VectorSetConstant();

template<u32 val0, u32 val1, u32 val2, u32 val3>
Vector_Out RECON_VEC_CALLCONV VectorSetConstant();

Vector_Out RECON_VEC_CALLCONV VectorSet(const f32& fVal);

Vector_Out RECON_VEC_CALLCONV VectorSet(const f32& fX, const f32& fY, const f32& fZ, const f32& fW);

Vector_Out RECON_VEC_CALLCONV VectorSet(const s32& iVal);

Vector_Out RECON_VEC_CALLCONV VectorSet(const s32& iX, const s32& iY, const s32& iZ, const s32& iW);

// Used to load Aligned Data
Vector_Out RECON_VEC_CALLCONV VectorLoad(const f32* const alignedFloat4Ptr);

// Used to load Unaligned Data
Vector_Out RECON_VEC_CALLCONV VectorLoadU(const f32* const unalignedFloat4Ptr);

// Used to store in Aligned Data
void RECON_VEC_CALLCONV VectorStore(Vector_In vec, f32* alignedFloat4Ptr);

// Used to store in Unaligned Data
void RECON_VEC_CALLCONV VectorStoreU(Vector_In vec, f32* unalignedFloat4Ptr);

template<VecElem index>
f32 RECON_VEC_CALLCONV VectorExtractFloat(Vector_In vec);

template<VecElem index>
s32 RECON_VEC_CALLCONV VectorExtractInt(Vector_In vec);


// Permute Operations:

template<VecElem splat>
Vector_Out RECON_VEC_CALLCONV VectorSplat(Vector_In vec);

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
Vector_Out RECON_VEC_CALLCONV VectorPermute(Vector_In vec);

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
Vector_Out RECON_VEC_CALLCONV VectorPermute(Vector_In lhs, Vector_In rhs);


// Conversion Operations:

Vector_Out RECON_VEC_CALLCONV VectorIntToFloat(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorFloatToInt(Vector_In vec);


// Arithmetic Operations: 

Vector_Out RECON_VEC_CALLCONV VectorAdd(Vector_In lhs, Vector_In rhs);
//Vector_Out operator+(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorAddInt(Vector_In lhs, Vector_In rhs);

// Operates in the following manner:
// {lhs.x+lhs.y, lhs.z+lhs.w, rhs.x+rhs.y, rhs.z+rhs.w}
Vector_Out RECON_VEC_CALLCONV VectorHAdd(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorSubtract(Vector_In lhs, Vector_In rhs);
//Vector_Out operator-(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorSubtractInt(Vector_In lhs, Vector_In rhs);

// Operates in the following manner:
// {lhs.x-lhs.y, lhs.z-lhs.w, rhs.x-rhs.y, rhs.z-rhs.w}
Vector_Out RECON_VEC_CALLCONV VectorHSub(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorMultiply(Vector_In lhs, Vector_In rhs);
//Vector_Out operator*(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorMultiplyInt(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorDivide(Vector_In lhs, Vector_In rhs);
//Vector_Out operator/(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorNegate(Vector_In vec);
//Vector_Out operator-(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorNegateInt(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorAbs(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorAbsInt(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorSqrt(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorRSqrt(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorRecip(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorFloor(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorCeil(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorTrunc(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorRound(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorSign(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorLog2(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorExp2(Vector_In vec);


// Trigonometry Operations:

Vector_Out RECON_VEC_CALLCONV VectorSin(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorASin(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorCos(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorACos(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorTan(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorATan(Vector_In vec);

// NOTE: Performs Sin/Cos of Vec.x
// Returns: Vector(Sin(), Cos(), Sin(), Cos());
Vector_Out RECON_VEC_CALLCONV VectorSinCos(Vector_In vec);


// Logical Operations:

Vector_Out RECON_VEC_CALLCONV VectorAnd(Vector_In lhs, Vector_In rhs);
//Vector_Out operator&(Vector_In lhs, Vector_In rhs);

// rhs is Negated Before the And so: result = lhs & ~rhs;
Vector_Out RECON_VEC_CALLCONV VectorAndNot(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorNot(Vector_In vec);
//Vector_Out operator~(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorOr(Vector_In lhs, Vector_In rhs);
//Vector_Out operator|(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorXOr(Vector_In lhs, Vector_In rhs);
//Vector_Out operator^(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorLeftShift(Vector_In vec, s32 nCount);
//Vector_Out operator<<(Vector_In vec, s32 nCount);

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
Vector_Out RECON_VEC_CALLCONV VectorLeftShift4(Vector_In vec, Vector_In shiftCount);

Vector_Out RECON_VEC_CALLCONV VectorRightShift(Vector_In vec, s32 nCount);
//Vector_Out operator>>(Vector_In vec, s32 nCount);

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
Vector_Out RECON_VEC_CALLCONV VectorRightShift4(Vector_In vec, Vector_In shiftCount);


// Comparison Functions:

// Floating Point Comparisons:

#define VEC_CMP_DECLBASE(name)	Vector_Out RECON_VEC_CALLCONV Vector##name (Vector_In lhs, Vector_In rhs);

#define VEC_CMP_DECL(name) bool RECON_VEC_CALLCONV Vector##name (Vector_In lhs, Vector_In rhs);
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

VEC_CMP_DECL_ALL(IsEqualInt);
VEC_CMP_DECL_ALL(IsGreaterThanInt);
VEC_CMP_DECL_ALL(IsLessThanInt);

VEC_CMP_DECL_ALL(IsNotEqualInt);

VEC_CMP_DECL_ALL(IsGreaterThanOrEqualInt);

VEC_CMP_DECL_ALL(IsLessThanOrEqualInt);

#undef VEC_CMP_DECL_ALL
#undef VEC_CMP_DECL4
#undef VEC_CMP_DECL3
#undef VEC_CMP_DECL2
#undef VEC_CMP_DECL1
#undef VEC_CMP_DECL
#undef VEC_CMP_DECLBASE


// Misc Operations:

s32 RECON_VEC_CALLCONV VectorSignMask(Vector_In vec);

Vector_Out RECON_VEC_CALLCONV VectorMin(Vector_In lhs, Vector_In rhs);
Vector_Out RECON_VEC_CALLCONV VectorMinInt(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorMax(Vector_In lhs, Vector_In rhs);
Vector_Out RECON_VEC_CALLCONV VectorMaxInt(Vector_In lhs, Vector_In rhs);

Vector_Out RECON_VEC_CALLCONV VectorClamp(Vector_In val, Vector_In minVal, Vector_In maxVal);
Vector_Out RECON_VEC_CALLCONV VectorClampInt(Vector_In val, Vector_In minVal, Vector_In maxVal);

Vector_Out RECON_VEC_CALLCONV VectorSelectTF(Vector_In condition, Vector_In ifTrue, Vector_In ifFalse);

Vector_Out RECON_VEC_CALLCONV VectorBitscanForward(Vector_In vec);


// Vector Math Operations:

Vector_Out RECON_VEC_CALLCONV VectorCrossProduct(Vector_In lhs, Vector_In rhs);

f32 RECON_VEC_CALLCONV VectorDot2(Vector_In lhs, Vector_In rhs);
f32 RECON_VEC_CALLCONV VectorDot3(Vector_In lhs, Vector_In rhs);
f32 RECON_VEC_CALLCONV VectorDot4(Vector_In lhs, Vector_In rhs);

#include "VectorWrapper.inl"

#endif // SSE_AVAILABLE

#endif // VECTORWRAPPER_H