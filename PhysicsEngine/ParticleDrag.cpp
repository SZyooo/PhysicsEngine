#include "ParticleDrag.h"
#include "Vector3.h"
#include "Particle.h"
YoungEngine::ParticleDrag::ParticleDrag(float pk1, float pk2)
	:k1(pk1), k2(pk2)
{
}

void YoungEngine::ParticleDrag::updateForce(Particle& p, float duration)
{
	Vector3 velocity = p.getVelocity();
	float coeff = velocity.magnitude();
	coeff = k1 * coeff + k2 * coeff * coeff;
	Vector3 dragForce = -velocity;
	dragForce.normalize();
	dragForce *= coeff;
	p.addForce(dragForce);
}
