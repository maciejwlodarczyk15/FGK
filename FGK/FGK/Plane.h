#pragma once
#include "Vector.h"
#include "Intensity.h"

class Plane
{
private:
	Vector3 normal;
	Vector3 point;
	Intensity color;

public:
	Plane(Vector3 n, Vector3 p, Intensity c);
	Plane();

	Vector3 GetNormal();
	Vector3 GetPoint();
	Intensity GetColor();
};

