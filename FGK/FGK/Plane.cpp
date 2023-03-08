#include "Plane.h"

Plane::Plane(Vector3 n, Vector3 p)
{
	normal = n;
	point = p;
}

Vector3 Plane::GetNormal()
{
	return normal;
}

Vector3 Plane::GetPoint()
{
	return point;
}
