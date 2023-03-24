#pragma once
#include "Vector3.h"
namespace YoungEngine
{
	
	class Vertex
	{
		Vector3 position;
	public:
		Vertex(float x, float y, float z);
		const static size_t StructSize = 16;
		float x()const;
		float y()const;
		float z()const;
		float& rx();
		float& ry();
		float& rz();
		operator YoungEngine::Vector3()const;
		Vertex operator*(const float v);
		void operator*=(const float v);
		friend Vertex operator*(const float v, Vertex& vertex);
		Vector3 operator-(const Vertex& v)const;
		Vertex operator+(const Vertex& v)const;
		Vertex operator+(const Vector3& v)const;
	};
};
