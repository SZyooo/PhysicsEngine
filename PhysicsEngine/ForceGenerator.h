#pragma once
namespace YoungEngine
{
	class RigidBody;
	class ForceGenerator
	{
	public:
		virtual void updateForce(RigidBody* rigidBody, float duration) = 0;
		virtual ~ForceGenerator();
	};
};