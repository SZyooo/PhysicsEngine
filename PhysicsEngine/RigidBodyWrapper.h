#pragma once
#include"Shape.h"
#include"RigidBody.h"
namespace YoungEngine
{
	class RigidBodyWrapper :public RigidBody, public Geometry::Shape
	{
		Shape* shape;
	public:
		RigidBodyWrapper(Geometry::Shape* shape);
		virtual void move(const glm::vec3& translate);
		virtual const glm::mat4& getTransform()const;

		virtual const std::vector<Geometry::Vertex>& getVertices();
		virtual const std::vector<unsigned int>& trianglatedIndices();
		virtual ~RigidBodyWrapper();
		virtual int getIndicesCount()const;
		virtual Vector3 transformWorldPointToLocalSpace(const Vector3& point_in_world) const;
		virtual Vector3 transformLocalPointToWorldSpace(const Vector3& local_point) const;
		virtual Vector3 transformWorldVectorToLocalSpace(const Vector3& vec) const;
		virtual Vector3 transformLocalVectorToWorldSpace(const Vector3& vec) const;
	};


};