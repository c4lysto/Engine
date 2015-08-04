
//#if SSE_AVAILABLE

// Initialization Operations:

template<u32 val>
FORCEINLINE Vector_Out VectorSetConstant()
{
	return VEC_INT_TO_FLOAT(_mm_set1_epi32((u32)val));
}

template<> FORCEINLINE Vector_Out VectorSetConstant<0>() { return _mm_setzero_ps(); }

template<u32 xVal, u32 yVal, u32 zVal, u32 wVal>
FORCEINLINE Vector_Out VectorSetConstant()
{
	return VEC_INT_TO_FLOAT(_mm_setr_epi32((u32)xVal, (u32)yVal, (u32)zVal, (u32)wVal));
}

FORCEINLINE Vector_Out VectorSet(const float& fVal)
{
	return _mm_set1_ps(fVal);
}

FORCEINLINE Vector_Out VectorSet(const float& fX, const float& fY, const float& fZ, const float& fW)
{
	return _mm_setr_ps(fX, fY, fZ, fW);
}

FORCEINLINE Vector_Out VectorSet(const int& iVal)
{
	return VEC_INT_TO_FLOAT(_mm_set1_epi32(iVal));
}

FORCEINLINE Vector_Out VectorSet(const int& iX, const int& iY, const int& iZ, const int& iW)
{
	return VEC_INT_TO_FLOAT(_mm_setr_epi32(iX, iY, iZ, iW));
}

// Used to load Aligned Data
FORCEINLINE Vector_Out VectorLoad(const float* const alignedFloat4Ptr)
{
	Assert(((((u64)alignedFloat4Ptr) & 15) == 0), "VectorLoad - Float Pointer MUST be 16-byte aligned!");
	return _mm_load_ps(alignedFloat4Ptr);
}

// Used to load Unaligned Data
FORCEINLINE Vector_Out VectorLoadU(const float* const unalignedFloat4Ptr)
{
	return _mm_loadu_ps(unalignedFloat4Ptr);
}

// Used to store in Aligned Data
FORCEINLINE void VectorStore(Vector_In lhs, float* alignedFloat4Ptr)
{
	Assert(((((u64)alignedFloat4Ptr) & 15) == 0), "VectorStore - Float Pointer MUST be 16-byte aligned!");
	_mm_store_ps(alignedFloat4Ptr, lhs);
}

// Used to store in Unaligned Data
FORCEINLINE void VectorStoreU(Vector_In lhs, float* unalignedFloat4Ptr)
{
	_mm_storeu_ps(unalignedFloat4Ptr, lhs);
}

template<VecElem index>
FORCEINLINE float VectorExtractFloat(Vector_In vec)
{
	CompileTimeAssert(index >= VecElem::X && index <= VecElem::W, "Invalid Permute X-Index. Must be between X & W!");
	return _mm_cvtss_f32(VectorPermute<index, index, index, index>(vec));
}

template<> FORCEINLINE float VectorExtractFloat<VecElem::X>(Vector_In vec) {return _mm_cvtss_f32(vec);}

template<VecElem index>
FORCEINLINE int VectorExtractInt(Vector_In vec)
{
	CompileTimeAssert(index >= VecElem::X && index <= VecElem::W, "Invalid Permute X-Index. Must be between X & W!");
	return _mm_extract_epi32(VEC_FLOAT_TO_INT(vec), (int)index);
}


// Permute Operations:

#define SHUFFLE_MASKED(index) ((int)(index) & 0x3)
#define PERM_SHUFFLE(x, y, z, w) (_MM_FSHUFFLE(SHUFFLE_MASKED(x), SHUFFLE_MASKED(y), SHUFFLE_MASKED(z), SHUFFLE_MASKED(w)))
#define BLEND_MASK(x, y, z, w) ((x) | ((y)<<1) | ((z)<<2) | ((w)<<3))

