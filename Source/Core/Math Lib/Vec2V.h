#ifndef VEC2V_H
#define VEC2V_H

#include "MathDeclarations.h"
#if SSE_AVAILABLE

#include "ScalarV.h"

class Vec2V;

typedef Vec2V& Vec2V_Ref;
typedef const Vec2V& Vec2V_ConstRef;

#if RECON_OS_64BIT
typedef Vec2V Vec2V_In;
#else
typedef Vec2V_ConstRef Vec2V_In;
#endif

typedef Vec2V Vec2V_Out;

typedef Vec2V_Ref Vec2V_InOut;

// Other Vec2V Aliases
typedef Vec2V float2V;


ALIGN(16) class Vec2V
{
#define DEFINE_VEC2V_ENUM_VAL_CONSTRUCTOR(enumeration, xIntRep, yIntRep)\
	explicit __forceinline Vec2V(enumeration) { row = VectorSetConstant<(u32)xIntRep, (u32)yIntRep, (u32)FloatToIntRep::Zero, (u32)FloatToIntRep::Zero>(); }

#define DEFINE_VEC2V_ENUM_CONSTRUCTOR(enumeration, intRep)\
	explicit __forceinline Vec2V(enumeration) { row = VectorSetConstant<(u32)intRep>(); }

#define VEC2V_ACCESSOR(retType, funcName, retVal) \
	__forceinline retType funcName() { return retVal; }

#define VEC2V_ACCESSOR_CONST(retType, funcName, retVal) \
	__forceinline retType funcName() const { return retVal; }

#define VEC2V_ACCESSOR_SCALARV_CONST(funcName, elementIndex) \
	__forceinline ScalarV_Out RECON_VEC_CALLCONV funcName() const \
		{ return ScalarV(VectorPermute< VecElem::##elementIndex , VecElem::##elementIndex , VecElem::##elementIndex , VecElem::##elementIndex >(row)); }

#define VEC2V_MUTATOR(funcName, inType, modifiedVal) \
	__forceinline void funcName(inType rhs) { modifiedVal = rhs; }


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
	Vec2V(){}
	explicit Vec2V(const f32& fVal);
	explicit Vec2V(const f32& fX, const f32& fY);
	explicit Vec2V(ScalarV_In vVal);
	explicit Vec2V(ScalarV_In vX, ScalarV_In vY);
	//Vec2V(Vec2V_In vVector);
#if !RECON_OS_64BIT
	Vec2V(Vec2V&& vVector);
#endif // !RECON_OS_64BIT
	~Vec2V(){}

	explicit Vec2V(Vector_In rhs);
#if !RECON_OS_64BIT
	Vec2V(Vector&& rhs);
#endif // !RECON_OS_64BIT

#if defined(DEFINE_VEC2V_ENUM_CONSTRUCTOR) && defined(DEFINE_VEC2V_ENUM_VAL_CONSTRUCTOR)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eZeroInitializer,		FloatToIntRep::Zero)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eOneInitializer,		FloatToIntRep::One)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eTwoInitializer,		FloatToIntRep::Two)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eThreeInitializer,	FloatToIntRep::Three)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eFourInitializer,		FloatToIntRep::Four)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eFiveInitializer,		FloatToIntRep::Five)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eSixInitializer,		FloatToIntRep::Six)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eSevenInitializer,	FloatToIntRep::Seven)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eEightInitializer,	FloatToIntRep::Eight)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNineInitializer,		FloatToIntRep::Nine)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eTenInitializer, 		FloatToIntRep::Ten)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eQuarterInitializer,	FloatToIntRep::Quarter)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eHalfInitializer,		FloatToIntRep::Half)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(ePIInitializer, 		FloatToIntRep::Pi)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eHalfPIInitializer,	FloatToIntRep::Half_Pi)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eTwoPIInitializer,	FloatToIntRep::Two_Pi)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eFLTMINInitializer,	FloatToIntRep::Flt_Min)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eFLTMAXInitializer,	FloatToIntRep::Flt_Max)

	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegOneInitializer,		FloatToIntRep::Neg_One)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegTwoInitializer,		FloatToIntRep::Neg_Two)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegThreeInitializer,		FloatToIntRep::Neg_Three)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegFourInitializer,		FloatToIntRep::Neg_Four)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegFiveInitializer,		FloatToIntRep::Neg_Five)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegSixInitializer, 		FloatToIntRep::Neg_Six)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegSevenInitializer,		FloatToIntRep::Neg_Seven)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegEightInitializer,		FloatToIntRep::Neg_Eight)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegNineInitializer,		FloatToIntRep::Neg_Nine)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegTenInitializer, 		FloatToIntRep::Neg_Ten)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegQuarterInitializer,	FloatToIntRep::Neg_Quarter)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegHalfInitializer,		FloatToIntRep::Neg_Half)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegPIInitializer,		FloatToIntRep::Neg_Pi)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegHalfPIInitializer, 	FloatToIntRep::Neg_Half_Pi)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegTwoPIInitializer, 	FloatToIntRep::Neg_Two_Pi)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegFLTMINInitializer,	FloatToIntRep::Neg_Flt_Min)
	DEFINE_VEC2V_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer,	FloatToIntRep::Neg_Flt_Max)

	DEFINE_VEC2V_ENUM_VAL_CONSTRUCTOR(eXAxisInitializer, FloatToIntRep::One, FloatToIntRep::Zero)
	DEFINE_VEC2V_ENUM_VAL_CONSTRUCTOR(eYAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One)
#undef DEFINE_VEC2V_ENUM_CONSTRUCTOR
#undef DEFINE_VEC2V_ENUM_VAL_CONSTRUCTOR
#else
#error VEC2V ENUM CONSTRUCTORS NOT DEFINED
#endif

