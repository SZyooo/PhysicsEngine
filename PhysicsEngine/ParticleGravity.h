#pragma once
#include"ParticleForceGenerator.h"
#include"Vector3.h"
namespace YoungEngine {
	
	class ParticleGravity:ParticleForceGenerator
	{
		Vector3 gravity;
	public:
		ParticleGravity(const Vector3& g);
		virtual void updateForce(Particle& p, float duration);
	};
};