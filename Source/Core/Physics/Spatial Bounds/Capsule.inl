
__forceinline Capsule::Capsule()
{

}

__forceinline Capsule::Capsule(Vec3V_In vStart, Vec3V_In vEnd, ScalarV_In vRadius) :
	m_vOrigin_Radius(vStart, vRadius),
	m_vDir_Extent(Normalize(vEnd - vStart), Mag(vEnd - vStart))
{
	Assert(MagSq(GetDir()));
}

__forceinline Capsule::Capsule(Vec3V_In vStart, Vec3V_In vDir, ScalarV_In vExtent, ScalarV_In vRadius) :
	m_vOrigin_Radius(vStart, vRadius),
	m_vDir_Extent(vDir, vExtent)
{
	Assert(MagSq(GetDir()));
}

__forceinline Vec3V_Out Capsule::GetOrigin() const
{
	return m_vOrigin_Radius.GetXYZ();
}

__forceinline Vec3V_Out Capsule::GetDir() const
{
	return m_vDir_Extent.GetXYZ();
}

__forceinline Vec3V_Out Capsule::GetStart() const
{
	return GetOrigin();
}

__forceinline Vec3V_Out Capsule::GetEnd() const
{
	return GetOrigin() + (GetDir() * GetExtent());
}

__forceinline ScalarV_Out Capsule::GetRadius() const
{
	return m_vOrigin_Radius.GetW();
}

__forceinline ScalarV_Out Capsule::GetRadiusSq() const
{
	return GetRadius() * GetRadius();
}

__forceinline ScalarV_Out Capsule::GetExtent() const
{
	return m_vDir_Extent.GetW();
}