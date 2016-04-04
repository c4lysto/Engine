#include "Random.h"

namespace recon
{

THREADLOCAL u32 Rand::ms_Seed1 = 0x1A2B3C4DU;
THREADLOCAL u32 Rand::ms_Seed2 = 0x2F01BEEFU;

#if RECON_SSE_VERSION
	#if RECON_RANDOM_USE_VEC4V
		THREADLOCAL Vec4V Rand::ms_vSeed(0x5B87E6E1, 0xC9E0E568, 0xE6E15C6D, 0x2D6F6F09);
	#else
		THREADLOCAL Vector128 Rand::ms_vSeed = {7.6505952e+16f, -1842349.0f, -5.321187e+23f, 1.3610232e-11f};
	#endif // RECON_RANDOM_USE_VEC4V
#endif // RECON_SSE_VERISON

} // namespace recon
