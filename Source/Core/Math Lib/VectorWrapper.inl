

#define RECON_USE_SVML (0 && RECON_SSE_VECTOR_INTRIN)
#define RECON_EXTRACT_FROM_VEC_VIA_CAST (1)

#if RECON_SSE_VECTOR_INTRIN
#define VEC_S32_TO_F32 _mm_castsi128_ps
#define VEC_F32_TO_S32 _mm_castps_si128
#elif RECON_ARM_VECTOR_INTRIN
#define VEC_S32_TO_F32
#define VEC_F32_TO_S32
#endif // RECON_SSE_VECTOR_INTRIN

// Initialization Operations:

template<u32 val>
__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSetConstant()
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_set1_epi32((u32)val));
#elif RECON_ARM_VECTOR_INTRIN
	return vdupq_n_s32((s32)val);
#endif // RECON_SSE_VECTOR_INTRIN
}

template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorSetConstant<0>()
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_setzero_ps(); 
#elif RECON_ARM_VECTOR_INTRIN
	return vdupq_n_f32();
#endif // RECON_SSE_VECTOR_INTRIN
}

template<u32 xVal, u32 yVal, u32 zVal, u32 wVal>
__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSetConstant()
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_setr_epi32((u32)xVal, (u32)yVal, (u32)zVal, (u32)wVal));
#elif RECON_ARM_VECTOR_INTRIN
	return vld1q_s32((s32)wVal, (s32)zVal, (s32)yVal, (s32)xVal);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSet(const f32& fVal)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_set1_ps(fVal);
#elif RECON_ARM_VECTOR_INTRIN
	return vdupq_n_f32(fVal);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSet(const f32& fX, const f32& fY, const f32& fZ, const f32& fW)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_setr_ps(fX, fY, fZ, fW);
#elif RECON_ARM_VECTOR_INTRIN
	return vld1q_f32(fW, fZ, fY, fZ);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSet(const s32& iVal)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_set1_epi32(iVal));
#elif RECON_ARM_VECTOR_INTRIN
	return vdupq_n_s32(iVal);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSet(const s32& iX, const s32& iY, const s32& iZ, const s32& iW)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_setr_epi32(iX, iY, iZ, iW));
#elif RECON_ARM_VECTOR_INTRIN
	return vld1q_s32(iW, iZ, iY, iX);
#endif // RECON_SSE_VECTOR_INTRIN
}

// Used to load Aligned Data
__forceinline Vector128_Out RECON_VEC_CALLCONV VectorLoad(const f32* const alignedFloat4Ptr)
{
	Assertf(((((u64)alignedFloat4Ptr) & 15) == 0), "VectorLoad - Float Pointer MUST be 16-byte aligned!");

#if RECON_SSE_VECTOR_INTRIN
	return _mm_load_ps(alignedFloat4Ptr);
#elif RECON_ARM_VECTOR_INTRIN
	return vld1q_f32(alignedFloat4Ptr);
#endif // RECON_SSE_VECTOR_INTRIN
}

// Used to load Unaligned Data
__forceinline Vector128_Out RECON_VEC_CALLCONV VectorLoadU(const f32* const unalignedFloat4Ptr)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_loadu_ps(unalignedFloat4Ptr);
#else RECON_ARM_VECTOR_INTRIN
	return vld1q_f32(unalignedFloat4Ptr);
#endif // RECON_SSE_VECTOR_INTRIN
}

