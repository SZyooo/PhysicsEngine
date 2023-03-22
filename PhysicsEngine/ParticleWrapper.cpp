#include "ParticleWrapper.h"
#include<glm/gtc/matrix_transform.hpp>
YoungEngine::ParticleWrapper::ParticleWrapper(Shape* pshape)
	:shape(pshape)
{
	if (shape == nullptr)
	{
		shape = new Shape;
	}
	glm::vec4 pos = shape->getTransform()[3];
	position = Vector3(pos.x, pos.y, pos.z);
}

void YoungEngine::ParticleWrapper::move(const glm::vec3& translate)
{
	shape->move(translate);
}

const glm::mat4& YoungEngine::ParticleWrapper::getTransform() const
{
	YoungEngine::ParticleWrapper* _this = const_cast<YoungEngine::ParticleWrapper*>(this);
	glm::mat4 transform = shape->getTransform();
	transform[3] += glm::vec4(position.x, position.y, position.z, 0);
	_this->getTransformData() = transform;
	return _this->getTransformData();
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
