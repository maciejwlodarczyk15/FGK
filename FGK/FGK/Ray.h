#pragma once
#include "Vector3.h"
#include "Sphere.h"

class Ray
{
private:
	Vector3 origin;
	Vector3 direction;

public:
	Ray(Vector3 point, Vector3 direct);

	bool intersectsSphere(Sphere sphere, Vector3& contactPoint);
};

