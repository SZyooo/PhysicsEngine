#include "Vertex.h"

YoungEngine::Vertex::Vertex(float x, float y, float z)
	:position(x,y,z)
{
}

float YoungEngine::Vertex::x() const
{
	return position.x;
}

float YoungEngine::Vertex::y() const
{
	return position.y;
}

float YoungEngine::Vertex::z() const
{
	return position.z;
}

float& YoungEngine::Vertex::rx()
{
	return position.x;
}
float& YoungEngine::Vertex::ry()
{
	return position.y;
}
float& YoungEngine::Vertex::rz()
{
	return position.z;
}


YoungEngine::Vertex::operator YoungEngine::Vector3() const
{
	return position;
}

YoungEngine::Vertex YoungEngine::Vertex::operator*(const float v)
{
	return Vertex(v * x(), v * y(), v * z());
}

void YoungEngine::Vertex::operator*=(const float v)
{
	position *= v;
}

YoungEngine::Vector3 YoungEngine::Vertex::operator-(const Vertex& v) const
{
	return position - v.position;
}

YoungEngine::Vertex YoungEngine::Vertex::operator+(const Vertex& v) const
{
	return Vertex(x() + v.x(), y() + v.y(), z() + v.z());
}

YoungEngine::Vertex YoungEngine::Vertex::operator+(const Vector3& v) const
{
	return Vertex(x() + v.x, y() + v.y, z() + v.z);
}

YoungEngine::Vertex YoungEngine::operator*(const float v, Vertex& vertex)
{
	return vertex * v;
}
