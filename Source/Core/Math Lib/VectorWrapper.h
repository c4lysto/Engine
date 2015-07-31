#ifndef VECTORWRAPPER_H
#define VECTORWRAPPER_H

#include "MathDeclarations.h"

#if SSE_AVAILABLE

#include <xmmintrin.h>
#include <intrin.h>

#define RECON_USE_SVML (0)

#define VEC_INT_TO_FLOAT _mm_castsi128_ps
#define VEC_FLOAT_TO_INT _mm_castps_si128

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
Vector_Out VectorSetConstant();

template<u32 val0, u32 val1, u32 val2, u32 val3>
Vector_Out VectorSetConstant();

Vector_Out VectorSet(const float& fVal);

Vector_Out VectorSet(const float& fX, const float& fY, const float& fZ, const float& fW);

Vector_Out VectorSet(const int& iVal);

Vector_Out VectorSet(const int& iX, const int& iY, const int& iZ, const int& iW);

// Used to load Aligned Data
Vector_Out VectorLoad(const float* const alignedFloat4Ptr);

// Used to load Unaligned Data
Vector_Out VectorLoadU(const float* const unalignedFloat4Ptr);

// Used to store in Aligned Data
void VectorStore(Vector_In vec, float* alignedFloat4Ptr);

// Used to store in Unaligned Data
void VectorStoreU(Vector_In vec, float* unalignedFloat4Ptr);

template<VecElem index>
float VectorExtractFloat(Vector_In vec);

template<VecElem index>
int VectorExtractInt(Vector_In vec);


// Permute Operations:

template<VecElem splat>
Vector_Out VectorSplat(Vector_In vec);

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
Vector_Out VectorPermute(Vector_In vec);

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
Vector_Out VectorPermute(Vector_In lhs, Vector_In rhs);


// Conversion Operations:

Vector_Out VectorIntToFloat(Vector_In vec);

Vector_Out VectorFloatToInt(Vector_In vec);


// Arithmetic Operations: 

Vector_Out VectorAdd(Vector_In lhs, Vector_In rhs);
//Vector_Out operator+(Vector_In lhs, Vector_In rhs);

Vector_Out VectorAddInt(Vector_In lhs, Vector_In rhs);

// Operates in the following manner:
// {lhs.x+lhs.y, lhs.z+lhs.w, rhs.x+rhs.y, rhs.z+rhs.w}
Vector_Out VectorHAdd(Vector_In lhs, Vector_In rhs);

Vector_Out VectorSubtract(Vector_In lhs, Vector_In rhs);
//Vector_Out operator-(Vector_In lhs, Vector_In rhs);

Vector_Out VectorSubtractInt(Vector_In lhs, Vector_In rhs);

// Operates in the following manner:
// {lhs.x-lhs.y, lhs.z-lhs.w, rhs.x-rhs.y, rhs.z-rhs.w}
Vector_Out VectorHSub(Vector_In lhs, Vector_In rhs);

Vector_Out VectorMultiply(Vector_In lhs, Vector_In rhs);
//Vector_Out operator*(Vector_In lhs, Vector_In rhs);

Vector_Out VectorMultiplyInt(Vector_In lhs, Vector_In rhs);

Vector_Out VectorDivide(Vector_In lhs, Vector_In rhs);
//Vector_Out operator/(Vector_In lhs, Vector_In rhs);

Vector_Out VectorNegate(Vector_In vec);
//Vector_Out operator-(Vector_In vec);

Vector_Out VectorAbs(Vector_In vec);

Vector_Out VectorSqrt(Vector_In vec);

Vector_Out VectorRSqrt(Vector_In vec);

Vector_Out VectorRecip(Vector_In vec);

Vector_Out VectorFloor(Vector_In vec);

Vector_Out VectorCeil(Vector_In vec);

Vector_Out VectorTrunc(Vector_In vec);

Vector_Out VectorRound(Vector_In vec);

Vector_Out VectorSign(Vector_In vec);

Vector_Out VectorLog2(Vector_In vec);

Vector_Out VectorExp2(Vector_In vec);


// Trigonometry Operations:

Vector_Out VectorSin(Vector_In vec);

Vector_Out VectorASin(Vector_In vec);

Vector_Out VectorCos(Vector_In vec);

Vector_Out VectorACos(Vector_In vec);

Vector_Out VectorTan(Vector_In vec);

Vector_Out VectorATan(Vector_In vec);

// NOTE: Performs Sin/Cos of Vec.x
// Returns: Vector(Sin(), Cos(), Sin(), Cos());
Vector_Out VectorSinCos(Vector_In vec);


// Logical Operations:

Vector_Out VectorAnd(Vector_In lhs, Vector_In rhs);
//Vector_Out operator&(Vector_In lhs, Vector_In rhs);

// rhs is Negated Before the And so: result = lhs & ~rhs;
Vector_Out VectorAndNot(Vector_In lhs, Vector_In rhs);

Vector_Out VectorNot(Vector_In vec);
//Vector_Out operator~(Vector_In vec);

Vector_Out VectorOr(Vector_In lhs, Vector_In rhs);
//Vector_Out operator|(Vector_In lhs, Vector_In rhs);

Vector_Out VectorXOr(Vector_In lhs, Vector_In rhs);
//Vector_Out operator^(Vector_In lhs, Vector_In rhs);

Vector_Out VectorLeftShift(Vector_In vec, int nCount);
//Vector_Out operator<<(Vector_In vec, int nCount);

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
Vector_Out VectorLeftShift4(Vector_In vec, Vector_In shiftCount);

Vector_Out VectorRightShift(Vector_In vec, int nCount);
//Vector_Out operator>>(Vector_In vec, int nCount);

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
Vector_Out VectorRightShift4(Vector_In vec, Vector_In shiftCount);


// Comparison Functions:

// Floating Point Comparisons:

#define VEC_CMP_DECLBASE(name)	Vector_Out Vector##name (Vector_In lhs, Vector_In rhs);

#define VEC_CMP_DECL(name) bool Vector##name (Vector_In lhs, Vector_In rhs);
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

s32 VectorSignMask(Vector_In vec);

Vector_Out VectorMin(Vector_In lhs, Vector_In rhs);
Vector_Out VectorMinInt(Vector_In lhs, Vector_In rhs);

Vector_Out VectorMax(Vector_In lhs, Vector_In rhs);
Vector_Out VectorMaxInt(Vector_In lhs, Vector_In rhs);

Vector_Out VectorSelectTF(Vector_In lhs, Vector_In rhs, Vector_In condition);

Vector_Out VectorBitscanForward(Vector_In vec);


// Vector Math Operations:

Vector_Out VectorCrossProduct(Vector_In lhs, Vector_In rhs);

float VectorDot2(Vector_In lhs, Vector_In rhs);
float VectorDot3(Vector_In lhs, Vector_In rhs);
float VectorDot4(Vector_In lhs, Vector_In rhs);

#include "VectorWrapper.inl"

#undef VEC_INT_TO_FLOAT
#undef VEC_FLOAT_TO_INT

#endif // SSE_AVAILABLE

#endif // VECTORWRAPPER_H