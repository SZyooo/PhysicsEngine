#include "Plane.h"

YoungEngine::Geometry::Plane::Plane(const Vec3D& norm, float d)
	:norm(norm),d(d)
{
}

YoungEngine::Geometry::Plane::Plane(const Vec3D& p1, const Vec3D& p2, const Vec3D& p3)
{
	Vec3D v1 = p1 - p2;
	Vec3D v2 = p2 - p3;
	Vec3D n = v1.cross(v2);
	n.normalize();
	norm = n;
	d = norm.dot(p1);
}

