#pragma once
#include"Shape.h"
#include<vector>
namespace YoungEngine::Geometry
{
	class Vec3D;
	class Vec2D;
	class Polygon:public Shape
	{
	public:
		/// <summary>
		/// generate a polygon. the norm will be randomly pointed.
		/// uv coords are all set zero
		/// </summary>
		Polygon(const std::vector<Vec3D>& vertices, const glm::mat4& model = glm::mat4(1));
		/// <summary>
		/// without uv coords being given, they are all set zero
		/// </summary>
		Polygon(const std::vector<Vec3D>& vertices,const Vec3D&norm, const glm::mat4& model = glm::mat4(1));
		/// <summary>
		/// UVs's size should at least equal to vertices's, or the remaining vertices will get (0,0)
		/// </summary>
		Polygon(const std::vector<Vec3D>& vertices, const std::vector<Vec2D>& UVs,const Vec3D& norm, const glm::mat4& model = glm::mat4(1));
	};
};