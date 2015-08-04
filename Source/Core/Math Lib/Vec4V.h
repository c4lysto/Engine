#ifndef VEC4V_H
#define VEC4V_H

#include "MathDeclarations.h"
#if SSE_AVAILABLE

typedef Vec4V& Vec4V_Ref;
typedef const Vec4V& Vec4V_ConstRef;

#if RECON_OS_64BIT
typedef Vec4V Vec4V_In;
#else
typedef Vec4V_ConstRef Vec4V_In;
#endif

typedef Vec4V Vec4V_Out;

typedef Vec4V_Ref Vec4V_InOut;

// Other Vec4V Aliases
typedef Vec4V float4V;

ALIGN(16) class Vec4V
{
#define DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(enumeration, xIntRep, yIntRep, zIntRep, wIntRep) \
	explicit FORCEINLINE Vec4V(enumeration) { row = VectorSetConstant<(u32)xIntRep, (u32)yIntRep, (u32)zIntRep, (u32)wIntRep>(); }

#define DEFINE_VEC4V_ENUM_CONSTRUCTOR(enumeration, intRep) \
	explicit FORCEINLINE Vec4V(enumeration) { row = VectorSetConstant<(u32)intRep>(); }

#define VEC4V_ACCESSOR(retType, funcName, retVal) \
	FORCEINLINE retType funcName() { return retVal; }

#define VEC4V_ACCESSOR_CONST(retType, funcName, retVal) \
	FORCEINLINE retType funcName() const { return retVal; }

#define VEC4V_ACCESSOR_SCALARV_CONST(element) \
	FORCEINLINE ScalarV_Out Get##element () const \
		{ return ScalarV(VectorPermute<VecElem::##element , VecElem::##element , VecElem::##element , VecElem::##element >(row)); }

#define VEC4V_MUTATOR(funcName, inType, modifiedVal) \
	FORCEINLINE void funcName(inType rhs) { modifiedVal = rhs; }


	friend class Mat44V;

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
	Vec4V(){}
	//Vec4V(Vec4V_In vVector);
#if !RECON_OS_64BIT
	Vec4V(Vec4V&& vVector);
#endif // !RECON_OS_64BIT
	explicit Vec4V(const float& fVal);
	explicit Vec4V(const float& fX, const float& fY, const float& fZ, const float& fW);
	explicit Vec4V(ScalarV_In vVal);
	explicit Vec4V(ScalarV_In vX, ScalarV_In vY, ScalarV_In vZ, ScalarV_In vW);
	explicit Vec4V(Vec2V_In vXY, Vec2V_In vZW);
	explicit Vec4V(ScalarV_In vX, ScalarV_In vY, Vec2V_In vZW);
	explicit Vec4V(Vec2V_In vXY, ScalarV_In vZ, ScalarV_In vW);
	explicit Vec4V(Vec3V_In vXYZ, ScalarV_In vW);
	explicit Vec4V(ScalarV_In vX, Vec3V_In vYZW);
	explicit Vec4V(Vector_In vVector);
#if !RECON_OS_64BIT
	Vec4V(Vector&& vVector);
#endif // !RECON_OS_64BIT

#if defined(VEC4V_ACCESSOR) && defined(VEC4V_ACCESSOR_CONST) && defined(VEC4V_ACCESSOR_SCALARV_CONST)
	VEC4V_ACCESSOR_SCALARV_CONST(X)
	VEC4V_ACCESSOR_SCALARV_CONST(Y)
	VEC4V_ACCESSOR_SCALARV_CONST(Z)
	VEC4V_ACCESSOR_SCALARV_CONST(W)
	VEC4V_ACCESSOR_CONST(const float&, GetXRef, x)
	VEC4V_ACCESSOR_CONST(const float&, GetYRef, y)
	VEC4V_ACCESSOR_CONST(const float&, GetZRef, z)
	VEC4V_ACCESSOR_CONST(const float&, GetWRef, w)
	FORCEINLINE Vec3V GetXYZ() const {return Vec3V(row);}

	VEC4V_ACCESSOR_CONST(Vector_Out, GetVector, row);

	VEC4V_ACCESSOR(float&, GetXRef, x)
	VEC4V_ACCESSOR(float&, GetYRef, y)
	VEC4V_ACCESSOR(float&, GetZRef, z)
	VEC4V_ACCESSOR(float&, GetWRef, w)
#undef VEC4V_ACCESSOR
#undef VEC4V_ACCESSOR_CONST
#undef VEC4V_ACCESSOR_SCALARV_CONST
#else
#error VEC4V ACCESSORS NOT DEFINED
#endif

#if defined(VEC4V_MUTATOR)
	void SetX(ScalarV_In vX);
	void SetY(ScalarV_In vY);
	void SetZ(ScalarV_In vZ);
	void SetW(ScalarV_In vW);

	VEC4V_MUTATOR(SetX, const float&, x)
	VEC4V_MUTATOR(SetY, const float&, y)
	VEC4V_MUTATOR(SetZ, const float&, z)
	VEC4V_MUTATOR(SetW, const float&, w)

	FORCEINLINE void SetXYZ(Vec3V_In rhs) {row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(rhs.GetVector(), row);}
	//FORCEINLINE void SetXYZ(Vec3V&& rhs) {row = VectorSet(rhs.x, rhs.y, rhs.z, w);}

#undef VEC4V_MUTATOR
#else
#error VEC4V MUTATORS NOT DEFINED
#endif

#ifdef DEFINE_VEC4V_ENUM_CONSTRUCTOR
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eZeroInitializer,		FloatToIntRep::Zero)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eOneInitializer,		FloatToIntRep::One)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eTwoInitializer,		FloatToIntRep::Two)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eThreeInitializer,	FloatToIntRep::Three)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFourInitializer,		FloatToIntRep::Four)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFiveInitializer,		FloatToIntRep::Five)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eSixInitializer,		FloatToIntRep::Six)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eSevenInitializer,	FloatToIntRep::Seven)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eEightInitializer,	FloatToIntRep::Eight)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNineInitializer,		FloatToIntRep::Nine)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eTenInitializer, 		FloatToIntRep::Ten)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eQuarterInitializer,	FloatToIntRep::Quarter)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eHalfInitializer,		FloatToIntRep::Half)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(ePIInitializer, 		FloatToIntRep::Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eHalfPIInitializer,	FloatToIntRep::Half_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eTwoPIInitializer,	FloatToIntRep::Two_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFLTMINInitializer,	FloatToIntRep::Flt_Min)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFLTMAXInitializer,	FloatToIntRep::Flt_Max)

	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegOneInitializer,		FloatToIntRep::Neg_One)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegTwoInitializer,		FloatToIntRep::Neg_Two)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegThreeInitializer,		FloatToIntRep::Neg_Three)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegFourInitializer,		FloatToIntRep::Neg_Four)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegFiveInitializer,		FloatToIntRep::Neg_Five)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegSixInitializer, 		FloatToIntRep::Neg_Six)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegSevenInitializer,		FloatToIntRep::Neg_Seven)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegEightInitializer,		FloatToIntRep::Neg_Eight)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegNineInitializer,		FloatToIntRep::Neg_Nine)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegTenInitializer, 		FloatToIntRep::Neg_Ten)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegQuarterInitializer,	FloatToIntRep::Neg_Quarter)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegHalfInitializer,		FloatToIntRep::Neg_Half)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegPIInitializer,		FloatToIntRep::Neg_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegHalfPIInitializer, 	FloatToIntRep::Neg_Half_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegTwoPIInitializer, 	FloatToIntRep::Neg_Two_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegFLTMINInitializer,	FloatToIntRep::Neg_Flt_Min)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer,	FloatToIntRep::Neg_Flt_Max)

	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eXAxisInitializer, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::Zero)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eYAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eZAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eWAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::One)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eUpAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero)
