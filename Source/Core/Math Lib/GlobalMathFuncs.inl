
template<typename Type>
__forceinline Type Max(Type lhs, Type rhs)
{
	return (lhs > rhs) ? lhs : rhs;
}

template<> __forceinline s8 Max(s8 lhs, s8 rhs) \
{ \
	s8 diff = lhs - rhs; \
	return lhs - (diff & (diff >> 7)); \
}

template<> __forceinline s16 Max(s16 lhs, s16 rhs) \
{ \
	s16 diff = lhs - rhs; \
	return lhs - (diff & (diff >> 15)); \
}

template<> __forceinline s32 Max(s32 lhs, s32 rhs) \
{ \
	s32 diff = lhs - rhs; \
	return lhs - (diff & (diff >> 31)); \
}

template<> __forceinline s64 Max(s64 lhs, s64 rhs) \
{ \
	s64 diff = lhs - rhs; \
	return lhs - (diff & (diff >> 63)); \
}

template<typename Type>
__forceinline Type Min(Type lhs, Type rhs)
{
	return (lhs < rhs) ? lhs : rhs;
}

template<> __forceinline s8 Min(s8 lhs, s8 rhs) \
{ \
	s8 diff = lhs - rhs; \
	return rhs + (diff & (diff >> 7)); \
}

template<> __forceinline s16 Min(s16 lhs, s16 rhs) \
{ \
	s16 diff = lhs - rhs; \
	return rhs + (diff & (diff >> 15)); \
}

template<> __forceinline s32 Min(s32 lhs, s32 rhs) \
{ \
	s32 diff = lhs - rhs; \
	return rhs + (diff & (diff >> 31)); \
}

template<> __forceinline s64 Min(s64 lhs, s64 rhs) \
{ \
	s64 diff = lhs - rhs; \
	return rhs + (diff & (diff >> 63)); \
}

template<typename Type>
__forceinline Type Clamp(Type val, Type minVal, Type maxVal)
{
	return Max(Min(val, maxVal), minVal);
}

template<typename Type>
__forceinline Type Saturate(Type val)
{
	return Clamp(val, Type(0.0f), Type(1.0f));
}

__forceinline float Lerp(const float& lhs, const float& rhs, const float& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline double Lerp(const double& lhs, const double& rhs, const double& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline Vec2f_Out Lerp(Vec2f_In lhs, Vec2f_In rhs, const float& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline Vec3f_Out Lerp(Vec3f_In lhs, Vec3f_In rhs, const float& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline Vec4f_Out Lerp(Vec4f_In lhs, Vec4f_In rhs, const float& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline s8 Abs(const s8& iScalar)
{
	s8 s = iScalar >> 7;
	return (iScalar ^ s) - s;
}

__forceinline s16 Abs(const s16& iScalar)
{
	s16 s = iScalar >> 15;
	return (iScalar ^ s) - s;
}

__forceinline s32 Abs(const s32& iScalar)
{
	s32 s = iScalar >> 31;
	return (iScalar ^ s) - s;
}

__forceinline s64 Abs(const s64& iScalar)
{
	s64 s = iScalar >> 63;
	return (iScalar ^ s) - s;
}

__forceinline float Abs(const float& fScalar)
{
	return abs(fScalar);
}

__forceinline double Abs(const double& fScalar)
{
	return abs(fScalar);
}

__forceinline Vec2f_Out Abs(Vec2f_In vVector)
{
	return Vec2f(Abs(vVector.GetXRef()), Abs(vVector.GetYRef()));
}

__forceinline Vec3f_Out Abs(Vec3f_In vVector)
{
	return Vec3f(Abs(vVector.GetXRef()), Abs(vVector.GetYRef()), Abs(vVector.GetZRef()));
}

__forceinline Vec4f_Out Abs(Vec4f_In vVector)
{
	return Vec4f(Abs(vVector.GetXRef()), Abs(vVector.GetYRef()), Abs(vVector.GetZRef()), Abs(vVector.GetWRef()));
}

__forceinline float Sqrt(const float& fScalar)
{
	return sqrtf(fScalar);
}

__forceinline double Sqrt(const double& fScalar)
{
	return sqrt(fScalar);
}

__forceinline Vec2f_Out Sqrt(Vec2f_In vVector)
{
	return Vec2f(Sqrt(vVector.GetXRef()), Sqrt(vVector.GetYRef()));
}

__forceinline Vec3f_Out Sqrt(Vec3f_In vVector)
{
	return Vec3f(Sqrt(vVector.GetXRef()), Sqrt(vVector.GetYRef()), Sqrt(vVector.GetZRef()));
}

__forceinline Vec4f_Out Sqrt(Vec4f_In vVector)
{
	return Vec4f(Sqrt(vVector.GetXRef()), Sqrt(vVector.GetYRef()), Sqrt(vVector.GetZRef()), Sqrt(vVector.GetWRef()));
}

__forceinline float SqrtSafe(const float& fScalar, const float& safeVal /*= 0.0f*/)
{
	return fScalar != 0.0f ? Sqrt(fScalar) : safeVal;
}

__forceinline double SqrtSafe(const double& fScalar, const double& safeVal /*= 0.0*/)
{
	return fScalar != 0.0 ? Sqrt(fScalar) : safeVal;
}

__forceinline Vec2f_Out SqrtSafe(Vec2f_In vVector, Vec2f_In vSafeVec /*= Vec2f(I_ZERO)*/)
{
	return Vec2f(SqrtSafe(vVector.GetXRef(), vSafeVec.GetXRef()), \
				 SqrtSafe(vVector.GetYRef(), vSafeVec.GetYRef()));
}

__forceinline Vec3f_Out SqrtSafe(Vec3f_In vVector, Vec3f_In vSafeVec /*= Vec3f(I_ZERO)*/)
{
	return Vec3f(SqrtSafe(vVector.GetXRef(), vSafeVec.GetXRef()), \
				 SqrtSafe(vVector.GetYRef(), vSafeVec.GetYRef()), \
				 SqrtSafe(vVector.GetZRef(), vSafeVec.GetZRef()));
}

__forceinline Vec4f_Out SqrtSafe(Vec4f_In vVector, Vec4f_In vSafeVec /*= Vec4f(I_ZERO)*/)
{
	return Vec4f(SqrtSafe(vVector.GetXRef(), vSafeVec.GetXRef()), \
				 SqrtSafe(vVector.GetYRef(), vSafeVec.GetYRef()), \
				 SqrtSafe(vVector.GetZRef(), vSafeVec.GetZRef()), \
				 SqrtSafe(vVector.GetWRef(), vSafeVec.GetWRef()));
}

template<VecElem splat>
__forceinline Vec2f_Out Splat(Vec2f_In lhs)
{
	return Permute<splat, splat>(lhs);
}

template<VecElem splat>
__forceinline Vec3f_Out Splat(Vec3f_In lhs)
{
	return Permute<splat, splat, splat>(lhs);
}

template<VecElem splat>
__forceinline Vec4f_Out Splat(Vec4f_In lhs)
{
	return Permute<splat, splat, splat, splat>(lhs);
}

template<VecElem pX, VecElem pY>
__forceinline Vec2f_Out Permute(Vec2f_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::Y) &&
						(pY >= VecElem::X && pY <= VecElem::Y), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec2f(lhs[(int)pX], lhs[(int)pY]);
}

template<VecElem pX, VecElem pY, VecElem pZ>
__forceinline Vec3f_Out Permute(Vec3f_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::Z) &&
						(pY >= VecElem::X && pY <= VecElem::Z) &&
						(pZ >= VecElem::X && pY <= VecElem::Z), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Z!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y && pZ == VecElem::Z), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec3f(lhs[(int)pX], lhs[(int)pY], lhs[(int)pZ]);
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> 
__forceinline Vec4f_Out Permute(Vec4f_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::W) &&
						(pY >= VecElem::X && pY <= VecElem::W) &&
						(pZ >= VecElem::X && pY <= VecElem::W) &&
						(pW >= VecElem::X && pY <= VecElem::W), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::W!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y && pZ == VecElem::Z && pW == VecElem::W), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec4f(lhs[(int)pX], lhs[(int)pY], lhs[(int)pZ], lhs[(int)pW]);
}

template<VecElem pX, VecElem pY>
__forceinline Vec2f_Out Permute(Vec2f_In lhs, Vec2f_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::Y1) || (pX >= VecElem::X2 && pX <= VecElem::Y2)) &&
						((pY >= VecElem::X1 && pY <= VecElem::Y1) || (pY >= VecElem::X2 && pY <= VecElem::Y2)), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1) || 
						  (pX == VecElem::X2 && pY == VecElem::Y2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	const float* vectors[] = {lhs.GetVector(), rhs.GetVector()};
	return Vec2f(vectors[(int)pX>>4][(int)pX&0x3], vectors[(int)pY>>4][(int)pY&0x3]);
}

template<VecElem pX, VecElem pY, VecElem pZ>
__forceinline Vec3f_Out Permute(Vec3f_In lhs, Vec3f_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::Z1) || (pX >= VecElem::X2 && pX <= VecElem::Z2)) &&
						((pY >= VecElem::X1 && pY <= VecElem::Z1) || (pY >= VecElem::X2 && pY <= VecElem::Z2)) &&
						((pZ >= VecElem::X1 && pZ <= VecElem::Z1) || (pZ >= VecElem::X2 && pZ <= VecElem::Z2)), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1 && pZ == VecElem::Z1) || 
						  (pX == VecElem::X2 && pY == VecElem::Y2 && pZ == VecElem::Z2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	const float* vectors[] = {lhs.GetVector(), rhs.GetVector()};
	return Vec3f(vectors[(int)pX>>4][(int)pX&0x3], vectors[(int)pY>>4][(int)pY&0x3], vectors[(int)pZ>>4][(int)pZ&0x3]);
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> 
__forceinline Vec4f_Out Permute(Vec4f_In lhs, Vec4f_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::W1) || (pX >= VecElem::X2 && pX <= VecElem::W2)) &&
						((pY >= VecElem::X1 && pY <= VecElem::W1) || (pY >= VecElem::X2 && pY <= VecElem::W2)) &&
						((pZ >= VecElem::X1 && pZ <= VecElem::W1) || (pZ >= VecElem::X2 && pZ <= VecElem::W2)) &&
						((pW >= VecElem::X1 && pW <= VecElem::W1) || (pW >= VecElem::X2 && pW <= VecElem::W2)), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1 && pZ == VecElem::Z1 && pW == VecElem::W1) || 
						  (pX == VecElem::X2 && pY == VecElem::Y2 && pZ == VecElem::Z2 && pW == VecElem::W2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	const float* vectors[] = {lhs.GetVector(), rhs.GetVector()};
	return Vec4f(vectors[(int)pX>>4][(int)pX&0x3], vectors[(int)pY>>4][(int)pY&0x3], vectors[(int)pZ>>4][(int)pZ&0x3], vectors[(int)pW>>4][(int)pW&0x3]);
}

