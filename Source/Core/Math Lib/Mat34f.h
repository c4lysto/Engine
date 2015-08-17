#ifndef MAT34F_H
#define MAT34F_H

#include "Mat33f.h"
#include "Mat44f.h"
#include "Vec3f.h"

class Mat34f;

typedef Mat34f& Mat34f_Ref;
typedef const Mat34f& Mat34f_ConstRef;

typedef Mat34f_ConstRef Mat34f_In;
typedef Mat34f_Ref Mat34f_InOut;

typedef Mat34f Mat34f_Out;

// Other Mat34f Aliases
typedef Mat34f float3x4;

class Mat34f
{
#define MAT34F_ACCESSOR(retType, name, retVal) \
	__forceinline retType name() { return retVal; }

#define MAT34F_ACCESSOR_CONST(retType, name, retVal) \
	__forceinline retType name() const { return retVal; }

#define MAT34F_MUTATOR(name, inType, modifiedVal) \
	__forceinline void RECON_VEC_CALLCONV name(inType rhs) { modifiedVal = rhs; }


private:
	union
	{
		f32 m[12];
		f32 ma[4][3];

		struct
		{
			Mat33f orientation;
		};

		struct
		{
			Vec3f xAxis, yAxis, zAxis, wAxis;
		};
	};

public:
	Mat34f(){}
	explicit Mat34f(const f32& fXx, const f32& fXy, const f32& fXz,
					const f32& fYx, const f32& fYy, const f32& fYz,
					const f32& fZx, const f32& fZy, const f32& fZz,
					const f32& fWx, const f32& fWy, const f32& fWz);
	Mat34f(Mat34f_In mMatrix);
	Mat34f(Mat34f&& mMatrix);
	explicit Mat34f(Vec3f_In vXAxis,
					Vec3f_In vYAxis,
					Vec3f_In vZAxis,
					Vec3f_In vWAxis);

	explicit Mat34f(eIdentityInitializer eIdentity);
	explicit Mat34f(eXRotationInitializer eXRotation, const f32& fRotationInRadians);
	explicit Mat34f(eYRotationInitializer eYRotation, const f32& fRotationInRadians);
	explicit Mat34f(eZRotationInitializer eZRotation, const f32& fRotationInRadians);
	explicit Mat34f(eMatrixPositionInitializer eMatrixPos, Vec3f_In vPos);

#if defined(MAT34F_ACCESSOR) && defined(MAT34F_ACCESSOR_CONST)
	MAT34F_ACCESSOR_CONST(Vec3f, GetXAxis, xAxis)
	MAT34F_ACCESSOR_CONST(Vec3f, GetYAxis, yAxis)
	MAT34F_ACCESSOR_CONST(Vec3f, GetZAxis, zAxis)
	MAT34F_ACCESSOR_CONST(Vec3f, GetWAxis, wAxis)
	MAT34F_ACCESSOR_CONST(Vec3f_ConstRef, GetXAxisRef, xAxis)
	MAT34F_ACCESSOR_CONST(Vec3f_ConstRef, GetYAxisRef, yAxis)
	MAT34F_ACCESSOR_CONST(Vec3f_ConstRef, GetZAxisRef, zAxis)
	MAT34F_ACCESSOR_CONST(Vec3f_ConstRef, GetWAxisRef, wAxis)

	MAT34F_ACCESSOR(Vec3f_Ref, GetXAxisRef, xAxis)
	MAT34F_ACCESSOR(Vec3f_Ref, GetYAxisRef, yAxis)
	MAT34F_ACCESSOR(Vec3f_Ref, GetZAxisRef, zAxis)
	MAT34F_ACCESSOR(Vec3f_Ref, GetWAxisRef, wAxis)
#undef MAT34F_ACCESSOR
#undef MAT34F_ACCESSOR_CONST
#else
#error MAT34F ACCESSORS NOT DEFINED
#endif

#ifdef MAT34F_MUTATOR
	MAT34F_MUTATOR(SetXAxis, Vec3f_In, xAxis)
	MAT34F_MUTATOR(SetYAxis, Vec3f_In, yAxis)
	MAT34F_MUTATOR(SetZAxis, Vec3f_In, zAxis)
	MAT34F_MUTATOR(SetWAxis, Vec3f_In, wAxis)
#undef MAT34F_MUTATOR
#else
#error MAT34F MUTATORS NOT DEFINED!
#endif


	void MakeIdentity3x3();

	Mat34f_Ref RECON_VEC_CALLCONV operator=(Mat34f_In mMatrix);
	Mat34f_Ref RECON_VEC_CALLCONV operator=(Mat34f&& mMatrix);

	friend Vec3f_Out RECON_VEC_CALLCONV operator*(Vec3f_ConstRef vPos, Mat34f_In mMatrix);
	friend Vec3f_Ref RECON_VEC_CALLCONV operator*=(Vec3f_Ref vPos, Mat34f_In mMatrix);
	friend Vec3f_Out RECON_VEC_CALLCONV operator*(Vec4f_In vVector, Mat34f_In mMatrix);

	Mat34f_Out RECON_VEC_CALLCONV operator+(Mat34f_In rhs) const;
	void RECON_VEC_CALLCONV operator+=(Mat34f_In rhs);

	Mat34f_Out RECON_VEC_CALLCONV operator-(Mat34f_In rhs) const;
	void RECON_VEC_CALLCONV operator-=(Mat34f_In rhs);

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

	void Transpose3x3();

	void Normalize();

	void RECON_VEC_CALLCONV LookAt(Vec3f_In mPos, Vec3f_In vWorldUp = g_IdentityY3);

	void RECON_VEC_CALLCONV TurnTo(Vec3f_In vPos, const f32& fDeltaTime, f32 fTurnModifier = 1.0f);
};

Mat44f_Out RECON_VEC_CALLCONV Mat34ToMat44(Mat34f_In mMatrix);

#include "Mat34f.inl"

#endif // MAT34F_H