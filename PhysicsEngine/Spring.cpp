#include "Spring.h"
#include "RigidBody.h"
YoungEngine::Spring::Spring(const Vector3& localConnectionPos, RigidBody* theOtherBody, const Vector3& theOtherConnectEnd, float constant, float restLen)
	:selfConnectionPoint(localConnectionPos),
	theOtherEnd(theOtherConnectEnd),
	other(theOtherBody),
	springConstant(constant),
	restLength(restLen)
{
}

void YoungEngine::Spring::updateForce(RigidBody* rigidBody, float duration)
{
	Vector3 dir = selfConnectionPoint - theOtherEnd;
	float mag = dir.magnitude();
	dir.normalize();
	Vector3 force = -springConstant * (mag - restLength) * dir;
	Vector3 forceInWorld = rigidBody->transformLocalVectorToWorldSpace(force);
	rigidBody->addForceAtBodyPoint(forceInWorld, selfConnectionPoint);
}
