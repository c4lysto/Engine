#ifndef GLOBALMATHFUNCS_H
#define GLOBALMATHFUNCS_H

//#ifndef GLOBALMATHFUNCS_INL
//#define GLOBALMATHFUNCS_INL

#include "MathDeclarations.h"
//#include "VecCmpResult.h"

#ifndef MATHLIB_H
#error "Don't Include GlobalMathFunc.h Directly. Include MathLib.h Instead."
#endif // MATHLIB_H

class VecCmpResult;


// Utility Functions

template<typename Type>
Type Max(Type lhs, Type rhs);

template<typename Type>
Type Min(Type lhs, Type rhs);

template<typename Type>
Type Clamp(Type val, Type minVal, Type maxVal);

template<typename Type>
Type Saturate(Type val);

float Lerp(const float& lhs, const float& rhs, const float& fLambda);
double Lerp(const double& lhs, const double& rhs, const double& fLambda);
Vec2f_Out Lerp(Vec2f_In lhs, Vec2f_In rhs, const float& fLambda);
Vec3f_Out Lerp(Vec3f_In lhs, Vec3f_In rhs, const float& fLambda);
Vec4f_Out Lerp(Vec4f_In lhs, Vec4f_In rhs, const float& fLambda);

float Abs(const float& fScalar);
double Abs(const double& fScalar);
Vec2f_Out Abs(Vec2f_In vec);
Vec3f_Out Abs(Vec3f_In vec);
Vec4f_Out Abs(Vec4f_In vec);

float Sqrt(const float& fScalar);
double Sqrt(const double& fScalar);
Vec2f_Out Sqrt(Vec2f_In vec);
Vec3f_Out Sqrt(Vec3f_In vec);
Vec4f_Out Sqrt(Vec4f_In vec);

template<VecElem pX, VecElem pY> Vec2f_Out Permute(Vec2f_In lhs);
template<VecElem pX, VecElem pY, VecElem pZ> Vec3f_Out Permute(Vec3f_In lhs);
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> Vec4f_Out Permute(Vec4f_In lhs);

template<VecElem pX, VecElem pY> Vec2f_Out Permute(Vec2f_In lhs, Vec2f_In rhs);
template<VecElem pX, VecElem pY, VecElem pZ> Vec3f_Out Permute(Vec3f_In lhs, Vec3f_In rhs);
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> Vec4f_Out Permute(Vec4f_In lhs, Vec4f_In rhs);

s32 SignMask(Vec2f_In vVector);
s32 SignMask(Vec3f_In vVector);
s32 SignMask(Vec4f_In vVector);


// Comparison Functions

#define VEC_CMP_DECLBASE(name, varType)	VecCmpResult name ( varType##_In lhs, varType##_In rhs);

#define VEC_CMP_DECL(name, varType) bool name ( varType##_In lhs, varType##_In rhs);
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
	varType##_Out name (varType##_In lhs, varType##_In rhs);

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

float Dot(Vec2f_In vVectorA, Vec2f_In vVectorB);
float Dot(Vec3f_In vVectorA, Vec3f_In vVectorB);
float Dot(Vec4f_In vVectorA, Vec4f_In vVectorB);

float Mag(Vec2f_In vVector);
float Mag(Vec3f_In vVector);
float Mag(Vec4f_In vVector);

float Length(Vec2f_In vVector);
float Length(Vec3f_In vVector);
float Length(Vec4f_In vVector);

float MagSq(Vec2f_In vVector);
float MagSq(Vec3f_In vVector);
float MagSq(Vec4f_In vVector);

float LengthSq(Vec2f_In vVector);
float LengthSq(Vec3f_In vVector);
float LengthSq(Vec4f_In vVector);

Vec2f_Out Normalize(Vec2f_In vVector);
Vec3f_Out Normalize(Vec3f_In vVector);
Vec4f_Out Normalize(Vec4f_In vVector);
Mat33f_Out Normalize(Mat33f_In mMatrix);
Mat44f_Out Normalize(Mat44f_In mMatrix);

