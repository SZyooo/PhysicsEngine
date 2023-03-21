#include "Debug.h"
#include<iostream>
#include"Vector3.h"

#define DEBUGGING
#define CONSOLE_OUTPUT

using namespace YoungEngine;

void YoungEngine::PrintInfo(std::string& s)
{
#ifdef DEBUGGING
	std::cout << s << std::endl;
#endif // DEBUGGING
}

void YoungEngine::PrintVector(const YoungEngine::Vector3& v)
{
#ifdef CONSOLE_OUTPUT
	std::cout << "[" << v.x << "," << v.y << "," << v.z << "]" << std::endl;
#else

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

