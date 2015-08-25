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
	explicit __forceinline Vec3f(enumeration) : iX((s32)xVal), iY((s32)yVal), iZ((s32)zVal) {}

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
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eZeroInitializer,			FloatToIntRep::Zero)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eOneInitializer,			FloatToIntRep::One)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eTwoInitializer,			FloatToIntRep::Two)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eThreeInitializer,			FloatToIntRep::Three)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eFourInitializer,			FloatToIntRep::Four)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eFiveInitializer,			FloatToIntRep::Five)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eSixInitializer,			FloatToIntRep::Six)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eSevenInitializer,			FloatToIntRep::Seven)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eEightInitializer,			FloatToIntRep::Eight)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNineInitializer,			FloatToIntRep::Nine)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eTenInitializer,			FloatToIntRep::Ten)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eQuarterInitializer,		FloatToIntRep::Quarter)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eHalfInitializer,			FloatToIntRep::Half)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(ePIInitializer,			FloatToIntRep::Pi)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eHalfPIInitializer,		FloatToIntRep::Half_Pi)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eTwoPIInitializer,			FloatToIntRep::Two_Pi)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eFLTMINInitializer,		FloatToIntRep::Flt_Min)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eFLTMAXInitializer,		FloatToIntRep::Flt_Max)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eFLTEpsilonInitializer,	FloatToIntRep::Flt_Epsilon)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNANInitializer,			FloatToIntRep::NaN)

	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegOneInitializer,		FloatToIntRep::Neg_One)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegTwoInitializer,		FloatToIntRep::Neg_Two)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegThreeInitializer,		FloatToIntRep::Neg_Three)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegFourInitializer,		FloatToIntRep::Neg_Four)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegFiveInitializer,		FloatToIntRep::Neg_Five)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegSixInitializer,		FloatToIntRep::Neg_Six)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegSevenInitializer,		FloatToIntRep::Neg_Seven)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegEightInitializer,		FloatToIntRep::Neg_Eight)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegNineInitializer,		FloatToIntRep::Neg_Nine)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegTenInitializer,		FloatToIntRep::Neg_Ten)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegQuarterInitializer,	FloatToIntRep::Neg_Quarter)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegHalfInitializer,		FloatToIntRep::Neg_Half)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegPIInitializer,			FloatToIntRep::Neg_Pi)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegHalfPIInitializer,		FloatToIntRep::Neg_Half_Pi)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegTwoPIInitializer,		FloatToIntRep::Neg_Two_Pi)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegFLTMINInitializer,		FloatToIntRep::Neg_Flt_Min)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer,		FloatToIntRep::Neg_Flt_Max)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegFLTEpsilonInitializer,	FloatToIntRep::Neg_Flt_Epsilon)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eNegNANInitializer,		FloatToIntRep::Neg_NaN)

	DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(eXAxisInitializer, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero)
	DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(eYAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero)
	DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(eZAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::One)
	DEFINE_VEC3_ENUM_CONSTRUCTOR(eWAxisInitializer, FloatToIntRep::Zero)
	DEFINE_VEC3_ENUM_VAL_CONSTRUCTOR(eUpAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero)
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

#include "Vec3f.inl"

#endif // VEC3F_H