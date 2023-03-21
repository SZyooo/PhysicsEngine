#pragma once
#include "ParticleForceGenerator.h"
#include "Vector3.h"
namespace YoungEngine
{
	class ParticleBuoyancy :public ParticleForceGenerator
	{
		//equal to the 0.5 * height of the object
		float maxSubmersionDepth;
		float volume;
		float waterHeight;
		float liquidDencity;
		Vector3 buoyancyDirection;
	public:
		ParticleBuoyancy(float mdepth, float v, float water_height, float liquid_dencity = 1000.f, Vector3 dir = Vector3(0, 1, 0));
		virtual void updateForce(Particle& p, float duration);
	};
};