#ifndef MAT43F_H
#define MAT43F_H

#include "Mat33f.h"
#include "Mat44f.h"
#include "Vec3f.h"

class Mat43f;

typedef Mat43f& Mat43f_Ref;
typedef const Mat43f& Mat43f_ConstRef;

typedef Mat43f_ConstRef Mat43f_In;
typedef Mat43f_Ref Mat43f_InOut;

typedef Mat43f Mat43f_Out;

// Other Mat43f Aliases
typedef Mat43f float4x3;

class Mat43f
{
#define MAT43F_ACCESSOR(retType, name, retVal) \
	__forceinline retType name() { return retVal; }

#define MAT43F_ACCESSOR_CONST(retType, name, retVal) \
	__forceinline retType name() const { return retVal; }

#define MAT43F_MUTATOR(name, inType, modifiedVal) \
	__forceinline void RECON_VEC_CALLCONV name(inType rhs) { modifiedVal = rhs; }


private:
	union
	{
		f32 m[12];
		f32 ma[4][3];

		struct
		{
			Mat33f mat33;
		};

		struct
		{
			Vec3f xAxis, yAxis, zAxis, wAxis;
		};
	};

public:
	Mat43f(){}
	explicit Mat43f(const f32& fXx, const f32& fXy, const f32& fXz,
					const f32& fYx, const f32& fYy, const f32& fYz,
					const f32& fZx, const f32& fZy, const f32& fZz,
					const f32& fWx, const f32& fWy, const f32& fWz);
	Mat43f(Mat43f_In mMatrix);
	Mat43f(Mat43f&& mMatrix);
	explicit Mat43f(Vec3f_In vXAxis,
					Vec3f_In vYAxis,
					Vec3f_In vZAxis,
					Vec3f_In vWAxis);

	explicit Mat43f(eIdentityInitializer eIdentity);
	explicit Mat43f(eXRotationInitializer eXRotation, const f32& fRotationInRadians);
	explicit Mat43f(eYRotationInitializer eYRotation, const f32& fRotationInRadians);
	explicit Mat43f(eZRotationInitializer eZRotation, const f32& fRotationInRadians);
	explicit Mat43f(eMatrixPositionInitializer eMatrixPos, Vec3f_In vPos);

#if defined(MAT43F_ACCESSOR) && defined(MAT43F_ACCESSOR_CONST)
	MAT43F_ACCESSOR_CONST(Vec3f, GetXAxis, xAxis)
	MAT43F_ACCESSOR_CONST(Vec3f, GetYAxis, yAxis)
	MAT43F_ACCESSOR_CONST(Vec3f, GetZAxis, zAxis)
	MAT43F_ACCESSOR_CONST(Vec3f, GetWAxis, wAxis)
	MAT43F_ACCESSOR_CONST(Mat33f, GetMat33, mat33)
	MAT43F_ACCESSOR_CONST(Vec3f_ConstRef, GetXAxisRef, xAxis)
	MAT43F_ACCESSOR_CONST(Vec3f_ConstRef, GetYAxisRef, yAxis)
	MAT43F_ACCESSOR_CONST(Vec3f_ConstRef, GetZAxisRef, zAxis)
	MAT43F_ACCESSOR_CONST(Vec3f_ConstRef, GetWAxisRef, wAxis)
	MAT43F_ACCESSOR_CONST(Mat33f_ConstRef, GetMat33Ref, mat33)

	MAT43F_ACCESSOR(Vec3f_Ref, GetXAxisRef, xAxis)
	MAT43F_ACCESSOR(Vec3f_Ref, GetYAxisRef, yAxis)
	MAT43F_ACCESSOR(Vec3f_Ref, GetZAxisRef, zAxis)
	MAT43F_ACCESSOR(Vec3f_Ref, GetWAxisRef, wAxis)
	MAT43F_ACCESSOR(Mat33f_Ref, GetMat33Ref, mat33)
#undef MAT43F_ACCESSOR
#undef MAT43F_ACCESSOR_CONST
#else
#error MAT43F ACCESSORS NOT DEFINED
#endif

#ifdef MAT43F_MUTATOR
	MAT43F_MUTATOR(SetXAxis, Vec3f_In, xAxis)
	MAT43F_MUTATOR(SetYAxis, Vec3f_In, yAxis)
	MAT43F_MUTATOR(SetZAxis, Vec3f_In, zAxis)
	MAT43F_MUTATOR(SetWAxis, Vec3f_In, wAxis)
	MAT43F_MUTATOR(SetMat33, Mat33f_In, mat33)
#undef MAT43F_MUTATOR
#else
#error MAT43F MUTATORS NOT DEFINED!
#endif


	void MakeIdentity3x3();

	Mat43f_Ref RECON_VEC_CALLCONV operator=(Mat43f_In mMatrix);
	Mat43f_Ref RECON_VEC_CALLCONV operator=(Mat43f&& mMatrix);

	friend Vec3f_Out RECON_VEC_CALLCONV operator*(Vec3f_ConstRef vPos, Mat43f_In mMatrix);
	friend Vec3f_Ref RECON_VEC_CALLCONV operator*=(Vec3f_Ref vPos, Mat43f_In mMatrix);
	friend Vec3f_Out RECON_VEC_CALLCONV operator*(Vec4f_In vVector, Mat43f_In mMatrix);

	Mat43f_Out RECON_VEC_CALLCONV operator+(Mat43f_In rhs) const;
	void RECON_VEC_CALLCONV operator+=(Mat43f_In rhs);

	Mat43f_Out RECON_VEC_CALLCONV operator-(Mat43f_In rhs) const;
	void RECON_VEC_CALLCONV operator-=(Mat43f_In rhs);

	void RECON_VEC_CALLCONV Rotate_GlobalX(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_GlobalY(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_GlobalZ(const f32& fRadians);

	void RECON_VEC_CALLCONV Rotate_LocalX(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_LocalY(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_LocalZ(const f32& fRadians);

	void RECON_VEC_CALLCONV Scale(Vec3f_In vScale);

	void RECON_VEC_CALLCONV SetScale(Vec3f_In vScale);
	Vec3f_Out GetScale() const;

	void RECON_VEC_CALLCONV Translate(Vec3f vTranslation);

	void Normalize();
};

Mat44f_Out RECON_VEC_CALLCONV Mat43ToMat44(Mat43f_In mMatrix);

#include "Mat43f.inl"

#endif // MAT43F_H