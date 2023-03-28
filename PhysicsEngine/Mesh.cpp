#include "Mesh.h"
#include "Vec3D.h"
#include <GL/glew.h>
YoungEngine::Model::Mesh::Mesh(const std::vector<YoungEngine::Geometry::Vec3D>& vertices, const std::vector<unsigned int>& indices)
	:vertices(vertices),indices(indices)
{
}

void YoungEngine::Model::Mesh::draw(unsigned int vao, unsigned int program)
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
}
