
#define SIGNED_INT_BRANCHLESS_MAX(b) \
	template<> __forceinline s##b Max(const s##b & lhs, const s##b & rhs) \
{ \
	s##b diff = lhs - rhs; \
	return lhs - (diff & (diff >> (b - 1))); \
}

template<typename Type>
__forceinline Type Max(const Type& lhs, const Type& rhs)
{
	return (lhs > rhs) ? lhs : rhs;
}

SIGNED_INT_BRANCHLESS_MAX(8)
SIGNED_INT_BRANCHLESS_MAX(16)
SIGNED_INT_BRANCHLESS_MAX(32)
SIGNED_INT_BRANCHLESS_MAX(64)
#undef SIGNED_INT_BRANCHLESS_MAX


#define SIGNED_INT_BRANCHLESS_MIN(b) \
	template<> __forceinline s##b Min(const s##b & lhs, const s##b & rhs) \
{ \
	s##b diff = lhs - rhs; \
	return rhs + (diff & (diff >> (b - 1))); \
}

template<typename Type>
__forceinline Type Min(const Type& lhs, const Type& rhs)
{
	return (lhs < rhs) ? lhs : rhs;
}

SIGNED_INT_BRANCHLESS_MIN(8)
SIGNED_INT_BRANCHLESS_MIN(16)
SIGNED_INT_BRANCHLESS_MIN(32)
SIGNED_INT_BRANCHLESS_MIN(64)
#undef SIGNED_INT_BRANCHLESS_MIN


template<typename Type>
__forceinline Type Clamp(const Type& val, const Type& minVal, const Type& maxVal)
{
	return Max(Min(val, maxVal), minVal);
}

template<typename Type>
__forceinline Type Saturate(const Type& val)
{
	return Clamp(val, Type(0), Type(1));
}


