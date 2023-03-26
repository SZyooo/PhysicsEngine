#include "ToolFuncs.h"
#include "Vec3D.h"
#include <functional>
#include <algorithm>
#include <stack>
namespace YoungEngine::Geometry
{

	bool testQuadConvexity(const Vec3D& a, const Vec3D& b, const Vec3D& c, const Vec3D& d)
	{
		Vec3D bd = d - b;
		Vec3D bda = bd.cross(a - b);
		Vec3D bdc = bd.cross(c - b);
		if (bda.dot(bdc) >= 0) return false;
		Vec3D ac = c - a;
		Vec3D acb = ac.cross(b - a);
		Vec3D acd = ac.cross(d - a);
		return acb.dot(acd) < 0;
	}
	std::vector<Vec3D> buildConvexHull2D(std::vector<Vec3D> vertices, Vec3D axis = { 1,0,0 })
	{
		if (axis == Vec3D{0, 0, 0})
		{
			return {};
		}
		if (vertices.size() < 3)
		{
			return {};
		}
		std::vector<Vec3D> res;
		std::function<bool(const Vec3D&, const Vec3D&)> cmp = [&axis](const Vec3D& v1, const Vec3D& v2)->bool
		{
			return v1.dot(axis) < v2.dot(axis);
		};
		std::sort(vertices.begin(),vertices.end(),cmp);
		float EPSILON = 0.00005;
		//avoid zero vector
		if (vertices[0] == Vec3D(0, 0, 0))
		{
			vertices[0] = Vec3D(EPSILON, EPSILON, EPSILON);
		}
		std::stack<Vec3D> stk;
		Vec3D ref = vertices[0].cross(axis);
		//upper
		for (int i = 0; i < vertices.size(); i++)
		{
			if (stk.size() < 2)
			{
				stk.push(vertices[i]);
				continue;
			}
			Vec3D top = stk.top();
			stk.pop();
			Vec3D second = stk.top();
			stk.pop();
			Vec3D v1 = top - second;
			Vec3D v2 = vertices[i] - top;
			bool addSecond = true;
			while ((v1.cross(v2)).dot(ref) < 0)
			{
				top = second;
				if (stk.size() == 0)
				{
					addSecond = false;
					break;
				}
				second = stk.top();
				v1 = top - second;
				v2 = vertices[i] - top;
				stk.pop();
			}
			if (addSecond)
			{
				stk.push(second);
			}
			stk.push(top);
			stk.push(vertices[i]);
		}
		while (stk.empty() == false)
		{
			res.push_back(stk.top());
			stk.pop();
		}
		//bottom
		for (int i = 0; i < vertices.size(); i++)
		{
			if (stk.size() < 2)
			{
				stk.push(vertices[i]);
				continue;
			}
			Vec3D top = stk.top();
			stk.pop();
			Vec3D second = stk.top();
			stk.pop();
			Vec3D v1 = top - second;
			Vec3D v2 = vertices[i] - top;
			bool addSecond = true;
			while ((v1.cross(v2)).dot(ref) > 0)
			{
				top = second;
				if (stk.size() == 0)
				{
					addSecond = false;
					break;
				}
				second = stk.top();
				v1 = top - second;
				v2 = vertices[i] - top;
				stk.pop();
			}
			if (addSecond)
			{
				stk.push(second);
			}
			stk.push(top);
			stk.push(vertices[i]);
		}
		stk.pop();
		std::stack<Vec3D> temp;
		while (stk.empty() == false)
		{
			temp.push(stk.top());
			stk.pop();
		}
		temp.pop();
		while (temp.empty() == false)
		{
			res.push_back(temp.top());
			temp.pop();
		}
		return res;
	}

}