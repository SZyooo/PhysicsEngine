#pragma once
#include "Vector3.h"
namespace YoungEngine
{
	
	class Vertex
	{
		Vector3 position;
	public:
		Vertex(float x, float y, float z);
		const static size_t StructSize = 16;
	};
};
