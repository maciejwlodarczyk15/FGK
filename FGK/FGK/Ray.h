#pragma once
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

class Ray
{
private:
	Vector3 origin;
	Vector3 direction;

public:
	Ray(Vector3 point, Vector3 direct);

	Vector3 GetDirection();

	bool intersectsSphere(Sphere sphere, Vector3& contactPoint);
	bool intersectPlane(Plane plane, Vector3& contactPoint);
	bool intersectTriangle(Triangle triangle, Vector3& contactPoint);
};

