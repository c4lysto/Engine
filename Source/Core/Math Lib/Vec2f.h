#ifndef VEC2F_H
#define VEC2F_H

#include "MathDeclarations.h"

class Vec2f;

typedef Vec2f& Vec2f_Ref;
typedef const Vec2f& Vec2f_ConstRef;

typedef Vec2f_ConstRef Vec2f_In;
typedef Vec2f_Ref Vec2f_InOut;

typedef Vec2f Vec2f_Out;

// Other Vec2f Aliases
typedef Vec2f float2;

class Vec2f
{
#define DEFINE_VEC2_ENUM_VAL_CONSTRUCTOR(enumeration, xVal, yVal)\
	explicit __forceinline Vec2f(enumeration) : x(xVal), y(yVal) {}

#define DEFINE_VEC2_ENUM_CONSTRUCTOR(enumeration, valueToInit)\
	explicit __forceinline Vec2f(enumeration) : x(valueToInit), y(valueToInit){}

#define VEC2_ACCESSOR(retType, funcName, retVal) \
	__forceinline retType funcName() { return retVal; }

#define VEC2_ACCESSOR_CONST(retType, funcName, retVal) \
	__forceinline retType funcName() const { return retVal; }

#define VEC2_MUTATOR(funcName, inType, modifiedVal) \
	__forceinline void funcName(inType rhs) { modifiedVal = rhs; }


private:
	union
	{
		f32 vector[2];

		struct
		{
			f32 x, y;
		};

		struct
		{
			s32 iX, iY;
		};
	};

public:

	Vec2f(){}

#ifdef	DEFINE_VEC2_ENUM_CONSTRUCTOR
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eZeroInitializer, 0.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eOneInitializer, 1.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eTwoInitializer, 2.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eThreeInitializer, 3.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eFourInitializer, 4.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eFiveInitializer, 5.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eSixInitializer, 6.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eSevenInitializer, 7.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eEightInitializer, 8.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNineInitializer, 9.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eTenInitializer, 10.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eQuarterInitializer, 0.25f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eHalfInitializer, 0.5f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(ePIInitializer, PI)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eHalfPIInitializer, PI_OVER_2)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eTwoPIInitializer, TWO_PI)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eFLTMINInitializer, FLT_MIN)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eFLTMAXInitializer, FLT_MAX)

	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegOneInitializer, -1.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegTwoInitializer, -2.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegThreeInitializer, -3.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegFourInitializer, -4.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegFiveInitializer, -5.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegSixInitializer, -6.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegSevenInitializer, -7.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegEightInitializer, -8.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegNineInitializer, -9.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegTenInitializer, -10.0f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegQuarterInitializer, -0.25f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegHalfInitializer, -0.5f)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegPIInitializer, -PI)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegHalfPIInitializer, -PI_OVER_2)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegTwoPIInitializer, -TWO_PI)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegFLTMINInitializer, -FLT_MIN)
	DEFINE_VEC2_ENUM_CONSTRUCTOR(eNegFLTMAXInitializer, -FLT_MAX)

	DEFINE_VEC2_ENUM_VAL_CONSTRUCTOR(eXAxisInitializer, 1.0f, 0.0f)
	DEFINE_VEC2_ENUM_VAL_CONSTRUCTOR(eYAxisInitializer, 0.0f, 1.0f)
#undef DEFINE_VEC2_ENUM_CONSTRUCTOR
#undef DEFINE_VEC2_ENUM_VAL_CONSTRUCTOR
#else
#error "VEC2F ENUM CONSTRUCTORS NOT DEFINED"
#endif //DEFINE_VEC2_ENUM_CONSTRUCTOR

	Vec2f(Vec2f_In vVector);
	Vec2f(Vec2f&& vVector);
	explicit Vec2f(const f32& fVal);
	Vec2f(const f32& fX, const f32& fY);

#if SSE_AVAILABLE
	explicit Vec2f(Vector_In vVector);

#if !RECON_OS_64BIT
	explicit Vec2f(Vector&& vVector);
#endif
#endif

