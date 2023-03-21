#pragma once
#include<vector>
namespace YoungEngine
{
	class Vertex;
	/// <summary>
/// create a buffer and move vertices data to the buffer
/// </summary>
/// <param name="vertices"></param>
/// <returns>buffer id</returns>
	unsigned int moveVertexToBuffer(const std::vector<YoungEngine::Vertex>& vertices);
	unsigned int generateVAOForCubeShader(unsigned int bufferid);
};
