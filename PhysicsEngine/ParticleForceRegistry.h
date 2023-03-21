#pragma once
#include<vector>
namespace YoungEngine {
	class Particle;
	class ParticleForceGenerator;
	class ParticleForceRegistry {
	protected:
		struct Registry{
			Particle* p;
			ParticleForceGenerator* generator;
		};
		typedef std::vector<Registry> Record;
		Record record;
	public:
		void add(Particle* particle, ParticleForceGenerator* generator);
		void remove(Particle* particle, ParticleForceGenerator* generator);
		void clear();
		void updateForces(float duration);
	};
};