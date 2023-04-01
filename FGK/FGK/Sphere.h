#pragma once
#include "Vector.h"

class Sphere
{
private:
	float radius;
	Vector3 center;

public:
	Sphere(float r, Vector3 point);
	Sphere() : radius(0.0f), center(Vector3(0.0f, 0.0f, 0.0f)) {}
	float GetRadius();
	Vector3 GetCenter();
	Vector3 GetNormal(Vector3 contact);
};

