#pragma once
#include<vector>
#include<glm/glm.hpp>
#include <string>
namespace YoungEngine
{
	namespace Geometry
	{
		class Vertex;
	}
	class Vector3;
	/// <summary>
/// create a buffer and move vertices data to the buffer
/// </summary>
/// <param name="vertices"></param>
/// <returns>buffer id</returns>
	unsigned int moveVertexToBuffer(const std::vector<Geometry::Vertex>& vertices);
	unsigned int generateVAOForDefaultShader(unsigned int bufferid);
	glm::vec3 convertVector3ToGLMVec3(const Vector3& v);
	void drawBasis(const glm::vec3& pos, const glm::mat4& view, const glm::mat4& project);
	void setMat4(unsigned int program, const glm::mat4& mat, std::string name);
};
