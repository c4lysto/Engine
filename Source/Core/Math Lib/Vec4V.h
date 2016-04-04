#ifndef VEC4V_H
#define VEC4V_H

#include "MathDeclarations.h"
#if RECON_SSE_VERSION

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
	explicit __forceinline Vec4V(enumeration) : row(VectorSetConstant<(u32)xIntRep, (u32)yIntRep, (u32)zIntRep, (u32)wIntRep>()) { }

#define DEFINE_VEC4V_ENUM_CONSTRUCTOR(enumeration, intRep) DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(enumeration, intRep, intRep, intRep, intRep)

#define VEC4V_ACCESSOR(retType, funcName, retVal) \
	__forceinline retType funcName() { return retVal; }

#define VEC4V_ACCESSOR_CONST(retType, funcName, retVal) \
	__forceinline retType funcName() const { return retVal; }

#define VEC4V_ACCESSOR_SCALARV_CONST(element) \
	__forceinline ScalarV_Out RECON_VEC_CALLCONV Get##element() const \
		{ return ScalarV(VectorPermute<VecElem::##element , VecElem::##element , VecElem::##element , VecElem::##element >(row)); }

#define VEC4V_MUTATOR(funcName, inType, modifiedVal) \
	__forceinline void funcName(inType rhs) { modifiedVal = rhs; }


	friend class Mat44V;

private:
	union
	{
		f32 floatArr[4];
		Vector128 row;

		union
		{
			struct
			{
				f32 x, y, z, w;
			};
		};
	};

public:
	Vec4V(){}
	//Vec4V(Vec4V_In vVector);
#if !RECON_OS_64BIT
	Vec4V(Vec4V&& vVector);
#endif // !RECON_OS_64BIT
	explicit Vec4V(const f32& fVal);
	explicit Vec4V(const f32& fX, const f32& fY, const f32& fZ, const f32& fW);
	explicit Vec4V(ScalarV_In vVal);
	explicit Vec4V(ScalarV_In vX, ScalarV_In vY, ScalarV_In vZ, ScalarV_In vW);
	explicit Vec4V(Vec2V_In vXY, Vec2V_In vZW);
	explicit Vec4V(ScalarV_In vX, ScalarV_In vY, Vec2V_In vZW);
	explicit Vec4V(Vec2V_In vXY, ScalarV_In vZ, ScalarV_In vW);
	explicit Vec4V(Vec3V_In vXYZ, ScalarV_In vW);
	explicit Vec4V(ScalarV_In vX, Vec3V_In vYZW);
	explicit Vec4V(Vector128_In vVector);
#if !RECON_OS_64BIT
	Vec4V(Vector128&& vVector);
#endif // !RECON_OS_64BIT

#if defined(VEC4V_ACCESSOR) && defined(VEC4V_ACCESSOR_CONST) && defined(VEC4V_ACCESSOR_SCALARV_CONST)
	VEC4V_ACCESSOR_SCALARV_CONST(X)
	VEC4V_ACCESSOR_SCALARV_CONST(Y)
	VEC4V_ACCESSOR_SCALARV_CONST(Z)
	VEC4V_ACCESSOR_SCALARV_CONST(W)
	VEC4V_ACCESSOR_CONST(const f32&, GetXRef, x)
	VEC4V_ACCESSOR_CONST(const f32&, GetYRef, y)
	VEC4V_ACCESSOR_CONST(const f32&, GetZRef, z)
	VEC4V_ACCESSOR_CONST(const f32&, GetWRef, w)
	__forceinline Vec3V RECON_VEC_CALLCONV GetXYZ() const { return Vec3V(row); }

	VEC4V_ACCESSOR_CONST(Vector128_Out, RECON_VEC_CALLCONV GetVector, row)
	VEC4V_ACCESSOR_CONST(Vector128_ConstRef, RECON_VEC_CALLCONV GetVectorRef, row)

	VEC4V_ACCESSOR(f32&, GetXRef, x)
	VEC4V_ACCESSOR(f32&, GetYRef, y)
	VEC4V_ACCESSOR(f32&, GetZRef, z)
	VEC4V_ACCESSOR(f32&, GetWRef, w)
	VEC4V_ACCESSOR(Vector128_Ref, RECON_VEC_CALLCONV GetVectorRef, row)
#undef VEC4V_ACCESSOR
#undef VEC4V_ACCESSOR_CONST
#undef VEC4V_ACCESSOR_SCALARV_CONST
#else
#error VEC4V ACCESSORS NOT DEFINED
#endif

#if defined(VEC4V_MUTATOR)
	void RECON_VEC_CALLCONV SetX(ScalarV_In vX);
	void RECON_VEC_CALLCONV SetY(ScalarV_In vY);
	void RECON_VEC_CALLCONV SetZ(ScalarV_In vZ);
	void RECON_VEC_CALLCONV SetW(ScalarV_In vW);

	VEC4V_MUTATOR(SetX, const f32&, x)
	VEC4V_MUTATOR(SetY, const f32&, y)
	VEC4V_MUTATOR(SetZ, const f32&, z)
	VEC4V_MUTATOR(SetW, const f32&, w)

	__forceinline void SetXYZ(Vec3V_In rhs) {row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(rhs.GetVector(), row);}
	//__forceinline void SetXYZ(Vec3V&& rhs) {row = VectorSet(rhs.x, rhs.y, rhs.z, w);}

#undef VEC4V_MUTATOR
#else
#error VEC4V MUTATORS NOT DEFINED
#endif

#ifdef DEFINE_VEC4V_ENUM_CONSTRUCTOR
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eZeroInitializer,			FloatToIntRep::Zero)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eOneInitializer,			FloatToIntRep::One)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eTwoInitializer,			FloatToIntRep::Two)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eThreeInitializer,		FloatToIntRep::Three)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFourInitializer,			FloatToIntRep::Four)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFiveInitializer,			FloatToIntRep::Five)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eSixInitializer,			FloatToIntRep::Six)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eSevenInitializer,		FloatToIntRep::Seven)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eEightInitializer,		FloatToIntRep::Eight)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNineInitializer,			FloatToIntRep::Nine)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eTenInitializer, 			FloatToIntRep::Ten)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eQuarterInitializer,		FloatToIntRep::Quarter)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eHalfInitializer,			FloatToIntRep::Half)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(ePIInitializer, 			FloatToIntRep::Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eHalfPIInitializer,		FloatToIntRep::Half_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eTwoPIInitializer,		FloatToIntRep::Two_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFLTMINInitializer,		FloatToIntRep::Flt_Min)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFLTMAXInitializer,		FloatToIntRep::Flt_Max)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFLTEpsilonInitializer,	FloatToIntRep::Flt_Epsilon)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNANInitializer,			FloatToIntRep::NaN)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eSignBitInitializer,		FloatToIntRep::Sign_Bit)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eAbsMaskInitializer,		FloatToIntRep::Abs_Mask)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTOneInitializer,		1)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTTwoInitializer,		2)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTThreeInitializer,		3)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTFourInitializer,		4)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTFiveInitializer,		5)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTSixInitializer,		6)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTSevenInitializer,		7)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTEightInitializer,		8)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNineInitializer,		9)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTTenInitializer,		10)

	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegOneInitializer,			FloatToIntRep::Neg_One)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegTwoInitializer,			FloatToIntRep::Neg_Two)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegThreeInitializer,			FloatToIntRep::Neg_Three)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegFourInitializer,			FloatToIntRep::Neg_Four)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegFiveInitializer,			FloatToIntRep::Neg_Five)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegSixInitializer, 			FloatToIntRep::Neg_Six)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegSevenInitializer,			FloatToIntRep::Neg_Seven)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegEightInitializer,			FloatToIntRep::Neg_Eight)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegNineInitializer,			FloatToIntRep::Neg_Nine)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegTenInitializer, 			FloatToIntRep::Neg_Ten)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegQuarterInitializer,		FloatToIntRep::Neg_Quarter)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegHalfInitializer,			FloatToIntRep::Neg_Half)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegPIInitializer,			FloatToIntRep::Neg_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegHalfPIInitializer, 		FloatToIntRep::Neg_Half_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegTwoPIInitializer, 		FloatToIntRep::Neg_Two_Pi)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegFLTMINInitializer,		FloatToIntRep::Neg_Flt_Min)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer,		FloatToIntRep::Neg_Flt_Max)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegFLTEpsilonInitializer,	FloatToIntRep::Neg_Flt_Epsilon)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eNegNANInitializer,			FloatToIntRep::Neg_NaN)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegOneInitializer,		-1)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegTwoInitializer,		-2)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegThreeInitializer,		-3)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegFourInitializer,		-4)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegFiveInitializer,		-5)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegSixInitializer,		-6)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegSevenInitializer,		-7)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegEightInitializer,		-8)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegNineInitializer,		-9)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eINTNegTenInitializer,		-10)

	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eXAxisInitializer, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::Zero)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eYAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eZAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eWAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::Zero, FloatToIntRep::One)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eUpAxisInitializer, FloatToIntRep::Zero, FloatToIntRep::One, FloatToIntRep::Zero, FloatToIntRep::Zero)

	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eTrueInitializer, FloatToIntRep::True)
	DEFINE_VEC4V_ENUM_CONSTRUCTOR(eFalseInitializer, FloatToIntRep::False)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eTTTFInitializer, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::False)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eTTFTInitializer, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::True)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eTTFFInitializer, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::False)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eTFTTInitializer, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::True)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eTFTFInitializer, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::False)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eTFFTInitializer, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::True)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eTFFFInitializer, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::False)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eFTTTInitializer, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::True)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eFTTFInitializer, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::True, FloatToIntRep::False)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eFTFTInitializer, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::True)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eFTFFInitializer, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::False, FloatToIntRep::False)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eFFTTInitializer, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::True)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eFFTFInitializer, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::True, FloatToIntRep::False)
	DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR(eFFFTInitializer, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::False, FloatToIntRep::True)
