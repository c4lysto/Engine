#if SSE_AVAILABLE

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

class Mat34V;

ALIGN(16) class Mat44V
{
#define Mat44V_ACCESSOR(retType, name, retVal) \
	__forceinline retType name() { return retVal; }

#define Mat44V_ACCESSOR_CONST(retType, name, retVal) \
	__forceinline retType name() const { return retVal; }

#define Mat44V_MUTATOR(name, inType, modifiedVal) \
	__forceinline void name(inType rhs) { modifiedVal = rhs; }


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
			Vec4V xAxis;
			Vec4V yAxis;
			Vec4V zAxis;
			Vec4V wAxis;
		};
	};

public:
	Mat44V(){}
	explicit Mat44V(const f32& fXx, const f32& fXy, const f32& fXz, const f32& fXw,
					const f32& fYx, const f32& fYy, const f32& fYz, const f32& fYw,
					const f32& fZx, const f32& fZy, const f32& fZz, const f32& fZw,
					const f32& fWx, const f32& fWy, const f32& fWz, const f32& fWw);
	Mat44V(Mat44V_In mMatrix);
	Mat44V(Mat44V&& mMatrix);
	explicit Mat44V(Vec4V_In vXAxis,
					Vec4V_In vYAxis,
					Vec4V_In vZAxis,
					Vec4V_In vWAxis);

	explicit Mat44V(eIdentityInitializer eIdentity);
	explicit Mat44V(eXRotationInitializer eXRotation, const f32& fRotationInRadians);
	explicit Mat44V(eYRotationInitializer eXRotation, const f32& fRotationInRadians);
	explicit Mat44V(eZRotationInitializer eXRotation, const f32& fRotationInRadians);
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

	Mat44V_ConstRef operator=(Mat44V_In mMatrix);
	Mat44V_ConstRef operator=(Mat44V&& mMatrix);

	Mat44V_Out operator*(Mat44V_In mMatrix) const;
	void operator*=(Mat44V_In mMatrix);

	Mat44V_Out operator+(Mat44V_In rhs) const;
	void operator+=(Mat44V_In rhs);

	Mat44V_Out operator-(Mat44V_In rhs) const;
	void operator-=(Mat44V_In rhs);

	void Rotate_GlobalX(const f32& fRadians);
	void Rotate_GlobalY(const f32& fRadians);
	void Rotate_GlobalZ(const f32& fRadians);

	void Rotate_LocalX(const f32& fRadians);
	void Rotate_LocalY(const f32& fRadians);
	void Rotate_LocalZ(const f32& fRadians);

	void Scale(Vec3V_In vScale);

	void SetScale(Vec3V_In vScale);
	Vec3V_Out GetScale() const;

	void Translate(Vec3V_In vTranslation);

	void Transpose();
	void Transpose3x3();

	void Normalize();

	void LookAt(Vec3V_In mPos, Vec3V_In vWorldUp = g_IdentityY3V);

	void TurnTo(Vec3V_In vPos, const f32& fDeltaTime, f32 fTurnModifier = 1.0f);

	void OrthoNormalInvert();
};

Mat34V RECON_VEC_CALLCONV Mat44ToMat34(Mat44V_In mMatrix);

#include "Mat44V.inl"

#endif // MAT44V_h

#endif // SSE_AVAILABLE