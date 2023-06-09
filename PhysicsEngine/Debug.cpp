#include "Debug.h"
#include<iostream>
#include"Vector3.h"
#include"Point.h"
#define DEBUGGING
#define CONSOLE_OUTPUT

using namespace YoungEngine;

void YoungEngine::PrintInfo(std::string& s)
{
#ifdef DEBUGGING
	std::cout << s << std::endl;
#endif // DEBUGGING
}

void YoungEngine::PrintVector(const YoungEngine::Vector3& v, const std::string& name)
{
#ifdef CONSOLE_OUTPUT
	std::cout << name << (name.length() > 0 ? "=" : "") << "[" << v.x << "," << v.y << "," << v.z << "]" << std::endl;
#else

#endif // CONSOLE_OUTPUT

}

void YoungEngine::PrintVector(const Point& v, const std::string& name)
{
#ifdef CONSOLE_OUTPUT
	std::cout << name <<(name.length()>0?"=":"")<<"[" << v.x() << "," << v.y() << "," << v.z() << "]" << std::endl;
#endif // CONSOLE_OUTPUT

}

void YoungEngine::PrintFloat(float v)
{
#ifdef DEBUGGING
	std::cout << v << std::endl;
#endif // DEBUGGING

}

void YoungEngine::PrintInt(int v)
{
#ifdef DEBUGGING
	std::cout << v << std::endl;
#endif // DEBUGGING

}

