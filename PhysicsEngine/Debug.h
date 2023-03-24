#pragma once
#include<string>
namespace YoungEngine {
	class Vector3;
	class Vertex;
	void PrintInfo(std::string& s);
	void PrintVector(const Vector3& v,const std::string& name = "");
	void PrintVector(const Vertex& v, const std::string& name = "");
	void PrintFloat(float v);
	void PrintInt(int v);
};
