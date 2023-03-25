#include "RigidBody.h"
#include<limits>
#include"Math.h"
void YoungEngine::RigidBody::calculateDerivedData()
{
	orientation = glm::normalize(orientation);
	glm::mat3 m(orientation);
	//transform[0] = glm::vec4(m[0].x, m[0].y, m[0].z, 0);
	//transform[1] = glm::vec4(m[1].x, m[1].y, m[1].z, 0);
	//transform[2] = glm::vec4(m[2].x, m[2].y, m[2].z, 0);
	//transform[3] = glm::vec4(position.x,position.y,position.z,1);
	transform = { glm::vec4(m[0],0),glm::vec4(m[1],0),glm::vec4(m[2],0),glm::vec4(position.x,position.y,position.z,1) };
	transform_inv = glm::inverse(transform);
	inverseInertiaTensorWorld = m * inverseInertiaTensor * glm::transpose(m);
}

glm::mat4& YoungEngine::RigidBody::getTransformData()
{
	return transform;
}

YoungEngine::RigidBody::RigidBody()
	:inverseMass(0.1),linearDamping(1),angularDamping(1),position(0,0,0),velocity(0,0,0),rotation(0,0,0),
	constantAcceleration(0,0,0),forceAccum(0,0,0),torquesAcum(0,0,0),lastFrameAcceleration(0,0,0),
	isAwake(true)
{
}

void YoungEngine::RigidBody::setInertiaTensor(const glm::mat3& inertiaTensor)
{
	inverseInertiaTensor = glm::inverse(inertiaTensor);
}

void YoungEngine::RigidBody::addForce(const Vector3& force)
{
	forceAccum += force;
	isAwake = true;
}

void YoungEngine::RigidBody::clearAccumulators()
{
	forceAccum.clear();
	torquesAcum.clear();
}

void YoungEngine::RigidBody::addForceAtPoint(const Vector3& forceInWorld, const Vector3& pointInWorldSpace)
{
	Vector3 arm = pointInWorldSpace - transformLocalPointToWorldSpace({ 0,0,0 });
	forceAccum += forceInWorld;
	torquesAcum += arm.cross(forceInWorld);
	isAwake = true;
}

void YoungEngine::RigidBody::addForceAtBodyPoint(const Vector3& forceInWorld, const Vector3& pointInBodySpace)
{
	Vector3 pointInWorldSpace = transformLocalPointToWorldSpace(pointInBodySpace);
	addForceAtPoint(forceInWorld, pointInWorldSpace);
}

YoungEngine::Vector3 YoungEngine::RigidBody::transformWorldVectorToLocalSpace(const Vector3& vec) const
{
	//glm::mat3 rot = glm::transpose(glm::mat3(transform));
	//glm::mat4 tran;
	//tran[0] = glm::vec4(rot[0].x, rot[0].y, rot[0].z, 0);
	//tran[1] = glm::vec4(rot[1].x, rot[1].y, rot[1].z, 0);
	//tran[2] = glm::vec4(rot[2].x, rot[2].y, rot[2].z, 0);
	//tran[3] = glm::vec4(-transform[3].x, -transform[3].y, -transform[3].z, 1);
	//glm::vec4 res = tran * glm::vec4(vec.x, vec.y, vec.z, 0);
	glm::vec4 res = transform_inv * glm::vec4(vec.x, vec.y, vec.z, 0);
	return Vector3(res.x, res.y, res.z);
}

YoungEngine::Vector3 YoungEngine::RigidBody::transformLocalVectorToWorldSpace(const Vector3& vec) const
{
	glm::vec4 res = glm::vec4(vec.x, vec.y, vec.z, 0);
	res = transform * res;
	return Vector3(res.x, res.y, res.z);
}

