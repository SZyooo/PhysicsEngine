#pragma once
#include "Vec3D.h"
namespace YoungEngine::Geometry
{
	/// <summary>
	/// p*n = d;
	/// </summary>
	class Plane
	{
		Vec3D norm;
		float d;
	public:
		Plane(const Vec3D& norm, float d);
		/// <summary>
		/// construct a plane through three non coplanar vertex. the norm will be constructed assuming they are in CCW order
		/// </summary>
		Plane(const Vec3D& p1, const Vec3D& p2, const Vec3D& p3);
	};
};