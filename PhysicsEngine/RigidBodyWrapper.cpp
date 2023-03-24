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
	RigidBodyWrapper* _this = const_cast<RigidBodyWrapper*>(this);
	glm::mat4& transform = _this->Shape::getTransformData();
	transform = _this->RigidBody::getTransformData() * shape->getTransform();
	//transform = shape->getTransform();
	//transform = _this->RigidBody::getTransformData() * transform;
	return transform;
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

int YoungEngine::RigidBodyWrapper::getIndicesCount() const
{
	return shape->getIndicesCount();
}

YoungEngine::Vector3 YoungEngine::RigidBodyWrapper::transformWorldPointToLocalSpace(const Vector3& point_in_world) const
{
	Vector3 toRigidBodySpace = RigidBody::transformWorldPointToLocalSpace(point_in_world);
	glm::vec4 v = glm::vec4(toRigidBodySpace.x, toRigidBodySpace.y, toRigidBodySpace.z, 1);
	glm::mat4 toModel;
	glm::mat4 shape_model = shape->getTransform();
	toModel[0] = glm::vec4(shape_model[0].x, shape_model[1].x, shape_model[2].x, 0);
	toModel[1] = glm::vec4(shape_model[0].y, shape_model[1].y, shape_model[2].y, 0);
	toModel[2] = glm::vec4(shape_model[0].z, shape_model[1].z, shape_model[2].z, 0);
	toModel[3] = glm::vec4(-shape_model[3].x, -shape_model[3].y, -shape_model[3].y, 1);
	glm::vec4 res = toModel * v;
	return {res.x,res.y,res.z};
}

YoungEngine::Vector3 YoungEngine::RigidBodyWrapper::transformLocalPointToWorldSpace(const Vector3& local_point) const
{
	glm::vec4 v(local_point.x,local_point.y,local_point.z,1);
	v = shape->getTransform() * v;
	return RigidBody::transformLocalPointToWorldSpace({ v.x,v.y,v.z });
}

YoungEngine::Vector3 YoungEngine::RigidBodyWrapper::transformWorldVectorToLocalSpace(const Vector3& vec) const
{
	Vector3 toRigidBodySpace = RigidBody::transformWorldVectorToLocalSpace(vec);
	glm::vec4 v = glm::vec4(toRigidBodySpace.x, toRigidBodySpace.y, toRigidBodySpace.z, 0);
	glm::mat4 toModel;
	glm::mat4 shape_model = shape->getTransform();
	toModel[0] = glm::vec4(shape_model[0].x, shape_model[1].x, shape_model[2].x, 0);
	toModel[1] = glm::vec4(shape_model[0].y, shape_model[1].y, shape_model[2].y, 0);
	toModel[2] = glm::vec4(shape_model[0].z, shape_model[1].z, shape_model[2].z, 0);
	toModel[3] = glm::vec4(-shape_model[3].x, -shape_model[3].y, -shape_model[3].y, 1);
	glm::vec4 res = toModel * v;
	return { res.x,res.y,res.z };
}

YoungEngine::Vector3 YoungEngine::RigidBodyWrapper::transformLocalVectorToWorldSpace(const Vector3& vec) const
{
	glm::vec4 v(vec.x, vec.y, vec.z, 0);
	v = shape->getTransform() * v;
	return RigidBody::transformLocalPointToWorldSpace({ v.x,v.y,v.z });
}
