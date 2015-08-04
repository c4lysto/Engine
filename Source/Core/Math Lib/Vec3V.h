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
#define DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(enumeration, xIntRep, yIntRep, zIntRep)\
	explicit FORCEINLINE Vec3V(enumeration) { row = VectorSetConstant<(u32)xIntRep, (u32)yIntRep, (u32)zIntRep, (u32)FloatToIntRep::Zero>(); }

#define DEFINE_VEC3V_ENUM_CONSTRUCTOR(enumeration, intRep)\
	explicit FORCEINLINE Vec3V(enumeration) { row = VectorSetConstant<(u32)intRep>(); }

#define DEFINE_VEC3V_ENUM_VEC_CONSTRUCTOR(enumeration, vec)\
	explicit FORCEINLINE Vec3V(enumeration) { row = vec.row; }

#define VEC3V_ACCESSOR(retType, funcName, retVal) \
	FORCEINLINE retType funcName() { return retVal; }

#define VEC3V_ACCESSOR_SCALARV_CONST(element) \
	FORCEINLINE ScalarV_Out Get##element () const \
	{ return ScalarV(VectorPermute<VecElem::##element , VecElem::##element , VecElem::##element , VecElem::##element >(row)); }

#define VEC3V_ACCESSOR_CONST(retType, funcName, retVal) \
	FORCEINLINE retType funcName() const { return retVal; }

#define VEC3V_MUTATOR(funcName, inType, modifiedVal) \
	FORCEINLINE void funcName(inType rhs) { modifiedVal = rhs; }

	friend class Vec4V;

private:
	union
	{
		float floatArr[4];
		Vector row;

		union
		{
			struct
			{
				float x, y, z, w;
			};
		};
	};

public:
	Vec3V(){}
	explicit Vec3V(const float& fVal);
	explicit Vec3V(const float& fX, const float& fY, const float& fZ);
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
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eZeroInitializer,		FloatToIntRep::Zero)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eOneInitializer,		FloatToIntRep::One)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eTwoInitializer,		FloatToIntRep::Two)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eThreeInitializer,	FloatToIntRep::Three)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFourInitializer,		FloatToIntRep::Four)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFiveInitializer,		FloatToIntRep::Five)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eSixInitializer,		FloatToIntRep::Six)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eSevenInitializer,	FloatToIntRep::Seven)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eEightInitializer,	FloatToIntRep::Eight)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNineInitializer,		FloatToIntRep::Nine)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eTenInitializer, 		FloatToIntRep::Ten)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eQuarterInitializer,	FloatToIntRep::Quarter)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eHalfInitializer,		FloatToIntRep::Half)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(ePIInitializer, 		FloatToIntRep::Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eHalfPIInitializer,	FloatToIntRep::Half_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eTwoPIInitializer,	FloatToIntRep::Two_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFLTMINInitializer,	FloatToIntRep::Flt_Min)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eFLTMAXInitializer,	FloatToIntRep::Flt_Max)

	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegOneInitializer,		FloatToIntRep::Neg_One)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegTwoInitializer,		FloatToIntRep::Neg_Two)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegThreeInitializer,		FloatToIntRep::Neg_Three)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegFourInitializer,		FloatToIntRep::Neg_Four)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegFiveInitializer,		FloatToIntRep::Neg_Five)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegSixInitializer, 		FloatToIntRep::Neg_Six)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegSevenInitializer,		FloatToIntRep::Neg_Seven)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegEightInitializer,		FloatToIntRep::Neg_Eight)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegNineInitializer,		FloatToIntRep::Neg_Nine)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegTenInitializer, 		FloatToIntRep::Neg_Ten)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegQuarterInitializer,	FloatToIntRep::Neg_Quarter)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegHalfInitializer,		FloatToIntRep::Neg_Half)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegPIInitializer,		FloatToIntRep::Neg_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegHalfPIInitializer, 	FloatToIntRep::Neg_Half_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegTwoPIInitializer, 	FloatToIntRep::Neg_Two_Pi)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegFLTMINInitializer,	FloatToIntRep::Neg_Flt_Min)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer,	FloatToIntRep::Neg_Flt_Max)

	DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(eXAxisInitializer, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero)
	DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(eYAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero)
	DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(eZAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::One)
	DEFINE_VEC3V_ENUM_CONSTRUCTOR(eWAxisInitializer, FloatToIntRep::Zero)
	DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR(eUpAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero)
#undef DEFINE_VEC3V_ENUM_CONSTRUCTOR
#undef DEFINE_VEC3V_ENUM_VAL_CONSTRUCTOR
#endif //DEFINE_VEC3_ENUM_CONSTRUCTOR

