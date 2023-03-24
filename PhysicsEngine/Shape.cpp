#include "Shape.h"
#include <glm/gtc/matrix_transform.hpp>
std::vector<YoungEngine::Geometry::Vertex>& YoungEngine::Geometry::Shape::getVerticesData()
{
	return vertices;
}
std::vector<unsigned int>& YoungEngine::Geometry::Shape::getIndicesData()
{
	return indices;
}
glm::mat4& YoungEngine::Geometry::Shape::getTransformData()
{
	return model;
}
YoungEngine::Geometry::Shape::Shape(const glm::mat4& m)
	:model(m)
{
}
void YoungEngine::Geometry::Shape::move(const glm::vec3& translate)
{
	model = glm::translate(model, translate);
}

const glm::mat4& YoungEngine::Geometry::Shape::getTransform() const
{
	return model;
}

const std::vector<YoungEngine::Geometry::Vertex>& YoungEngine::Geometry::Shape::getVertices()
{
	return vertices;
}

const std::vector<unsigned int>& YoungEngine::Geometry::Shape::trianglatedIndices()
{
	return indices;
}

YoungEngine::Geometry::Shape::~Shape()
{
}

int YoungEngine::Geometry::Shape::getIndicesCount() const
{
	return indices.size();
}
