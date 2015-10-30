#ifndef _RECON_GLOBALSPATIALBOUNDSFUNCS_H_
#define _RECON_GLOBALSPATIALBOUNDSFUNCS_H_

namespace recon
{

#ifndef _RECON_SPATIALBOUNDS_H_
	#error "Don't Include GlobalSpatialBoundsFuncs.h Directly. Include SpatialBounds.h Instead!"
#endif // _RECON_SPATIALBOUNDS_H_


// Point Intersections:
bool TestPointToCapsule(Vec3V_In vPoint, Capsule_In vCapsule);

bool TestPointToSphere(Vec3V_In vPoint, Sphere_In vSphere);

bool TestPointToAABB(Vec3V_In vPoint, AABB_In vAABB);


// Capsule Intersections:

bool TestCapsuleToAABB(Capsule_In vCapsule, AABB_In vAABB);

bool TestCapsuleToPoint(Capsule_In vCapsule, Vec3V_In vPoint);

bool TestCapsuleToSphere(Capsule_In vCapsule, Sphere_In vSphere);


// Sphere Intersections:

bool TestSphereToCapsule(Sphere_In vSphere, Capsule_In vCapsule);

bool TestSphereToSphere(Sphere_In lhs, Sphere_In rhs);
// bool TestphereToSphere(Sphere_In lhs, Sphere_In rhs, ScalarV_Ref vOverlap);

// Returns True For Any Sort Of Intersection
bool TestSphereToPlane(Sphere_In vSphere, Plane_In vPlane);

bool TestSphereToPoint(Sphere_In vSphere, Vec3V_In vPoint);

bool TestSphereToRay(Sphere_In vSphere, Ray_In vRay);

bool TestSphereToFrustum(Sphere_In vSphere, Frustum_In vFrustum);

// Returns True For Any Sort Of Intersection
// vOverlap - Will Return Negative If The Sphere Is Behind The Plane
//bool TestSphereToPlane(Sphere_In vSphere, Plane_In vPlane, ScalarV_Ref vOverlap);


// Plane Intersections:

// Returns True For Any Sort Of Intersection
bool TestPlaneToSphere(Plane_In vPlane, Sphere_In vSphere);

bool TestPlaneToAABB(Plane_In vPlane, AABB_In vAABB);

// Returns True For Any Sort Of Intersection
// vOverlap - Will Return Negative If The Sphere Is Behind The Plane
// bool TestPlaneToSphere(Plane_In vPlane, Sphere_In vSphere, ScalarV_Ref vOverlap);


// Ray Intersections:

bool TestRayToAABB(Ray_In vRay, AABB_In vAABB);

bool TestRayToSphere(Ray_In vRay, Sphere_In vSphere);


// AABB Intersections:

bool TestAABBToAABB(AABB_In lhs, AABB_In rhs);

bool TestAABBToCapsule(AABB_In vAABB, Capsule_In vCapsule);

bool TestAABBToFrustum(AABB_In vAABB, Frustum_In vFrustum);

bool TestAABBToPlane(AABB_In vAABB, Plane_In vPlane);

bool TestAABBToPoint(AABB_In vAABB, Vec3V_In vPoint);

bool TestAABBToRay(AABB_In vAABB, Ray_In vRay);


// Frustum Intersections:

bool TestFrustumToSphere(Frustum_In vFrustum, Sphere_In vSphere);

bool TestFrustumToAABB(Frustum_In vFrustum, AABB_In vAABB);



// Misc Functions:

Capsule_Out Transform(Capsule_In vCapsule, Mat43V_In vTransform);

Plane_Out Transform(Plane_In vPlane, Mat43V_In vTransform);

Ray_Out Transform(Ray_In vRay, Mat43V_In vTransform);

Sphere_Out Transform(Sphere_In vSphere, Mat43V_In vTransform);


#include "GlobalSpatialBoundsFuncs.inl"

} // namespace recon

#endif // _RECON_GLOBALSPATIALBOUNDSFUNCS_H_