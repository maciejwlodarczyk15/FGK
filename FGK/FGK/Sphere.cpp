#include "Sphere.h"

Sphere::Sphere(float r, Vector3 point, int s, Intensity c)
{
	radius = r;
	center = point;
	state = s;
	color = c;
}

float Sphere::GetRadius()
{
	return radius;
}

Vector3 Sphere::GetCenter()
{
	return center;
}

int Sphere::GetState()
{
	return state;
}

Intensity Sphere::GetColor()
{
	return color;
}

Vector3 Sphere::GetNormal(Vector3 contact)
{
	return (contact - center);
}
