#ifndef VEC3F_H
#define VEC3F_H

#include "MathDeclarations.h"

class Vec3f;

typedef Vec3f& Vec3f_Ref;
typedef const Vec3f& Vec3f_ConstRef;

typedef Vec3f_ConstRef Vec3f_In;
typedef Vec3f_Ref Vec3f_InOut;

typedef Vec3f Vec3f_Out;

// Other Vec3f Aliases
typedef Vec3f float3;

class Vec3f
{
#define DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(enumeration, xVal, yVal, zVal) \
	explicit __forceinline Vec3f(enumeration) : x(xVal), y(yVal), z(zVal) {}

#define DEFINE_VEC3_ENUM_CONSTRUCTOR(enumeration, valueToInit) DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(enumeration, valueToInit, valueToInit, valueToInit)

#define VEC3_ACCESSOR(retType, funcName, retVal) \
	__forceinline retType funcName() { return retVal; }

#define VEC3_ACCESSOR_CONST(retType, funcName, retVal) \
	__forceinline retType funcName() const { return retVal; }

#define VEC3_MUTATOR(funcName, inType, modifiedVal) \
	__forceinline void funcName(inType rhs) { modifiedVal = rhs; }


private:
	union
	{
		f32 vector[3];

		struct
		{
			f32 x, y, z;
		};

		struct
		{
			s32 iX, iY, iZ;
		};
	};

public:
	Vec3f(){}
	explicit Vec3f(const f32& fVal);
	explicit Vec3f(const f32& fX, const f32& fY, const f32& fZ);
	explicit Vec3f(const f32& fX, Vec2f_In vYZ);
	explicit Vec3f(Vec2f_In vXY, const f32& fZ);
	Vec3f(Vec3f_In vVector);
	Vec3f(Vec3f&& vVector);

#if SSE_AVAILABLE
	explicit Vec3f(Vector_In vVector);

#if !RECON_OS_64BIT
	explicit Vec3f(Vector&& vVector);
#endif
#endif

#ifdef DEFINE_VEC3_ENUM_CONSTRUCTOR
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eZeroInitializer, 0.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eOneInitializer, 1.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eTwoInitializer, 2.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eThreeInitializer, 3.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eFourInitializer, 4.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eFiveInitializer, 5.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eSixInitializer, 6.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eSevenInitializer, 7.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eEightInitializer, 8.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNineInitializer, 9.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eTenInitializer, 10.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eQuarterInitializer, 0.25f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eHalfInitializer, 0.5f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(ePIInitializer, PI)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eHalfPIInitializer, PI_OVER_2)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eTwoPIInitializer, TWO_PI)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eFLTMINInitializer, FLT_MIN)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eFLTMAXInitializer, FLT_MAX)

	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegOneInitializer, -1.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegTwoInitializer, -2.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegThreeInitializer, -3.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegFourInitializer, -4.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegFiveInitializer, -5.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegSixInitializer, -6.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegSevenInitializer, -7.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegEightInitializer, -8.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegNineInitializer, -9.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegTenInitializer, -10.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegQuarterInitializer, -0.25f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegHalfInitializer, -0.5f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegPIInitializer, -PI)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegHalfPIInitializer, -PI_OVER_2)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegTwoPIInitializer, -TWO_PI)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegFLTMINInitializer, -FLT_MIN)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer, -FLT_MAX)

	DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(eXAxisInitializer, 1.0f, 0.0f, 0.0f)
	DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(eYAxisInitializer, 0.0f, 1.0f, 0.0f)
	DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(eZAxisInitializer, 0.0f, 0.0f, 1.0f)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eWAxisInitializer, 0.0f)
	DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(eUpAxisInitializer, 0.0f, 1.0f, 0.0f)
#undef DEFINE_VEC3_ENUM_CONSTRUCTOR
#undef DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR
#endif //DEFINE_VEC3_ENUM_CONSTRUCTOR

#if defined(VEC3_ACCESSOR) && defined(VEC3_ACCESSOR_CONST)
	VEC3_ACCESSOR_CONST(f32, GetX, x)
	VEC3_ACCESSOR_CONST(f32, GetY, y)
	VEC3_ACCESSOR_CONST(f32, GetZ, z)
	VEC3_ACCESSOR_CONST(const f32&, GetXRef, x)
	VEC3_ACCESSOR_CONST(const f32&, GetYRef, y)
	VEC3_ACCESSOR_CONST(const f32&, GetZRef, z)
	VEC3_ACCESSOR_CONST(const f32*, GetVector, vector)

	VEC3_ACCESSOR_CONST(s32, GetXi, iX)
	VEC3_ACCESSOR_CONST(s32, GetYi, iY)
	VEC3_ACCESSOR_CONST(s32, GetZi, iZ)
	VEC3_ACCESSOR_CONST(const s32&, GetXiRef, iX)
	VEC3_ACCESSOR_CONST(const s32&, GetYiRef, iY)
	VEC3_ACCESSOR_CONST(const s32&, GetZiRef, iZ)

	VEC3_ACCESSOR(f32&, GetXRef, x)
	VEC3_ACCESSOR(f32&, GetYRef, y)
	VEC3_ACCESSOR(f32&, GetZRef, z)
	VEC3_ACCESSOR(f32*, GetVector, vector)

	VEC3_ACCESSOR(s32&, GetXiRef, iX)
	VEC3_ACCESSOR(s32&, GetYiRef, iY)
	VEC3_ACCESSOR(s32&, GetZiRef, iZ)
