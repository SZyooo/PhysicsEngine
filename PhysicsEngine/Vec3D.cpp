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
YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::operator+(const Vec3D& v) const
{
	return Vec3D(x + v.x, y + v.y, z + v.z);
}
void YoungEngine::Geometry::Vec3D::operator+=(const Vec3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
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

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::operator*(float v) const
{
	return Vec3D(x * v, y * v, z * v);
}

bool YoungEngine::Geometry::Vec3D::all() const
{
	return x && y && z;
}

bool YoungEngine::Geometry::Vec3D::any() const
{
	return x || y || z;
}

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::less(const Vec3D& v) const
{
	return Vec3D(x < v.x, y < v.y, z < v.z);
}

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::greater(const Vec3D& v) const
{
	return Vec3D(x > v.x, y > v.y, z > v.z);
}

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Vec3D::equalTo(const Vec3D& v, float tolerance)
{
	return Vec3D(
	fabs(x - v.x) <= tolerance,
	fabs(y - v.y) <= tolerance,
	fabs(z - v.z) <= tolerance
	);
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


YoungEngine::Geometry::Vec3D YoungEngine::Geometry::operator*(float val, const Vec3D& vec)
{
	return Vec3D(vec.x * val, vec.y * val, vec.z * val);
}
