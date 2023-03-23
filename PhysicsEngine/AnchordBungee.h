#pragma once
#include"ForceGenerator.h"
#include"Vector3.h"
namespace YoungEngine
{
	class AnchoredBungee :public ForceGenerator
	{
		Vector3 anchorInWorld;
		Vector3 localConnectPoint;
		float restLength;
		float springConstant;
	public:
		AnchoredBungee(const Vector3& anchor_pos, const Vector3& local_cnn_pos, float resLen, float constant);
		virtual void updateForce(RigidBody* rigidBody, float duration);
	};
};