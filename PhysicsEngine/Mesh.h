#pragma once
#include <vector>
namespace YoungEngine::Geometry
{
	class Vec3D;
}
namespace YoungEngine::Model
{

	class Mesh
	{
		std::vector < YoungEngine::Geometry::Vec3D> vertices;
		std::vector <unsigned int> indices;
		
	public:
		Mesh(const std::vector<YoungEngine::Geometry::Vec3D>& vertices, const std::vector <unsigned int>& indices);
		void draw(unsigned int vao, unsigned int program);
	};
};