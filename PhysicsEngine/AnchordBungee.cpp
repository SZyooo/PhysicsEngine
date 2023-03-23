#include "AnchordBungee.h"
#include"RigidBody.h"
YoungEngine::AnchoredBungee::AnchoredBungee(const Vector3& anchor_pos_in_world, const Vector3& local_cnn_pos, float resLen, float constant)
	:anchorInWorld(anchor_pos_in_world),localConnectPoint(local_cnn_pos),restLength(resLen),springConstant(constant)
{
}

void YoungEngine::AnchoredBungee::updateForce(RigidBody* rigidBody, float duration)
{
	Vector3 connPosInWorld = rigidBody->transformLocalPointToWorldSpace(localConnectPoint);
	Vector3 d = connPosInWorld - anchorInWorld;
	float m = d.magnitude();
	if (m < restLength)
	{
		return;
	}
	d.normalize();
	Vector3 force = -springConstant * (m - restLength) * d;
	rigidBody->addForceAtPoint(force, connPosInWorld);
}
