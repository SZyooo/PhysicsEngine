#include "Vec3D.h"
#include <cmath>
YoungEngine::Geometry::Vec3D::Vec3D(float x, float y, float z)
	:x(x),y(y),z(z)
{
}

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::componentProduct(const Vec3D& v) const
{
	return Vec3D(x * v.x, y * v.y, z * v.z);
}

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::normalize() const
{
	double m = magnitude();
	return Vec3D(x / m, y / m, z / m);
}

double YoungEngine::Geometry::Vec3D::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}
