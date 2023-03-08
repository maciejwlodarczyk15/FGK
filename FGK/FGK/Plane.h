#pragma once
#include "Vector3.h"
class Plane
{
private:
	Vector3 normal;
	Vector3 point;

public:
	Plane(Vector3 n, Vector3 p);
	Vector3 GetNormal();
	Vector3 GetPoint();
};

