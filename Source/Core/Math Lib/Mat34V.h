#if SSE_AVAILABLE

#ifndef MAT34V_H
#define MAT34V_H

#include "Vec3V.h"
#include "Mat44V.h"

typedef Mat34V& Mat34V_Ref;
typedef const Mat34V& Mat34V_ConstRef;

typedef Mat34V_Ref Mat34V_InOut;
typedef Mat34V_ConstRef Mat34V_In;

typedef Mat34V Mat34V_Out;

// Other Mat34V Aliases
typedef Mat34V float3x4V;

class Mat44V;

ALIGN(16) class Mat34V
{
#define MAT34V_ACCESSOR(retType, name, retVal) \
	__forceinline retType name() { return retVal; }

#define MAT34V_ACCESSOR_CONST(retType, name, retVal) \
	__forceinline retType name() const { return retVal; }

#define MAT34V_MUTATOR(name, inType, modifiedVal) \
	__forceinline void RECON_VEC_CALLCONV name(inType rhs) { modifiedVal = rhs; }


private:
	union
	{
		f32 m[16];
		f32 ma[4][4];

		struct
		{
			Vector row1, row2, row3, row4;
		};

		struct
		{
			Vec3V xAxis;
			Vec3V yAxis;
			Vec3V zAxis;
			Vec3V wAxis;
		};
	};

public:
	Mat34V(){}
	explicit Mat34V(const f32& fXx, const f32& fXy, const f32& fXz,
					const f32& fYx, const f32& fYy, const f32& fYz,
					const f32& fZx, const f32& fZy, const f32& fZz,
					const f32& fWx, const f32& fWy, const f32& fWz);
	Mat34V(Mat34V_In mMatrix);
	Mat34V(Mat34V&& mMatrix);
	explicit Mat34V(Vec3V_In vXAxis,
					Vec3V_In vYAxis,
					Vec3V_In vZAxis,
					Vec3V_In vWAxis);

	explicit Mat34V(eIdentityInitializer eIdentity);
	explicit Mat34V(eXRotationInitializer eXRotation, const f32& fRotationInRadians);
	explicit Mat34V(eYRotationInitializer eXRotation, const f32& fRotationInRadians);
	explicit Mat34V(eZRotationInitializer eXRotation, const f32& fRotationInRadians);
	explicit Mat34V(eMatrixPositionInitializer eMatrixPos, Vec3V_In vPos);

#if defined(MAT34V_ACCESSOR) && defined(MAT34V_ACCESSOR_CONST)
	MAT34V_ACCESSOR_CONST(Vec3V, GetXAxis, xAxis)
	MAT34V_ACCESSOR_CONST(Vec3V, GetYAxis, yAxis)
	MAT34V_ACCESSOR_CONST(Vec3V, GetZAxis, zAxis)
	MAT34V_ACCESSOR_CONST(Vec3V, GetWAxis, wAxis)
	MAT34V_ACCESSOR_CONST(Vec3V_ConstRef, GetXAxisRef, xAxis)
	MAT34V_ACCESSOR_CONST(Vec3V_ConstRef, GetYAxisRef, yAxis)
	MAT34V_ACCESSOR_CONST(Vec3V_ConstRef, GetZAxisRef, zAxis)
	MAT34V_ACCESSOR_CONST(Vec3V_ConstRef, GetWAxisRef, wAxis)

	MAT34V_ACCESSOR(Vec3V_Ref, GetXAxisRef, xAxis)
	MAT34V_ACCESSOR(Vec3V_Ref, GetYAxisRef, yAxis)
	MAT34V_ACCESSOR(Vec3V_Ref, GetZAxisRef, zAxis)
	MAT34V_ACCESSOR(Vec3V_Ref, GetWAxisRef, wAxis)
#undef MAT34V_ACCESSOR
#undef MAT34V_ACCESSOR_CONST
#else
#error Mat34V ACCESSORS NOT DEFINED
#endif

#ifdef MAT34V_MUTATOR
	MAT34V_MUTATOR(SetXAxis, Vec3V_In, xAxis)
	MAT34V_MUTATOR(SetYAxis, Vec3V_In, yAxis)
	MAT34V_MUTATOR(SetZAxis, Vec3V_In, zAxis)
	MAT34V_MUTATOR(SetWAxis, Vec3V_In, wAxis)
#undef MAT34V_MUTATOR
#else
#error Mat34V MUTATORS NOT DEFINED!
#endif

	//explicit operator XMMATRIX() const;
	//explicit operator XMMATRIX*() const;

	Mat34V_ConstRef RECON_VEC_CALLCONV operator=(Mat34V_In mMatrix);
	Mat34V_ConstRef RECON_VEC_CALLCONV operator=(Mat34V&& mMatrix);

	friend Vec3V_Out RECON_VEC_CALLCONV operator*(Vec3V_ConstRef vPos, Mat34V_In mMatrix);
	friend Vec3V_Ref RECON_VEC_CALLCONV operator*=(Vec3V_Ref vPos, Mat34V_In mMatrix);
	friend Vec3V_Out RECON_VEC_CALLCONV operator*(Vec4V_ConstRef vPos, Mat34V_In mMatrix);

	Mat34V_Out RECON_VEC_CALLCONV operator+(Mat34V_In rhs) const;
	void RECON_VEC_CALLCONV operator+=(Mat34V_In rhs);

	Mat34V_Out RECON_VEC_CALLCONV operator-(Mat34V_In rhs) const;
	void RECON_VEC_CALLCONV operator-=(Mat34V_In rhs);

	void RECON_VEC_CALLCONV Rotate_GlobalX(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_GlobalY(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_GlobalZ(const f32& fRadians);

	void RECON_VEC_CALLCONV Rotate_LocalX(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_LocalY(const f32& fRadians);
	void RECON_VEC_CALLCONV Rotate_LocalZ(const f32& fRadians);

	void RECON_VEC_CALLCONV Scale(Vec3V_In vScale);

	void RECON_VEC_CALLCONV SetScale(Vec3V_In vScale);
	Vec3V_Out GetScale() const;

	void RECON_VEC_CALLCONV Translate(Vec3V_In vTranslation);

	void Transpose();
	void Transpose3x3();

	void Normalize();

	void RECON_VEC_CALLCONV LookAt(Vec3V_In mPos, Vec3V_In vWorldUp = g_IdentityY3V);

	void RECON_VEC_CALLCONV TurnTo(Vec3V_In vPos, const f32& fDeltaTime, f32 fTurnModifier = 1.0f);
};

Mat44V_Out RECON_VEC_CALLCONV Mat34ToMat44(Mat34V_In mMatrix);

#include "Mat34V.inl"

#endif // MAT34V_h

#endif // SSE_AVAILABLE