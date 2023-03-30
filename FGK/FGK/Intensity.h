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

	void WriteToConsole();

	Intensity operator+(Intensity o)
	{
		return Intensity(r + o.GetRed(), g + o.GetGreen(), b + o.GetBlue());
	}
	Intensity operator-(Intensity o)
	{
		return Intensity(r - o.GetRed(), g - o.GetGreen(), b - o.GetBlue());
	}
	Intensity operator*(float o)
	{
		return Intensity(r * o, g * o, b * o);
	}
	Intensity operator/(float o)
	{
		return Intensity(r / o, g /o , b / o);
	}
	// Calculate color * color
	Intensity operator*(Intensity o)
	{
		float red = r * o.GetRed();
		float green = g * o.GetGreen();
		float blue = b * o.GetBlue();
		float intensity = red + green + blue;
		return Intensity(intensity, intensity, intensity);
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

