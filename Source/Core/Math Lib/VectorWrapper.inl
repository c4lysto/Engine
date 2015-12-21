

#define RECON_USE_SVML (0)

#define VEC_INT_TO_FLOAT _mm_castsi128_ps
#define VEC_FLOAT_TO_INT _mm_castps_si128

// Initialization Operations:

template<u32 val>
__forceinline Vector_Out RECON_VEC_CALLCONV VectorSetConstant()
{
	return VEC_INT_TO_FLOAT(_mm_set1_epi32((u32)val));
}

template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorSetConstant<0>() { return _mm_setzero_ps(); }

template<u32 xVal, u32 yVal, u32 zVal, u32 wVal>
__forceinline Vector_Out RECON_VEC_CALLCONV VectorSetConstant()
{
	return VEC_INT_TO_FLOAT(_mm_setr_epi32((u32)xVal, (u32)yVal, (u32)zVal, (u32)wVal));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorSet(const f32& fVal)
{
	return _mm_set1_ps(fVal);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorSet(const f32& fX, const f32& fY, const f32& fZ, const f32& fW)
{
	return _mm_setr_ps(fX, fY, fZ, fW);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorSet(const s32& iVal)
{
	return VEC_INT_TO_FLOAT(_mm_set1_epi32(iVal));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorSet(const s32& iX, const s32& iY, const s32& iZ, const s32& iW)
{
	return VEC_INT_TO_FLOAT(_mm_setr_epi32(iX, iY, iZ, iW));
}

// Used to load Aligned Data
__forceinline Vector_Out RECON_VEC_CALLCONV VectorLoad(const f32* const alignedFloat4Ptr)
{
	Assertf(((((u64)alignedFloat4Ptr) & 15) == 0), "VectorLoad - Float Pointer MUST be 16-byte aligned!");
	return _mm_load_ps(alignedFloat4Ptr);
}

// Used to load Unaligned Data
__forceinline Vector_Out RECON_VEC_CALLCONV VectorLoadU(const f32* const unalignedFloat4Ptr)
{
	return _mm_loadu_ps(unalignedFloat4Ptr);
}

// Used to store in Aligned Data
__forceinline void RECON_VEC_CALLCONV VectorStore(Vector_In lhs, f32* alignedFloat4Ptr)
{
	Assertf(((((u64)alignedFloat4Ptr) & 15) == 0), "VectorStore - Float Pointer MUST be 16-byte aligned!");
	_mm_store_ps(alignedFloat4Ptr, lhs);
}

// Used to store in Unaligned Data
__forceinline void RECON_VEC_CALLCONV VectorStoreU(Vector_In lhs, f32* unalignedFloat4Ptr)
{
	_mm_storeu_ps(unalignedFloat4Ptr, lhs);
}

template<VecElem index>
__forceinline f32 RECON_VEC_CALLCONV VectorExtractFloat(Vector_In vec)
{
	static_assert(index >= VecElem::X && index <= VecElem::W, "Invalid Permute X-Index. Must be between X & W!");
	return _mm_cvtss_f32(VectorPermute<index, index, index, index>(vec));
}

template<> __forceinline f32 RECON_VEC_CALLCONV VectorExtractFloat<VecElem::X>(Vector_In vec) { return _mm_cvtss_f32(vec); }

template<VecElem index>
__forceinline s32 RECON_VEC_CALLCONV VectorExtractInt(Vector_In vec)
{
	static_assert(index >= VecElem::X && index <= VecElem::W, "Invalid Permute X-Index. Must be between X & W!");
	return _mm_extract_epi32(VEC_FLOAT_TO_INT(vec), (s32)index);
}


// Permute Operations:

#define SHUFFLE_MASKED(index) ((s32)(index) & 0x3)
#define PERM_SHUFFLE(x, y, z, w) (_MM_FSHUFFLE(SHUFFLE_MASKED(x), SHUFFLE_MASKED(y), SHUFFLE_MASKED(z), SHUFFLE_MASKED(w)))
#define BLEND_MASK(x, y, z, w) ((x) | ((y)<<1) | ((z)<<2) | ((w)<<3))

template<VecElem splat>
__forceinline Vector_Out RECON_VEC_CALLCONV VectorSplat(Vector_In vec)
{
	static_assert(splat >= VecElem::X && splat <= VecElem::W, "Invalid Splat Index. Must be between VecElem::X & VecElem::W!");
	return _mm_shuffle_ps(vec, vec, PERM_SHUFFLE(splat, splat, splat, splat));
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
__forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute(Vector_In vec)
{
	static_assert(pX >= VecElem::X && pX <= VecElem::W, "Invalid Permute X-Index. Must be between VecElem::X & VecElem::W!");
	static_assert(pY >= VecElem::X && pY <= VecElem::W, "Invalid Permute Y-Index. Must be between VecElem::X & VecElem::W!");
	static_assert(pZ >= VecElem::X && pZ <= VecElem::W, "Invalid Permute Z-Index. Must be between VecElem::X & VecElem::W!");
	static_assert(pW >= VecElem::X && pW <= VecElem::W, "Invalid Permute W-Index. Must be between VecElem::X & VecElem::W!");
	return _mm_shuffle_ps(vec, vec, PERM_SHUFFLE(pX, pY, pZ, pW));
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
__forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute(Vector_In lhs, Vector_In rhs)
{
	static_assert((pX >= VecElem::X1 && pX <= VecElem::W1) || (pX >= VecElem::X2 && pX <= VecElem::W2), "Invalid Permute X-Index. Must be between VecElem::X1 & VecElem::W2!");
	static_assert((pY >= VecElem::X1 && pY <= VecElem::W1) || (pY >= VecElem::X2 && pY <= VecElem::W2), "Invalid Permute Y-Index. Must be between VecElem::X1 & VecElem::W2!");
	static_assert((pZ >= VecElem::X1 && pZ <= VecElem::W1) || (pZ >= VecElem::X2 && pZ <= VecElem::W2), "Invalid Permute Z-Index. Must be between VecElem::X1 & VecElem::W2!");
	static_assert((pW >= VecElem::X1 && pW <= VecElem::W1) || (pW >= VecElem::X2 && pW <= VecElem::W2), "Invalid Permute W-Index. Must be between VecElem::X1 & VecElem::W2!");

	static_assert(!((pX < VecElem::X2 && pY < VecElem::X2 && pZ < VecElem::X2 && pW < VecElem::X2) ||
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
		//static_assert(false, "Unhandled Permute Case!");
		return _mm_setzero_ps();
	}
}

#undef PERM_SHUFFLE
#undef SHUFFLE_MASKED

template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 0, 0)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z1, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 1, 0, 0)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 1, 1, 0)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 1, 0, 1)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 1, 0)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z2, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 1, 1)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 0, 1)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 0, 0)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 1, 0)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z2, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 1, 1)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 0, 1)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 0, 1, 0)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 0, 1, 1)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 0, 0, 1)); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::X2, VecElem::Y1, VecElem::Y2>(Vector_In lhs, Vector_In rhs) { return _mm_unpacklo_ps(lhs, rhs); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::X1, VecElem::Y2, VecElem::Y1>(Vector_In lhs, Vector_In rhs) { return _mm_unpacklo_ps(rhs, lhs); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::Z1, VecElem::Z2, VecElem::W1, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_unpackhi_ps(lhs, rhs); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::Z2, VecElem::Z1, VecElem::W2, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_unpackhi_ps(rhs, lhs); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::Z2, VecElem::W2, VecElem::Z1, VecElem::W1>(Vector_In lhs, Vector_In rhs) { return _mm_movehl_ps(lhs, rhs); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::Z1, VecElem::W1, VecElem::Z2, VecElem::W2>(Vector_In lhs, Vector_In rhs) { return _mm_movehl_ps(rhs, lhs); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(Vector_In lhs, Vector_In rhs) { return _mm_movelh_ps(lhs, rhs); }
template<> __forceinline Vector_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y2, VecElem::X1, VecElem::Y1>(Vector_In lhs, Vector_In rhs) { return _mm_movelh_ps(rhs, lhs); }

#undef BLEND_MASK


// Conversion Operations:

__forceinline Vector_Out RECON_VEC_CALLCONV VectorIntToFloat(Vector_In vec)
{
	return _mm_cvtepi32_ps(VEC_FLOAT_TO_INT(vec));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorFloatToInt(Vector_In vec)
{
	return VEC_INT_TO_FLOAT(_mm_cvttps_epi32(vec));
}


// Arithmetic Operations: 

__forceinline Vector_Out RECON_VEC_CALLCONV VectorAdd(Vector_In lhs, Vector_In rhs)
{
	return _mm_add_ps(lhs, rhs);
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator+(Vector_In lhs, Vector_In rhs)
//{
//	return VectorAdd(lhs, rhs);
//}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorAddInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_add_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

// Operates in the following manner:
// {lhs.x+lhs.y, lhs.z+lhs.w, rhs.x+rhs.y, rhs.z+rhs.w}
__forceinline Vector_Out RECON_VEC_CALLCONV VectorHAdd(Vector_In lhs, Vector_In rhs)
{
	return _mm_hadd_ps(lhs, rhs);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorSubtract(Vector_In lhs, Vector_In rhs)
{
	return _mm_sub_ps(lhs, rhs);
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator-(Vector_In lhs, Vector_In rhs)
//{
//	return VectorSubtract(lhs, rhs);
//}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorSubtractInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_sub_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

// Operates in the following manner:
// {lhs.x-lhs.y, lhs.z-lhs.w, rhs.x-rhs.y, rhs.z-rhs.w}
__forceinline Vector_Out RECON_VEC_CALLCONV VectorHSub(Vector_In lhs, Vector_In rhs)
{
	return _mm_hsub_ps(lhs, rhs);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMultiply(Vector_In lhs, Vector_In rhs)
{
	return _mm_mul_ps(lhs, rhs);
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator*(Vector_In lhs, Vector_In rhs)
//{
//	return VectorMultiply(lhs, rhs);
//}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMultiplyInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_mul_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorDivide(Vector_In lhs, Vector_In rhs)
{
	return _mm_div_ps(lhs, rhs);
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator/(Vector_In lhs, Vector_In rhs)
//{
//	return VectorDivide(lhs, rhs);
//}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorNegate(Vector_In vec)
{
	return _mm_xor_ps(vec, VEC_INT_TO_FLOAT(_mm_set1_epi32(0x80000000)));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorNegateInt(Vector_In vec)
{
	return VectorSubtractInt(VectorSetConstant<0>(), vec);
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator-(Vector_In vec)
//{
//	return VectorNegate(vec);
//}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorAbs(Vector_In vec)
{
	return _mm_and_ps(vec, VEC_INT_TO_FLOAT(_mm_set1_epi32(0x7FFFFFFF)));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorAbsInt(Vector_In vec)
{
	return VEC_INT_TO_FLOAT(_mm_abs_epi32(VEC_FLOAT_TO_INT(vec)));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorSqrt(Vector_In vec)
{
	return _mm_sqrt_ps(vec);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorRSqrt(Vector_In vec)
{
	return _mm_rsqrt_ps(vec);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorRecip(Vector_In vec)
{
	return _mm_rcp_ps(vec);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorFloor(Vector_In vec)
{
	return _mm_round_ps(vec, _MM_FROUND_TO_NEG_INF);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorCeil(Vector_In vec)
{
	return _mm_round_ps(vec, _MM_FROUND_TO_POS_INF);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorTrunc(Vector_In vec)
{
	return _mm_round_ps(vec, _MM_FROUND_TO_ZERO);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorRound(Vector_In vec)
{
	return _mm_round_ps(vec, _MM_FROUND_TO_NEAREST_INT);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorSign(Vector_In vec)
{
	return VectorAnd(VectorIsNotEqual(vec, VectorSetConstant<0>()), VectorOr(VectorAnd(vec, VectorSet((s32)0x80000000)), VectorSet(1.0f)));
}

inline Vector_Out RECON_VEC_CALLCONV VectorLog2(Vector_In vec)
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

inline Vector_Out RECON_VEC_CALLCONV VectorExp2(Vector_In vec)
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

inline Vector_Out RECON_VEC_CALLCONV VectorSin(Vector_In vec)
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

inline Vector_Out RECON_VEC_CALLCONV VectorASin(Vector_In vec)
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

inline Vector_Out RECON_VEC_CALLCONV VectorCos(Vector_In vec)
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

inline Vector_Out RECON_VEC_CALLCONV VectorACos(Vector_In vec)
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

inline Vector_Out RECON_VEC_CALLCONV VectorTan(Vector_In vec)
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

	N = VectorSelectTF(VCNearZero, VC, N);
	D = VectorSelectTF(VCNearZero, VectorSetConstant<(u32)FloatToIntRep::One>(), D);

	Vector R0 = VectorNegate(N);
	Vector R1 = VectorDivide(N, D);
	R0 = VectorDivide(D, R0);

	Vector VIsZero = VectorIsEqual(vec, VectorSetConstant<(u32)FloatToIntRep::Zero>());

	Vector Result = VectorSelectTF(VBIsEven, R1, R0);

	Result = VectorSelectTF(VIsZero, VectorSetConstant<(u32)FloatToIntRep::Zero>(), Result);

	return Result;
#endif // RECON_USE_SVML
}

inline Vector_Out RECON_VEC_CALLCONV VectorATan(Vector_In vec)
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
inline Vector_Out RECON_VEC_CALLCONV VectorSinCos(Vector_In vec)
{
#if RECON_USE_SVML
	return _mm_sincos_ps(vec);
#else
	Vector vecX = VectorSplat<VecElem::X>(vec);
	return VectorSin(VectorAdd(vec, VectorSetConstant<(u32)FloatToIntRep::Zero, (u32)FloatToIntRep::Half_Pi, (u32)FloatToIntRep::Zero, (u32)FloatToIntRep::Half_Pi>()));
#endif // RECON_USE_SVML
}


// Logical Operations:

__forceinline Vector_Out RECON_VEC_CALLCONV VectorAnd(Vector_In lhs, Vector_In rhs)
{
	return _mm_and_ps(lhs, rhs);
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator&(Vector_In lhs, Vector_In rhs)
//{
//	return VectorAnd(lhs, rhs);
//}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorAndNot(Vector_In lhs, Vector_In rhs)
{
	return _mm_andnot_ps(rhs, lhs);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorNot(Vector_In vec)
{
	return _mm_xor_ps(vec, VEC_INT_TO_FLOAT(_mm_set1_epi32(0xFFFFFFFF)));
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator~(Vector_In vec)
//{
//	return VectorNot(vec);
//}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorOr(Vector_In lhs, Vector_In rhs)
{
	return _mm_or_ps(lhs, rhs);
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator|(Vector_In lhs, Vector_In rhs)
//{
//	return VectorOr(lhs, rhs);
//}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorXOr(Vector_In lhs, Vector_In rhs)
{
	return _mm_xor_ps(lhs, rhs);
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator^(Vector_In lhs, Vector_In rhs)
//{
//	return VectorXOr(lhs, rhs);
//}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorLeftShift(Vector_In vec, s32 nCount)
{
	return VEC_INT_TO_FLOAT(_mm_slli_epi32(VEC_FLOAT_TO_INT(vec), nCount));
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator<<(Vector_In vec, s32 nCount)
//{
//	return VectorLeftShift(vec, nCount);
//}

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
inline Vector_Out RECON_VEC_CALLCONV VectorLeftShift4(Vector_In vec, Vector_In shiftCount)
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

__forceinline Vector_Out RECON_VEC_CALLCONV VectorRightShift(Vector_In vec, s32 nCount)
{
	return VEC_INT_TO_FLOAT(_mm_srli_epi32(VEC_FLOAT_TO_INT(vec), nCount));
}

//__forceinline Vector_Out RECON_VEC_CALLCONV operator>>(Vector_In vec, s32 nCount)
//{
//	return VectorRightShift(vec, nCount);
//}

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
inline Vector_Out RECON_VEC_CALLCONV VectorRightShift4(Vector_In vec, Vector_In shiftCount)
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
	__forceinline Vector_Out RECON_VEC_CALLCONV Vector##name(Vector_In lhs, Vector_In rhs) \
	{ \
		return intrinsic (lhs, rhs); \
	}

#define VEC_CMP_DEF(name, nameExt) \
	__forceinline bool RECON_VEC_CALLCONV Vector##name##nameExt(Vector_In lhs, Vector_In rhs) \
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
	__forceinline Vector_Out RECON_VEC_CALLCONV Vector##name(Vector_In lhs, Vector_In rhs) \
{ \
	return VEC_INT_TO_FLOAT(intrinsic(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs))); \
}

#undef VEC_CMP_DEF
#define VEC_CMP_DEF(name, nameExt) \
	__forceinline bool RECON_VEC_CALLCONV Vector##name##nameExt(Vector_In lhs, Vector_In rhs) \
	{ \
	return ( _mm_movemask_ps( Vector##name (lhs, rhs) ) == CMP_MASK_##nameExt ); \
	}

VEC_CMP_DEF_ALL(IsEqualInt, _mm_cmpeq_epi32);
VEC_CMP_DEF_ALL(IsGreaterThanInt, _mm_cmpgt_epi32);
VEC_CMP_DEF_ALL(IsLessThanInt, _mm_cmplt_epi32);

__forceinline Vector_Out RECON_VEC_CALLCONV VectorIsNotEqualInt(Vector_In lhs, Vector_In rhs)
{
	return VectorNot(VectorIsEqualInt(lhs, rhs));
}

__forceinline bool RECON_VEC_CALLCONV VectorIsNotEqualIntX(Vector_In lhs, Vector_In rhs)
{
	return (_mm_movemask_ps(VectorIsNotEqualInt(lhs, rhs))&CMP_MASK_X) == CMP_MASK_X;
}

__forceinline bool RECON_VEC_CALLCONV VectorIsNotEqualIntXY(Vector_In lhs, Vector_In rhs)
{
	return (_mm_movemask_ps(VectorIsNotEqualInt(lhs, rhs))&CMP_MASK_XY) == CMP_MASK_XY;
}

__forceinline bool RECON_VEC_CALLCONV VectorIsNotEqualIntXYZ(Vector_In lhs, Vector_In rhs)
{
	return (_mm_movemask_ps(VectorIsNotEqualInt(lhs, rhs))&CMP_MASK_XYZ) == CMP_MASK_XYZ;
}

__forceinline bool RECON_VEC_CALLCONV VectorIsNotEqualIntXYZW(Vector_In lhs, Vector_In rhs)
{
	return (_mm_movemask_ps(VectorIsNotEqualInt(lhs, rhs))&CMP_MASK_XYZW) == CMP_MASK_XYZW;
}

#define VEC_CMP_OREQUAL_INT_DEFBASE(name, cmp) \
	__forceinline Vector_Out RECON_VEC_CALLCONV Vector##name(Vector_In lhs, Vector_In rhs) \
	{ \
		return VectorOr( Vector##name (lhs, rhs), VectorIsEqualInt(lhs, rhs)); \
	}

#define VEC_CMP_OREQUAL_INT_DEF(name, nameExt, cmp) \
	__forceinline bool RECON_VEC_CALLCONV Vector##name##nameExt(Vector_In lhs, Vector_In rhs) \
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

//__forceinline bool IsLessThanEqualIntAll(Vector_In lhs, Vector_In rhs)
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

__forceinline s32 RECON_VEC_CALLCONV VectorMoveMask(Vector_In vec)
{
	return _mm_movemask_ps(vec);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMin(Vector_In lhs, Vector_In rhs)
{
	return _mm_min_ps(lhs, rhs);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMinInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_min_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMax(Vector_In lhs, Vector_In rhs)
{
	return _mm_max_ps(lhs, rhs);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMaxInt(Vector_In lhs, Vector_In rhs)
{
	return VEC_INT_TO_FLOAT(_mm_max_epi32(VEC_FLOAT_TO_INT(lhs), VEC_FLOAT_TO_INT(rhs)));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorClamp(Vector_In val, Vector_In minVal, Vector_In maxVal)
{
	return VectorMax(minVal, VectorMin(val, maxVal));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorClampInt(Vector_In val, Vector_In minVal, Vector_In maxVal)
{
	return VectorMaxInt(minVal, VectorMinInt(val, maxVal));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorSelectTF(Vector_In condition, Vector_In ifTrue, Vector_In ifFalse)
{
	return _mm_blendv_ps(ifFalse, ifTrue, condition);
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMinComponentV2(Vector_In vec)
{
	return VectorMin(VectorSplat<VecElem::X>(vec), VectorSplat<VecElem::Y>(vec));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMinComponentV3(Vector_In vec)
{
	Vector MinXY = VectorMin(vec, VectorSplat<VecElem::Y>(vec));
	return VectorSplat<VecElem::X>(VectorMin(MinXY, VectorSplat<VecElem::Z>(vec)));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMinComponentV4(Vector_In vec)
{
	Vector MinXZ_YW = VectorMin(vec, VectorPermute<VecElem::Z, VecElem::W, VecElem::Z, VecElem::W>(vec));
	return VectorSplat<VecElem::X>(VectorMin(MinXZ_YW, VectorSplat<VecElem::Y>(MinXZ_YW)));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMaxComponentV2(Vector_In vec)
{
	return VectorMax(VectorSplat<VecElem::X>(vec), VectorSplat<VecElem::Y>(vec));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMaxComponentV3(Vector_In vec)
{
	Vector MaxXY = VectorMax(vec, VectorSplat<VecElem::Y>(vec));
	return VectorSplat<VecElem::X>(VectorMax(MaxXY, VectorSplat<VecElem::Z>(vec)));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorMaxComponentV4(Vector_In vec)
{
	Vector MaxXZ_YW = VectorMax(vec, VectorPermute<VecElem::Z, VecElem::W, VecElem::Z, VecElem::W>(vec));
	return VectorSplat<VecElem::X>(VectorMax(MaxXZ_YW, VectorSplat<VecElem::Y>(MaxXZ_YW)));
}

inline Vector_Out RECON_VEC_CALLCONV VectorBitscanForward(Vector_In vec)
{
	// Modified from "DirectXMathVector.inl"

	Vector c = VectorIsGreaterThanInt(vec, VectorSetConstant<0xFFFF>());	// c = (v > 0xFFFF)
	Vector b = VectorRightShift(c, 31);										// b = (c ? 1 : 0)
	Vector r = VectorLeftShift(b, 4);										// r = (b << 4)
	Vector vecOut = VectorRightShift4(vec, r);										// v = (v >> r)

	c = VectorIsGreaterThanInt(vecOut, VectorSetConstant<0xFF>());	// c = (v > 0xFF)
	b = VectorRightShift(c, 31);								// b = (c ? 1 : 0)
	Vector s = VectorLeftShift(b, 3);							// s = (b << 3)
	vecOut = VectorRightShift4(vecOut, s);							// v = (v >> s)
	r = VectorOr(r, s);											// r = (r | s)

	c = VectorIsGreaterThanInt(vecOut, VectorSetConstant<0xF>());	// c = (v > 0xF)
	b = VectorRightShift(c, 31);								// b = (c ? 1 : 0)
	s = VectorLeftShift(b, 2);									// s = (b << 2)
	vecOut = VectorRightShift4(vecOut, s);							// v = (v >> s)
	r = VectorOr(r, s);											// r = (r | s)

	c = VectorIsGreaterThanInt(vecOut, VectorSetConstant<0x3>());  // c = (v > 0x3)
	b = VectorRightShift(c, 31);								// b = (c ? 1 : 0)
	s = VectorLeftShift(b, 1);									// s = (b << 1)
	vecOut = VectorRightShift4(vecOut, s);							// v = (v >> s)
	r = VectorOr(r, s);											// r = (r | s)

	s = VectorRightShift(vecOut, 1);
	r = VectorOr(r, s);

	return r;
}


// Vector Math Operations:

__forceinline Vector_Out RECON_VEC_CALLCONV VectorCrossProduct(Vector_In lhs, Vector_In rhs)
{
	Vector vec1 = VectorPermute<VecElem::Y, VecElem::Z, VecElem::X, VecElem::X>(lhs);
	Vector vec2 = VectorPermute<VecElem::Z, VecElem::X, VecElem::Y, VecElem::X>(rhs);
	Vector vec3 = VectorMultiply(vec1, vec2);

	vec1 = VectorPermute<VecElem::Z, VecElem::X, VecElem::Y, VecElem::X>(lhs);
	vec2 = VectorPermute<VecElem::Y, VecElem::Z, VecElem::X, VecElem::X>(rhs);

	return VectorSubtract(vec3, VectorMultiply(vec1, vec2));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorDotV2(Vector_In lhs, Vector_In rhs)
{
	Vector dp = VectorMultiply(lhs, rhs);
	return VectorSplat<VecElem::X>(VectorHAdd(dp, dp));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorDotV3(Vector_In lhs, Vector_In rhs)
{
	Vector rhsWZero = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::X2>(rhs, VectorSetConstant<0x0>());
	Vector dp = VectorMultiply(lhs, rhsWZero);
	Vector result = VectorHAdd(dp, dp);
	return VectorSplat<VecElem::X>(VectorHAdd(result, result));
}

__forceinline Vector_Out RECON_VEC_CALLCONV VectorDotV4(Vector_In lhs, Vector_In rhs)
{
	Vector dp = VectorMultiply(lhs, rhs);
	Vector result = VectorHAdd(dp, dp);
	return VectorSplat<VecElem::X>(VectorHAdd(result, result));
}

#undef VEC_INT_TO_FLOAT
#undef VEC_FLOAT_TO_INT
