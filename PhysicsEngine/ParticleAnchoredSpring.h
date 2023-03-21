#pragma once
#include"ParticleForceGenerator.h"
#include"Vector3.h"
namespace YoungEngine
{
	class ParticleAnchoredSpring:public ParticleForceGenerator
	{
		Vector3 anchorPos;
		float springConstant;
		float restLength;
	public:
		ParticleAnchoredSpring(const Vector3& anchor_pos, float spring_constant, float rest_len);
		virtual void updateForce(Particle& p, float duration);
		const Vector3& getAnchorPosition()const;
	};
}