#undef DEFINE_VEC4V_ENUM_CONSTRUCTOR
#undef DEFINE_VEC4V_ENUM_VAL_CONSTRUCTOR
#endif //DEFINE_VEC4_ENUM_CONSTRUCTOR

	Vec4V_Out operator-() const;

	Vec4V_Out RECON_VEC_CALLCONV operator=(Vec4V_In vVector);
#if !RECON_OS_64BIT
	Vec4V_Out RECON_VEC_CALLCONV operator=(Vec4V&& vVector);
#endif // !_WIN_64

	Vec4V_Out RECON_VEC_CALLCONV operator-(Vec4V_In vVector) const;
	void RECON_VEC_CALLCONV operator-=(Vec4V_In vVector);

	Vec4V_Out RECON_VEC_CALLCONV operator+(Vec4V_In vVector) const;
	void RECON_VEC_CALLCONV operator+=(Vec4V_In vVector);

	Vec4V_Out RECON_VEC_CALLCONV operator/(ScalarV_In vScalar) const;
	void RECON_VEC_CALLCONV operator/=(ScalarV_In vScalar);
	Vec4V_Out RECON_VEC_CALLCONV operator/(Vec4V_In vVector) const;
	void RECON_VEC_CALLCONV operator/=(Vec4V_In vVector);

	Vec4V_Out RECON_VEC_CALLCONV operator*(ScalarV_In vScalar) const;
	void RECON_VEC_CALLCONV operator*=(ScalarV_In vScalar);
	friend Vec4V_Out RECON_VEC_CALLCONV operator*(ScalarV_Ref vScalar, Vec4V_In vVector);
	Vec4V_Out RECON_VEC_CALLCONV operator*(Vec4V_In vVector) const;
	void RECON_VEC_CALLCONV operator*=(Vec4V_In vVector);

	bool RECON_VEC_CALLCONV operator==(Vec4V_In vVector) const;
	bool RECON_VEC_CALLCONV operator!=(Vec4V_In vVector) const;

	Vec4V_Out RECON_VEC_CALLCONV operator&(Vec4V_In vVector) const;
	void RECON_VEC_CALLCONV operator&=(Vec4V_In vVector);

	Vec4V_Out RECON_VEC_CALLCONV operator|(Vec4V_In vVector) const;
	void RECON_VEC_CALLCONV operator|=(Vec4V_In vVector);

	Vec4V_Out RECON_VEC_CALLCONV operator^(Vec4V_In vVector) const;
	void RECON_VEC_CALLCONV operator^=(Vec4V_In vVector);

	Vec4V_Out operator~() const;

	const f32& operator[](s32 index) const;
	f32& operator[](s32 index);
};

