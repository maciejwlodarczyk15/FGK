#pragma once
#include "Vector.h"
#include "Intensity.h"

class Sphere
{
private:
	float radius;
	Vector3 center;
	int state;
	Intensity color;

public:
	Sphere(float r, Vector3 point, int s, Intensity c);
	Sphere() : radius(0.0f), center(Vector3(0.0f, 0.0f, 0.0f)), state(0) {}
	float GetRadius();
	Vector3 GetCenter();
	int GetState();
	Intensity GetColor();
	Vector3 GetNormal(Vector3 contact);
};