#undef DEFINE_VEC4V_ENUM_CONSTRUCTOR
#undef DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR
#endif //DEFINE_VEC4_ENUM_CONSTRUCTOR

	Vec4V_Out operator-() const;

	Vec4V_Out operator=(Vec4V_In vVector);
#if !RECON_OS_64BIT
	Vec4V_Out operator=(Vec4V&& vVector);
#endif // !_WIN_64

	Vec4V_Out operator-(Vec4V_In vVector) const;
	void operator-=(Vec4V_In vVector);

	Vec4V_Out operator+(Vec4V_In vVector) const;
	void operator+=(Vec4V_In vVector);

	Vec4V_Out operator/(ScalarV_In vScalar) const;
	void operator/=(ScalarV_In vScalar);
	Vec4V_Out operator/(Vec4V_In vVector) const;
	void operator/=(Vec4V_In vVector);

	Vec4V_Out operator*(ScalarV_In vScalar) const;
	void operator*=(ScalarV_In vScalar);
	friend Vec4V_Out operator*(ScalarV_Ref vScalar, Vec4V_In vVector);
	Vec4V_Out operator*(Vec4V_In vVector) const;
	void operator*=(Vec4V_In vVector);

	bool operator==(Vec4V_In vVector) const;
	bool operator!=(Vec4V_In vVector) const;

	Vec4V_Out operator&(Vec4V_In vVector) const;
	void operator&=(Vec4V_In vVector);

	Vec4V_Out operator|(Vec4V_In vVector) const;
	void operator|=(Vec4V_In vVector);

	Vec4V_Out operator^(Vec4V_In vVector) const;
	void operator^=(Vec4V_In vVector);

	Vec4V_Out operator~() const;

	const float& operator[](int index) const;
	float& operator[](int index);

	Vec4V_Out Normalize();
};

GLOBALCONST Vec4V g_IdentityX4V = Vec4V(I_X_AXIS);
GLOBALCONST Vec4V g_IdentityY4V = Vec4V(I_Y_AXIS);
GLOBALCONST Vec4V g_IdentityZ4V = Vec4V(I_Z_AXIS);
GLOBALCONST Vec4V g_IdentityW4V = Vec4V(I_W_AXIS);
GLOBALCONST Vec4V g_WorldUp4V	= Vec4V(I_UP_AXIS);

Vec4V_Out Vec4VInt(int intVal);
Vec4V_Out Vec4VInt(int intX, int intY, int intZ, int intW);

ScalarV Dot(Vec4V_In lhs, Vec4V_In rhs);

ScalarV Mag(Vec4V_In vVector);
ScalarV Length(Vec4V_In vVector);
ScalarV MagSq(Vec4V_In vVector);
ScalarV LengthSq(Vec4V_In vVector);

Vec4V_Out Normalize(Vec4V_In vVector);
Vec4V_Out Cross(Vec4V_In vVectorA, Vec4V_In vVectorB);

#include "Vec4V.inl"

#endif // SSE_AVAILABLE

#endif // VEC4V_H