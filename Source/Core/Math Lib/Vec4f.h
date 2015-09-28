#ifndef VEC4F_H
#define VEC4F_H

#include "MathDeclarations.h"
#include "Vec3f.h"

class Vec4f;

typedef Vec4f& Vec4f_Ref;
typedef const Vec4f& Vec4f_ConstRef;

typedef Vec4f_ConstRef Vec4f_In;
typedef Vec4f_Ref Vec4f_InOut;

typedef Vec4f Vec4f_Out;

// Other Vec4f Aliases
typedef Vec4f float4;

class Vec4f
{
#if SSE_AVAILABLE && 0
#define DEFINE_VEC4_ENUM_CONSTRUCTOR(enumeration, valueToInit)\
	explicit __forceinline Vec4f(enumeration)\
	{\
		VectorStoreU(VectorSet(valueToInit), vector); \
	}
#else
#define DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(enumeration, xVal, yVal, zVal, wVal)\
	explicit __forceinline Vec4f(enumeration) : iX((s32)xVal), iY((s32)yVal), iZ((s32)zVal), iW((s32)wVal){}

#define DEFINE_VEC4_ENUM_CONSTRUCTOR(enumeration, valueToInit) DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(enumeration, valueToInit, valueToInit, valueToInit, valueToInit)
#endif //SSE_AVAILABLE

#define VEC4_ACCESSOR(retType, funcName, retVal) \
	__forceinline retType funcName() { return retVal; }

#define VEC4_ACCESSOR_CONST(retType, funcName, retVal) \
	__forceinline retType funcName() const { return retVal; }

#define VEC4_MUTATOR(funcName, inType, modifiedVal) \
	__forceinline void funcName(inType rhs) { modifiedVal = rhs; }

#define VEC4_MUTATOR_MOVE(funcName, inType, modifiedVal) \
	__forceinline void funcName(inType&& rhs) { modifiedVal = std::move(rhs); }

private:
	union
	{
		f32 vector[4];

		union
		{
			struct
			{
				s32 iX, iY, iZ, iW;
			};
			struct
			{
				f32 x, y, z, w;
			};
			struct
			{
				Vec3f position; f32 padW;
			};
		};
	};

public:
	Vec4f(){}
	Vec4f(Vec4f_In vVector);
	Vec4f(Vec4f&& vVector);
	explicit Vec4f(const f32& fVal);
	explicit Vec4f(const f32& fX, const f32& fY, const f32& fZ, const f32& fW);
	explicit Vec4f(Vec2f_In vXY, Vec2f_In vZW);
	explicit Vec4f(const f32& fX, const f32& fY, Vec2f_In vZW);
	explicit Vec4f(Vec2f_In vXY, const f32& fZ, const f32& fW);
	explicit Vec4f(const f32& fX, Vec3f_In vYZW);
	explicit Vec4f(Vec3f_In vVector, const f32& fA);

#if SSE_AVAILABLE
	explicit Vec4f(Vector_In vVector);
#if !RECON_OS_64BIT
	explicit Vec4f(Vector&& vVector);
#endif // !RECON_OS_64BIT
#endif //SSE_AVAILABLE

#if defined(VEC4_ACCESSOR) && defined(VEC4_ACCESSOR_CONST)
	VEC4_ACCESSOR_CONST(f32, GetX, x)
	VEC4_ACCESSOR_CONST(f32, GetY, y)
	VEC4_ACCESSOR_CONST(f32, GetZ, z)
	VEC4_ACCESSOR_CONST(f32, GetW, w)
	VEC4_ACCESSOR_CONST(Vec3f_Out, GetXYZ, position)

	VEC4_ACCESSOR_CONST(s32, GetXi, iX)
	VEC4_ACCESSOR_CONST(s32, GetYi, iY)
	VEC4_ACCESSOR_CONST(s32, GetZi, iZ)
	VEC4_ACCESSOR_CONST(s32, GetWi, iW)

	VEC4_ACCESSOR_CONST(const f32&, GetXRef, x)
	VEC4_ACCESSOR_CONST(const f32&, GetYRef, y)
	VEC4_ACCESSOR_CONST(const f32&, GetZRef, z)
	VEC4_ACCESSOR_CONST(const f32&, GetWRef, w)
	VEC4_ACCESSOR_CONST(const f32*, GetVector, vector);

	VEC4_ACCESSOR_CONST(const s32&, GetXiRef, iX)
	VEC4_ACCESSOR_CONST(const s32&, GetYiRef, iY)
	VEC4_ACCESSOR_CONST(const s32&, GetZiRef, iZ)
	VEC4_ACCESSOR_CONST(const s32&, GetWiRef, iW)