Vec2f_Out IntToFloat(Vec2f_In vVector);
Vec3f_Out IntToFloat(Vec3f_In vVector);
Vec4f_Out IntToFloat(Vec4f_In vVector);

Vec2f_Out FloatToInt(Vec2f_In vVector);
Vec3f_Out FloatToInt(Vec3f_In vVector);
Vec4f_Out FloatToInt(Vec4f_In vVector);

Vec2f_Out Floor(Vec2f_In vVector);
Vec3f_Out Floor(Vec3f_In vVector);
Vec4f_Out Floor(Vec4f_In vVector);

Vec2f_Out Ceil(Vec2f_In vVector);
Vec3f_Out Ceil(Vec3f_In vVector);
Vec4f_Out Ceil(Vec4f_In vVector);

Vec2f_Out Trunc(Vec2f_In vVector);
Vec3f_Out Trunc(Vec3f_In vVector);
Vec4f_Out Trunc(Vec4f_In vVector);

Vec2f_Out Round(Vec2f& vVector);
Vec3f_Out Round(Vec3f_In vVector);
Vec4f_Out Round(Vec4f_In vVector);

Mat44f_Out Lerp(Mat44f_In MatrixA, Mat44f_In MatrixB, const float fLambda);

Vec3f_Out Cross(Vec3f_In lhs, Vec3f_In rhs);


// Matrix Function

Mat44f_Out MatrixInverse(Mat44f_In mMatrix);

Mat33f_Out Transpose(Mat33f_In mMatrix);
Mat44f_Out Transpose(Mat44f_In mMatrix);

Mat44f_Out Transpose3x3(Mat44f_In mMatrix);

Mat44f_Out RotateAround(Vec3f_In origin, Mat44f_In rotatorsMatrix, Mat44f_In rotationMatrix);

Mat44f_Out MakePerspectiveMatrix(float fFOV, float fAspectRatio, float fNearClip, float fFarClip);
Mat44f_Out MakeOrthographicMatrix(float fWidth, float fHeight, float fNear, float fFar);
Mat44f_Out MakeTextureMatrixOffset(u32 unWidth, u32 unHeight);

float CalculateGaussianWeight(s32 nOffset, float fSigma = 1.0f);

// unRadius - Number of Pixels to Blur In a Single Direction Including the Center Pixel
inline void CalculateGaussianWeights(_Out_writes_all_(unRadius) float* pGaussianWeights, u32 unRadius, float fLimit = 1.0f);

#if SSE_AVAILABLE
ScalarV_Out Lerp(ScalarV_In lhs, ScalarV_In rhs, ScalarV_In vLambda);
Vec2V_Out Lerp(Vec2V_In lhs, Vec2V_In rhs, ScalarV_In vLambda);
Vec3V_Out Lerp(Vec3V_In lhs, Vec3V_In rhs, ScalarV_In vLambda);
Vec4V_Out Lerp(Vec4V_In lhs, Vec4V_In rhs, ScalarV_In vLambda);

ScalarV_Out Abs(ScalarV_In vScalar);
Vec2V_Out Abs(Vec2V_In vec);
Vec3V_Out Abs(Vec3V_In vec);
Vec4V_Out Abs(Vec4V_In vec);

template<VecElem pX, VecElem pY> Vec2V_Out Permute(Vec2V_In lhs);
template<VecElem pX, VecElem pY, VecElem pZ> Vec3V_Out Permute(Vec3V_In lhs);
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> Vec4V_Out Permute(Vec4V_In lhs);

template<VecElem pX, VecElem pY> Vec2V_Out Permute(Vec2V_In lhs, Vec2V_In rhs);
template<VecElem pX, VecElem pY, VecElem pZ> Vec3V_Out Permute(Vec3V_In lhs, Vec3V_In rhs);
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> Vec4V_Out Permute(Vec4V_In lhs, Vec4V_In rhs);

