#ifndef VEC3V_H
#define VEC3V_H

#include "MathDeclarations.h"

#if SSE_AVAILABLE

#include "ScalarV.h"

typedef Vec3V& Vec3V_Ref;
typedef const Vec3V& Vec3V_ConstRef;

#if RECON_OS_64BIT
typedef Vec3V Vec3V_In;
#else
typedef Vec3V_ConstRef Vec3V_In;
#endif

typedef Vec3V Vec3V_Out;

typedef Vec3V_Ref Vec3V_InOut;

// Other Vec3V Aliases
typedef Vec3V float3V;

ALIGN(16) class Vec3V
{
#define DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(enumeration, xIntRep, yIntRep, zIntRep) \
	explicit __forceinline Vec3V(enumeration) : row(VectorSetConstant<(u32)xIntRep, (u32)yIntRep, (u32)zIntRep, (u32)FloatToIntRep::Zero>()) { }

#define DEFINE_VEC3V_ENUM_CONSTRUCTOR(enumeration, intRep) DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(enumeration, intRep, intRep, intRep)

#define VEC3V_ACCESSOR(retType, funcName, retVal) \
	__forceinline retType funcName() { return retVal; }

#define VEC3V_ACCESSOR_SCALARV_CONST(element) \
	__forceinline ScalarV_Out RECON_VEC_CALLCONV Get##element() const \
	{ return ScalarV(VectorPermute<VecElem::##element , VecElem::##element , VecElem::##element , VecElem::##element >(row)); }

#define VEC3V_ACCESSOR_CONST(retType, funcName, retVal) \
	__forceinline retType funcName() const { return retVal; }

#define VEC3V_MUTATOR(funcName, inType, modifiedVal) \
	__forceinline void funcName(inType rhs) { modifiedVal = rhs; }

	friend class Vec4V;

private:
	union
	{
		f32 floatArr[4];
		Vector row;

		union
		{
			struct
			{
				f32 x, y, z, w;
			};
		};
	};

public:
	Vec3V(){}
	explicit Vec3V(const f32& fVal);
	explicit Vec3V(const f32& fX, const f32& fY, const f32& fZ);
	explicit Vec3V(ScalarV_In vVal);
	explicit Vec3V(ScalarV_In vX, ScalarV_In vY, ScalarV_In vZ);
	explicit Vec3V(Vec2V_In vXY, ScalarV_In fZ);
	explicit Vec3V(ScalarV_In fX, Vec2V_In vYZ);
	//Vec3V(Vec3V_In vVector);
#if !RECON_OS_64BIT
	Vec3V(Vec3V&& vVector);
#endif // !RECON_OS_64BIT
	explicit Vec3V(Vector_In vVector);
#if !RECON_OS_64BIT
	Vec3V(Vector&& vVector);
#endif // !RECON_OS_64BIT

#ifdef DEFINE_VEC3V_ENUM_CONSTRUCTOR
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eZeroInitializer,			FloatToIntRep::Zero)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eOneInitializer,			FloatToIntRep::One)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eTwoInitializer,			FloatToIntRep::Two)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eThreeInitializer,		FloatToIntRep::Three)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFourInitializer,			FloatToIntRep::Four)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFiveInitializer,			FloatToIntRep::Five)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eSixInitializer,			FloatToIntRep::Six)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eSevenInitializer,		FloatToIntRep::Seven)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eEightInitializer,		FloatToIntRep::Eight)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNineInitializer,			FloatToIntRep::Nine)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eTenInitializer, 			FloatToIntRep::Ten)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eQuarterInitializer,		FloatToIntRep::Quarter)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eHalfInitializer,			FloatToIntRep::Half)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(ePIInitializer, 			FloatToIntRep::Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eHalfPIInitializer,		FloatToIntRep::Half_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eTwoPIInitializer,		FloatToIntRep::Two_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFLTMINInitializer,		FloatToIntRep::Flt_Min)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFLTMAXInitializer,		FloatToIntRep::Flt_Max)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFLTEpsilonInitializer,	FloatToIntRep::Flt_Epsilon)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNANInitializer,			FloatToIntRep::NaN)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eSignBitInitializer,		FloatToIntRep::Sign_Bit)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eAbsMaskInitializer,		FloatToIntRep::Abs_Mask)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTOneInitializer,		1)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTTwoInitializer,		2)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTThreeInitializer,		3)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTFourInitializer,		4)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTFiveInitializer,		5)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTSixInitializer,		6)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTSevenInitializer,		7)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTEightInitializer,		8)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNineInitializer,		9)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTTenInitializer,		10)

	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegOneInitializer,			FloatToIntRep::Neg_One)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegTwoInitializer,			FloatToIntRep::Neg_Two)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegThreeInitializer,			FloatToIntRep::Neg_Three)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegFourInitializer,			FloatToIntRep::Neg_Four)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegFiveInitializer,			FloatToIntRep::Neg_Five)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegSixInitializer, 			FloatToIntRep::Neg_Six)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegSevenInitializer,			FloatToIntRep::Neg_Seven)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegEightInitializer,			FloatToIntRep::Neg_Eight)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegNineInitializer,			FloatToIntRep::Neg_Nine)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegTenInitializer, 			FloatToIntRep::Neg_Ten)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegQuarterInitializer,		FloatToIntRep::Neg_Quarter)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegHalfInitializer,			FloatToIntRep::Neg_Half)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegPIInitializer,			FloatToIntRep::Neg_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegHalfPIInitializer, 		FloatToIntRep::Neg_Half_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegTwoPIInitializer, 		FloatToIntRep::Neg_Two_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegFLTMINInitializer,		FloatToIntRep::Neg_Flt_Min)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer,		FloatToIntRep::Neg_Flt_Max)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegFLTEpsilonInitializer,	FloatToIntRep::Neg_Flt_Epsilon)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegNANInitializer,			FloatToIntRep::Neg_NaN)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegOneInitializer,		-1)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegTwoInitializer,		-2)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegThreeInitializer,		-3)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegFourInitializer,		-4)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegFiveInitializer,		-5)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegSixInitializer,		-6)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegSevenInitializer,		-7)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegEightInitializer,		-8)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegNineInitializer,		-9)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eINTNegTenInitializer,		-10)

	DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(eXAxisInitializer,		FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero)
	DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(eYAxisInitializer,		FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero)
	DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(eZAxisInitializer,		FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::One)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eWAxisInitializer,			FloatToIntRep::Zero)
	DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(eUpAxisInitializer,		FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero)

	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eTrueInitializer,				FloatToIntRep::True)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFalseInitializer,			FloatToIntRep::False)