	VEC4_ACCESSOR(f32&, GetXRef, x)
	VEC4_ACCESSOR(f32&, GetYRef, y)
	VEC4_ACCESSOR(f32&, GetZRef, z)
	VEC4_ACCESSOR(f32&, GetWRef, w)
	VEC4_ACCESSOR(f32*, GetVector, vector)

	VEC4_ACCESSOR(s32&, GetXiRef, iX)
	VEC4_ACCESSOR(s32&, GetYiRef, iY)
	VEC4_ACCESSOR(s32&, GetZiRef, iZ)
	VEC4_ACCESSOR(s32&, GetWiRef, iW)
#undef VEC4_ACCESSOR
#undef VEC4_ACCESSOR_CONST
#else
#error VEC4 ACCESSORS NOT DEFINED
#endif

#if defined(VEC4_MUTATOR) && defined(VEC4_MUTATOR_MOVE)
	VEC4_MUTATOR(SetX, const f32&, x)
	VEC4_MUTATOR(SetY, const f32&, y)
	VEC4_MUTATOR(SetZ, const f32&, z)
	VEC4_MUTATOR(SetW, const f32&, w)
	VEC4_MUTATOR(SetXYZ, Vec3f_In, position)
	VEC4_MUTATOR_MOVE(SetXYZ, Vec3f, position)

	VEC4_MUTATOR(SetXi, const s32&, iX)
	VEC4_MUTATOR(SetYi, const s32&, iY)
	VEC4_MUTATOR(SetZi, const s32&, iZ)
	VEC4_MUTATOR(SetWi, const s32&, iW)
#undef VEC4_MUTATOR
#undef VEC4_MUTATOR_MOVE
#else
#error VEC4 MUTATORS NOT DEFINED
#endif

#ifdef DEFINE_VEC4_ENUM_CONSTRUCTOR
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eZeroInitializer,			FloatToIntRep::Zero)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eOneInitializer,			FloatToIntRep::One)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eTwoInitializer,			FloatToIntRep::Two)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eThreeInitializer,			FloatToIntRep::Three)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eFourInitializer,			FloatToIntRep::Four)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eFiveInitializer,			FloatToIntRep::Five)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eSixInitializer,			FloatToIntRep::Six)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eSevenInitializer,			FloatToIntRep::Seven)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eEightInitializer,			FloatToIntRep::Eight)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNineInitializer,			FloatToIntRep::Nine)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eTenInitializer,			FloatToIntRep::Ten)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eQuarterInitializer,		FloatToIntRep::Quarter)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eHalfInitializer,			FloatToIntRep::Half)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(ePIInitializer,			FloatToIntRep::Pi)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eHalfPIInitializer,		FloatToIntRep::Half_Pi)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eTwoPIInitializer,			FloatToIntRep::Two_Pi)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eFLTMINInitializer,		FloatToIntRep::Flt_Min)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eFLTMAXInitializer,		FloatToIntRep::Flt_Max)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eFLTEpsilonInitializer,	FloatToIntRep::Flt_Epsilon)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNANInitializer,			FloatToIntRep::NaN)

	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegOneInitializer,		FloatToIntRep::Neg_One)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegTwoInitializer,		FloatToIntRep::Neg_Two)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegThreeInitializer,		FloatToIntRep::Neg_Three)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegFourInitializer,		FloatToIntRep::Neg_Four)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegFiveInitializer,		FloatToIntRep::Neg_Five)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegSixInitializer,		FloatToIntRep::Neg_Six)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegSevenInitializer,		FloatToIntRep::Neg_Seven)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegEightInitializer,		FloatToIntRep::Neg_Eight)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegNineInitializer,		FloatToIntRep::Neg_Nine)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegTenInitializer,		FloatToIntRep::Neg_Ten)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegQuarterInitializer,	FloatToIntRep::Neg_Quarter)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegHalfInitializer,		FloatToIntRep::Neg_Half)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegPIInitializer,			FloatToIntRep::Neg_Pi)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegHalfPIInitializer,		FloatToIntRep::Neg_Half_Pi)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegTwoPIInitializer,		FloatToIntRep::Neg_Two_Pi)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegFLTMINInitializer,		FloatToIntRep::Neg_Flt_Min)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer,		FloatToIntRep::Neg_Flt_Max)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegFLTEpsilonInitializer,	FloatToIntRep::Neg_Flt_Epsilon)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eNegNANInitializer,		FloatToIntRep::Neg_NaN)

	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eXAxisInitializer, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::Zero)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eYAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eZAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eWAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::One)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eUpAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero)

	DEFINE_VEC4_ENUM_CONSTRUCTOR(eTrueInitializer, FloatToIntRep::True)
	DEFINE_VEC4_ENUM_CONSTRUCTOR(eFalseInitializer, FloatToIntRep::False)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eTTTFInitializer, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::False)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eTTFTInitializer, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::True)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eTTFFInitializer, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::False)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eTFTTInitializer, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::True)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eTFTFInitializer, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::False)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eTFFTInitializer, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::True)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eTFFFInitializer, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::False)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eFTTTInitializer, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::True)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eFTTFInitializer, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::False)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eFTFTInitializer, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::True)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eFTFFInitializer, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::False)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eFFTTInitializer, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::True)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eFFTFInitializer, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::False)
	DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR(eFFFTInitializer, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::True)

