
__forceinline AABB::AABB() {}

__forceinline AABB::AABB(Vec3V_In vMin, Vec3V_In vMax) : m_vMin(vMin), m_vMax(vMax) {}

__forceinline AABB::AABB(Sphere_In vSurroundingSphere)
{
	SetFromSphere(vSurroundingSphere);
}

// Will Overwrite User Data 1
__forceinline void AABB::SetMin(Vec3V_In vMin)
{
	m_vMin = vMin;
}

__forceinline Vec3V_Out AABB::GetMin() const
{
	return m_vMin;
}

__forceinline Vec3V_Ref AABB::GetMinRef()
{
	return m_vMin;
}

__forceinline Vec3V_ConstRef AABB::GetMinRef() const
{
	return m_vMin;
}

// Will Overwrite User Data 2
__forceinline void AABB::SetMax(Vec3V_In vMax)
{
	m_vMax = vMax;
}

__forceinline Vec3V_Out AABB::GetMax() const
{
	return m_vMax;
}

__forceinline Vec3V_Ref AABB::GetMaxRef()
{
	return m_vMax;
}

__forceinline Vec3V_ConstRef AABB::GetMaxRef() const
{
	return m_vMax;
}

__forceinline Vec3V_Out AABB::GetCenter() const
{
	return (m_vMax + m_vMin) * Vec3V(I_HALF);
}

__forceinline Vec3V_Out AABB::GetDimensions() const
{
	return m_vMax - m_vMin;
}

__forceinline Vec3V_Out AABB::GetExtents() const
{
	return GetDimensions() * ScalarV(I_HALF);
}

__forceinline void AABB::SetUserData1(ScalarV_In vData)
{
	m_vMin.SetW(vData);
}

__forceinline ScalarV_Out AABB::GetUserData1() const
{
	return m_vMin.GetW();
}

__forceinline void AABB::SetUserData2(ScalarV_In vData)
{
	m_vMax.SetW(vData);
}

__forceinline ScalarV_Out AABB::GetUserData2() const
{
	return m_vMax.GetW();
}

__forceinline void AABB::SetFromSphere(Sphere_In vSurroundingSphere)
{
	Vec3V vSphereCenter = vSurroundingSphere.GetCenter();
	m_vMin = vSphereCenter - Vec3V(vSurroundingSphere.GetRadius());
	m_vMax = vSphereCenter + Vec3V(vSurroundingSphere.GetRadius());
}

__forceinline Sphere_Out AABB::GetSuroundingSphere() const
{
	return Sphere(GetCenter(), Mag(m_vMax - m_vMin) * ScalarV(I_HALF));
}

__forceinline Sphere_Out AABB::GetInscribedSphere() const
{
	return Sphere(GetCenter(), MinComponent(GetExtents()));
}