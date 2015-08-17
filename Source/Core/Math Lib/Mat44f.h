#ifndef MAT44F_H
#define MAT44F_H

#include "vec3f.h"

class Mat44f;

typedef Mat44f& Mat44f_Ref;
typedef const Mat44f& Mat44f_ConstRef;

typedef Mat44f_ConstRef Mat44f_In;
typedef Mat44f_Ref Mat44f_InOut;

typedef Mat44f Mat44f_Out;

// Other Mat44f Aliases
typedef Mat44f float4x4;

class Mat34f;

class Mat44f
{
#define Mat44_ACCESSOR(retType, name, retVal) \
	__forceinline retType name() { return retVal; }

#define Mat44_ACCESSOR_CONST(retType, name, retVal) \
	__forceinline retType name() const { return retVal; }

#define MAT44_MUTATOR(name, inType, modifiedVal) \
	__forceinline void RECON_VEC_CALLCONV name(inType rhs) { modifiedVal = rhs; }


private:
	union
	{
		f32 m[16];
		f32 ma[4][4];

		struct
		{
			Vec4f xAxis, yAxis, zAxis, wAxis;
		};
	};

public:
	Mat44f(){}
	explicit Mat44f(const f32& fXx, const f32& fXy, const f32& fXz, const f32& fXw,
					const f32& fYx, const f32& fYy, const f32& fYz, const f32& fYw,
					const f32& fZx, const f32& fZy, const f32& fZz, const f32& fZw,
					const f32& fWx, const f32& fWy, const f32& fWz, const f32& fWw);
	Mat44f(Mat44f_In mMatrix);
	Mat44f(Mat44f&& mMatrix);
	explicit Mat44f(Vec4f_In vXAxis,
					Vec4f_In vYAxis,
					Vec4f_In vZAxis,
					Vec4f_In vWAxis);

	explicit Mat44f(eIdentityInitializer eIdentity);
	explicit Mat44f(eXRotationInitializer eXRotation, const f32& fRotationInRadians);
	explicit Mat44f(eYRotationInitializer eYRotation, const f32& fRotationInRadians);
	explicit Mat44f(eZRotationInitializer eZRotation, const f32& fRotationInRadians);
	explicit Mat44f(eMatrixPositionInitializer eMatrixPos, Vec3f_In vPos);

#if defined(Mat44_ACCESSOR) && defined(Mat44_ACCESSOR_CONST)
	Mat44_ACCESSOR_CONST(Vec4f, GetXAxis, xAxis)
	Mat44_ACCESSOR_CONST(Vec4f, GetYAxis, yAxis)
	Mat44_ACCESSOR_CONST(Vec4f, GetZAxis, zAxis)
	Mat44_ACCESSOR_CONST(Vec4f, GetWAxis, wAxis)
	Mat44_ACCESSOR_CONST(Vec4f_ConstRef, GetXAxisRef, xAxis)
	Mat44_ACCESSOR_CONST(Vec4f_ConstRef, GetYAxisRef, yAxis)
	Mat44_ACCESSOR_CONST(Vec4f_ConstRef, GetZAxisRef, zAxis)
	Mat44_ACCESSOR_CONST(Vec4f_ConstRef, GetWAxisRef, wAxis)

	Mat44_ACCESSOR(Vec4f_Ref, GetXAxisRef, xAxis)
	Mat44_ACCESSOR(Vec4f_Ref, GetYAxisRef, yAxis)
	Mat44_ACCESSOR(Vec4f_Ref, GetZAxisRef, zAxis)
	Mat44_ACCESSOR(Vec4f_Ref, GetWAxisRef, wAxis)
#undef Mat44_ACCESSOR
#undef Mat44_ACCESSOR_CONST
#else
#error Mat44 ACCESSORS NOT DEFINED
#endif

#ifdef MAT44_MUTATOR
	MAT44_MUTATOR(SetXAxis, Vec4f_In, xAxis)
	MAT44_MUTATOR(SetYAxis, Vec4f_In, yAxis)
	MAT44_MUTATOR(SetZAxis, Vec4f_In, zAxis)
	MAT44_MUTATOR(SetWAxis, Vec4f_In, wAxis)
#undef MAT44_MUTATOR
#else
#error MAT44 MUTATORS NOT DEFINED!
#endif


	void MakeIdentity3x3();

	Mat44f_Ref RECON_VEC_CALLCONV operator=(Mat44f_In mMatrix);
	Mat44f_Ref RECON_VEC_CALLCONV operator=(Mat44f&& mMatrix);

	Mat44f_Out RECON_VEC_CALLCONV operator*(Mat44f_In mMatrix) const;
	void RECON_VEC_CALLCONV operator*=(Mat44f_In mMatrix);
	friend Vec4f_Out RECON_VEC_CALLCONV operator*(Vec4f_In vVector, Mat44f_In mMatrix);
	friend Vec4f_Ref RECON_VEC_CALLCONV operator*=(Vec4f_Ref vVector, Mat44f_In mMatrix);

	Mat44f_Out RECON_VEC_CALLCONV operator+(Mat44f_In rhs) const;
	void RECON_VEC_CALLCONV operator+=(Mat44f_In rhs);

	Mat44f_Out RECON_VEC_CALLCONV operator-(Mat44f_In rhs) const;
	void RECON_VEC_CALLCONV operator-=(Mat44f_In rhs);

	// actually faster than DirectX Version :)
	void RECON_VEC_CALLCONV Rotate_GlobalX(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_GlobalY(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_GlobalZ(const f32& fRadians);

	void RECON_VEC_CALLCONV Rotate_LocalX(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_LocalY(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_LocalZ(const f32& fRadians);

	void RECON_VEC_CALLCONV Scale(const Vec3f& vScale);

	void RECON_VEC_CALLCONV SetScale(const Vec3f& vScale);
	Vec3f_Out GetScale() const;

	void RECON_VEC_CALLCONV Translate(Vec3f vTranslation);

	void Transpose();
	void Transpose3x3();

	void Normalize();

	void RECON_VEC_CALLCONV LookAt(const Vec3f& mPos, const Vec3f& vWorldUp = g_IdentityY3);

	void RECON_VEC_CALLCONV TurnTo(Vec3f_In vPos, const f32& fDeltaTime, f32 fTurnModifier = 1.0f);

	void OrthoNormalInvert();
};

Mat34f RECON_VEC_CALLCONV Mat44ToMat34(Mat44f_In mMatrix);

#include "Mat44f.inl"

#endif // MAT44F_H