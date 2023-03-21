#pragma once
#include"ParticleForceGenerator.h"

namespace YoungEngine
{
	class ParticleBungee:public ParticleForceGenerator
	{
		Particle* particle;
		float springConstant;
		float restLength;
	public:
		ParticleBungee(Particle* p, float spring_constant, float rest_len);
		virtual void updateForce(Particle& p, float duration);
	};
};