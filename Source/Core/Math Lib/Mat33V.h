#ifndef Mat33V_H
#define Mat33V_H

#include "Vec3V.h"

class Mat33V;

typedef Mat33V& Mat33V_Ref;
typedef const Mat33V& Mat33V_ConstRef;

typedef Mat33V_ConstRef Mat33V_In;
typedef Mat33V_Ref Mat33V_InOut;

typedef Mat33V Mat33V_Out;

// Other Mat33V Aliases
typedef Mat33V float3x3V;

class Mat33V
{
#define MAT33V_ACCESSOR(retType, name, retVal) \
	__forceinline retType name() { return retVal; }

#define MAT33V_ACCESSOR_CONST(retType, name, retVal) \
	__forceinline retType name() const { return retVal; }

#define MAT33V_MUTATOR(name, inType, modifiedVal) \
	__forceinline void RECON_VEC_CALLCONV name(inType rhs) { modifiedVal = rhs; }

private:
	union
	{
		f32 m[12];
		f32 ma[3][4];

		struct  
		{
			Vector row1, row2, row3;
		};

		struct
		{
			Vec3V xAxis, yAxis, zAxis;
		};
	};

public:
	Mat33V(){}
	explicit Mat33V(const f32& fXx, const f32& fXy, const f32& fXz,
					const f32& fYx, const f32& fYy, const f32& fYz,
					const f32& fZx, const f32& fZy, const f32& fZz);
	Mat33V(Mat33V_In rhs);
	Mat33V(Mat33V&& rhs);
	explicit Mat33V(Vec3V_In vXAxis,
					Vec3V_In vYAxis,
					Vec3V_In vZAxis);
	explicit Mat33V(eIdentityInitializer eIdentity);
	explicit Mat33V(eXRotationInitializer eXRotation, ScalarV_In vRotationInRadians);
	explicit Mat33V(eYRotationInitializer eYRotation, ScalarV_In vRotationInRadians);
	explicit Mat33V(eZRotationInitializer eZRotation, ScalarV_In vRotationInRadians);

#if defined(MAT33V_ACCESSOR) && defined(MAT33V_ACCESSOR_CONST)
	MAT33V_ACCESSOR_CONST(Vec3V_Out, GetXAxis, xAxis)
	MAT33V_ACCESSOR_CONST(Vec3V_Out, GetYAxis, yAxis)
	MAT33V_ACCESSOR_CONST(Vec3V_Out, GetZAxis, zAxis)
	MAT33V_ACCESSOR_CONST(Vec3V_ConstRef, GetXAxisRef, xAxis)
	MAT33V_ACCESSOR_CONST(Vec3V_ConstRef, GetYAxisRef, yAxis)
	MAT33V_ACCESSOR_CONST(Vec3V_ConstRef, GetZAxisRef, zAxis)

	MAT33V_ACCESSOR(Vec3V_Ref, GetXAxisRef, xAxis)
	MAT33V_ACCESSOR(Vec3V_Ref, GetYAxisRef, yAxis)
	MAT33V_ACCESSOR(Vec3V_Ref, GetZAxisRef, zAxis)

#undef MAT33V_ACCESSOR
#undef MAT33V_ACCESSOR_CONST
#else
#error MAT33V ACCESSORS NOT DEFINED
#endif

#ifdef MAT33V_MUTATOR
	MAT33V_MUTATOR(SetXAxis, Vec3V_In, xAxis)
	MAT33V_MUTATOR(SetYAxis, Vec3V_In, yAxis)
	MAT33V_MUTATOR(SetZAxis, Vec3V_In, zAxis)
#undef MAT33V_MUTATOR
#else
#error MAT33V MUTATORS NOT DEFINED!
#endif

	Mat33V_Ref RECON_VEC_CALLCONV operator=(Mat33V_In mMatrix);
	Mat33V_Ref RECON_VEC_CALLCONV operator=(Mat33V&& mMatrix);

	Mat33V_Out RECON_VEC_CALLCONV operator*(Mat33V_In mMatrix) const;
	void RECON_VEC_CALLCONV operator*=(Mat33V_In mMatrix);
	friend Vec3V_Out RECON_VEC_CALLCONV operator*(Vec3V_ConstRef vVector, Mat33V_In mMatrix);
	friend Vec3V_Ref RECON_VEC_CALLCONV operator*=(Vec3V_Ref vVector, Mat33V_In mMatrix);

	Mat33V_Out RECON_VEC_CALLCONV operator+(Mat33V_In rhs) const;
	void RECON_VEC_CALLCONV operator+=(Mat33V_In rhs);

	Mat33V_Out RECON_VEC_CALLCONV operator-(Mat33V_In rhs) const;
	void RECON_VEC_CALLCONV operator-=(Mat33V_In rhs);

	void RECON_VEC_CALLCONV RotateLocalX(ScalarV_In vRadians);
	void RECON_VEC_CALLCONV RotateLocalY(ScalarV_In vRadians);
	void RECON_VEC_CALLCONV RotateLocalZ(ScalarV_In vRadians);

	void RECON_VEC_CALLCONV Scale(Vec3V_In vScale);

	void RECON_VEC_CALLCONV SetScale(Vec3V_In vScale);
	Vec3V_Out GetScale() const;
};

#include "Mat33V.inl"

#endif // Mat33V_H