// Used to store in Aligned Data
__forceinline void RECON_VEC_CALLCONV VectorStore(Vector128_In lhs, f32* alignedFloat4Ptr)
{
	Assertf(((((u64)alignedFloat4Ptr) & 15) == 0), "VectorStore - Float Pointer MUST be 16-byte aligned!");
#if RECON_SSE_VECTOR_INTRIN
	_mm_store_ps(alignedFloat4Ptr, lhs);
#elif RECON_ARM_VECTOR_INTRIN
	vst1q_f32(alignedFloat4Ptr, lhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

// Used to store in Unaligned Data
__forceinline void RECON_VEC_CALLCONV VectorStoreU(Vector128_In lhs, f32* unalignedFloat4Ptr)
{
#if RECON_SSE_VECTOR_INTRIN
	_mm_storeu_ps(unalignedFloat4Ptr, lhs);
#elif RECON_ARM_VECTOR_INTRIN
	vst1q_f32(alignedFloat4Ptr, lhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

template<VecElem index>
__forceinline f32 RECON_VEC_CALLCONV VectorExtractFloat(Vector128_In vec)
{
	static_assert(index >= VecElem::X && index <= VecElem::W, "Invalid Permute X-Index. Must be between X & W!");
#if RECON_SSE_VECTOR_INTRIN && !RECON_EXTRACT_FROM_VEC_VIA_CAST
	return _mm_cvtss_f32(VectorPermute<index, index, index, index>(vec));
#elif RECON_ARM_VECTOR_INTRIN
	return ((f32*)vec)[(s32)index];
#endif // RECON_SSE_VECTOR_INTRIN
}

#if RECON_SSE_VECTOR_INTRIN && !RECON_EXTRACT_FROM_VEC_VIA_CAST
template<> __forceinline f32 RECON_VEC_CALLCONV VectorExtractFloat<VecElem::X>(Vector128_In vec) { return _mm_cvtss_f32(vec); }
#endif // RECON_SSE_VECTOR_INTRIN && !RECON_EXTRACT_FROM_VEC_VIA_CAST

template<VecElem index>
__forceinline s32 RECON_VEC_CALLCONV VectorExtractS32(Vector128_In vec)
{
	static_assert(index >= VecElem::X && index <= VecElem::W, "Invalid Permute X-Index. Must be between X & W!");
#if RECON_SSE_VECTOR_INTRIN && !RECON_EXTRACT_FROM_VEC_VIA_CAST
	return _mm_extract_epi32(VEC_F32_TO_S32(vec), (s32)index);
#elif RECON_ARM_VECTOR_INTRIN
	return ((s32*)&vec)[(s32)index];
#endif // RECON_SSE_VECTOR_INTRIN
}


// Permute Operations:

#define SHUFFLE_MASKED(index) ((s32)(index) & 0x3)
#define PERM_SHUFFLE(x, y, z, w) (_MM_FSHUFFLE(SHUFFLE_MASKED(x), SHUFFLE_MASKED(y), SHUFFLE_MASKED(z), SHUFFLE_MASKED(w)))
#define BLEND_MASK(x, y, z, w) ((x) | ((y)<<1) | ((z)<<2) | ((w)<<3))

template<VecElem splat>
__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSplat(Vector128_In vec)
{
	static_assert(splat >= VecElem::X && splat <= VecElem::W, "Invalid Splat Index. Must be between VecElem::X & VecElem::W!");
#if RECON_SSE_VECTOR_INTRIN
	return _mm_shuffle_ps(vec, vec, PERM_SHUFFLE(splat, splat, splat, splat));
#elif RECON_ARM_VECTOR_INTRIN
	return VectorPermute<splat, splat, splat, splat>(vec);
#endif // RECON_SSE_VECTOR_INTRIN
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
__forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute(Vector128_In vec)
{
	static_assert(pX >= VecElem::X && pX <= VecElem::W, "Invalid Permute X-Index. Must be between VecElem::X & VecElem::W!");
	static_assert(pY >= VecElem::X && pY <= VecElem::W, "Invalid Permute Y-Index. Must be between VecElem::X & VecElem::W!");
	static_assert(pZ >= VecElem::X && pZ <= VecElem::W, "Invalid Permute Z-Index. Must be between VecElem::X & VecElem::W!");
	static_assert(pW >= VecElem::X && pW <= VecElem::W, "Invalid Permute W-Index. Must be between VecElem::X & VecElem::W!");

#if RECON_SSE_VECTOR_INTRIN
	return _mm_shuffle_ps(vec, vec, PERM_SHUFFLE(pX, pY, pZ, pW));
#elif RECON_ARM_VECTOR_INTRIN
	ALIGN(16) float fVec[4];
	VectorStore(vec, fVec);
	ALIGN(16) float result[4] = { fVec[(s32)pX & 0x3], fVec[(s32)pY & 0x3], fVec[(s32)pZ & 0x3], fVec[(s32)pW & 0x3] };
	return VectorLoad(result);
#endif // RECON_SSE_VECTOR_INTRIN
}

template<VecElem pX, VecElem pY, VecElem pZ, VecElem pW>
__forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute(Vector128_In lhs, Vector128_In rhs)
{
	static_assert((pX >= VecElem::X1 && pX <= VecElem::W1) || (pX >= VecElem::X2 && pX <= VecElem::W2), "Invalid Permute X-Index. Must be between VecElem::X1 & VecElem::W2!");
	static_assert((pY >= VecElem::X1 && pY <= VecElem::W1) || (pY >= VecElem::X2 && pY <= VecElem::W2), "Invalid Permute Y-Index. Must be between VecElem::X1 & VecElem::W2!");
	static_assert((pZ >= VecElem::X1 && pZ <= VecElem::W1) || (pZ >= VecElem::X2 && pZ <= VecElem::W2), "Invalid Permute Z-Index. Must be between VecElem::X1 & VecElem::W2!");
	static_assert((pW >= VecElem::X1 && pW <= VecElem::W1) || (pW >= VecElem::X2 && pW <= VecElem::W2), "Invalid Permute W-Index. Must be between VecElem::X1 & VecElem::W2!");

	static_assert(!((pX < VecElem::X2 && pY < VecElem::X2 && pZ < VecElem::X2 && pW < VecElem::X2) ||
					(pX > VecElem::W1 && pY > VecElem::W1 && pZ > VecElem::W1 && pW > VecElem::W1)), "All Components Are From The Same Vector128, Use 'Permute(Vector128_In vec)' Instead");

#if RECON_SSE_VECTOR_INTRIN

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
		Vector128 tmpRhs = _mm_shuffle_ps(lhs, rhs, PERM_SHUFFLE(pZ, pZ, pW, pW));
		return _mm_shuffle_ps(lhs, tmpRhs, PERM_SHUFFLE(pX, pY, 0, 2));
	}
	else if((pX > VecElem::W1 && pY > VecElem::W1) &&		// Permute<Vec2, Vec2, Vec2, Vec1>
			(pZ > VecElem::W1 && pW < VecElem::X2))
	{
		Vector128 tmpRhs = _mm_shuffle_ps(rhs, lhs, PERM_SHUFFLE(pZ, pZ, pW, pW));
		return _mm_shuffle_ps(rhs, tmpRhs, PERM_SHUFFLE(pX, pY, 0, 2));
	}
	else if((pX < VecElem::X2 && pY > VecElem::W1) &&		// Permute<Vec1, Vec2, Vec2, Vec2>
			(pZ > VecElem::W1 && pW > VecElem::W1))
	{
		Vector128 tmpLhs = _mm_shuffle_ps(lhs, rhs, PERM_SHUFFLE(pX, pX, pY, pY));
		return _mm_shuffle_ps(tmpLhs, rhs, PERM_SHUFFLE(0, 2, pZ, pW));
	}
	else if((pX > VecElem::W1 && pY < VecElem::X2) &&		// Permute<Vec2, Vec1, Vec1, Vec1>
			(pZ < VecElem::X2 && pW < VecElem::X2))
	{
		Vector128 tmpLhs = _mm_shuffle_ps(rhs, lhs, PERM_SHUFFLE(pX, pX, pY, pY));
		return _mm_shuffle_ps(tmpLhs, lhs, PERM_SHUFFLE(0, 2, pZ, pW));
	}
	else if((pX < VecElem::X2 && pZ < VecElem::X2) &&		// Permute<Vec1, Vec2, Vec1, Vec2>
			(pY > VecElem::W1 && pW > VecElem::W1))
	{
		Vector128 tmpLhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pZ), (VecElem)SHUFFLE_MASKED(pZ)>(lhs);
		Vector128 tmpRhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pW), (VecElem)SHUFFLE_MASKED(pW)>(rhs);
		return _mm_blend_ps(tmpLhs, tmpRhs, BLEND_MASK(0, 1, 0, 1));
	}
	else if((pX > VecElem::W1 && pZ > VecElem::W1) &&		// Permute<Vec2, Vec1, Vec2, Vec1>
			(pY < VecElem::X2 && pW < VecElem::X2))
	{
		Vector128 tmpLhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pZ), (VecElem)SHUFFLE_MASKED(pZ)>(rhs);
		Vector128 tmpRhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pW), (VecElem)SHUFFLE_MASKED(pW)>(lhs);
		return _mm_blend_ps(tmpLhs, tmpRhs, BLEND_MASK(0, 1, 0, 1));
	}
	else if((pX < VecElem::X2 && pW < VecElem::X2) &&		// Permute<Vec1, Vec2, Vec2, Vec1>
			(pY > VecElem::W1 && pZ > VecElem::W1))
	{
		Vector128 tmpLhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pW), (VecElem)SHUFFLE_MASKED(pW)>(lhs);
		Vector128 tmpRhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pZ), (VecElem)SHUFFLE_MASKED(pZ)>(rhs);
		return _mm_blend_ps(tmpLhs, tmpRhs, BLEND_MASK(0, 1, 1, 0));
	}
	else if((pX > VecElem::W1 && pW > VecElem::W1) &&		// Permute<Vec2, Vec1, Vec1, Vec2>
			(pY < VecElem::X2 && pZ < VecElem::X2))
	{
		Vector128 tmpLhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pX), (VecElem)SHUFFLE_MASKED(pW), (VecElem)SHUFFLE_MASKED(pW)>(rhs);
		Vector128 tmpRhs = VectorPermute<(VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pY), (VecElem)SHUFFLE_MASKED(pZ), (VecElem)SHUFFLE_MASKED(pZ)>(lhs);
		return _mm_blend_ps(tmpLhs, tmpRhs, BLEND_MASK(0, 1, 1, 0));
	}
	else if((pX < VecElem::X2 && pY > VecElem::W1) &&		// Permute<Vec1, Vec2, Vec1, Vec1>
			(pZ < VecElem::X2 && pW < VecElem::X2))
	{
		Vector128 tmpLhs = _mm_shuffle_ps(lhs, rhs, PERM_SHUFFLE(pX, pX, pY, pY));
		return _mm_shuffle_ps(tmpLhs, lhs, PERM_SHUFFLE(0, 2, pZ, pW));
	}
	else if((pX > VecElem::W1 && pY < VecElem::X2) &&		// Permute<Vec2, Vec1, Vec2, Vec2>
			(pZ > VecElem::W1 && pW > VecElem::W1))
	{
		Vector128 tmpLhs = _mm_shuffle_ps(rhs, lhs, PERM_SHUFFLE(pX, pX, pY, pY));
		return _mm_shuffle_ps(tmpLhs, rhs, PERM_SHUFFLE(0, 2, pZ, pW));
	}
	else if((pX < VecElem::X2 && pY < VecElem::X2) &&		// Permute<Vec1, Vec1, Vec2, Vec1>
			(pZ > VecElem::W1 && pW < VecElem::X2))
	{
		Vector128 tmpRhs = _mm_shuffle_ps(rhs, lhs, PERM_SHUFFLE(pZ, pZ, pW, pW));
		return _mm_shuffle_ps(lhs, tmpRhs, PERM_SHUFFLE(pX, pY, 0, 2));
	}
	else if((pX > VecElem::W1 && pY > VecElem::W1) &&		// Permute<Vec2, Vec2, Vec1, Vec2>
			(pZ < VecElem::X2 && pW > VecElem::W1))
	{
		Vector128 tmpRhs = _mm_shuffle_ps(lhs, rhs, PERM_SHUFFLE(pZ, pZ, pW, pW));
		return _mm_shuffle_ps(rhs, tmpRhs, PERM_SHUFFLE(pX, pY, 0, 2));
	}
	else
	{
		//static_assert(false, "Unhandled Permute Case!");
		return _mm_setzero_ps();
	}

