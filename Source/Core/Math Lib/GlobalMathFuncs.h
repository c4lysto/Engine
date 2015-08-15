#ifndef GLOBALMATHFUNCS_H
#define GLOBALMATHFUNCS_H

#include "MathDeclarations.h"

#ifndef MATHLIB_H
#error "Don't Include GlobalMathFunc.h Directly. Include MathLib.h Instead."
#endif // MATHLIB_H

class VecCmpResult;

// Utility Functions

template<typename Type>
Type Max(const Type& lhs, const Type& rhs);

template<typename Type>
Type Min(const Type& lhs, const Type& rhs);

template<typename Type>
Type Clamp(const Type& val, const Type& minVal, const Type& maxVal);

template<typename Type>
Type Saturate(const Type& val);


Vec2f_Out RECON_VEC_CALLCONV Max(Vec2f_In lhs, Vec2f_In rhs);
Vec3f_Out RECON_VEC_CALLCONV Max(Vec3f_In lhs, Vec3f_In rhs);
Vec4f_Out RECON_VEC_CALLCONV Max(Vec4f_In lhs, Vec4f_In rhs);

Vec2f_Out RECON_VEC_CALLCONV Min(Vec2f_In lhs, Vec2f_In rhs);
Vec3f_Out RECON_VEC_CALLCONV Min(Vec3f_In lhs, Vec3f_In rhs);
Vec4f_Out RECON_VEC_CALLCONV Min(Vec4f_In lhs, Vec4f_In rhs);

Vec2f_Out RECON_VEC_CALLCONV Clamp(Vec2f_In val, Vec2f_In minVal, Vec2f_In maxVal);
Vec3f_Out RECON_VEC_CALLCONV Clamp(Vec3f_In val, Vec3f_In minVal, Vec3f_In maxVal);
Vec4f_Out RECON_VEC_CALLCONV Clamp(Vec4f_In val, Vec4f_In minVal, Vec4f_In maxVal);