template<VecElem splat>
FORCEINLINE Vector_Out VectorSplat(Vector_In vec)
{
	CompileTimeAssert(splat >= VecElem::X && splat <= VecElem::W, "Invalid Splat Index. Must be between VecElem::X & VecElem::W!");
	return _mm_shuffle_ps(vec, vec, PERM_SHUFFLE(splat, splat, splat, splat));
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
FORCEINLINE Vector_Out VectorPermute(Vector_In vec)
{
	CompileTimeAssert(pX >= VecElem::X && pX <= VecElem::W, "Invalid Permute X-Index. Must be between VecElem::X & VecElem::W!");
	CompileTimeAssert(pY >= VecElem::X && pY <= VecElem::W, "Invalid Permute Y-Index. Must be between VecElem::X & VecElem::W!");
	CompileTimeAssert(pZ >= VecElem::X && pZ <= VecElem::W, "Invalid Permute Z-Index. Must be between VecElem::X & VecElem::W!");
	CompileTimeAssert(pW >= VecElem::X && pW <= VecElem::W, "Invalid Permute W-Index. Must be between VecElem::X & VecElem::W!");
	return _mm_shuffle_ps(vec, vec, PERM_SHUFFLE(pX, pY, pZ, pW));
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
FORCEINLINE Vector_Out VectorPermute(Vector_In lhs, Vector_In rhs)
{
	CompileTimeAssert((pX >= VecElem::X1 && pX <= VecElem::W1) || (pX >= VecElem::X2 && pX <= VecElem::W2), "Invalid Permute X-Index. Must be between VecElem::X1 & VecElem::W2!");
	CompileTimeAssert((pY >= VecElem::X1 && pY <= VecElem::W1) || (pY >= VecElem::X2 && pY <= VecElem::W2), "Invalid Permute Y-Index. Must be between VecElem::X1 & VecElem::W2!");
	CompileTimeAssert((pZ >= VecElem::X1 && pZ <= VecElem::W1) || (pZ >= VecElem::X2 && pZ <= VecElem::W2), "Invalid Permute Z-Index. Must be between VecElem::X1 & VecElem::W2!");
	CompileTimeAssert((pW >= VecElem::X1 && pW <= VecElem::W1) || (pW >= VecElem::X2 && pW <= VecElem::W2), "Invalid Permute W-Index. Must be between VecElem::X1 & VecElem::W2!");

	CompileTimeAssert(!((pX < VecElem::X2 && pY < VecElem::X2 && pZ < VecElem::X2 && pW < VecElem::X2) ||
		(pX > VecElem::W1 && pY > VecElem::W1 && pZ > VecElem::W1 && pW > VecElem::W1)), "All Components Are From The Same Vector, Use 'Permute(Vector_In vec)' Instead");

	if((pX < VecElem::X2 && pY < VecElem::X2) &&			// Permute<Vec1, Vec1, Vec2, Vec2>
	   (pZ > VecElem::W1 && pW > VecElem::W1))
	{
		return _mm_shuffle_ps(lhs, rhs, PERM_SHUFFLE(pX, pY, pZ, pW));
	}
	else if((pX > VecElem::W1 && pY > VecElem::W1) &&		// Permute<Vec2, Vec2, Vec1, Vec1>
			(pZ < VecElem::X2 && pW < VecElem::X2))
	{
		return _mm_shuffle_ps(rhs, lhs, PERM_SHUFFLE(pX, pY, pZ, pW));
	}
	else if((pX < VecElem::X2 && pY < VecElem::X2) &&		// Permute<Vec1, Vec1, Vec1, Vec2>
			(pZ < VecElem::X2 && pW > VecElem::W1))
	{
		Vector tmpRhs = _mm_shuffle_ps(lhs, rhs, PERM_SHUFFLE(pZ, pZ, pW, pW));
		return _mm_shuffle_ps(lhs, tmpRhs, PERM_SHUFFLE(pX, pY, 0, 2));
	}
	else if((pX > VecElem::W1 && pY > VecElem::W1) &&		// Permute<Vec2, Vec2, Vec2, Vec1>
			(pZ > VecElem::W1 && pW < VecElem::X2))
	{
		Vector tmpRhs = _mm_shuffle_ps(rhs, lhs, PERM_SHUFFLE(pZ, pZ, pW, pW));
		return _mm_shuffle_ps(rhs, tmpRhs, PERM_SHUFFLE(pX, pY, 0, 2));
	}
	else if((pX < VecElem::X2 && pY > VecElem::W1) &&		// Permute<Vec1, Vec2, Vec2, Vec2>
			(pZ > VecElem::W1 && pW > VecElem::W1))
	{
		Vector tmpLhs = _mm_shuffle_ps(lhs, rhs, PERM_SHUFFLE(pX, pX, pY, pY));
		return _mm_shuffle_ps(tmpLhs, rhs, PERM_SHUFFLE(0, 2, pZ, pW));
	}
	else if((pX > VecElem::W1 && pY < VecElem::X2) &&		// Permute<Vec2, Vec1, Vec1, Vec1>
			(pZ < VecElem::X2 && pW < VecElem::X2))
	{
		Vector tmpLhs = _mm_shuffle_ps(rhs, lhs, PERM_SHUFFLE(pX, pX, pY, pY));
		return _mm_shuffle_ps(tmpLhs, lhs, PERM_SHUFFLE(0, 2, pZ, pW));
	}
	else if((pX < VecElem::X2 && pZ < VecElem::X2) &&		// Permute<Vec1, Vec2, Vec1, Vec2>
			(pY > VecElem::W1 && pW > VecElem::W1))
	{
		Vector tmpLhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pZ), (VecElem)SHUFFLE_MASKED(pZ)>(lhs);
		Vector tmpRhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pW), (VecElem)SHUFFLE_MASKED(pW)>(rhs);
		return _mm_blend_ps(tmpLhs, tmpRhs, BLEND_MASK(0, 1, 0, 1));
	}
	else if((pX > VecElem::W1 && pZ > VecElem::W1) &&		// Permute<Vec2, Vec1, Vec2, Vec1>
			(pY < VecElem::X2 && pW < VecElem::X2))
	{
		Vector tmpLhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pZ), (VecElem)SHUFFLE_MASKED(pZ)>(rhs);
		Vector tmpRhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pW), (VecElem)SHUFFLE_MASKED(pW)>(lhs);
		return _mm_blend_ps(tmpLhs, tmpRhs, BLEND_MASK(0, 1, 0, 1));
	}
	else if((pX < VecElem::X2 && pW < VecElem::X2) &&		// Permute<Vec1, Vec2, Vec2, Vec1>
			(pY > VecElem::W1 && pZ > VecElem::W1))
	{
		Vector tmpLhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pW), (VecElem)SHUFFLE_MASKED(pW)>(lhs);
		Vector tmpRhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pZ), (VecElem)SHUFFLE_MASKED(pZ)>(rhs);
		return _mm_blend_ps(tmpLhs, tmpRhs, BLEND_MASK(0, 1, 1, 0));
	}
	else if((pX > VecElem::W1 && pW > VecElem::W1) &&		// Permute<Vec2, Vec1, Vec1, Vec2>
			(pY < VecElem::X2 && pZ < VecElem::X2))
	{
		Vector tmpLhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pW), (VecElem)SHUFFLE_MASKED(pW)>(rhs);
		Vector tmpRhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pZ), (VecElem)SHUFFLE_MASKED(pZ)>(lhs);
		return _mm_blend_ps(tmpLhs, tmpRhs, BLEND_MASK(0, 1, 1, 0));
	}
	else if((pX < VecElem::X2 && pY > VecElem::W1) &&		// Permute<Vec1, Vec2, Vec1, Vec1>
			(pZ < VecElem::X2 && pW < VecElem::X2))
	{
		Vector tmpLhs = _mm_shuffle_ps(lhs, rhs, PERM_SHUFFLE(pX, pX, pY, pY));
		return _mm_shuffle_ps(tmpLhs, lhs, PERM_SHUFFLE(0, 2, pZ, pW));
	}
	else if((pX > VecElem::W1 && pY < VecElem::X2) &&		// Permute<Vec2, Vec1, Vec2, Vec2>
			(pZ > VecElem::W1 && pW > VecElem::W1))
	{
		Vector tmpLhs = _mm_shuffle_ps(rhs, lhs, PERM_SHUFFLE(pX, pX, pY, pY));
		return _mm_shuffle_ps(tmpLhs, rhs, PERM_SHUFFLE(0, 2, pZ, pW));
	}
	else if((pX < VecElem::X2 && pY < VecElem::X2) &&		// Permute<Vec1, Vec1, Vec2, Vec1>
			(pZ > VecElem::W1 && pW < VecElem::X2))
	{
		Vector tmpRhs = _mm_shuffle_ps(rhs, lhs, PERM_SHUFFLE(pZ, pZ, pW, pW));
		return _mm_shuffle_ps(lhs, tmpRhs, PERM_SHUFFLE(pX, pY, 0, 2));
	}
	else if((pX > VecElem::W1 && pY > VecElem::W1) &&		// Permute<Vec2, Vec2, Vec1, Vec2>
			(pZ < VecElem::X2 && pW > VecElem::W1))
	{
		Vector tmpRhs = _mm_shuffle_ps(lhs, rhs, PERM_SHUFFLE(pZ, pZ, pW, pW));
		return _mm_shuffle_ps(rhs, tmpRhs, PERM_SHUFFLE(pX, pY, 0, 2));
	}
	else
	{
		//CompileTimeAssert(false, "Unhandled Permute Case!");
		return _mm_setzero_ps();
	}
}

#undef PERM_SHUFFLE
#undef SHUFFLE_MASKED

