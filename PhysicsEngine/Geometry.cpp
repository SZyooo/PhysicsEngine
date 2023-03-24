#include "Geometry.h"
#include "Point.h"
#include "Vector3.h"
#include "Math.h"

/// <summary>
/// calculates the signed area of triangle formed by (x1,y1),(x2,y2) and (x3,y3) 
/// </summary>
inline float signedArea2D(float x1,float y1,float x2,float y2,float x3,float y3)
{
	//(x1-x2,y1-y2)x(x2-x3,y2-y3)
	return (x1 - x2) * (y2 - y3) - (x2 - x3) * (y1 - y2);
}

void YoungEngine::Barycentric(const Point& a, const Point& b, const Point& c, const Point& p,float& u, float& v, float& w)
{
	Vector3 norm = Cross(a - b, b - c);
	float px = abs(norm.x);
	float py = abs(norm.y);
	float pz = abs(norm.z);
	float wholeSignedAreaInv = 0;
	//onto yz plane
	if (px >= py && px >= pz)
	{
		u = signedArea2D(p.y(), p.z(), b.y(), b.z(), c.y(), c.z());
		v = signedArea2D(a.y(), a.z(), p.y(), p.z(), c.y(), c.z());
		wholeSignedAreaInv = 1.f / norm.x;
	}
	//onto xz plane
	else if (py >= px && py >= pz)
	{
		u = signedArea2D(p.x(), p.z(), b.x(), b.z(), c.x(), c.z());
		v = signedArea2D(a.x(), a.z(), p.x(), p.z(), c.x(), c.z());
		wholeSignedAreaInv = 1.f / -norm.y;
	}
	//onto xy plane
	else {
		u = signedArea2D(p.x(), p.y(), b.x(), b.y(), c.x(), c.y());
		v = signedArea2D(a.x(), a.y(), p.x(), p.y(), c.x(), c.y());
		wholeSignedAreaInv = 1.f / norm.z;
	}
	u *= wholeSignedAreaInv;
	v *= wholeSignedAreaInv;
	w = 1 - u - v;
}

void YoungEngine::BarycentricCramerRule(const Point& A, const Point& B, const Point& C, const Point& P, float& u, float& v, float& w)
{
	Vector3 v0 = B - A;
	Vector3 v1 = C - A;
	Vector3 vp = P - A;
	float a = Dot(v0, v0);
	float b = Dot(v1, v0);
	float c = Dot(v0, v1);
	float d = Dot(v1, v1);
	float e = Dot(vp, v0);
	float f = Dot(vp, v1);
	float denom_inv = 1.f / (a * d - b * c);
	v = (e * d - b * f) * denom_inv;
	w = (a * f - e * c) * denom_inv;
	u = 1 - v - w;
}
