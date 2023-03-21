#include "ParticleBungee.h"
#include "Vector3.h"
#include "Particle.h"
#include <cmath>
YoungEngine::ParticleBungee::ParticleBungee(Particle* p, float spring_constant, float rest_len)
	:particle(p), springConstant(spring_constant), restLength(rest_len)
{
}

void YoungEngine::ParticleBungee::updateForce(Particle& p, float duration)
{
	Vector3 thisEnd = particle->getPosition();
	Vector3 targetPos = p.getPosition();
	Vector3 dis = targetPos - thisEnd;
	float len = dis.magnitude();
	float extent = len - restLength;
	if (extent <= 0)return;
	Vector3 dir = dis;
	dir.normalize();
	Vector3 force = -springConstant * extent * dir;
	p.addForce(force);
}


