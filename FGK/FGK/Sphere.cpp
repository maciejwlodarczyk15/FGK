#include "Sphere.h"

Sphere::Sphere(float r, Vector3 point)
{
	radius = r;
	center = point;
}

Vector3 Sphere::GetCenter()
{
	return center;
}

float Sphere::GetRadius()
{
	return radius;
}
