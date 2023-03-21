#include "ParticleSpring.h"
#include "Vector3.h"
#include "Particle.h"
#include<cmath>
YoungEngine::ParticleSpring::ParticleSpring(Particle* p1, float constant, float rLen)
	:particle(p1),springConstant(constant),restLength(rLen)
{

}

void YoungEngine::ParticleSpring::updateForce(Particle& p, float duration)
{
	Vector3 thisEndPos = particle->getPosition();
	Vector3 targetPos = p.getPosition();
	Vector3 d = targetPos - thisEndPos;
	Vector3 dir = d;
	dir.normalize();
	Vector3 force = -springConstant * abs(d.magnitude() - restLength) * dir;
	p.addForce(force);
}
