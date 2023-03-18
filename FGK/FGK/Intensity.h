#pragma once
class Intensity
{
protected:
	float r, g, b;

public:
	Intensity();
	Intensity(float r, float g, float b);
	Intensity(float r, float g);
	Intensity(float r);

	float GetRed();
	float GetGreen();
	float GetBlue();
};

