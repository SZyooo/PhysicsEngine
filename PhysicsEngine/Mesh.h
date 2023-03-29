#pragma once
#include <vector>
#include <string>
namespace YoungEngine::Geometry
{
	class Vertex;
}
namespace YoungEngine::Model
{

	class Mesh
	{
		std::vector < Geometry::Vertex> vertices;
		std::vector <unsigned int> indices;
		std::string name;
		std::vector<unsigned int> diffuses_texs;
		std::vector<unsigned int> specular_texs;
		std::vector<unsigned int> ambient_texs;
	public:
		Mesh(const std::string& name,const std::vector<Geometry::Vertex>& vertices, const std::vector <unsigned int>& indices);
		void draw(unsigned int vao, unsigned int program);
		void setDiffuses(const std::vector<unsigned int>& diffs);
		void setSpeuclars(const std::vector<unsigned int>& specs);
		void setAmbients(const std::vector<unsigned int>& ambients);
	};
};