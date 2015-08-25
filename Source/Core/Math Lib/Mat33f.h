#ifndef MAT33F_H
#define MAT33F_H

#include "Vec3f.h"

class Mat33f;

typedef Mat33f& Mat33f_Ref;
typedef const Mat33f& Mat33f_ConstRef;

typedef Mat33f_ConstRef Mat33f_In;
typedef Mat33f_Ref Mat33f_InOut;

typedef Mat33f Mat33f_Out;

// Other Mat33f Aliases
typedef Mat33f float3x3;

class Mat33f
{
#define MAT33F_ACCESSOR(retType, name, retVal) \
	__forceinline retType name() { return retVal; }

#define MAT33F_ACCESSOR_CONST(retType, name, retVal) \
	__forceinline retType name() const { return retVal; }

#define MAT33F_MUTATOR(name, inType, modifiedVal) \
	__forceinline void RECON_VEC_CALLCONV name(inType rhs) { modifiedVal = rhs; }

private:
	union
	{
		f32 m[9];
		f32 ma[3][3];

		struct
		{
			f32 Xx, Xy, Xz,
				  Yx, Yy, Yz,
				  Zx, Zy, Zz;
		};

		struct
		{
			Vec3f xAxis, yAxis, zAxis;
		};
	};

public:
	Mat33f(){}
	explicit Mat33f(const f32& fXx, const f32& fXy, const f32& fXz,
					const f32& fYx, const f32& fYy, const f32& fYz,
					const f32& fZx, const f32& fZy, const f32& fZz);
	Mat33f(Mat33f_In rhs);
	Mat33f(Mat33f&& rhs);
	explicit Mat33f(Vec3f_In vXAxis,
					Vec3f_In vYAxis,
					Vec3f_In vZAxis);
	explicit Mat33f(eIdentityInitializer eIdentity);
	explicit Mat33f(eXRotationInitializer eXRotation, const f32& fRotationInRadians);
	explicit Mat33f(eYRotationInitializer eYRotation, const f32& fRotationInRadians);
	explicit Mat33f(eZRotationInitializer eZRotation, const f32& fRotationInRadians);

#if defined(MAT33F_ACCESSOR) && defined(MAT33F_ACCESSOR_CONST)
	MAT33F_ACCESSOR_CONST(Vec3f_Out, GetXAxis, xAxis)
	MAT33F_ACCESSOR_CONST(Vec3f_Out, GetYAxis, yAxis)
	MAT33F_ACCESSOR_CONST(Vec3f_Out, GetZAxis, zAxis)
	MAT33F_ACCESSOR_CONST(Vec3f_ConstRef, GetXAxisRef, xAxis)
	MAT33F_ACCESSOR_CONST(Vec3f_ConstRef, GetYAxisRef, yAxis)
	MAT33F_ACCESSOR_CONST(Vec3f_ConstRef, GetZAxisRef, zAxis)

	MAT33F_ACCESSOR(Vec3f_Ref, GetXAxisRef, xAxis)
	MAT33F_ACCESSOR(Vec3f_Ref, GetYAxisRef, yAxis)
	MAT33F_ACCESSOR(Vec3f_Ref, GetZAxisRef, zAxis)

#undef MAT33F_ACCESSOR
#undef MAT33F_ACCESSOR_CONST
#else
#error MAT33F ACCESSORS NOT DEFINED
#endif

#ifdef MAT33F_MUTATOR
	MAT33F_MUTATOR(SetXAxis, Vec3f_In, xAxis)
	MAT33F_MUTATOR(SetYAxis, Vec3f_In, yAxis)
	MAT33F_MUTATOR(SetZAxis, Vec3f_In, zAxis)
#undef MAT33F_MUTATOR
#else
#error MAT33F MUTATORS NOT DEFINED!
#endif

	Mat33f_Ref RECON_VEC_CALLCONV operator=(Mat33f_In mMatrix);
	Mat33f_Ref RECON_VEC_CALLCONV operator=(Mat33f&& mMatrix);

	Mat33f_Out RECON_VEC_CALLCONV operator*(Mat33f_In mMatrix) const;
	void RECON_VEC_CALLCONV operator*=(Mat33f_In mMatrix);
	friend Vec3f_Out RECON_VEC_CALLCONV operator*(Vec3f_ConstRef vVector, Mat33f_In mMatrix);
	friend Vec3f_Ref RECON_VEC_CALLCONV operator*=(Vec3f_Ref vVector, Mat33f_In mMatrix);

	Mat33f_Out RECON_VEC_CALLCONV operator+(Mat33f_In rhs) const;
	void RECON_VEC_CALLCONV operator+=(Mat33f_In rhs);

	Mat33f_Out RECON_VEC_CALLCONV operator-(Mat33f_In rhs) const;
	void RECON_VEC_CALLCONV operator-=(Mat33f_In rhs);

	void RECON_VEC_CALLCONV Rotate_LocalX(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_LocalY(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_LocalZ(const f32& fRadians);

	void RECON_VEC_CALLCONV Scale(Vec3f_In vScale);

	void RECON_VEC_CALLCONV SetScale(Vec3f_In vScale);
	Vec3f_Out GetScale() const;

	void Normalize();
};

#include "Mat33f.inl"

#endif // MAT33F_H