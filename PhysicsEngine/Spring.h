#pragma once
#include"ForceGenerator.h"
#include"Vector3.h"
namespace YoungEngine
{
	class Spring :public ForceGenerator
	{
		/// <summary>
		/// connection point in this body's space
		/// </summary>
		Vector3 selfConnectionPoint;
		/// <summary>
		/// spring's the other end in the other body's space
		/// </summary>
		Vector3 theOtherEnd;
		RigidBody* other;
		float springConstant;
		float restLength;
	public:
		Spring(const Vector3& localConnectionPos,RigidBody* theOtherBody, const Vector3& theOtherConnectEnd, float constant, float restLen);
		virtual void updateForce(RigidBody* rigidBody, float duration);
	};
}