#pragma once
#include"Particle.h"
#include"Shape.h"

namespace YoungEngine
{
	class ParticleWrapper :public Particle, public Geometry::Shape
	{
		Shape* shape;
	public:
		ParticleWrapper(Shape* shape);
		virtual void move(const glm::vec3& translate);
		virtual const glm::mat4& getTransform()const;

		virtual const std::vector<Geometry::Vertex>& getVertices();
		virtual const std::vector<unsigned int>& trianglatedIndices();
		virtual ~ParticleWrapper();
	};
};
