#include "VerticesCloud.h"
#include "Vertex.h"
YoungEngine::Geometry::VerticesCloud::VerticesCloud(const std::vector<Vec3D>& vertices, glm::mat4 model)
	:Shape(model)
{
	int n = vertices.size();
	auto& verts = getVerticesData();
	auto& indices = getIndicesData();
	for (int i = 0; i < n; i++)
	{
		Vertex v;
		v.position = vertices[i];
		verts.push_back(v);
		indices.push_back(i);
	}
}
