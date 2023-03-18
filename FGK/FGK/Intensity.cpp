#include "Intensity.h"

Intensity::Intensity()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
}

Intensity::Intensity(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Intensity::Intensity(float r, float g)
{
	this->r = r;
	this->g = g;
	b = 0.0f;
}

Intensity::Intensity(float r)
{
	this->r = r;
	g = 0.0f;
	b = 0.0f;
}

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
