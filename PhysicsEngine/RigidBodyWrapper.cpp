#include "RigidBodyWrapper.h"

YoungEngine::RigidBodyWrapper::RigidBodyWrapper(Geometry::Shape* shape)
	:shape(shape)
{
	if (shape == nullptr)
	{
		shape = new Geometry::Shape;
	}
}

void YoungEngine::RigidBodyWrapper::move(const glm::vec3& translate)
{
	Vector3 pos = getPosition();
	Vector3 move(translate.x, translate.y, translate.z);
	setPosition(pos + move);
}

const glm::mat4& YoungEngine::RigidBodyWrapper::getTransform() const
{
	//RigidBodyWrapper* _this = const_cast<RigidBodyWrapper*>(this);
	//glm::mat4 m = shape->getTransform();
	//Vector3 pos = getPosition();
	//m[3] += glm::vec4(pos.x, pos.y, pos.z, 0);
	//_this->getTransformData() = m;
	//return _this->getTransformData();
	RigidBodyWrapper* _this = const_cast<RigidBodyWrapper*>(this);
	return _this->RigidBody::getTransformData();
}

const std::vector<YoungEngine::Geometry::Vertex>& YoungEngine::RigidBodyWrapper::getVertices()
{
	return shape->getVertices();
}

const std::vector<unsigned int>& YoungEngine::RigidBodyWrapper::trianglatedIndices()
{
	return shape->trianglatedIndices();
}

YoungEngine::RigidBodyWrapper::~RigidBodyWrapper()
{
	delete shape;
}
