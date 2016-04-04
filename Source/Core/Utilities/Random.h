#ifndef _RECON_RANDOM_H_
#define _RECON_RANDOM_H_

#include "../Math Lib/MathLib.h"

#define RECON_RANDOM_USE_VEC4V (0)// Set to 1 if using visual studio 2015

namespace recon
{

class Rand
{
private:
	static THREADLOCAL u32 ms_Seed1;
	static THREADLOCAL u32 ms_Seed2;

#if RECON_SSE_VERSION
	#if RECON_RANDOM_USE_VEC4V
		static THREADLOCAL Vec4V ms_vSeed;
	#else
		static THREADLOCAL Vector128 ms_vSeed;
	#endif // RECON_RANDOM_USE_VEC4V
#endif // RECON_SSE_VERSION

public:
	Rand() = delete;
	~Rand() = delete;

	static void Seed(u32 seed = 1);

	static s32 Draw();
	static s32 Draw(s32 nMin, s32 nMax);
	static f32 Draw(f32 fMin, f32 fMax);

	static f32 DrawNormalized();

	static bool DrawBool();

	static Vec2f_Out Draw2();
	static Vec2f_Out Draw2(f32 fMin, f32 fMax);
	static Vec2f_Out Draw2(Vec2f_In vMin, Vec2f_In vMax);

	static Vec3f_Out Draw3();
	static Vec3f_Out Draw3(f32 fMin, f32 fMax);
	static Vec3f_Out Draw3(Vec3f_In vMin, Vec3f_In vMax);

	static Vec4f_Out Draw4();
	static Vec4f_Out Draw4(f32 fMin, f32 fMax);
	static Vec4f_Out Draw4(Vec4f_In vMin, Vec4f_In vMax);
	

#if RECON_SSE_VERSION
	static Vec4V_Out DrawV();

	static ScalarV_Out Draw(ScalarV_In vMin, ScalarV_In vMax);

	static Vec2V_Out Draw2(ScalarV_In vMin, ScalarV_In vMax);
	static Vec2V_Out Draw2(Vec2V_In vMin, Vec2V_In vMax);

	static Vec3V_Out Draw3(ScalarV_In vMin, ScalarV_In vMax);
	static Vec3V_Out Draw3(Vec3V_In vMin, Vec3V_In vMax);

