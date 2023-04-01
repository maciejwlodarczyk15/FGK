#include "Sphere.h"

Sphere::Sphere(float r, Vector3 point)
{
	radius = r;
	center = point;
}

float Sphere::GetRadius()
{
	return radius;
}

Vector3 Sphere::GetCenter()
{
	return center;
}

Vector3 Sphere::GetNormal(Vector3 contact)
{
	return (contact - center);
}
