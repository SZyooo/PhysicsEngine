#pragma once
#include"Vector3.h"
#include"ForceGenerator.h"
namespace YoungEngine
{
	class Gravity:public ForceGenerator
	{
		Vector3 gravity;
	public:
		Gravity(const Vector3& g);
		virtual void updateForce(RigidBody* rigidBody, float duration);
	};
};