#pragma once
#include"Vector3.h"
namespace YoungEngine {
	class Particle {
	protected:
		Vector3 position;
		Vector3 velocity;
		/// <summary>
		/// 这个加速是恒加速，例如重力加速度
		/// </summary>
		Vector3 acceleration;
		Vector3 forceAccum;
		float dampling;
		float inverseMass;
	public:
		void setPosition(const Vector3& pos);
		Vector3 getPosition()const;
		void setVelocity(const Vector3& v);
		Vector3 getVelocity()const;
		void setAcceleration(const Vector3& acc);
		Vector3 getAcceleration()const;
		void setDamping(float d);
		float getDampling()const ;
		void setMass(float m);
		float getMass()const;
		float getInverseMass()const;
		bool infiniteMass()const;
		
		void addForce(const Vector3& force);
		void integrate(float duration);
		void clearAccumulator();
	};
};