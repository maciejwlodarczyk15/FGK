#pragma once

#include "Vector.h"

class Triangle
{
private:
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;
	Vector3 vn;

public:
	Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 vn);
	Triangle() : v1(0.0f, 0.0f, 0.0f), v2(0.0f, 0.0f, 0.0f), v3(0.0f, 0.0f, 0.0f), vn(0.0f, 0.0f, 0.0f) {}

	Vector3 GetVn();
	Vector3 GetV1();
	Vector3 GetV2();
	Vector3 GetV3();
};

