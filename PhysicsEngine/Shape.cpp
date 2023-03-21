#include "Shape.h"
#include <glm/gtc/matrix_transform.hpp>
std::vector<YoungEngine::Vertex>& YoungEngine::Shape::getVerticesData()
{
	return vertices;
}
std::vector<unsigned int>& YoungEngine::Shape::getIndicesData()
{
	return indices;
}
YoungEngine::Shape::Shape(const glm::mat4& m)
	:model(m)
{
}
void YoungEngine::Shape::move(const glm::vec3& translate)
{
	model = glm::translate(model, translate);
}

const glm::mat4& YoungEngine::Shape::getTransform() const
{
	return model;
}

const std::vector<YoungEngine::Vertex>& YoungEngine::Shape::getVertices()
{
	return vertices;
}

const std::vector<unsigned int>& YoungEngine::Shape::trianglatedIndices()
{
	return indices;
}

YoungEngine::Shape::~Shape()
{
}
