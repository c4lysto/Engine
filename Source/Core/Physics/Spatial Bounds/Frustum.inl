
Frustum::Frustum()
{

}

inline void Frustum::Build(Mat44V_In vViewProjMatrix)
{
	Mat44V splatMat = Transpose(vViewProjMatrix);

	Vec4V_ConstRef xSplat = splatMat.GetXAxisRef();
	Vec4V_ConstRef ySplat = splatMat.GetYAxisRef();
	Vec4V_ConstRef zSplat = splatMat.GetZAxisRef();
	Vec4V_ConstRef wSplat = splatMat.GetWAxisRef();

	BuildPlane(m_Planes[(u32)FrustumPlane::Left], wSplat + xSplat);
	BuildPlane(m_Planes[(u32)FrustumPlane::Right], wSplat - xSplat);
	BuildPlane(m_Planes[(u32)FrustumPlane::Top], wSplat - ySplat);
	BuildPlane(m_Planes[(u32)FrustumPlane::Bottom], wSplat + ySplat);
	BuildPlane(m_Planes[(u32)FrustumPlane::Near], zSplat);
	BuildPlane(m_Planes[(u32)FrustumPlane::Far], wSplat - zSplat);

#if RECON_DEBUG
	m_bTransposed = false;
#endif // RECON_DEBUG
}

__forceinline void Frustum::TransposePlanes()
{
	Mat44V* pTransposedPlanes = (Mat44V*)m_Planes;
	*pTransposedPlanes = Transpose(*pTransposedPlanes);

	pTransposedPlanes = (Mat44V*)(m_Planes + 4);
	*pTransposedPlanes = Transpose(*pTransposedPlanes);

#if RECON_DEBUG
	m_bTransposed = !m_bTransposed;
#endif // RECON_DEBUG
}

inline void Frustum::BuildPlane(Plane_Ref vPlane, Vec4V_In vPlaneEquation) const
{
	Vec4V vTmp = vPlaneEquation;
	ScalarV vMag = Mag(vTmp.GetXYZ());
	vTmp.SetXYZ(vTmp.GetXYZ() / vMag);
	vTmp.SetW(vTmp.GetW() / vMag);
	vPlane.Set(vTmp);
}