
FORCEINLINE AABB::AABB() {}

FORCEINLINE AABB::AABB(Vec3V_In vMin, Vec3V_In vMax) : m_vMin(vMin), m_vMax(vMax) {}

FORCEINLINE AABB::AABB(Sphere_In vSurroundingSphere)
{
	SetFromSurroundingSphere(vSurroundingSphere);
}

// Will Overwrite User Data 1
FORCEINLINE void AABB::SetMin(Vec3V_In vMin)
{
	m_vMin = vMin;
}

FORCEINLINE Vec3V_Out AABB::GetMin() const
{
	return m_vMin;
}

FORCEINLINE Vec3V_Ref AABB::GetMinRef()
{
	return m_vMin;
}

FORCEINLINE Vec3V_ConstRef AABB::GetMinRef() const
{
	return m_vMin;
}

// Will Overwrite User Data 2
FORCEINLINE void AABB::SetMax(Vec3V_In vMax)
{
	m_vMax = vMax;
}

FORCEINLINE Vec3V_Out AABB::GetMax() const
{
	return m_vMax;
}

FORCEINLINE Vec3V_Ref AABB::GetMaxRef()
{
	return m_vMax;
}

FORCEINLINE Vec3V_ConstRef AABB::GetMaxRef() const
{
	return m_vMax;
}

FORCEINLINE Vec3V_Out AABB::GetDimensions() const
{
	return m_vMax - m_vMin;
}

FORCEINLINE Vec3V_Out AABB::GetHalfDimensions() const
{
	return GetDimensions() * ScalarV(I_HALF);
}

FORCEINLINE void AABB::SetUserData1(ScalarV_In vData)
{
	m_vMin.SetW(vData);
}

FORCEINLINE ScalarV_Out AABB::GetUserData1() const
{
	return m_vMin.GetW();
}

FORCEINLINE void AABB::SetUserData2(ScalarV_In vData)
{
	m_vMax.SetW(vData);
}

FORCEINLINE ScalarV_Out AABB::GetUserData2() const
{
	return m_vMax.GetW();
}

FORCEINLINE Vec3V_Out AABB::GetDimensions() const
{
	return m_vMax - m_vMin;
}

FORCEINLINE void AABB::SetFromSurroundingSphere(Sphere_In vSurroundingSphere)
{
	Vec3V vSphereCenter = vSurroundingSphere.GetCenter();
	m_vMin = vSphereCenter - Vec3V(vSurroundingSphere.GetRadius());
	m_vMax = vSphereCenter + Vec3V(vSurroundingSphere.GetRadius());
}