#elif RECON_ARM_VECTOR_INTRIN

	ALIGN(16) float vectors[2][4];
	VectorStore(lhs, vectors[0]);
	VectorStore(rhs, vectors[1]);

	ALIGN(16) float result[4] = { vectors[(s32)pX >> 4][(s32)pX & 0x3], vectors[(s32)pY >> 4][(s32)pY & 0x3], vectors[(s32)pZ >> 4][(s32)pZ & 0x3], vectors[(s32)pW >> 4][(s32)pW & 0x3] };
	return VectorLoad(result);

#endif // RECON_SSE_VECTOR_INTRIN
}

#undef PERM_SHUFFLE
#undef SHUFFLE_MASKED

#if RECON_SSE_VECTOR_INTRIN
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W1>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 0, 0)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z1, VecElem::W1>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 1, 0, 0)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z2, VecElem::W1>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 1, 1, 0)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z1, VecElem::W2>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 1, 0, 1)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z2, VecElem::W1>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 1, 0)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z2, VecElem::W2>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 1, 1)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W2>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(1, 0, 0, 1)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 0, 0)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z2, VecElem::W1>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 1, 0)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z2, VecElem::W2>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 1, 1)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W2>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 1, 0, 1)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 0, 1, 0)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W2>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 0, 1, 1)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(Vector128_In lhs, Vector128_In rhs) { return _mm_blend_ps(lhs, rhs, BLEND_MASK(0, 0, 0, 1)); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::X2, VecElem::Y1, VecElem::Y2>(Vector128_In lhs, Vector128_In rhs) { return _mm_unpacklo_ps(lhs, rhs); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::X1, VecElem::Y2, VecElem::Y1>(Vector128_In lhs, Vector128_In rhs) { return _mm_unpacklo_ps(rhs, lhs); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::Z1, VecElem::Z2, VecElem::W1, VecElem::W2>(Vector128_In lhs, Vector128_In rhs) { return _mm_unpackhi_ps(lhs, rhs); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::Z2, VecElem::Z1, VecElem::W2, VecElem::W1>(Vector128_In lhs, Vector128_In rhs) { return _mm_unpackhi_ps(rhs, lhs); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::Z2, VecElem::W2, VecElem::Z1, VecElem::W1>(Vector128_In lhs, Vector128_In rhs) { return _mm_movehl_ps(lhs, rhs); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::Z1, VecElem::W1, VecElem::Z2, VecElem::W2>(Vector128_In lhs, Vector128_In rhs) { return _mm_movehl_ps(rhs, lhs); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(Vector128_In lhs, Vector128_In rhs) { return _mm_movelh_ps(lhs, rhs); }
template<> __forceinline Vector128_Out RECON_VEC_CALLCONV VectorPermute<VecElem::X2, VecElem::Y2, VecElem::X1, VecElem::Y1>(Vector128_In lhs, Vector128_In rhs) { return _mm_movelh_ps(rhs, lhs); }
#endif // RECON_SSE_VECTOR_INTRIN

#undef BLEND_MASK


// Conversion Operations:

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorS32ToF32(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_cvtepi32_ps(VEC_F32_TO_S32(vec));
#elif RECON_ARM_VECTOR_INTRIN
	return vcvtq_f32_s32(vec);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorF32ToS32(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_cvttps_epi32(vec));
#elif RECON_ARM_VECTOR_INTRIN
	return vcvtq_s32_f32(vec);
#endif // RECON_SSE_VECTOR_INTRIN
}


// Arithmetic Operations: 

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorAdd(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_add_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vaddq_f32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorAddS32(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_add_epi32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
#elif RECON_ARM_VECTOR_INTRIN
	return vaddq_s32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

// Operates in the following manner:
// {lhs.x+lhs.y, lhs.z+lhs.w, rhs.x+rhs.y, rhs.z+rhs.w}
__forceinline Vector128_Out RECON_VEC_CALLCONV VectorHAdd(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_hadd_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vcombine_f32(vpadd_f32(vget_low_f32(lhs), vget_high_f32(lhs)), vpadd_f32(vget_low_f32(rhs), vget_high_f32(rhs)));
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSubtract(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_sub_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vsubq_f32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSubtractS32(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_sub_epi32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
#elif RECON_ARM_VECTOR_INTRIN
	return vsubq_s32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

// Operates in the following manner:
// {lhs.x-lhs.y, lhs.z-lhs.w, rhs.x-rhs.y, rhs.z-rhs.w}
__forceinline Vector128_Out RECON_VEC_CALLCONV VectorHSub(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_hsub_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vcombine_f32(vpadd_f32(vget_low_f32(lhs), vget_high_f32(VectorNegate(lhs))), vpadd_f32(vget_low_f32(rhs), vget_high_f32(VectorNegate(rhs))));
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMultiply(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_mul_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vmulq_f32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMad(Vector128_In vecMul1, Vector128_In vecMul2, Vector128_In vecAdd)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_fmadd_ps(vecMul1, vecMul2, vecAdd);
#elif RECON_ARM_VECTOR_INTRIN
	return vmlaq_f32(vecAdd, vecMul1, vecMul2);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMultiplyS32(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_mul_epi32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
#elif RECON_ARM_VECTOR_INTRIN
	return vmulq_s32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorDivide(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_div_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return VectorMultiply(lhs, VectorInverse(rhs));
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorNegate(Vector128_In vec)
{
	return VectorXOr(vec, VectorSetConstant<0x80000000>());
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorNegateS32(Vector128_In vec)
{
	return VectorSubtractS32(VectorSetConstant<0>(), vec);
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorAbs(Vector128_In vec)
{
	return VectorAnd(vec, VectorSetConstant<0x7FFFFFFF>());
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorAbsS32(Vector128_In vec)
{
	return VEC_S32_TO_F32(_mm_abs_epi32(VEC_F32_TO_S32(vec)));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorInverse(Vector128_In vec)
{
	return VectorInvert_NewtonRaphsonRefinement(vec);
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSqrt(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_sqrt_ps(vec);
#elif RECON_ARM_VECTOR_INTRIN
	return vrecpeq_f32(vrsqrteq_f32(vec));
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorInvSqrt(Vector128_In vec)
{
	return VectorInvertSqrt_NewtonRaphsonRefinement(vec);
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorRecip(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_rcp_ps(vec);
#elif RECON_ARM_VECTOR_INTRIN
	return vrecpeq_f32(vec);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorFloor(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_round_ps(vec, _MM_FROUND_TO_NEG_INF);
#elif RECON_ARM_VECTOR_INTRIN
	Vector128 vTrunc = VectorTrunc(vec);
	return VectorSubtract(vTrunc, VectorAnd(IsGreaterThan(vTrunc, vec), VectorSetConstant<(u32)FloatToIntRep::One>()));
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorCeil(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_round_ps(vec, _MM_FROUND_TO_POS_INF);
#elif RECON_ARM_VECTOR_INTRIN
	Vector128 vTrunc = VectorTrunc(vec);
	return VectorSubtract(vTrunc, VectorAnd(IsLessThan(vTrunc, vec), VectorSetConstant<(u32)FloatToIntRep::One>()));
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorTrunc(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_round_ps(vec, _MM_FROUND_TO_ZERO);
#elif RECON_ARM_VECTOR_INTRIN
	return VectorS32ToF32(VectorF32ToS32(vec));
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorRound(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_round_ps(vec, _MM_FROUND_TO_NEAREST_INT);
#elif RECON_ARM_VECTOR_INTRIN
	return VectorFloor(VectorAdd(vec, VectorSetConstant<(u32)FloatToIntRep::Half>()));
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSign(Vector128_In vec)
{
	return VectorAnd(VectorIsNotEqual(vec, VectorSetConstant<0>()), VectorOr(VectorAnd(vec, VectorSetConstant<0x80000000>()), VectorSetConstant<(u32)FloatToIntRep::One>()));
}

inline Vector128_Out RECON_VEC_CALLCONV VectorLog2(Vector128_In vec)
{
#if RECON_USE_SVML
	return _mm_log2_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector128 rawBiased = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	Vector128 trailing = VectorAnd(vec, VectorSetConstant<0x007FFFFF>());
	Vector128 isExponentZero = VectorIsEqualS32(VectorSetConstant<(u32)FloatToIntRep::Zero>(), rawBiased);

	// Compute exponent and significand for normals.
	Vector128 biased = VectorRightShift(rawBiased, 23);
	Vector128 exponentNor = VectorSubtractS32(biased, VectorSetConstant<(u32)127>());
	Vector128 trailingNor = trailing;

	// Compute exponent and significand for subnormals.
	Vector128 leading = VectorBitscanForward(trailing);
	Vector128 shift = VectorSubtractS32(VectorSetConstant<(u32)23>(), leading);
	Vector128 exponentSub = VectorSubtractS32(VectorSetConstant<(u32)-126>(), shift);
	Vector128 trailingSub = VectorLeftShift4(trailing, shift);
	trailingSub = VectorAnd(trailingSub, VectorSetConstant<0x007FFFFF>());

	Vector128 select0 = VectorAnd(isExponentZero, exponentSub);
	Vector128 select1 = VectorAndNot(exponentNor, isExponentZero);
	Vector128 e = VectorOr(select0, select1);

	select0 = VectorAnd(isExponentZero, trailingSub);
	select1 = VectorAndNot(trailingNor, isExponentZero);
	Vector128 t = VectorOr(select0, select1);

	// Compute the approximation.
	Vector128 tmp = VectorOr(VectorSetConstant<(u32)FloatToIntRep::One>(), t);
	Vector128 y = VectorSubtract(tmp, VectorSetConstant<(u32)FloatToIntRep::One>());

	Vector128 log2 = VectorMad(VectorSetConstant<0xBC2D4F59>(), y, VectorSetConstant<0x3D6A1405>());
	log2 = VectorMad(log2, y, VectorSetConstant<0xBE153261>());
	log2 = VectorMad(log2, y, VectorSetConstant<0x3E7E8E61>());
	log2 = VectorMad(log2, y, VectorSetConstant<0xBEB359DE>());
	log2 = VectorMad(log2, y, VectorSetConstant<0x3EF571D2>());
	log2 = VectorMad(log2, y, VectorSetConstant<0xBF38A351>());
	log2 = VectorMad(log2, y, VectorSetConstant<0x3FB8AA2A>());
	log2 = VectorMad(log2, y, VectorS32ToF32(e));

	Vector128 isInfinite = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Abs_Mask>());
	isInfinite = VectorIsEqualS32(isInfinite, VectorSetConstant<(u32)FloatToIntRep::Infinity>());

	Vector128 isGreaterZero = VectorIsGreaterThanS32(vec, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	Vector128 isNotFinite = VectorIsGreaterThanS32(vec, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	Vector128 isPositive = VectorAndNot(isGreaterZero, isNotFinite);

	Vector128 isZero = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Abs_Mask>());
	isZero = VectorIsEqualS32(isZero, VectorSetConstant<(u32)FloatToIntRep::Zero>());

	Vector128 t0 = VectorAnd(vec, VectorSetConstant<0x007FFFFF>());
	Vector128 t1 = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	t0 = VectorIsEqualS32(t0, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	t1 = VectorIsEqualS32(t1, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	Vector128 isNaN = VectorAndNot(t1, t0);

	select0 = VectorAnd(isInfinite, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	select1 = VectorAndNot(log2, isInfinite);
	Vector128 result = VectorOr(select0, select1);

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

inline Vector128_Out RECON_VEC_CALLCONV VectorExp2(Vector128_In vec)
{
#if RECON_USE_SVML
	return _mm_exp2_ps(vec);
#else
	Vector128 itrunc = VectorF32ToS32(vec);
	Vector128 ftrunc = VectorS32ToF32(itrunc);
	Vector128 y = VectorSubtract(vec, ftrunc);
	Vector128 poly = VectorMad(VectorSetConstant<0xB7364261>(), y, VectorSetConstant<0x391AA7D7>());
	poly = VectorMad(poly, y, VectorSetConstant<0xBAAE1854>());
	poly = VectorMad(poly, y, VectorSetConstant<0x3C1D8C54>());
	poly = VectorMad(poly, y, VectorSetConstant<0xBD6357CA>());
	poly = VectorMad(poly, y, VectorSetConstant<0x3E75FDED>());
	poly = VectorMad(poly, y, VectorSetConstant<0xBF317218>());
	poly = VectorMad(poly, y, VectorSetConstant<(u32)FloatToIntRep::One>());

	Vector128 biased = VectorAddS32(itrunc, VectorSetConstant<127>());
	biased = VectorLeftShift(biased, 23);
	Vector128 result0 = VectorDivide(biased, poly);

	biased = VectorAddS32(itrunc, VectorSetConstant<253>());
	biased = VectorLeftShift(biased, 23);
	Vector128 result1 = VectorDivide(biased, poly);
	result1 = VectorMultiply(VectorSetConstant<0x00800000>(), result1);

	Vector128 comp = VectorIsLessThanS32(vec, VectorSetConstant<0x43000000>());
	Vector128 select0 = VectorAnd(comp, result0);
	Vector128 select1 = VectorAndNot(VectorSetConstant<(u32)FloatToIntRep::Infinity>(), comp);
	Vector128 result2 = VectorOr(select0, select1);

	comp = VectorIsLessThanS32(itrunc, VectorSetConstant<(u32)-126>());
	select1 = VectorAnd(comp, result1);
	select0 = VectorAndNot(result0, comp);
	Vector128 result3 = VectorOr(select0, select1);

	comp = VectorIsLessThanS32(vec, VectorSetConstant<0xC3160000>());
	select0 = VectorAnd(comp, result3);
	select1 = VectorAndNot(VectorSetConstant<(u32)FloatToIntRep::Zero>(), comp);
	Vector128 result4 = VectorOr(select0, select1);

	Vector128 sign = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Sign_Bit>());
	comp = VectorIsEqualS32(sign, VectorSetConstant<(u32)FloatToIntRep::Sign_Bit>());
	select0 = VectorAnd(comp, result4);
	select1 = VectorAndNot(result2, comp);
	Vector128 result5 = VectorOr(select0, select1);

	Vector128 t0 = VectorAnd(vec, VectorSetConstant<0x007FFFFF>());
	Vector128 t1 = VectorAnd(vec, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	t0 = VectorIsEqualS32(t0, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	t1 = VectorIsEqualS32(t1, VectorSetConstant<(u32)FloatToIntRep::Infinity>());
	Vector128 isNaN = VectorAndNot(t1, t0);

	select0 = VectorAnd(isNaN, VectorSetConstant<(u32)FloatToIntRep::NaN>());
	select1 = VectorAndNot(result5, isNaN);
	Vector128 vResult = VectorOr(select0, select1);

	return vResult;
#endif // RECON_USE_SVML
}


// Trigonometry Operations:

inline Vector128_Out RECON_VEC_CALLCONV VectorSin(Vector128_In vec)
{
#if RECON_USE_SVML
	return _mm_sin_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	// Force the value within the bounds of pi
	Vector128 x = VectorMultiply(vec, VectorSetConstant<(u32)FloatToIntRep::One_Over_Two_Pi>());
	x = VectorRound(x);
	x = VectorMultiply(x, VectorSetConstant<(u32)FloatToIntRep::Two_Pi>());
	x = VectorSubtract(vec, x);

	// Map in [-pi/2,pi/2] with sin(y) = sin(x).
	Vector128 sign = VectorAnd(x, VectorSetConstant<(u32)FloatToIntRep::Sign_Bit>());
	Vector128 c = VectorOr(VectorSetConstant<(u32)FloatToIntRep::Pi>(), sign);  // pi when x >= 0, -pi when x < 0
	Vector128 absx = VectorAndNot(x, sign);  // |x|
	Vector128 rflx = VectorSubtract(c, x);
	Vector128 comp = VectorIsLessThanOrEqual(absx, VectorSetConstant<(u32)FloatToIntRep::Half_Pi>());
	Vector128 select0 = VectorAnd(comp, x);
	Vector128 select1 = VectorAndNot(rflx, comp);
	x = VectorOr(select0, select1);

	Vector128 x2 = VectorMultiply(x, x);

	// Compute polynomial approximation
	Vector128 Result = VectorMad(VectorSetConstant<0xB2CD365B>(), x2, VectorSetConstant<0x3638B88E>());
	Result = VectorMad(Result, x2, VectorSetConstant<0xB9500bF1>());
	Result = VectorMad(Result, x2, VectorSetConstant<0x3C088886>());
	Result = VectorMad(Result, x2, VectorSetConstant<0xBE2AAAAB>());
	Result = VectorMad(Result, x2, VectorSetConstant<(u32)FloatToIntRep::One>());
	Result = VectorMultiply(Result, x);
	return Result;
#endif // RECON_USE_SVML
}

inline Vector128_Out RECON_VEC_CALLCONV VectorASin(Vector128_In vec)
{
#if RECON_USE_SVML
	return _mm_asin_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector128 nonnegative = VectorIsGreaterThanOrEqual(vec, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	Vector128 x = VectorAbs(vec);

	// Compute (1-|V|), clamp to zero to avoid sqrt of negative number.
	Vector128 oneMValue = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::One>(), x);
	Vector128 clampOneMValue = VectorMax(VectorSetConstant<(u32)FloatToIntRep::Zero>(), oneMValue);
	Vector128 root = VectorSqrt(clampOneMValue);  // sqrt(1-|vec|)

	// Compute polynomial approximation
	Vector128 t0 = VectorMad(VectorSetConstant<0x3CFD10F8>(), x, VectorSetConstant<0xBC8BFC66>());
	t0 = VectorMad(t0, x, VectorSetConstant<0x3BDA90C5>());
	t0 = VectorMad(t0, x, VectorSetConstant<0xBAA57A2C>());
	t0 = VectorMad(t0, x, VectorSetConstant<0x3FC90FDA>());
	t0 = VectorMad(t0, x, VectorSetConstant<0xBE5BBFCA>());
	t0 = VectorMad(t0, x, VectorSetConstant<0x3DB63A9E>());
	t0 = VectorMad(t0, x, VectorSetConstant<0xBD4D8392>());

	t0 = VectorMultiply(t0, root);

	Vector128 t1 = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::Pi>(), t0);
	t0 = VectorAnd(nonnegative, t0);
	t1 = VectorAndNot(t1, nonnegative);
	t0 = VectorOr(t0, t1);
	t0 = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::Half_Pi>(), t0);
	return t0;
#endif // RECON_USE_SVML
}

inline Vector128_Out RECON_VEC_CALLCONV VectorCos(Vector128_In vec)
{
#if RECON_USE_SVML
	return _mm_cos_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	// Force the value within the bounds of pi
	Vector128 x = VectorMultiply(vec, VectorSetConstant<(u32)FloatToIntRep::One_Over_Two_Pi>());
	x = VectorRound(x);
	x = VectorMultiply(x, VectorSetConstant<(u32)FloatToIntRep::Two_Pi>());
	x = VectorSubtract(vec, x);

	// Map in [-pi/2,pi/2] with cos(y) = sign*cos(x).
	Vector128 sign = VectorAnd(x, VectorSetConstant<(u32)FloatToIntRep::Sign_Bit>());
	Vector128 c = VectorOr(VectorSetConstant<(u32)FloatToIntRep::Pi>(), sign);  // pi when x >= 0, -pi when x < 0
	Vector128 absx = VectorAndNot(x, sign);  // |x|
	Vector128 rflx = VectorSubtract(c, x);
	Vector128 comp = VectorIsLessThanOrEqual(absx, VectorSetConstant<(u32)FloatToIntRep::Half_Pi>());
	Vector128 select0 = VectorAnd(comp, x);
	Vector128 select1 = VectorAndNot(rflx, comp);
	x = VectorOr(select0, select1);
	select0 = VectorAnd(comp, VectorSetConstant<(u32)FloatToIntRep::One>());
	select1 = VectorAndNot(VectorSetConstant<(u32)FloatToIntRep::Neg_One>(), comp);
	sign = VectorOr(select0, select1);

	Vector128 x2 = VectorMultiply(x, x);

	// Compute polynomial approximation
	Vector128 Result = VectorMad(VectorSetConstant<0xB48BDD11>(), x2, VectorSetConstant<0x37CFB4C2>());
	Result = VectorMad(Result, x2, VectorSetConstant<0xBAB609AA>());
	Result = VectorMad(Result, x2, VectorSetConstant<0x3D2AAAA3>());
	Result = VectorMad(Result, x2, VectorSetConstant<(u32)FloatToIntRep::Neg_Half>());
	Result = VectorMad(Result, x2, VectorSetConstant<(u32)FloatToIntRep::One>());
	Result = VectorMultiply(Result, sign);
	return Result;
#endif // RECON_USE_SVML
}

inline Vector128_Out RECON_VEC_CALLCONV VectorACos(Vector128_In vec)
{
#if RECON_USE_SVML
	return _mm_acos_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector128 nonnegative = VectorIsGreaterThanOrEqual(vec, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	Vector128 x = VectorAbs(vec);

	// Compute (1-|vec|), clamp to zero to avoid sqrt of negative number.
	Vector128 oneMValue = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::One>(), x);
	Vector128 clampOneMValue = VectorMax(VectorSetConstant<(u32)FloatToIntRep::Zero>(), oneMValue);
	Vector128 root = VectorSqrt(clampOneMValue);  // sqrt(1-|vec|)

	// Compute polynomial approximation
	Vector128 t0 = VectorMad(VectorSetConstant<0xBAA57A2C>(), x, VectorSetConstant<0x3BDA90C5>());
	t0 = VectorMad(t0, x, VectorSetConstant<0xBC8BFC66>());
	t0 = VectorMad(t0, x, VectorSetConstant<0x3CFD10F8>());
	t0 = VectorMad(t0, x, VectorSetConstant<0xBD4D8392>());
	t0 = VectorMad(t0, x, VectorSetConstant<0x3DB63A9E>());
	t0 = VectorMad(t0, x, VectorSetConstant<0xBE5BBFCA>());
	t0 = VectorMad(t0, x, VectorSetConstant<0x3FC90FDA>());
	t0 = VectorMultiply(t0, root);

	Vector128 t1 = VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::Pi>(), t0);
	t0 = VectorAnd(nonnegative, t0);
	t1 = VectorAndNot(t1, nonnegative);
	t0 = VectorOr(t0, t1);
	return t0;
#endif // RECON_USE_SVML
}

inline Vector128_Out RECON_VEC_CALLCONV VectorTan(Vector128_In vec)
{
#if RECON_USE_SVML
	return _mm_tan_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector128 VA = VectorMultiply(vec, VectorSetConstant<0x3F22F983>());
	VA = VectorRound(VA);
	Vector128 VC = VectorSubtract(vec, VectorMultiply(VA, VectorSetConstant<0x3FC90FDB>()));
	Vector128 VB = VectorAbs(VA);
	VC = VectorSubtract(VC, VectorMultiply(VA, VectorSetConstant<0x2E85A309>()));
	VB = VectorF32ToS32(VB);
	Vector128 VC2 = VectorMultiply(VC, VC);	

	Vector128 VBIsEven = VectorAnd(VB, VectorSetConstant<0x1>());
	VBIsEven = VectorIsEqualS32(VBIsEven, VectorSetConstant<(u32)FloatToIntRep::Zero>());

	Vector128 N = VectorMad(VC2, VectorSetConstant<0xB795D5B9>(), VectorSetConstant<0x3B607415>());
	Vector128 D = VectorMad(VC2, VectorSetConstant<0x3505BBA8>(), VectorSetConstant<0xB9A37B25>());
	N = VectorMad(VC2, N, VectorSetConstant<0xBE0895AF>());
	D = VectorMad(VC2, D, VectorSetConstant<0x3CD23CF5>());
	N = VectorMultiply(VC2, N);
	D = VectorMad(VC2, D, VectorSetConstant<0xBEEEF582>());
	N = VectorMad(VC, N, VC);

	Vector128 VCNearZeroLE = VectorIsLessThanOrEqual(VC, VectorSetConstant<0x39800000>());
	Vector128 VCNearZeroGE = VectorIsLessThanOrEqual(VectorSetConstant<0xB9800000>(), VC);
	Vector128 VCNearZero = VectorAnd(VCNearZeroLE, VCNearZeroGE);

	D = VectorMad(VC2, D, VectorSetConstant<(u32)FloatToIntRep::One>());

	N = VectorSelectTF(VCNearZero, VC, N);
	D = VectorSelectTF(VCNearZero, VectorSetConstant<(u32)FloatToIntRep::One>(), D);

	Vector128 R0 = VectorNegate(N);
	Vector128 R1 = VectorDivide(N, D);
	R0 = VectorDivide(D, R0);

	Vector128 VIsZero = VectorIsEqual(vec, VectorSetConstant<(u32)FloatToIntRep::Zero>());

	Vector128 Result = VectorSelectTF(VBIsEven, R1, R0);

	Result = VectorSelectTF(VIsZero, VectorSetConstant<(u32)FloatToIntRep::Zero>(), Result);

	return Result;
#endif // RECON_USE_SVML
}

inline Vector128_Out RECON_VEC_CALLCONV VectorATan(Vector128_In vec)
{
#if RECON_USE_SVML
	_mm_atan_ps(vec);
#else
	// Modified From The "DirectX Math Library: DirectXMathVector.inl"

	Vector128 absV = VectorAbs(vec);
	Vector128 invV = VectorDivide(VectorSetConstant<(u32)FloatToIntRep::One>(), vec);
	Vector128 comp = VectorIsGreaterThan(vec, VectorSetConstant<(u32)FloatToIntRep::One>());
	Vector128 select0 = VectorAnd(comp, VectorSetConstant<(u32)FloatToIntRep::One>());
	Vector128 select1 = VectorAndNot(VectorSetConstant<(u32)FloatToIntRep::Neg_One>(), comp);
	Vector128 sign = VectorOr(select0, select1);
	comp = VectorIsLessThanOrEqual(absV, VectorSetConstant<(u32)FloatToIntRep::One>());
	select0 = VectorAnd(comp, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	select1 = VectorAndNot(sign, comp);
	sign = VectorOr(select0, select1);
	select0 = VectorAnd(comp, vec);
	select1 = VectorAndNot(invV, comp);
	Vector128 x = VectorOr(select0, select1);

	Vector128 x2 = VectorMultiply(x, x);

	// Compute polynomial approximation
	Vector128 Result = VectorMad(VectorSetConstant<0x3B3BD74A>(), x2, VectorSetConstant<0xBC846E02>());
	Result = VectorMad(Result, x2, VectorSetConstant<0x3D2FC1FE>());
	Result = VectorMad(Result, x2, VectorSetConstant<0xBD9A3174>());
	Result = VectorMad(Result, x2, VectorSetConstant<0x3DDA3D83>());
	Result = VectorMad(Result, x2, VectorSetConstant<0xBE117FC7>());
	Result = VectorMad(Result, x2, VectorSetConstant<0x3E4CBBE5>());
	Result = VectorMad(Result, x2, VectorSetConstant<0xBEAAAA6C>());
	Result = VectorMad(Result, x2, VectorSetConstant<(u32)FloatToIntRep::One>());

	Result = VectorMultiply(Result, x);
	Vector128 result1 = VectorMultiply(sign, VectorSetConstant<(u32)FloatToIntRep::Half_Pi>());
	result1 = VectorSubtract(result1, Result);

	comp = VectorIsEqual(sign, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	select0 = VectorAnd(comp, Result);
	select1 = VectorAndNot(result1, comp);
	Result = VectorOr(select0, select1);
	return Result;
#endif // RECON_USE_SVML
}

// NOTE: Performs Sin/Cos of Vec.x
// Returns: Vector128(Sin(), Cos(), Sin(), Cos());
inline Vector128_Out RECON_VEC_CALLCONV VectorSinCos(Vector128_In vec)
{
#if RECON_USE_SVML
	return _mm_sincos_ps(vec);
#else
	Vector128 vecX = VectorSplat<VecElem::X>(vec);
	return VectorSin(VectorAdd(vec, VectorSetConstant<(u32)FloatToIntRep::Zero, (u32)FloatToIntRep::Half_Pi, (u32)FloatToIntRep::Zero, (u32)FloatToIntRep::Half_Pi>()));
#endif // RECON_USE_SVML
}


// Logical Operations:

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorAnd(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_and_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vandq_s32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorAndNot(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_andnot_ps(rhs, lhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vbicq_s32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorNot(Vector128_In vec)
{
	return VectorXOr(vec, VectorSetConstant<0xFFFFFFFF>());
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorOr(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_or_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vorrq_s32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorXOr(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_xor_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return veorq_s32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorLeftShift(Vector128_In vec, s32 nCount)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_slli_epi32(VEC_F32_TO_S32(vec), nCount));
#elif RECON_ARM_VECTOR_INTRIN
	return vshlq_n_s32(vec, nCount);
#endif // RECON_SSE_VECTOR_INTRIN
}

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
inline Vector128_Out RECON_VEC_CALLCONV VectorLeftShift4(Vector128_In vec, Vector128_In shiftCount)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_sllv_epi32(VEC_F32_TO_S32(vec), VEC_F32_TO_S32(shiftCount)));
#elif RECON_ARM_VECTOR_INTRIN
	Vector128 xShift = VectorLeftShift(vec, VectorExtractS32<VecElem::X>(shiftCount));
	Vector128 yShift = VectorLeftShift(vec, VectorExtractS32<VecElem::Y>(shiftCount));
	Vector128 zShift = VectorLeftShift(vec, VectorExtractS32<VecElem::Z>(shiftCount));
	Vector128 wShift = VectorLeftShift(vec, VectorExtractS32<VecElem::W>(shiftCount));
	Vector128 xy = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(xShift, yShift);
	Vector128 zw = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(zShift, wShift);
	return VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W2>(xy, zw);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorRightShift(Vector128_In vec, s32 nCount)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_srli_epi32(VEC_F32_TO_S32(vec), nCount));
#elif RECON_ARM_VECTOR_INTRIN
	return vshrq_n_s32(vec, nCount);
#endif // RECON_SSE_VECTOR_INTRIN
}

// shiftCount is is expected to have integer data NOT floats
// If all values of shiftCount are the same then you should use VectorLeftShift as it is MUCH faster
inline Vector128_Out RECON_VEC_CALLCONV VectorRightShift4(Vector128_In vec, Vector128_In shiftCount)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_srlv_epi32(VEC_F32_TO_S32(vec), VEC_F32_TO_S32(shiftCount)));
#elif RECON_ARM_VECTOR_INTRIN
	Vector128 xShift = VectorRightShift(vec, VectorExtractS32<VecElem::X>(shiftCount));
	Vector128 yShift = VectorRightShift(vec, VectorExtractS32<VecElem::Y>(shiftCount));
	Vector128 zShift = VectorRightShift(vec, VectorExtractS32<VecElem::Z>(shiftCount));
	Vector128 wShift = VectorRightShift(vec, VectorExtractS32<VecElem::W>(shiftCount));
	Vector128 xy = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(xShift, yShift);
	Vector128 zw = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(zShift, wShift);
	return VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W2>(xy, zw);
#endif // RECON_SSE_VECTOR_INTRIN
}


// Comparison Functions:

// Floating Point Comparisons:
#define CMP_MASK_X (0x1)
#define CMP_MASK_XY (0x3)
#define CMP_MASK_XYZ (0x7)
#define CMP_MASK_XYZW (0xF)

#define VEC_CMP_DEFBASE_IMPL(name, ...) \
	__forceinline Vector128_Out RECON_VEC_CALLCONV Vector##name(Vector128_In lhs, Vector128_In rhs) \
	{ \
		return __VA_ARGS__; \
	}

#define VEC_CMP_DEF(name, nameExt) \
	__forceinline bool RECON_VEC_CALLCONV Vector##name##nameExt(Vector128_In lhs, Vector128_In rhs) \
	{ \
		return ( VectorMoveMask( Vector##name (lhs, rhs) ) & CMP_MASK_##nameExt ) == CMP_MASK_##nameExt ; \
	}

#define VEC_CMP_DEFBASE(name, ...)  VEC_CMP_DEFBASE_IMPL(name, __VA_ARGS__)
#define VEC_CMP1_DEF(name) VEC_CMP_DEF(name, X)
#define VEC_CMP2_DEF(name) VEC_CMP_DEF(name, XY)
#define VEC_CMP3_DEF(name) VEC_CMP_DEF(name, XYZ)
#define VEC_CMP4_DEF(name) VEC_CMP_DEF(name, XYZW)

#define VEC_CMP_DEF_ALL(name, ...)  \
			VEC_CMP_DEFBASE(name, __VA_ARGS__) \
			VEC_CMP1_DEF(name) \
			VEC_CMP2_DEF(name) \
			VEC_CMP3_DEF(name) \
			VEC_CMP4_DEF(name)

#if RECON_SSE_VECTOR_INTRIN
VEC_CMP_DEF_ALL(IsEqual, _mm_cmpeq_ps(lhs, rhs));
VEC_CMP_DEF_ALL(IsNotEqual, _mm_cmpneq_ps(lhs, rhs));
VEC_CMP_DEF_ALL(IsGreaterThan, _mm_cmpgt_ps(lhs, rhs));
VEC_CMP_DEF_ALL(IsGreaterThanOrEqual, _mm_cmpge_ps(lhs, rhs));
VEC_CMP_DEF_ALL(IsLessThan, _mm_cmplt_ps(lhs, rhs));
VEC_CMP_DEF_ALL(IsLessThanOrEqual, _mm_cmple_ps(lhs, rhs));
#elif RECON_ARM_VECTOR_INTRIN
VEC_CMP_DEF_ALL(IsEqual, vceqq_f32(lhs, rhs));
VEC_CMP_DEF_ALL(IsNotEqual, vmvnq_s32(vceqq_f32(a, b)));
VEC_CMP_DEF_ALL(IsGreaterThan, vcgtq_f32(lhs, rhs));
VEC_CMP_DEF_ALL(IsGreaterThanOrEqual, vcgeq_f32(lhs, rhs));
VEC_CMP_DEF_ALL(IsLessThan, vcltq_f32(lhs, rhs));
VEC_CMP_DEF_ALL(IsLessThanOrEqual, vcleq_f32(lhs, rhs));
#endif // RECON_SSE_VECTOR_INTRIN


// Integer Comparisons:
// Redefine VEC_CMP_DEF & VEC_CMP_DEFBASE for integer operations
#undef VEC_CMP_DEFBASE_IMPL
#define VEC_CMP_DEFBASE_IMPL(name, ...) \
	__forceinline Vector128_Out RECON_VEC_CALLCONV Vector##name(Vector128_In lhs, Vector128_In rhs) \
{ \
	return VEC_S32_TO_F32( __VA_ARGS__ ); \
}

#undef VEC_CMP_DEF
#define VEC_CMP_DEF(name, nameExt) \
	__forceinline bool RECON_VEC_CALLCONV Vector##name##nameExt(Vector128_In lhs, Vector128_In rhs) \
	{ \
		return (VectorMoveMask(Vector##name(lhs, rhs)) == CMP_MASK_##nameExt); \
	}

#if RECON_SSE_VECTOR_INTRIN
VEC_CMP_DEF_ALL(IsEqualS32, _mm_cmpeq_epi32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
VEC_CMP_DEF_ALL(IsGreaterThanS32, _mm_cmpgt_epi32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
VEC_CMP_DEF_ALL(IsLessThanS32, _mm_cmplt_epi32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
#elif RECON_ARM_VECTOR_INTRIN
VEC_CMP_DEF_ALL(IsEqualS32, vceqq_s32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
VEC_CMP_DEF_ALL(IsGreaterThanS32, vcgtq_s32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
VEC_CMP_DEF_ALL(IsLessThanS32, vcltq_s32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
#endif // RECON_SSE_VECTOR_INTRIN

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorIsNotEqualS32(Vector128_In lhs, Vector128_In rhs)
{
	return VectorNot(VectorIsEqualS32(lhs, rhs));
}

__forceinline bool RECON_VEC_CALLCONV VectorIsNotEqualS32X(Vector128_In lhs, Vector128_In rhs)
{
	return (VectorMoveMask(VectorIsNotEqualS32(lhs, rhs))&CMP_MASK_X) == CMP_MASK_X;
}

__forceinline bool RECON_VEC_CALLCONV VectorIsNotEqualS32XY(Vector128_In lhs, Vector128_In rhs)
{
	return (VectorMoveMask(VectorIsNotEqualS32(lhs, rhs))&CMP_MASK_XY) == CMP_MASK_XY;
}

__forceinline bool RECON_VEC_CALLCONV VectorIsNotEqualS32XYZ(Vector128_In lhs, Vector128_In rhs)
{
	return (VectorMoveMask(VectorIsNotEqualS32(lhs, rhs))&CMP_MASK_XYZ) == CMP_MASK_XYZ;
}

__forceinline bool RECON_VEC_CALLCONV VectorIsNotEqualS32XYZW(Vector128_In lhs, Vector128_In rhs)
{
	return (VectorMoveMask(VectorIsNotEqualS32(lhs, rhs))&CMP_MASK_XYZW) == CMP_MASK_XYZW;
}

#define VEC_CMP_OREQUAL_INT_DEFBASE(name, cmp) \
	__forceinline Vector128_Out RECON_VEC_CALLCONV Vector##name(Vector128_In lhs, Vector128_In rhs) \
	{ \
		return VectorOr(Vector##name(lhs, rhs), VectorIsEqualS32(lhs, rhs)); \
	}

#define VEC_CMP_OREQUAL_INT_DEF(name, nameExt, cmp) \
	__forceinline bool RECON_VEC_CALLCONV Vector##name##nameExt(Vector128_In lhs, Vector128_In rhs) \
	{ \
		return Vector##cmp##nameExt(lhs, rhs) || VectorIsEqualS32##nameExt(lhs, rhs); \
	}

#define VEC_CMP_OREQUAL_INT_DEF_ALL(name, cmp1) \
	VEC_CMP_OREQUAL_INT_DEFBASE(name, cmp1) \
	VEC_CMP_OREQUAL_INT_DEF(name, X, cmp1) \
	VEC_CMP_OREQUAL_INT_DEF(name, XY, cmp1) \
	VEC_CMP_OREQUAL_INT_DEF(name, XYZ, cmp1) \
	VEC_CMP_OREQUAL_INT_DEF(name, XYZW, cmp1)

VEC_CMP_OREQUAL_INT_DEF_ALL(IsGreaterThanOrEqualS32, IsGreaterThanS32);
VEC_CMP_OREQUAL_INT_DEF_ALL(IsLessThanOrEqualS32, IsLessThanS32);

#undef VEC_CMP_OREQUAL_INT_DEF_ALL
#undef VEC_CMP_OREQUAL_INT_DEF
#undef VEC_CMP_OREQUAL_INT_DEFBASE

//__forceinline bool IsLessThanEqualIntAll(Vector128_In lhs, Vector128_In rhs)
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

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorInvert_NewtonRaphsonRefinement(Vector128_In vec)
{
	const Vector128 recip(VectorRecip(vec));
	return VectorMad(VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::One>(), VectorMultiply(vec, recip)), recip, recip);
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorInvertSqrt_NewtonRaphsonRefinement(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	const Vector128 recip(_mm_rsqrt_ps(vec));
#elif RECON_ARM_VECTOR_INTRIN
	const Vector128 recip(vrsqrteq_f32(vec));
#endif // RECON_SSE_VECTOR_INTRIN

	return VectorMad(VectorSubtract(VectorSetConstant<(u32)FloatToIntRep::Half>(), VectorMultiply(VectorSetConstant<(u32)FloatToIntRep::Half>(), VectorMultiply(vec, VectorMultiply(recip, recip)))), recip, recip);
}

__forceinline s32 RECON_VEC_CALLCONV VectorMoveMask(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_movemask_ps(vec);
#elif RECON_ARM_VECTOR_INTRIN
	Vector128 tmp = VectorAnd(vtstq_u32(vec, VectorSetConstant<(u32)FloatToIntRep::Sign_Bit>()), VectorSetConstant<1, 2, 4, 8>());
	tmp = vorr_u32(vget_low_u32(tmp), vget_high_u32(tmp));
	return vget_lane_u32(tmp, 0) | vget_lane_u32(tmp, 1);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMin(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_min_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vminq_f32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMinS32(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_min_epi32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
#elif RECON_ARM_VECTOR_INTRIN
	return vminq_s32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMax(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_max_ps(lhs, rhs);
#elif RECON_ARM_VECTOR_INTRIN
	return vmaxq_f32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMaxS32(Vector128_In lhs, Vector128_In rhs)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_max_epi32(VEC_F32_TO_S32(lhs), VEC_F32_TO_S32(rhs)));
#elif RECON_ARM_VECTOR_INTRIN
	return vmaxq_s32(lhs, rhs);
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorClamp(Vector128_In val, Vector128_In minVal, Vector128_In maxVal)
{
	return VectorMax(minVal, VectorMin(val, maxVal));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorClampS32(Vector128_In val, Vector128_In minVal, Vector128_In maxVal)
{
	return VectorMaxS32(minVal, VectorMinS32(val, maxVal));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorSelectTF(Vector128_In condition, Vector128_In ifTrue, Vector128_In ifFalse)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_blendv_ps(ifFalse, ifTrue, condition);
#elif RECON_ARM_VECTOR_INTRIN
	return VectorOr(VectorAnd(condition, ifTrue), VectorAndNot(condition, ifFalse));
#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMinComponentV2(Vector128_In vec)
{
	return VectorMin(VectorSplat<VecElem::X>(vec), VectorSplat<VecElem::Y>(vec));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMinComponentV3(Vector128_In vec)
{
	Vector128 MinXY = VectorMin(vec, VectorSplat<VecElem::Y>(vec));
	return VectorSplat<VecElem::X>(VectorMin(MinXY, VectorSplat<VecElem::Z>(vec)));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMinComponentV4(Vector128_In vec)
{
	Vector128 MinXZ_YW = VectorMin(vec, VectorPermute<VecElem::Z, VecElem::W, VecElem::Z, VecElem::W>(vec));
	return VectorSplat<VecElem::X>(VectorMin(MinXZ_YW, VectorSplat<VecElem::Y>(MinXZ_YW)));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMaxComponentV2(Vector128_In vec)
{
	return VectorMax(VectorSplat<VecElem::X>(vec), VectorSplat<VecElem::Y>(vec));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMaxComponentV3(Vector128_In vec)
{
	Vector128 MaxXY = VectorMax(vec, VectorSplat<VecElem::Y>(vec));
	return VectorSplat<VecElem::X>(VectorMax(MaxXY, VectorSplat<VecElem::Z>(vec)));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorMaxComponentV4(Vector128_In vec)
{
	Vector128 MaxXZ_YW = VectorMax(vec, VectorPermute<VecElem::Z, VecElem::W, VecElem::Z, VecElem::W>(vec));
	return VectorSplat<VecElem::X>(VectorMax(MaxXZ_YW, VectorSplat<VecElem::Y>(MaxXZ_YW)));
}

inline Vector128_Out RECON_VEC_CALLCONV VectorBitscanForward(Vector128_In vec)
{
	// Modified from "DirectXMathVector.inl"

	Vector128 c = VectorIsGreaterThanS32(vec, VectorSetConstant<0xFFFF>());		// c = (v > 0xFFFF)
	Vector128 b = VectorRightShift(c, 31);										// b = (c ? 1 : 0)
	Vector128 r = VectorLeftShift(b, 4);										// r = (b << 4)
	Vector128 vecOut = VectorRightShift4(vec, r);								// v = (v >> r)

	c = VectorIsGreaterThanS32(vecOut, VectorSetConstant<0xFF>());				// c = (v > 0xFF)
	b = VectorRightShift(c, 31);												// b = (c ? 1 : 0)
	Vector128 s = VectorLeftShift(b, 3);										// s = (b << 3)
	vecOut = VectorRightShift4(vecOut, s);										// v = (v >> s)
	r = VectorOr(r, s);															// r = (r | s)

	c = VectorIsGreaterThanS32(vecOut, VectorSetConstant<0xF>());				// c = (v > 0xF)
	b = VectorRightShift(c, 31);												// b = (c ? 1 : 0)
	s = VectorLeftShift(b, 2);													// s = (b << 2)
	vecOut = VectorRightShift4(vecOut, s);										// v = (v >> s)
	r = VectorOr(r, s);															// r = (r | s)

	c = VectorIsGreaterThanS32(vecOut, VectorSetConstant<0x3>());				// c = (v > 0x3)
	b = VectorRightShift(c, 31);												// b = (c ? 1 : 0)
	s = VectorLeftShift(b, 1);													// s = (b << 1)
	vecOut = VectorRightShift4(vecOut, s);										// v = (v >> s)
	r = VectorOr(r, s);															// r = (r | s)

	s = VectorRightShift(vecOut, 1);
	r = VectorOr(r, s);

	return r;
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorF32ToF16(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return VEC_S32_TO_F32(_mm_cvtps_ph(vec, _MM_FROUND_TO_ZERO));
#elif RECON_ARM_VECTOR_INTRIN

#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorF32ToF16(Vector128_In lowerHalf4, Vector128_In upperHalf4)
{
	return VectorPermute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(VectorF32ToF16(lowerHalf4), VectorF32ToF16(upperHalf4));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorF16ToF32(Vector128_In vec)
{
#if RECON_SSE_VECTOR_INTRIN
	return _mm_cvtph_ps(VEC_F32_TO_S32(vec));
#elif RECON_ARM_VECTOR_INTRIN

#endif // RECON_SSE_VECTOR_INTRIN
}

__forceinline void RECON_VEC_CALLCONV VectorF16ToF32(Vector128_In packedVec, Vector128_InOut lowerFloat4, Vector128_InOut upperFloat4)
{
	lowerFloat4 = VectorF16ToF32(packedVec);
	upperFloat4 = VectorF16ToF32(VectorPermute<VecElem::Z, VecElem::W, VecElem::Z, VecElem::W>(packedVec));
}


// Vector128 Math Operations:

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorCrossProduct(Vector128_In lhs, Vector128_In rhs)
{
	Vector128 vec1 = VectorPermute<VecElem::Y, VecElem::Z, VecElem::X, VecElem::X>(lhs);
	Vector128 vec2 = VectorPermute<VecElem::Z, VecElem::X, VecElem::Y, VecElem::X>(rhs);
	Vector128 vec3 = VectorMultiply(vec1, vec2);

	vec1 = VectorPermute<VecElem::Z, VecElem::X, VecElem::Y, VecElem::X>(lhs);
	vec2 = VectorPermute<VecElem::Y, VecElem::Z, VecElem::X, VecElem::X>(rhs);

	return VectorSubtract(vec3, VectorMultiply(vec1, vec2));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorDotV2(Vector128_In lhs, Vector128_In rhs)
{
	Vector128 dp = VectorMultiply(lhs, rhs);
	return VectorSplat<VecElem::X>(VectorHAdd(dp, dp));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorDotV3(Vector128_In lhs, Vector128_In rhs)
{
	Vector128 rhsWZero = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(rhs, VectorSetConstant<(u32)FloatToIntRep::Zero>());
	Vector128 dp = VectorMultiply(lhs, rhsWZero);
	Vector128 result = VectorHAdd(dp, dp);
	return VectorSplat<VecElem::X>(VectorHAdd(result, result));
}

__forceinline Vector128_Out RECON_VEC_CALLCONV VectorDotV4(Vector128_In lhs, Vector128_In rhs)
{
	Vector128 dp = VectorMultiply(lhs, rhs);
	Vector128 result = VectorHAdd(dp, dp);
	return VectorSplat<VecElem::X>(VectorHAdd(result, result));
}

#undef VEC_S32_TO_F32
#undef VEC_F32_TO_S32