Vec4V_Out RECON_VEC_CALLCONV Vec4VInt(s32 intVal);
Vec4V_Out RECON_VEC_CALLCONV Vec4VInt(s32 intX, s32 intY, s32 intZ, s32 intW);

template<s32 constantVal>
Vec4V_Out RECON_VEC_CALLCONV Vec4VConstant();

template<s32 constantX, s32 constantY>
Vec4V_Out RECON_VEC_CALLCONV Vec4VConstant();

template<s32 constantX, s32 constantY, s32 constantZ>
Vec4V_Out RECON_VEC_CALLCONV Vec4VConstant();

template<s32 constantX, s32 constantY, s32 constantZ, s32 constantW>
Vec4V_Out RECON_VEC_CALLCONV Vec4VConstant();


ScalarV_Out RECON_VEC_CALLCONV Dot(Vec4V_In lhs, Vec4V_In rhs);

ScalarV_Out RECON_VEC_CALLCONV Mag(Vec4V_In vVector);
ScalarV_Out RECON_VEC_CALLCONV Length(Vec4V_In vVector);
ScalarV_Out RECON_VEC_CALLCONV MagSq(Vec4V_In vVector);
ScalarV_Out RECON_VEC_CALLCONV LengthSq(Vec4V_In vVector);

Vec4V_Out RECON_VEC_CALLCONV Normalize(Vec4V_In vVector);
Vec4V_Out RECON_VEC_CALLCONV Cross(Vec4V_In vVectorA, Vec4V_In vVectorB);

#include "Vec4V.inl"

#endif // RECON_SSE_VERSION

#endif // VEC4V_H