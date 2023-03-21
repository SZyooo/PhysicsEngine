#include "ParticleWrapper.h"
#include<glm/gtc/matrix_transform.hpp>
YoungEngine::ParticleWrapper::ParticleWrapper(Shape* pshape)
	:shape(pshape)
{
	if (shape == nullptr)
	{
		shape = new Shape;
	}
}

void YoungEngine::ParticleWrapper::move(const glm::vec3& translate)
{
	position += YoungEngine::Vector3(translate.x, translate.y, translate.z);
}

const glm::mat4& YoungEngine::ParticleWrapper::getTransform() const
{
	glm::vec3 pos = glm::vec3(position.x, position.y, position.z);
	return glm::translate(shape->getTransform(), pos);
}

const std::vector<YoungEngine::Vertex>& YoungEngine::ParticleWrapper::getVertices()
{
	
	return shape->getVertices();
}

const std::vector<unsigned int>& YoungEngine::ParticleWrapper::trianglatedIndices()
{
	return shape->trianglatedIndices();
}

YoungEngine::ParticleWrapper::~ParticleWrapper()
{
	delete shape;
}
