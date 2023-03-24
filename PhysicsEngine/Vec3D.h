#pragma once
namespace YoungEngine::Geometry
{
	class Vec3D
	{
	public:
		float x, y, z;
		Vec3D(float x = 0, float y = 0, float z = 0);
		Vec3D componentProduct(const Vec3D& v)const;
	private:
		float padding = 1;
	};
};