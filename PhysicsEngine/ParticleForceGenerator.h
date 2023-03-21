#pragma once
namespace YoungEngine {
	class Particle;
	class ParticleForceGenerator {
	public:
		virtual void updateForce(Particle& p, float duration) = 0;
	};
};