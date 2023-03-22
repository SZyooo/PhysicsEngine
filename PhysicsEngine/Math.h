#pragma once
#include<glm/gtc/quaternion.hpp>
namespace YoungEngine {
	class Vector3;
	/// <summary>
	/// generate an orthornormal basis through two non-parallel vector v1,v2
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <param name="v3"></param>
	void GenOrthoNormalBasis(Vector3& v1,Vector3& v2,Vector3& v3);
	Vector3 Cross(const Vector3& v1, const Vector3& v2);
	float Dot(const Vector3& v1, const Vector3& v2);
	Vector3 Normalize(const Vector3& v);
	void RotateQuaternion(glm::quat& q,const Vector3& rot,float duration);
};
