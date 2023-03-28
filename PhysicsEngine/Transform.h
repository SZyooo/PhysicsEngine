#pragma once
#include "Vec3D.h"
#include <glm/gtc/quaternion.hpp>
namespace YoungEngine::Geometry
{
	class Transform
	{
		Vec3D position;
		glm::quat q;
	public:
		Transform();

		enum class ROTATEORDER
		{
			XYZ,XZY,
			YXZ,YZX,
			ZXY,ZYX
		};
		Vec3D getPosition() const;
		glm::quat getQuatRotation()const;
		/// <summary>
		/// get Eular angles
		/// </summary>
		Vec3D getRotation() const;
		glm::mat4 getTransformMatrix() const;
		void translate(const Vec3D& move);
		void rotate(const Vec3D& eularAngle, ROTATEORDER order);
		void rotate(const glm::quat& q);
	};
};