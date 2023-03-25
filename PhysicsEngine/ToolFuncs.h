#pragma once
#include<vector>
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
};