	static Vec4V_Out Draw4(ScalarV_In vMin, ScalarV_In vMax);
	static Vec4V_Out Draw4(Vec4V_In vMin, Vec4V_In vMax);
#endif // RECON_SSE_VERISON
};

__forceinline void Rand::Seed(u32 seed)
{
	ms_Seed1 = (seed & 0xFFFFFFFE) | 1; // Seed Can't be 0
	ms_Seed2 = ms_Seed1 ^ U32_MAX;

#if RECON_SSE_VERSION
	Vec4V vSeed = Vec4VInt(((seed >> 16) & U16_MAX) | (seed << 16), seed ^ 0x2F01BEEF, (seed >> 24) + seed, ((seed * 10876813) + (seed & 0xFFFF00)));
	vSeed = (vSeed & Vec4VConstant<0xFFFFFFFE>()) | Vec4VConstant<1>();

	#if RECON_RANDOM_USE_VEC4V
		ms_vSeed = vSeed;
	#else
		ms_vSeed = vSeed.GetVectorRef();
	#endif // RECON_RANDOM_USE_VEC4V
#endif // RECON_SSE_VERSION
}

__forceinline s32 Rand::Draw()
{
	u64 mulWithCarry = (u64)1557985959 * ms_Seed1 + ms_Seed2;

	ms_Seed1 = mulWithCarry & U32_MAX;
	ms_Seed2 = (mulWithCarry >> 32) & U32_MAX;

	return ms_Seed1;
}

__forceinline s32 Rand::Draw(s32 nMin, s32 nMax)
{
	return s32((DrawNormalized() * (nMax - nMin)) + nMin);
}

__forceinline f32 Rand::Draw(f32 fMin, f32 fMax)
{
	return (DrawNormalized() * (fMax - fMin)) + fMin;
}

__forceinline f32 Rand::DrawNormalized()
{
									// 1.0f/((2^23)-1)
	return (Draw() & ((1<<23)-1)) * 1.1920930376163765926810017443897e-7f;
}

__forceinline bool Rand::DrawBool()
{
	return (Draw() & 1) != 0;
}

__forceinline Vec2f_Out Rand::Draw2()
{
	s32 seed1 = Draw();
	s32 seed2 = ms_Seed2;
	return Vec2fInt(seed1, (seed1 & 0x55555555) | (seed2 & 0xAAAAAAAA));
}

__forceinline Vec2f_Out Rand::Draw2(f32 fMin, f32 fMax)
{
	return Draw2(Vec2f(fMin), Vec2f(fMax));
}

__forceinline Vec2f_Out Rand::Draw2(Vec2f_In vMin, Vec2f_In vMax)
{
	Vec2f floatMask(S32ToF32(Draw2() & Vec2fInt(0x7FFFFF)) * Vec2fInt(0x34000000)); // oneOver2Pow23MinusOne
	return floatMask * (vMax - vMin) + vMin;
}

__forceinline Vec3f_Out Rand::Draw3()
{
	s32 seed1 = Draw();
	s32 seed2 = ms_Seed2;
	return Vec3fInt(seed1, (seed1 & 0x55555555) | (seed2 & 0xAAAAAAAA), seed2);
}

__forceinline Vec3f_Out Rand::Draw3(f32 fMin, f32 fMax)
{
	return Draw3(Vec3f(fMin), Vec3f(fMax));
}

__forceinline Vec3f_Out Rand::Draw3(Vec3f_In vMin, Vec3f_In vMax)
{
	Vec3f floatMask(S32ToF32(Draw3() & Vec3fInt(0x7FFFFF)) * Vec3fInt(0x34000000)); // oneOver2Pow23MinusOne
	return floatMask * (vMax - vMin) + vMin;
}

__forceinline Vec4f_Out Rand::Draw4()
{
	s32 seed1 = Draw();
	s32 seed2 = ms_Seed2;
	return Vec4fInt(seed1, (seed1 & 0x55555555) | (seed2 & 0xAAAAAAAA), seed2, (seed1 & 0xAAAAAAAA) | (seed2 & 0x55555555));
}

__forceinline Vec4f_Out Rand::Draw4(f32 fMin, f32 fMax)
{
	return Draw4(Vec4f(fMin), Vec4f(fMax));
}

__forceinline Vec4f_Out Rand::Draw4(Vec4f_In vMin, Vec4f_In vMax)
{
	Vec4f floatMask(S32ToF32(Draw4() & Vec4fInt(0x7FFFFF)) * Vec4fInt(0x34000000)); // oneOver2Pow23MinusOne
	return floatMask * (vMax - vMin) + vMin;
}

#if RECON_SSE_VERSION

__forceinline Vec4V_Out Rand::DrawV()
{
#if RECON_RANDOM_USE_VEC4V
	Vec4V vMult = Vec4VConstant<214013, 17405, 214013, 69069>();
	Vec4V cur_seed_split = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(ms_vSeed);
	ms_vSeed = AbsS32(MultiplyS32(ms_vSeed, vMult));
	vMult = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(vMult);
	cur_seed_split = AbsS32(MultiplyS32(cur_seed_split, vMult));
	ms_vSeed = ms_vSeed & Vec4VConstant<0xFFFFFFFF, 0, 0xFFFFFFFF, 0>();
	cur_seed_split = cur_seed_split & Vec4VConstant<0xFFFFFFFF, 0, 0xFFFFFFFF, 0>();
	cur_seed_split = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(cur_seed_split);
	ms_vSeed = ms_vSeed | cur_seed_split;
	ms_vSeed = AddInt(ms_vSeed, Vec4VConstant<2531011, 10395331, 13737667, 1>());
	return ms_vSeed;
#else
	Vec4V vSeedTmp(ms_vSeed);
	Vec4V vMult = Vec4VConstant<214013, 17405, 214013, 69069>();
	Vec4V cur_seed_split = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(vSeedTmp);
	vSeedTmp = AbsS32(MultiplyS32(vSeedTmp, vMult));
	vMult = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(vMult);
	cur_seed_split = AbsS32(MultiplyS32(cur_seed_split, vMult));
	vSeedTmp = vSeedTmp & Vec4VConstant<0xFFFFFFFF, 0, 0xFFFFFFFF, 0>();
	cur_seed_split = cur_seed_split & Vec4VConstant<0xFFFFFFFF, 0, 0xFFFFFFFF, 0>();
	cur_seed_split = Permute<VecElem::Y, VecElem::X, VecElem::W, VecElem::Z>(cur_seed_split);
	vSeedTmp = vSeedTmp | cur_seed_split;
	vSeedTmp = AddInt(vSeedTmp, Vec4VConstant<2531011, 10395331, 13737667, 1>());
	ms_vSeed = vSeedTmp.GetVectorRef();
	return vSeedTmp;
#endif // RECON_RANDOM_USE_VEC4V
}

__forceinline ScalarV_Out Rand::Draw(ScalarV_In vMin, ScalarV_In vMax)
{
	ScalarV floatMask(S32ToF32(ScalarV(Splat<VecElem::X>(DrawV()).GetVectorRef()) & ScalarVConstant<0x7FFFFF>()) * ScalarVConstant<0x34000000>()); // oneOver2Pow23MinusOne
	return ScalarV();
}

__forceinline Vec2V_Out Rand::Draw2(ScalarV_In vMin, ScalarV_In vMax)
{
	return Draw2(Vec2V(vMin), Vec2V(vMax));
}

__forceinline Vec2V_Out Rand::Draw2(Vec2V_In vMin, Vec2V_In vMax)
{
	Vec2V floatMask(S32ToF32(Vec2V(DrawV().GetVectorRef()) & Vec2VConstant<0x7FFFFF>()) * Vec2VConstant<0x34000000>()); // oneOver2Pow23MinusOne
	return floatMask * (vMax - vMin) + vMin;
}

__forceinline Vec3V_Out Rand::Draw3(ScalarV_In vMin, ScalarV_In vMax)
{
	return Draw3(Vec3V(vMin), Vec3V(vMax));
}

__forceinline Vec3V_Out Rand::Draw3(Vec3V_In vMin, Vec3V_In vMax)
{
	Vec3V floatMask(S32ToF32(Vec3V(DrawV().GetVectorRef()) & Vec3VConstant<0x7FFFFF>()) * Vec3VConstant<0x34000000>()); // oneOver2Pow23MinusOne
	return floatMask * (vMax - vMin) + vMin;
}

__forceinline Vec4V_Out Rand::Draw4(ScalarV_In vMin, ScalarV_In vMax)
{
	return Draw4(Vec4V(vMin), Vec4V(vMax));
}

__forceinline Vec4V_Out Rand::Draw4(Vec4V_In vMin, Vec4V_In vMax)
{
	Vec4V floatMask(S32ToF32(DrawV() & Vec4VConstant<0x7FFFFF>()) * Vec4VConstant<0x34000000>()); // oneOver2Pow23MinusOne
	return floatMask * (vMax - vMin) + vMin;
}

#endif // RECON_SSE_VERSIN

} // namespace recon

#endif // _RECON_RANDOM_H_