#pragma once
#include<string>
namespace YoungEngine {
	class Vector3;
	class Point;
	void PrintInfo(std::string& s);
	void PrintVector(const Vector3& v,const std::string& name = "");
	void PrintVector(const Point& v, const std::string& name = "");
	void PrintFloat(float v);
	void PrintInt(int v);
};
