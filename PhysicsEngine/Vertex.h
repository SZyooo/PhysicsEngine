#pragma once
#include"Vec3D.h"
namespace YoungEngine::Geometry
{
	class Vertex
	{
	public:
		Vec3D position;
		Vec3D norm;
		float u, v;
		const static int StructSize = 48;
	};
};