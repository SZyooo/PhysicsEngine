#pragma once
#include<vector>
#include<glm/glm.hpp>
#include "Vertex.h"
namespace YoungEngine
{
	class Vertex;
	class Shape
	{
		glm::mat4 model;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	protected:
		std::vector<Vertex>& getVerticesData();
		std::vector<unsigned int>& getIndicesData();
		glm::mat4& getTransformData();
	public:
		Shape(const glm::mat4& m = glm::mat4(1));
		virtual void move(const glm::vec3& translate);
		virtual const glm::mat4& getTransform()const;

		virtual const std::vector<Vertex>& getVertices();
		virtual const std::vector<unsigned int>& trianglatedIndices();
		virtual ~Shape();
	};
};