YoungEngine::Vector3 YoungEngine::RigidBody::transformWorldPointToLocalSpace(const Vector3& point_in_world) const
{
	//glm::mat3 rot = glm::transpose(glm::mat3(transform));
	//glm::mat4 tran;
	//tran[0] = glm::vec4(rot[0].x, rot[0].y, rot[0].z, 0);
	//tran[1] = glm::vec4(rot[1].x, rot[1].y, rot[1].z, 0);
	//tran[2] = glm::vec4(rot[2].x, rot[2].y, rot[2].z, 0);
	//tran[3] = glm::vec4(-transform[3].x,-transform[3].y,-transform[3].z,1);
	glm::vec4 res = transform_inv * glm::vec4(point_in_world.x, point_in_world.y, point_in_world.z,1);
	return Vector3(res.x, res.y, res.z);
}

YoungEngine::Vector3 YoungEngine::RigidBody::transformLocalPointToWorldSpace(const Vector3& local_point) const
{
	glm::vec4 res = glm::vec4(local_point.x, local_point.y, local_point.z, 1);
	res = transform * res;
	return Vector3(res.x, res.y, res.z);
}

bool YoungEngine::RigidBody::hasFiniteMass() const
{
	return inverseMass != 0;
}

void YoungEngine::RigidBody::setMass(float mass)
{
	if (mass == 0)
	{
		inverseMass = INFINITY;
	}
	else if (mass == INFINITY)
	{
		inverseMass = 0;
	}
	else inverseMass = 1 / mass;
}

void YoungEngine::RigidBody::setLinearDamping(float damping)
{
	if (damping < 0) {
		damping = 0;
	}
	if (damping > 1)
	{
		damping = 1;
	}
	linearDamping = damping;
}

void YoungEngine::RigidBody::setAngularDamping(float angular_damping)
{
	angularDamping = angular_damping;
}

void YoungEngine::RigidBody::setPosition(const Vector3& pos)
{
	position = pos;
}

void YoungEngine::RigidBody::setVelocity(const Vector3& v)
{
	velocity = v;
}

void YoungEngine::RigidBody::setRotation(const Vector3& rot)
{
	rotation = rot;
}

void YoungEngine::RigidBody::setOrientation(const Vector3& axis, float radius)
{
	radius *= 0.5;
	float sine = glm::sin(radius);
	orientation.w = glm::cos(radius);
	orientation.x = axis.x * sine;
	orientation.y = axis.y * sine;
	orientation.z = axis.z * sine;
}

void YoungEngine::RigidBody::setInertiaTensor(const glm::mat4 iTensor)
{
	inverseInertiaTensor = glm::inverse(iTensor);
}

void YoungEngine::RigidBody::setConstantAcceleration(const Vector3& acc)
{
	constantAcceleration = acc;
}

float YoungEngine::RigidBody::getMass() const
{
	if (inverseMass == INFINITY)
	{
		return 0;
	}
	else if (inverseMass == 0)
	{
		return INFINITY;
	}
	return 1 / inverseMass;
}

YoungEngine::Vector3 YoungEngine::RigidBody::getPosition() const
{
	return position;
}

YoungEngine::Vector3 YoungEngine::RigidBody::getVelocity() const
{
	return velocity;
}

YoungEngine::Vector3 YoungEngine::RigidBody::getRotation() const
{
	return rotation;
}

void YoungEngine::RigidBody::integrate(float duration)
{
	lastFrameAcceleration = constantAcceleration;
	lastFrameAcceleration.addScaledVector(forceAccum, inverseMass);
	glm::vec3 anguAc = inverseInertiaTensorWorld * glm::vec3(torquesAcum.x, torquesAcum.y, torquesAcum.z);
	Vector3 angularAcceleration(anguAc.x, anguAc.y, anguAc.z);
	velocity.addScaledVector(lastFrameAcceleration, duration);
	rotation.addScaledVector(angularAcceleration, duration);
	velocity *= pow(linearDamping, duration);
	rotation *= pow(angularDamping, duration);
	position.addScaledVector(velocity, duration);
	RotateQuaternion(orientation, rotation,duration);
	calculateDerivedData();
	clearAccumulators();

}
