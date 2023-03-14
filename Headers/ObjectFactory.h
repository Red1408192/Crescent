#pragma once
#include "Object.h"

static class ObjectFactory
{
public:
	static Object CreateCube(std::string name);
	static Object CreateTriangle(std::string name);
	static Object CreateHexagon(std::string name);
	static Object CreatePiramid(std::string name);
};

