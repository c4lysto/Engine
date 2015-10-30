

// Point Intersections:
__forceinline bool TestPointToCapsule(Vec3V_In vPoint, Capsule_In vCapsule)
{
	Vec3V vCapsuleOrigin(vCapsule.GetOrigin());
	Vec3V vCapsuleDir(vCapsule.GetDir());
	Vec3V vClosestPointToCapsule(vCapsuleOrigin + vCapsuleDir * Clamp(Dot(vCapsuleDir, vPoint - vCapsuleOrigin), ScalarV(I_ZERO), vCapsule.GetExtent()));
	return MagSq(vClosestPointToCapsule - vPoint) <= vCapsule.GetRadiusSq();
}

__forceinline bool TestPointToSphere(Vec3V_In vPoint, Sphere_In vSphere)
{
	return MagSq(vPoint - vSphere.GetCenter()) <= vSphere.GetRadiusSq();
}

__forceinline bool TestPointToAABB(Vec3V_In vPoint, AABB_In vAABB)
{
	return IsLessThanOrEqualXYZ(Abs(vPoint - vAABB.GetCenter()), vAABB.GetExtents());
}


// Capsule Intersections:

__forceinline bool TestCapsuleToAABB(Capsule_In vCapsule, AABB_In vAABB)
{
	return TestAABBToCapsule(vAABB, vCapsule);
}

__forceinline bool TestCapsuleToPoint(Capsule_In vCapsule, Vec3V_In vPoint)
{
	return TestPointToCapsule(vPoint, vCapsule);
}

__forceinline bool TestCapsuleToSphere(Capsule_In vCapsule, Sphere_In vSphere)
{
	return TestSphereToCapsule(vSphere, vCapsule);
}


// Sphere Intersections:

__forceinline bool TestSphereToCapsule(Sphere_In vSphere, Capsule_In vCapsule)
{
	Vec3V vCapsuleOrigin(vCapsule.GetOrigin());
	Vec3V vCapsuleDir(vCapsule.GetDir());
	Vec3V vSphereCenter(vSphere.GetCenter());
	Vec3V vClosestPointToCapsule(vCapsuleOrigin + vCapsuleDir * Clamp(Dot(vCapsuleDir, vSphereCenter - vCapsuleOrigin), ScalarV(I_ZERO), vCapsule.GetExtent()));
	return MagSq(vClosestPointToCapsule - vSphereCenter) <= (vCapsule.GetRadiusSq() + vSphere.GetRadiusSq());
}

__forceinline bool TestSphereToSphere(Sphere_In lhs, Sphere_In rhs)
{
	Vec3V vCenterToCenter = lhs.GetCenter() - rhs.GetCenter();
	ScalarV vRadiiSq = lhs.GetRadiusSq() + rhs.GetRadiusSq();
	return vRadiiSq >= MagSq(vCenterToCenter);
}

//inline bool TestSphereToSphere(Sphere_In lhs, Sphere_In rhs, ScalarV_Ref vOverlap)
//{
//	Vec3V vCenterToCenter = lhs.GetCenter() - rhs.GetCenter();
//	ScalarV vRadiiSq = lhs.GetRadiusSq() + rhs.GetRadiusSq();
//	ScalarV vDistSq = MagSq(vCenterToCenter);
//	vOverlap = Sqrt(vRadiiSq - vDistSq);
//	return vRadiiSq >= vDistSq;
//}

__forceinline bool TestSphereToPlane(Sphere_In vSphere, Plane_In vPlane)
{
	ScalarV vDot = Dot(vSphere.GetCenter(),  vPlane.GetNormal());
	return Abs(vPlane.GetOffset() - vDot) <= vSphere.GetRadius();
}

__forceinline bool TestSphereToPoint(Sphere_In vSphere, Vec3V_In vPoint)
{
	return TestPointToSphere(vPoint, vSphere);
}

inline bool TestSphereToRay(Sphere_In vSphere, Ray_In vRay)
{
	Vec3V vSphereCenter = vSphere.GetCenter();
	Vec3V vClosestPointToSphere = vRay.GetDirRef() * Max(ScalarV(I_ZERO), Dot(vRay.GetDirRef(), vSphereCenter - vRay.GetOriginRef()));
	return vSphere.GetRadiusSq() >= MagSq(vClosestPointToSphere-vSphereCenter);
}

__forceinline bool TestSphereToFrustum(Sphere_In vSphere, Frustum_In vFrustum)
{
	return TestFrustumToSphere(vFrustum, vSphere);
}

