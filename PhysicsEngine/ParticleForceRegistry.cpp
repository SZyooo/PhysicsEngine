#include "ParticleForceRegistry.h"
#include "ParticleForceGenerator.h"
void YoungEngine::ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* generator)
{
	record.push_back({particle,generator});
}

void YoungEngine::ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* generator)
{
	for (auto iter = record.begin(); iter != record.end(); iter++) {
		if (iter->p == particle && iter->generator == generator) {
			iter = record.erase(iter);
			return;
		}
	}
}

void YoungEngine::ParticleForceRegistry::clear()
{
	Record empty;
	record.swap(empty);
}

void YoungEngine::ParticleForceRegistry::updateForces(float duration)
{
	for (auto& registry : record) {
		registry.generator->updateForce(*registry.p, duration);
	}
}

