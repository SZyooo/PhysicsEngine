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

	};


};