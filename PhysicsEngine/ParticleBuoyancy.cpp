#include "ParticleBuoyancy.h"
#include "Particle.h"
#include "Math.h"
YoungEngine::ParticleBuoyancy::ParticleBuoyancy(float mdepth, float v, float water_height, float liquid_dencity, Vector3 dir)
	:maxSubmersionDepth(mdepth),volume(v),waterHeight(water_height),liquidDencity(liquid_dencity),buoyancyDirection(Normalize(dir))
{
}

void YoungEngine::ParticleBuoyancy::updateForce(Particle& p, float duration)
{
	float depth = p.getPosition().dot(buoyancyDirection) - maxSubmersionDepth;
	//out of water
	if (depth >= waterHeight) return;
	if (depth <= (waterHeight - 2*maxSubmersionDepth))
	{
		Vector3 force = volume * liquidDencity * buoyancyDirection;
		p.addForce(force);
		return;
	}
	//partially submerged
	float factor = (depth - waterHeight) * liquidDencity * volume / 2.f * maxSubmersionDepth;
	Vector3 force = factor * buoyancyDirection;
	p.addForce(force);
}

