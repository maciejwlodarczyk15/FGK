#include "Intensity.h"
#include <iostream>

Intensity::Intensity()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
}

Intensity::Intensity(float r, float g, float b)
{
	this->r = std::max(std::min(r, 1.0f), 0.0f);
	this->g = std::max(std::min(g, 1.0f), 0.0f);
	this->b = std::max(std::min(b, 1.0f), 0.0f);
}

Intensity::Intensity(float r, float g)
{
	this->r = std::max(std::min(r, 1.0f), 0.0f);
	this->g = std::max(std::min(g, 1.0f), 0.0f);
	b = 0.0f;
}

Intensity::Intensity(float r)
{
	this->r = std::max(std::min(r, 1.0f), 0.0f);
	g = 0.0f;
	b = 0.0f;
}

//Intensity::Intensity(Vector3 newVector)
//{
//	this->r = newVector.x;
//	this->g = newVector.y;
//	this->b = newVector.z;
//}

float Intensity::GetRed()
{
	return r;
}

float Intensity::GetGreen()
{
	return g;
}

float Intensity::GetBlue()
{
	return b;
}

void Intensity::WriteToConsole()
{
	std::cout << "(r: " << r << ", g: " << g << ", b: " << b << ")";
}
