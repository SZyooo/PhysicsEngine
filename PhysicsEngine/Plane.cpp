#include "Plane.h"
#include <random>
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

YoungEngine::Geometry::Vec3D YoungEngine::Geometry::Plane::getNorm() const
{
	return norm;
}

float YoungEngine::Geometry::Plane::queryX(float y, float z, bool& valid) const
{
	if (norm.x == 0)
	{
		valid = false;
		return 1;
	}
	valid = true;
	return (d - y * norm.y - z * norm.z) / norm.x;
}

float YoungEngine::Geometry::Plane::queryY(float x, float z, bool& valid) const
{
	if (norm.y == 0)
	{
		valid = false;
		return 1;
	}
	valid = true;
	return (d - x * norm.x - z * norm.z) / norm.y;
}

float YoungEngine::Geometry::Plane::queryZ(float x, float y, bool& valid) const
{
	if (norm.z == 0)
	{
		valid = false;
		return 1;
	}
	valid = true;
	return (d - x * norm.x - y * norm.y) / norm.z;
}

std::vector<YoungEngine::Geometry::Vec3D> YoungEngine::Geometry::Plane::generateTwoVertices() const
{
	Vec3D v1;
	Vec3D v2;
	if (norm.x != 0)
	{
		bool t;
		int y = rand() % 10 + 1;
		int z = rand() % 10 + 1;
		v1.x = queryX(y, z, t);
		v1.y = y;
		v1.z = z;
		v2.x = queryX(y, z+1, t);
		v2.y = y;
		v2.z = z + 1;
		return { v1,v2 };
	}
	if (norm.y != 0)
	{
		bool t;
		int x = rand() % 10 + 1;
		int z = rand() % 10 + 1;
		v1.y = queryY(x, z, t);
		v1.x = x;
		v1.z = z;
		v2.y = queryY(x, z+1, t);
		v2.x = x;
		v2.z = z + 1;
		return { v1,v2 };
	}
	if (norm.z != 0)
	{
		bool t;
		int x = rand() % 10 + 1;
		int y = rand() % 10 + 1;
		v1.z = queryY(x, y, t);
		v1.x = x;
		v1.y = y;
		v2.z = queryY(x, y + 1, t);
		v2.x = x;
		v2.y = y + 1;
		return { v1,v2 };
	}
}


