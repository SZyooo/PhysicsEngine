#pragma once
#include"ParticleForceGenerator.h"
namespace YoungEngine {
	class ParticleDrag :public ParticleForceGenerator
	{
		float k1, k2;
	public:
		ParticleDrag(float pk1, float pk2);
		virtual void updateForce(Particle& p, float duration);
	};

};