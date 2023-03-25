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

	Intensity operator+(Intensity o)
	{
		return Intensity(r + o.GetRed(), g + o.GetGreen(), b + o.GetBlue());
	}
	Intensity operator-(Intensity o)
	{
		return Intensity(r - o.GetRed(), g - o.GetGreen(), b - o.GetBlue());
	}
	Intensity operator/(float o)
	{
		return Intensity(r / o, g /o , b / o);
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

