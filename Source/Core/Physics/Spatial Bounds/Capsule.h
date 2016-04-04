#ifndef _RECON_CAPSULE_H_
#define _RECON_CAPSULE_H_

namespace recon
{

class Capsule;

typedef Capsule& Capsule_Ref;
typedef const Capsule& Capsule_ConstRef;

typedef Capsule_ConstRef Capsule_In;

typedef Capsule Capsule_Out;

typedef Capsule_Ref Capsule_InOut;

class Capsule
{
private:
	Vec4V m_vOrigin_Radius;
	Vec4V m_vDir_Extent;

public:
	Capsule();
	Capsule(Vec3V_In vStart, Vec3V_In vEnd, ScalarV_In vRadius);
	Capsule(Vec3V_In vStart, Vec3V_In vDir, ScalarV_In vExtent, ScalarV_In vRadius);

	Vec3V_Out GetOrigin() const;
	Vec3V_Out GetDir() const;

	Vec3V_Out GetStart() const;
	Vec3V_Out GetEnd() const;

	ScalarV_Out GetRadius() const;
	ScalarV_Out GetRadiusSq() const;

	ScalarV_Out GetExtent() const;
};

#include "Capsule.inl"

} // namespace recon

#endif // _RECON_CAPSULE_H_