__forceinline s32 SignMask(Vec2f_In vVector)
{
	return s32(((vVector.GetXiRef() & BIT31) << (s32)VecElem::X) | \
			   ((vVector.GetYiRef() & BIT31) << (s32)VecElem::Y));
}

__forceinline s32 SignMask(Vec3f_In vVector)
{
	return s32(((vVector.GetXiRef() & BIT31) << (s32)VecElem::X) | \
			   ((vVector.GetYiRef() & BIT31) << (s32)VecElem::Y) | \
			   ((vVector.GetZiRef() & BIT31) << (s32)VecElem::Z));
}

__forceinline s32 SignMask(Vec4f_In vVector)
{
	return s32(((vVector.GetXiRef() & BIT31) << (s32)VecElem::X) | \
			   ((vVector.GetYiRef() & BIT31) << (s32)VecElem::Y) | \
			   ((vVector.GetZiRef() & BIT31) << (s32)VecElem::Z) | \
			   ((vVector.GetWiRef() & BIT31) << (s32)VecElem::W));
}

__forceinline Vec2f_Out SelectTF(Vec2f_In lhs, Vec2f_In rhs, Vec2f_In condition)
{
	return Vec2f((condition.GetXiRef() & BIT31) ? lhs.GetXRef() : rhs.GetXRef(),
				 (condition.GetYiRef() & BIT31) ? lhs.GetYRef() : rhs.GetYRef());
}

__forceinline Vec3f_Out SelectTF(Vec3f_In lhs, Vec3f_In rhs, Vec3f_In condition)
{
	return Vec3f((condition.GetXiRef() & BIT31) ? lhs.GetXRef() : rhs.GetXRef(),
				 (condition.GetYiRef() & BIT31) ? lhs.GetYRef() : rhs.GetYRef(),
				 (condition.GetZiRef() & BIT31) ? lhs.GetZRef() : rhs.GetZRef());
}

__forceinline Vec4f_Out SelectTF(Vec4f_In lhs, Vec4f_In rhs, Vec4f_In condition)
{
	return Vec4f((condition.GetXiRef() & BIT31) ? lhs.GetXRef() : rhs.GetXRef(),
				 (condition.GetYiRef() & BIT31) ? lhs.GetYRef() : rhs.GetYRef(),
				 (condition.GetZiRef() & BIT31) ? lhs.GetZRef() : rhs.GetZRef(),
				 (condition.GetWiRef() & BIT31) ? lhs.GetWRef() : rhs.GetWRef());
}

__forceinline float Sin(const float& fRadians)
{
	return sinf(fRadians);
}

__forceinline double Sin(const double& fRadians)
{
	return sin(fRadians);
}

__forceinline Vec2f_Out Sin(Vec2f_In vRadians)
{
	return Vec2f(Sin(vRadians.GetXRef()), Sin(vRadians.GetYRef()));
}

__forceinline Vec3f_Out Sin(Vec3f_In vRadians)
{
	return Vec3f(Sin(vRadians.GetXRef()), Sin(vRadians.GetYRef()), Sin(vRadians.GetZRef()));
}

__forceinline Vec4f_Out Sin(Vec4f_In vRadians)
{
	return Vec4f(Sin(vRadians.GetXRef()), Sin(vRadians.GetYRef()), Sin(vRadians.GetZRef()), Sin(vRadians.GetWRef()));
}

__forceinline float ASin(const float& fRadians)
{
	return asinf(fRadians);
}

__forceinline double ASin(const double& fRadians)
{
	return asin(fRadians);
}

__forceinline Vec2f_Out ASin(Vec2f_In vRadians)
{
	return Vec2f(ASin(vRadians.GetXRef()), ASin(vRadians.GetYRef()));
}

__forceinline Vec3f_Out ASin(Vec3f_In vRadians)
{
	return Vec3f(ASin(vRadians.GetXRef()), ASin(vRadians.GetYRef()), ASin(vRadians.GetZRef()));
}

__forceinline Vec4f_Out ASin(Vec4f_In vRadians)
{
	return Vec4f(ASin(vRadians.GetXRef()), ASin(vRadians.GetYRef()), ASin(vRadians.GetZRef()), ASin(vRadians.GetWRef()));
}

__forceinline float Cos(const float& fRadians)
{
	return cosf(fRadians);
}

__forceinline double Cos(const double& fRadians)
{
	return cos(fRadians);
}

__forceinline Vec2f_Out Cos(Vec2f_In vRadians)
{
	return Vec2f(Cos(vRadians.GetXRef()), Cos(vRadians.GetYRef()));
}

__forceinline Vec3f_Out Cos(Vec3f_In vRadians)
{
	return Vec3f(Cos(vRadians.GetXRef()), Cos(vRadians.GetYRef()), Cos(vRadians.GetZRef()));
}

__forceinline Vec4f_Out Cos(Vec4f_In vRadians)
{
	return Vec4f(Cos(vRadians.GetXRef()), Cos(vRadians.GetYRef()), Cos(vRadians.GetZRef()), Cos(vRadians.GetWRef()));
}

__forceinline float ACos(const float& fRadians)
{
	return acosf(fRadians);
}

__forceinline double ACos(const double& fRadians)
{
	return acos(fRadians);
}

__forceinline Vec2f_Out ACos(Vec2f_In vRadians)
{
	return Vec2f(ACos(vRadians.GetXRef()), ACos(vRadians.GetYRef()));
}

__forceinline Vec3f_Out ACos(Vec3f_In vRadians)
{
	return Vec3f(ACos(vRadians.GetXRef()), ACos(vRadians.GetYRef()), ACos(vRadians.GetZRef()));
}

__forceinline Vec4f_Out ACos(Vec4f_In vRadians)
{
	return Vec4f(ACos(vRadians.GetXRef()), ACos(vRadians.GetYRef()), ACos(vRadians.GetZRef()), ACos(vRadians.GetWRef()));
}

__forceinline float Tan(const float& fRadians)
{
	return tanf(fRadians);
}

__forceinline double Tan(const double& fRadians)
{
	return tan(fRadians);
}

__forceinline Vec2f_Out Tan(Vec2f_In vRadians)
{
	return Vec2f(Tan(vRadians.GetXRef()), Tan(vRadians.GetYRef()));
}

__forceinline Vec3f_Out Tan(Vec3f_In vRadians)
{
	return Vec3f(Tan(vRadians.GetXRef()), Tan(vRadians.GetYRef()), Tan(vRadians.GetZRef()));
}

__forceinline Vec4f_Out Tan(Vec4f_In vRadians)
{
	return Vec4f(Tan(vRadians.GetXRef()), Tan(vRadians.GetYRef()), Tan(vRadians.GetZRef()), Tan(vRadians.GetWRef()));
}

__forceinline float ATan(const float& fRadians)
{
	return atanf(fRadians);
}

__forceinline double ATan(const double& fRadians)
{
	return atan(fRadians);
}

__forceinline Vec2f_Out ATan(Vec2f_In vRadians)
{
	return Vec2f(ATan(vRadians.GetXRef()), ATan(vRadians.GetYRef()));
}

__forceinline Vec3f_Out ATan(Vec3f_In vRadians)
{
	return Vec3f(ATan(vRadians.GetXRef()), ATan(vRadians.GetYRef()), ATan(vRadians.GetZRef()));
}

__forceinline Vec4f_Out ATan(Vec4f_In vRadians)
{
	return Vec4f(ATan(vRadians.GetXRef()), ATan(vRadians.GetYRef()), ATan(vRadians.GetZRef()), ATan(vRadians.GetWRef()));
}

// Returns: Vec2f(Sin(), Cos());
__forceinline Vec2f_Out SinCos(const float& fRadians)
{
	return Vec2f(Sin(fRadians), Cos(fRadians));
}


// Comparison Funcs

#define VEC_CMP_MAKE_MASK_1  ((vecResult.GetXRef() != 0.0f) << 0)

#define VEC_CMP_MAKE_MASK_2 VEC_CMP_MAKE_MASK_1 | ((vecResult.GetYRef() != 0) << 1)

#define VEC_CMP_MAKE_MASK_3 VEC_CMP_MAKE_MASK_2 | ((vecResult.GetZRef() != 0) << 2)

#define VEC_CMP_MAKE_MASK_4 VEC_CMP_MAKE_MASK_3 | ((vecResult.GetWRef() != 0) << 3)

#define VEC_CMP_2(cmp) \
	lhs.GetXRef() cmp rhs.GetXRef(), \
	lhs.GetYRef() cmp rhs.GetYRef()

#define VEC_CMP_3(cmp) \
	VEC_CMP_2(cmp) \
	, lhs.GetZRef() cmp rhs.GetZRef()

#define VEC_CMP_4(cmp) \
	VEC_CMP_3(cmp) \
	, lhs.GetWRef() cmp rhs.GetWRef()

