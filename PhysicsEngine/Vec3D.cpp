#include "Vec3D.h"

YoungEngine::Geometry::Vec3D::Vec3D(float x, float y, float z)
	:x(x),y(y),z(z)
{
}

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::componentProduct(const Vec3D& v) const
{
	return Vec3D(x * v.x, y * v.y, z * v.z);
}
