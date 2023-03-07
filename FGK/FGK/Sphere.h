#pragma once
#include "Vector3.h"

class Sphere
{
private:
	float radius;
	Vector3 center;

public:
	Sphere(float r, Vector3 point);
	Vector3 GetCenter();
	float GetRadius();
};