#undef VEC3_ACCESSOR
#undef VEC3_ACCESSOR_CONST
#else
#error VEC3 ACCESSORS NOT DEFINED
#endif

#if defined(VEC3_MUTATOR)
	VEC3_MUTATOR(SetX, const f32&, x)
	VEC3_MUTATOR(SetY, const f32&, y)
	VEC3_MUTATOR(SetZ, const f32&, z)

	VEC3_MUTATOR(SetXi, const s32&, iX)
	VEC3_MUTATOR(SetYi, const s32&, iY)
	VEC3_MUTATOR(SetZi, const s32&, iZ)
#undef VEC3_MUTATOR
#else
#error VEC3 MUTATORS NOT DEFINED
#endif

	Vec3f_Out operator-() const;

	Vec3f_Ref RECON_VEC_CALLCONV operator=(Vec3f_In vVector);
	Vec3f_Ref RECON_VEC_CALLCONV operator=(Vec3f&& vVector);

	void RECON_VEC_CALLCONV operator*=(const f32& fScalar);
	void RECON_VEC_CALLCONV operator*=(Vec3f_In vScale);

	Vec3f_Out RECON_VEC_CALLCONV operator/(const f32& fScalar) const;
	Vec3f_Out RECON_VEC_CALLCONV operator/(Vec3f_In vScale) const;

	void RECON_VEC_CALLCONV operator/=(const f32& fScalar);
	void RECON_VEC_CALLCONV operator/=(Vec3f_In vScale);

	Vec3f_Out RECON_VEC_CALLCONV operator*(const f32& fScalar) const;
	friend Vec3f_Out RECON_VEC_CALLCONV operator*(const f32& fScalar, Vec3f_In vVector);
	Vec3f_Out RECON_VEC_CALLCONV operator*(Vec3f_In vScale) const;

	void RECON_VEC_CALLCONV operator+=(Vec3f_In vVector);
	Vec3f_Out RECON_VEC_CALLCONV operator+(Vec3f_In vVector) const;

	void RECON_VEC_CALLCONV operator-=(Vec3f_In vVector);
	Vec3f_Out RECON_VEC_CALLCONV operator-(Vec3f_In vVector) const;

	bool RECON_VEC_CALLCONV operator==(Vec3f_In vVector) const;

	bool RECON_VEC_CALLCONV operator!=(Vec3f_In vVector) const;

	Vec3f_Out RECON_VEC_CALLCONV operator&(Vec3f_In vVector) const;
	void RECON_VEC_CALLCONV operator&=(Vec3f_In vVector);

	Vec3f_Out RECON_VEC_CALLCONV operator|(Vec3f_In vVector) const;
	void RECON_VEC_CALLCONV operator|=(Vec3f_In vVector);

	Vec3f_Out RECON_VEC_CALLCONV operator^(Vec3f_In vVector) const;
	void RECON_VEC_CALLCONV operator^=(Vec3f_In vVector);

	Vec3f_Out operator~() const;

	const f32& operator[](s32 index) const;
	f32& operator[](s32 index);
};

Vec3f_Out RECON_VEC_CALLCONV Vec3fInt(const s32& intVal);
Vec3f_Out RECON_VEC_CALLCONV Vec3fInt(const s32& intX, const s32& intY, const s32& intZ);

f32 RECON_VEC_CALLCONV Dot(Vec3f_In lhs, Vec3f_In rhs);

f32 RECON_VEC_CALLCONV Mag(Vec3f_In vVector);
f32 RECON_VEC_CALLCONV Length(Vec3f_In vVector);
f32 RECON_VEC_CALLCONV MagSq(Vec3f_In vVector);
f32 RECON_VEC_CALLCONV LengthSq(Vec3f_In vVector);

Vec3f_Out RECON_VEC_CALLCONV Normalize(Vec3f_In vVector);
Vec3f_Out RECON_VEC_CALLCONV Cross(Vec3f_In vVectorA, Vec3f_In vVectorB);

GLOBALCONST Vec3f g_IdentityX3 = Vec3f(I_X_AXIS);
GLOBALCONST Vec3f g_IdentityY3 = Vec3f(I_Y_AXIS);
GLOBALCONST Vec3f g_IdentityZ3 = Vec3f(I_Z_AXIS);
GLOBALCONST Vec3f g_IdentityW3 = Vec3f(I_W_AXIS);
GLOBALCONST Vec3f g_WorldUp	   = Vec3f(I_UP_AXIS);

#include "Vec3f.inl"

#endif // VEC3F_H