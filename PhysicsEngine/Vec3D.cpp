#include "Vec3D.h"
#include <cmath>
#include "Vertex.h"
YoungEngine::Geometry::Vec3D::Vec3D(float x, float y, float z)
	:x(x),y(y),z(z)
{
}

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::componentProduct(const Vec3D& v) const
{
	return Vec3D(x * v.x, y * v.y, z * v.z);
}

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::operator-(const Vec3D& v) const
{
	return Vec3D(x - v.x, y - v.y, z - v.z);
}
bool YoungEngine::Geometry::Vec3D::operator==(const Vec3D& v)const 
{
	double d = (v - *this).squaredMagnitude();
	if (d <= 1E-10)
	{
		return true;
	}
	return false;
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
double YoungEngine::Geometry::Vec3D::squaredMagnitude()const
{
	return x * x + y * y + z * z;
}
YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::cross(const Vec3D& v3) const
{
	Vec3D res;
	res.x = y * v3.z - z * v3.y;
	res.y = z * v3.x - x * v3.z;
	res.z = x * v3.y - y * v3.x;
	return res;
}

float YoungEngine::Geometry::Vec3D::dot(const Vec3D& v) const
{
	return x * v.x + y * v.y + z * v.z;
}
