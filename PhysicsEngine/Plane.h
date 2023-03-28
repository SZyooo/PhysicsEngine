#pragma once
#include "Vec3D.h"
#include <vector>
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
		Vec3D getNorm()const;
		/// <summary>
		/// giving y,z, query x. out parameter valid inform whether the result is valid.
		/// for some cases like p:z = 3, any (x,y) pair can be a result so a random value will be returned and valid will be set false
		/// </summary>
		float queryX(float y, float z,bool& valid) const;
		float queryY(float x, float z, bool &valid) const;
		float queryZ(float x, float y, bool & valid) const;
		std::vector<Vec3D> generateTwoVertices() const;
	};
};