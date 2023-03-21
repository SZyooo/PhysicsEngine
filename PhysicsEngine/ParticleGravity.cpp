#include "ParticleGravity.h"
#include "Particle.h"
YoungEngine::ParticleGravity::ParticleGravity(const Vector3& g)
	:gravity(g)
{
}

void YoungEngine::ParticleGravity::updateForce(Particle& p, float duration)
{
	if (p.infiniteMass())return;
	p.addForce(gravity * p.getMass());
}
