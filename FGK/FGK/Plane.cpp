#include "Plane.h"

Plane::Plane(Vector3 n, Vector3 p, Intensity c)
{
	normal = n;
	point = p;
	color = c;
}

Plane::Plane()
{
	normal = Vector3(0.0f, 0.0f, 0.0f);
	point = Vector3(0.0f, 0.0f, 0.0f);
	color = Intensity(0.0f, 0.0f, 0.0f);
}

Vector3 Plane::GetNormal()
{
	return normal;
}

Vector3 Plane::GetPoint()
{
	return point;
}

Intensity Plane::GetColor()
{
	return color;
}