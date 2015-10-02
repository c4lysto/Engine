
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

	m_Planes[(u32)FrustumPlane::Left].Set(wSplat + xSplat);
	m_Planes[(u32)FrustumPlane::Right].Set(wSplat - xSplat);
	m_Planes[(u32)FrustumPlane::Top].Set(wSplat - ySplat);
	m_Planes[(u32)FrustumPlane::Bottom].Set(wSplat + ySplat);
	m_Planes[(u32)FrustumPlane::Near].Set(zSplat);
	m_Planes[(u32)FrustumPlane::Far].Set(wSplat - zSplat);
}