#define VEC_CMP_DEFBASE(name, varType, cmpDef)	\
	__forceinline VecCmpResult name(varType##_In lhs, varType##_In rhs) \
{ \
	return VecCmpResult(cmpDef); \
}

#define VEC_CMP_DEF(name, amt, nameExt, varType) \
	__forceinline bool name##nameExt(varType##_In lhs, varType##_In rhs) \
{ \
	return VecCmpResult(name(lhs, rhs)) == CMP_MASK_##nameExt; \
}

#define VEC_CMP_DEF1(name, varType) VEC_CMP_DEF( name, 1, X, varType)
#define VEC_CMP_DEF2(name, varType) VEC_CMP_DEF( name, 2, XY, varType)
#define VEC_CMP_DEF3(name, varType) VEC_CMP_DEF( name, 3, XYZ, varType)
#define VEC_CMP_DEF4(name, varType) VEC_CMP_DEF( name, 4, XYZW, varType)

#define VEC_CMP_DEF_VEC2(name, cmp, varType)  \
	VEC_CMP_DEFBASE(name, varType, VEC_CMP_2(cmp)) \
	VEC_CMP_DEF1(name, varType) \
	VEC_CMP_DEF2(name, varType)

#define VEC_CMP_DEF_VEC3(name, cmp, varType)  \
	VEC_CMP_DEFBASE(name, varType, VEC_CMP_3(cmp)) \
	VEC_CMP_DEF1(name, varType) \
	VEC_CMP_DEF2(name, varType) \
	VEC_CMP_DEF3(name, varType)

#define VEC_CMP_DEF_VEC4(name, cmp, varType)  \
	VEC_CMP_DEFBASE(name, varType, VEC_CMP_4(cmp)) \
	VEC_CMP_DEF1(name, varType) \
	VEC_CMP_DEF2(name, varType) \
	VEC_CMP_DEF3(name, varType) \
	VEC_CMP_DEF4(name, varType)

VEC_CMP_DEF_VEC2(IsEqual, == , Vec2f)
VEC_CMP_DEF_VEC3(IsEqual, == , Vec3f)
VEC_CMP_DEF_VEC4(IsEqual, == , Vec4f)

VEC_CMP_DEF_VEC2(IsNotEqual, != , Vec2f)
VEC_CMP_DEF_VEC3(IsNotEqual, != , Vec3f)
VEC_CMP_DEF_VEC4(IsNotEqual, != , Vec4f)

VEC_CMP_DEF_VEC2(IsGreaterThan, >, Vec2f)
VEC_CMP_DEF_VEC3(IsGreaterThan, >, Vec3f)
VEC_CMP_DEF_VEC4(IsGreaterThan, >, Vec4f)

VEC_CMP_DEF_VEC2(IsGreaterThanOrEqual, >= , Vec2f)
VEC_CMP_DEF_VEC3(IsGreaterThanOrEqual, >= , Vec3f)
VEC_CMP_DEF_VEC4(IsGreaterThanOrEqual, >= , Vec4f)

VEC_CMP_DEF_VEC2(IsLessThan, <, Vec2f)
VEC_CMP_DEF_VEC3(IsLessThan, <, Vec3f)
VEC_CMP_DEF_VEC4(IsLessThan, <, Vec4f)

VEC_CMP_DEF_VEC2(IsLessThanOrEqual, <= , Vec2f)
VEC_CMP_DEF_VEC3(IsLessThanOrEqual, <= , Vec3f)
VEC_CMP_DEF_VEC4(IsLessThanOrEqual, <= , Vec4f)

#undef VEC_CMP_2
#undef VEC_CMP_3
#undef VEC_CMP_4

#define VEC_CMP_2(cmp) \
	lhs.GetXiRef() cmp rhs.GetXiRef(), \
	lhs.GetYiRef() cmp rhs.GetYiRef()

#define VEC_CMP_3(cmp) \
	VEC_CMP_2(cmp) \
	, lhs.GetZiRef() cmp rhs.GetZiRef()

#define VEC_CMP_4(cmp) \
	VEC_CMP_3(cmp) \
	, lhs.GetWiRef() cmp rhs.GetWiRef()

VEC_CMP_DEF_VEC2(IsEqualInt, == , Vec2f)
VEC_CMP_DEF_VEC3(IsEqualInt, == , Vec3f)
VEC_CMP_DEF_VEC4(IsEqualInt, == , Vec4f)

VEC_CMP_DEF_VEC2(IsNotEqualInt, != , Vec2f)
VEC_CMP_DEF_VEC3(IsNotEqualInt, != , Vec3f)
VEC_CMP_DEF_VEC4(IsNotEqualInt, != , Vec4f)

VEC_CMP_DEF_VEC2(IsGreaterThanInt, >, Vec2f)
VEC_CMP_DEF_VEC3(IsGreaterThanInt, >, Vec3f)
VEC_CMP_DEF_VEC4(IsGreaterThanInt, >, Vec4f)

VEC_CMP_DEF_VEC2(IsGreaterThanOrEqualInt, >= , Vec2f)
VEC_CMP_DEF_VEC3(IsGreaterThanOrEqualInt, >= , Vec3f)
VEC_CMP_DEF_VEC4(IsGreaterThanOrEqualInt, >= , Vec4f)

VEC_CMP_DEF_VEC2(IsLessThanInt, <, Vec2f)
VEC_CMP_DEF_VEC3(IsLessThanInt, <, Vec3f)
VEC_CMP_DEF_VEC4(IsLessThanInt, <, Vec4f)

VEC_CMP_DEF_VEC2(IsLessThanOrEqualInt, <= , Vec2f)
VEC_CMP_DEF_VEC3(IsLessThanOrEqualInt, <= , Vec3f)
VEC_CMP_DEF_VEC4(IsLessThanOrEqualInt, <= , Vec4f)

#undef VEC_CMP_DEF_VEC4
#undef VEC_CMP_DEF_VEC3
#undef VEC_CMP_DEF_VEC2

#undef VEC_CMP_DEF4
#undef VEC_CMP_DEF3
#undef VEC_CMP_DEF2
#undef VEC_CMP_DEF1

#undef VEC_CMP_DEF
#undef VEC_CMP_DEFBASE

#undef VEC_CMP_4
#undef VEC_CMP_3
#undef VEC_CMP_2

#undef VEC_CMP_MAKE_MASK_4
#undef VEC_CMP_MAKE_MASK_3
#undef VEC_CMP_MAKE_MASK_2
#undef VEC_CMP_MAKE_MASK_1

// Arithmetic Operation:

#define VEC_ARITH_OP2(componentType, cmp) \
	lhs.GetX##componentType##Ref() cmp rhs.GetX##componentType##Ref(), \
	lhs.GetY##componentType##Ref() cmp rhs.GetY##componentType##Ref()

#define VEC_ARITH_OP3(componentType, cmp) \
	VEC_ARITH_OP2(componentType, cmp) \
	, lhs.GetZ##componentType##Ref() cmp rhs.GetZ##componentType##Ref()

#define VEC_ARITH_OP4(componentType, cmp) \
	VEC_ARITH_OP3(componentType, cmp) \
	, lhs.GetW##componentType##Ref() cmp rhs.GetW##componentType##Ref()


#define VEC_ARITH_DEF(name, varType, operations) \
	__forceinline varType##_Out name(varType##_In lhs, varType##_In rhs) \
{ \
	return varType(operations); \
}

#define VEC_ARITH_DEF_SIZE(name, cmp, num) \
	VEC_ARITH_DEF(name, Vec##num##f, VEC_ARITH_OP##num(, cmp))

// Floating Point Operations
VEC_ARITH_DEF_SIZE(Add, +, 2)
VEC_ARITH_DEF_SIZE(Add, +, 3)
VEC_ARITH_DEF_SIZE(Add, +, 4)

VEC_ARITH_DEF_SIZE(Subtract, -, 2)
VEC_ARITH_DEF_SIZE(Subtract, -, 3)
VEC_ARITH_DEF_SIZE(Subtract, -, 4)

VEC_ARITH_DEF_SIZE(Multiply, *, 2)
VEC_ARITH_DEF_SIZE(Multiply, *, 3)
VEC_ARITH_DEF_SIZE(Multiply, *, 4)

VEC_ARITH_DEF_SIZE(Divide, / , 2)
VEC_ARITH_DEF_SIZE(Divide, / , 3)
VEC_ARITH_DEF_SIZE(Divide, / , 4)


#undef	VEC_ARITH_DEF
#define VEC_ARITH_DEF(name, varType, operations) \
	__forceinline varType##_Out name(varType##_In lhs, varType##_In rhs) \
{ \
	return varType##Int(operations); \
}

#undef	VEC_ARITH_DEF_SIZE
#define	VEC_ARITH_DEF_SIZE(name, cmp, num) \
	VEC_ARITH_DEF(name, Vec##num##f, VEC_ARITH_OP##num(i, cmp))


// Integer Operations
VEC_ARITH_DEF_SIZE(AddInt, +, 2)
VEC_ARITH_DEF_SIZE(AddInt, +, 3)
VEC_ARITH_DEF_SIZE(AddInt, +, 4)

VEC_ARITH_DEF_SIZE(SubtractInt, -, 2)
VEC_ARITH_DEF_SIZE(SubtractInt, -, 3)
VEC_ARITH_DEF_SIZE(SubtractInt, -, 4)

VEC_ARITH_DEF_SIZE(MultiplyInt, *, 2)
VEC_ARITH_DEF_SIZE(MultiplyInt, *, 3)
VEC_ARITH_DEF_SIZE(MultiplyInt, *, 4)

VEC_ARITH_DEF_SIZE(DivideInt, / , 2)
VEC_ARITH_DEF_SIZE(DivideInt, / , 3)
VEC_ARITH_DEF_SIZE(DivideInt, / , 4)


__forceinline float Dot(Vec2f_In vVectorA, Vec2f_In vVectorB)
{
	return (vVectorA.x * vVectorB.x) + (vVectorA.y * vVectorB.y);
}

__forceinline float Dot(Vec3f_In vVectorA, Vec3f_In vVectorB)
{
	return (vVectorA.x * vVectorB.x) + (vVectorA.y * vVectorB.y) + (vVectorA.z * vVectorB.z);
}

__forceinline float Dot(Vec4f_In vVectorA, Vec4f_In vVectorB)
{
#if SSE_AVAILABLE
	Vector vec1 = VectorLoadU(vVectorA.GetVector());
	Vector vec2 = VectorLoadU(vVectorB.GetVector());
	vec1 = VectorMultiply(vec1, vec2);
	vec1 = VectorHAdd(vec1, vec1);
	return VectorExtractFloat<VecElem::X>(VectorHAdd(vec1, vec1));
#else
	return (vVectorA.x * vVectorB.x) + (vVectorA.y * vVectorB.y) + (vVectorA.z * vVectorB.z) + (vVectorA.w * vVectorB.w);
#endif
}

__forceinline float Mag(Vec2f_In vVector)
{
	return sqrtf(MagSq(vVector));
}

__forceinline float Mag(Vec3f_In vVector)
{
	return sqrtf(MagSq(vVector));
}

__forceinline float Mag(Vec4f_In vVector)
{
#if SSE_AVAILABLE
	Vector vec = VectorLoadU(vVector.GetVector());
	Vector magSq = VectorMultiply(vec, vec);
	magSq = VectorHAdd(magSq, magSq);
	magSq = VectorHAdd(magSq, magSq);
	return VectorExtractFloat<VecElem::X>(VectorSqrt(magSq));
#else
	return sqrtf(MagSq());
#endif
}

__forceinline float Length(Vec2f_In vVector)
{
	return Mag(vVector);
}

__forceinline float Length(Vec3f_In vVector)
{
	return Mag(vVector);
}

__forceinline float Length(Vec4f_In vVector)
{
	return Mag(vVector);
}

__forceinline float MagSq(Vec2f_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline float MagSq(Vec3f_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline float MagSq(Vec4f_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline float LengthSq(Vec2f_In vVector)
{
	return MagSq(vVector);
}

__forceinline float LengthSq(Vec3f_In vVector)
{
	return MagSq(vVector);
}

__forceinline float LengthSq(Vec4f_In vVector)
{
	return MagSq(vVector);
}

__forceinline Vec2f_Out Normalize(Vec2f_In vVector)
{
	float mag = Mag(vVector);
	if(mag)
	{
		mag = 1 / mag;

		return vVector * mag;
	}
	return vVector;
}

__forceinline Vec3f_Out Normalize(Vec3f_In vVector)
{
	float mag = Mag(vVector);

	// protection against divide by zero
	if(mag)
	{
#if SSE_AVAILABLE
		return Vec3f(VectorDivide(VectorLoadU(vVector.GetVector()), VectorSet(mag, mag, mag, 0.0f)));
#else 
		mag = 1 / mag;

		return vVector * mag;
#endif
	}

	return vVector;
}

__forceinline Vec4f_Out Normalize(Vec4f_In vVector)
{
	float mag = Mag(vVector);
	if(mag)
	{
#if SSE_AVAILABLE
		return Vec4f(VectorDivide(VectorLoadU(vVector.GetVector()), VectorSet(mag)));
#else
		mag = 1 / mag;

		return vVector * mag;
#endif
	}
	return vVector;
}

__forceinline Mat33f_Out Normalize(Mat33f_In mMatrix)
{
	Mat33f tmp(mMatrix);
	tmp.Normalize();
	return tmp;
}

__forceinline Mat44f_Out Normalize(Mat44f_In mMatrix)
{
	Mat44f tmp(mMatrix);
	tmp.Normalize();
	return tmp;
}

__forceinline Vec2f_Out IntToFloat(Vec2f_In vVector)
{
	return Vec2f((float)vVector.GetXiRef(), 
				 (float)vVector.GetYiRef());
}

__forceinline Vec3f_Out IntToFloat(Vec3f_In vVector)
{
	return Vec3f((float)vVector.GetXiRef(), 
				 (float)vVector.GetYiRef(), 
				 (float)vVector.GetZiRef());
}

__forceinline Vec4f_Out IntToFloat(Vec4f_In vVector)
{
	return Vec4f((float)vVector.GetXiRef(), 
				 (float)vVector.GetYiRef(), 
				 (float)vVector.GetZiRef(),
				 (float)vVector.GetWiRef());
}

__forceinline Vec2f_Out FloatToInt(Vec2f_In vVector)
{
	return Vec2fInt((s32)vVector.GetXRef(), (s32)vVector.GetYRef());
}

__forceinline Vec3f_Out FloatToInt(Vec3f_In vVector)
{
	return Vec3fInt((s32)vVector.GetXRef(), (s32)vVector.GetYRef(), (s32)vVector.GetZRef());
}

__forceinline Vec4f_Out FloatToInt(Vec4f_In vVector)
{
	return Vec4fInt((s32)vVector.GetXRef(), (s32)vVector.GetYRef(), (s32)vVector.GetZRef(), (s32)vVector.GetWRef());
}

__forceinline float Floor(const float& fScalar)
{
	return floorf(fScalar);
}

__forceinline double Floor(const double& fScalar)
{
	return floor(fScalar);
}

__forceinline Vec2f_Out Floor(Vec2f_In vVector)
{
	return Vec2f(floorf(vVector.GetXRef()), floorf(vVector.GetYRef()));
}

__forceinline Vec3f_Out Floor(Vec3f_In vVector)
{
	return Vec3f(floorf(vVector.GetXRef()), floorf(vVector.GetYRef()), floorf(vVector.GetZRef()));
}

__forceinline Vec4f_Out Floor(Vec4f_In vVector)
{
	return Vec4f(floorf(vVector.GetXRef()), floorf(vVector.GetYRef()), floorf(vVector.GetZRef()), floorf(vVector.GetWRef()));
}

__forceinline float Ceil(const float& fScalar)
{
	return ceilf(fScalar);
}

__forceinline double Ceil(const double& fScalar)
{
	return ceil(fScalar);
}

__forceinline Vec2f_Out Ceil(Vec2f_In vVector)
{
	return Vec2f(ceilf(vVector.GetXRef()), ceilf(vVector.GetYRef()));
}

__forceinline Vec3f_Out Ceil(Vec3f_In vVector)
{
	return Vec3f(ceilf(vVector.GetXRef()), ceilf(vVector.GetYRef()), ceilf(vVector.GetZRef()));
}

__forceinline Vec4f_Out Ceil(Vec4f_In vVector)
{
	return Vec4f(ceilf(vVector.GetXRef()), ceilf(vVector.GetYRef()), ceilf(vVector.GetZRef()), ceilf(vVector.GetWRef()));
}

__forceinline float Trunc(const float& fScalar)
{
	return float(s64(fScalar));
}

__forceinline double Trunc(const double& fScalar)
{
	return double(s64(fScalar));
}

__forceinline Vec2f_Out Trunc(Vec2f_In vVector)
{
	return Vec2f(Trunc(vVector.GetXRef()), Trunc(vVector.GetYRef()));
}

__forceinline Vec3f_Out Trunc(Vec3f_In vVector)
{
	return Vec3f(Trunc(vVector.GetXRef()), Trunc(vVector.GetYRef()), Trunc(vVector.GetZRef()));
}

__forceinline Vec4f_Out Trunc(Vec4f_In vVector)
{
	return Vec4f(Trunc(vVector.GetXRef()), Trunc(vVector.GetYRef()), Trunc(vVector.GetZRef()), Trunc(vVector.GetWRef()));
}

__forceinline float Round(const float& fScalar)
{
	return Floor(fScalar + 0.5f);
}

__forceinline double Round(const double& fScalar)
{
	return Floor(fScalar + 0.5);
}

__forceinline Vec2f_Out Round(Vec2f& vVector)
{
	return Vec2f(Round(vVector.GetXRef()), Round(vVector.GetYRef()));
}

__forceinline Vec3f_Out Round(Vec3f_In vVector)
{
	return Vec3f(Round(vVector.GetXRef()), Round(vVector.GetYRef()), Round(vVector.GetZRef()));
}

__forceinline Vec4f_Out Round(Vec4f_In vVector)
{
	return Vec4f(Round(vVector.GetXRef()), Round(vVector.GetYRef()), Round(vVector.GetZRef()), Round(vVector.GetWRef()));
}

__forceinline float Log2(const float& fScalar)
{
	Assertf(fScalar > 0.0f, "Log2 - fScalar Cannot Be Less Than Zero!");
	return log2f(fScalar);
}

__forceinline double Log2(const double& fScalar)
{
	Assertf(fScalar > 0.0f, "Log2 - fScalar Cannot Be Less Than Zero!");
	return log2(fScalar);
}

__forceinline Vec2f_Out Log2(Vec2f_In vVector)
{
	return Vec2f(Log2(vVector.GetXRef()), Log2(vVector.GetYRef()));
}

__forceinline Vec3f_Out Log2(Vec3f_In vVector)
{
	return Vec3f(Log2(vVector.GetXRef()), Log2(vVector.GetYRef()), Log2(vVector.GetZRef()));
}

__forceinline Vec4f_Out Log2(Vec4f_In vVector)
{
	return Vec4f(Log2(vVector.GetXRef()), Log2(vVector.GetYRef()), Log2(vVector.GetZRef()), Log2(vVector.GetWRef()));
}

__forceinline Mat44f_Out Lerp(Mat44f_In MatrixA, Mat44f_In MatrixB, const float fLambda)
{
	Mat44f result;
	result.GetXAxisRef().SetXYZ(Lerp(MatrixA.GetXAxis().GetXYZ(), MatrixB.GetXAxis().GetXYZ(), fLambda));
	result.GetYAxisRef().SetXYZ(Lerp(MatrixA.GetYAxis().GetXYZ(), MatrixB.GetYAxis().GetXYZ(), fLambda));
	result.GetZAxisRef().SetXYZ(Lerp(MatrixA.GetZAxis().GetXYZ(), MatrixB.GetZAxis().GetXYZ(), fLambda));
	result.GetWAxisRef().SetXYZ(Lerp(MatrixA.GetWAxis().GetXYZ(), MatrixB.GetWAxis().GetXYZ(), fLambda));
	return result;
}

__forceinline Vec3f_Out Cross(Vec3f_In lhs, Vec3f_In rhs)
{
	return Vec3f(lhs.GetY() * rhs.GetZ() - lhs.GetZ() * rhs.GetY(),
				 lhs.GetZ() * rhs.GetX() - lhs.GetX() * rhs.GetZ(),
				 lhs.GetX() * rhs.GetY() - lhs.GetY() * rhs.GetX());
}

__forceinline Mat44f Mat34ToMat44(Mat34f_In mMatrix)
{
	return Mat44f(Vec4f(mMatrix.GetXAxisRef(), 0.0f), \
				  Vec4f(mMatrix.GetYAxisRef(), 0.0f), \
				  Vec4f(mMatrix.GetZAxisRef(), 0.0f), \
				  Vec4f(mMatrix.GetWAxisRef(), 1.0f));
}

__forceinline Mat34f Mat44ToMat34(Mat44f_In mMatrix)
{
	return Mat34f(mMatrix.GetXAxisRef().GetXYZ(), \
				  mMatrix.GetYAxisRef().GetXYZ(), \
				  mMatrix.GetZAxisRef().GetXYZ(), \
				  mMatrix.GetWAxisRef().GetXYZ());
}

inline Mat44f_Out MatrixInverse(Mat44f_In mMatrix)
{
	/*
	Derived From The Intel Paper At:
	ftp://download.intel.com/design/pentiumiii/sml/24504301.pdf
	*/

	Vec4f_ConstRef xAxis = mMatrix.GetXAxisRef();
	Vec4f_ConstRef yAxis = mMatrix.GetYAxisRef();
	Vec4f_ConstRef zAxis = mMatrix.GetZAxisRef();
	Vec4f_ConstRef wAxis = mMatrix.GetWAxisRef();

	Vec4f minor0, minor1, minor2, minor3;
	Vec4f row0, row1, row2, row3;
	Vec4f tmp1;
	Vec4f det4f;

	tmp1 = Permute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(xAxis, yAxis);
	row1 = Permute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(zAxis, wAxis);
	row0 = Permute<VecElem::X1, VecElem::Z1, VecElem::X2, VecElem::Z2>(tmp1, row1);
	row1 = Permute<VecElem::Y1, VecElem::W1, VecElem::Y2, VecElem::W2>(row1, tmp1);
	tmp1 = Permute<VecElem::Z1, VecElem::W1, VecElem::Z2, VecElem::W2>(xAxis, yAxis);
	row3 = Permute<VecElem::Z1, VecElem::W1, VecElem::Z2, VecElem::W2>(zAxis, wAxis);
	row2 = Permute<VecElem::X1, VecElem::Z1, VecElem::X2, VecElem::Z2>(tmp1, row3);
	row3 = Permute<VecElem::Y1, VecElem::W1, VecElem::Y2, VecElem::W2>(row3, tmp1);
	tmp1 = row2 * row3;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor0 = row1 * tmp1;
	minor1 = row0 * tmp1;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor0 = (row1 * tmp1) - minor0;
	minor1 = (row0 * tmp1) - minor1;
	minor1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(minor1);
	tmp1 = row1 * row2;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor0 = (row3 * tmp1) + minor0;
	minor3 = row0 * tmp1;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor0 = minor0 - (row3 * tmp1);
	minor3 = (row0 * tmp1) - minor3;
	minor3 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(minor3);
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(row1) * row3;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	row2 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(row2);
	minor0 = (row2 * tmp1) + minor0;
	minor2 = row0 * tmp1;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor0 = minor0 - (row2 * tmp1);
	minor2 = (row0 * tmp1) - minor2;
	minor2 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(minor2);
	tmp1 = row0 * row1;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor2 = (row3 * tmp1) + minor2;
	minor3 = (row2 * tmp1) - minor3;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor2 = (row3 * tmp1) - minor2;
	minor3 = minor3 - (row2 * tmp1);
	tmp1 = row0 * row3;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor1 = minor1 - (row2 * tmp1);
	minor2 = (row1 * tmp1) + minor2;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor1 = (row2 * tmp1) + minor1;
	minor2 = minor2 - (row1 * tmp1);
	tmp1 = row0 * row2;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor1 = (row3 * tmp1) + minor1;
	minor3 = minor3 - (row1 * tmp1);
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor1 = minor1 - (row3 * tmp1);
	minor3 = (row1 * tmp1) + minor3;
	det4f = row0 * minor0;
	det4f = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(det4f) + det4f;
	det4f = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(det4f) + det4f;
	Vec4f det4fTmp = Vec4f(I_ONE) / det4f;
	det4f = ((det4fTmp + det4fTmp) - (det4f * (det4fTmp * det4fTmp)));
	const float& det = det4f.GetXRef();
	if (Verifyf(det != 0.0f, "Matrix Inverse - Determinant == 0, Cannot Perform Matrix Inverse!!!"))
	{
		minor0 = det * minor0;
		minor1 = det * minor1;
		minor2 = det * minor2;
		minor3 = det * minor3;

		return Mat44f(minor0, minor1, minor2, minor3);
	}
	return mMatrix;
}

__forceinline Mat33f_Out Transpose(Mat33f_In mMatrix)
{
	Mat33f retVal(mMatrix);
	retVal.Transpose();
	return retVal;
}

__forceinline Mat44f_Out Transpose(Mat44f_In mMatrix)
{
	Mat44f retVal(mMatrix);
	retVal.Transpose();
	return retVal;
}

__forceinline Mat44f_Out Transpose3x3(Mat44f_In mMatrix)
{
	Mat44f retVal(mMatrix);
	retVal.Transpose3x3();
	return retVal;
}

__forceinline Mat44f_Out RotateAround(Vec3f_In origin, Mat44f_In rotatorsMatrix, Mat44f_In rotationMatrix)
{
	Mat44f newMat(rotatorsMatrix);
	newMat.Translate(-origin);
	newMat *= rotationMatrix;
	newMat.Translate(origin);
	return newMat;
}

__forceinline Mat44f_Out MakePerspectiveMatrix(float fFOV, float fAspectRatio, float fNearClip, float fFarClip)
{
	float yScale = 1 / tan(fFOV * 0.5f);
	float xScale = yScale / fAspectRatio;

	return Mat44f(	xScale,		0.0f,	0.0f,												0.0f,
					0.0f,		yScale,	0.0f,												0.0f,
					0.0f,		0.0f,	fFarClip / (fFarClip - fNearClip),					1.0f,
					0.0f,		0.0f,	(-fNearClip * fFarClip) / (fFarClip - fNearClip),	0.0f);
}

__forceinline Mat44f_Out MakeOrthographicMatrix(float fWidth, float fHeight, float fNear, float fFar)
{
	return Mat44f(	2.0f / fWidth,		0.0f,					0.0f,						0.0f,
					0.0f,				2.0f / fHeight,			0.0f,						0.0f,
					0.0f,				0.0f,					1.0f / (fFar - fNear),		0.0f,
					0.0f,				0.0f,					-fNear / (fFar - fNear),	1.0f);
}

__forceinline Mat44f_Out MakeTextureMatrixOffset(u32 unWidth, u32 unHeight)
{
	return Mat44f(0.5f,						0.0f,						0.0f,	0.0f,
				  0.0f,						-0.5f,						0.0f,	0.0f,
				  0.0f,						0.0f,						1.0f,	0.0f,
				  0.5f + (0.5f / unWidth),	0.5f + (0.5f / unHeight),	0.0f,	1.0f);
}

__forceinline float CalculateGaussianWeight(s32 nOffset, float fSigma)
{
	return (1 / sqrt(TWO_PI * (fSigma * fSigma))) * exp(-(nOffset * nOffset) / (2 * (fSigma * fSigma)));
}

// unRadius - Number of Pixels to Blur In a Single Direction Including the Center Pixel
inline void CalculateGaussianWeights(float* pGaussianWeights, u32 unRadius, float fLimit)
{
	u32 i;
	float fCurrWeight;
	float fTotalWeight = 0;
	for(i = 0; i < unRadius; ++i)
	{
		fCurrWeight = CalculateGaussianWeight(i, fLimit);
		fTotalWeight += fCurrWeight;
		pGaussianWeights[i] = fCurrWeight;
	}

	fTotalWeight = fLimit / fTotalWeight;

	// Do the Center one, this also avoids if-checking in the following for loop
	pGaussianWeights[0] *= fTotalWeight;
	for(i = 1; i < unRadius; ++i)
	{
		pGaussianWeights[i] *= fTotalWeight * 0.5f;
	}
}

#if SSE_AVAILABLE
__forceinline ScalarV_Out Lerp(ScalarV_In lhs, ScalarV_In rhs, ScalarV_In vLambda)
{
	return lhs + (rhs - lhs) * vLambda;
}

__forceinline Vec2V_Out Lerp(Vec2V_In lhs, Vec2V_In rhs, ScalarV_In vLambda)
{
	return lhs + (rhs - lhs) * vLambda;
}

__forceinline Vec3V_Out Lerp(Vec3V_In lhs, Vec3V_In rhs, ScalarV_In vLambda)
{
	return lhs + (rhs - lhs) * vLambda;
}

__forceinline Vec4V_Out Lerp(Vec4V_In lhs, Vec4V_In rhs, ScalarV_In vLambda)
{
	return lhs + (rhs - lhs) * vLambda;
}

__forceinline ScalarV_Out Abs(ScalarV_In vScalar)
{
	return ScalarV(VectorAbs(vScalar.GetVector()));
}

__forceinline Vec2V_Out Abs(Vec2V_In vVector)
{
	return Vec2V(VectorAbs(vVector.GetVector()));
}

__forceinline Vec3V_Out Abs(Vec3V_In vVector)
{
	return Vec3V(VectorAbs(vVector.GetVector()));
}

__forceinline Vec4V_Out Abs(Vec4V_In vVector)
{
	return Vec4V(VectorAbs(vVector.GetVector()));
}

template<VecElem splat>
__forceinline Vec2V_Out Splat(Vec2V_In lhs)
{
	return Permute<splat, splat>(lhs);
}

template<VecElem splat>
__forceinline Vec3V_Out Splat(Vec3V_In lhs)
{
	return Permute<splat, splat, splat>(lhs);
}

template<VecElem splat>
__forceinline Vec4V_Out Splat(Vec4V_In lhs)
{
	return Permute<splat, splat, splat, splat>(lhs);
}

template<VecElem pX, VecElem pY>
__forceinline Vec2V_Out Permute(Vec2V_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::Y) &&
						(pY >= VecElem::X && pY <= VecElem::Y), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec2V(VectorPermute<pX, pY, VecElem::Z, VecElem::W>(lhs.GetVector()));
}

template<VecElem pX, VecElem pY, VecElem pZ>
__forceinline Vec3V_Out Permute(Vec3V_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::Z) &&
						(pY >= VecElem::X && pY <= VecElem::Z) &&
						(pZ >= VecElem::X && pY <= VecElem::Z), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Z!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y && pZ == VecElem::Z), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec3V(VectorPermute<pX, pY, pZ, VecElem::W>(lhs.GetVector()));
}
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
__forceinline Vec4V_Out Permute(Vec4V_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::W) &&
						(pY >= VecElem::X && pY <= VecElem::W) &&
						(pZ >= VecElem::X && pY <= VecElem::W) &&
						(pW >= VecElem::X && pY <= VecElem::W), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::W!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y && pZ == VecElem::Z && pW == VecElem::W), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec4V(VectorPermute<pX, pY, pZ, pW>(lhs.GetVector()));
}

template<VecElem pX, VecElem pY>
__forceinline Vec2V_Out Permute(Vec2V_In lhs, Vec2V_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::Y1) || (pX >= VecElem::X2 && pX <= VecElem::Y2)) &&
						((pY >= VecElem::X1 && pY <= VecElem::Y1) || (pY >= VecElem::X2 && pY <= VecElem::Y2)), "Invalid Permute Indices! Indices must be between VecElem::X1 <-> VecElem::W2!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1) || 
						  (pX == VecElem::X2 && pY == VecElem::Y2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec2V(VectorPermute<pX, pY, VecElem::Z1, VecElem::W1>(lhs.GetVector(), rhs.GetVector()));
}