// Returns True For Any Sort Of Intersection
// vOverlap - Will Return Negative If The Sphere Is Behind The Plane
//__forceinline bool TestSphereToPlane(Sphere_In vSphere, Plane_In vPlane, ScalarV_Ref vOverlap)
//{
//	Vec3V vPlanePosToCenter = vSphere.GetCenter() - vPlane.GetPlanePos();
//	vOverlap = Dot(vPlanePosToCenter, vPlane.GetNormal());
//	return vSphere.GetRadiusSq() <= Abs(vOverlap);
//}


// Plane Intersections:

__forceinline bool TestPlaneToSphere(Plane_In vPlane, Sphere_In vSphere)
{
	return TestSphereToPlane(vSphere, vPlane);
}

__forceinline bool TestPlaneToAABB(Plane_In vPlane, AABB_In vAABB)
{
	return TestAABBToPlane(vAABB, vPlane);
}

//__forceinline bool TestPlaneToSphere(Plane_In vPlane, Sphere_In vSphere, ScalarV_Ref vOverlap)
//{
//	return IntersectSphereToPlane(vSphere, vPlane, vOverlap);
//}


// Ray Intersections:

__forceinline bool TestRayToAABB(Ray_In vRay, AABB_In vAABB)
{
	return TestAABBToRay(vAABB, vRay);
}

__forceinline bool TestRayToSphere(Ray_In vRay, Sphere_In vSphere)
{
	return TestSphereToRay(vSphere, vRay);
}


// AABB Intersections:

__forceinline bool TestAABBToAABB(AABB_In lhs, AABB_In rhs)
{
	return (IsGreaterThanOrEqualXYZ(lhs.GetMax(), rhs.GetMin()) & IsLessThanOrEqualXYZ(lhs.GetMin(), rhs.GetMax())) != 0;
}

inline bool TestAABBToCapsule(AABB_In vAABB, Capsule_In vCapsule)
{
	Vec3V vAABBCenter(vAABB.GetCenter());
	Vec3V vAABBExtents(vAABB.GetExtents());
	Vec3V vCapsuleOrigin(vCapsule.GetOrigin());
	Vec3V vCapsuleDir(vCapsule.GetDir());
	Vec3V vClosestPointToCapsule(vCapsuleOrigin + vCapsuleDir * Clamp(Dot(vCapsuleDir, vAABBCenter - vCapsuleOrigin), ScalarV(I_ZERO), vCapsule.GetExtent()));
	Vec3V vCenterToClosestPoint(vClosestPointToCapsule - vAABBCenter);
	Vec3V vClosestPointOnAABB(vAABBCenter + (Min(Abs(vCenterToClosestPoint), vAABBExtents) | (vCenterToClosestPoint & Vec3V(I_SIGN_BIT))));
	return MagSq(vClosestPointToCapsule - vClosestPointOnAABB) <= vCapsule.GetRadiusSq();
}

__forceinline bool TestAABBToFrustum(AABB_In vAABB, Frustum_In vFrustum)
{
	return TestFrustumToAABB(vFrustum, vAABB);
}

__forceinline bool TestAABBToPlane(AABB_In vAABB, Plane_In vPlane)
{
	Vec3V planeNormal(vPlane.GetNormal());
	Vec3V_ConstRef vMin(vAABB.GetMinRef());
	Vec3V_ConstRef vMax(vAABB.GetMaxRef());

	Vec3V vVertexP(SelectTF(IsLessThan(planeNormal, Vec3V(I_ZERO)), vMin, vMax));
	Vec3V vVertexN(SelectTF(IsGreaterThan(planeNormal, Vec3V(I_ZERO)), vMax, vMin));

	ScalarV vP_Result(Dot(vVertexP, planeNormal) + vPlane.GetOffset());
	ScalarV vN_Result(Dot(vVertexN, planeNormal) + vPlane.GetOffset());

	return ((vP_Result >= ScalarV(I_ZERO)) & (vN_Result <= ScalarV(I_ZERO)));
}

__forceinline bool TestAABBToPoint(AABB_In vAABB, Vec3V_In vPoint)
{
	return TestPointToAABB(vPoint, vAABB);
}

__forceinline bool TestAABBToRay(AABB_In vAABB, Ray_In vRay)
{
	Vec3V vAABBCenter = vAABB.GetCenter();
	Vec3V vClosestPointToAABB = vRay.GetDirRef() * Max(ScalarV(I_ZERO), Dot(vRay.GetDirRef(), vAABBCenter - vRay.GetOriginRef()));
	return TestPointToAABB(vClosestPointToAABB, vAABB);
}


