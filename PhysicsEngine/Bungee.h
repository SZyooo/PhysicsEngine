#pragma once
#include"ForceGenerator.h"
#include"Vector3.h"
namespace YoungEngine
{
	class RigidBody;
	class Bungee:public ForceGenerator
	{
		RigidBody* otherBody;
		//this end in self's space
		Vector3 localConnectedPoint;
		//the other end in that body's space
		Vector3 theLocalOtherEnd;
		float springConstant;
		float restLength;
	public:
		Bungee(RigidBody* body, const Vector3& local_conn_point, const Vector3& the_other_end, float spring_constant, float resLen);
		virtual void updateForce(RigidBody* rigidBody, float duration);
	};
};