s32 SignMask(Vec2V_In vVector);
s32 SignMask(Vec3V_In vVector);
s32 SignMask(Vec4V_In vVector);

template<VecElem elem> ScalarV_Out ScalarVFromElement(Vector_In vVector);
template<VecElem elem> ScalarV_Out ScalarVFromElement(Vec2V_In vVector);
template<VecElem elem> ScalarV_Out ScalarVFromElement(Vec3V_In vVector);
template<VecElem elem> ScalarV_Out ScalarVFromElement(Vec4V_In vVector);



// Comparison Functions:


#define VEC_CMP_DECLBASE(name, varType)	varType##_Out name ( varType##_In lhs, varType##_In rhs);

#define VEC_CMP_DECL(name, varType) bool name ( varType##_In lhs, varType##_In rhs);
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

VEC_CMP_DECL_VEC2(IsEqual, Vec2V)
VEC_CMP_DECL_VEC3(IsEqual, Vec3V)
VEC_CMP_DECL_VEC4(IsEqual, Vec4V)

VEC_CMP_DECL_VEC2(IsNotEqual, Vec2V)
VEC_CMP_DECL_VEC3(IsNotEqual, Vec3V)
VEC_CMP_DECL_VEC4(IsNotEqual, Vec4V)

VEC_CMP_DECL_VEC2(IsGreaterThan, Vec2V)
VEC_CMP_DECL_VEC3(IsGreaterThan, Vec3V)
VEC_CMP_DECL_VEC4(IsGreaterThan, Vec4V)

VEC_CMP_DECL_VEC2(IsGreaterThanOrEqual, Vec2V)
VEC_CMP_DECL_VEC3(IsGreaterThanOrEqual, Vec3V)
VEC_CMP_DECL_VEC4(IsGreaterThanOrEqual, Vec4V)

VEC_CMP_DECL_VEC2(IsLessThan, Vec2V)
VEC_CMP_DECL_VEC3(IsLessThan, Vec3V)
VEC_CMP_DECL_VEC4(IsLessThan, Vec4V)

VEC_CMP_DECL_VEC2(IsLessThanOrEqual, Vec2V)
VEC_CMP_DECL_VEC3(IsLessThanOrEqual, Vec3V)
VEC_CMP_DECL_VEC4(IsLessThanOrEqual, Vec4V)

VEC_CMP_DECL_VEC2(IsEqualInt, Vec2V)
VEC_CMP_DECL_VEC3(IsEqualInt, Vec3V)
VEC_CMP_DECL_VEC4(IsEqualInt, Vec4V)

VEC_CMP_DECL_VEC2(IsNotEqualInt, Vec2V)
VEC_CMP_DECL_VEC3(IsNotEqualInt, Vec3V)
VEC_CMP_DECL_VEC4(IsNotEqualInt, Vec4V)

VEC_CMP_DECL_VEC2(IsGreaterThanInt, Vec2V)
VEC_CMP_DECL_VEC3(IsGreaterThanInt, Vec3V)
VEC_CMP_DECL_VEC4(IsGreaterThanInt, Vec4V)

VEC_CMP_DECL_VEC2(IsGreaterThanOrEqualInt, Vec2V)
VEC_CMP_DECL_VEC3(IsGreaterThanOrEqualInt, Vec3V)
VEC_CMP_DECL_VEC4(IsGreaterThanOrEqualInt, Vec4V)

VEC_CMP_DECL_VEC2(IsLessThanInt, Vec2V)
VEC_CMP_DECL_VEC3(IsLessThanInt, Vec3V)
VEC_CMP_DECL_VEC4(IsLessThanInt, Vec4V)

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

ScalarV_Out Sqrt(ScalarV_In vScalar);
Vec2V_Out Sqrt(Vec2V_In vec);
Vec3V_Out Sqrt(Vec3V_In vec);
Vec4V_Out Sqrt(Vec4V_In vec);

