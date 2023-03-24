#include"Vector3.h"
#include<cmath>
using namespace YoungEngine;

Vector3::Vector3() :x(0), y(0), z(0),padding(0) {}
Vector3::Vector3(float px, float py, float pz) :x(px), y(py), z(pz),padding(0) {}
void Vector3::invert() {
	x = -x;
	y = -y;
	z = -z;
}

float YoungEngine::Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

float YoungEngine::Vector3::squareMagnitude() const
{
	return x * x + y * y + z * z;
}

void YoungEngine::Vector3::normalize()
{
	float l = magnitude();
	if (l > 0) {
		(*this) *= 1.f / l;
	}
}

void YoungEngine::Vector3::clear()
{
	x = y = z = 0;
}

Vector3 YoungEngine::Vector3::operator*(float x) const
{
	return Vector3(this->x*x,y*x,z*x);
}

Vector3& YoungEngine::Vector3::operator*=(float x)
{
	this->x *= x;
	this->y *= x;
	this->z *= x;
	return *this;
}

Vector3 YoungEngine::Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3& YoungEngine::Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3 YoungEngine::Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x,y-other.y,z-other.z);
}

Vector3& YoungEngine::Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3& YoungEngine::Vector3::operator-()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

void YoungEngine::Vector3::addScaledVector(const Vector3& other, float factor)
{
	x += factor * other.x;
	y += factor * other.y;
	z += factor * other.z;
}

Vector3 YoungEngine::Vector3::componentProduct(const Vector3& other) const
{
	return Vector3(x * other.x,y * other.y,z * other.z);
}

void YoungEngine::Vector3::componentProductUpdate(const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

float YoungEngine::Vector3::dot(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float YoungEngine::Vector3::operator*(const Vector3& other) const
{
	return dot(other);
}

Vector3 YoungEngine::Vector3::cross(const Vector3& other) const
{
	return Vector3(y*other.z - z*other.y,z*other.x-x*other.z,x*other.y - y*other.x);
}

Vector3 YoungEngine::operator*(float val, const Vector3& v)
{
	return v * val;
}
