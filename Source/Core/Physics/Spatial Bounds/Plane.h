#ifndef _RECON_PLANE_H_
#define _RECON_PLANE_H_

//#include "../../Math Lib/MathLib.h"

namespace recon
{

class Plane;

typedef Plane& Plane_Ref;
typedef const Plane& Plane_ConstRef;

#if RECON_OS_64BIT
typedef Plane Plane_In;
#else
typedef Plane_ConstRef Plane_In;
#endif

typedef Plane Plane_Out;

typedef Plane_Ref Plane_InOut;

// Plane Equation: Ax + By + Cz + D = 0
class Plane
{
private:
	Vec4V m_vPlane;

public:
	Plane();
	explicit Plane(Vec3V_In vPosition);
	explicit Plane(Vec3V_In vNormal, ScalarV_In vOffset);
	explicit Plane(Vec3V_In vNormal, Vec3V_In vPosition);
	explicit Plane(Vec4V_In vPlane);

	Vec3V_Out GetNormal() const;
	void SetNormal(Vec3V_In vNormal);

	ScalarV_Out GetOffset() const;
	void SetOffset(ScalarV_In vOffset);

	void Set(Vec4V_In vPlane);
	Vec4V_Out Get() const;

	Vec4V_Ref GetRef();
	Vec4V_ConstRef GetRef() const;

	Vec3V_Out GetPos() const;
};

#include "Plane.inl"

} // namespace recon

#endif // _RECON_PLANE_H_