#undef DEFINE_VEC4_ENUM_CONSTRUCTOR
#undef DEFINE_VEC4_ENUM_VAL_CONSTRUCTOR
#endif //DEFINE_VEC4_ENUM_CONSTRUCTOR

	Vec3f_Out RECON_VEC_CALLCONV GetXYZ() { return position; }

	Vec4f_Out operator-();

	Vec4f_Ref RECON_VEC_CALLCONV operator=(Vec4f_In vVector);
	Vec4f_Ref RECON_VEC_CALLCONV operator=(Vec4f&& vVector);

	Vec4f_Out RECON_VEC_CALLCONV operator-(Vec4f_In vVector) const;
	void RECON_VEC_CALLCONV operator-=(Vec4f_In vVector);

	Vec4f_Out RECON_VEC_CALLCONV operator+(Vec4f_In vVector) const;
	void RECON_VEC_CALLCONV operator+=(Vec4f_In vVector);

	Vec4f_Out RECON_VEC_CALLCONV operator/(const f32& fScalar) const;
	void RECON_VEC_CALLCONV operator/=(const f32& fScalar);
	Vec4f_Out RECON_VEC_CALLCONV operator/(Vec4f_In vVector) const;
	void RECON_VEC_CALLCONV operator/=(Vec4f_In vVector);

	Vec4f_Out RECON_VEC_CALLCONV operator*(const f32& fScalar) const;
	void RECON_VEC_CALLCONV operator*=(const f32& fScalar);
	friend Vec4f_Out RECON_VEC_CALLCONV operator*(const f32& fScalar, Vec4f_In vVector);
	Vec4f_Out RECON_VEC_CALLCONV operator*(Vec4f_In vVector) const;
	void RECON_VEC_CALLCONV operator*=(Vec4f_In vVector);

	bool RECON_VEC_CALLCONV operator==(Vec4f_In vVector);
	bool RECON_VEC_CALLCONV operator!=(Vec4f_In vVector);

	Vec4f_Out RECON_VEC_CALLCONV operator&(Vec4f_In vVector) const;
	void RECON_VEC_CALLCONV operator&=(Vec4f_In vVector);

	Vec4f_Out RECON_VEC_CALLCONV operator|(Vec4f_In vVector) const;
	void RECON_VEC_CALLCONV operator|=(Vec4f_In vVector);

	Vec4f_Out RECON_VEC_CALLCONV operator^(Vec4f_In vVector) const;
	void RECON_VEC_CALLCONV operator^=(Vec4f_In vVector);

	Vec4f_Out operator~() const;

	const f32& operator[](s32 index) const;
	f32& operator[](s32 index);
};

Vec4f_Out RECON_VEC_CALLCONV Vec4fInt(const s32& intVal);
Vec4f_Out RECON_VEC_CALLCONV Vec4fInt(const s32& intX, const s32& intY, const s32& intZ, const s32& intW);


GLOBALCONST Vec4f g_IdentityX4 = Vec4f(I_X_AXIS);
GLOBALCONST Vec4f g_IdentityY4 = Vec4f(I_Y_AXIS);
GLOBALCONST Vec4f g_IdentityZ4 = Vec4f(I_Z_AXIS);
GLOBALCONST Vec4f g_IdentityW4 = Vec4f(I_W_AXIS);
GLOBALCONST Vec4f g_WorldUp4   = Vec4f(I_UP_AXIS);

f32 RECON_VEC_CALLCONV Dot(Vec4f_In lhs, Vec4f_In rhs);

f32 RECON_VEC_CALLCONV Mag(Vec4f_In vVector);
f32 RECON_VEC_CALLCONV Length(Vec4f_In vVector);
f32 RECON_VEC_CALLCONV MagSq(Vec4f_In vVector);
f32 RECON_VEC_CALLCONV LengthSq(Vec4f_In vVector);

Vec4f_Out RECON_VEC_CALLCONV Normalize(Vec4f_In vVector);
Vec4f_Out RECON_VEC_CALLCONV Cross(Vec4f_In vVectorA, Vec4f_In vVectorB);

#include "Vec4f.inl"

#endif // VEC4F_H