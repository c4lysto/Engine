#if RECON_SSE_VERSION

#ifndef MAT43V_H
#define MAT43V_H

#include "Vec3V.h"
#include "Mat33V.h"
#include "Mat44V.h"

typedef Mat43V& Mat43V_Ref;
typedef const Mat43V& Mat43V_ConstRef;

typedef Mat43V_Ref Mat43V_InOut;
typedef Mat43V_ConstRef Mat43V_In;

typedef Mat43V Mat43V_Out;

// Other Mat43V Aliases
typedef Mat43V float4x3V;

class Mat44V;

ALIGN(16) class Mat43V
{
#define MAT43V_ACCESSOR(retType, name, retVal) \
	__forceinline retType name() { return retVal; }

#define MAT43V_ACCESSOR_CONST(retType, name, retVal) \
	__forceinline retType name() const { return retVal; }

#define MAT43V_MUTATOR(name, inType, modifiedVal) \
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
			Vec3V xAxis;
			Vec3V yAxis;
			Vec3V zAxis;
			Vec3V wAxis;
		};

		struct
		{
			Mat33V mat33;
		};
	};

public:
	Mat43V(){}
	explicit Mat43V(ScalarV_In vXx, ScalarV_In vXy, ScalarV_In vXz,
					ScalarV_In vYx, ScalarV_In vYy, ScalarV_In vYz,
					ScalarV_In vZx, ScalarV_In vZy, ScalarV_In vZz,
					ScalarV_In vWx, ScalarV_In vWy, ScalarV_In vWz);
	Mat43V(Mat43V_In mMatrix);
	Mat43V(Mat43V&& mMatrix);
	explicit Mat43V(Vec3V_In vXAxis,
					Vec3V_In vYAxis,
					Vec3V_In vZAxis,
					Vec3V_In vWAxis);

	explicit Mat43V(eIdentityInitializer eIdentity);
	explicit Mat43V(eXRotationInitializer eXRotation, ScalarV_In vRotationInRadians);
	explicit Mat43V(eYRotationInitializer eXRotation, ScalarV_In vRotationInRadians);
	explicit Mat43V(eZRotationInitializer eXRotation, ScalarV_In vRotationInRadians);
	explicit Mat43V(eMatrixPositionInitializer eMatrixPos, Vec3V_In vPos);

#if defined(MAT43V_ACCESSOR) && defined(MAT43V_ACCESSOR_CONST)
	MAT43V_ACCESSOR_CONST(Vec3V, GetXAxis, xAxis)
	MAT43V_ACCESSOR_CONST(Vec3V, GetYAxis, yAxis)
	MAT43V_ACCESSOR_CONST(Vec3V, GetZAxis, zAxis)
	MAT43V_ACCESSOR_CONST(Vec3V, GetWAxis, wAxis)
	MAT43V_ACCESSOR_CONST(Mat33V, GetMat33, mat33)
	MAT43V_ACCESSOR_CONST(Vec3V_ConstRef, GetXAxisRef, xAxis)
	MAT43V_ACCESSOR_CONST(Vec3V_ConstRef, GetYAxisRef, yAxis)
	MAT43V_ACCESSOR_CONST(Vec3V_ConstRef, GetZAxisRef, zAxis)
	MAT43V_ACCESSOR_CONST(Vec3V_ConstRef, GetWAxisRef, wAxis)
	MAT43V_ACCESSOR_CONST(Mat33V_ConstRef, GetMat33Ref, mat33)

	MAT43V_ACCESSOR(Vec3V_Ref, GetXAxisRef, xAxis)
	MAT43V_ACCESSOR(Vec3V_Ref, GetYAxisRef, yAxis)
	MAT43V_ACCESSOR(Vec3V_Ref, GetZAxisRef, zAxis)
	MAT43V_ACCESSOR(Vec3V_Ref, GetWAxisRef, wAxis)
	MAT43V_ACCESSOR(Mat33V_Ref, GetMat33Ref, mat33)
#undef MAT43V_ACCESSOR
#undef MAT43V_ACCESSOR_CONST
#else
#error Mat43V ACCESSORS NOT DEFINED
#endif

#ifdef MAT43V_MUTATOR
	MAT43V_MUTATOR(SetXAxis, Vec3V_In, xAxis)
	MAT43V_MUTATOR(SetYAxis, Vec3V_In, yAxis)
	MAT43V_MUTATOR(SetZAxis, Vec3V_In, zAxis)
	MAT43V_MUTATOR(SetWAxis, Vec3V_In, wAxis)
	MAT43V_MUTATOR(SetMat33, Mat33V_In, mat33)
#undef MAT43V_MUTATOR
#else
#error Mat43V MUTATORS NOT DEFINED!
#endif

	//explicit operator XMMATRIX() const;
	//explicit operator XMMATRIX*() const;

	Mat43V_ConstRef RECON_VEC_CALLCONV operator=(Mat43V_In mMatrix);
	Mat43V_ConstRef RECON_VEC_CALLCONV operator=(Mat43V&& mMatrix);

	friend Vec3V_Out RECON_VEC_CALLCONV operator*(Vec3V_ConstRef vPos, Mat43V_In mMatrix);
	friend Vec3V_Ref RECON_VEC_CALLCONV operator*=(Vec3V_Ref vPos, Mat43V_In mMatrix);
	friend Vec3V_Out RECON_VEC_CALLCONV operator*(Vec4V_ConstRef vPos, Mat43V_In mMatrix);

	Mat43V_Out RECON_VEC_CALLCONV operator+(Mat43V_In rhs) const;
	void RECON_VEC_CALLCONV operator+=(Mat43V_In rhs);

	Mat43V_Out RECON_VEC_CALLCONV operator-(Mat43V_In rhs) const;
	void RECON_VEC_CALLCONV operator-=(Mat43V_In rhs);

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

Mat44V_Out RECON_VEC_CALLCONV Mat43ToMat44(Mat43V_In mMatrix);

#include "Mat43V.inl"

#endif // MAT43V_H

#endif // RECON_SSE_VERSION