ScalarV Dot(Vec2V_In vVectorA, Vec2V_In vVectorB);
ScalarV Dot(Vec3V_In vVectorA, Vec3V_In vVectorB);
ScalarV Dot(Vec4V_In vVectorA, Vec4V_In vVectorB);

ScalarV Mag(Vec2V_In vVector);
ScalarV Mag(Vec3V_In vVector);
ScalarV Mag(Vec4V_In vVector);

ScalarV Length(Vec2V_In vVector);
ScalarV Length(Vec3V_In vVector);
ScalarV Length(Vec4V_In vVector);

ScalarV MagSq(Vec2V_In vVector);
ScalarV MagSq(Vec3V_In vVector);
ScalarV MagSq(Vec4V_In vVector);

ScalarV LengthSq(Vec2V_In vVector);
ScalarV LengthSq(Vec3V_In vVector);
ScalarV LengthSq(Vec4V_In vVector);

Vec2V_Out Normalize(Vec2V_In vVector);
Vec3V_Out Normalize(Vec3V_In vVector);
Vec4V_Out Normalize(Vec4V_In vVector);
//Mat33V_Out Normalize(Mat33V_In mMatrix);
Mat44V_Out Normalize(Mat44V_In mMatrix);

Vec2V_Out AddInt(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out AddInt(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out AddInt(Vec4V_In lhs, Vec4V_In rhs);

Vec2V_Out SubtractInt(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out SubtractInt(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out SubtractInt(Vec4V_In lhs, Vec4V_In rhs);

Vec2V_Out MultiplyInt(Vec2V_In lhs, Vec2V_In rhs);
Vec3V_Out MultiplyInt(Vec3V_In lhs, Vec3V_In rhs);
Vec4V_Out MultiplyInt(Vec4V_In lhs, Vec4V_In rhs);

Vec2V_Out IntToFloat(Vec2V_In vVector);
Vec3V_Out IntToFloat(Vec3V_In vVector);
Vec4V_Out IntToFloat(Vec4V_In vVector);

Vec2V_Out FloatToInt(Vec2V_In vVector);
Vec3V_Out FloatToInt(Vec3V_In vVector);
Vec4V_Out FloatToInt(Vec4V_In vVector);

Vec2V_Out Floor(Vec2V_In vVector);
Vec3V_Out Floor(Vec3V_In vVector);
Vec4V_Out Floor(Vec4V_In vVector);

Vec2V_Out Ceil(Vec2V_In vVector);
Vec3V_Out Ceil(Vec3V_In vVector);
Vec4V_Out Ceil(Vec4V_In vVector);

Vec2V_Out Trunc(Vec2V_In vVector);
Vec3V_Out Trunc(Vec3V_In vVector);
Vec4V_Out Trunc(Vec4V_In vVector);

Vec2V_Out Round(Vec2V_In vVector);
Vec3V_Out Round(Vec3V_In vVector);
Vec4V_Out Round(Vec4V_In vVector);

Mat44V_Out Lerp(Mat44V_In MatrixA, Mat44V_In MatrixB, ScalarV_In vLambda);

Vec3V_Out CrossProduct(Vec3V_In lhs, Vec3V_In rhs);

Mat44V_Out MatrixInverse(Mat44V_In mMatrix);

Mat44V_Out Transpose(Mat44V_In mMatrix);

Mat44V_Out Transpose3x3(Mat44V_In mMatrix);

Mat44V_Out RotateAround(Vec3V_In origin, Mat44V_In rotatorsMatrix, Mat44V_In rotationMatrix);

Mat44V MakePerspectiveMatrixV(float fFOV, float fAspectRatio, float fNearClip, float fFarClip);

Mat44V MakeOrthographicMatrixV(float fWidth, float fHeight, float fNear, float fFar);

Mat44V MakeTextureMatrixOffsetV(unsigned int unWidth, unsigned int unHeight);
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

//#endif //GLOBALMATHFUNCS_INL

#include "GlobalMathFuncs.inl"

#endif // GLOBALMATHFUNCS_H