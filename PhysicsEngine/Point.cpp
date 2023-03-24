#include "Point.h"

YoungEngine::Point::Point(float x, float y, float z)
	:position(x,y,z)
{
}

float YoungEngine::Point::x() const
{
	return position.x;
}

float YoungEngine::Point::y() const
{
	return position.y;
}

float YoungEngine::Point::z() const
{
	return position.z;
}

float& YoungEngine::Point::rx()
{
	return position.x;
}
float& YoungEngine::Point::ry()
{
	return position.y;
}
float& YoungEngine::Point::rz()
{
	return position.z;
}


YoungEngine::Point::operator YoungEngine::Vector3() const
{
	return position;
}

YoungEngine::Point YoungEngine::Point::operator*(const float v)
{
	return Point(v * x(), v * y(), v * z());
}

void YoungEngine::Point::operator*=(const float v)
{
	position *= v;
}

YoungEngine::Vector3 YoungEngine::Point::operator-(const Point& v) const
{
	return position - v.position;
}

YoungEngine::Point YoungEngine::Point::operator+(const Point& v) const
{
	return Point(x() + v.x(), y() + v.y(), z() + v.z());
}

YoungEngine::Point YoungEngine::Point::operator+(const Vector3& v) const
{
	return Point(x() + v.x, y() + v.y, z() + v.z);
}

YoungEngine::Point YoungEngine::operator*(const float v, Point& point)
{
	return point * v;
}
