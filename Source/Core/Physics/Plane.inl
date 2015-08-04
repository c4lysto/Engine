
FORCEINLINE Plane::Plane() {}

inline Plane::Plane(Vec3V_In vPosition) : m_vPlane(Normalize(vPosition), Mag(vPosition))
{

}

FORCEINLINE Plane::Plane(Vec3V_In vNormal, ScalarV_In vOffset) : m_vPlane(Normalize(vNormal), vOffset)
{

}

FORCEINLINE Plane::Plane(Vec4V_In vPlane) : m_vPlane(vPlane)
{

}

FORCEINLINE Vec3V_Out Plane::GetNormal() const
{
	return m_vPlane.GetXYZ();
}

FORCEINLINE void Plane::SetNormal(Vec3V_In vNormal)
{
	m_vPlane.SetXYZ(vNormal);
}

FORCEINLINE ScalarV_Out Plane::GetOffset() const
{
	return m_vPlane.GetW();
}

FORCEINLINE void Plane::SetOffset(ScalarV_In vOffset)
{
	m_vPlane.SetW(vOffset);
}

FORCEINLINE void Plane::Set(Vec4V_In vPlane)
{
	m_vPlane = vPlane;
}

FORCEINLINE Vec4V_Out Plane::Get() const
{
	return m_vPlane;
}

FORCEINLINE Vec3V_Out Plane::GetPos() const
{
	return GetNormal() * GetOffset();
}