template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 0, 0)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z1, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 1, 0, 0)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 1, 1, 0)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 1, 0, 1)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 1, 0)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z2, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 1, 1)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 0, 1)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 0, 0)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 1, 0)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z2, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 1, 1)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 0, 1)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 0, 1, 0)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 0, 1, 1)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 0, 0, 1)); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X1, VecElem::X2, VecElem::Y1, VecElem::Y2>(Vector_In lhs, Vector_In rhs) { return _mm_unpacklo_ps(lhs, rhs); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X2, VecElem::X1, VecElem::Y2, VecElem::Y1>(Vector_In lhs, Vector_In rhs) { return _mm_unpacklo_ps(rhs, lhs); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::Z1, VecElem::Z2, VecElem::W1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_unpackhi_ps(lhs, rhs); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::Z2, VecElem::Z1, VecElem::W2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_unpackhi_ps(rhs, lhs); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::Z2, VecElem::W2, VecElem::Z1, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_movehl_ps(lhs, rhs); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::Z1, VecElem::W1, VecElem::Z2, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_movehl_ps(rhs, lhs); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(Vector_In lhs, Vector_In rhs) { return _mm_movelh_ps(lhs, rhs); }
template<> FORCEINLINE Vector_Out VectorPermute<VecElem::X2, VecElem::Y2, VecElem::X1, VecElem::Y1>(Vector_In lhs, Vector_In rhs) { return _mm_movelh_ps(rhs, lhs); }

#undef BLEND_MASK


// Conversion Operations:

FORCEINLINE Vector_Out VectorIntToFloat(Vector_In vec)
{
	return _mm_cvtepi32_ps(VEC_FLOAT_TO_INT(vec));
}

FORCEINLINE Vector_Out VectorFloatToInt(Vector_In vec)
{
	return VEC_INT_TO_FLOAT(_mm_cvttps_epi32(vec));
}


// Arithmetic Operations: 

FORCEINLINE Vector_Out VectorAdd(Vector_In lhs, Vector_In rhs)
{
	return _mm_add_ps(lhs, rhs);
}

//FORCEINLINE Vector_Out operator+(Vector_In lhs, Vector_In rhs)
//{
//	return VectorAdd(lhs, rhs);
//}

FORCEINLINE Vector_Out VectorAddInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_add_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

// Operates in the following manner:
// {lhs.x+lhs.y, lhs.z+lhs.w, rhs.x+rhs.y, rhs.z+rhs.w}
FORCEINLINE Vector_Out VectorHAdd(Vector_In lhs, Vector_In rhs)
{
	return _mm_hadd_ps(lhs, rhs);
}

FORCEINLINE Vector_Out VectorSubtract(Vector_In lhs, Vector_In rhs)
{
	return _mm_sub_ps(lhs, rhs);
}

//FORCEINLINE Vector_Out operator-(Vector_In lhs, Vector_In rhs)
//{
//	return VectorSubtract(lhs, rhs);
//}

FORCEINLINE Vector_Out VectorSubtractInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_sub_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

// Operates in the following manner:
// {lhs.x-lhs.y, lhs.z-lhs.w, rhs.x-rhs.y, rhs.z-rhs.w}
FORCEINLINE Vector_Out VectorHSub(Vector_In lhs, Vector_In rhs)
{
	return _mm_hsub_ps(lhs, rhs);
}

FORCEINLINE Vector_Out VectorMultiply(Vector_In lhs, Vector_In rhs)
{
	return _mm_mul_ps(lhs, rhs);
}

//FORCEINLINE Vector_Out operator*(Vector_In lhs, Vector_In rhs)
//{
//	return VectorMultiply(lhs, rhs);
//}

FORCEINLINE Vector_Out VectorMultiplyInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_mul_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

FORCEINLINE Vector_Out VectorDivide(Vector_In lhs, Vector_In rhs)
{
	return _mm_div_ps(lhs, rhs);
}

//FORCEINLINE Vector_Out operator/(Vector_In lhs, Vector_In rhs)
//{
//	return VectorDivide(lhs, rhs);
//}

FORCEINLINE Vector_Out VectorNegate(Vector_In vec)
{
	// Toggle The Sign Bit
	return _mm_xor_ps(vec, VEC_INT_TO_FLOAT(_mm_set1_epi32(0x80000000)));
}

//FORCEINLINE Vector_Out operator-(Vector_In vec)
//{
//	return VectorNegate(vec);
//}

FORCEINLINE Vector_Out VectorAbs(Vector_In vec)
{
	return _mm_and_ps(vec, VEC_INT_TO_FLOAT(_mm_set1_epi32(0x7FFFFFFF)));
}

FORCEINLINE Vector_Out VectorSqrt(Vector_In vec)
{
	return _mm_sqrt_ps(vec);
}

FORCEINLINE Vector_Out VectorRSqrt(Vector_In vec)
{
	return _mm_rsqrt_ps(vec);
}

FORCEINLINE Vector_Out VectorRecip(Vector_In vec)
{
	return _mm_rcp_ps(vec);
}

FORCEINLINE Vector_Out VectorFloor(Vector_In vec)
{
	return _mm_round_ps(vec, _MM_FROUND_TO_NEG_INF);
}

FORCEINLINE Vector_Out VectorCeil(Vector_In vec)
{
	return _mm_round_ps(vec, _MM_FROUND_TO_POS_INF);
}

FORCEINLINE Vector_Out VectorTrunc(Vector_In vec)
{
	return _mm_round_ps(vec, _MM_FROUND_TO_ZERO);
}

FORCEINLINE Vector_Out VectorRound(Vector_In vec)
{
	return _mm_round_ps(vec, _MM_FROUND_TO_NEAREST_INT);
}

FORCEINLINE Vector_Out VectorSign(Vector_In vec)
{
	return VectorOr(VectorAnd(vec, VectorSet((int)0x80000000)), VectorSet(1.0f));
}

inline Vector_Out VectorLog2(Vector_In vec)
{
#if RECON_USE_SVML
	return _mm_log2_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector rawBiased = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	Vector trailing = VectorAnd(vec, VectorSetConstant<0x007FFFFF>());
	Vector isExponentZero = VectorIsEqualInt(VectorSetConstant<(u32)FloatToIntRep::Zero>(), rawBiased);

	// Compute exponent and significand for normals.
	Vector biased = VectorRightShift(rawBiased, 23);
	Vector exponentNor = VectorSubtractInt(biased, VectorSetConstant<(u32)127>());
	Vector trailingNor = trailing;

	// Compute exponent and significand for subnormals.
	Vector leading = VectorBitscanForward(trailing);
	Vector shift = VectorSubtractInt(VectorSetConstant<(u32)23>(), leading);
	Vector exponentSub = VectorSubtractInt(VectorSetConstant<(u32)-126>(), shift);
	Vector trailingSub = VectorLeftShift4(trailing, shift);
	trailingSub = VectorAnd(trailingSub, VectorSetConstant<0x007FFFFF>());

	Vector select0 = VectorAnd(isExponentZero, exponentSub);
	Vector select1 = VectorAndNot(exponentNor, isExponentZero);
	Vector e = VectorOr(select0, select1);

	select0 = VectorAnd(isExponentZero, trailingSub);
	select1 = VectorAndNot(trailingNor, isExponentZero);
	Vector t = VectorOr(select0, select1);

	// Compute the approximation.
	Vector tmp = VectorOr(VectorSetConstant<(u32)FloatToIntRep::One>(), t);
	Vector y = VectorSubtract(tmp, VectorSetConstant<(u32)FloatToIntRep::One>());

	Vector log2 = VectorMultiply(VectorSetConstant<0xBC2D4F59>(), y);
	log2 = VectorAdd(VectorSetConstant<0x3D6A1405>(), log2);
	log2 = VectorMultiply(log2, y);
	log2 = VectorAdd(VectorSetConstant<0xBE153261>(), log2);
	log2 = VectorMultiply(log2, y);
	log2 = VectorAdd(VectorSetConstant<0x3E7E8E61>(), log2);
	log2 = VectorMultiply(log2, y);
	log2 = VectorAdd(VectorSetConstant<0xBEB359DE>(), log2);
	log2 = VectorMultiply(log2, y);
	log2 = VectorAdd(VectorSetConstant<0x3EF571D2>(), log2);
	log2 = VectorMultiply(log2, y);
	log2 = VectorAdd(VectorSetConstant<0xBF38A351>(), log2);
	log2 = VectorMultiply(log2, y);
	log2 = VectorAdd(VectorSetConstant<0x3FB8AA2A>(), log2);
	log2 = VectorMultiply(log2, y);
	log2 = VectorAdd(log2, VectorIntToFloat(e));

	Vector isInfinite = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Abs_Mask>());
	isInfinite = VectorIsEqualInt(isInfinite, VectorSetConstant<(u32)FloatToIntRep::Infinity>());

	Vector isGreaterZero = VectorIsGreaterThanInt(vec, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	Vector isNotFinite = VectorIsGreaterThanInt(vec, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	Vector isPositive = VectorAndNot(isGreaterZero, isNotFinite);

	Vector isZero = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Abs_Mask>());
	isZero = VectorIsEqualInt(isZero, VectorSetConstant<(u32)FloatToIntRep::Zero>());

	Vector t0 = VectorAnd(vec, VectorSetConstant<0x007FFFFF>());
	Vector t1 = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	t0 = VectorIsEqualInt(t0, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	t1 = VectorIsEqualInt(t1, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	Vector isNaN = VectorAndNot(t1, t0);

	select0 = VectorAnd(isInfinite, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	select1 = VectorAndNot(log2, isInfinite);
	Vector result = VectorOr(select0, select1);

	select0 = VectorAnd(isZero, VectorSetConstant<(u32)FloatToIntRep::Neg_Infinity>());
	select1 = VectorAndNot(VectorSetConstant<(u32)FloatToIntRep::Neg_NaN>(), isZero);
	tmp = VectorOr(select0, select1);

	select0 = VectorAnd(isPositive, result);
	select1 = VectorAndNot(tmp, isPositive);
	result = VectorOr(select0, select1);

	select0 = VectorAnd(isNaN, VectorSetConstant<(u32)FloatToIntRep::NaN>());
	select1 = VectorAndNot(result, isNaN);
	return VectorOr(select0, select1);
#endif // RECON_USE_SVML
}

inline Vector_Out VectorExp2(Vector_In vec)
{
#if RECON_USE_SVML
	return _mm_exp2_ps(vec);
#else
	Vector itrunc = VectorFloatToInt(vec);
	Vector ftrunc = VectorIntToFloat(itrunc);
	Vector y = VectorSubtract(vec, ftrunc);
	Vector poly = VectorMultiply(VectorSetConstant<0xB7364261>(), y);
	poly = VectorAdd(VectorSetConstant<0x391AA7D7>(), poly);
	poly = VectorMultiply(poly, y);
	poly = VectorAdd(VectorSetConstant<0xBAAE1854>(), poly);
	poly = VectorMultiply(poly, y);
	poly = VectorAdd(VectorSetConstant<0x3C1D8C54>(), poly);
	poly = VectorMultiply(poly, y);
	poly = VectorAdd(VectorSetConstant<0xBD6357CA>(), poly);
	poly = VectorMultiply(poly, y);
	poly = VectorAdd(VectorSetConstant<0x3E75FDED>(), poly);
	poly = VectorMultiply(poly, y);
	poly = VectorAdd(VectorSetConstant<0xBF317218>(), poly);
	poly = VectorMultiply(poly, y);
	poly = VectorAdd(VectorSetConstant<(u32)FloatToIntRep::One>(), poly);

	Vector biased = VectorAddInt(itrunc, VectorSetConstant<127>());
	biased = VectorLeftShift(biased, 23);
	Vector result0 = VectorDivide(biased, poly);

	biased = VectorAddInt(itrunc, VectorSetConstant<253>());
	biased = VectorLeftShift(biased, 23);
	Vector result1 = VectorDivide(biased, poly);
	result1 = VectorMultiply(VectorSetConstant<0x00800000>(), result1);

	Vector comp = VectorIsLessThanInt(vec, VectorSetConstant<0x43000000>());
	Vector select0 = VectorAnd(comp, result0);
	Vector select1 = VectorAndNot(VectorSetConstant<(u32)FloatToIntRep::Infinity>(), comp);
	Vector result2 = VectorOr(select0, select1);

	comp = VectorIsLessThanInt(itrunc, VectorSetConstant<(u32)-126>());
	select1 = VectorAnd(comp, result1);
	select0 = VectorAndNot(result0, comp);
	Vector result3 = VectorOr(select0, select1);

	comp = VectorIsLessThanInt(vec, VectorSetConstant<0xC3160000>());
	select0 = VectorAnd(comp, result3);
	select1 = VectorAndNot(VectorSetConstant<(u32)FloatToIntRep::Zero>(), comp);
	Vector result4 = VectorOr(select0, select1);

	Vector sign = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Sign_Bit>());
	comp = VectorIsEqualInt(sign, VectorSetConstant<(u32)FloatToIntRep::Sign_Bit>());
	select0 = VectorAnd(comp, result4);
	select1 = VectorAndNot(result2, comp);
	Vector result5 = VectorOr(select0, select1);

	Vector t0 = VectorAnd(vec, VectorSetConstant<0x007FFFFF>());
	Vector t1 = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	t0 = VectorIsEqualInt(t0, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	t1 = VectorIsEqualInt(t1, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	Vector isNaN = VectorAndNot(t1, t0);

	select0 = VectorAnd(isNaN, VectorSetConstant<(u32)FloatToIntRep::NaN>());
	select1 = VectorAndNot(result5, isNaN);
	Vector vResult = VectorOr(select0, select1);

	return vResult;
#endif // RECON_USE_SVML
}


// Trigonometry Operations:

inline Vector_Out VectorSin(Vector_In vec)
{
#if RECON_USE_SVML
	return _mm_sin_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	// Force the value within the bounds of pi
	Vector x = VectorMultiply(vec, VectorSetConstant<(u32)FloatToIntRep::One_Over_Two_Pi>());
	x = VectorRound(x);
	x = VectorMultiply(x, VectorSetConstant<(u32)FloatToIntRep::Two_Pi>());
	x = VectorSubtract(vec, x);

	// Map in [-pi/2,pi/2] with sin(y) = sin(x).
	Vector sign = VectorAnd(x, VectorSetConstant<(u32)FloatToIntRep::Sign_Bit>());
	Vector c = VectorOr(VectorSetConstant<(u32)FloatToIntRep::Pi>(), sign);  // pi when x >= 0, -pi when x < 0
	Vector absx = VectorAndNot(x, sign);  // |x|
	Vector rflx = VectorSubtract(c, x);
	Vector comp = VectorIsLessThanOrEqual(absx, VectorSetConstant<(u32)FloatToIntRep::Half_Pi>());
	Vector select0 = VectorAnd(comp, x);
	Vector select1 = VectorAndNot(rflx, comp);
	x = VectorOr(select0, select1);

	Vector x2 = VectorMultiply(x, x);

	// Compute polynomial approximation
	Vector Result = VectorMultiply(VectorSetConstant<0xB2CD365B>(), x2);

	Result = VectorAdd(Result, VectorSetConstant<0x3638B88E>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0xB9500bF1>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0x3C088886>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0xBE2AAAAB>());
	Result = VectorMultiply(Result, x2);
	Result = VectorAdd(Result, VectorSetConstant<(u32)FloatToIntRep::One>());
	Result = VectorMultiply(Result, x);
	return Result;
#endif // RECON_USE_SVML
}

inline Vector_Out VectorASin(Vector_In vec)
{
#if RECON_USE_SVML
	return _mm_asin_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector nonnegative = VectorIsGreaterThanOrEqual(vec, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	Vector x = VectorAbs(vec);

	// Compute (1-|V|), clamp to zero to avoid sqrt of negative number.
	Vector oneMValue = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::One>(), x);
	Vector clampOneMValue = VectorMax(VectorSetConstant<(u32)FloatToIntRep::Zero>(), oneMValue);
	Vector root = VectorSqrt(clampOneMValue);  // sqrt(1-|vec|)

	// Compute polynomial approximation
	Vector t0 = VectorMultiply(VectorSetConstant<0x3CFD10F8>(), x);

	t0 = VectorAdd(t0, VectorSetConstant<0xBC8BFC66>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0x3BDA90C5>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0xBAA57A2C>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0x3FC90FDA>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0xBE5BBFCA>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0x3DB63A9E>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0xBD4D8392>());
	t0 = VectorMultiply(t0, root);

	Vector t1 = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::Pi>(), t0);
	t0 = VectorAnd(nonnegative, t0);
	t1 = VectorAndNot(t1, nonnegative);
	t0 = VectorOr(t0, t1);
	t0 = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::Half_Pi>(), t0);
	return t0;
#endif // RECON_USE_SVML
}

inline Vector_Out VectorCos(Vector_In vec)
{
#if RECON_USE_SVML
	return _mm_cos_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	// Force the value within the bounds of pi
	Vector x = VectorMultiply(vec, VectorSetConstant<(u32)FloatToIntRep::One_Over_Two_Pi>());
	x = VectorRound(x);
	x = VectorMultiply(x, VectorSetConstant<(u32)FloatToIntRep::Two_Pi>());
	x = VectorSubtract(vec, x);

	// Map in [-pi/2,pi/2] with cos(y) = sign*cos(x).
	Vector sign = VectorAnd(x, VectorSetConstant<(u32)FloatToIntRep::Sign_Bit>());
	Vector c = VectorOr(VectorSetConstant<(u32)FloatToIntRep::Pi>(), sign);  // pi when x >= 0, -pi when x < 0
	Vector absx = VectorAndNot(x, sign);  // |x|
	Vector rflx = VectorSubtract(c, x);
	Vector comp = VectorIsLessThanOrEqual(absx, VectorSetConstant<(u32)FloatToIntRep::Half_Pi>());
	Vector select0 = VectorAnd(comp, x);
	Vector select1 = VectorAndNot(rflx, comp);
	x = VectorOr(select0, select1);
	select0 = VectorAnd(comp, VectorSetConstant<(u32)FloatToIntRep::One>());
	select1 = VectorAndNot(VectorSetConstant<(u32)FloatToIntRep::Neg_One>(), comp);
	sign = VectorOr(select0, select1);

	Vector x2 = VectorMultiply(x, x);

	// Compute polynomial approximation
	Vector Result = VectorMultiply(VectorSetConstant<0xB48BDD11>(), x2);

	Result = VectorAdd(Result, VectorSetConstant<0x37CFB4C2>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0xBAB609AA>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0x3D2AAAA3>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<(u32)FloatToIntRep::Neg_Half>());
	Result = VectorMultiply(Result, x2);
	Result = VectorAdd(Result, VectorSetConstant<(u32)FloatToIntRep::One>());
	Result = VectorMultiply(Result, sign);
	return Result;
#endif // RECON_USE_SVML
}

inline Vector_Out VectorACos(Vector_In vec)
{
#if RECON_USE_SVML
	return _mm_acos_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector nonnegative = VectorIsGreaterThanOrEqual(vec, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	Vector x = VectorAbs(vec);

	// Compute (1-|vec|), clamp to zero to avoid sqrt of negative number.
	Vector oneMValue = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::One>(), x);
	Vector clampOneMValue = VectorMax(VectorSetConstant<(u32)FloatToIntRep::Zero>(), oneMValue);
	Vector root = VectorSqrt(clampOneMValue);  // sqrt(1-|vec|)

	// Compute polynomial approximation
	Vector t0 = VectorMultiply(VectorSetConstant<0xBAA57A2C>(), x);

	t0 = VectorAdd(t0, VectorSetConstant<0x3BDA90C5>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0xBC8BFC66>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0x3CFD10F8>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0xBD4D8392>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0x3DB63A9E>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0xBE5BBFCA>());
	t0 = VectorMultiply(t0, x);

	t0 = VectorAdd(t0, VectorSetConstant<0x3FC90FDA>());
	t0 = VectorMultiply(t0, root);

	Vector t1 = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::Pi>(), t0);
	t0 = VectorAnd(nonnegative, t0);
	t1 = VectorAndNot(t1, nonnegative);
	t0 = VectorOr(t0, t1);
	return t0;
#endif // RECON_USE_SVML
}

inline Vector_Out VectorTan(Vector_In vec)
{
#if RECON_USE_SVML
	return _mm_tan_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector VA = VectorMultiply(vec, VectorSetConstant<0x3F22F983>());

	VA = VectorRound(VA);

	Vector VC = VectorSubtract(vec, VectorMultiply(VA, VectorSetConstant<0x3FC90FDB>()));

	Vector VB = VectorAbs(VA);

	VC = VectorSubtract(VC, VectorMultiply(VA, VectorSetConstant<0x2E85A309>()));

	VB = VectorFloatToInt(VB);

	Vector VC2 = VectorMultiply(VC, VC);	

	Vector VBIsEven = VectorAnd(VB, VectorSetConstant<0x1>());
	VBIsEven = VectorIsEqualInt(VBIsEven, VectorSetConstant<(u32)FloatToIntRep::Zero>());

	Vector N = VectorAdd(VectorMultiply(VC2, VectorSetConstant<0xB795D5B9>()), VectorSetConstant<0x3B607415>());
	Vector D = VectorAdd(VectorMultiply(VC2, VectorSetConstant<0x3505BBA8>()), VectorSetConstant<0xB9A37B25>());
	N = VectorAdd(VectorMultiply(VC2, N), VectorSetConstant<0xBE0895AF>());
	D = VectorAdd(VectorMultiply(VC2, D), VectorSetConstant<0x3CD23CF5>());
	N = VectorMultiply(VC2, N);
	D = VectorAdd(VectorMultiply(VC2, D), VectorSetConstant<0xBEEEF582>());
	N = VectorAdd(VectorMultiply(VC, N), VC);

	Vector VCNearZeroLE = VectorIsLessThanOrEqual(VC, VectorSetConstant<0x39800000>());
	Vector VCNearZeroGE = VectorIsLessThanOrEqual(VectorSetConstant<0xB9800000>(), VC);
	Vector VCNearZero = VectorAnd(VCNearZeroLE, VCNearZeroGE);

	D = VectorAdd(VectorMultiply(VC2, D), VectorSetConstant<(u32)FloatToIntRep::One>());

	N = VectorSelectTF(VC, N, VCNearZero);
	D = VectorSelectTF(VectorSetConstant<(u32)FloatToIntRep::One>(), D, VCNearZero);

	Vector R0 = VectorNegate(N);
	Vector R1 = VectorDivide(N, D);
	R0 = VectorDivide(D, R0);

	Vector VIsZero = VectorIsEqual(vec, VectorSetConstant<(u32)FloatToIntRep::Zero>());

	Vector Result = VectorSelectTF(R1, R0, VBIsEven);

	Result = VectorSelectTF(VectorSetConstant<(u32)FloatToIntRep::Zero>(), Result, VIsZero);

	return Result;
#endif // RECON_USE_SVML
}

inline Vector_Out VectorATan(Vector_In vec)
{
#if RECON_USE_SVML
	_mm_atan_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector absV = VectorAbs(vec);
	Vector invV = VectorDivide(VectorSetConstant<(u32)FloatToIntRep::One>(), vec);
	Vector comp = VectorIsGreaterThan(vec, VectorSetConstant<(u32)FloatToIntRep::One>());
	Vector select0 = VectorAnd(comp, VectorSetConstant<(u32)FloatToIntRep::One>());
	Vector select1 = VectorAndNot(VectorSetConstant<(u32)FloatToIntRep::Neg_One>(), comp);
	Vector sign = VectorOr(select0, select1);
	comp = VectorIsLessThanOrEqual(absV, VectorSetConstant<(u32)FloatToIntRep::One>());
	select0 = VectorAnd(comp, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	select1 = VectorAndNot(sign, comp);
	sign = VectorOr(select0, select1);
	select0 = VectorAnd(comp, vec);
	select1 = VectorAndNot(invV, comp);
	Vector x = VectorOr(select0, select1);

	Vector x2 = VectorMultiply(x, x);

	// Compute polynomial approximation
	Vector Result = VectorMultiply(VectorSetConstant<0x3B3BD74A>(), x2);

	Result = VectorAdd(Result, VectorSetConstant<0xBC846E02>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0x3D2FC1FE>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0xBD9A3174>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0x3DDA3D83>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0xBE117FC7>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0x3E4CBBE5>());
	Result = VectorMultiply(Result, x2);

	Result = VectorAdd(Result, VectorSetConstant<0xBEAAAA6C>());
	Result = VectorMultiply(Result, x2);
	Result = VectorAdd(Result, VectorSetConstant<(u32)FloatToIntRep::One>());
	Result = VectorMultiply(Result, x);
	Vector result1 = VectorMultiply(sign, VectorSetConstant<(u32)FloatToIntRep::Half_Pi>());
	result1 = VectorSubtract(result1, Result);

	comp = VectorIsEqual(sign, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	select0 = VectorAnd(comp, Result);
	select1 = VectorAndNot(result1, comp);
	Result = VectorOr(select0, select1);
	return Result;
#endif // RECON_USE_SVML
}

// NOTE: Performs Sin/Cos of Vec.x
// Returns: Vector(Sin(), Cos(), Sin(), Cos());
inline Vector_Out VectorSinCos(Vector_In vec)
{
#if RECON_USE_SVML
	return _mm_sincos_ps(vec);
#else
	Vector vecX = VectorSplat<VecElem::X>(vec);
	return VectorSin(VectorAdd(vec, VectorSetConstant<(u32)FloatToIntRep::Zero, (u32)FloatToIntRep::Half_Pi, (u32)FloatToIntRep::Zero, (u32)FloatToIntRep::Half_Pi>()));
#endif // RECON_USE_SVML
}


// Logical Operations:

FORCEINLINE Vector_Out VectorAnd(Vector_In lhs, Vector_In rhs)
{
	return _mm_and_ps(lhs, rhs);
}

//FORCEINLINE Vector_Out operator&(Vector_In lhs, Vector_In rhs)
//{
//	return VectorAnd(lhs, rhs);
//}

FORCEINLINE Vector_Out VectorAndNot(Vector_In lhs, Vector_In rhs)
{
	return _mm_andnot_ps(rhs, lhs);
}

FORCEINLINE Vector_Out VectorNot(Vector_In vec)
{
	return _mm_xor_ps(vec, VEC_INT_TO_FLOAT(_mm_set1_epi32(0xFFFFFFFF)));
}

//FORCEINLINE Vector_Out operator~(Vector_In vec)
//{
//	return VectorNot(vec);
//}

FORCEINLINE Vector_Out VectorOr(Vector_In lhs, Vector_In rhs)
{
	return _mm_or_ps(lhs, rhs);
}

//FORCEINLINE Vector_Out operator|(Vector_In lhs, Vector_In rhs)
//{
//	return VectorOr(lhs, rhs);
//}

FORCEINLINE Vector_Out VectorXOr(Vector_In lhs, Vector_In rhs)
{
	return _mm_xor_ps(lhs, rhs);
}

//FORCEINLINE Vector_Out operator^(Vector_In lhs, Vector_In rhs)
//{
//	return VectorXOr(lhs, rhs);
//}

FORCEINLINE Vector_Out VectorLeftShift(Vector_In vec, int nCount)
{
	return VEC_INT_TO_FLOAT(_mm_slli_epi32(VEC_FLOAT_TO_INT(vec), nCount));
}

//FORCEINLINE Vector_Out operator<<(Vector_In vec, int nCount)
//{
//	return VectorLeftShift(vec, nCount);
//}

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
inline Vector_Out VectorLeftShift4(Vector_In vec, Vector_In shiftCount)
{
	Vector shift = VectorSplat<VecElem::X>(shiftCount);
	Vector xShift = VEC_INT_TO_FLOAT(_mm_sll_epi32(VEC_FLOAT_TO_INT(vec), VEC_FLOAT_TO_INT(shift)));

	shift = VectorSplat<VecElem::Y>(shiftCount);
	Vector yShift = VEC_INT_TO_FLOAT(_mm_sll_epi32(VEC_FLOAT_TO_INT(vec), VEC_FLOAT_TO_INT(shift)));

	shift = VectorSplat<VecElem::Z>(shiftCount);
	Vector zShift = VEC_INT_TO_FLOAT(_mm_sll_epi32(VEC_FLOAT_TO_INT(vec), VEC_FLOAT_TO_INT(shift)));

	shift = VectorSplat<VecElem::W>(shiftCount);
	Vector wShift = VEC_INT_TO_FLOAT(_mm_sll_epi32(VEC_FLOAT_TO_INT(vec), VEC_FLOAT_TO_INT(shift)));

	Vector xy = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(xShift, yShift);
	Vector zw = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(zShift, wShift);
	return VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W2>(xy, zw);
}

FORCEINLINE Vector_Out VectorRightShift(Vector_In vec, int nCount)
{
	return VEC_INT_TO_FLOAT(_mm_srli_epi32(VEC_FLOAT_TO_INT(vec), nCount));
}

//FORCEINLINE Vector_Out operator>>(Vector_In vec, int nCount)
//{
//	return VectorRightShift(vec, nCount);
//}

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
inline Vector_Out VectorRightShift4(Vector_In vec, Vector_In shiftCount)
{
	Vector shift = VectorSplat<VecElem::X>(shiftCount);
	Vector xShift = VEC_INT_TO_FLOAT(_mm_srl_epi32(VEC_FLOAT_TO_INT(vec), VEC_FLOAT_TO_INT(shift)));

	shift = VectorSplat<VecElem::Y>(shiftCount);
	Vector yShift = VEC_INT_TO_FLOAT(_mm_srl_epi32(VEC_FLOAT_TO_INT(vec), VEC_FLOAT_TO_INT(shift)));

	shift = VectorSplat<VecElem::Z>(shiftCount);
	Vector zShift = VEC_INT_TO_FLOAT(_mm_srl_epi32(VEC_FLOAT_TO_INT(vec), VEC_FLOAT_TO_INT(shift)));

	shift = VectorSplat<VecElem::W>(shiftCount);
	Vector wShift = VEC_INT_TO_FLOAT(_mm_srl_epi32(VEC_FLOAT_TO_INT(vec), VEC_FLOAT_TO_INT(shift)));

	Vector xy = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(xShift, yShift);
	Vector zw = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(zShift, wShift);
	return VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W2>(xy, zw);
}


// Comparison Functions:

// Floating Point Comparisons:
#define CMP_MASK_X (0x1)
#define CMP_MASK_XY (0x3)
#define CMP_MASK_XYZ (0x7)
#define CMP_MASK_XYZW (0xF)

#define VEC_CMP_DEFBASE_IMPL(name, intrinsic) \
	FORCEINLINE Vector_Out Vector##name (Vector_In lhs, Vector_In rhs) \
	{ \
		return intrinsic (lhs, rhs); \
	}

#define VEC_CMP_DEF(name, nameExt) \
	FORCEINLINE bool Vector##name##nameExt (Vector_In lhs, Vector_In rhs) \
	{ \
		return ( _mm_movemask_ps( Vector##name (lhs, rhs) ) & CMP_MASK_##nameExt ) == CMP_MASK_##nameExt ; \
	}

#define VEC_CMP_DEFBASE(name, intrinsic)  VEC_CMP_DEFBASE_IMPL(name, intrinsic)
#define VEC_CMP1_DEF(name) VEC_CMP_DEF(name, X)
#define VEC_CMP2_DEF(name) VEC_CMP_DEF(name, XY)
#define VEC_CMP3_DEF(name) VEC_CMP_DEF(name, XYZ)
#define VEC_CMP4_DEF(name) VEC_CMP_DEF(name, XYZW)

#define VEC_CMP_DEF_ALL(name, intrinsic)  \
			VEC_CMP_DEFBASE(name, intrinsic) \
			VEC_CMP1_DEF(name) \
			VEC_CMP2_DEF(name) \
			VEC_CMP3_DEF(name) \
			VEC_CMP4_DEF(name)

VEC_CMP_DEF_ALL(IsEqual, _mm_cmpeq_ps);
VEC_CMP_DEF_ALL(IsNotEqual, _mm_cmpneq_ps);
VEC_CMP_DEF_ALL(IsGreaterThan, _mm_cmpgt_ps);
VEC_CMP_DEF_ALL(IsGreaterThanOrEqual, _mm_cmpge_ps);
VEC_CMP_DEF_ALL(IsLessThan, _mm_cmplt_ps);
VEC_CMP_DEF_ALL(IsLessThanOrEqual, _mm_cmple_ps);


// Integer Comparisons:
// Redefine VEC_CMP_DEF & VEC_CMP_DEFBASE for integer operations
#undef VEC_CMP_DEFBASE_IMPL
#define VEC_CMP_DEFBASE_IMPL(name, intrinsic) \
	FORCEINLINE Vector_Out Vector##name (Vector_In lhs, Vector_In rhs) \
{ \
	return VEC_INT_TO_FLOAT(intrinsic(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs))); \
}

#undef VEC_CMP_DEF
#define VEC_CMP_DEF(name, nameExt) \
	FORCEINLINE bool Vector##name##nameExt (Vector_In lhs, Vector_In rhs) \
	{ \
	return ( _mm_movemask_ps( Vector##name (lhs, rhs) ) == CMP_MASK_##nameExt ); \
	}

VEC_CMP_DEF_ALL(IsEqualInt, _mm_cmpeq_epi32);
VEC_CMP_DEF_ALL(IsGreaterThanInt, _mm_cmpgt_epi32);
VEC_CMP_DEF_ALL(IsLessThanInt, _mm_cmplt_epi32);

FORCEINLINE Vector_Out VectorIsNotEqualInt(Vector_In lhs, Vector_In rhs)
{
	return VectorNot(VectorIsEqualInt(lhs, rhs));
}

FORCEINLINE bool VectorIsNotEqualIntX(Vector_In lhs, Vector_In rhs)
{
	return (_mm_movemask_ps(VectorIsNotEqualInt(lhs, rhs))&CMP_MASK_X) == CMP_MASK_X;
}

FORCEINLINE bool VectorIsNotEqualIntXY(Vector_In lhs, Vector_In rhs)
{
	return (_mm_movemask_ps(VectorIsNotEqualInt(lhs, rhs))&CMP_MASK_XY) == CMP_MASK_XY;
}

FORCEINLINE bool VectorIsNotEqualIntXYZ(Vector_In lhs, Vector_In rhs)
{
	return (_mm_movemask_ps(VectorIsNotEqualInt(lhs, rhs))&CMP_MASK_XYZ) == CMP_MASK_XYZ;
}

FORCEINLINE bool VectorIsNotEqualIntXYZW(Vector_In lhs, Vector_In rhs)
{
	return (_mm_movemask_ps(VectorIsNotEqualInt(lhs, rhs))&CMP_MASK_XYZW) == CMP_MASK_XYZW;
}

#define VEC_CMP_OREQUAL_INT_DEFBASE(name, cmp) \
	FORCEINLINE Vector_Out Vector##name (Vector_In lhs, Vector_In rhs) \
	{ \
		return VectorOr( Vector##name (lhs, rhs), VectorIsEqualInt(lhs, rhs)); \
	}

#define VEC_CMP_OREQUAL_INT_DEF(name, nameExt, cmp) \
	FORCEINLINE bool Vector##name##nameExt (Vector_In lhs, Vector_In rhs) \
	{ \
		return Vector##cmp##nameExt (lhs, rhs) || VectorIsEqualInt##nameExt (lhs, rhs); \
	}

#define VEC_CMP_OREQUAL_INT_DEF_ALL(name, cmp1) \
	VEC_CMP_OREQUAL_INT_DEFBASE(name, cmp1) \
	VEC_CMP_OREQUAL_INT_DEF(name, X, cmp1) \
	VEC_CMP_OREQUAL_INT_DEF(name, XY, cmp1) \
	VEC_CMP_OREQUAL_INT_DEF(name, XYZ, cmp1) \
	VEC_CMP_OREQUAL_INT_DEF(name, XYZW, cmp1)

VEC_CMP_OREQUAL_INT_DEF_ALL(IsGreaterThanOrEqualInt, IsGreaterThanInt);
VEC_CMP_OREQUAL_INT_DEF_ALL(IsLessThanOrEqualInt, IsLessThanInt);

#undef VEC_CMP_OREQUAL_INT_DEF_ALL
#undef VEC_CMP_OREQUAL_INT_DEF
#undef VEC_CMP_OREQUAL_INT_DEFBASE

//FORCEINLINE bool IsLessThanEqualIntAll(Vector_In lhs, Vector_In rhs)
//{
//	return IsLessThanIntAll(lhs, rhs) || IsEqualIntAll(lhs, rhs);
//}

#undef VEC_CMP_DEF_ALL
#undef VEC_CMP4_DEF
#undef VEC_CMP3_DEF
#undef VEC_CMP2_DEF
#undef VEC_CMP1_DEF
#undef VEC_CMP_DEFBASE
#undef VEC_CMP_DEF
#undef VEC_CMP_DEFBASE_IMPL


// Misc Operations

FORCEINLINE s32 VectorSignMask(Vector_In vec)
{
	return _mm_movemask_ps(vec);
}

FORCEINLINE Vector_Out VectorMin(Vector_In lhs, Vector_In rhs)
{
	return _mm_min_ps(lhs, rhs);
}

FORCEINLINE Vector_Out VectorMinInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_min_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

FORCEINLINE Vector_Out VectorMax(Vector_In lhs, Vector_In rhs)
{
	return _mm_max_ps(lhs, rhs);
}

FORCEINLINE Vector_Out VectorMaxInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_max_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

FORCEINLINE Vector_Out VectorSelectTF(Vector_In lhs, Vector_In rhs, Vector_In condition)
{
	return _mm_blendv_ps(rhs, lhs, condition);
}

inline Vector_Out VectorBitscanForward(Vector_In vec)
{
	// Modified from "DirectXMathVector.inl"

	Vector c = VectorIsGreaterThanInt(vec, VectorSetConstant<0xFFFF>());   // c = (v > 0xFFFF)
	Vector b = VectorRightShift(c, 31);              // b = (c ? 1 : 0)
	Vector r = VectorLeftShift(b, 4);               // r = (b << 4)
	vec = VectorRightShift4(vec, r);              // v = (v >> r)

	c = VectorIsGreaterThanInt(vec, VectorSetConstant<0xFF>());   // c = (v > 0xFF)
	b = VectorRightShift(c, 31);              // b = (c ? 1 : 0)
	Vector s = VectorLeftShift(b, 3);               // s = (b << 3)
	vec = VectorRightShift4(vec, s);              // v = (v >> s)
	r = VectorOr(r, s);                 // r = (r | s)

	c = VectorIsGreaterThanInt(vec, VectorSetConstant<0xF>());   // c = (v > 0xF)
	b = VectorRightShift(c, 31);              // b = (c ? 1 : 0)
	s = VectorLeftShift(b, 2);               // s = (b << 2)
	vec = VectorRightShift4(vec, s);              // v = (v >> s)
	r = VectorOr(r, s);                 // r = (r | s)

	c = VectorIsGreaterThanInt(vec, VectorSetConstant<0x3>());   // c = (v > 0x3)
	b = VectorRightShift(c, 31);              // b = (c ? 1 : 0)
	s = VectorLeftShift(b, 1);               // s = (b << 1)
	vec = VectorRightShift4(vec, s);              // v = (v >> s)
	r = VectorOr(r, s);                 // r = (r | s)

	s = VectorRightShift(vec, 1);
	r = VectorOr(r, s);

	return r;
}


// Vector Math Operations:

FORCEINLINE Vector_Out VectorCrossProduct(Vector_In lhs, Vector_In rhs)
{
	Vector vec1 = VectorPermute<VecElem::Y, VecElem::Z, VecElem::X, VecElem::X>(lhs);
	Vector vec2 = VectorPermute<VecElem::Z, VecElem::X, VecElem::Y, VecElem::X>(rhs);
	Vector vec3 = VectorMultiply(vec1, vec2);

	vec1 = VectorPermute<VecElem::Z, VecElem::X, VecElem::Y, VecElem::X>(lhs);
	vec2 = VectorPermute<VecElem::Y, VecElem::Z, VecElem::X, VecElem::X>(rhs);

	return VectorSubtract(vec3, VectorMultiply(vec1, vec2));
}

FORCEINLINE float VectorDot2(Vector_In lhs, Vector_In rhs)
{
	Vector dp = VectorMultiply(lhs, rhs);
	return VectorExtractFloat<VecElem::X>(VectorHAdd(dp, dp));
}

FORCEINLINE float VectorDot3(Vector_In lhs, Vector_In rhs)
{
	Vector rhsWZero = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::X2>(rhs, VectorSet(0.0f));
	Vector dp = VectorMultiply(lhs, rhsWZero);
	Vector result = VectorHAdd(dp, dp);
	return VectorExtractFloat<VecElem::X>(VectorHAdd(result, result));
}

FORCEINLINE float VectorDot4(Vector_In lhs, Vector_In rhs)
{
	Vector dp = VectorMultiply(lhs, rhs);
	Vector result = VectorHAdd(dp, dp);
	return VectorExtractFloat<VecElem::X>(VectorHAdd(result, result));
}

//#endif // SSE_AVAILABLE