template<VecElem pX, VecElem pY, VecElem pZ>
__forceinline Vec3V_Out Permute(Vec3V_In lhs, Vec3V_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::Z1) || (pX >= VecElem::X2 && pX <= VecElem::Z2)) &&
						((pY >= VecElem::X1 && pY <= VecElem::Z1) || (pY >= VecElem::X2 && pY <= VecElem::Z2)) &&
						((pZ >= VecElem::X1 && pZ <= VecElem::Z1) || (pZ >= VecElem::X2 && pZ <= VecElem::Z2)), "Invalid Permute Indices! Indices must be between VecElem::X1 <-> VecElem::W2!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1 && pZ == VecElem::Z1) || 
						  (pX == VecElem::X2 && pY == VecElem::Y2 && pZ == VecElem::Z2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec3V(VectorPermute<pX, pY, pZ, VecElem::W1>(lhs.GetVector(), rhs.GetVector()));
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
__forceinline Vec4V_Out Permute(Vec4V_In lhs, Vec4V_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::W1) || (pX >= VecElem::X2 && pX <= VecElem::W2)) &&
						((pY >= VecElem::X1 && pY <= VecElem::W1) || (pY >= VecElem::X2 && pY <= VecElem::W2)) &&
						((pZ >= VecElem::X1 && pZ <= VecElem::W1) || (pZ >= VecElem::X2 && pZ <= VecElem::W2)) &&
						((pW >= VecElem::X1 && pW <= VecElem::W1) || (pW >= VecElem::X2 && pW <= VecElem::W2)), "Invalid Permute Indices! Indices must be between VecElem::X1 <-> VecElem::W2!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1 && pZ == VecElem::Z1 && pW == VecElem::W1) || 
						  (pX == VecElem::X2 && pY == VecElem::Y2 && pZ == VecElem::Z2 && pW == VecElem::W2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec4V(VectorPermute<pX, pY, pZ, pW>(lhs.GetVector(), rhs.GetVector()));
}

