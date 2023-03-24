#pragma once
#include "Vector3.h"
namespace YoungEngine
{
	
	class Point
	{
		Vector3 position;
	public:
		Point(float x, float y, float z);
		const static size_t StructSize = 16;
		float x()const;
		float y()const;
		float z()const;
		float& rx();
		float& ry();
		float& rz();
		operator YoungEngine::Vector3()const;
		Point operator*(const float v);
		void operator*=(const float v);
		friend Point operator*(const float v, Point& vertex);
		Vector3 operator-(const Point& v)const;
		Point operator+(const Point& v)const;
		Point operator+(const Vector3& v)const;
	};
};
