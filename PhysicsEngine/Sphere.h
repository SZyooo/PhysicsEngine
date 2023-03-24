#pragma once
#include "Shape.h"
namespace YoungEngine::Geometry
{
	class Sphere:public Shape
	{
	public:
		/// <summary>
		/// detailLv describe the tesselation level of the sphere, if it is less than 5, it will be clamped to 5
		/// </summary>
		Sphere(int detailLv, float radius,const glm::mat4& model = glm::mat4(1));
	};
};