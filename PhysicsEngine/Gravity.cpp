#include "Gravity.h"
#include "RigidBody.h"
YoungEngine::Gravity::Gravity(const Vector3& g)
	:gravity(g)
{
}

void YoungEngine::Gravity::updateForce(RigidBody* rigidBody, float duration)
{
	if (rigidBody->hasFiniteMass() == false)
	{
		return;
	}
	rigidBody->addForce(gravity * rigidBody->getMass());
}
