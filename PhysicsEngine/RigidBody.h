#pragma once
#include "Vector3.h"
#include<glm/gtc/quaternion.hpp>
namespace YoungEngine
{
	
	class RigidBody
	{
		float inverseMass;
		float linearDamping;
		float angularDamping;
		Vector3 position;
		Vector3 velocity;
		Vector3 rotation;
		Vector3 constantAcceleration;
		glm::quat orientation;
		glm::mat4 transform;
		glm::mat3 inverseInertiaTensor;
		glm::mat3 inverseInertiaTensorWorld;
		
		Vector3 forceAccum;
		Vector3 torquesAcum;
		Vector3 lastFrameAcceleration;

		bool isAwake;

		void calculateDerivedData();
	protected:
		glm::mat4& getTransformData();
	public:
		void setInertiaTensor(const glm::mat3& inertiaTensor);
		void addForce(const Vector3& force);
		void clearAccumulators();
		void addForceAtPoint(const Vector3& forceInWorld,const Vector3& pointInWorldSpace);
		void addForceAtBodyPoint(const Vector3& forceInWorld, const Vector3& pointInBodySpace);
		Vector3 transformWorldPointToLocalSpace(const Vector3& point_in_world) const ;
		Vector3 transformLocalPointToWorldSpace(const Vector3& local_point) const ;
		Vector3 transformWorldVectorToLocalSpace(const Vector3& vec) const;
		Vector3 transformLocalVectorToWorldSpace(const Vector3& vec) const;

		bool hasFiniteMass() const;

		void setMass(float mass);
		/// <summary>
		/// damping will be clamped to range[0,1]
		/// </summary>
		/// <param name="damping"></param>
		void setLinearDamping(float damping);
		void setAngularDamping(float angular_damping);
		void setPosition(const Vector3& pos);
		void setVelocity(const Vector3& v);
		void setRotation(const Vector3& rot);
		void setOrientation(const Vector3& axis, float radius);
		void setInertiaTensor(const glm::mat4 iTensor);
		void setConstantAcceleration(const Vector3& acc);

		float getMass()const;
		Vector3 getPosition()const;
		Vector3 getVelocity()const;
		Vector3 getRotation()const;

		void integrate(float duration);
	};
};