__forceinline Vec2f_Out RECON_VEC_CALLCONV Max(Vec2f_In lhs, Vec2f_In rhs)
{
	return Vec2f(Max(lhs.GetXRef(), rhs.GetXRef()), \
				 Max(lhs.GetYRef(), rhs.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Max(Vec3f_In lhs, Vec3f_In rhs)
{
	return Vec3f(Max(lhs.GetXRef(), rhs.GetXRef()), \
				 Max(lhs.GetYRef(), rhs.GetYRef()), \
				 Max(lhs.GetZRef(), rhs.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Max(Vec4f_In lhs, Vec4f_In rhs)
{
	return Vec4f(Max(lhs.GetXRef(), rhs.GetXRef()), \
				 Max(lhs.GetYRef(), rhs.GetYRef()), \
				 Max(lhs.GetZRef(), rhs.GetZRef()), \
				 Max(lhs.GetWRef(), rhs.GetWRef()));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Min(Vec2f_In lhs, Vec2f_In rhs)
{
	return Vec2f(Min(lhs.GetXRef(), rhs.GetXRef()), \
				 Min(lhs.GetYRef(), rhs.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Min(Vec3f_In lhs, Vec3f_In rhs)
{
	return Vec3f(Min(lhs.GetXRef(), rhs.GetXRef()), \
				 Min(lhs.GetYRef(), rhs.GetYRef()), \
				 Min(lhs.GetZRef(), rhs.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Min(Vec4f_In lhs, Vec4f_In rhs)
{
	return Vec4f(Min(lhs.GetXRef(), rhs.GetXRef()), \
				 Min(lhs.GetYRef(), rhs.GetYRef()), \
				 Min(lhs.GetZRef(), rhs.GetZRef()), \
				 Min(lhs.GetWRef(), rhs.GetWRef()));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Clamp(Vec2f_In val, Vec2f_In minVal, Vec2f_In maxVal)
{
	return Vec2f(Clamp(val.GetXRef(), minVal.GetXRef(), maxVal.GetXRef()), \
				 Clamp(val.GetYRef(), minVal.GetYRef(), maxVal.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Clamp(Vec3f_In val, Vec3f_In minVal, Vec3f_In maxVal)
{
	return Vec3f(Clamp(val.GetXRef(), minVal.GetXRef(), maxVal.GetXRef()), \
				 Clamp(val.GetYRef(), minVal.GetYRef(), maxVal.GetYRef()), \
				 Clamp(val.GetZRef(), minVal.GetZRef(), maxVal.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Clamp(Vec4f_In val, Vec4f_In minVal, Vec4f_In maxVal)
{
	return Vec4f(Clamp(val.GetXRef(), minVal.GetXRef(), maxVal.GetXRef()), \
				 Clamp(val.GetYRef(), minVal.GetYRef(), maxVal.GetYRef()), \
				 Clamp(val.GetZRef(), minVal.GetZRef(), maxVal.GetZRef()), \
				 Clamp(val.GetWRef(), minVal.GetWRef(), maxVal.GetWRef()));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Saturate(Vec2f_In vVector)
{
	return Vec2f(Saturate(vVector.GetXRef()), \
				 Saturate(vVector.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Saturate(Vec3f_In vVector)
{
	return Vec3f(Saturate(vVector.GetXRef()), \
				 Saturate(vVector.GetYRef()), \
				 Saturate(vVector.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Saturate(Vec4f_In vVector)
{
	return Vec4f(Saturate(vVector.GetXRef()), \
				 Saturate(vVector.GetYRef()), \
				 Saturate(vVector.GetZRef()), \
				 Saturate(vVector.GetWRef()));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV MaxInt(Vec2f_In lhs, Vec2f_In rhs)
{
	return Vec2fInt(Max(lhs.GetXiRef(), rhs.GetXiRef()), \
					Max(lhs.GetYiRef(), rhs.GetYiRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV MaxInt(Vec3f_In lhs, Vec3f_In rhs)
{
	return Vec3fInt(Max(lhs.GetXiRef(), rhs.GetXiRef()), \
					Max(lhs.GetYiRef(), rhs.GetYiRef()), \
					Max(lhs.GetZiRef(), rhs.GetZiRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV MaxInt(Vec4f_In lhs, Vec4f_In rhs)
{
	return Vec4fInt(Max(lhs.GetXiRef(), rhs.GetXiRef()), \
					Max(lhs.GetYiRef(), rhs.GetYiRef()), \
					Max(lhs.GetZiRef(), rhs.GetZiRef()), \
					Max(lhs.GetWiRef(), rhs.GetWiRef()));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV MinInt(Vec2f_In lhs, Vec2f_In rhs)
{
	return Vec2fInt(Min(lhs.GetXiRef(), rhs.GetXiRef()), \
					Min(lhs.GetYiRef(), rhs.GetYiRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV MinInt(Vec3f_In lhs, Vec3f_In rhs)
{
	return Vec3fInt(Min(lhs.GetXiRef(), rhs.GetXiRef()), \
					Min(lhs.GetYiRef(), rhs.GetYiRef()), \
					Min(lhs.GetZiRef(), rhs.GetZiRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV MinInt(Vec4f_In lhs, Vec4f_In rhs)
{
	return Vec4fInt(Min(lhs.GetXiRef(), rhs.GetXiRef()), \
					Min(lhs.GetYiRef(), rhs.GetYiRef()), \
					Min(lhs.GetZiRef(), rhs.GetZiRef()), \
					Min(lhs.GetWiRef(), rhs.GetWiRef()));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV ClampInt(Vec2f_In val, Vec2f_In minVal, Vec2f_In maxVal)
{
	return Vec2fInt(Clamp(val.GetXiRef(), minVal.GetXiRef(), maxVal.GetXiRef()), \
					Clamp(val.GetYiRef(), minVal.GetYiRef(), maxVal.GetYiRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV ClampInt(Vec3f_In val, Vec3f_In minVal, Vec3f_In maxVal)
{
	return Vec3fInt(Clamp(val.GetXiRef(), minVal.GetXiRef(), maxVal.GetXiRef()), \
					Clamp(val.GetYiRef(), minVal.GetYiRef(), maxVal.GetYiRef()), \
					Clamp(val.GetZiRef(), minVal.GetZiRef(), maxVal.GetZiRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV ClampInt(Vec4f_In val, Vec4f_In minVal, Vec4f_In maxVal)
{
	return Vec4fInt(Clamp(val.GetXiRef(), minVal.GetXiRef(), maxVal.GetXiRef()), \
					Clamp(val.GetYiRef(), minVal.GetYiRef(), maxVal.GetYiRef()), \
					Clamp(val.GetZiRef(), minVal.GetZiRef(), maxVal.GetZiRef()), \
					Clamp(val.GetWiRef(), minVal.GetWiRef(), maxVal.GetWiRef()));
}

__forceinline f32 RECON_VEC_CALLCONV Lerp(const f32& lhs, const f32& rhs, const f32& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline f64 RECON_VEC_CALLCONV Lerp(const f64& lhs, const f64& rhs, const f64& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Lerp(Vec2f_In lhs, Vec2f_In rhs, const f32& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Lerp(Vec3f_In lhs, Vec3f_In rhs, const f32& fLambda)
{
	return lhs + (rhs - lhs) * fLambda;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Lerp(Vec4f_In lhs, Vec4f_In rhs, const f32& fLambda)
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

__forceinline f32 Abs(const f32& fScalar)
{
	return abs(fScalar);
}

__forceinline f64 Abs(const f64& fScalar)
{
	return abs(fScalar);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Abs(Vec2f_In vVector)
{
	return Vec2f(Abs(vVector.GetXRef()), Abs(vVector.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Abs(Vec3f_In vVector)
{
	return Vec3f(Abs(vVector.GetXRef()), Abs(vVector.GetYRef()), Abs(vVector.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Abs(Vec4f_In vVector)
{
	return Vec4f(Abs(vVector.GetXRef()), Abs(vVector.GetYRef()), Abs(vVector.GetZRef()), Abs(vVector.GetWRef()));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV AbsInt(Vec2f_In vVector)
{
	return Vec2fInt(Abs(vVector.GetXiRef()), Abs(vVector.GetYiRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV AbsInt(Vec3f_In vVector)
{
	return Vec3fInt(Abs(vVector.GetXiRef()), Abs(vVector.GetYiRef()), Abs(vVector.GetZiRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV AbsInt(Vec4f_In vVector)
{
	return Vec4fInt(Abs(vVector.GetXiRef()), Abs(vVector.GetYiRef()), Abs(vVector.GetZiRef()), Abs(vVector.GetWiRef()));
}

__forceinline f32 Sqrt(const f32& fScalar)
{
	return sqrtf(fScalar);
}

__forceinline f64 Sqrt(const f64& fScalar)
{
	return sqrt(fScalar);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Sqrt(Vec2f_In vVector)
{
	return Vec2f(Sqrt(vVector.GetXRef()), Sqrt(vVector.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Sqrt(Vec3f_In vVector)
{
	return Vec3f(Sqrt(vVector.GetXRef()), Sqrt(vVector.GetYRef()), Sqrt(vVector.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Sqrt(Vec4f_In vVector)
{
	return Vec4f(Sqrt(vVector.GetXRef()), Sqrt(vVector.GetYRef()), Sqrt(vVector.GetZRef()), Sqrt(vVector.GetWRef()));
}

__forceinline f32 SqrtSafe(const f32& fScalar, const f32& safeVal /*= 0.0f*/)
{
	return fScalar != 0.0f ? Sqrt(fScalar) : safeVal;
}

__forceinline f64 SqrtSafe(const f64& fScalar, const f64& safeVal /*= 0.0*/)
{
	return fScalar != 0.0 ? Sqrt(fScalar) : safeVal;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV SqrtSafe(Vec2f_In vVector, Vec2f_In vSafeVec /*= Vec2f(I_ZERO)*/)
{
	return Vec2f(SqrtSafe(vVector.GetXRef(), vSafeVec.GetXRef()), \
				 SqrtSafe(vVector.GetYRef(), vSafeVec.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV SqrtSafe(Vec3f_In vVector, Vec3f_In vSafeVec /*= Vec3f(I_ZERO)*/)
{
	return Vec3f(SqrtSafe(vVector.GetXRef(), vSafeVec.GetXRef()), \
				 SqrtSafe(vVector.GetYRef(), vSafeVec.GetYRef()), \
				 SqrtSafe(vVector.GetZRef(), vSafeVec.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV SqrtSafe(Vec4f_In vVector, Vec4f_In vSafeVec /*= Vec4f(I_ZERO)*/)
{
	return Vec4f(SqrtSafe(vVector.GetXRef(), vSafeVec.GetXRef()), \
				 SqrtSafe(vVector.GetYRef(), vSafeVec.GetYRef()), \
				 SqrtSafe(vVector.GetZRef(), vSafeVec.GetZRef()), \
				 SqrtSafe(vVector.GetWRef(), vSafeVec.GetWRef()));
}

template<VecElem splat>
__forceinline Vec2f_Out RECON_VEC_CALLCONV Splat(Vec2f_In lhs)
{
	return Permute<splat, splat>(lhs);
}

template<VecElem splat>
__forceinline Vec3f_Out RECON_VEC_CALLCONV Splat(Vec3f_In lhs)
{
	return Permute<splat, splat, splat>(lhs);
}

template<VecElem splat>
__forceinline Vec4f_Out RECON_VEC_CALLCONV Splat(Vec4f_In lhs)
{
	return Permute<splat, splat, splat, splat>(lhs);
}

template<VecElem pX, VecElem pY>
__forceinline Vec2f_Out RECON_VEC_CALLCONV Permute(Vec2f_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::Y) &&
					(pY >= VecElem::X && pY <= VecElem::Y), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec2f(lhs[(s32)pX], lhs[(s32)pY]);
}

template<VecElem pX, VecElem pY, VecElem pZ>
__forceinline Vec3f_Out RECON_VEC_CALLCONV Permute(Vec3f_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::Z) &&
					(pY >= VecElem::X && pY <= VecElem::Z) &&
					(pZ >= VecElem::X && pY <= VecElem::Z), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Z!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y && pZ == VecElem::Z), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec3f(lhs[(s32)pX], lhs[(s32)pY], lhs[(s32)pZ]);
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> 
__forceinline Vec4f_Out RECON_VEC_CALLCONV Permute(Vec4f_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::W) &&
					(pY >= VecElem::X && pY <= VecElem::W) &&
					(pZ >= VecElem::X && pY <= VecElem::W) &&
					(pW >= VecElem::X && pY <= VecElem::W), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::W!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y && pZ == VecElem::Z && pW == VecElem::W), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec4f(lhs[(s32)pX], lhs[(s32)pY], lhs[(s32)pZ], lhs[(s32)pW]);
}

template<VecElem pX, VecElem pY>
__forceinline Vec2f_Out RECON_VEC_CALLCONV Permute(Vec2f_In lhs, Vec2f_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::Y1) || (pX >= VecElem::X2 && pX <= VecElem::Y2)) &&
					((pY >= VecElem::X1 && pY <= VecElem::Y1) || (pY >= VecElem::X2 && pY <= VecElem::Y2)), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1) || 
					(pX == VecElem::X2 && pY == VecElem::Y2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	const f32* vectors[] = {lhs.GetVector(), rhs.GetVector()};
	return Vec2f(vectors[(s32)pX >> 4][(s32)pX & 0x3], vectors[(s32)pY >> 4][(s32)pY & 0x3]);
}

template<VecElem pX, VecElem pY, VecElem pZ>
__forceinline Vec3f_Out RECON_VEC_CALLCONV Permute(Vec3f_In lhs, Vec3f_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::Z1) || (pX >= VecElem::X2 && pX <= VecElem::Z2)) &&
					((pY >= VecElem::X1 && pY <= VecElem::Z1) || (pY >= VecElem::X2 && pY <= VecElem::Z2)) &&
					((pZ >= VecElem::X1 && pZ <= VecElem::Z1) || (pZ >= VecElem::X2 && pZ <= VecElem::Z2)), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1 && pZ == VecElem::Z1) || 
					(pX == VecElem::X2 && pY == VecElem::Y2 && pZ == VecElem::Z2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	const f32* vectors[] = {lhs.GetVector(), rhs.GetVector()};
	return Vec3f(vectors[(s32)pX >> 4][(s32)pX & 0x3], vectors[(s32)pY >> 4][(s32)pY & 0x3], vectors[(s32)pZ >> 4][(s32)pZ & 0x3]);
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW> 
__forceinline Vec4f_Out RECON_VEC_CALLCONV Permute(Vec4f_In lhs, Vec4f_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::W1) || (pX >= VecElem::X2 && pX <= VecElem::W2)) &&
					((pY >= VecElem::X1 && pY <= VecElem::W1) || (pY >= VecElem::X2 && pY <= VecElem::W2)) &&
					((pZ >= VecElem::X1 && pZ <= VecElem::W1) || (pZ >= VecElem::X2 && pZ <= VecElem::W2)) &&
					((pW >= VecElem::X1 && pW <= VecElem::W1) || (pW >= VecElem::X2 && pW <= VecElem::W2)), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1 && pZ == VecElem::Z1 && pW == VecElem::W1) || 
					(pX == VecElem::X2 && pY == VecElem::Y2 && pZ == VecElem::Z2 && pW == VecElem::W2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	const f32* vectors[] = {lhs.GetVector(), rhs.GetVector()};
	return Vec4f(vectors[(s32)pX >> 4][(s32)pX & 0x3], vectors[(s32)pY >> 4][(s32)pY & 0x3], vectors[(s32)pZ >> 4][(s32)pZ & 0x3], vectors[(s32)pW >> 4][(s32)pW & 0x3]);
}

__forceinline s32 RECON_VEC_CALLCONV SignMask(Vec2f_In vVector)
{
	return s32(((vVector.GetXiRef() & BIT31) << (s32)VecElem::X) | \
			   ((vVector.GetYiRef() & BIT31) << (s32)VecElem::Y));
}

__forceinline s32 RECON_VEC_CALLCONV SignMask(Vec3f_In vVector)
{
	return s32(((vVector.GetXiRef() & BIT31) << (s32)VecElem::X) | \
			   ((vVector.GetYiRef() & BIT31) << (s32)VecElem::Y) | \
			   ((vVector.GetZiRef() & BIT31) << (s32)VecElem::Z));
}

__forceinline s32 RECON_VEC_CALLCONV SignMask(Vec4f_In vVector)
{
	return s32(((vVector.GetXiRef() & BIT31) << (s32)VecElem::X) | \
			   ((vVector.GetYiRef() & BIT31) << (s32)VecElem::Y) | \
			   ((vVector.GetZiRef() & BIT31) << (s32)VecElem::Z) | \
			   ((vVector.GetWiRef() & BIT31) << (s32)VecElem::W));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV SelectTF(Vec2f_In condition, Vec2f_In ifTrue, Vec2f_In ifFalse)
{
	return Vec2f((condition.GetXiRef() & BIT31) ? ifTrue.GetXRef() : ifFalse.GetXRef(),
				 (condition.GetYiRef() & BIT31) ? ifTrue.GetYRef() : ifFalse.GetYRef());
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV SelectTF(Vec3f_In condition, Vec3f_In ifTrue, Vec3f_In ifFalse)
{
	return Vec3f((condition.GetXiRef() & BIT31) ? ifTrue.GetXRef() : ifFalse.GetXRef(),
				 (condition.GetYiRef() & BIT31) ? ifTrue.GetYRef() : ifFalse.GetYRef(),
				 (condition.GetZiRef() & BIT31) ? ifTrue.GetZRef() : ifFalse.GetZRef());
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV SelectTF(Vec4f_In condition, Vec4f_In ifTrue, Vec4f_In ifFalse)
{
	return Vec4f((condition.GetXiRef() & BIT31) ? ifTrue.GetXRef() : ifFalse.GetXRef(),
				 (condition.GetYiRef() & BIT31) ? ifTrue.GetYRef() : ifFalse.GetYRef(),
				 (condition.GetZiRef() & BIT31) ? ifTrue.GetZRef() : ifFalse.GetZRef(),
				 (condition.GetWiRef() & BIT31) ? ifTrue.GetWRef() : ifFalse.GetWRef());
}

__forceinline f32 Sin(const f32& fRadians)
{
	return sinf(fRadians);
}

__forceinline f64 Sin(const f64& fRadians)
{
	return sin(fRadians);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Sin(Vec2f_In vRadians)
{
	return Vec2f(Sin(vRadians.GetXRef()), Sin(vRadians.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Sin(Vec3f_In vRadians)
{
	return Vec3f(Sin(vRadians.GetXRef()), Sin(vRadians.GetYRef()), Sin(vRadians.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Sin(Vec4f_In vRadians)
{
	return Vec4f(Sin(vRadians.GetXRef()), Sin(vRadians.GetYRef()), Sin(vRadians.GetZRef()), Sin(vRadians.GetWRef()));
}

__forceinline f32 ASin(const f32& fRadians)
{
	return asinf(fRadians);
}

__forceinline f64 ASin(const f64& fRadians)
{
	return asin(fRadians);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV ASin(Vec2f_In vRadians)
{
	return Vec2f(ASin(vRadians.GetXRef()), ASin(vRadians.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV ASin(Vec3f_In vRadians)
{
	return Vec3f(ASin(vRadians.GetXRef()), ASin(vRadians.GetYRef()), ASin(vRadians.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV ASin(Vec4f_In vRadians)
{
	return Vec4f(ASin(vRadians.GetXRef()), ASin(vRadians.GetYRef()), ASin(vRadians.GetZRef()), ASin(vRadians.GetWRef()));
}

__forceinline f32 Cos(const f32& fRadians)
{
	return cosf(fRadians);
}

__forceinline f64 Cos(const f64& fRadians)
{
	return cos(fRadians);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Cos(Vec2f_In vRadians)
{
	return Vec2f(Cos(vRadians.GetXRef()), Cos(vRadians.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Cos(Vec3f_In vRadians)
{
	return Vec3f(Cos(vRadians.GetXRef()), Cos(vRadians.GetYRef()), Cos(vRadians.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Cos(Vec4f_In vRadians)
{
	return Vec4f(Cos(vRadians.GetXRef()), Cos(vRadians.GetYRef()), Cos(vRadians.GetZRef()), Cos(vRadians.GetWRef()));
}

__forceinline f32 ACos(const f32& fRadians)
{
	return acosf(fRadians);
}

__forceinline f64 ACos(const f64& fRadians)
{
	return acos(fRadians);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV ACos(Vec2f_In vRadians)
{
	return Vec2f(ACos(vRadians.GetXRef()), ACos(vRadians.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV ACos(Vec3f_In vRadians)
{
	return Vec3f(ACos(vRadians.GetXRef()), ACos(vRadians.GetYRef()), ACos(vRadians.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV ACos(Vec4f_In vRadians)
{
	return Vec4f(ACos(vRadians.GetXRef()), ACos(vRadians.GetYRef()), ACos(vRadians.GetZRef()), ACos(vRadians.GetWRef()));
}

__forceinline f32 Tan(const f32& fRadians)
{
	return tanf(fRadians);
}

__forceinline f64 Tan(const f64& fRadians)
{
	return tan(fRadians);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Tan(Vec2f_In vRadians)
{
	return Vec2f(Tan(vRadians.GetXRef()), Tan(vRadians.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Tan(Vec3f_In vRadians)
{
	return Vec3f(Tan(vRadians.GetXRef()), Tan(vRadians.GetYRef()), Tan(vRadians.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Tan(Vec4f_In vRadians)
{
	return Vec4f(Tan(vRadians.GetXRef()), Tan(vRadians.GetYRef()), Tan(vRadians.GetZRef()), Tan(vRadians.GetWRef()));
}

__forceinline f32 ATan(const f32& fRadians)
{
	return atanf(fRadians);
}

__forceinline f64 ATan(const f64& fRadians)
{
	return atan(fRadians);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV ATan(Vec2f_In vRadians)
{
	return Vec2f(ATan(vRadians.GetXRef()), ATan(vRadians.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV ATan(Vec3f_In vRadians)
{
	return Vec3f(ATan(vRadians.GetXRef()), ATan(vRadians.GetYRef()), ATan(vRadians.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV ATan(Vec4f_In vRadians)
{
	return Vec4f(ATan(vRadians.GetXRef()), ATan(vRadians.GetYRef()), ATan(vRadians.GetZRef()), ATan(vRadians.GetWRef()));
}

// Returns: Vec2f(Sin(), Cos());
__forceinline Vec2f_Out RECON_VEC_CALLCONV SinCos(const f32& fRadians)
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
	__forceinline VecCmpResult RECON_VEC_CALLCONV name(varType##_In lhs, varType##_In rhs) \
{ \
	return VecCmpResult(cmpDef); \
}

#define VEC_CMP_DEF(name, amt, nameExt, varType) \
	__forceinline bool RECON_VEC_CALLCONV name##nameExt(varType##_In lhs, varType##_In rhs) \
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
	__forceinline varType##_Out RECON_VEC_CALLCONV name(varType##_In lhs, varType##_In rhs) \
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
	__forceinline varType##_Out RECON_VEC_CALLCONV name(varType##_In lhs, varType##_In rhs) \
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


__forceinline f32 RECON_VEC_CALLCONV Dot(Vec2f_In vVectorA, Vec2f_In vVectorB)
{
	return (vVectorA.x * vVectorB.x) + (vVectorA.y * vVectorB.y);
}

__forceinline f32 RECON_VEC_CALLCONV Dot(Vec3f_In vVectorA, Vec3f_In vVectorB)
{
	return (vVectorA.x * vVectorB.x) + (vVectorA.y * vVectorB.y) + (vVectorA.z * vVectorB.z);
}

__forceinline f32 RECON_VEC_CALLCONV Dot(Vec4f_In vVectorA, Vec4f_In vVectorB)
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

__forceinline f32 RECON_VEC_CALLCONV Mag(Vec2f_In vVector)
{
	return sqrtf(MagSq(vVector));
}

__forceinline f32 RECON_VEC_CALLCONV Mag(Vec3f_In vVector)
{
	return sqrtf(MagSq(vVector));
}

__forceinline f32 RECON_VEC_CALLCONV Mag(Vec4f_In vVector)
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

__forceinline f32 RECON_VEC_CALLCONV Length(Vec2f_In vVector)
{
	return Mag(vVector);
}

__forceinline f32 RECON_VEC_CALLCONV Length(Vec3f_In vVector)
{
	return Mag(vVector);
}

__forceinline f32 RECON_VEC_CALLCONV Length(Vec4f_In vVector)
{
	return Mag(vVector);
}

__forceinline f32 RECON_VEC_CALLCONV MagSq(Vec2f_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline f32 RECON_VEC_CALLCONV MagSq(Vec3f_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline f32 RECON_VEC_CALLCONV MagSq(Vec4f_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline f32 RECON_VEC_CALLCONV LengthSq(Vec2f_In vVector)
{
	return MagSq(vVector);
}

__forceinline f32 RECON_VEC_CALLCONV LengthSq(Vec3f_In vVector)
{
	return MagSq(vVector);
}

__forceinline f32 RECON_VEC_CALLCONV LengthSq(Vec4f_In vVector)
{
	return MagSq(vVector);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Normalize(Vec2f_In vVector)
{
	f32 magSq = MagSq(vVector); \
	return magSq ? (vVector * (1 / Sqrt(magSq))) : vVector;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Normalize(Vec3f_In vVector)
{
	f32 magSq = MagSq(vVector); \
	return magSq ? (vVector * (1 / Sqrt(magSq))) : vVector;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Normalize(Vec4f_In vVector)
{
	f32 magSq = MagSq(vVector); \
	return magSq ? (vVector * (1 / Sqrt(magSq))) : vVector;
}

__forceinline Mat33f_Out RECON_VEC_CALLCONV Normalize(Mat33f_In mMatrix)
{
	return Mat33f(Normalize(mMatrix.GetXAxisRef()), \
				  Normalize(mMatrix.GetYAxisRef()), \
				  Normalize(mMatrix.GetZAxisRef()));
}

__forceinline Mat43f_Out RECON_VEC_CALLCONV Normalize(Mat43f_In mMatrix)
{
	return Mat43f(Normalize(mMatrix.GetXAxisRef()), \
				  Normalize(mMatrix.GetYAxisRef()), \
				  Normalize(mMatrix.GetZAxisRef()), \
				  mMatrix.GetWAxisRef());
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV Normalize(Mat44f_In mMatrix)
{
	return Mat44f(Vec4f(Normalize(mMatrix.GetXAxisRef().GetXYZ()), mMatrix.GetXAxisRef().GetWRef()), \
				  Vec4f(Normalize(mMatrix.GetYAxisRef().GetXYZ()), mMatrix.GetYAxisRef().GetWRef()), \
				  Vec4f(Normalize(mMatrix.GetZAxisRef().GetXYZ()), mMatrix.GetZAxisRef().GetWRef()), \
				  mMatrix.GetWAxisRef());
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV IntToFloat(Vec2f_In vVector)
{
	return Vec2f((f32)vVector.GetXiRef(), 
				 (f32)vVector.GetYiRef());
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV IntToFloat(Vec3f_In vVector)
{
	return Vec3f((f32)vVector.GetXiRef(), 
				 (f32)vVector.GetYiRef(),
				 (f32)vVector.GetZiRef());
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV IntToFloat(Vec4f_In vVector)
{
	return Vec4f((f32)vVector.GetXiRef(), 
				 (f32)vVector.GetYiRef(),
				 (f32)vVector.GetZiRef(),
				 (f32)vVector.GetWiRef());
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV FloatToInt(Vec2f_In vVector)
{
	return Vec2fInt((s32)vVector.GetXRef(), (s32)vVector.GetYRef());
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV FloatToInt(Vec3f_In vVector)
{
	return Vec3fInt((s32)vVector.GetXRef(), (s32)vVector.GetYRef(), (s32)vVector.GetZRef());
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV FloatToInt(Vec4f_In vVector)
{
	return Vec4fInt((s32)vVector.GetXRef(), (s32)vVector.GetYRef(), (s32)vVector.GetZRef(), (s32)vVector.GetWRef());
}

__forceinline f32 Floor(const f32& fScalar)
{
	return floorf(fScalar);
}

__forceinline f64 Floor(const f64& fScalar)
{
	return floor(fScalar);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Floor(Vec2f_In vVector)
{
	return Vec2f(Floor(vVector.GetXRef()), Floor(vVector.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Floor(Vec3f_In vVector)
{
	return Vec3f(Floor(vVector.GetXRef()), Floor(vVector.GetYRef()), Floor(vVector.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Floor(Vec4f_In vVector)
{
	return Vec4f(Floor(vVector.GetXRef()), Floor(vVector.GetYRef()), Floor(vVector.GetZRef()), Floor(vVector.GetWRef()));
}

__forceinline f32 Ceil(const f32& fScalar)
{
	return ceilf(fScalar);
}

__forceinline f64 Ceil(const f64& fScalar)
{
	return ceil(fScalar);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Ceil(Vec2f_In vVector)
{
	return Vec2f(Ceil(vVector.GetXRef()), Ceil(vVector.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Ceil(Vec3f_In vVector)
{
	return Vec3f(Ceil(vVector.GetXRef()), Ceil(vVector.GetYRef()), Ceil(vVector.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Ceil(Vec4f_In vVector)
{
	return Vec4f(Ceil(vVector.GetXRef()), Ceil(vVector.GetYRef()), Ceil(vVector.GetZRef()), Ceil(vVector.GetWRef()));
}

__forceinline f32 Trunc(const f32& fScalar)
{
	return f32(s64(fScalar));
}

__forceinline f64 Trunc(const f64& fScalar)
{
	return f64(s64(fScalar));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Trunc(Vec2f_In vVector)
{
	return Vec2f(Trunc(vVector.GetXRef()), Trunc(vVector.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Trunc(Vec3f_In vVector)
{
	return Vec3f(Trunc(vVector.GetXRef()), Trunc(vVector.GetYRef()), Trunc(vVector.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Trunc(Vec4f_In vVector)
{
	return Vec4f(Trunc(vVector.GetXRef()), Trunc(vVector.GetYRef()), Trunc(vVector.GetZRef()), Trunc(vVector.GetWRef()));
}

__forceinline f32 Round(const f32& fScalar)
{
	return Floor(fScalar + 0.5f);
}

__forceinline f64 Round(const f64& fScalar)
{
	return Floor(fScalar + 0.5);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Round(Vec2f& vVector)
{
	return Vec2f(Round(vVector.GetXRef()), Round(vVector.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Round(Vec3f_In vVector)
{
	return Vec3f(Round(vVector.GetXRef()), Round(vVector.GetYRef()), Round(vVector.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Round(Vec4f_In vVector)
{
	return Vec4f(Round(vVector.GetXRef()), Round(vVector.GetYRef()), Round(vVector.GetZRef()), Round(vVector.GetWRef()));
}

__forceinline f32 Log2(const f32& fScalar)
{
	Assertf(fScalar > 0.0f, "Log2 - fScalar Cannot Be Less Than Zero!");
	return log2f(fScalar);
}

__forceinline f64 Log2(const f64& fScalar)
{
	Assertf(fScalar > 0.0f, "Log2 - fScalar Cannot Be Less Than Zero!");
	return log2(fScalar);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Log2(Vec2f_In vVector)
{
	return Vec2f(Log2(vVector.GetXRef()), Log2(vVector.GetYRef()));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Log2(Vec3f_In vVector)
{
	return Vec3f(Log2(vVector.GetXRef()), Log2(vVector.GetYRef()), Log2(vVector.GetZRef()));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Log2(Vec4f_In vVector)
{
	return Vec4f(Log2(vVector.GetXRef()), Log2(vVector.GetYRef()), Log2(vVector.GetZRef()), Log2(vVector.GetWRef()));
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV Lerp(Mat44f_In MatrixA, Mat44f_In MatrixB, const f32 fLambda)
{
	Mat44f result;
	result.GetXAxisRef().SetXYZ(Lerp(MatrixA.GetXAxis().GetXYZ(), MatrixB.GetXAxis().GetXYZ(), fLambda));
	result.GetYAxisRef().SetXYZ(Lerp(MatrixA.GetYAxis().GetXYZ(), MatrixB.GetYAxis().GetXYZ(), fLambda));
	result.GetZAxisRef().SetXYZ(Lerp(MatrixA.GetZAxis().GetXYZ(), MatrixB.GetZAxis().GetXYZ(), fLambda));
	result.GetWAxisRef().SetXYZ(Lerp(MatrixA.GetWAxis().GetXYZ(), MatrixB.GetWAxis().GetXYZ(), fLambda));
	return result;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Cross(Vec3f_In lhs, Vec3f_In rhs)
{
	return Vec3f(lhs.GetY() * rhs.GetZ() - lhs.GetZ() * rhs.GetY(),
				 lhs.GetZ() * rhs.GetX() - lhs.GetX() * rhs.GetZ(),
				 lhs.GetX() * rhs.GetY() - lhs.GetY() * rhs.GetX());
}

__forceinline Mat44f RECON_VEC_CALLCONV Mat43ToMat44(Mat43f_In mMatrix)
{
	return Mat44f(Vec4f(mMatrix.GetXAxisRef(), 0.0f), \
				  Vec4f(mMatrix.GetYAxisRef(), 0.0f), \
				  Vec4f(mMatrix.GetZAxisRef(), 0.0f), \
				  Vec4f(mMatrix.GetWAxisRef(), 1.0f));
}

__forceinline Mat43f RECON_VEC_CALLCONV Mat44ToMat43(Mat44f_In mMatrix)
{
	return Mat43f(mMatrix.GetXAxisRef().GetXYZ(), \
				  mMatrix.GetYAxisRef().GetXYZ(), \
				  mMatrix.GetZAxisRef().GetXYZ(), \
				  mMatrix.GetWAxisRef().GetXYZ());
}

__forceinline Mat43f_Out RECON_VEC_CALLCONV LookAt(Vec3f_In viewerPos, Vec3f_In lookAtPos, Vec3f_In vWorldUp /*= Vec3f(I_WORLD_UP)*/)
{
	Mat43f retVal;
	retVal.SetZAxis(Normalize(lookAtPos - viewerPos));
	retVal.SetXAxis(Normalize(Cross(vWorldUp, retVal.GetZAxisRef())));
	retVal.SetYAxis(Normalize(Cross(retVal.GetZAxisRef(), retVal.GetXAxisRef())));
	retVal.SetWAxis(viewerPos);
	return retVal;
}

inline Mat43f_Out RECON_VEC_CALLCONV TurnTo(Mat43f_In vTurningMat, Vec3f_In vTurnToPos, const f32& fDeltaTime, const f32& fTurnModifier /*= 1.0f*/)
{
	Mat43f retVal(vTurningMat);

	Vec3f vecToPos = Normalize(vTurnToPos - retVal.GetWAxisRef());

	f32 protection = Dot(vecToPos, retVal.GetZAxisRef());

	if(protection != protection)
	{
		// You are already facing that exact direction
		return retVal;
	}

	f32 fRotation = Dot(vecToPos, retVal.GetXAxisRef());

	if(fRotation > FLT_EPSILON || fRotation < -FLT_EPSILON)
	{
		// protection to keep the matrix from turning slowly
		// if the position is behind the matrix
		if(Dot(vecToPos, retVal.GetZAxisRef()) < 0.0f)
			fRotation = (fRotation < 0.0f) ? -1.0f : 1.0f;

		retVal.RotateLocalY(fRotation * fTurnModifier * fDeltaTime);
	}

	fRotation = Dot(vecToPos, retVal.GetYAxisRef());

	if(fRotation > FLT_EPSILON || fRotation < -FLT_EPSILON)
		retVal.RotateLocalX(-fRotation * fTurnModifier * fDeltaTime);

	retVal.SetXAxis(Normalize(Cross(Vec3f(I_WORLD_UP), retVal.GetZAxisRef())));
	retVal.SetYAxis(Normalize(Cross(retVal.GetZAxisRef(), retVal.GetXAxisRef())));

	return retVal;
}

inline Mat44f_Out RECON_VEC_CALLCONV Invert(Mat44f_In mMatrix)
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
	const f32& det = det4f.GetXRef();
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

inline Mat44f_Out RECON_VEC_CALLCONV InvertOrtho(Mat44f_In mMatrix)
{
	Mat44f retVal(Transpose3x3(mMatrix));
	Vec4f_Ref wAxis = retVal.GetWAxisRef();
	wAxis.SetX(-Dot(mMatrix.GetWAxisRef().GetXYZ(), mMatrix.GetXAxisRef().GetXYZ()));
	wAxis.SetY(-Dot(mMatrix.GetWAxisRef().GetXYZ(), mMatrix.GetYAxisRef().GetXYZ()));
	wAxis.SetZ(-Dot(mMatrix.GetWAxisRef().GetXYZ(), mMatrix.GetZAxisRef().GetXYZ()));
	return retVal;
}

__forceinline Mat33f_Out RECON_VEC_CALLCONV Transpose(Mat33f_In mMatrix)
{
	Mat33f retVal(mMatrix); 
	std::swap(retVal.GetYAxisRef().GetXRef(), retVal.GetXAxisRef().GetYRef());
	std::swap(retVal.GetZAxisRef().GetXRef(), retVal.GetXAxisRef().GetZRef());
	std::swap(retVal.GetZAxisRef().GetYRef(), retVal.GetYAxisRef().GetZRef());
	return retVal;
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV Transpose(Mat44f_In mMatrix)
{
	Mat44f retVal(mMatrix);
	std::swap(retVal.GetXAxisRef().GetYRef(), retVal.GetYAxisRef().GetXRef());
	std::swap(retVal.GetXAxisRef().GetZRef(), retVal.GetZAxisRef().GetXRef());
	std::swap(retVal.GetYAxisRef().GetZRef(), retVal.GetZAxisRef().GetYRef());
	std::swap(retVal.GetWAxisRef().GetXRef(), retVal.GetXAxisRef().GetWRef());
	std::swap(retVal.GetWAxisRef().GetYRef(), retVal.GetYAxisRef().GetWRef());
	std::swap(retVal.GetWAxisRef().GetZRef(), retVal.GetZAxisRef().GetWRef());
	return retVal;
}

__forceinline Mat43f_Out RECON_VEC_CALLCONV Transpose3x3(Mat43f_In mMatrix)
{
	Mat43f retVal;
	retVal.SetMat33(Transpose(mMatrix.GetMat33Ref()));
	retVal.SetWAxis(mMatrix.GetWAxisRef());
	return retVal;
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV Transpose3x3(Mat44f_In mMatrix)
{
	Mat44f retVal(mMatrix);
	std::swap(retVal.GetYAxisRef().GetXRef(), retVal.GetXAxisRef().GetYRef());
	std::swap(retVal.GetZAxisRef().GetXRef(), retVal.GetXAxisRef().GetZRef());
	std::swap(retVal.GetZAxisRef().GetYRef(), retVal.GetYAxisRef().GetZRef());
	return retVal;
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV RotateAround(Vec3f_In origin, Mat44f_In rotatorsMatrix, Mat44f_In rotationMatrix)
{
	Mat44f newMat(rotatorsMatrix);
	newMat.Translate(-origin);
	newMat *= rotationMatrix;
	newMat.Translate(origin);
	return newMat;
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV MakePerspectiveMatrix(f32 fFOV, f32 fAspectRatio, f32 fNearClip, f32 fFarClip)
{
	f32 yScale = 1 / tan(fFOV * 0.5f);
	f32 xScale = yScale / fAspectRatio;

	return Mat44f(	xScale,		0.0f,	0.0f,												0.0f,
					0.0f,		yScale,	0.0f,												0.0f,
					0.0f,		0.0f,	fFarClip / (fFarClip - fNearClip),					1.0f,
					0.0f,		0.0f,	(-fNearClip * fFarClip) / (fFarClip - fNearClip),	0.0f);
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV MakeOrthographicMatrix(f32 fWidth, f32 fHeight, f32 fNear, f32 fFar)
{
	return Mat44f(	2.0f / fWidth,		0.0f,					0.0f,						0.0f,
					0.0f,				2.0f / fHeight,			0.0f,						0.0f,
					0.0f,				0.0f,					1.0f / (fFar - fNear),		0.0f,
					0.0f,				0.0f,					-fNear / (fFar - fNear),	1.0f);
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV MakeTextureMatrixOffset(f32 fWidth, f32 fHeight)
{
	return Mat44f(0.5f,						0.0f,						0.0f,	0.0f,
				  0.0f,						-0.5f,						0.0f,	0.0f,
				  0.0f,						0.0f,						1.0f,	0.0f,
				  0.5f + (0.5f / fWidth),	0.5f + (0.5f / fHeight),	0.0f,	1.0f);
}

__forceinline f32 CalculateGaussianWeight(s32 nOffset, f32 fSigma)
{
	return (1 / sqrt(TWO_PI * (fSigma * fSigma))) * exp(-(nOffset * nOffset) / (2 * (fSigma * fSigma)));
}

// unRadius - Number of Pixels to Blur In a Single Direction Including the Center Pixel
inline void CalculateGaussianWeights(f32* pGaussianWeights, u32 unRadius, f32 fLimit)
{
	u32 i;
	f32 fCurrWeight;
	f32 fTotalWeight = 0;
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

__forceinline ScalarV_Out RECON_VEC_CALLCONV Max(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorMax(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Max(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorMax(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Max(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorMax(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Max(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorMax(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Min(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorMin(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Min(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorMin(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Min(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorMin(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Min(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorMin(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Clamp(ScalarV_In val, ScalarV_In minVal, ScalarV_In maxVal)
{
	return ScalarV(VectorClamp(val.GetVector(), minVal.GetVector(), maxVal.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Clamp(Vec2V_In val, Vec2V_In minVal, Vec2V_In maxVal)
{
	return Vec2V(VectorClamp(val.GetVector(), minVal.GetVector(), maxVal.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Clamp(Vec3V_In val, Vec3V_In minVal, Vec3V_In maxVal)
{
	return Vec3V(VectorClamp(val.GetVector(), minVal.GetVector(), maxVal.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Clamp(Vec4V_In val, Vec4V_In minVal, Vec4V_In maxVal)
{
	return Vec4V(VectorClamp(val.GetVector(), minVal.GetVector(), maxVal.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Saturate(ScalarV_In vVector)
{
	return Clamp(vVector, ScalarV(I_ZERO), ScalarV(I_ONE));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Saturate(Vec2V_In vVector)
{
	return Clamp(vVector, Vec2V(I_ZERO), Vec2V(I_ONE));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Saturate(Vec3V_In vVector)
{
	return Clamp(vVector, Vec3V(I_ZERO), Vec3V(I_ONE));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Saturate(Vec4V_In vVector)
{
	return Clamp(vVector, Vec4V(I_ZERO), Vec4V(I_ONE));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV MaxInt(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorMaxInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV MaxInt(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorMaxInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV MaxInt(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorMaxInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV MaxInt(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorMaxInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV MinInt(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorMinInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV MinInt(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorMinInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV MinInt(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorMinInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV MinInt(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorMinInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV ClampInt(ScalarV_In val, ScalarV_In minVal, ScalarV_In maxVal)
{
	return ScalarV(VectorClampInt(val.GetVector(), minVal.GetVector(), maxVal.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV ClampInt(Vec2V_In val, Vec2V_In minVal, Vec2V_In maxVal)
{
	return Vec2V(VectorClampInt(val.GetVector(), minVal.GetVector(), maxVal.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV ClampInt(Vec3V_In val, Vec3V_In minVal, Vec3V_In maxVal)
{
	return Vec3V(VectorClampInt(val.GetVector(), minVal.GetVector(), maxVal.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV ClampInt(Vec4V_In val, Vec4V_In minVal, Vec4V_In maxVal)
{
	return Vec4V(VectorClampInt(val.GetVector(), minVal.GetVector(), maxVal.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Lerp(ScalarV_In lhs, ScalarV_In rhs, ScalarV_In vLambda)
{
	return lhs + (rhs - lhs) * vLambda;
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Lerp(Vec2V_In lhs, Vec2V_In rhs, ScalarV_In vLambda)
{
	return lhs + (rhs - lhs) * vLambda;
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Lerp(Vec3V_In lhs, Vec3V_In rhs, ScalarV_In vLambda)
{
	return lhs + (rhs - lhs) * vLambda;
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Lerp(Vec4V_In lhs, Vec4V_In rhs, ScalarV_In vLambda)
{
	return lhs + (rhs - lhs) * vLambda;
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Abs(ScalarV_In vScalar)
{
	return ScalarV(VectorAbs(vScalar.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Abs(Vec2V_In vVector)
{
	return Vec2V(VectorAbs(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Abs(Vec3V_In vVector)
{
	return Vec3V(VectorAbs(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Abs(Vec4V_In vVector)
{
	return Vec4V(VectorAbs(vVector.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV AbsInt(ScalarV_In vVector)
{
	return ScalarV(VectorAbsInt(vVector.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV AbsInt(Vec2V_In vVector)
{
	return Vec2V(VectorAbsInt(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV AbsInt(Vec3V_In vVector)
{
	return Vec3V(VectorAbsInt(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV AbsInt(Vec4V_In vVector)
{
	return Vec4V(VectorAbsInt(vVector.GetVector()));
}

template<VecElem splat>
__forceinline Vec2V_Out RECON_VEC_CALLCONV Splat(Vec2V_In lhs)
{
	return Permute<splat, splat>(lhs);
}

template<VecElem splat>
__forceinline Vec3V_Out RECON_VEC_CALLCONV Splat(Vec3V_In lhs)
{
	return Permute<splat, splat, splat>(lhs);
}

template<VecElem splat>
__forceinline Vec4V_Out RECON_VEC_CALLCONV Splat(Vec4V_In lhs)
{
	return Permute<splat, splat, splat, splat>(lhs);
}

template<VecElem pX, VecElem pY>
__forceinline Vec2V_Out RECON_VEC_CALLCONV Permute(Vec2V_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::Y) &&
					(pY >= VecElem::X && pY <= VecElem::Y), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Y!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec2V(VectorPermute<pX, pY, VecElem::Z, VecElem::W>(lhs.GetVector()));
}

template<VecElem pX, VecElem pY, VecElem pZ>
__forceinline Vec3V_Out RECON_VEC_CALLCONV Permute(Vec3V_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::Z) &&
					(pY >= VecElem::X && pY <= VecElem::Z) &&
					(pZ >= VecElem::X && pY <= VecElem::Z), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::Z!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y && pZ == VecElem::Z), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec3V(VectorPermute<pX, pY, pZ, VecElem::W>(lhs.GetVector()));
}
template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
__forceinline Vec4V_Out RECON_VEC_CALLCONV Permute(Vec4V_In lhs)
{
	static_assert(	(pX >= VecElem::X && pX <= VecElem::W) &&
					(pY >= VecElem::X && pY <= VecElem::W) &&
					(pZ >= VecElem::X && pY <= VecElem::W) &&
					(pW >= VecElem::X && pY <= VecElem::W), "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::W!");
	static_assert(	!(pX == VecElem::X && pY == VecElem::Y && pZ == VecElem::Z && pW == VecElem::W), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec4V(VectorPermute<pX, pY, pZ, pW>(lhs.GetVector()));
}

template<VecElem pX, VecElem pY>
__forceinline Vec2V_Out RECON_VEC_CALLCONV Permute(Vec2V_In lhs, Vec2V_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::Y1) || (pX >= VecElem::X2 && pX <= VecElem::Y2)) &&
					((pY >= VecElem::X1 && pY <= VecElem::Y1) || (pY >= VecElem::X2 && pY <= VecElem::Y2)), "Invalid Permute Indices! Indices must be between VecElem::X1 <-> VecElem::W2!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1) || 
					  (pX == VecElem::X2 && pY == VecElem::Y2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec2V(VectorPermute<pX, pY, VecElem::Z1, VecElem::W1>(lhs.GetVector(), rhs.GetVector()));
}

template<VecElem pX, VecElem pY, VecElem pZ>
__forceinline Vec3V_Out RECON_VEC_CALLCONV Permute(Vec3V_In lhs, Vec3V_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::Z1) || (pX >= VecElem::X2 && pX <= VecElem::Z2)) &&
					((pY >= VecElem::X1 && pY <= VecElem::Z1) || (pY >= VecElem::X2 && pY <= VecElem::Z2)) &&
					((pZ >= VecElem::X1 && pZ <= VecElem::Z1) || (pZ >= VecElem::X2 && pZ <= VecElem::Z2)), "Invalid Permute Indices! Indices must be between VecElem::X1 <-> VecElem::W2!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1 && pZ == VecElem::Z1) || 
						 (pX == VecElem::X2 && pY == VecElem::Y2 && pZ == VecElem::Z2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec3V(VectorPermute<pX, pY, pZ, VecElem::W1>(lhs.GetVector(), rhs.GetVector()));
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
__forceinline Vec4V_Out RECON_VEC_CALLCONV Permute(Vec4V_In lhs, Vec4V_In rhs)
{
	static_assert(	((pX >= VecElem::X1 && pX <= VecElem::W1) || (pX >= VecElem::X2 && pX <= VecElem::W2)) &&
					((pY >= VecElem::X1 && pY <= VecElem::W1) || (pY >= VecElem::X2 && pY <= VecElem::W2)) &&
					((pZ >= VecElem::X1 && pZ <= VecElem::W1) || (pZ >= VecElem::X2 && pZ <= VecElem::W2)) &&
					((pW >= VecElem::X1 && pW <= VecElem::W1) || (pW >= VecElem::X2 && pW <= VecElem::W2)), "Invalid Permute Indices! Indices must be between VecElem::X1 <-> VecElem::W2!");
	static_assert(	!((pX == VecElem::X1 && pY == VecElem::Y1 && pZ == VecElem::Z1 && pW == VecElem::W1) || 
						 (pX == VecElem::X2 && pY == VecElem::Y2 && pZ == VecElem::Z2 && pW == VecElem::W2)), "Invalid Permute Indices! Vector Will Not Change, So Don't Bother Calling Permute!");
	return Vec4V(VectorPermute<pX, pY, pZ, pW>(lhs.GetVector(), rhs.GetVector()));
}

__forceinline s32 RECON_VEC_CALLCONV SignMask(Vec2V_In vVector)
{
	return VectorSignMask(vVector.GetVector()) & 0x3;
}

__forceinline s32 RECON_VEC_CALLCONV SignMask(Vec3V_In vVector)
{
	return VectorSignMask(vVector.GetVector()) & 0x7;
}

__forceinline s32 RECON_VEC_CALLCONV SignMask(Vec4V_In vVector)
{
	return VectorSignMask(vVector.GetVector()) & 0xF;
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV SelectTF(ScalarV_In condition, ScalarV_In ifTrue, ScalarV_In ifFalse)
{
	return ScalarV(VectorSelectTF(condition.GetVector(), ifTrue.GetVector(), ifFalse.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV SelectTF(Vec2V_In condition, Vec2V_In ifTrue, Vec2V_In ifFalse)
{
	return Vec2V(VectorSelectTF(condition.GetVector(), ifTrue.GetVector(), ifFalse.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV SelectTF(Vec3V_In condition, Vec3V_In ifTrue, Vec3V_In ifFalse)
{
	return Vec3V(VectorSelectTF(condition.GetVector(), ifTrue.GetVector(), ifFalse.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV SelectTF(Vec4V_In condition, Vec4V_In ifTrue, Vec4V_In ifFalse)
{
	return Vec4V(VectorSelectTF(condition.GetVector(), ifTrue.GetVector(), ifFalse.GetVector()));
}

template<VecElem elem> 
__forceinline ScalarV_Out RECON_VEC_CALLCONV ScalarVFromElement(Vector_In vVector)
{
	static_assert(elem >= VecElem::X && elem <= VecElem::W, "Invalid Permute Indices! Indices must be between VecElem::X <-> VecElem::W!");
	return ScalarV(VectorPermute<elem, elem, elem, elem>(vVector));
}

template<VecElem elem> 
__forceinline ScalarV_Out RECON_VEC_CALLCONV ScalarVFromElement(Vec2V_In vVector)
{
	return ScalarVFromElement<elem>(vVector.GetVector());
}

template<VecElem elem> 
__forceinline ScalarV_Out RECON_VEC_CALLCONV ScalarVFromElement(Vec3V_In vVector)
{
	return ScalarVFromElement<elem>(vVector.GetVector());
}

template<VecElem elem> 
__forceinline ScalarV_Out RECON_VEC_CALLCONV ScalarVFromElement(Vec4V_In vVector)
{
	return ScalarVFromElement<elem>(vVector.GetVector());
}


// Trigonometry Functions:

__forceinline ScalarV_Out RECON_VEC_CALLCONV Sin(ScalarV_In vRadians)
{
	return ScalarV(VectorSin(vRadians.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Sin(Vec2V_In vRadians)
{
	return Vec2V(VectorSin(vRadians.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Sin(Vec3V_In vRadians)
{
	return Vec3V(VectorSin(vRadians.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Sin(Vec4V_In vRadians)
{
	return Vec4V(VectorSin(vRadians.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV ASin(ScalarV_In vRadians)
{
	return ScalarV(VectorASin(vRadians.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV ASin(Vec2V_In vRadians)
{
	return Vec2V(VectorASin(vRadians.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV ASin(Vec3V_In vRadians)
{
	return Vec3V(VectorASin(vRadians.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV ASin(Vec4V_In vRadians)
{
	return Vec4V(VectorASin(vRadians.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Cos(ScalarV_In vRadians)
{
	return ScalarV(VectorCos(vRadians.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Cos(Vec2V_In vRadians)
{
	return Vec2V(VectorCos(vRadians.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Cos(Vec3V_In vRadians)
{
	return Vec3V(VectorCos(vRadians.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Cos(Vec4V_In vRadians)
{
	return Vec4V(VectorCos(vRadians.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV ACos(ScalarV_In vRadians)
{
	return ScalarV(VectorACos(vRadians.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV ACos(Vec2V_In vRadians)
{
	return Vec2V(VectorACos(vRadians.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV ACos(Vec3V_In vRadians)
{
	return Vec3V(VectorACos(vRadians.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV ACos(Vec4V_In vRadians)
{
	return Vec4V(VectorACos(vRadians.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Tan(ScalarV_In vRadians)
{
	return ScalarV(VectorTan(vRadians.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Tan(Vec2V_In vRadians)
{
	return Vec2V(VectorTan(vRadians.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Tan(Vec3V_In vRadians)
{
	return Vec3V(VectorTan(vRadians.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Tan(Vec4V_In vRadians)
{
	return Vec4V(VectorTan(vRadians.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV ATan(ScalarV_In vRadians)
{
	return ScalarV(VectorATan(vRadians.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV ATan(Vec2V_In vRadians)
{
	return Vec2V(VectorATan(vRadians.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV ATan(Vec3V_In vRadians)
{
	return Vec3V(VectorATan(vRadians.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV ATan(Vec4V_In vRadians)
{
	return Vec4V(VectorATan(vRadians.GetVector()));
}

// Returns: Vec2V(Sin(), Cos(), Sin(), Cos());
__forceinline Vec2V_Out RECON_VEC_CALLCONV SinCos(ScalarV_In vRadians)
{
	return Vec2V(VectorSinCos(vRadians.GetVector()));
}



// Comparison Functions

#define VEC_CMP_DEFBASE(name, varType)	\
	__forceinline varType##_Out RECON_VEC_CALLCONV name(varType##_In lhs, varType##_In rhs) \
{ \
	return varType(Vector##name(lhs.GetVector(), rhs.GetVector())); \
}

#define VEC_CMP_DEF(name, nameExt, varType) \
	__forceinline bool RECON_VEC_CALLCONV name##nameExt(varType##_In lhs, varType##_In rhs) \
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

VEC_CMP_DEF_VEC2(IsEqual, ScalarV)
VEC_CMP_DEF_VEC2(IsEqual, Vec2V)
VEC_CMP_DEF_VEC3(IsEqual, Vec3V)
VEC_CMP_DEF_VEC4(IsEqual, Vec4V)

VEC_CMP_DEF_VEC2(IsNotEqual, ScalarV)
VEC_CMP_DEF_VEC2(IsNotEqual, Vec2V)
VEC_CMP_DEF_VEC3(IsNotEqual, Vec3V)
VEC_CMP_DEF_VEC4(IsNotEqual, Vec4V)

VEC_CMP_DEF_VEC2(IsGreaterThan, ScalarV)
VEC_CMP_DEF_VEC2(IsGreaterThan, Vec2V)
VEC_CMP_DEF_VEC3(IsGreaterThan, Vec3V)
VEC_CMP_DEF_VEC4(IsGreaterThan, Vec4V)

VEC_CMP_DEF_VEC2(IsGreaterThanOrEqual, ScalarV)
VEC_CMP_DEF_VEC2(IsGreaterThanOrEqual, Vec2V)
VEC_CMP_DEF_VEC3(IsGreaterThanOrEqual, Vec3V)
VEC_CMP_DEF_VEC4(IsGreaterThanOrEqual, Vec4V)

VEC_CMP_DEF_VEC2(IsLessThan, ScalarV)
VEC_CMP_DEF_VEC2(IsLessThan, Vec2V)
VEC_CMP_DEF_VEC3(IsLessThan, Vec3V)
VEC_CMP_DEF_VEC4(IsLessThan, Vec4V)

VEC_CMP_DEF_VEC2(IsLessThanOrEqual, ScalarV)
VEC_CMP_DEF_VEC2(IsLessThanOrEqual, Vec2V)
VEC_CMP_DEF_VEC3(IsLessThanOrEqual, Vec3V)
VEC_CMP_DEF_VEC4(IsLessThanOrEqual, Vec4V)

VEC_CMP_DEF_VEC2(IsEqualInt, ScalarV)
VEC_CMP_DEF_VEC2(IsEqualInt, Vec2V)
VEC_CMP_DEF_VEC3(IsEqualInt, Vec3V)
VEC_CMP_DEF_VEC4(IsEqualInt, Vec4V)

VEC_CMP_DEF_VEC2(IsNotEqualInt, ScalarV)
VEC_CMP_DEF_VEC2(IsNotEqualInt, Vec2V)
VEC_CMP_DEF_VEC3(IsNotEqualInt, Vec3V)
VEC_CMP_DEF_VEC4(IsNotEqualInt, Vec4V)

VEC_CMP_DEF_VEC2(IsGreaterThanInt, ScalarV)
VEC_CMP_DEF_VEC2(IsGreaterThanInt, Vec2V)
VEC_CMP_DEF_VEC3(IsGreaterThanInt, Vec3V)
VEC_CMP_DEF_VEC4(IsGreaterThanInt, Vec4V)

VEC_CMP_DEF_VEC2(IsGreaterThanOrEqualInt, ScalarV)
VEC_CMP_DEF_VEC2(IsGreaterThanOrEqualInt, Vec2V)
VEC_CMP_DEF_VEC3(IsGreaterThanOrEqualInt, Vec3V)
VEC_CMP_DEF_VEC4(IsGreaterThanOrEqualInt, Vec4V)

VEC_CMP_DEF_VEC2(IsLessThanInt, ScalarV)
VEC_CMP_DEF_VEC2(IsLessThanInt, Vec2V)
VEC_CMP_DEF_VEC3(IsLessThanInt, Vec3V)
VEC_CMP_DEF_VEC4(IsLessThanInt, Vec4V)

VEC_CMP_DEF_VEC2(IsLessThanOrEqualInt, ScalarV)
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

__forceinline ScalarV_Out RECON_VEC_CALLCONV Sqrt(ScalarV_In vScalar)
{
	return ScalarV(VectorSqrt(vScalar.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Sqrt(Vec2V_In vVector)
{
	return Vec2V(VectorSqrt(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Sqrt(Vec3V_In vVector)
{
	return Vec3V(VectorSqrt(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Sqrt(Vec4V_In vVector)
{
	return Vec4V(VectorSqrt(vVector.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV SqrtSafe(ScalarV_In vScalar, ScalarV_In safeVec /*= ScalarV(I_ZERO)*/)
{
	Vector NotZeroVecMask = VectorIsNotEqual(vScalar.GetVector(), VectorSetConstant<FloatToIntRep::Zero>());
	Vector sqrtVal = VectorSqrt(vScalar.GetVector());
	return ScalarV(VectorOr(VectorAnd(sqrtVal, NotZeroVecMask), VectorAndNot(safeVec.GetVector(), NotZeroVecMask)));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV SqrtSafe(Vec2V_In vVector, Vec2V_In safeVec /*= Vec2V(I_ZERO)*/)
{
	Vector NotZeroVecMask = VectorIsNotEqual(vVector.GetVector(), VectorSetConstant<FloatToIntRep::Zero>());
	Vector sqrtVal = VectorSqrt(vVector.GetVector());
	return Vec2V(VectorOr(VectorAnd(sqrtVal, NotZeroVecMask), VectorAndNot(safeVec.GetVector(), NotZeroVecMask)));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV SqrtSafe(Vec3V_In vVector, Vec3V_In safeVec /*= Vec3V(I_ZERO)*/)
{
	Vector NotZeroVecMask = VectorIsNotEqual(vVector.GetVector(), VectorSetConstant<FloatToIntRep::Zero>());
	Vector sqrtVal = VectorSqrt(vVector.GetVector());
	return Vec3V(VectorOr(VectorAnd(sqrtVal, NotZeroVecMask), VectorAndNot(safeVec.GetVector(), NotZeroVecMask)));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV SqrtSafe(Vec4V_In vVector, Vec4V_In safeVec /*= Vec4V(I_ZERO)*/)
{
	Vector NotZeroVecMask = VectorIsNotEqual(vVector.GetVector(), VectorSetConstant<FloatToIntRep::Zero>());
	Vector sqrtVal = VectorSqrt(vVector.GetVector());
	return Vec4V(VectorOr(VectorAnd(sqrtVal, NotZeroVecMask), VectorAndNot(safeVec.GetVector(), NotZeroVecMask)));
}


__forceinline ScalarV RECON_VEC_CALLCONV Dot(Vec2V_In vVectorA, Vec2V_In vVectorB)
{
	Vector tmp = VectorMultiply(vVectorA.GetVector(), vVectorB.GetVector());
	return ScalarVFromElement<VecElem::X>(VectorHAdd(tmp, tmp));
}

__forceinline ScalarV RECON_VEC_CALLCONV Dot(Vec3V_In vVectorA, Vec3V_In vVectorB)
{
	Vector tmpRhs = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(vVectorB.GetVector(), VectorSetConstant<FloatToIntRep::Zero>());
	Vector tmp = VectorMultiply(vVectorA.GetVector(), tmpRhs);
	tmp = VectorHAdd(tmp, tmp);
	return ScalarVFromElement<VecElem::X>(VectorHAdd(tmp, tmp));
}

__forceinline ScalarV RECON_VEC_CALLCONV Dot(Vec4V_In vVectorA, Vec4V_In vVectorB)
{
	Vector tmp = VectorMultiply(vVectorA.GetVector(), vVectorB.GetVector());
	tmp = VectorHAdd(tmp, tmp);
	return ScalarVFromElement<VecElem::X>(VectorHAdd(tmp, tmp));
}

__forceinline ScalarV RECON_VEC_CALLCONV Mag(Vec2V_In vVector)
{
	return Sqrt(MagSq(vVector));
}

__forceinline ScalarV RECON_VEC_CALLCONV Mag(Vec3V_In vVector)
{
	return Sqrt(MagSq(vVector));
}

__forceinline ScalarV RECON_VEC_CALLCONV Mag(Vec4V_In vVector)
{
	return Sqrt(MagSq(vVector));
}

__forceinline ScalarV RECON_VEC_CALLCONV Length(Vec2V_In vVector)
{
	return Sqrt(LengthSq(vVector));
}

__forceinline ScalarV RECON_VEC_CALLCONV Length(Vec3V_In vVector)
{
	return Sqrt(LengthSq(vVector));
}

__forceinline ScalarV RECON_VEC_CALLCONV Length(Vec4V_In vVector)
{
	return Sqrt(LengthSq(vVector));
}

__forceinline ScalarV RECON_VEC_CALLCONV MagSq(Vec2V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV RECON_VEC_CALLCONV MagSq(Vec3V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV RECON_VEC_CALLCONV MagSq(Vec4V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV RECON_VEC_CALLCONV LengthSq(Vec2V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV RECON_VEC_CALLCONV LengthSq(Vec3V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline ScalarV RECON_VEC_CALLCONV LengthSq(Vec4V_In vVector)
{
	return Dot(vVector, vVector);
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Normalize(Vec2V_In vVector)
{
	Vec2V magSq(MagSq(vVector));
	return Vec2V(SelectTF(IsGreaterThan(magSq, Vec2V(I_ZERO)), vVector / Sqrt(magSq), Vec2V(I_ZERO)));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Normalize(Vec3V_In vVector)
{
	Vec3V magSq(MagSq(vVector));
	return Vec3V(SelectTF(IsGreaterThan(magSq, Vec3V(I_ZERO)), vVector / Sqrt(magSq), Vec3V(I_ZERO)));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Normalize(Vec4V_In vVector)
{
	Vec4V magSq(MagSq(vVector));
	return Vec4V(SelectTF(IsGreaterThan(magSq, Vec4V(I_ZERO)), vVector / Sqrt(magSq), Vec4V(I_ZERO)));
}

__forceinline Mat33V_Out RECON_VEC_CALLCONV Normalize(Mat33V_In mMatrix)
{
	return Mat33V(Normalize(mMatrix.GetXAxisRef()), \
				  Normalize(mMatrix.GetYAxisRef()), \
				  Normalize(mMatrix.GetZAxisRef()));
}

__forceinline Mat43V_Out RECON_VEC_CALLCONV Normalize(Mat43V_In mMatrix)
{
	return Mat43V(Normalize(mMatrix.GetXAxisRef()), \
				  Normalize(mMatrix.GetYAxisRef()), \
				  Normalize(mMatrix.GetZAxisRef()), \
				  mMatrix.GetWAxisRef());
}

__forceinline Mat44V_Out RECON_VEC_CALLCONV Normalize(Mat44V_In mMatrix)
{
	return Mat44V(Vec4V(Normalize(mMatrix.GetXAxisRef().GetXYZ()), mMatrix.GetXAxisRef().GetW()), \
				  Vec4V(Normalize(mMatrix.GetYAxisRef().GetXYZ()), mMatrix.GetYAxisRef().GetW()), \
				  Vec4V(Normalize(mMatrix.GetZAxisRef().GetXYZ()), mMatrix.GetZAxisRef().GetW()), \
				  mMatrix.GetWAxisRef());
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV AddInt(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorAddInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV AddInt(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorAddInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec3V_Out RECON_VEC_CALLCONV AddInt(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorAddInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec4V_Out RECON_VEC_CALLCONV AddInt(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorAddInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV SubtractInt(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorSubtractInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV SubtractInt(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorSubtractInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec3V_Out RECON_VEC_CALLCONV SubtractInt(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorSubtractInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec4V_Out RECON_VEC_CALLCONV SubtractInt(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorSubtractInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV MultiplyInt(ScalarV_In lhs, ScalarV_In rhs)
{
	return ScalarV(VectorMultiplyInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV MultiplyInt(Vec2V_In lhs, Vec2V_In rhs)
{
	return Vec2V(VectorMultiplyInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec3V_Out RECON_VEC_CALLCONV MultiplyInt(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorMultiplyInt(lhs.GetVector(), rhs.GetVector()));
}
__forceinline Vec4V_Out RECON_VEC_CALLCONV MultiplyInt(Vec4V_In lhs, Vec4V_In rhs)
{
	return Vec4V(VectorMultiplyInt(lhs.GetVector(), rhs.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV IntToFloat(ScalarV_In vVector)
{
	return ScalarV(VectorIntToFloat(vVector.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV IntToFloat(Vec2V_In vVector)
{
	return Vec2V(VectorIntToFloat(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV IntToFloat(Vec3V_In vVector)
{
	return Vec3V(VectorIntToFloat(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV IntToFloat(Vec4V_In vVector)
{
	return Vec4V(VectorIntToFloat(vVector.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV FloatToInt(ScalarV_In vVector)
{
	return ScalarV(VectorFloatToInt(vVector.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV FloatToInt(Vec2V_In vVector)
{
	return Vec2V(VectorFloatToInt(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV FloatToInt(Vec3V_In vVector)
{
	return Vec3V(VectorFloatToInt(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV FloatToInt(Vec4V_In vVector)
{
	return Vec4V(VectorFloatToInt(vVector.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Floor(ScalarV_In vVector)
{
	return ScalarV(VectorFloor(vVector.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Floor(Vec2V_In vVector)
{
	return Vec2V(VectorFloor(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Floor(Vec3V_In vVector)
{
	return Vec3V(VectorFloor(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Floor(Vec4V_In vVector)
{
	return Vec4V(VectorFloor(vVector.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Ceil(ScalarV_In vVector)
{
	return ScalarV(VectorCeil(vVector.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Ceil(Vec2V_In vVector)
{
	return Vec2V(VectorCeil(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Ceil(Vec3V_In vVector)
{
	return Vec3V(VectorCeil(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Ceil(Vec4V_In vVector)
{
	return Vec4V(VectorCeil(vVector.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Trunc(ScalarV_In vVector)
{
	return ScalarV(VectorTrunc(vVector.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Trunc(Vec2V_In vVector)
{
	return Vec2V(VectorTrunc(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Trunc(Vec3V_In vVector)
{
	return Vec3V(VectorTrunc(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Trunc(Vec4V_In vVector)
{
	return Vec4V(VectorTrunc(vVector.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Round(ScalarV_In vVector)
{
	return ScalarV(VectorRound(vVector.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Round(Vec2V_In vVector)
{
	return Vec2V(VectorRound(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Round(Vec3V_In vVector)
{
	return Vec3V(VectorRound(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Round(Vec4V_In vVector)
{
	return Vec4V(VectorRound(vVector.GetVector()));
}

__forceinline ScalarV_Out RECON_VEC_CALLCONV Log2(ScalarV_In vScalar)
{
	return ScalarV(VectorLog2(vScalar.GetVector()));
}
__forceinline Vec2V_Out RECON_VEC_CALLCONV Log2(Vec2V_In vVector)
{
	return Vec2V(VectorLog2(vVector.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Log2(Vec3V_In vVector)
{
	return Vec3V(VectorLog2(vVector.GetVector()));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Log2(Vec4V_In vVector)
{
	return Vec4V(VectorLog2(vVector.GetVector()));
}

inline Mat44V_Out RECON_VEC_CALLCONV Lerp(Mat44V_In MatrixA, Mat44V_In MatrixB, ScalarV_In vLambda)
{
	Mat44V result;
	result.GetXAxisRef().SetXYZ(Lerp(MatrixA.GetXAxis().GetXYZ(), MatrixB.GetXAxis().GetXYZ(), vLambda));
	result.GetYAxisRef().SetXYZ(Lerp(MatrixA.GetYAxis().GetXYZ(), MatrixB.GetYAxis().GetXYZ(), vLambda));
	result.GetZAxisRef().SetXYZ(Lerp(MatrixA.GetZAxis().GetXYZ(), MatrixB.GetZAxis().GetXYZ(), vLambda));
	result.GetWAxisRef().SetXYZ(Lerp(MatrixA.GetWAxis().GetXYZ(), MatrixB.GetWAxis().GetXYZ(), vLambda));
	return result;
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Cross(Vec3V_In lhs, Vec3V_In rhs)
{
	return Vec3V(VectorCrossProduct(lhs.GetVector(), rhs.GetVector()));
}

__forceinline Mat44V RECON_VEC_CALLCONV Mat43ToMat44(Mat43V_In mMatrix)
{
	return Mat44V(Vec4V(mMatrix.GetXAxisRef(), ScalarV(I_ZERO)), \
				  Vec4V(mMatrix.GetYAxisRef(), ScalarV(I_ZERO)), \
				  Vec4V(mMatrix.GetZAxisRef(), ScalarV(I_ZERO)), \
				  Vec4V(mMatrix.GetWAxisRef(), ScalarV(I_ONE)));
}

__forceinline Mat43V RECON_VEC_CALLCONV Mat44ToMat43(Mat44V_In mMatrix)
{
	return Mat43V(mMatrix.GetXAxisRef().GetXYZ(), \
				  mMatrix.GetYAxisRef().GetXYZ(), \
				  mMatrix.GetZAxisRef().GetXYZ(), \
				  mMatrix.GetWAxisRef().GetXYZ());
}

__forceinline Mat43V_Out RECON_VEC_CALLCONV LookAt(Vec3V_In viewerPos, Vec3V_In lookAtPos, Vec3V_In vWorldUp /*= Vec3V(I_WORLD_UP)*/)
{
	Mat43V retVal;
	retVal.SetZAxis(Normalize(lookAtPos - viewerPos));
	retVal.SetXAxis(Normalize(Cross(vWorldUp, retVal.GetZAxisRef())));
	retVal.SetYAxis(Normalize(Cross(retVal.GetZAxisRef(), retVal.GetXAxisRef())));
	retVal.SetWAxis(viewerPos);
	return retVal;
}

inline Mat43V_Out RECON_VEC_CALLCONV TurnTo(Mat43V_In vTurningMat, Vec3V_In vTurnToPos, ScalarV_In vDeltaTime, ScalarV_In vTurnModifier /*= ScalarV(I_ONE)*/)
{
	Mat43V retVal(vTurningMat);

	Vec3V vecToPos = Normalize(vTurnToPos - retVal.GetWAxisRef());

	ScalarV protection = Dot(vecToPos, retVal.GetZAxisRef());

	if(protection != protection)
	{
		// You are already facing that exact direction
		return retVal;
	}

	ScalarV fRotation = Dot(vecToPos, retVal.GetXAxisRef());

	if(fRotation > ScalarV(I_FLT_EPSILON) || fRotation < ScalarV(I_NEG_FLT_EPSILON))
	{
		// protection to keep the matrix from turning slowly
		// if the position is behind the matrix
		if(Dot(vecToPos, retVal.GetZAxisRef()) < ScalarV(I_ZERO))
			fRotation = (fRotation < ScalarV(I_ZERO)) ? ScalarV(I_NEG_ONE) : ScalarV(I_ONE);

		retVal.RotateLocalY(fRotation * vTurnModifier * vDeltaTime);
	}

	fRotation = Dot(vecToPos, retVal.GetYAxisRef());

	if(fRotation > ScalarV(I_FLT_EPSILON) || fRotation < ScalarV(I_NEG_FLT_EPSILON))
		retVal.RotateLocalX(-fRotation * vTurnModifier * vDeltaTime);

	retVal.SetXAxis(Normalize(Cross(Vec3V(I_WORLD_UP), retVal.GetZAxisRef())));
	retVal.SetYAxis(Normalize(Cross(retVal.GetZAxisRef(), retVal.GetXAxisRef())));

	return retVal;
}

inline Mat44V_Out RECON_VEC_CALLCONV Invert(Mat44V_In mMatrix)
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

inline Mat44V_Out RECON_VEC_CALLCONV InvertOrtho(Mat44V_In mMatrix)
{
	Mat44V retVal(Transpose3x3(mMatrix));
	Vec4V_Ref wAxis = retVal.GetWAxisRef();
	wAxis.SetX(-Dot(mMatrix.GetWAxisRef().GetXYZ(), mMatrix.GetXAxisRef().GetXYZ()));
	wAxis.SetY(-Dot(mMatrix.GetWAxisRef().GetXYZ(), mMatrix.GetYAxisRef().GetXYZ()));
	wAxis.SetZ(-Dot(mMatrix.GetWAxisRef().GetXYZ(), mMatrix.GetZAxisRef().GetXYZ()));
	return retVal;
}

__forceinline Mat33V_Out RECON_VEC_CALLCONV Transpose(Mat33V_In mMatrix)
{
	Mat33V retVal;
	Vec3V tmp = Permute<VecElem::X1, VecElem::X2, VecElem::Z1>(mMatrix.GetXAxisRef(), mMatrix.GetYAxisRef());
	retVal.SetXAxis(Permute<VecElem::X1, VecElem::Y1, VecElem::X2>(tmp, mMatrix.GetZAxisRef()));
	tmp = Permute<VecElem::Y2, VecElem::Y1, VecElem::Z1>(mMatrix.GetYAxisRef(), mMatrix.GetXAxisRef());
	retVal.SetYAxis(Permute<VecElem::X1, VecElem::Y1, VecElem::Y2>(tmp, mMatrix.GetZAxisRef()));
	tmp = Permute<VecElem::Z2, VecElem::Y1, VecElem::Z1>(mMatrix.GetZAxisRef(), mMatrix.GetXAxisRef());
	retVal.SetZAxis(Permute<VecElem::X1, VecElem::Z2, VecElem::Z1>(tmp, mMatrix.GetYAxisRef()));
	return retVal;
}

__forceinline Mat44V_Out RECON_VEC_CALLCONV Transpose(Mat44V_In mMatrix)
{
	Mat44V retVal;
	Vec4V tmp1 = Permute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(mMatrix.GetXAxisRef(), mMatrix.GetYAxisRef());
	Vec4V tmp2 = Permute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(mMatrix.GetZAxisRef(), mMatrix.GetWAxisRef());
	Vec4V tmp3 = Permute<VecElem::Z1, VecElem::W1, VecElem::Z2, VecElem::W2>(mMatrix.GetXAxisRef(), mMatrix.GetYAxisRef());
	Vec4V tmp4 = Permute<VecElem::Z1, VecElem::W1, VecElem::Z2, VecElem::W2>(mMatrix.GetZAxisRef(), mMatrix.GetWAxisRef());
	retVal.SetXAxis(Permute<VecElem::X1, VecElem::Z1, VecElem::X2, VecElem::Z2>(tmp1, tmp2));
	retVal.SetYAxis(Permute<VecElem::Y1, VecElem::W1, VecElem::Y2, VecElem::W2>(tmp1, tmp2));
	retVal.SetZAxis(Permute<VecElem::X1, VecElem::Z1, VecElem::X2, VecElem::Z2>(tmp3, tmp4));
	retVal.SetWAxis(Permute<VecElem::Y1, VecElem::W1, VecElem::Y2, VecElem::W2>(tmp3, tmp4));
	return retVal;
}

__forceinline Mat43V_Out RECON_VEC_CALLCONV Transpose3x3(Mat43V_In mMatrix)
{
	Mat43V retVal;
	retVal.SetMat33(Transpose(mMatrix.GetMat33Ref()));
	retVal.SetWAxis(mMatrix.GetWAxisRef());
	return retVal;
}

__forceinline Mat44V_Out RECON_VEC_CALLCONV Transpose3x3(Mat44V_In mMatrix)
{
	Mat44V retVal;
	Vec4V tmp = Permute<VecElem::X1, VecElem::X2, VecElem::Z1, VecElem::W1>(mMatrix.GetXAxisRef(), mMatrix.GetYAxisRef());
	retVal.SetXAxis(Permute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::W1>(tmp, mMatrix.GetZAxisRef()));
	tmp = Permute<VecElem::Y2, VecElem::Y1, VecElem::Z1, VecElem::W1>(mMatrix.GetYAxisRef(), mMatrix.GetXAxisRef());
	retVal.SetYAxis(Permute<VecElem::X1, VecElem::Y1, VecElem::Y2, VecElem::W1>(tmp, mMatrix.GetZAxisRef()));
	tmp = Permute<VecElem::Z2, VecElem::Y1, VecElem::Z1, VecElem::W1>(mMatrix.GetZAxisRef(), mMatrix.GetXAxisRef());
	retVal.SetZAxis(Permute<VecElem::X1, VecElem::Z2, VecElem::Z1, VecElem::W1>(tmp, mMatrix.GetYAxisRef()));
	retVal.SetWAxis(mMatrix.GetWAxisRef());
	return retVal;
}

__forceinline Mat44V_Out RECON_VEC_CALLCONV RotateAround(Vec3V_In origin, Mat44V_In rotatorsMatrix, Mat44V_In rotationMatrix)
{
	Mat44V newMat(rotatorsMatrix);
	newMat.Translate(-origin);
	newMat *= rotationMatrix;
	newMat.Translate(origin);
	return newMat;
}

__forceinline Mat44V_Out RECON_VEC_CALLCONV MakePerspectiveMatrix(ScalarV_In vFOV, ScalarV_In vAspectRatio, ScalarV_In vNearClip, ScalarV_In vFarClip)
{
	ScalarV yScale(ScalarV(I_ONE) / Tan(vFOV * ScalarV(I_HALF)));
	ScalarV xScale(yScale / vAspectRatio);

	return Mat44V(	Vec4V(xScale,			Vec3V(I_ZERO)),
					Vec4V(ScalarV(I_ZERO),	yScale,												Vec2V(I_ZERO)),
					Vec4V(Vec2V(I_ZERO),	vFarClip / (vFarClip - vNearClip),					ScalarV(I_ONE)),
					Vec4V(Vec2V(I_ZERO),	(-vNearClip * vFarClip) / (vFarClip - vNearClip),	ScalarV(I_ZERO)));
}

__forceinline Mat44V_Out RECON_VEC_CALLCONV MakeOrthographicMatrix(ScalarV_In vWidth, ScalarV_In vHeight, ScalarV_In vNear, ScalarV_In vFar)
{
	return Mat44V(	Vec4V(ScalarV(I_TWO) / vWidth,	Vec3V(I_ZERO)),
					Vec4V(ScalarV(I_ZERO),			ScalarV(I_TWO) / vHeight,			Vec2V(I_ZERO)),
					Vec4V(Vec2V(I_ZERO),			ScalarV(I_ONE) / (vFar - vNear),	ScalarV(I_ZERO)),
					Vec4V(Vec2V(I_ZERO),			-vNear / (vFar - vNear),			ScalarV(I_ONE)));
}

__forceinline Mat44V_Out RECON_VEC_CALLCONV MakeTextureMatrixOffset(ScalarV_In vWidth, ScalarV_In vHeight)
{
	return Mat44V(Vec4V(ScalarV(I_HALF),								Vec3V(I_ZERO)),
				  Vec4V(ScalarV(I_ZERO),								ScalarV(I_NEG_HALF),							Vec2V(I_ZERO)),
				  Vec4V(I_Z_AXIS),
				  Vec4V(ScalarV(I_HALF) + (ScalarV(I_HALF) / vWidth),	ScalarV(I_HALF) + (ScalarV(I_HALF) / vHeight),	ScalarV(I_ZERO), ScalarV(I_ONE)));
}
#endif //SSE_AVAILABLE


__forceinline VecCmpResult::VecCmpResult(const bool& bX)
{
	m_VectorMask = Vec4V(VectorIsNotEqualInt(VectorSetConstant<FloatToIntRep::Zero>(), VectorSet(bX, 0, 0, 0)));
}
__forceinline VecCmpResult::VecCmpResult(const bool& bX, const bool& bY)
{
	m_VectorMask = Vec4V(VectorIsNotEqualInt(VectorSetConstant<FloatToIntRep::Zero>(), VectorSet(bX, bY, 0, 0)));
}
__forceinline VecCmpResult::VecCmpResult(const bool& bX, const bool& bY, const bool& bZ)
{
	m_VectorMask = Vec4V(VectorIsNotEqualInt(VectorSetConstant<FloatToIntRep::Zero>(), VectorSet(bX, bY, bZ, 0)));
}
__forceinline VecCmpResult::VecCmpResult(const bool& bX, const bool& bY, const bool& bZ, const bool bW)
{
	m_VectorMask = Vec4V(VectorIsNotEqualInt(VectorSetConstant<FloatToIntRep::Zero>(), VectorSet(bX, bY, bZ, bW)));
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

__forceinline s32 VecCmpResult::GetResultMask() const { return SignMask(m_VectorMask); }
__forceinline VecCmpResult::operator s32 () const { return GetResultMask(); }

__forceinline bool VecCmpResult::IsTrueAny() const { return GetResultMask() != 0; }
__forceinline bool VecCmpResult::IsTrueAll() const { return (GetResultMask() & ((1 << (s32)VecElem::X) | (1 << (s32)VecElem::Y) | (1 << (s32)VecElem::Z) | (1 << (s32)VecElem::W))) != 0; }

template<VecElem index>
__forceinline bool VecCmpResult::IsTrue() const { static_assert(index > = VecElem::X && index <= VecElem::W, "Invalid VecCmpResult Index!"); return (GetResultMask() & (1 << index)) != 0; }

template<VecElem index0, VecElem index1>
__forceinline bool VecCmpResult::IsTrue() const
{
	static_assert((index0 >= VecElem::X && index0 <= VecElem::W) && \
				  (index1 >= VecElem::X && index1 <= VecElem::W), "Invalid VecCmpResult Index!");
	static_assert(index0 != index1, "index0 & index1 Cannot Be The Same Index");
	return (GetResultMask() & ((1 << index0) | (1 << index1))) != 0;
}

template<VecElem index0, VecElem index1, VecElem index2>
__forceinline bool VecCmpResult::IsTrue() const
{
	static_assert((index0 >= VecElem::X && index0 <= VecElem::W) && \
				  (index1 >= VecElem::X && index1 <= VecElem::W) && \
				  (index2 >= VecElem::X && index2 <= VecElem::W), "Invalid VecCmpResult Index!");
	static_assert(index0 != index1 && index0 != index2 && index1 != index2, "index0 & index1 & index2 Cannot Be The Same Index");
	return (GetResultMask() & ((1 << index0) | (1 << index1) | (1 << index2))) != 0;
}
