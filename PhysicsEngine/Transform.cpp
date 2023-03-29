#include "Transform.h"
#include <cmath>
#include <glm/gtc/quaternion.hpp>
namespace YoungEngine::Geometry
{
	Transform::Transform()
		:position({ 0,0,0 }), q(1,0,0,0), _scale({1,1,1})
	{
	}
	Vec3D Transform::getPosition() const
	{
		return position;
	}
	glm::quat Transform::getQuatRotation() const
	{
		return q;
	}
	Vec3D Transform::getRotation() const
	{
		Vec3D res;
		res.x = atan2(2 * (q[0] * q[1] + q[2] * q[3]), 1 - 2 * (q[1] * q[1] + q[2] * q[2]));
		res.y = asin(2 * (q[0] * q[2] - q[3] * q[1]));
		res.z = atan2(2 * (q[0] * q[3] + q[1] * q[2]), 1 - 2 * (q[2] * q[2] + q[3] * q[3]));
		return res;
	}
	glm::mat4 Transform::getTransformMatrix() const
	{
		auto nq = glm::normalize(q);
		glm::mat4 rot = glm::mat4_cast(nq);
		glm::mat4 move = glm::mat4({ 1,0,0,0 }, { 0,1,0,0 }, { 0,0,1,0 }, { position.x,position.y,position.z,1 });
		glm::mat4 scaleMat = { {_scale.x,0,0,0},{0,_scale.y,0,0},{0,0,_scale.z,0},{0,0,0,1} };
		return move * rot * scaleMat;
	}
	void Transform::translate(const Vec3D& move)
	{
		position += move;
	}
	void Transform::rotate(const Vec3D& eularAngle,ROTATEORDER order)
	{
		float r = eularAngle.x;
		float y = eularAngle.y;
		float p = eularAngle.z;
		glm::quat qx = { float(cos(r * 0.5)),float(sin(r * 0.5)),0,0 };
		glm::quat qy = { float(cos(y * 0.5)),0,float(sin(y * 0.5)),0 };
		glm::quat qz = { float(cos(p * 0.5)),0,0,float(sin(p * 0.5)) };
		glm::quat Q;
		switch (order)
		{
		case YoungEngine::Geometry::Transform::ROTATEORDER::XYZ:
			Q = qz * qy * qx;
			break;
		case YoungEngine::Geometry::Transform::ROTATEORDER::XZY:
			Q = qy * qz * qx;
			break;
		case YoungEngine::Geometry::Transform::ROTATEORDER::YXZ:
			Q = qz * qx * qy;
			break;
		case YoungEngine::Geometry::Transform::ROTATEORDER::YZX:
			Q = qx * qz * qy;
			break;
		case YoungEngine::Geometry::Transform::ROTATEORDER::ZXY:
			Q = qy * qx * qz;
			break;
		case YoungEngine::Geometry::Transform::ROTATEORDER::ZYX:
			Q = qx * qy * qz;
			break;
		default:
			Q = { 1,0,0,0 };
			break;
		}
		q = Q * q;
	}
	void Transform::rotate(const glm::quat& Q)
	{
		this->q = Q * this->q;
	}
	void Transform::scale(const Vec3D& s)
	{
		_scale = s;
	}
}