#if defined(VEC2V_ACCESSOR) && defined(VEC2V_ACCESSOR_CONST) && defined(VEC2V_ACCESSOR_SCALARV_CONST)
	VEC2V_ACCESSOR_SCALARV_CONST(GetX, X)
	VEC2V_ACCESSOR_SCALARV_CONST(GetY, Y)
	VEC2V_ACCESSOR_SCALARV_CONST(GetZ, Z)
	VEC2V_ACCESSOR_SCALARV_CONST(GetW, W)
	VEC2V_ACCESSOR_CONST(const f32&, GetXRef, x)
	VEC2V_ACCESSOR_CONST(const f32&, GetYRef, y)
	VEC2V_ACCESSOR_CONST(const f32&, GetZRef, z)
	VEC2V_ACCESSOR_CONST(const f32&, GetWRef, w)

	VEC2V_ACCESSOR_CONST(Vector_Out, RECON_VEC_CALLCONV GetVector, row)

	VEC2V_ACCESSOR(f32&, GetXRef, x)
	VEC2V_ACCESSOR(f32&, GetYRef, y)
	VEC2V_ACCESSOR(f32&, GetZRef, z)
	VEC2V_ACCESSOR(f32&, GetWRef, w)
#undef VEC2V_ACCESSOR
#undef VEC2V_ACCESSOR_CONST
#undef VEC2V_ACCESSOR_SCALARV_CONST
#else
#error VEC2V ACCESSORS NOT DEFINED
#endif

#if defined(VEC2V_MUTATOR)
	void RECON_VEC_CALLCONV SetX(ScalarV_In xVal);
	void RECON_VEC_CALLCONV SetY(ScalarV_In yVal);
	void RECON_VEC_CALLCONV SetZ(ScalarV_In zVal);
	void RECON_VEC_CALLCONV SetW(ScalarV_In wVal);

	VEC2V_MUTATOR(SetX, const f32&, x)
	VEC2V_MUTATOR(SetY, const f32&, y)
	VEC2V_MUTATOR(SetZ, const f32&, z)
	VEC2V_MUTATOR(SetW, const f32&, w)

#undef VEC2V_MUTATOR
#else
#error VEC2V MUTATORS NOT DEFINED
#endif

	Vec2V_Out operator-() const;

	Vec2V_Out RECON_VEC_CALLCONV operator=(Vec2V_In vVector);
#if !RECON_OS_64BIT
	Vec2V_Out RECON_VEC_CALLCONV operator=(Vec2V&& vVector);
#endif // !RECON_OS_64BIT

	Vec2V_Out RECON_VEC_CALLCONV operator+(Vec2V_In vVector) const;
	void RECON_VEC_CALLCONV operator+=(Vec2V_In vVector);

	Vec2V_Out RECON_VEC_CALLCONV operator-(Vec2V_In vVector) const;
	void RECON_VEC_CALLCONV operator-=(Vec2V_In vVector);

	Vec2V_Out RECON_VEC_CALLCONV operator*(Vec2V_In vVector) const;
	Vec2V_Out RECON_VEC_CALLCONV operator*(ScalarV_In vScalar) const;
	friend Vec2V_Out RECON_VEC_CALLCONV operator*(ScalarV_Ref vScalar, Vec2V_In vVector);

	void RECON_VEC_CALLCONV operator*=(Vec2V_In vVector);
	void RECON_VEC_CALLCONV operator*=(ScalarV_In vScalar);

	Vec2V_Out RECON_VEC_CALLCONV operator/(Vec2V_In vVector) const;
	Vec2V_Out RECON_VEC_CALLCONV operator/(ScalarV_In fScalar) const;

	void RECON_VEC_CALLCONV operator/=(Vec2V_In vVector);
	void RECON_VEC_CALLCONV operator/=(ScalarV_In fScalar);

	bool RECON_VEC_CALLCONV operator==(Vec2V_In vVector) const;
	bool RECON_VEC_CALLCONV operator!=(Vec2V_In vVector) const;

	Vec2V_Out RECON_VEC_CALLCONV operator&(Vec2V_In vVector) const;
	void RECON_VEC_CALLCONV operator&=(Vec2V_In vVector);

	Vec2V_Out RECON_VEC_CALLCONV operator|(Vec2V_In vVector) const;
	void RECON_VEC_CALLCONV operator|=(Vec2V_In vVector);

	Vec2V_Out RECON_VEC_CALLCONV operator^(Vec2V_In vVector) const;
	void RECON_VEC_CALLCONV operator^=(Vec2V_In vVector);

	Vec2V_Out RECON_VEC_CALLCONV operator~() const;

	const f32& operator[](s32 index) const;
	f32& operator[](s32 index);
};

Vec2V_Out RECON_VEC_CALLCONV Vec2VInt(s32 intVal);
Vec2V_Out RECON_VEC_CALLCONV Vec2VInt(s32 intX, s32 intY);

ScalarV RECON_VEC_CALLCONV Dot(Vec2V_In lhs, Vec2V_In rhs);

ScalarV RECON_VEC_CALLCONV Mag(Vec2V_In vVector);
ScalarV RECON_VEC_CALLCONV Length(Vec2V_In vVector);
ScalarV RECON_VEC_CALLCONV MagSq(Vec2V_In vVector);
ScalarV RECON_VEC_CALLCONV LengthSq(Vec2V_In vVector);

Vec2V_Out RECON_VEC_CALLCONV Normalize(Vec2V_In vVector);
Vec2V_Out RECON_VEC_CALLCONV Cross(Vec2V_In vVectorA, Vec2V_In vVectorB);

#include "Vec2V.inl"

#endif //SSE_AVAILABLE

#endif // VEC2V_H