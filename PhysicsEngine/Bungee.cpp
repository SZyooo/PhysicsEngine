#include "Bungee.h"
#include<cmath>
#include"RigidBody.h"

YoungEngine::Bungee::Bungee(RigidBody* body, const Vector3& local_conn_point, const Vector3& the_other_end, float spring_constant, float resLen)
	:otherBody(body),localConnectedPoint(local_conn_point),theLocalOtherEnd(the_other_end),springConstant(spring_constant),restLength(resLen)
{

}

void YoungEngine::Bungee::updateForce(RigidBody* rigidBody, float duration)
{
	Vector3 self_cnn = rigidBody->transformLocalPointToWorldSpace(localConnectedPoint);
	Vector3 other_cnn = otherBody->transformLocalPointToWorldSpace(theLocalOtherEnd);
	Vector3 d = self_cnn - other_cnn;
	float m = d.magnitude();
	if (m < restLength)
	{
		return;
	}
	d.normalize();
	Vector3 force = -springConstant * (m - restLength) * d;
	rigidBody->addForceAtPoint(force, self_cnn);
}

