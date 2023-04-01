#pragma once

#include "Vector.h"

class Intensity : Vector3
{
protected:
	float r, g, b;

public:
	Intensity();
	Intensity(float r, float g, float b);
	Intensity(float r, float g);
	Intensity(float r);
	//Intensity(Vector3 newVector);

	float GetRed();
	float GetGreen();
	float GetBlue();

	void WriteToConsole();

	Intensity operator+(Intensity o)
	{
		float new_r = r + o.GetRed();
		float new_g = g + o.GetGreen();
		float new_b = b + o.GetBlue();
		if (new_r > 1.0f) new_r = 1.0f;
		if (new_g > 1.0f) new_g = 1.0f;
		if (new_b > 1.0f) new_b = 1.0f;

		return Intensity(new_r, new_g, new_b);
	}
	Intensity operator-(Intensity o)
	{
		float new_r = r + o.GetRed();
		float new_g = g + o.GetGreen();
		float new_b = b + o.GetBlue();
		if (new_r < 0.0f) new_r = 0.0f;
		if (new_g < 0.0f) new_g = 0.0f;
		if (new_b < 0.0f) new_b = 0.0f;

		return Intensity(new_r, new_g, new_b);
	}
	Intensity operator*(float o)
	{
		return Intensity(r * o, g * o, b * o);
	}
	Intensity operator/(float o)
	{
		return Intensity(r / o, g /o , b / o);
	}
	Intensity operator*(Vector3 o)
	{
		return Intensity(r * o.x, g * o.y, b * o.z);
	}
	// Calculate color * color
	Intensity operator*(Intensity o)
	{
		float red = r * o.GetRed();
		float green = g * o.GetGreen();
		float blue = b * o.GetBlue();
		//float intensity = red + green + blue;
		return Intensity(red, green, blue);
	}
	bool operator !=(Intensity o)
	{
		if (r == o.GetRed() && g == o.GetGreen() && b == o.GetBlue())
		{
			return false;
		}
		else 
		{
			return true;
		}
	}
};