#if defined(VEC2_ACCESSOR) && defined(VEC2_ACCESSOR_CONST)
	VEC2_ACCESSOR_CONST(f32, GetX, x)
	VEC2_ACCESSOR_CONST(f32, GetY, y)
	VEC2_ACCESSOR_CONST(const f32&, GetXRef, x)
	VEC2_ACCESSOR_CONST(const f32&, GetYRef, y)
	VEC2_ACCESSOR_CONST(const f32*, GetVector, vector)

	VEC2_ACCESSOR_CONST(s32, GetXi, iX)
	VEC2_ACCESSOR_CONST(s32, GetYi, iY)
	VEC2_ACCESSOR_CONST(const s32&, GetXiRef, iX)
	VEC2_ACCESSOR_CONST(const s32&, GetYiRef, iY)

	VEC2_ACCESSOR(f32&, GetXRef, x)
	VEC2_ACCESSOR(f32&, GetYRef, y)
	VEC2_ACCESSOR(f32*, GetVector, vector)

	VEC2_ACCESSOR(s32&, GetXiRef, iX)
	VEC2_ACCESSOR(s32&, GetYiRef, iY)
#undef VEC2_ACCESSOR
#undef VEC2_ACCESSOR_CONST
#else
#error VEC2 ACCESSORS NOT DEFINED
#endif

#if defined(VEC2_MUTATOR)
	VEC2_MUTATOR(SetX, const f32&, x)
	VEC2_MUTATOR(SetY, const f32&, y)

	VEC2_MUTATOR(SetXi, const s32&, iX)
	VEC2_MUTATOR(SetYi, const s32&, iY)
#undef VEC2_MUTATOR
#else
#error VEC2 MUTATORS NOT DEFINED
#endif

	Vec2f_Out operator-() const;

	Vec2f_Ref RECON_VEC_CALLCONV operator=(Vec2f_In vVector);
	Vec2f_Ref RECON_VEC_CALLCONV operator=(Vec2f&& vVector);

	Vec2f_Out RECON_VEC_CALLCONV operator+(Vec2f_In vVector) const;
	void RECON_VEC_CALLCONV operator+=(Vec2f_In vVector);

	Vec2f_Out RECON_VEC_CALLCONV operator-(Vec2f_In vVector) const;
	void RECON_VEC_CALLCONV operator-=(Vec2f_In vVector);

	Vec2f_Out RECON_VEC_CALLCONV operator*(const f32& fScalar) const;
	friend Vec2f_Out RECON_VEC_CALLCONV operator*(const f32& fScalar, Vec2f_In vVector);
	void RECON_VEC_CALLCONV operator*=(const f32& fScalar);
	Vec2f_Out RECON_VEC_CALLCONV operator*(Vec2f_In vVector) const;
	void RECON_VEC_CALLCONV operator*=(Vec2f_In vVector);

	Vec2f_Out RECON_VEC_CALLCONV operator/(const f32& fScalar) const;
	void RECON_VEC_CALLCONV operator/=(const f32& fScalar);
	Vec2f_Out RECON_VEC_CALLCONV operator/(Vec2f_In vVector) const;
	void RECON_VEC_CALLCONV operator/=(Vec2f_In vVector);

	bool RECON_VEC_CALLCONV operator==(Vec2f_In vVector);
	bool RECON_VEC_CALLCONV operator!=(Vec2f_In vVector);

	Vec2f_Out RECON_VEC_CALLCONV operator&(Vec2f_In vVector) const;
	void RECON_VEC_CALLCONV operator&=(Vec2f_In vVector);

	Vec2f_Out RECON_VEC_CALLCONV operator|(Vec2f_In vVector) const;
	void RECON_VEC_CALLCONV operator|=(Vec2f_In vVector);

	Vec2f_Out RECON_VEC_CALLCONV operator^(Vec2f_In vVector) const;
	void RECON_VEC_CALLCONV operator^=(Vec2f_In vVector);

	Vec2f_Out operator~() const;

	const f32& operator[](s32 index) const;
	f32& operator[](s32 index);
};

Vec2f_Out RECON_VEC_CALLCONV Vec2fInt(const s32& intVal);
Vec2f_Out RECON_VEC_CALLCONV Vec2fInt(const s32& intX, const s32& intY);

f32 RECON_VEC_CALLCONV Dot(Vec2f_In lhs, Vec2f_In rhs);

f32 RECON_VEC_CALLCONV Mag(Vec2f_In vVector);
f32 RECON_VEC_CALLCONV Length(Vec2f_In vVector);
f32 RECON_VEC_CALLCONV MagSq(Vec2f_In vVector);
f32 RECON_VEC_CALLCONV LengthSq(Vec2f_In vVector);

Vec2f_Out RECON_VEC_CALLCONV Normalize(Vec2f_In vVector);
Vec2f_Out RECON_VEC_CALLCONV Cross(Vec2f_In vVectorA, Vec2f_In vVectorB);

#include "Vec2f.inl"

#endif // VEC2F_H