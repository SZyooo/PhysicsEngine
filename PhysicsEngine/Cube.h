#pragma once
#include"Shape.h"
#include"Vertex.h"
namespace YoungEngine
{
	class Cube:public Shape
	{
	public:
		Cube(const glm::mat4& m,float xspan,float yspan,float zspan);
	};
};