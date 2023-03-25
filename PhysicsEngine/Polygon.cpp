#include "Polygon.h"
#include "Vec3D.h"
#include "Vec2D.h"
YoungEngine::Geometry::Polygon::Polygon(const std::vector<Vec3D>& vertices, const glm::mat4& model)
	:Shape(model)
{
	if (vertices.size() < 3)
	{
		return;
	}
	int n = vertices.size();
	auto& verts = getVerticesData();
	auto& indices = getIndicesData();
	const Vec3D& v1 = vertices[0];
	const Vec3D& v2 = vertices[n / 2];
	const Vec3D& v3 = vertices[n - 1];
	Vec3D norm = (v2 - v1).cross(v3 - v1).normalize();
	for (int i = 0; i < n; i++)
	{
		Vertex v;
		v.norm = norm;
		v.position = vertices[i];
		v.u = v.v = 0;
		verts.push_back(v);
		indices.push_back(i);
	}
}

YoungEngine::Geometry::Polygon::Polygon(const std::vector<Vec3D>& vertices, const Vec3D& norm, const glm::mat4& model)
	:Shape(model)
{
	if (vertices.size() < 3)
	{
		return;
	}
	int n = vertices.size();
	auto& verts = getVerticesData();
	auto& indices = getIndicesData();
	for (int i = 0; i < n; i++)
	{
		Vertex v;
		v.norm = norm;
		v.position = vertices[i];
		v.u = v.v = 0;
		verts.push_back(v);
		indices.push_back(i);
	}
}

YoungEngine::Geometry::Polygon::Polygon(const std::vector<Vec3D>& vertices, const std::vector<Vec2D>& UVs, const Vec3D& norm, const glm::mat4& model)
	:Shape(model)
{
	if (vertices.size() < 3)
	{
		return;
	}
	int n = vertices.size();
	auto& verts = getVerticesData();
	auto& indices = getIndicesData();
	for (int i = 0; i < n; i++)
	{
		Vertex v;
		v.norm = norm;
		v.position = vertices[i];
		if (i < UVs.size())
		{
			v.u = UVs[i].x;
			v.v = UVs[i].y;
		}
		else
		{
			v.u = 0;
			v.v = 0;
		}
		verts.push_back(v);
		indices.push_back(i);
	}
}