#undef DEFINE_VEC3V_ENUM_CONSTRUCTOR
#undef DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR
#endif //DEFINE_VEC3_ENUM_CONSTRUCTOR

#if defined(VEC3V_ACCESSOR) && defined(VEC3V_ACCESSOR_CONST) && defined(VEC3V_ACCESSOR_SCALARV_CONST)
	VEC3V_ACCESSOR_SCALARV_CONST(X)
	VEC3V_ACCESSOR_SCALARV_CONST(Y)
	VEC3V_ACCESSOR_SCALARV_CONST(Z)
	VEC3V_ACCESSOR_SCALARV_CONST(W)
	VEC3V_ACCESSOR_CONST(const f32&, GetXRef, x)
	VEC3V_ACCESSOR_CONST(const f32&, GetYRef, y)
	VEC3V_ACCESSOR_CONST(const f32&, GetZRef, z)
	VEC3V_ACCESSOR_CONST(const f32&, GetWRef, w)

	// Returns the Vector Intrinsic Data Type
	VEC3V_ACCESSOR_CONST(Vector_Out, RECON_VEC_CALLCONV GetVector, row)

	VEC3V_ACCESSOR(f32&, GetXRef, x)
	VEC3V_ACCESSOR(f32&, GetYRef, y)
	VEC3V_ACCESSOR(f32&, GetZRef, z)
	VEC3V_ACCESSOR(f32&, GetWRef, w)
#undef VEC3V_ACCESSOR
#undef VEC3V_ACCESSOR_CONST
#undef VEC3V_ACCESSOR_SCALARV_CONST
#else
#error VEC3V ACCESSORS NOT DEFINED
#endif

