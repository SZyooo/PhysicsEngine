#pragma once
#include"Shape.h"
namespace YoungEngine::Geometry
{
	class Vec3D;
	class VerticesCloud:public Shape
	{
		
	public:
		VerticesCloud(const std::vector<Vec3D>& vertices,glm::mat4 model = glm::mat4(1));
	};
};