#include "ParticleAnchoredSpring.h"
#include "Particle.h"
#include <cmath>
YoungEngine::ParticleAnchoredSpring::ParticleAnchoredSpring(const Vector3& anchor_pos, float spring_constant, float rest_len)
	:anchorPos(anchor_pos), springConstant(spring_constant), restLength(rest_len)
{
}

void YoungEngine::ParticleAnchoredSpring::updateForce(Particle& p, float duration)
{
	Vector3 dis = p.getPosition() - anchorPos;
	Vector3 dir = dis; dir.normalize();
	Vector3 force = -springConstant * abs(dis.magnitude() - restLength) * dir;
	p.addForce(force);
}

const YoungEngine::Vector3& YoungEngine::ParticleAnchoredSpring::getAnchorPosition() const
{
	return anchorPos;
}