Vec2f_Out RECON_VEC_CALLCONV Saturate(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV Saturate(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Saturate(Vec4f_In vVector);

Vec2f_Out RECON_VEC_CALLCONV MaxInt(Vec2f_In lhs, Vec2f_In rhs);
Vec3f_Out RECON_VEC_CALLCONV MaxInt(Vec3f_In lhs, Vec3f_In rhs);
Vec4f_Out RECON_VEC_CALLCONV MaxInt(Vec4f_In lhs, Vec4f_In rhs);

Vec2f_Out RECON_VEC_CALLCONV MinInt(Vec2f_In lhs, Vec2f_In rhs);
Vec3f_Out RECON_VEC_CALLCONV MinInt(Vec3f_In lhs, Vec3f_In rhs);
Vec4f_Out RECON_VEC_CALLCONV MinInt(Vec4f_In lhs, Vec4f_In rhs);

Vec2f_Out RECON_VEC_CALLCONV ClampInt(Vec2f_In val, Vec2f_In minVal, Vec2f_In maxVal);
Vec3f_Out RECON_VEC_CALLCONV ClampInt(Vec3f_In val, Vec3f_In minVal, Vec3f_In maxVal);
Vec4f_Out RECON_VEC_CALLCONV ClampInt(Vec4f_In val, Vec4f_In minVal, Vec4f_In maxVal);

float RECON_VEC_CALLCONV Lerp(const float& lhs, const float& rhs, const float& fLambda);
double RECON_VEC_CALLCONV Lerp(const double& lhs, const double& rhs, const double& fLambda);
Vec2f_Out RECON_VEC_CALLCONV Lerp(Vec2f_In lhs, Vec2f_In rhs, const float& fLambda);
Vec3f_Out RECON_VEC_CALLCONV Lerp(Vec3f_In lhs, Vec3f_In rhs, const float& fLambda);
Vec4f_Out RECON_VEC_CALLCONV Lerp(Vec4f_In lhs, Vec4f_In rhs, const float& fLambda);

s8 Abs(const s8& iScalar);
s16 Abs(const s16& iScalar);
s32 Abs(const s32& iScalar);
s64 Abs(const s64& iScalar);
float Abs(const float& fScalar);
double Abs(const double& fScalar);
Vec2f_Out RECON_VEC_CALLCONV Abs(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV Abs(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Abs(Vec4f_In vVector);

float Sqrt(const float& fScalar);
double Sqrt(const double& fScalar);
Vec2f_Out RECON_VEC_CALLCONV Sqrt(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV Sqrt(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Sqrt(Vec4f_In vVector);

float SqrtSafe(const float& fScalar, const float& safeVal = 0.0f);
double SqrtSafe(const double& fScalar, const double& safeVal = 0.0);
Vec2f_Out RECON_VEC_CALLCONV SqrtSafe(Vec2f_In vVector, Vec2f_In vSafeVec = Vec2f(I_ZERO));
Vec3f_Out RECON_VEC_CALLCONV SqrtSafe(Vec3f_In vVector, Vec3f_In vSafeVec = Vec3f(I_ZERO));
Vec4f_Out RECON_VEC_CALLCONV SqrtSafe(Vec4f_In vVector, Vec4f_In vSafeVec = Vec4f(I_ZERO));

template<VecElem splat> Vec2f_Out RECON_VEC_CALLCONV Splat(Vec2f_In lhs);
template<VecElem splat> Vec3f_Out RECON_VEC_CALLCONV Splat(Vec3f_In lhs);
template<VecElem splat> Vec4f_Out RECON_VEC_CALLCONV Splat(Vec4f_In lhs);

template<VecElem pX, VecElem pY> Vec2f_Out RECON_VEC_CALLCONV Permute(Vec2f_In lhs);
template<VecElem pX, VecElem pY, VecElem pZ> Vec3f_Out RECON_VEC_CALLCONV Permute(Vec3f_In lhs);
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> Vec4f_Out RECON_VEC_CALLCONV Permute(Vec4f_In lhs);

template<VecElem pX, VecElem pY> Vec2f_Out RECON_VEC_CALLCONV Permute(Vec2f_In lhs, Vec2f_In rhs);
template<VecElem pX, VecElem pY, VecElem pZ> Vec3f_Out RECON_VEC_CALLCONV Permute(Vec3f_In lhs, Vec3f_In rhs);
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> Vec4f_Out RECON_VEC_CALLCONV Permute(Vec4f_In lhs, Vec4f_In rhs);

s32 RECON_VEC_CALLCONV SignMask(Vec2f_In vVector);
s32 RECON_VEC_CALLCONV SignMask(Vec3f_In vVector);
s32 RECON_VEC_CALLCONV SignMask(Vec4f_In vVector);

Vec2f_Out RECON_VEC_CALLCONV SelectTF(Vec2f_In lhs, Vec2f_In rhs, Vec2f_In condition);
Vec3f_Out RECON_VEC_CALLCONV SelectTF(Vec3f_In lhs, Vec3f_In rhs, Vec3f_In condition);
Vec4f_Out RECON_VEC_CALLCONV SelectTF(Vec4f_In lhs, Vec4f_In rhs, Vec4f_In condition);


// Trigonometry

float Sin(const float& fRadians);
double Sin(const double& fRadians);
Vec2f_Out RECON_VEC_CALLCONV Sin(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV Sin(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV Sin(Vec4f_In vRadians);

float ASin(const float& fRadians);
double ASin(const double& fRadians);
Vec2f_Out RECON_VEC_CALLCONV ASin(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV ASin(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV ASin(Vec4f_In vRadians);

float Cos(const float& fRadians);
double Cos(const double& fRadians);
Vec2f_Out RECON_VEC_CALLCONV Cos(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV Cos(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV Cos(Vec4f_In vRadians);

float ACos(const float& fRadians);
double ACos(const double& fRadians);
Vec2f_Out RECON_VEC_CALLCONV ACos(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV ACos(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV ACos(Vec4f_In vRadians);

float Tan(const float& fRadians);
double Tan(const double& fRadians);
Vec2f_Out RECON_VEC_CALLCONV Tan(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV Tan(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV Tan(Vec4f_In vRadians);

float ATan(const float& fRadians);
double ATan(const double& fRadians);
Vec2f_Out RECON_VEC_CALLCONV ATan(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV ATan(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV ATan(Vec4f_In vRadians);

// Returns: Vec2f(Sin(), Cos());
Vec2f_Out RECON_VEC_CALLCONV SinCos(const float& fRadians);


// Comparison Functions

#define VEC_CMP_DECLBASE(name, varType)	VecCmpResult RECON_VEC_CALLCONV name ( varType##_In lhs, varType##_In rhs);

#define VEC_CMP_DECL(name, varType) bool RECON_VEC_CALLCONV name ( varType##_In lhs, varType##_In rhs);
#define VEC_CMP_DECL1(name, varType) VEC_CMP_DECL( name##X, varType)
#define VEC_CMP_DECL2(name, varType) VEC_CMP_DECL( name##XY, varType)
#define VEC_CMP_DECL3(name, varType) VEC_CMP_DECL( name##XYZ, varType)
#define VEC_CMP_DECL4(name, varType) VEC_CMP_DECL( name##XYZW, varType)

#define VEC_CMP_DECL_VEC2(name, varType)  \
	VEC_CMP_DECLBASE(name, varType) \
	VEC_CMP_DECL1(name, varType) \
	VEC_CMP_DECL2(name, varType)

#define VEC_CMP_DECL_VEC3(name, varType)  \
	VEC_CMP_DECL_VEC2(name, varType) \
	VEC_CMP_DECL3(name, varType)

#define VEC_CMP_DECL_VEC4(name, varType)  \
	VEC_CMP_DECL_VEC3(name, varType) \
	VEC_CMP_DECL4(name, varType)

VEC_CMP_DECL_VEC2(IsEqual, Vec2f)
VEC_CMP_DECL_VEC3(IsEqual, Vec3f)
VEC_CMP_DECL_VEC4(IsEqual, Vec4f)

VEC_CMP_DECL_VEC2(IsNotEqual, Vec2f)
VEC_CMP_DECL_VEC3(IsNotEqual, Vec3f)
VEC_CMP_DECL_VEC4(IsNotEqual, Vec4f)

VEC_CMP_DECL_VEC2(IsGreaterThan, Vec2f)
VEC_CMP_DECL_VEC3(IsGreaterThan, Vec3f)
VEC_CMP_DECL_VEC4(IsGreaterThan, Vec4f)

VEC_CMP_DECL_VEC2(IsGreaterThanOrEqual, Vec2f)
VEC_CMP_DECL_VEC3(IsGreaterThanOrEqual, Vec3f)
VEC_CMP_DECL_VEC4(IsGreaterThanOrEqual, Vec4f)

VEC_CMP_DECL_VEC2(IsLessThan, Vec2f)
VEC_CMP_DECL_VEC3(IsLessThan, Vec3f)
VEC_CMP_DECL_VEC4(IsLessThan, Vec4f)

VEC_CMP_DECL_VEC2(IsLessThanOrEqual, Vec2f)
VEC_CMP_DECL_VEC3(IsLessThanOrEqual, Vec3f)
VEC_CMP_DECL_VEC4(IsLessThanOrEqual, Vec4f)

VEC_CMP_DECL_VEC2(IsEqualInt, Vec2f)
VEC_CMP_DECL_VEC3(IsEqualInt, Vec3f)
VEC_CMP_DECL_VEC4(IsEqualInt, Vec4f)

VEC_CMP_DECL_VEC2(IsGreaterThanInt, Vec2f)
VEC_CMP_DECL_VEC3(IsGreaterThanInt, Vec3f)
VEC_CMP_DECL_VEC4(IsGreaterThanInt, Vec4f)

VEC_CMP_DECL_VEC2(IsLessThanInt, Vec2f)
VEC_CMP_DECL_VEC3(IsLessThanInt, Vec3f)
VEC_CMP_DECL_VEC4(IsLessThanInt, Vec4f)

VEC_CMP_DECL_VEC2(IsNotEqualInt, Vec2f)
VEC_CMP_DECL_VEC3(IsNotEqualInt, Vec3f)
VEC_CMP_DECL_VEC4(IsNotEqualInt, Vec4f)

VEC_CMP_DECL_VEC2(IsGreaterThanOrEqualInt, Vec2f)
VEC_CMP_DECL_VEC3(IsGreaterThanOrEqualInt, Vec3f)
VEC_CMP_DECL_VEC4(IsGreaterThanOrEqualInt, Vec4f)

VEC_CMP_DECL_VEC2(IsLessThanOrEqualInt, Vec2f)
VEC_CMP_DECL_VEC3(IsLessThanOrEqualInt, Vec3f)
VEC_CMP_DECL_VEC4(IsLessThanOrEqualInt, Vec4f)

#undef VEC_CMP_DECL_VEC4
#undef VEC_CMP_DECL_VEC3
#undef VEC_CMP_DECL_VEC2
#undef VEC_CMP_DECL4
#undef VEC_CMP_DECL3
#undef VEC_CMP_DECL2
#undef VEC_CMP_DECL1
#undef VEC_CMP_DECLBASE
#undef VEC_CMP_DECL


// Arithmetic Operation:

#define VEC_ARITH_DECL(name, varType) \
	varType##_Out RECON_VEC_CALLCONV name(varType##_In lhs, varType##_In rhs);

// Floating Point Operations
VEC_ARITH_DECL(Add, Vec2f)
VEC_ARITH_DECL(Add, Vec3f)
VEC_ARITH_DECL(Add, Vec4f)

VEC_ARITH_DECL(Subtract, Vec2f)
VEC_ARITH_DECL(Subtract, Vec3f)
VEC_ARITH_DECL(Subtract, Vec4f)

VEC_ARITH_DECL(Multiply, Vec2f)
VEC_ARITH_DECL(Multiply, Vec3f)
VEC_ARITH_DECL(Multiply, Vec4f)

VEC_ARITH_DECL(Divide, Vec2f)
VEC_ARITH_DECL(Divide, Vec3f)
VEC_ARITH_DECL(Divide, Vec4f)


// Integer Operations
VEC_ARITH_DECL(AddInt, Vec2f)
VEC_ARITH_DECL(AddInt, Vec3f)
VEC_ARITH_DECL(AddInt, Vec4f)

VEC_ARITH_DECL(SubtractInt, Vec2f)
VEC_ARITH_DECL(SubtractInt, Vec3f)
VEC_ARITH_DECL(SubtractInt, Vec4f)

VEC_ARITH_DECL(MultiplyInt, Vec2f)
VEC_ARITH_DECL(MultiplyInt, Vec3f)
VEC_ARITH_DECL(MultiplyInt, Vec4f)

VEC_ARITH_DECL(DivideInt, Vec2f)
VEC_ARITH_DECL(DivideInt, Vec3f)
VEC_ARITH_DECL(DivideInt, Vec4f)

#undef VEC_ARITH_DECL


// Vector Math Functions

float RECON_VEC_CALLCONV Dot(Vec2f_In vVectorA, Vec2f_In vVectorB);
float RECON_VEC_CALLCONV Dot(Vec3f_In vVectorA, Vec3f_In vVectorB);
float RECON_VEC_CALLCONV Dot(Vec4f_In vVectorA, Vec4f_In vVectorB);

float RECON_VEC_CALLCONV Mag(Vec2f_In vVector);
float RECON_VEC_CALLCONV Mag(Vec3f_In vVector);
float RECON_VEC_CALLCONV Mag(Vec4f_In vVector);

float RECON_VEC_CALLCONV Length(Vec2f_In vVector);
float RECON_VEC_CALLCONV Length(Vec3f_In vVector);
float RECON_VEC_CALLCONV Length(Vec4f_In vVector);

float RECON_VEC_CALLCONV MagSq(Vec2f_In vVector);
float RECON_VEC_CALLCONV MagSq(Vec3f_In vVector);
float RECON_VEC_CALLCONV MagSq(Vec4f_In vVector);

float RECON_VEC_CALLCONV LengthSq(Vec2f_In vVector);
float RECON_VEC_CALLCONV LengthSq(Vec3f_In vVector);
float RECON_VEC_CALLCONV LengthSq(Vec4f_In vVector);

Vec2f_Out RECON_VEC_CALLCONV Normalize(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV Normalize(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Normalize(Vec4f_In vVector);
Mat33f_Out RECON_VEC_CALLCONV Normalize(Mat33f_In mMatrix);
Mat44f_Out RECON_VEC_CALLCONV Normalize(Mat44f_In mMatrix);

Vec2f_Out RECON_VEC_CALLCONV IntToFloat(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV IntToFloat(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV IntToFloat(Vec4f_In vVector);

Vec2f_Out RECON_VEC_CALLCONV FloatToInt(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV FloatToInt(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV FloatToInt(Vec4f_In vVector);

float Floor(const float& fScalar);
double Floor(const double& fScalar);
Vec2f_Out RECON_VEC_CALLCONV Floor(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV Floor(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Floor(Vec4f_In vVector);

float Ceil(const float& fScalar);
double Ceil(const double& fScalar);
Vec2f_Out RECON_VEC_CALLCONV Ceil(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV Ceil(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Ceil(Vec4f_In vVector);

float Trunc(const float& fScalar);
double Trunc(const double& fScalar);
Vec2f_Out RECON_VEC_CALLCONV Trunc(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV Trunc(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Trunc(Vec4f_In vVector);

float Round(const float& fScalar);
double Round(const double& fScalar);
Vec2f_Out RECON_VEC_CALLCONV Round(Vec2f& vVector);
Vec3f_Out RECON_VEC_CALLCONV Round(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Round(Vec4f_In vVector);

float Log2(const float& fScalar);
double Log2(const double& fScalar);
Vec2f_Out RECON_VEC_CALLCONV Log2(Vec2f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV Log2(Vec3f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Log2(Vec4f_In vVector);

Mat44f_Out RECON_VEC_CALLCONV Lerp(Mat44f_In MatrixA, Mat44f_In MatrixB, const float fLambda);

Vec3f_Out RECON_VEC_CALLCONV Cross(Vec3f_In lhs, Vec3f_In rhs);


// Matrix Function

Mat44f RECON_VEC_CALLCONV Mat34ToMat44(Mat34f_In mMatrix);
Mat34f RECON_VEC_CALLCONV Mat44ToMat34(Mat44f_In mMatrix);

Mat44f_Out RECON_VEC_CALLCONV MatrixInverse(Mat44f_In mMatrix);

Mat33f_Out RECON_VEC_CALLCONV Transpose(Mat33f_In mMatrix);
Mat44f_Out RECON_VEC_CALLCONV Transpose(Mat44f_In mMatrix);

Mat44f_Out RECON_VEC_CALLCONV Transpose3x3(Mat44f_In mMatrix);

Mat44f_Out RECON_VEC_CALLCONV RotateAround(Vec3f_In origin, Mat44f_In rotatorsMatrix, Mat44f_In rotationMatrix);

Mat44f_Out RECON_VEC_CALLCONV MakePerspectiveMatrix(float fFOV, float fAspectRatio, float fNearClip, float fFarClip);
Mat44f_Out RECON_VEC_CALLCONV MakeOrthographicMatrix(float fWidth, float fHeight, float fNear, float fFar);
Mat44f_Out RECON_VEC_CALLCONV MakeTextureMatrixOffset(u32 unWidth, u32 unHeight);

float CalculateGaussianWeight(s32 nOffset, float fSigma = 1.0f);

// unRadius - Number of Pixels to Blur In a Single Direction Including the Center Pixel
inline void CalculateGaussianWeights(float* pGaussianWeights, u32 unRadius, float fLimit = 1.0f);

#if SSE_AVAILABLE

ScalarV_Out RECON_VEC_CALLCONV Max(ScalarV_In lhs, ScalarV_In rhs);
Vec2V_Out RECON_VEC_CALLCONV Max(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out RECON_VEC_CALLCONV Max(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out RECON_VEC_CALLCONV Max(Vec4V_In lhs, Vec4V_In rhs);

ScalarV_Out RECON_VEC_CALLCONV Min(ScalarV_In lhs, ScalarV_In rhs);
Vec2V_Out RECON_VEC_CALLCONV Min(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out RECON_VEC_CALLCONV Min(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out RECON_VEC_CALLCONV Min(Vec4V_In lhs, Vec4V_In rhs);

ScalarV_Out RECON_VEC_CALLCONV Clamp(ScalarV_In val, ScalarV_In minVal, ScalarV_In maxVal);
Vec2V_Out RECON_VEC_CALLCONV Clamp(Vec2V_In val, Vec2V_In minVal, Vec2V_In maxVal);
Vec3V_Out RECON_VEC_CALLCONV Clamp(Vec3V_In val, Vec3V_In minVal, Vec3V_In maxVal);
Vec4V_Out RECON_VEC_CALLCONV Clamp(Vec4V_In val, Vec4V_In minVal, Vec4V_In maxVal);

ScalarV_Out RECON_VEC_CALLCONV Saturate(ScalarV_In vVector);
Vec2V_Out RECON_VEC_CALLCONV Saturate(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Saturate(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Saturate(Vec4V_In vVector);

ScalarV_Out RECON_VEC_CALLCONV MaxInt(ScalarV_In lhs, ScalarV_In rhs);
Vec2V_Out RECON_VEC_CALLCONV MaxInt(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out RECON_VEC_CALLCONV MaxInt(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out RECON_VEC_CALLCONV MaxInt(Vec4V_In lhs, Vec4V_In rhs);

ScalarV_Out RECON_VEC_CALLCONV MinInt(ScalarV_In lhs, ScalarV_In rhs);
Vec2V_Out RECON_VEC_CALLCONV MinInt(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out RECON_VEC_CALLCONV MinInt(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out RECON_VEC_CALLCONV MinInt(Vec4V_In lhs, Vec4V_In rhs);

ScalarV_Out RECON_VEC_CALLCONV ClampInt(ScalarV_In val, ScalarV_In minVal, ScalarV_In maxVal);
Vec2V_Out RECON_VEC_CALLCONV ClampInt(Vec2V_In val, Vec2V_In minVal, Vec2V_In maxVal);
Vec3V_Out RECON_VEC_CALLCONV ClampInt(Vec3V_In val, Vec3V_In minVal, Vec3V_In maxVal);
Vec4V_Out RECON_VEC_CALLCONV ClampInt(Vec4V_In val, Vec4V_In minVal, Vec4V_In maxVal);

ScalarV_Out RECON_VEC_CALLCONV Lerp(ScalarV_In lhs, ScalarV_In rhs, ScalarV_In vLambda);
Vec2V_Out RECON_VEC_CALLCONV Lerp(Vec2V_In lhs, Vec2V_In rhs, ScalarV_In vLambda);
Vec3V_Out RECON_VEC_CALLCONV Lerp(Vec3V_In lhs, Vec3V_In rhs, ScalarV_In vLambda);
Vec4V_Out RECON_VEC_CALLCONV Lerp(Vec4V_In lhs, Vec4V_In rhs, ScalarV_In vLambda);

ScalarV_Out RECON_VEC_CALLCONV Abs(ScalarV_In vScalar);
Vec2V_Out RECON_VEC_CALLCONV Abs(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Abs(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Abs(Vec4V_In vVector);

template<VecElem splat> Vec2V_Out RECON_VEC_CALLCONV Splat(Vec2V_In lhs);
template<VecElem splat> Vec3V_Out RECON_VEC_CALLCONV Splat(Vec3V_In lhs);
template<VecElem splat> Vec4V_Out RECON_VEC_CALLCONV Splat(Vec4V_In lhs);

template<VecElem pX, VecElem pY> Vec2V_Out RECON_VEC_CALLCONV Permute(Vec2V_In lhs);
template<VecElem pX, VecElem pY, VecElem pZ> Vec3V_Out RECON_VEC_CALLCONV Permute(Vec3V_In lhs);
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> Vec4V_Out RECON_VEC_CALLCONV Permute(Vec4V_In lhs);

template<VecElem pX, VecElem pY> Vec2V_Out RECON_VEC_CALLCONV Permute(Vec2V_In lhs, Vec2V_In rhs);
template<VecElem pX, VecElem pY, VecElem pZ> Vec3V_Out RECON_VEC_CALLCONV Permute(Vec3V_In lhs, Vec3V_In rhs);
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> Vec4V_Out RECON_VEC_CALLCONV Permute(Vec4V_In lhs, Vec4V_In rhs);

s32 RECON_VEC_CALLCONV SignMask(Vec2V_In vVector);
s32 RECON_VEC_CALLCONV SignMask(Vec3V_In vVector);
s32 RECON_VEC_CALLCONV SignMask(Vec4V_In vVector);

ScalarV_Out RECON_VEC_CALLCONV SelectTF(ScalarV_In condition, ScalarV_In ifTrue, ScalarV_In ifFalse);
Vec2V_Out RECON_VEC_CALLCONV SelectTF(Vec2V_In condition, Vec2V_In ifTrue, Vec2V_In ifFalse);
Vec3V_Out RECON_VEC_CALLCONV SelectTF(Vec3V_In condition, Vec3V_In ifTrue, Vec3V_In ifFalse);
Vec4V_Out RECON_VEC_CALLCONV SelectTF(Vec4V_In condition, Vec4V_In ifTrue, Vec4V_In ifFalse);

template<VecElem elem> ScalarV_Out RECON_VEC_CALLCONV ScalarVFromElement(Vector_In vVector);
template<VecElem elem> ScalarV_Out RECON_VEC_CALLCONV ScalarVFromElement(Vec2V_In vVector);
template<VecElem elem> ScalarV_Out RECON_VEC_CALLCONV ScalarVFromElement(Vec3V_In vVector);
template<VecElem elem> ScalarV_Out RECON_VEC_CALLCONV ScalarVFromElement(Vec4V_In vVector);


// Trigonometry Functions:

ScalarV_Out RECON_VEC_CALLCONV Sin(ScalarV_In vRadians);
Vec2V_Out RECON_VEC_CALLCONV Sin(Vec2V_In vRadians);
Vec3V_Out RECON_VEC_CALLCONV Sin(Vec3V_In vRadians);
Vec4V_Out RECON_VEC_CALLCONV Sin(Vec4V_In vRadians);

ScalarV_Out RECON_VEC_CALLCONV ASin(ScalarV_In vRadians);
Vec2f_Out RECON_VEC_CALLCONV ASin(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV ASin(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV ASin(Vec4f_In vRadians);

ScalarV_Out RECON_VEC_CALLCONV Cos(ScalarV_In vRadians);
Vec2f_Out RECON_VEC_CALLCONV Cos(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV Cos(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV Cos(Vec4f_In vRadians);

ScalarV_Out RECON_VEC_CALLCONV ACos(ScalarV_In vRadians);
Vec2f_Out RECON_VEC_CALLCONV ACos(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV ACos(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV ACos(Vec4f_In vRadians);

ScalarV_Out RECON_VEC_CALLCONV Tan(ScalarV_In vRadians);
Vec2f_Out RECON_VEC_CALLCONV Tan(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV Tan(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV Tan(Vec4f_In vRadians);

ScalarV_Out RECON_VEC_CALLCONV ATan(ScalarV_In vRadians);
Vec2f_Out RECON_VEC_CALLCONV ATan(Vec2f_In vRadians);
Vec3f_Out RECON_VEC_CALLCONV ATan(Vec3f_In vRadians);
Vec4f_Out RECON_VEC_CALLCONV ATan(Vec4f_In vRadians);

// Returns: Vec2V(Sin(), Cos(), Sin(), Cos());
Vec2V_Out RECON_VEC_CALLCONV SinCos(ScalarV_In vRadians);


// Comparison Functions:


#define VEC_CMP_DECLBASE(name, varType)	varType##_Out RECON_VEC_CALLCONV name ( varType##_In lhs, varType##_In rhs);

#define VEC_CMP_DECL(name, varType) bool RECON_VEC_CALLCONV name ( varType##_In lhs, varType##_In rhs);
#define VEC_CMP_DECL1(name, varType) VEC_CMP_DECL( name##X, varType)
#define VEC_CMP_DECL2(name, varType) VEC_CMP_DECL( name##XY, varType)
#define VEC_CMP_DECL3(name, varType) VEC_CMP_DECL( name##XYZ, varType)
#define VEC_CMP_DECL4(name, varType) VEC_CMP_DECL( name##XYZW, varType)

#define VEC_CMP_DECL_VEC2(name, varType)  \
	VEC_CMP_DECLBASE(name, varType) \
	VEC_CMP_DECL1(name, varType) \
	VEC_CMP_DECL2(name, varType)

#define VEC_CMP_DECL_VEC3(name, varType)  \
	VEC_CMP_DECL_VEC2(name, varType) \
	VEC_CMP_DECL3(name, varType)

#define VEC_CMP_DECL_VEC4(name, varType)  \
	VEC_CMP_DECL_VEC3(name, varType) \
	VEC_CMP_DECL4(name, varType)

VEC_CMP_DECL_VEC2(IsEqual, ScalarV)
VEC_CMP_DECL_VEC2(IsEqual, Vec2V)
VEC_CMP_DECL_VEC3(IsEqual, Vec3V)
VEC_CMP_DECL_VEC4(IsEqual, Vec4V)

VEC_CMP_DECL_VEC2(IsNotEqual, ScalarV)
VEC_CMP_DECL_VEC2(IsNotEqual, Vec2V)
VEC_CMP_DECL_VEC3(IsNotEqual, Vec3V)
VEC_CMP_DECL_VEC4(IsNotEqual, Vec4V)

VEC_CMP_DECL_VEC2(IsGreaterThan, ScalarV)
VEC_CMP_DECL_VEC2(IsGreaterThan, Vec2V)
VEC_CMP_DECL_VEC3(IsGreaterThan, Vec3V)
VEC_CMP_DECL_VEC4(IsGreaterThan, Vec4V)

VEC_CMP_DECL_VEC2(IsGreaterThanOrEqual, ScalarV)
VEC_CMP_DECL_VEC2(IsGreaterThanOrEqual, Vec2V)
VEC_CMP_DECL_VEC3(IsGreaterThanOrEqual, Vec3V)
VEC_CMP_DECL_VEC4(IsGreaterThanOrEqual, Vec4V)

VEC_CMP_DECL_VEC2(IsLessThan, ScalarV)
VEC_CMP_DECL_VEC2(IsLessThan, Vec2V)
VEC_CMP_DECL_VEC3(IsLessThan, Vec3V)
VEC_CMP_DECL_VEC4(IsLessThan, Vec4V)

VEC_CMP_DECL_VEC2(IsLessThanOrEqual, ScalarV)
VEC_CMP_DECL_VEC2(IsLessThanOrEqual, Vec2V)
VEC_CMP_DECL_VEC3(IsLessThanOrEqual, Vec3V)
VEC_CMP_DECL_VEC4(IsLessThanOrEqual, Vec4V)

VEC_CMP_DECL_VEC2(IsEqualInt, ScalarV)
VEC_CMP_DECL_VEC2(IsEqualInt, Vec2V)
VEC_CMP_DECL_VEC3(IsEqualInt, Vec3V)
VEC_CMP_DECL_VEC4(IsEqualInt, Vec4V)

VEC_CMP_DECL_VEC2(IsNotEqualInt, ScalarV)
VEC_CMP_DECL_VEC2(IsNotEqualInt, Vec2V)
VEC_CMP_DECL_VEC3(IsNotEqualInt, Vec3V)
VEC_CMP_DECL_VEC4(IsNotEqualInt, Vec4V)

VEC_CMP_DECL_VEC2(IsGreaterThanInt, ScalarV)
VEC_CMP_DECL_VEC2(IsGreaterThanInt, Vec2V)
VEC_CMP_DECL_VEC3(IsGreaterThanInt, Vec3V)
VEC_CMP_DECL_VEC4(IsGreaterThanInt, Vec4V)

VEC_CMP_DECL_VEC2(IsGreaterThanOrEqualInt, ScalarV)
VEC_CMP_DECL_VEC2(IsGreaterThanOrEqualInt, Vec2V)
VEC_CMP_DECL_VEC3(IsGreaterThanOrEqualInt, Vec3V)
VEC_CMP_DECL_VEC4(IsGreaterThanOrEqualInt, Vec4V)

VEC_CMP_DECL_VEC2(IsLessThanInt, ScalarV)
VEC_CMP_DECL_VEC2(IsLessThanInt, Vec2V)
VEC_CMP_DECL_VEC3(IsLessThanInt, Vec3V)
VEC_CMP_DECL_VEC4(IsLessThanInt, Vec4V)

VEC_CMP_DECL_VEC2(IsLessThanOrEqualInt, ScalarV)
VEC_CMP_DECL_VEC2(IsLessThanOrEqualInt, Vec2V)
VEC_CMP_DECL_VEC3(IsLessThanOrEqualInt, Vec3V)
VEC_CMP_DECL_VEC4(IsLessThanOrEqualInt, Vec4V)

#undef VEC_CMP_DECL_VEC4
#undef VEC_CMP_DECL_VEC3
#undef VEC_CMP_DECL_VEC2
#undef VEC_CMP_DECL4
#undef VEC_CMP_DECL3
#undef VEC_CMP_DECL2
#undef VEC_CMP_DECL1
#undef VEC_CMP_DECLBASE
#undef VEC_CMP_DECL



// Vector Math Functions

ScalarV_Out RECON_VEC_CALLCONV Sqrt(ScalarV_In vScalar);
Vec2V_Out RECON_VEC_CALLCONV Sqrt(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Sqrt(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Sqrt(Vec4V_In vVector);

ScalarV_Out RECON_VEC_CALLCONV SqrtSafe(ScalarV_In vScalar, ScalarV_In safeVec = ScalarV(I_ZERO));
Vec2V_Out RECON_VEC_CALLCONV SqrtSafe(Vec2V_In vVector, Vec2V_In safeVec = Vec2V(I_ZERO));
Vec3V_Out RECON_VEC_CALLCONV SqrtSafe(Vec3V_In vVector, Vec3V_In safeVec = Vec3V(I_ZERO));
Vec4V_Out RECON_VEC_CALLCONV SqrtSafe(Vec4V_In vVector, Vec4V_In safeVec = Vec4V(I_ZERO));

ScalarV RECON_VEC_CALLCONV Dot(Vec2V_In vVectorA, Vec2V_In vVectorB);
ScalarV RECON_VEC_CALLCONV Dot(Vec3V_In vVectorA, Vec3V_In vVectorB);
ScalarV RECON_VEC_CALLCONV Dot(Vec4V_In vVectorA, Vec4V_In vVectorB);

ScalarV RECON_VEC_CALLCONV Mag(Vec2V_In vVector);
ScalarV RECON_VEC_CALLCONV Mag(Vec3V_In vVector);
ScalarV RECON_VEC_CALLCONV Mag(Vec4V_In vVector);

ScalarV RECON_VEC_CALLCONV Length(Vec2V_In vVector);
ScalarV RECON_VEC_CALLCONV Length(Vec3V_In vVector);
ScalarV RECON_VEC_CALLCONV Length(Vec4V_In vVector);

ScalarV RECON_VEC_CALLCONV MagSq(Vec2V_In vVector);
ScalarV RECON_VEC_CALLCONV MagSq(Vec3V_In vVector);
ScalarV RECON_VEC_CALLCONV MagSq(Vec4V_In vVector);

ScalarV RECON_VEC_CALLCONV LengthSq(Vec2V_In vVector);
ScalarV RECON_VEC_CALLCONV LengthSq(Vec3V_In vVector);
ScalarV RECON_VEC_CALLCONV LengthSq(Vec4V_In vVector);

Vec2V_Out RECON_VEC_CALLCONV Normalize(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Normalize(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Normalize(Vec4V_In vVector);
//Mat33V_Out RECON_VEC_CALLCONV Normalize(Mat33V_In mMatrix);
Mat44V_Out RECON_VEC_CALLCONV Normalize(Mat44V_In mMatrix);

ScalarV_Out RECON_VEC_CALLCONV AddInt(ScalarV_In lhs, ScalarV_In rhs);
Vec2V_Out RECON_VEC_CALLCONV AddInt(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out RECON_VEC_CALLCONV AddInt(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out RECON_VEC_CALLCONV AddInt(Vec4V_In lhs, Vec4V_In rhs);

ScalarV_Out RECON_VEC_CALLCONV SubtractInt(ScalarV_In lhs, ScalarV_In rhs);
Vec2V_Out RECON_VEC_CALLCONV SubtractInt(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out RECON_VEC_CALLCONV SubtractInt(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out RECON_VEC_CALLCONV SubtractInt(Vec4V_In lhs, Vec4V_In rhs);

ScalarV_Out RECON_VEC_CALLCONV MultiplyInt(ScalarV_In lhs, ScalarV_In rhs);
Vec2V_Out RECON_VEC_CALLCONV MultiplyInt(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out RECON_VEC_CALLCONV MultiplyInt(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out RECON_VEC_CALLCONV MultiplyInt(Vec4V_In lhs, Vec4V_In rhs);

ScalarV_Out RECON_VEC_CALLCONV IntToFloat(ScalarV_In vVector);
Vec2V_Out RECON_VEC_CALLCONV IntToFloat(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV IntToFloat(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV IntToFloat(Vec4V_In vVector);

ScalarV_Out RECON_VEC_CALLCONV FloatToInt(ScalarV_In vVector);
Vec2V_Out RECON_VEC_CALLCONV FloatToInt(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV FloatToInt(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV FloatToInt(Vec4V_In vVector);

ScalarV_Out RECON_VEC_CALLCONV Floor(ScalarV_In vVector);
Vec2V_Out RECON_VEC_CALLCONV Floor(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Floor(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Floor(Vec4V_In vVector);

ScalarV_Out RECON_VEC_CALLCONV Ceil(ScalarV_In vVector);
Vec2V_Out RECON_VEC_CALLCONV Ceil(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Ceil(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Ceil(Vec4V_In vVector);

ScalarV_Out RECON_VEC_CALLCONV Trunc(ScalarV_In vVector);
Vec2V_Out RECON_VEC_CALLCONV Trunc(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Trunc(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Trunc(Vec4V_In vVector);

ScalarV_Out RECON_VEC_CALLCONV Round(ScalarV_In vVector);
Vec2V_Out RECON_VEC_CALLCONV Round(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Round(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Round(Vec4V_In vVector);

ScalarV_Out RECON_VEC_CALLCONV Log2(ScalarV_In vScalar);
Vec2V_Out RECON_VEC_CALLCONV Log2(Vec2V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Log2(Vec3V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Log2(Vec4V_In vVector);

Mat44V_Out RECON_VEC_CALLCONV Lerp(Mat44V_In MatrixA, Mat44V_In MatrixB, ScalarV_In vLambda);

Vec3V_Out RECON_VEC_CALLCONV Cross(Vec3V_In lhs, Vec3V_In rhs);

Mat44V RECON_VEC_CALLCONV Mat34ToMat44(Mat34V_In mMatrix);
Mat34V RECON_VEC_CALLCONV Mat44ToMat34(Mat44V_In mMatrix);

Mat44V_Out RECON_VEC_CALLCONV MatrixInverse(Mat44V_In mMatrix);

Mat44V_Out RECON_VEC_CALLCONV Transpose(Mat44V_In mMatrix);

Mat44V_Out RECON_VEC_CALLCONV Transpose3x3(Mat44V_In mMatrix);

Mat44V_Out RECON_VEC_CALLCONV RotateAround(Vec3V_In origin, Mat44V_In rotatorsMatrix, Mat44V_In rotationMatrix);

Mat44V RECON_VEC_CALLCONV MakePerspectiveMatrixV(float fFOV, float fAspectRatio, float fNearClip, float fFarClip);

Mat44V RECON_VEC_CALLCONV MakeOrthographicMatrixV(float fWidth, float fHeight, float fNear, float fFar);

Mat44V RECON_VEC_CALLCONV MakeTextureMatrixOffsetV(unsigned int unWidth, unsigned int unHeight);
#endif //SSE_AVAILABLE

class VecCmpResult
{
private:
	Vec4V m_VectorMask;

public:
	explicit VecCmpResult(const bool& bX);
	VecCmpResult(const bool& bX, const bool& bY);
	VecCmpResult(const bool& bX, const bool& bY, const bool& bZ);
	VecCmpResult(const bool& bX, const bool& bY, const bool& bZ, const bool bW);

#if SSE_AVAILABLE
	VecCmpResult(Vector_In result);
#endif // SSE_AVAILABLE

	explicit operator Vec2f() const;
	explicit operator Vec3f() const;
	explicit operator Vec4f() const;

#if SSE_AVAILABLE
	explicit operator Vec2V() const;
	explicit operator Vec3V() const;
	explicit operator Vec4V() const;
	explicit operator Vector() const;
#endif // SSE_AVAILABLE

	int GetResultMask() const;
	operator s32 () const;

	bool IsTrueAny() const;
	bool IsTrueAll() const;

	template<VecElem index>
	__forceinline bool IsTrue() const;

	template<VecElem index0, VecElem index1>
	__forceinline bool IsTrue() const;

	template<VecElem index0, VecElem index1, VecElem index2>
	bool IsTrue() const;
};

#include "GlobalMathFuncs.inl"

#endif // GLOBALMATHFUNCS_H