#pragma once
#include<vector>
#include<glm/glm.hpp>
#include<list>
#include "Plane.h"
namespace YoungEngine::Geometry
{
	class Vec3D;
	/// <summary>
	/// test quad abcd convexity. Notice the order of them. DO NOT let ab cross with cd
	/// </summary>
	bool testQuadConvexity(const Vec3D& a, const Vec3D& b, const Vec3D& c, const Vec3D& d);
	/// <summary>
	/// build a convex hull based on the vertices set. axis is an axis on the plane along which the vertices being sorted.
	/// When build the hull on xy-plane, the axis can be set as [1,0,0] or [0,1,0]. If length of axis is zero empty vector 
	/// will be returned
	/// It is an implementation of Andrew.Alex's algorithm. 
	/// see['Another Efficient Algorithm for Convex HUlls in Two Dimensions.' Information Processing Letters, Vol.9, no.5, pp.216-219,1979.]
	/// </summary>
	std::vector<Vec3D> buildConvexHull2D(std::vector<Vec3D> vertices, Vec3D axis );
	/// <summary>
	/// build a 2D convex hull using quick hull algorithm. 
	/// </summary>
	/// <param name="vertices"></param>
	/// <param name="model">:plane is where the convex hull is generated</param>
	/// <returns>:resultant convex hull</returns>
	std::vector<Vec3D> quickHull2D(std::vector<Vec3D> vertices, Plane p);
	/// <summary>
	/// test whether a vertex is within a convex polygon. MAKE SURE THEY ARE ALL IN ONE PLANE AND verts FORM A POLYGON IN ORDER
	/// if the vertices' count is less then 3 in which situation no polygon can be formed the function will return false
	/// </summary>
	bool testVertexInConvexPolygon2D(const Vec3D& vertex, const std::vector<Vec3D>& verts);
	bool testVertexInConvexPolygon2D(const Vec3D& vertex, const std::list<Vec3D>& verts);
};