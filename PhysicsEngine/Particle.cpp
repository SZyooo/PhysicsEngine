#include "Particle.h"
#include<assert.h>
#include<cmath>
#include<limits>
void YoungEngine::Particle::addForce(const Vector3& force)
{
	forceAccum += force;
}
void YoungEngine::Particle::integrate(float duration)
{
	if (inverseMass == 0)
	{
		return;
	}
	assert(duration > 0);
	position.addScaledVector(velocity, duration);
	Vector3 resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAccum, inverseMass);
	velocity.addScaledVector(resultingAcc, duration);
	velocity *= pow(dampling, duration);
	clearAccumulator();
}

void YoungEngine::Particle::clearAccumulator()
{
	forceAccum.clear();
}

void YoungEngine::Particle::setPosition(const Vector3& pos)
{
	position = pos;
}

YoungEngine::Vector3 YoungEngine::Particle::getPosition() const
{
	return position;
}

void YoungEngine::Particle::setVelocity(const Vector3& v)
{
	velocity = v;
}

YoungEngine::Vector3 YoungEngine::Particle::getVelocity() const
{
	return velocity;
}

void YoungEngine::Particle::setAcceleration(const Vector3& acc)
{
	acceleration = acc;
}

YoungEngine::Vector3 YoungEngine::Particle::getAcceleration() const
{
	return acceleration;
}

void YoungEngine::Particle::setDamping(float d)
{
	dampling = d;
}

float YoungEngine::Particle::getDampling()const
{
	return dampling;
}

void YoungEngine::Particle::setMass(float m)
{
	if (m == 0) 
	{
		inverseMass = INFINITY;
	}
	else
	{
		inverseMass = 1.f / m;
	}
}

float YoungEngine::Particle::getMass() const
{
	if (inverseMass == 0) 
	{
		return INFINITY;
	}
	else
	{
		return 1.f / inverseMass;
	}
}

float YoungEngine::Particle::getInverseMass() const
{
	return inverseMass;
}

bool YoungEngine::Particle::infiniteMass() const
{
	return inverseMass == 0;
}
