#pragma once
namespace YoungEngine
{
	class Point;
	/// <summary>
	/// get the barycentric coordinate for point p in CCW-order triangle {a,b,c}, returned through u,v,w
	/// the tirangle abc and point p will be projected onto an axis-aligned plane where it can have maximum projected area
	/// projection will not change barycentric coordinate u,v and w
	/// </summary>
	void Barycentric(const Point& a, const Point& b, const Point& c, const Point& p, float& u, float& v, float& w);
	/// <summary>
	/// calculate barycentric coordinate for point p with respect to triangle a-b-c using Cramer's rule
	/// $1 = b - a;
	/// $2 = c - a;
	/// $p = p - a;
	/// v * $1 + w * $2 = $p =>
	/// 1.v * dot($1,$1) + w * dot($1,$2) = dot($1,$p)
	/// 2.v * dot($1,$2) + w * dot($2,$2) = dot($2,$p)
	/// </summary>
	void BarycentricCramerRule(const Point& a, const Point& b, const Point& c, const Point& p, float& u, float& v, float& w);
};