#ifndef _RECON_FRUSTUM_H_
#define _RECON_FRUSTUM_H_

#include "Plane.h"

namespace recon
{
class Frustum;

typedef Frustum& Frustum_Ref;
typedef const Frustum& Frustum_ConstRef;

typedef Frustum_ConstRef Frustum_In;
typedef Frustum Frustum_Out;
typedef Frustum& Frustum_InOut;


enum class FrustumPlane
{
	Left,
	Right,
	Top,
	Bottom,
	Near,
	Far,
	NumPlanes
};


class Frustum
{
private:
	Plane m_Planes[FrustumPlane::NumPlanes];

public:
	Frustum();

	void Build(Mat44V_In vViewProjMatrix);

	Plane_Out GetPlane(FrustumPlane planeIndex) { Assert(planeIndex < FrustumPlane::NumPlanes); return m_Planes[(u32)planeIndex]; }

	void TransposePlanes();
};

Frustum_Out RECON_VEC_CALLCONV TransformFrustum(Frustum_In vFrustum, Mat43V_In vTransform);

#include "Frustum.inl"

} // namespace recon

#endif // _RECON_FRUSTUM_H_