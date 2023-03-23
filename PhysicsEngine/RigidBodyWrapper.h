#pragma once
#include"Shape.h"
#include"RigidBody.h"
namespace YoungEngine
{
	class RigidBodyWrapper :public RigidBody, public Shape
	{
		Shape* shape;
	public:
		RigidBodyWrapper(Shape* shape);
		virtual void move(const glm::vec3& translate);
		virtual const glm::mat4& getTransform()const;

		virtual const std::vector<Vertex>& getVertices();
		virtual const std::vector<unsigned int>& trianglatedIndices();
		virtual ~RigidBodyWrapper();

	};


};