__forceinline s32 SignMask(Vec2V_In vVector)
{
	return VectorSignMask(vVector.GetVector()) & 0x3;
}

__forceinline s32 SignMask(Vec3V_In vVector)
{
	return VectorSignMask(vVector.GetVector()) & 0x7;
}

__forceinline s32 SignMask(Vec4V_In vVector)
{
	return VectorSignMask(vVector.GetVector()) & 0xF;
}

__forceinline Vec2V_Out SelectTF(Vec2V_In lhs, Vec2V_In rhs, Vec2V_In condition)
{
	return Vec2V(VectorSelectTF(lhs.GetVector(), rhs.GetVector(), condition.GetVector()));
}

__forceinline Vec3V_Out SelectTF(Vec3V_In lhs, Vec3V_In rhs, Vec3V_In condition)
{
	return Vec3V(VectorSelectTF(lhs.GetVector(), rhs.GetVector(), condition.GetVector()));
}

__forceinline Vec4V_Out SelectTF(Vec4V_In lhs, Vec4V_In rhs, Vec4V_In condition)
{
	return Vec4V(VectorSelectTF(lhs.GetVector(), rhs.GetVector(), condition.GetVector()));
}

template<VecElem elem> 
__forceinline ScalarV_Out ScalarVFromElement(Vector_In vVector)
{
	static_assert(elem >= VecElem::X && elem <= VecElem::W, "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::W!");
	return ScalarV(VectorPermute<elem, elem, elem, elem>(vVector));
}

