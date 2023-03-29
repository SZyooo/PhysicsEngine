#include "Mesh.h"
#include <GL/glew.h>
#include "Vertex.h"
YoungEngine::Model::Mesh::Mesh(const std::string&name, const std::vector<YoungEngine::Geometry::Vertex>& vertices, const std::vector<unsigned int>& indices)
	:vertices(vertices),indices(indices),name(name)
{
}

void YoungEngine::Model::Mesh::draw(unsigned int vao, unsigned int program)
{
	glUseProgram(program);
	glBindVertexArray(vao);
	int texCount = 0;
	for (int i = 0; i < specular_texs.size(); i++)
	{
		glBindTextureUnit(texCount++, specular_texs[i]);
	}
	for (int i = 0; i < diffuses_texs.size(); i++)
	{
		glBindTextureUnit(texCount++, diffuses_texs[i]);
	}
	for (int i = 0; i < ambient_texs.size(); i++)
	{
		glBindTextureUnit(texCount++, ambient_texs[i]);
	}
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
}

void YoungEngine::Model::Mesh::setDiffuses(const std::vector<unsigned int>& diffs)
{
	diffuses_texs = diffs;
}

void YoungEngine::Model::Mesh::setSpeuclars(const std::vector<unsigned int>& specs)
{
	specular_texs = specs;
}

void YoungEngine::Model::Mesh::setAmbients(const std::vector<unsigned int>& ambients)
{
	ambient_texs = ambients;
}