#if defined(VEC3V_MUTATOR)
	void RECON_VEC_CALLCONV SetX(ScalarV_In vX);
	void RECON_VEC_CALLCONV SetY(ScalarV_In vY);
	void RECON_VEC_CALLCONV SetZ(ScalarV_In vZ);
	void RECON_VEC_CALLCONV SetW(ScalarV_In vW);

	VEC3V_MUTATOR(SetX, const f32&, x)
	VEC3V_MUTATOR(SetY, const f32&, y)
	VEC3V_MUTATOR(SetZ, const f32&, z)
	VEC3V_MUTATOR(SetW, const f32&, w)
#undef VEC3V_MUTATOR
#else
#error VEC3V MUTATORS NOT DEFINED
#endif

	Vec3V_Out operator-() const;

	Vec3V_Out RECON_VEC_CALLCONV operator=(Vec3V_In vVector);
#if !RECON_OS_64BIT
	Vec3V_Out RECON_VEC_CALLCONV operator=(Vec3V&& vVector);
#endif // !RECON_OS_64BIT
	Vec3V_Out RECON_VEC_CALLCONV operator=(Vector_In vVector);

	void RECON_VEC_CALLCONV operator*=(ScalarV_In vScalar);
	void RECON_VEC_CALLCONV operator*=(Vec3V_In rhs);

	Vec3V_Out RECON_VEC_CALLCONV operator/(ScalarV_In vScalar) const;
	Vec3V_Out RECON_VEC_CALLCONV operator/(Vec3V_In rhs) const;

	void RECON_VEC_CALLCONV operator/=(ScalarV_In vScalar);
	void RECON_VEC_CALLCONV operator/=(Vec3V_In rhs);

	Vec3V_Out RECON_VEC_CALLCONV operator*(ScalarV_In vScalar) const;
	friend Vec3V_Out RECON_VEC_CALLCONV operator*(ScalarV_Ref vScalar, Vec3V_In vVector);
	Vec3V_Out RECON_VEC_CALLCONV operator*(Vec3V_In rhs) const;

	void RECON_VEC_CALLCONV operator+=(Vec3V_In vVector);
	Vec3V_Out RECON_VEC_CALLCONV operator+(Vec3V_In vVector) const;

	void RECON_VEC_CALLCONV operator-=(Vec3V_In vVector);
	Vec3V_Out RECON_VEC_CALLCONV operator-(Vec3V_In vVector) const;

	bool RECON_VEC_CALLCONV operator==(Vec3V_In vVector) const;

	bool RECON_VEC_CALLCONV operator!=(Vec3V_In vVector) const;

	Vec3V_Out RECON_VEC_CALLCONV operator&(Vec3V_In vVector) const;
	void RECON_VEC_CALLCONV operator&=(Vec3V_In vVector);

	Vec3V_Out RECON_VEC_CALLCONV operator|(Vec3V_In vVector) const;
	void RECON_VEC_CALLCONV operator|=(Vec3V_In vVector);

	Vec3V_Out RECON_VEC_CALLCONV operator^(Vec3V_In vVector) const;
	void RECON_VEC_CALLCONV operator^=(Vec3V_In vVector);

	Vec3V_Out operator~() const;

	const f32& operator[](s32 index) const;
	f32& operator[](s32 index);
};

ScalarV RECON_VEC_CALLCONV Dot(Vec3V_In lhs, Vec3V_In rhs);

ScalarV RECON_VEC_CALLCONV Mag(Vec3V_In vVector);
ScalarV RECON_VEC_CALLCONV Length(Vec3V_In vVector);
ScalarV RECON_VEC_CALLCONV MagSq(Vec3V_In vVector);
ScalarV RECON_VEC_CALLCONV LengthSq(Vec3V_In vVector);

Vec3V_Out RECON_VEC_CALLCONV Normalize(Vec3V_In vVector);
Vec3V_Out RECON_VEC_CALLCONV Cross(Vec3V_In vVectorA, Vec3V_In vVectorB);

Vec3V_Out RECON_VEC_CALLCONV Vec3VInt(s32 intVal);
Vec3V_Out RECON_VEC_CALLCONV Vec3VInt(s32 intX, s32 intY, s32 intZ);

#include "Vec3V.inl"

#endif // SSE_AVAILABLE

#endif // VEC3V_H