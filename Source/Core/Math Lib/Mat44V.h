#if RECON_SSE_VERSION

#ifndef MAT44V_H
#define MAT44V_H

#include "Vec3V.h"
#include "Vec4V.h"

typedef Mat44V& Mat44V_Ref;
typedef const Mat44V& Mat44V_ConstRef;

typedef Mat44V_Ref Mat44V_InOut;
typedef Mat44V_ConstRef Mat44V_In;

typedef Mat44V Mat44V_Out;

// Other Mat44V Aliases
typedef Mat44V float4x4V;

class Mat43V;

ALIGN(16) class Mat44V
{
#define Mat44V_ACCESSOR(retType, name, retVal) \
	__forceinline retType name() { return retVal; }

#define Mat44V_ACCESSOR_CONST(retType, name, retVal) \
	__forceinline retType name() const { return retVal; }

#define Mat44V_MUTATOR(name, inType, modifiedVal) \
	__forceinline void RECON_VEC_CALLCONV name(inType rhs) { modifiedVal = rhs; }


private:
	union
	{
		f32 m[16];
		f32 ma[4][4];

		struct
		{
			Vector128 row1, row2, row3, row4;
		};

		struct
		{
			Vec4V xAxis;
			Vec4V yAxis;
			Vec4V zAxis;
			Vec4V wAxis;
		};
	};

public:
	Mat44V(){}
	explicit Mat44V(ScalarV_In vXx, ScalarV_In vXy, ScalarV_In vXz, ScalarV_In vXw,
					ScalarV_In vYx, ScalarV_In vYy, ScalarV_In vYz, ScalarV_In vYw,
					ScalarV_In vZx, ScalarV_In vZy, ScalarV_In vZz, ScalarV_In vZw,
					ScalarV_In vWx, ScalarV_In vWy, ScalarV_In vWz, ScalarV_In vWw);
	Mat44V(Mat44V_In mMatrix);
	Mat44V(Mat44V&& mMatrix);
	explicit Mat44V(Vec4V_In vXAxis,
					Vec4V_In vYAxis,
					Vec4V_In vZAxis,
					Vec4V_In vWAxis);

	explicit Mat44V(eIdentityInitializer eIdentity);
	explicit Mat44V(eXRotationInitializer eXRotation, ScalarV_In vRotationInRadians);
	explicit Mat44V(eYRotationInitializer eXRotation, ScalarV_In vRotationInRadians);
	explicit Mat44V(eZRotationInitializer eXRotation, ScalarV_In vRotationInRadians);
	explicit Mat44V(eMatrixPositionInitializer eMatrixPos, Vec3V_In vPos);

#if defined(Mat44V_ACCESSOR) && defined(Mat44V_ACCESSOR_CONST)
	Mat44V_ACCESSOR_CONST(Vec4V, GetXAxis, xAxis)
	Mat44V_ACCESSOR_CONST(Vec4V, GetYAxis, yAxis)
	Mat44V_ACCESSOR_CONST(Vec4V, GetZAxis, zAxis)
	Mat44V_ACCESSOR_CONST(Vec4V, GetWAxis, wAxis)
	Mat44V_ACCESSOR_CONST(Vec4V_ConstRef, GetXAxisRef, xAxis)
	Mat44V_ACCESSOR_CONST(Vec4V_ConstRef, GetYAxisRef, yAxis)
	Mat44V_ACCESSOR_CONST(Vec4V_ConstRef, GetZAxisRef, zAxis)
	Mat44V_ACCESSOR_CONST(Vec4V_ConstRef, GetWAxisRef, wAxis)

	Mat44V_ACCESSOR(Vec4V_Ref, GetXAxisRef, xAxis)
	Mat44V_ACCESSOR(Vec4V_Ref, GetYAxisRef, yAxis)
	Mat44V_ACCESSOR(Vec4V_Ref, GetZAxisRef, zAxis)
	Mat44V_ACCESSOR(Vec4V_Ref, GetWAxisRef, wAxis)
#undef Mat44V_ACCESSOR
#undef Mat44V_ACCESSOR_CONST
#else
#error Mat44V ACCESSORS NOT DEFINED
#endif

#ifdef Mat44V_MUTATOR
	Mat44V_MUTATOR(SetXAxis, Vec4V_In, xAxis)
	Mat44V_MUTATOR(SetYAxis, Vec4V_In, yAxis)
	Mat44V_MUTATOR(SetZAxis, Vec4V_In, zAxis)
	Mat44V_MUTATOR(SetWAxis, Vec4V_In, wAxis)
#undef Mat44V_MUTATOR
#else
#error Mat44V MUTATORS NOT DEFINED!
#endif

	//explicit operator XMMATRIX() const;
	//explicit operator XMMATRIX*() const;

	Mat44V_ConstRef RECON_VEC_CALLCONV operator=(Mat44V_In mMatrix);
	Mat44V_ConstRef RECON_VEC_CALLCONV operator=(Mat44V&& mMatrix);

	Mat44V_Out RECON_VEC_CALLCONV operator*(Mat44V_In mMatrix) const;
	void RECON_VEC_CALLCONV operator*=(Mat44V_In mMatrix);

	Mat44V_Out RECON_VEC_CALLCONV operator+(Mat44V_In rhs) const;
	void RECON_VEC_CALLCONV operator+=(Mat44V_In rhs);

	Mat44V_Out RECON_VEC_CALLCONV operator-(Mat44V_In rhs) const;
	void RECON_VEC_CALLCONV operator-=(Mat44V_In rhs);

	void RECON_VEC_CALLCONV RotateGlobalX(ScalarV_In vRadians);
	void RECON_VEC_CALLCONV RotateGlobalY(ScalarV_In vRadians);
	void RECON_VEC_CALLCONV RotateGlobalZ(ScalarV_In vRadians);

	void RECON_VEC_CALLCONV RotateLocalX(ScalarV_In vRadians);
	void RECON_VEC_CALLCONV RotateLocalY(ScalarV_In vRadians);
	void RECON_VEC_CALLCONV RotateLocalZ(ScalarV_In vRadians);

	void RECON_VEC_CALLCONV Scale(Vec3V_In vScale);

	void RECON_VEC_CALLCONV SetScale(Vec3V_In vScale);
	Vec3V_Out GetScale() const;

	void RECON_VEC_CALLCONV Translate(Vec3V_In vTranslation);
};

Mat43V RECON_VEC_CALLCONV Mat44ToMat43(Mat44V_In mMatrix);
Mat44V_Out RECON_VEC_CALLCONV Transpose3x3(Mat44V_In mMatrix);
Vec2V_Out RECON_VEC_CALLCONV SinCos(ScalarV_In vRadians);

#include "Mat44V.inl"

#endif // MAT44V_h

#endif // RECON_SSE_VERSION