template<VecElem elem> 
__forceinline ScalarV_Out ScalarVFromElement(Vec2V_In vVector)
{
	return ScalarVFromElement<elem>(vVector.GetVector());
}

template<VecElem elem> 
__forceinline ScalarV_Out ScalarVFromElement(Vec3V_In vVector)
{
	return ScalarVFromElement<elem>(vVector.GetVector());
}

template<VecElem elem> 
__forceinline ScalarV_Out ScalarVFromElement(Vec4V_In vVector)
{
	return ScalarVFromElement<elem>(vVector.GetVector());
}


// Trigonometry Functions:

__forceinline ScalarV_Out Sin(ScalarV_In vRadians)
{
	return ScalarV(VectorSin(vRadians.GetVector()));
}

__forceinline Vec2V_Out Sin(Vec2V_In vRadians)
{
	return Vec2V(VectorSin(vRadians.GetVector()));
}

__forceinline Vec3V_Out Sin(Vec3V_In vRadians)
{
	return Vec3V(VectorSin(vRadians.GetVector()));
}

__forceinline Vec4V_Out Sin(Vec4V_In vRadians)
{
	return Vec4V(VectorSin(vRadians.GetVector()));
}

__forceinline ScalarV_Out ASin(ScalarV_In vRadians)
{
	return ScalarV(VectorASin(vRadians.GetVector()));
}

__forceinline Vec2V_Out ASin(Vec2V_In vRadians)
{
	return Vec2V(VectorASin(vRadians.GetVector()));
}

__forceinline Vec3V_Out ASin(Vec3V_In vRadians)
{
	return Vec3V(VectorASin(vRadians.GetVector()));
}

__forceinline Vec4V_Out ASin(Vec4V_In vRadians)
{
	return Vec4V(VectorASin(vRadians.GetVector()));
}

__forceinline ScalarV_Out Cos(ScalarV_In vRadians)
{
	return ScalarV(VectorCos(vRadians.GetVector()));
}

__forceinline Vec2V_Out Cos(Vec2V_In vRadians)
{
	return Vec2V(VectorCos(vRadians.GetVector()));
}

__forceinline Vec3V_Out Cos(Vec3V_In vRadians)
{
	return Vec3V(VectorCos(vRadians.GetVector()));
}

__forceinline Vec4V_Out Cos(Vec4V_In vRadians)
{
	return Vec4V(VectorCos(vRadians.GetVector()));
}

__forceinline ScalarV_Out ACos(ScalarV_In vRadians)
{
	return ScalarV(VectorACos(vRadians.GetVector()));
}

__forceinline Vec2V_Out ACos(Vec2V_In vRadians)
{
	return Vec2V(VectorACos(vRadians.GetVector()));
}

__forceinline Vec3V_Out ACos(Vec3V_In vRadians)
{
	return Vec3V(VectorACos(vRadians.GetVector()));
}

__forceinline Vec4V_Out ACos(Vec4V_In vRadians)
{
	return Vec4V(VectorACos(vRadians.GetVector()));
}

__forceinline ScalarV_Out Tan(ScalarV_In vRadians)
{
	return ScalarV(VectorTan(vRadians.GetVector()));
}

__forceinline Vec2V_Out Tan(Vec2V_In vRadians)
{
	return Vec2V(VectorTan(vRadians.GetVector()));
}

__forceinline Vec3V_Out Tan(Vec3V_In vRadians)
{
	return Vec3V(VectorTan(vRadians.GetVector()));
}

__forceinline Vec4V_Out Tan(Vec4V_In vRadians)
{
	return Vec4V(VectorTan(vRadians.GetVector()));
}

__forceinline ScalarV_Out ATan(ScalarV_In vRadians)
{
	return ScalarV(VectorATan(vRadians.GetVector()));
}

__forceinline Vec2V_Out ATan(Vec2V_In vRadians)
{
	return Vec2V(VectorATan(vRadians.GetVector()));
}

__forceinline Vec3V_Out ATan(Vec3V_In vRadians)
{
	return Vec3V(VectorATan(vRadians.GetVector()));
}

__forceinline Vec4V_Out ATan(Vec4V_In vRadians)
{
	return Vec4V(VectorATan(vRadians.GetVector()));
}

// Returns: Vec2V(Sin(), Cos(), Sin(), Cos());
__forceinline Vec2V_Out SinCos(ScalarV_In vRadians)
{
	return Vec2V(VectorSinCos(vRadians.GetVector()));
}



// Comparison Functions

