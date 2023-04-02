#include "ToolFuncs.h"
#include "Vec3D.h"
#include <functional>
#include <algorithm>
#include <stack>
#include <limits>
#include "Debug.h"
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
		//removing leading zero vectors
		int start = 0;
		Vec3D zero{ 0,0,0 };
		bool hasZero = false;
		while (start < vertices.size() && vertices[start] == zero)
		{
			start++;
			hasZero = true;
		}
		if (hasZero)
		{
			//all are zero vectors
			if (start == vertices.size() - 1)
			{
				return { vertices[0] };
			}
			if (vertices[start + 1].x < EPSILON)
			{
				vertices[start].x = vertices[start + 1].x * 0.5;
			}
			else {
				vertices[start].x = EPSILON;
			}
			if (vertices[start + 1].y < EPSILON)
			{
				vertices[start].y = vertices[start + 1].y * 0.5;
			}
			else
			{
				vertices[start].y = EPSILON;
			}
			if (vertices[start + 1].z < EPSILON)
			{
				vertices[start].z = vertices[start + 1].z * 0.5;
			}
			else
			{
				vertices[start].z = EPSILON;
			}
		}


		std::stack<Vec3D> stk;
		Vec3D ref = vertices[0].cross(axis);
		//upper
		for (int i = start; i < vertices.size(); i++)
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
		for (int i = start; i < vertices.size(); i++)
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

	std::vector<Vec3D> quickHull2D(std::vector<Vec3D> vertices, Plane p)
	{
		if (vertices.size() < 3)
		{
			return {};
		}
		std::list<Vec3D> vList;
		std::list<Vec3D>::iterator left=vList.end(), right= vList.end(), up= vList.end(), bottom= vList.end();
		float l = std::numeric_limits<float>::max();
		float r = std::numeric_limits<float>::lowest();
		float u = std::numeric_limits<float>::lowest();
		float b = std::numeric_limits<float>::max();
		auto ps = p.generateTwoVertices();
		Vec3D v1 = (ps[1] - ps[0]).normalize();
		Vec3D v2 = (p.getNorm().cross(v1)).normalize();
		for(int i= 0; i < vertices.size(); i++)
		{
			auto& v = vertices[i];
			Vec3D vec = v - ps[0];
			glm::vec3 vert(vec.dot(v1),vec.dot(v2),0);
			auto end = vList.insert(vList.end(),Vec3D(vert.x,vert.y,vert.z));
			if (vert.x < l)
			{
				left = end;
				l = vert.x;
			}
			if (vert.x > r)
			{
				right = end;
				r = vert.x;
			}
			if (vert.y > u)
			{
				up = end;
				u = vert.y;
			}
			if (vert.y < b)
			{
				bottom = end;
				b = vert.y;
			}
		}
		std::list<Vec3D> resList;
		auto tackleDegeneratedSituation = [&vList, &resList](std::list<Vec3D>::iterator& it1, std::list<Vec3D>::iterator& it2)->bool
		{
			auto left = it1;
			auto right = it2;
			Vec3D axle = *right - *left;
			resList.push_back(*left);
			vList.erase(left);
			resList.push_back(*right);
			vList.erase(right);
			//a bug here that it1 and it2 have nonsense value
			auto rb = resList.begin(); rb++;
			auto lv = vList.end();
			for (auto it = vList.begin(); it != vList.end(); it++)
			{
				Vec3D v = *it - *left;
				if ((v.cross(axle).equalTo({ 0,0,0 })).all())
				{
					continue;
				}
				else
				{
					lv = it;
					break;
				}
			}
			//all vertices are aligned on one single line
			if (lv == vList.end())
			{
				return false;
			}
			resList.insert(rb, *lv);
			vList.erase(lv);
			Vec3D ref = (*lv - *left).cross(axle);
			//find another vertex on the other side of axle
			auto rv = vList.end();
			for (auto it = vList.begin(); it != vList.end(); it++)
			{
				Vec3D v = *it - *left;
				//parallel
				if ((v.cross(axle).equalTo({ 0,0,0 })).all())
				{
					continue;
				}
				else
				{
					// on the other side
					if (v.cross(axle).dot(ref) < 0)
					{
						rv = it;
						break;
					}
				}
			}
			//found
			if (rv != vList.end())
			{
				resList.push_back(*rv);
				vList.erase(rv);
			}
			return true;
		};

		if (left == up)
		{
			if (right != bottom)
			{
				resList.push_back(*left);
				resList.push_back(*right);
				resList.push_back(*bottom);
				vList.erase(left);
				vList.erase(right);
				vList.erase(bottom);
			}
			//degenerated, choose another two vertex randomly
			else
			{
				if (tackleDegeneratedSituation(left, right) == false)
				{
					return {};
				}
			}
		}
		else if (up == right)
		{
			if (left != bottom)
			{
				resList.push_back(*left);
				resList.push_back(*up);
				resList.push_back(*bottom);
				vList.erase(left);
				vList.erase(up);
				vList.erase(bottom);
			}
			else
			{
				if (tackleDegeneratedSituation(left, right) == false)
				{
					return {};
				}
			}
		}
		else if (right == bottom)
		{
			if (up != left)
			{
				resList.push_back(*left);
				resList.push_back(*up);
				resList.push_back(*bottom);
				vList.erase(left);
				vList.erase(up);
				vList.erase(bottom);
			}
			else
			{
				if (tackleDegeneratedSituation(left, right) == false)
				{
					return {};
				}
			}
		}
		else if (bottom == left)
		{
			if (up != right)
			{
				resList.push_back(*left);
				resList.push_back(*up);
				resList.push_back(*right);
				vList.erase(left);
				vList.erase(up);
				vList.erase(right);
			}
			else
			{
				if (tackleDegeneratedSituation(left, right) == false)
				{
					return {};
				}
			}
		}
		else
		{
			resList.push_back(*left);
			resList.push_back(*up);
			resList.push_back(*right);
			resList.push_back(*bottom);
			vList.erase(left);
			vList.erase(up);
			vList.erase(right);
			vList.erase(bottom);
		}
		while (vList.size() > 0)
		{
			//remove vertices has been in the polygon
			for (auto it = vList.begin(); it != vList.end();)
			{
				if (testVertexInConvexPolygon2D(*it, resList))
				{
					it = vList.erase(it);
				}
				else
				{
					it++;
				}
			}
			if (vList.size() == 0)
			{
				break;
			}
			auto upAndRightMost = [](const Vec3D& v1, const Vec3D& v2, const Vec3D& vInside, const std::list<Vec3D>& candidates)
				->std::list<Vec3D>::const_iterator {
				Vec3D v1v2 = v2 - v1;
				Vec3D ref = v1v2.cross(vInside - v1);
				Vec3D n = Vec3D(-v1v2.y, v1v2.x, 0);
				float right = std::numeric_limits<float>::lowest();
				float d = std::numeric_limits<float>::lowest();
				std::list<Vec3D>::const_iterator iter = candidates.end();
				for (auto it = candidates.begin(); it != candidates.end(); it++)
				{
					Vec3D v1p = *it - v1;
					Vec3D vec = v1p.cross(v1v2);
					//outside the edge
					if (vec.dot(ref) >= 0)
					{
						float dis = fabs(v1p.dot(n));
						if (dis > d || (dis == d && it->x > right))
						{
							right = it->x;
							d = dis;
							iter = it;
						}
					}
				}
				return iter;
			};
			for (auto it = resList.begin(); it != resList.end(); it++)
			{
				Vec3D p1 = *it;
				it++;
				if (it == resList.end())
				{
					it = resList.begin();
				}
				Vec3D p2 = *it;
				it++;
				if (it == resList.end())
				{
					it = resList.begin();
				}
				Vec3D refP = *it;
				if (it == resList.begin())
				{
					it = resList.end();
					it--;
				}
				else
				{
					it--;
				}
				if (it == resList.begin())
				{
					it = resList.end();
					it--;
				}
				else
				{
					it--;
				}
				auto iter = upAndRightMost(p1, p2, refP, vList);
				if (iter != vList.end())
				{
					it++;
					it = resList.insert(it, *iter);
					vList.erase(iter);
					for (auto it = vList.begin(); it != vList.end();)
					{
						if (testVertexInConvexPolygon2D(*it, resList))
						{
							it = vList.erase(it);
						}
						else
						{
							it++;
						}
					}
				}
			}
		}
		std::vector<Vec3D> res;
		for (auto& vt : resList)
		{
			Vec3D v = vt.x * v1 + vt.y * v2 + ps[0];
			res.push_back(v);
		}
		return res;
	}

	bool testVertexInConvexPolygon2D(const Vec3D& vertex, const std::vector<Vec3D>& verts)
	{
		int n = verts.size();
		if (n < 3)
		{
			return false;
		}
		
		for (int i = 0; i < n; i++) {
			Vec3D v1 = verts[(i + 1) % n] - verts[i];
			Vec3D v2 = verts[(i + 2) % n] - verts[i];
			Vec3D vp = vertex - verts[i];
			if ((v1.cross(v2)).dot(v1.cross(vp)) < 0)
			{
				return false;
			}
		}
		return true;
	}

	bool testVertexInConvexPolygon2D(const Vec3D& vertex, const std::list<Vec3D>& verts)
	{
		int n = verts.size();
		if (n < 3)
		{
			return false;
		}

		for (auto it = verts.begin(); it != verts.end();it++) {
			Vec3D p1 = *it;
			it++;
			if (it == verts.end())
			{
				it = verts.begin();
			}
			Vec3D p2 = *it;
			it++;
			if (it == verts.end())
			{
				it = verts.begin();
			}
			Vec3D p3 = *it;
			if (it == verts.begin())
			{
				it = verts.end();
				it--;
			}
			else
			{
				it--;
			}
			if (it == verts.begin())
			{
				it = verts.end();
				it--;
			}
			else
			{
				it--;
			}
			if ((p2 - p1).cross(p3 - p1).dot((vertex - p1).cross(p2 - p1)) > 0)
			{
				return false;
			}
		}
		return true;
	}


}