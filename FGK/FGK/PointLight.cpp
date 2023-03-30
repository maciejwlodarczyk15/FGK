#include "PointLight.h"

PointLight::PointLight(Vector3 pos, Intensity col, float intensity, float range, float constant, float linear, float quadratic)
{
	position = pos;
	color = col;
	this->intensity = intensity;
	this->range = range;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

PointLight::PointLight()
{
	position = Vector3(0.0f, 0.0f, 0.0f);
	color = Intensity(1.0f, 1.0f, 1.0f);
	intensity = 1.0f;
	range = 1.0f;
	constant = 1.0f;
	linear = 1.0f;
	quadratic = 1.0f;
}

Vector3 PointLight::GetPosition()
{
	return position;
}

Intensity PointLight::GetColor()
{
	return color;
}

float PointLight::GetIntensity()
{
	return intensity;
}

float PointLight::GetRange()
{
	return range;
}

float PointLight::GetConstant()
{
	return constant;
}

float PointLight::GetLinear()
{
	return linear;
}

float PointLight::GetQuadratic()
{
	return quadratic;
}
