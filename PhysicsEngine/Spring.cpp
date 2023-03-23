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
	Vector3 connInWorld = rigidBody->transformLocalPointToWorldSpace(selfConnectionPoint);
	Vector3 theOtherEndInWorld = other->transformLocalPointToWorldSpace(theOtherEnd);
	Vector3 dir = connInWorld - theOtherEndInWorld;
	float mag = dir.magnitude();
	dir.normalize();
	Vector3 force = -springConstant * (mag - restLength) * dir;
	rigidBody->addForceAtPoint(force, connInWorld);
}
