#pragma once

#include "Vector.h"
#include "Intensity.h"

class PointLight
{
private:
	Vector3 position;
	Intensity color;
	float intensity;
	float range;
	float constant;
	float linear;
	float quadratic;

public:
	PointLight(Vector3 pos, Intensity col, float intensity, float range, float constant, float linear, float quadratic);
	PointLight();

	Vector3 GetPosition();
	Intensity GetColor();
	float GetIntensity();
	float GetRange();
	float GetConstant();
	float GetLinear();
	float GetQuadratic();
};

