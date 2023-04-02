#include "Mesh.h"
#include <GL/glew.h>
#include "Vertex.h"
#include "HelperFuncs.h"
YoungEngine::Model::Mesh::Mesh(const std::string&name, const std::vector<YoungEngine::Geometry::Vertex>& vertices, const std::vector<unsigned int>& indices)
	:vertices(vertices),indices(indices),name(name)
{

	vertex_buffer = moveVertexToBuffer(vertices);
	vao = generateVAOForDefaultShader(vertex_buffer);
}

YoungEngine::Model::Mesh::Mesh(Mesh&& m)noexcept
	:name(m.name),vertex_buffer(m.vertex_buffer),
	vao(m.vao)
{
	vertices.swap(m.vertices);
	indices.swap(m.indices);
	diffuses_texs.swap(m.diffuses_texs);
	specular_texs.swap(m.specular_texs);
	ambient_texs.swap(m.ambient_texs);
	m.vertex_buffer = 0;
	m.vao = 0;
}

YoungEngine::Model::Mesh& YoungEngine::Model::Mesh::operator=(Mesh&& m)noexcept
{
	vertices.swap(m.vertices);
	indices.swap(m.indices);
	name = m.name;
	diffuses_texs.swap(m.diffuses_texs);
	specular_texs.swap(m.specular_texs);
	ambient_texs.swap(m.ambient_texs);
	vertex_buffer = m.vertex_buffer;
	vao = m.vao;
	m.vertex_buffer = 0;
	m.vao = 0;
	return *this;
}



void YoungEngine::Model::Mesh::draw(unsigned int program)
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

void YoungEngine::Model::Mesh::drawNorm(const unsigned int program)
{
	glBindVertexArray(vao);
	glUseProgram(program);
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
YoungEngine::Model::Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteVertexArrays(1, &vao);
}