#define VEC_CMP_DEFBASE(name, varType)	\
	__forceinline varType##_Out name(varType##_In lhs, varType##_In rhs) \
{ \
	return varType(Vector##name(lhs.GetVector(), rhs.GetVector())); \
}

#define VEC_CMP_DEF(name, nameExt, varType) \
	__forceinline bool name##nameExt(varType##_In lhs, varType##_In rhs) \
{ \
	return Vector##name##nameExt(lhs.GetVector(), rhs.GetVector()); \
}

#define VEC_CMP_DEF1(name, varType) VEC_CMP_DEF(name, X, varType)
#define VEC_CMP_DEF2(name, varType) VEC_CMP_DEF(name, XY, varType)
#define VEC_CMP_DEF3(name, varType) VEC_CMP_DEF(name, XYZ, varType)
#define VEC_CMP_DEF4(name, varType) VEC_CMP_DEF(name, XYZW, varType)

#define VEC_CMP_DEF_VEC2(name, varType) \
	VEC_CMP_DEFBASE(name, varType) \
	VEC_CMP_DEF1(name, varType) \
	VEC_CMP_DEF2(name, varType)

#define VEC_CMP_DEF_VEC3(name, varType) \
	VEC_CMP_DEF_VEC2(name, varType) \
	VEC_CMP_DEF3(name, varType)

#define VEC_CMP_DEF_VEC4(name, varType) \
	VEC_CMP_DEF_VEC3(name, varType) \
	VEC_CMP_DEF4(name, varType)

VEC_CMP_DEF_VEC2(IsEqual, Vec2V)
VEC_CMP_DEF_VEC3(IsEqual, Vec3V)
VEC_CMP_DEF_VEC4(IsEqual, Vec4V)

VEC_CMP_DEF_VEC2(IsNotEqual, Vec2V)
VEC_CMP_DEF_VEC3(IsNotEqual, Vec3V)
VEC_CMP_DEF_VEC4(IsNotEqual, Vec4V)

VEC_CMP_DEF_VEC2(IsGreaterThan, Vec2V)
VEC_CMP_DEF_VEC3(IsGreaterThan, Vec3V)
VEC_CMP_DEF_VEC4(IsGreaterThan, Vec4V)

VEC_CMP_DEF_VEC2(IsGreaterThanOrEqual, Vec2V)
VEC_CMP_DEF_VEC3(IsGreaterThanOrEqual, Vec3V)
VEC_CMP_DEF_VEC4(IsGreaterThanOrEqual, Vec4V)

VEC_CMP_DEF_VEC2(IsLessThan, Vec2V)
VEC_CMP_DEF_VEC3(IsLessThan, Vec3V)
VEC_CMP_DEF_VEC4(IsLessThan, Vec4V)

VEC_CMP_DEF_VEC2(IsLessThanOrEqual, Vec2V)
VEC_CMP_DEF_VEC3(IsLessThanOrEqual, Vec3V)
VEC_CMP_DEF_VEC4(IsLessThanOrEqual, Vec4V)

VEC_CMP_DEF_VEC2(IsEqualInt, Vec2V)
VEC_CMP_DEF_VEC3(IsEqualInt, Vec3V)
VEC_CMP_DEF_VEC4(IsEqualInt, Vec4V)

VEC_CMP_DEF_VEC2(IsNotEqualInt, Vec2V)
VEC_CMP_DEF_VEC3(IsNotEqualInt, Vec3V)
VEC_CMP_DEF_VEC4(IsNotEqualInt, Vec4V)

VEC_CMP_DEF_VEC2(IsGreaterThanInt, Vec2V)
VEC_CMP_DEF_VEC3(IsGreaterThanInt, Vec3V)
VEC_CMP_DEF_VEC4(IsGreaterThanInt, Vec4V)

VEC_CMP_DEF_VEC2(IsGreaterThanOrEqualInt, Vec2V)
VEC_CMP_DEF_VEC3(IsGreaterThanOrEqualInt, Vec3V)
VEC_CMP_DEF_VEC4(IsGreaterThanOrEqualInt, Vec4V)

VEC_CMP_DEF_VEC2(IsLessThanInt, Vec2V)
VEC_CMP_DEF_VEC3(IsLessThanInt, Vec3V)
VEC_CMP_DEF_VEC4(IsLessThanInt, Vec4V)

VEC_CMP_DEF_VEC2(IsLessThanOrEqualInt, Vec2V)
VEC_CMP_DEF_VEC3(IsLessThanOrEqualInt, Vec3V)
VEC_CMP_DEF_VEC4(IsLessThanOrEqualInt, Vec4V)

#undef VEC_CMP_DEF_VEC4
#undef VEC_CMP_DEF_VEC3
#undef VEC_CMP_DEF_VEC2

#undef VEC_CMP_DEF4
#undef VEC_CMP_DEF3
#undef VEC_CMP_DEF2
#undef VEC_CMP_DEF1

#undef VEC_CMP_DEF
#undef VEC_CMP_DEFBASE


// Vector Math Functions

__forceinline ScalarV_Out Sqrt(ScalarV_In vScalar)
{
	return ScalarV(VectorSqrt(vScalar.GetVector()));
}

__forceinline Vec2V_Out Sqrt(Vec2V_In vVector)
{
	return Vec2V(VectorSqrt(vVector.GetVector()));
}

__forceinline Vec3V_Out Sqrt(Vec3V_In vVector)
{
	return Vec3V(VectorSqrt(vVector.GetVector()));
}

__forceinline Vec4V_Out Sqrt(Vec4V_In vVector)
{
	return Vec4V(VectorSqrt(vVector.GetVector()));
}

__forceinline ScalarV_Out SqrtSafe(ScalarV_In vScalar, ScalarV_In safeVec /*= ScalarV(I_ZERO)*/)
{
	Vector NotZeroVecMask = VectorIsNotEqual(vScalar.GetVector(), VectorSet(0.0f));
	Vector sqrtVal = VectorSqrt(vScalar.GetVector());
	return ScalarV(VectorOr(VectorAnd(sqrtVal, NotZeroVecMask), VectorAndNot(safeVec.GetVector(), NotZeroVecMask)));
}

__forceinline Vec2V_Out SqrtSafe(Vec2V_In vVector, Vec2V_In safeVec /*= Vec2V(I_ZERO)*/)
{
	Vector NotZeroVecMask = VectorIsNotEqual(vVector.GetVector(), VectorSet(0.0f));
	Vector sqrtVal = VectorSqrt(vVector.GetVector());
	return Vec2V(VectorOr(VectorAnd(sqrtVal, NotZeroVecMask), VectorAndNot(safeVec.GetVector(), NotZeroVecMask)));
}

__forceinline Vec3V_Out SqrtSafe(Vec3V_In vVector, Vec3V_In safeVec /*= Vec3V(I_ZERO)*/)
{
	Vector NotZeroVecMask = VectorIsNotEqual(vVector.GetVector(), VectorSet(0.0f));
	Vector sqrtVal = VectorSqrt(vVector.GetVector());
	return Vec3V(VectorOr(VectorAnd(sqrtVal, NotZeroVecMask), VectorAndNot(safeVec.GetVector(), NotZeroVecMask)));
}

__forceinline Vec4V_Out SqrtSafe(Vec4V_In vVector, Vec4V_In safeVec /*= Vec4V(I_ZERO)*/)
{
	Vector NotZeroVecMask = VectorIsNotEqual(vVector.GetVector(), VectorSet(0.0f));
	Vector sqrtVal = VectorSqrt(vVector.GetVector());
	return Vec4V(VectorOr(VectorAnd(sqrtVal, NotZeroVecMask), VectorAndNot(safeVec.GetVector(), NotZeroVecMask)));
}


__forceinline ScalarV Dot(Vec2V_In vVectorA, Vec2V_In vVectorB)
{
	Vector tmp = VectorMultiply(vVectorA.GetVector(), vVectorB.GetVector());
	return ScalarVFromElement<VecElem::X>(VectorHAdd(tmp, tmp));
}

__forceinline ScalarV Dot(Vec3V_In vVectorA, Vec3V_In vVectorB)
{
	Vector tmpRhs = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(vVectorB.GetVector(), VectorSet(0.0f));
	Vector tmp = VectorMultiply(vVectorA.GetVector(), tmpRhs);
	tmp = VectorHAdd(tmp, tmp);
	return ScalarVFromElement<VecElem::X>(VectorHAdd(tmp, tmp));
}

__forceinline ScalarV Dot(Vec4V_In vVectorA, Vec4V_In vVectorB)
{
	Vector tmp = VectorMultiply(vVectorA.GetVector(), vVectorB.GetVector());
	tmp = VectorHAdd(tmp, tmp);
	return ScalarVFromElement<VecElem::X>(VectorHAdd(tmp, tmp));
}

__forceinline ScalarV Mag(Vec2V_In vVector)
{
	return Sqrt(MagSq(vVector));
}

__forceinline ScalarV Mag(Vec3V_In vVector)
{
	return Sqrt(MagSq(vVector));
}

__forceinline ScalarV Mag(Vec4V_In vVector)
{
	return Sqrt(MagSq(vVector));
}

__forceinline ScalarV Length(Vec2V_In vVector)
{
	return Sqrt(LengthSq(vVector));
}

__forceinline ScalarV Length(Vec3V_In vVector)
{
	return Sqrt(LengthSq(vVector));
}

__forceinline ScalarV Length(Vec4V_In vVector)
{
	return Sqrt(LengthSq(vVector));
}

__forceinline ScalarV MagSq(Vec2V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV MagSq(Vec3V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV MagSq(Vec4V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV LengthSq(Vec2V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV LengthSq(Vec3V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV LengthSq(Vec4V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline Vec2V_Out Normalize(Vec2V_In vVector)
{
	Vec2V tmp(vVector);
	return tmp.Normalize();
}

__forceinline Vec3V_Out Normalize(Vec3V_In vVector)
{
	Vec3V tmp(vVector);
	return tmp.Normalize();
}

__forceinline Vec4V_Out Normalize(Vec4V_In vVector)
{
	Vec4V tmp(vVector);
	return tmp.Normalize();
}

//__forceinline Mat33V_Out Normalize(Mat33V_In mMatrix)
//{
//	Mat33V tmp(mMatrix);
//	tmp.Normalize();
//	return tmp;
//}

__forceinline Mat44V_Out Normalize(Mat44V_In mMatrix)
{
	Mat44V tmp(mMatrix);
	tmp.Normalize();
	return tmp;
}

__forceinline ScalarV_Out AddInt(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorAddInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out AddInt(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorAddInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec3V_Out AddInt(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorAddInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec4V_Out AddInt(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorAddInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out SubtractInt(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorSubtractInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out SubtractInt(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorSubtractInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec3V_Out SubtractInt(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorSubtractInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec4V_Out SubtractInt(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorSubtractInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out MultiplyInt(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorMultiplyInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out MultiplyInt(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorMultiplyInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec3V_Out MultiplyInt(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorMultiplyInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec4V_Out MultiplyInt(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorMultiplyInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out IntToFloat(ScalarV_In vVector)
{
	return ScalarV(VectorIntToFloat(vVector.GetVector()));
}

__forceinline Vec2V_Out IntToFloat(Vec2V_In vVector)
{
	return Vec2V(VectorIntToFloat(vVector.GetVector()));
}

__forceinline Vec3V_Out IntToFloat(Vec3V_In vVector)
{
	return Vec3V(VectorIntToFloat(vVector.GetVector()));
}

__forceinline Vec4V_Out IntToFloat(Vec4V_In vVector)
{
	return Vec4V(VectorIntToFloat(vVector.GetVector()));
}

__forceinline ScalarV_Out FloatToInt(ScalarV_In vVector)
{
	return ScalarV(VectorFloatToInt(vVector.GetVector()));
}

__forceinline Vec2V_Out FloatToInt(Vec2V_In vVector)
{
	return Vec2V(VectorFloatToInt(vVector.GetVector()));
}

__forceinline Vec3V_Out FloatToInt(Vec3V_In vVector)
{
	return Vec3V(VectorFloatToInt(vVector.GetVector()));
}

__forceinline Vec4V_Out FloatToInt(Vec4V_In vVector)
{
	return Vec4V(VectorFloatToInt(vVector.GetVector()));
}

__forceinline ScalarV_Out Floor(ScalarV_In vVector)
{
	return ScalarV(VectorFloor(vVector.GetVector()));
}

__forceinline Vec2V_Out Floor(Vec2V_In vVector)
{
	return Vec2V(VectorFloor(vVector.GetVector()));
}

__forceinline Vec3V_Out Floor(Vec3V_In vVector)
{
	return Vec3V(VectorFloor(vVector.GetVector()));
}

__forceinline Vec4V_Out Floor(Vec4V_In vVector)
{
	return Vec4V(VectorFloor(vVector.GetVector()));
}

__forceinline ScalarV_Out Ceil(ScalarV_In vVector)
{
	return ScalarV(VectorCeil(vVector.GetVector()));
}

__forceinline Vec2V_Out Ceil(Vec2V_In vVector)
{
	return Vec2V(VectorCeil(vVector.GetVector()));
}

__forceinline Vec3V_Out Ceil(Vec3V_In vVector)
{
	return Vec3V(VectorCeil(vVector.GetVector()));
}

__forceinline Vec4V_Out Ceil(Vec4V_In vVector)
{
	return Vec4V(VectorCeil(vVector.GetVector()));
}

__forceinline ScalarV_Out Trunc(ScalarV_In vVector)
{
	return ScalarV(VectorTrunc(vVector.GetVector()));
}

__forceinline Vec2V_Out Trunc(Vec2V_In vVector)
{
	return Vec2V(VectorTrunc(vVector.GetVector()));
}

__forceinline Vec3V_Out Trunc(Vec3V_In vVector)
{
	return Vec3V(VectorTrunc(vVector.GetVector()));
}

__forceinline Vec4V_Out Trunc(Vec4V_In vVector)
{
	return Vec4V(VectorTrunc(vVector.GetVector()));
}

__forceinline ScalarV_Out Round(ScalarV_In vVector)
{
	return ScalarV(VectorRound(vVector.GetVector()));
}

__forceinline Vec2V_Out Round(Vec2V_In vVector)
{
	return Vec2V(VectorRound(vVector.GetVector()));
}

__forceinline Vec3V_Out Round(Vec3V_In vVector)
{
	return Vec3V(VectorRound(vVector.GetVector()));
}

__forceinline Vec4V_Out Round(Vec4V_In vVector)
{
	return Vec4V(VectorRound(vVector.GetVector()));
}

__forceinline ScalarV_Out Log2(ScalarV_In vScalar)
{
	return ScalarV(VectorLog2(vScalar.GetVector()));
}
__forceinline Vec2V_Out Log2(Vec2V_In vVector)
{
	return Vec2V(VectorLog2(vVector.GetVector()));
}

__forceinline Vec3V_Out Log2(Vec3V_In vVector)
{
	return Vec3V(VectorLog2(vVector.GetVector()));
}

__forceinline Vec4V_Out Log2(Vec4V_In vVector)
{
	return Vec4V(VectorLog2(vVector.GetVector()));
}

inline Mat44V_Out Lerp(Mat44V_In MatrixA, Mat44V_In MatrixB, ScalarV_In vLambda)
{
	Mat44V result;
	result.GetXAxisRef().SetXYZ(Lerp(MatrixA.GetXAxis().GetXYZ(), MatrixB.GetXAxis().GetXYZ(), vLambda));
	result.GetYAxisRef().SetXYZ(Lerp(MatrixA.GetYAxis().GetXYZ(), MatrixB.GetYAxis().GetXYZ(), vLambda));
	result.GetZAxisRef().SetXYZ(Lerp(MatrixA.GetZAxis().GetXYZ(), MatrixB.GetZAxis().GetXYZ(), vLambda));
	result.GetWAxisRef().SetXYZ(Lerp(MatrixA.GetWAxis().GetXYZ(), MatrixB.GetWAxis().GetXYZ(), vLambda));
	return result;
}

__forceinline Vec3V_Out Cross(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorCrossProduct(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Mat44V Mat34ToMat44(Mat34V_In mMatrix)
{
	return Mat44V(Vec4V(mMatrix.GetXAxisRef(), ScalarV(I_ZERO)), \
				  Vec4V(mMatrix.GetYAxisRef(), ScalarV(I_ZERO)), \
				  Vec4V(mMatrix.GetZAxisRef(), ScalarV(I_ZERO)), \
				  Vec4V(mMatrix.GetWAxisRef(), ScalarV(I_ONE)));
}

__forceinline Mat34V Mat44ToMat34(Mat44V_In mMatrix)
{
	return Mat34V(mMatrix.GetXAxisRef().GetXYZ(), \
				  mMatrix.GetYAxisRef().GetXYZ(), \
				  mMatrix.GetZAxisRef().GetXYZ(), \
				  mMatrix.GetWAxisRef().GetXYZ());
}

__forceinline Mat44V_Out MatrixInverse(Mat44V_In mMatrix)
{
	/*
		Derived From The Intel Paper At:
		ftp://download.intel.com/design/pentiumiii/sml/24504301.pdf
	*/

	Vec4V_ConstRef xAxis = mMatrix.GetXAxisRef();
	Vec4V_ConstRef yAxis = mMatrix.GetYAxisRef();
	Vec4V_ConstRef zAxis = mMatrix.GetZAxisRef();
	Vec4V_ConstRef wAxis = mMatrix.GetWAxisRef();

	Vec4V minor0, minor1, minor2, minor3;
	Vec4V row0, row1, row2, row3;
	Vec4V tmp1;
	Vec4V det4V;

	tmp1 = Permute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(xAxis, yAxis);
	row1 = Permute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(zAxis, wAxis);
	row0 = Permute<VecElem::X1, VecElem::Z1, VecElem::X2, VecElem::Z2>(tmp1, row1);
	row1 = Permute<VecElem::Y1, VecElem::W1, VecElem::Y2, VecElem::W2>(row1, tmp1);
	tmp1 = Permute<VecElem::Z1, VecElem::W1, VecElem::Z2, VecElem::W2>(xAxis, yAxis);
	row3 = Permute<VecElem::Z1, VecElem::W1, VecElem::Z2, VecElem::W2>(zAxis, wAxis);
	row2 = Permute<VecElem::X1, VecElem::Z1, VecElem::X2, VecElem::Z2>(tmp1, row3);
	row3 = Permute<VecElem::Y1, VecElem::W1, VecElem::Y2, VecElem::W2>(row3, tmp1);
	tmp1 = row2 * row3;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor0 = row1 * tmp1;
	minor1 = row0 * tmp1;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor0 = (row1 * tmp1) - minor0;
	minor1 = (row0 * tmp1) - minor1;
	minor1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(minor1);
	tmp1 = row1 * row2;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor0 = (row3 * tmp1) + minor0;
	minor3 = row0 * tmp1;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor0 = minor0 - (row3 * tmp1);
	minor3 = (row0 * tmp1) - minor3;
	minor3 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(minor3);
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(row1) * row3;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	row2 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(row2);
	minor0 = (row2 * tmp1) + minor0;
	minor2 = row0 * tmp1;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor0 = minor0 - (row2 * tmp1);
	minor2 = (row0 * tmp1) - minor2;
	minor2 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(minor2);
	tmp1 = row0 * row1;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor2 = (row3 * tmp1) + minor2;
	minor3 = (row2 * tmp1) - minor3;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor2 = (row3 * tmp1) - minor2;
	minor3 = minor3 - (row2 * tmp1);
	tmp1 = row0 * row3;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor1 = minor1 - (row2 * tmp1);
	minor2 = (row1 * tmp1) + minor2;
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor1 = (row2 * tmp1) + minor1;
	minor2 = minor2 - (row1 * tmp1);
	tmp1 = row0 * row2;
	tmp1 = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(tmp1);
	minor1 = (row3 * tmp1) + minor1;
	minor3 = minor3 - (row1 * tmp1);
	tmp1 = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(tmp1);
	minor1 = minor1 - (row3 * tmp1);
	minor3 = (row1 * tmp1) + minor3;
	det4V = row0 * minor0;
	det4V = Permute<VecElem::Z, VecElem::W, VecElem::X, VecElem::Y>(det4V) + det4V;
	det4V = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(det4V) + det4V;
	Vec4V det4VTmp = Vec4V(I_ONE) / det4V;
	det4V = ((det4VTmp + det4VTmp) - (det4V * (det4VTmp * det4VTmp)));
	ScalarV det = ScalarVFromElement<VecElem::X>(det4V);
	if (Verifyf(det, "Matrix Inverse - Determinant == 0, Cannot Perform Matrix Inverse!!!"))
	{
		minor0 = det * minor0;
		minor1 = det * minor1;
		minor2 = det * minor2;
		minor3 = det * minor3;
		return Mat44V(minor0, minor1, minor2, minor3);
	}
	return mMatrix;
}

__forceinline Mat44V_Out Transpose(Mat44V_In mMatrix)
{
	Mat44V retVal(mMatrix);
	retVal.Transpose();
	return retVal;
}

__forceinline Mat44V_Out Transpose3x3(Mat44V_In mMatrix)
{
	Mat44V retVal(mMatrix);
	retVal.Transpose3x3();
	return retVal;
}

__forceinline Mat44V_Out RotateAround(Vec3V_In origin, Mat44V_In rotatorsMatrix, Mat44V_In rotationMatrix)
{
	Mat44V newMat(rotatorsMatrix);
	newMat.Translate(-origin);
	newMat *= rotationMatrix;
	newMat.Translate(origin);
	return newMat;
}

__forceinline Mat44V_Out MakePerspectiveMatrixV(float fFOV, float fAspectRatio, float fNearClip, float fFarClip)
{
	float yScale = 1 / tan(fFOV * 0.5f);
	float xScale = yScale / fAspectRatio;

	return Mat44V(	xScale,		0.0f,	0.0f,												0.0f,
					0.0f,		yScale,	0.0f,												0.0f,
					0.0f,		0.0f,	fFarClip / (fFarClip - fNearClip),					1.0f,
					0.0f,		0.0f,	(-fNearClip * fFarClip) / (fFarClip - fNearClip),	0.0f);
}

__forceinline Mat44V_Out MakeOrthographicMatrixV(float fWidth, float fHeight, float fNear, float fFar)
{
	return Mat44V(	2.0f / fWidth,		0.0f,					0.0f,						0.0f,
					0.0f,				2.0f / fHeight,			0.0f,						0.0f,
					0.0f,				0.0f,					1.0f / (fFar - fNear),		0.0f,
					0.0f,				0.0f,					-fNear / (fFar - fNear),	1.0f);
}

__forceinline Mat44V_Out MakeTextureMatrixOffsetV(unsigned int unWidth, unsigned int unHeight)
{
	return Mat44V(0.5f,						0.0f,						0.0f,	0.0f,
				  0.0f,						-0.5f,						0.0f,	0.0f,
				  0.0f,						0.0f,						1.0f,	0.0f,
				  0.5f + (0.5f / unWidth),	0.5f + (0.5f / unHeight),	0.0f,	1.0f);
}
#endif //SSE_AVAILABLE


__forceinline VecCmpResult::VecCmpResult(const bool& bX)
{
	m_VectorMask = Vec4V(VectorIsNotEqualInt(VectorSet(0), VectorSet(bX, 0, 0, 0)));
}
__forceinline VecCmpResult::VecCmpResult(const bool& bX, const bool& bY)
{
	m_VectorMask = Vec4V(VectorIsNotEqualInt(VectorSet(0), VectorSet(bX, bY, 0, 0)));
}
__forceinline VecCmpResult::VecCmpResult(const bool& bX, const bool& bY, const bool& bZ)
{
	m_VectorMask = Vec4V(VectorIsNotEqualInt(VectorSet(0), VectorSet(bX, bY, bZ, 0)));
}
__forceinline VecCmpResult::VecCmpResult(const bool& bX, const bool& bY, const bool& bZ, const bool bW)
{
	m_VectorMask = Vec4V(VectorIsNotEqualInt(VectorSet(0), VectorSet(bX, bY, bZ, bW)));
}

#if SSE_AVAILABLE
__forceinline VecCmpResult::VecCmpResult(Vector_In result) : m_VectorMask(result) {}
#endif // SSE_AVAILABLE

__forceinline VecCmpResult::operator Vec2f() const { return *reinterpret_cast<const Vec2f*>(&m_VectorMask); }
__forceinline VecCmpResult::operator Vec3f() const { return *reinterpret_cast<const Vec3f*>(&m_VectorMask); }
__forceinline VecCmpResult::operator Vec4f() const { return *reinterpret_cast<const Vec4f*>(&m_VectorMask); }

#if SSE_AVAILABLE
__forceinline VecCmpResult::operator Vec2V() const { return Vec2V(m_VectorMask.GetVector()); }
__forceinline VecCmpResult::operator Vec3V() const { return Vec3V(m_VectorMask.GetVector()); }
__forceinline VecCmpResult::operator Vec4V() const { return Vec4V(m_VectorMask.GetVector()); }
__forceinline VecCmpResult::operator Vector() const { return m_VectorMask.GetVector(); }
#endif // SSE_AVAILABLE

__forceinline int VecCmpResult::GetResultMask() const { return SignMask(m_VectorMask); }
__forceinline VecCmpResult::operator s32 () const { return GetResultMask(); }

__forceinline bool VecCmpResult::IsTrueAny() const { return GetResultMask() != 0; }
__forceinline bool VecCmpResult::IsTrueAll() const { return (GetResultMask() & ((1 << (int)VecElem::X) | (1 << (int)VecElem::Y) | (1 << (int)VecElem::Z) | (1 << (int)VecElem::W))) != 0; }

template<VecElem index>
__forceinline bool VecCmpResult::IsTrue() const { static_assert(index > = VecElem::X && index <= VecElem::W, "Invalid VecCmpResult Index!"); return (GetResultMask() & (1 << index)) != 0; }

template<VecElem index0, VecElem index1>
__forceinline bool VecCmpResult::IsTrue() const
{
	static_assert((index0 >= VecElem::X && index0 <= VecElem::W) && \
		(index1 >= VecElem::X && index1 <= VecElem::W), "Invalid VecCmpResult Index!");
	return (GetResultMask() & ((1 << index0) | (1 << index1))) != 0;
}

template<VecElem index0, VecElem index1, VecElem index2>
__forceinline bool VecCmpResult::IsTrue() const
{
	static_assert((index0 >= VecElem::X && index0 <= VecElem::W) && \
		(index1 >= VecElem::X && index1 <= VecElem::W) && \
		(index2 >= VecElem::X && index2 <= VecElem::W), "Invalid VecCmpResult Index!");
	return (GetResultMask() & ((1 << index0) | (1 << index1) | (1 << index2))) != 0;
}
