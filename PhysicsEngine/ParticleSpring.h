#pragma once
#include "ParticleForceGenerator.h"

namespace YoungEngine
{
	class ParticleSpring
	{
		Particle* particle;
		float springConstant;
		float restLength;
	public:
		ParticleSpring(Particle* p1,float constant, float rLen);
		virtual void updateForce(Particle& p, float duration);
	};
};