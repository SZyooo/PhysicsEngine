#pragma once
#include<string>
namespace YoungEngine {
	class Vector3;
	void PrintInfo(std::string& s);
	void PrintVector(const YoungEngine::Vector3& v,const std::string& name = "");
	void PrintFloat(float v);
	void PrintInt(int v);
};
