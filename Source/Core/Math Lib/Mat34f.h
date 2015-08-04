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
	FORCEINLINE retType name() { return retVal; }

#define MAT34F_ACCESSOR_CONST(retType, name, retVal) \
	FORCEINLINE retType name() const { return retVal; }

#define MAT34F_MUTATOR(name, inType, modifiedVal) \
	FORCEINLINE void name(inType rhs) { modifiedVal = rhs; }


private:
	union
	{
		float m[12];
		float ma[4][3];

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
	explicit Mat34f(const float& fXx, const float& fXy, const float& fXz,
					const float& fYx, const float& fYy, const float& fYz,
					const float& fZx, const float& fZy, const float& fZz,
					const float& fWx, const float& fWy, const float& fWz);
	Mat34f(Mat34f_In mMatrix);
	Mat34f(Mat34f&& mMatrix);
	explicit Mat34f(Vec3f_In vXAxis,
					Vec3f_In vYAxis,
					Vec3f_In vZAxis,
					Vec3f_In vWAxis);

	explicit Mat34f(eIdentityInitializer eIdentity);
	explicit Mat34f(eXRotationInitializer eXRotation, const float& fRotationInRadians);
	explicit Mat34f(eYRotationInitializer eYRotation, const float& fRotationInRadians);
	explicit Mat34f(eZRotationInitializer eZRotation, const float& fRotationInRadians);
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

	Mat34f_Ref operator=(Mat34f_In mMatrix);
	Mat34f_Ref operator=(Mat34f&& mMatrix);

	friend Vec3f_Out operator*(Vec3f_ConstRef vPos, Mat34f_In mMatrix);
	friend Vec3f_Ref operator*=(Vec3f_Ref vPos, Mat34f_In mMatrix);
	friend Vec3f_Out operator*(Vec4f_In vVector, Mat34f_In mMatrix);

	Mat34f_Out operator+(Mat34f_In rhs) const;
	void operator+=(Mat34f_In rhs);

	Mat34f_Out operator-(Mat34f_In rhs) const;
	void operator-=(Mat34f_In rhs);

	void Rotate_GlobalX(const float& fRadians);
	void Rotate_GlobalY(const float& fRadians);
	void Rotate_GlobalZ(const float& fRadians);

	void Rotate_LocalX(const float& fRadians);
	void Rotate_LocalY(const float& fRadians);
	void Rotate_LocalZ(const float& fRadians);

	void Scale(Vec3f_In vScale);

	void SetScale(Vec3f_In vScale);
	Vec3f_Out GetScale() const;

	void Translate(Vec3f vTranslation);

	void Transpose3x3();

	void Normalize();

	void LookAt(Vec3f_In mPos, Vec3f_In vWorldUp = g_IdentityY3);

	void TurnTo(Vec3f_In vPos, const float& fDeltaTime, float fTurnModifier = 1.0f);
};

Mat44f_Out Mat34ToMat44(Mat34f_In mMatrix);

#include "Mat34f.inl"

#endif // MAT34F_H