#if defined(VEC3V_ACCESSOR) && defined(VEC3V_ACCESSOR_CONST) && defined(VEC3V_ACCESSOR_SCALARV_CONST)
	VEC3V_ACCESSOR_SCALARV_CONST(X)
	VEC3V_ACCESSOR_SCALARV_CONST(Y)
	VEC3V_ACCESSOR_SCALARV_CONST(Z)
	VEC3V_ACCESSOR_SCALARV_CONST(W)
	VEC3V_ACCESSOR_CONST(const float&, GetXRef, x)
	VEC3V_ACCESSOR_CONST(const float&, GetYRef, y)
	VEC3V_ACCESSOR_CONST(const float&, GetZRef, z)
	VEC3V_ACCESSOR_CONST(const float&, GetWRef, w)

	// Returns the Vector Intrinsic Data Type
	VEC3V_ACCESSOR_CONST(Vector_Out, GetVector, row)

	VEC3V_ACCESSOR(float&, GetXRef, x)
	VEC3V_ACCESSOR(float&, GetYRef, y)
	VEC3V_ACCESSOR(float&, GetZRef, z)
	VEC3V_ACCESSOR(float&, GetWRef, w)
#undef VEC3V_ACCESSOR
#undef VEC3V_ACCESSOR_CONST
#undef VEC3V_ACCESSOR_SCALARV_CONST
#else
#error VEC3V ACCESSORS NOT DEFINED
#endif

#if defined(VEC3V_MUTATOR)
	void SetX(ScalarV_In vX);
	void SetY(ScalarV_In vY);
	void SetZ(ScalarV_In vZ);
	void SetW(ScalarV_In vW);

	VEC3V_MUTATOR(SetX, const float&, x)
	VEC3V_MUTATOR(SetY, const float&, y)
	VEC3V_MUTATOR(SetZ, const float&, z)
	VEC3V_MUTATOR(SetW, const float&, w)
#undef VEC3V_MUTATOR
#else
#error VEC3V MUTATORS NOT DEFINED
#endif

	Vec3V_Out operator-() const;

	Vec3V_Out operator=(Vec3V_In vVector);
#if !RECON_OS_64BIT
	Vec3V_Out operator=(Vec3V&& vVector);
#endif // !RECON_OS_64BIT
	Vec3V_Out operator=(Vector_In vVector);

	void operator*=(ScalarV_In vScalar);
	void operator*=(Vec3V_In rhs);

	Vec3V_Out operator/(ScalarV_In vScalar) const;
	Vec3V_Out operator/(Vec3V_In rhs) const;

	void operator/=(ScalarV_In vScalar);
	void operator/=(Vec3V_In rhs);

	Vec3V_Out operator*(ScalarV_In vScalar) const;
	friend Vec3V_Out operator*(ScalarV_Ref vScalar, Vec3V_In vVector);
	Vec3V_Out operator*(Vec3V_In rhs) const;

	void operator+=(Vec3V_In vVector);
	Vec3V_Out operator+(Vec3V_In vVector) const;

	void operator-=(Vec3V_In vVector);
	Vec3V_Out operator-(Vec3V_In vVector) const;

	bool operator==(Vec3V_In vVector) const;

	bool operator!=(Vec3V_In vVector) const;

	Vec3V_Out operator&(Vec3V_In vVector) const;
	void operator&=(Vec3V_In vVector);

	Vec3V_Out operator|(Vec3V_In vVector) const;
	void operator|=(Vec3V_In vVector);

	Vec3V_Out operator^(Vec3V_In vVector) const;
	void operator^=(Vec3V_In vVector);

	Vec3V_Out operator~() const;

	const float& operator[](int index) const;
	float& operator[](int index);

	Vec3V_Out Normalize();
};

ScalarV Dot(Vec3V_In lhs, Vec3V_In rhs);

ScalarV Mag(Vec3V_In vVector);
ScalarV Length(Vec3V_In vVector);
ScalarV MagSq(Vec3V_In vVector);
ScalarV LengthSq(Vec3V_In vVector);

Vec3V_Out Normalize(Vec3V_In vVector);
Vec3V_Out Cross(Vec3V_In vVectorA, Vec3V_In vVectorB);

Vec3V_Out Vec3VInt(int intVal);
Vec3V_Out Vec3VInt(int intX, int intY, int intZ);

Vec3V_Out Vec3VIntToFloat(Vec3V_In vec);
Vec3V_Out Vec3VFloatToInt(Vec3V_In vec);


GLOBALCONST Vec3V g_IdentityX3V = Vec3V(I_X_AXIS);
GLOBALCONST Vec3V g_IdentityY3V = Vec3V(I_Y_AXIS);
GLOBALCONST Vec3V g_IdentityZ3V = Vec3V(I_Z_AXIS);
GLOBALCONST Vec3V g_IdentityW3V	= Vec3V(I_ZERO);
GLOBALCONST Vec3V g_WorldUp3V	= Vec3V(I_UP_AXIS);

#include "Vec3V.inl"

#endif // SSE_AVAILABLE

#endif // VEC3V_H