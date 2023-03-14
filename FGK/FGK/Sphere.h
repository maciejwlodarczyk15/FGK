#pragma once
#include "Vector.h"

class Sphere
{
private:
	float radius;
	Vector3 center;

public:
	Sphere(float r, Vector3 point);
	float GetRadius();
	Vector3 GetCenter();
};

