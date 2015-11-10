#ifndef _RECON_AABB_H_
#define _RECON_AABB_H_

#include "Sphere.h"

namespace recon
{

class AABB;

typedef AABB& AABB_Ref;
typedef const AABB& AABB_ConstRef;

typedef AABB_ConstRef AABB_In;

typedef AABB AABB_Out;

typedef AABB_Ref AABB_InOut;

class AABB
{
private:
	Vec3V m_vMin;
	Vec3V m_vMax;

public:
	AABB();
	explicit AABB(Vec3V_In vMin, Vec3V_In vMax);
	explicit AABB(Sphere_In vSurroundingSphere);

	// Will Overwrite User Data 1
	void SetMin(Vec3V_In vMin);

	Vec3V_Out GetMin() const;
	Vec3V_Ref GetMinRef();
	Vec3V_ConstRef GetMinRef() const;

	// Will Overwrite User Data 2
	void SetMax(Vec3V_In vMax);

	Vec3V_Out GetMax() const;
	Vec3V_Ref GetMaxRef();
	Vec3V_ConstRef GetMaxRef() const;

	Vec3V_Out GetCenter() const;

	Vec3V_Out GetDimensions() const;
	Vec3V_Out GetExtents() const;

	void SetUserData1(ScalarV_In vData);
	ScalarV_Out GetUserData1() const;

	void SetUserData2(ScalarV_In vData);
	ScalarV_Out GetUserData2() const;

	void SetFromSphere(Sphere_In vSurroundingSphere);

	Sphere_Out GetSuroundingSphere() const;
	Sphere_Out GetInscribedSphere() const;
};

#include "AABB.inl"

} // namespace recon

#endif // _RECON_AABB_H_