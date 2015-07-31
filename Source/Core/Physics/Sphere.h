#ifndef _RECON_SPHERE_H_
#define _RECON_SPHERE_H_

namespace recon
{

class Sphere;

typedef Sphere& Sphere_Ref;
typedef const Sphere& Sphere_ConstRef;

#if RECON_OS_64BIT
typedef Sphere Sphere_In;
#else
typedef Sphere_ConstRef Sphere_In;
#endif

typedef Sphere Sphere_Out;

typedef Sphere_Ref Sphere_InOut;

class Sphere
{
private:
	Vec4V m_vSphere;

public:
	Sphere();
	explicit Sphere(Vec3V_In vCenter, ScalarV_In vRadius);
	explicit Sphere(Vec4V_In vSphere);

	Vec3V_Out GetCenter() const;
	void SetCenter(Vec3V_In vCenter);

	ScalarV_Out GetRadius() const;
	ScalarV_Out GetRadiusSq() const;
	void SetRadius(ScalarV_In vRadius);

	void Set(Vec4V_In vSphere);
	Vec4V_Out Get() const;
	Vec4V_Ref GetRef();
	Vec4V_ConstRef GetRef() const;

};

bool IntersectSphereToSphere(Sphere_ConstRef lhs, Sphere_ConstRef rhs);
bool IntersectSphereToSphere(Sphere_ConstRef lhs, Sphere_ConstRef rhs, ScalarV_Ref vOverlap);

#include "Sphere.inl"

} // namespace recon

#endif // _RECON_SPHERE_H_