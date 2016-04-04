#ifndef MATHLIB_H
#define MATHLIB_H

#include "../Utilities/UtilitiesInclude.h"
#include "MathDeclarations.h"

#if RECON_SSE_VERSION
#include "VectorWrapper.h"
#endif

#include "Vec2f.h"
#include "Vec3f.h"
#include "Vec4f.h"
#include "Mat33f.h"
#include "Mat43f.h"
#include "Mat44f.h"

#if RECON_SSE_VERSION
#include "ScalarV.h"
#include "Vec2V.h"
#include "Vec3V.h"
#include "Vec4V.h"
#include "Mat33V.h"
#include "Mat43V.h"
#include "Mat44V.h"
#endif

#include "GlobalMathFuncs.h"

#endif //MATHLIB_H