// Frustum Intersections:
inline bool TestFrustumToSphere(Frustum_In vFrustum, Sphere_In vSphere)
{
	Assertf(vFrustum.IsTranposed(), "Frustum MUST be transposed in order to test against shapes");

	Vec4V_ConstRef vSphereV4 = vSphere.GetRef();

	Vec4V posX(vSphereV4.GetX());
	Vec4V posY(vSphereV4.GetY());
	Vec4V posZ(vSphereV4.GetZ());
	Vec4V negRadius(-vSphereV4.GetW());

	Mat44V_ConstRef vLRTB = vFrustum.GetLRTB();
	Vec4V vLRTBDotVal(posX * vLRTB.GetXAxisRef());
	vLRTBDotVal += posY * vLRTB.GetYAxisRef();
	vLRTBDotVal += posZ * vLRTB.GetZAxisRef();
	vLRTBDotVal += vLRTB.GetWAxisRef();

	Mat44V_ConstRef vNF = vFrustum.GetNF();
	Vec4V vNFDotVal(posX * vNF.GetXAxisRef());
	vNFDotVal += posY * vNF.GetYAxisRef();
	vNFDotVal += posZ * vNF.GetZAxisRef();
	vNFDotVal += vNF.GetWAxisRef();

	return (IsGreaterThanXYZW(vLRTBDotVal, negRadius) && IsGreaterThanXY(vNFDotVal, negRadius));
}

inline bool TestFrustumToAABB(Frustum_In vFrustum, AABB_In vAABB)
{
	Vec4V vMinX(vAABB.GetMinRef().GetX());
	Vec4V vMinY(vAABB.GetMinRef().GetY());
	Vec4V vMinZ(vAABB.GetMinRef().GetZ());
	Vec4V vMaxX(vAABB.GetMaxRef().GetX());
	Vec4V vMaxY(vAABB.GetMaxRef().GetY());
	Vec4V vMaxZ(vAABB.GetMaxRef().GetZ());
	Vec4V vZero(I_ZERO);

	Mat44V_ConstRef vLRTB = vFrustum.GetLRTB();
	Mat44V_ConstRef vNF = vFrustum.GetNF();

	Vec4V vVertPX(SelectTF(IsLessThan(vLRTB.GetXAxisRef(), vZero), vMinX, vMaxX));
	Vec4V vVertPY(SelectTF(IsLessThan(vLRTB.GetYAxisRef(), vZero), vMinY, vMaxY));
	Vec4V vVertPZ(SelectTF(IsLessThan(vLRTB.GetZAxisRef(), vZero), vMinZ, vMaxZ));

	Vec4V vLRTB_test(vVertPX * vLRTB.GetXAxisRef());
	vLRTB_test += vVertPY * vLRTB.GetYAxisRef();
	vLRTB_test += vVertPZ * vLRTB.GetZAxisRef();
	vLRTB_test += vLRTB.GetWAxisRef();

	vVertPX = SelectTF(IsLessThan(vLRTB.GetXAxisRef(), vZero), vMinX, vMaxX);
	vVertPY = SelectTF(IsLessThan(vLRTB.GetYAxisRef(), vZero), vMinY, vMaxY);
	vVertPZ = SelectTF(IsLessThan(vLRTB.GetZAxisRef(), vZero), vMinZ, vMaxZ);

	Vec4V vNF_test(vVertPX * vNF.GetXAxisRef());
	vNF_test += vVertPY * vNF.GetYAxisRef();
	vNF_test += vVertPZ * vNF.GetZAxisRef();
	vNF_test += vNF.GetWAxisRef();

	return IsGreaterThanOrEqualXYZW(vLRTB_test, vZero) && IsGreaterThanOrEqualXY(vNF_test, vZero);
}



// Misc Functions:

__forceinline Capsule_Out Transform(Capsule_In vCapsule, Mat43V_In vTransform)
{
	return Capsule(vCapsule.GetStart() * vTransform, vCapsule.GetEnd() * vTransform, vCapsule.GetRadius());
}

__forceinline Plane_Out Transform(Plane_In vPlane, Mat43V_In vTransform)
{
	return Plane(vPlane.GetNormal() * vTransform.GetMat33Ref(), vPlane.GetPos() * vTransform);
}

__forceinline Ray_Out Transform(Ray_In vRay, Mat43V_In vTransform)
{
	return Ray(vRay.GetOriginRef() * vTransform, vRay.GetDirRef() * vTransform.GetMat33Ref());
}

__forceinline Sphere_Out Transform(Sphere_In vSphere, Mat43V_In vTransform)
{
	return Sphere(vSphere.GetCenter() * vTransform, vSphere.GetRadius());
}