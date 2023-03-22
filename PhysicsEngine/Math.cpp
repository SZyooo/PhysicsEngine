#include "Math.h"
#include "Vector3.h"
#include<assert.h>
void YoungEngine::GenOrthoNormalBasis(Vector3& v1, Vector3& v2, Vector3& v3)
{
	v3 = v1.cross(v2);
	assert(v3.squareMagnitude());
	v2 = v1.cross(v3);
	v1.normalize();
	v2.normalize();
	v3.normalize();
}

YoungEngine::Vector3 YoungEngine::Cross(const Vector3 & v1, const Vector3 & v2)
{
	return v1.cross(v2);
}

float YoungEngine::Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.dot(v2);
}

YoungEngine::Vector3 YoungEngine::Normalize(const Vector3& v)
{
	Vector3 nv = v;
	nv.normalize();
	return nv;
}

void YoungEngine::RotateQuaternion(glm::quat& q, const Vector3& rot, float duration)
{
	glm::quat q_ = q * glm::quat(0, rot.x, rot.y, rot.z);
	q_ *= duration * 0.5;
	q += q_;
}
