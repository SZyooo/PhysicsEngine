#pragma once
#include<vector>
#include<glm/glm.hpp>

namespace YoungEngine
{
	class Vertex;
	class Vector3;
	/// <summary>
/// create a buffer and move vertices data to the buffer
/// </summary>
/// <param name="vertices"></param>
/// <returns>buffer id</returns>
	unsigned int moveVertexToBuffer(const std::vector<YoungEngine::Vertex>& vertices);
	unsigned int generateVAOForCubeShader(unsigned int bufferid);
	glm::vec3 convertVector3ToGLMVec3(const Vector3& v);
	void drawBasis(const glm::vec3& pos, const glm::mat4& view, const glm::mat4& project);
};
