#ifndef SCALARV_H
#define SCALARV_H

#if SSE_AVAILABLE

class ScalarV;

typedef ScalarV& ScalarV_Ref;
typedef const ScalarV& ScalarV_ConstRef;

#if RECON_OS_64BIT
typedef ScalarV ScalarV_In;
#else
typedef ScalarV_ConstRef ScalarV_In;
#endif

typedef ScalarV ScalarV_Out;

typedef ScalarV_Ref ScalarV_InOut;


class ScalarV
{
#define DEFINE_SCALARV_ENUM_CONSTRUCTOR(enumeration, intRep) \
	explicit __forceinline ScalarV(enumeration) {	row = VectorSetConstant<(u32)intRep>();	}

private:

	Vector row;

public:
	ScalarV(){}
#if !RECON_OS_64BIT
	ScalarV(ScalarV&& vVector);
#endif // !RECON_OS_64BIT
	explicit ScalarV(Vector_In vVector);
	explicit ScalarV(const float& fVal);
	explicit ScalarV(const int& iVal);

#ifdef DEFINE_SCALARV_ENUM_CONSTRUCTOR
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eZeroInitializer,		FloatToIntRep::Zero)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eOneInitializer,		FloatToIntRep::One)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eTwoInitializer,		FloatToIntRep::Two)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eThreeInitializer,		FloatToIntRep::Three)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eFourInitializer,		FloatToIntRep::Four)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eFiveInitializer,		FloatToIntRep::Five)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eSixInitializer,		FloatToIntRep::Six)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eSevenInitializer,		FloatToIntRep::Seven)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eEightInitializer,		FloatToIntRep::Eight)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNineInitializer,		FloatToIntRep::Nine)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eTenInitializer,		FloatToIntRep::Ten)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eQuarterInitializer,	FloatToIntRep::Quarter)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eHalfInitializer,		FloatToIntRep::Half)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(ePIInitializer,			FloatToIntRep::Pi)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eHalfPIInitializer,		FloatToIntRep::Half_Pi)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eTwoPIInitializer,		FloatToIntRep::Two_Pi)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eFLTMINInitializer,		FloatToIntRep::Flt_Min)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eFLTMAXInitializer,		FloatToIntRep::Flt_Max)

	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegOneInitializer,		FloatToIntRep::Neg_One)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegTwoInitializer,		FloatToIntRep::Neg_Two)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegThreeInitializer,	FloatToIntRep::Neg_Three)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegFourInitializer,	FloatToIntRep::Neg_Four)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegFiveInitializer,	FloatToIntRep::Neg_Five)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegSixInitializer,		FloatToIntRep::Neg_Six)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegSevenInitializer,	FloatToIntRep::Neg_Seven)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegEightInitializer,	FloatToIntRep::Neg_Eight)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegNineInitializer,	FloatToIntRep::Neg_Nine)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegTenInitializer,		FloatToIntRep::Neg_Ten)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegQuarterInitializer,	FloatToIntRep::Neg_Quarter)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegHalfInitializer,	FloatToIntRep::Neg_Half)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegPIInitializer,		FloatToIntRep::Neg_Pi)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegHalfPIInitializer,	FloatToIntRep::Neg_Half_Pi)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegTwoPIInitializer,	FloatToIntRep::Neg_Two_Pi)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegFLTMINInitializer,	FloatToIntRep::Neg_Flt_Min)
	DEFINE_SCALARV_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer,	FloatToIntRep::Neg_Flt_Max)
#undef DEFINE_SCALARV_ENUM_CONSTRUCTOR
#endif //DEFINE_SCALARV_ENUM_CONSTRUCTOR

	Vector_Out GetVector() const;

	float GetFloat() const;
	float AsFloat() const;

	int GetInt() const;
	int AsInt() const;

	bool IsValid() const;

	ScalarV_Out operator-() const;

	ScalarV_Ref operator=(ScalarV_In rhs);

	ScalarV_Out operator+(ScalarV_In rhs) const;
	ScalarV_Ref operator+=(ScalarV_In rhs);

	ScalarV_Out operator-(ScalarV_In rhs) const;
	ScalarV_Ref operator-=(ScalarV_In rhs);

	ScalarV_Out operator*(ScalarV_In rhs) const;
	ScalarV_Ref operator*=(ScalarV_In rhs);

	ScalarV_Out operator/(ScalarV_In rhs) const;
	ScalarV_Ref operator/=(ScalarV_In rhs);

	// Logical Operators
	ScalarV_Out operator<<(int nCount) const;
	ScalarV_Ref operator<<=(int nCount);

	ScalarV_Out operator>>(int nCount) const;
	ScalarV_Ref operator>>=(int nCount);

	ScalarV_Out operator&(ScalarV_In rhs) const;
	ScalarV_Ref operator&=(ScalarV_In rhs);

	ScalarV_Out operator|(ScalarV_In rhs) const;
	ScalarV_Ref operator|=(ScalarV_In rhs);

	ScalarV_Out operator~() const;

	ScalarV_Out operator^(ScalarV_In rhs) const;
	ScalarV_Ref operator^=(ScalarV_In rhs);

	// Bit comparison
	bool operator==(ScalarV_In rhs) const;	
	bool operator!=(ScalarV_In rhs) const;

	// Floating Point Comparison
	bool operator<(ScalarV_In rhs) const;
	bool operator<=(ScalarV_In rhs) const;
	bool operator>(ScalarV_In rhs) const;
	bool operator>=(ScalarV_In rhs) const;

	operator bool() const;
};

#include "ScalarV.inl"

#endif // SSE_AVAILABLE

#endif // SCALARV_H