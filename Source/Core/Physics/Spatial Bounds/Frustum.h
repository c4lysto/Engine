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
	// Add 2 For Near/Far Repeats (makes culling faster)
	Plane m_Planes[(u32)FrustumPlane::NumPlanes+2];

#if RECON_DEBUG
	bool m_bTransposed;
#endif // RECON_DEBUG

public:
	Frustum();

#if RECON_DEBUG
	bool IsTranposed() const { return m_bTransposed; }
#endif // RECON_DEBUG

	Mat44V_ConstRef GetLRTB() const { return *(Mat44V*)m_Planes; }
	Mat44V_ConstRef GetNF() const { return *(Mat44V*)(m_Planes + 4); }

	void Build(Mat44V_In vViewProjMatrix);

	Plane_Out GetPlane(FrustumPlane planeIndex) { Assert(planeIndex < FrustumPlane::NumPlanes); return m_Planes[(u32)planeIndex]; }

	void TransposePlanes();

private:
	void BuildPlane(Plane_Ref vPlane, Vec4V_In vPlaneEquation) const;
};

Frustum_Out RECON_VEC_CALLCONV TransformFrustum(Frustum_In vFrustum, Mat43V_In vTransform);

#include "Frustum.inl"

} // namespace recon

#endif // _RECON_FRUSTUM_H_