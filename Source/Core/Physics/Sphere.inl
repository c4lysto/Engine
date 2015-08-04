
FORCEINLINE Sphere::Sphere() {}

FORCEINLINE Sphere::Sphere(Vec3V_In vCenter, ScalarV_In vRadius) : m_vSphere(vCenter, vRadius) {}

FORCEINLINE Sphere::Sphere(Vec4V_In vSphere) : m_vSphere(vSphere) {}

FORCEINLINE Vec3V_Out Sphere::GetCenter() const
{
	return m_vSphere.GetXYZ();
}

FORCEINLINE void Sphere::SetCenter(Vec3V_In vCenter)
{
	m_vSphere.SetXYZ(vCenter);
}

FORCEINLINE ScalarV_Out Sphere::GetRadius() const
{
	return m_vSphere.GetW();
}

FORCEINLINE ScalarV_Out Sphere::GetRadiusSq() const
{
	ScalarV vRadius = GetRadius();
	return vRadius * vRadius;
}

FORCEINLINE void Sphere::SetRadius(ScalarV_In vRadius)
{
	m_vSphere.SetW(vRadius);
}

FORCEINLINE void Sphere::Set(Vec4V_In vSphere)
{
	m_vSphere = vSphere;
}

FORCEINLINE Vec4V_Out Sphere::Get() const
{
	return m_vSphere;
}

FORCEINLINE Vec4V_Ref Sphere::GetRef()
{
	return m_vSphere;
}

FORCEINLINE Vec4V_ConstRef Sphere::GetRef() const
{
	return m_vSphere;
}