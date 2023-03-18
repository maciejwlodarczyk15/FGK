#pragma once

#include "Image.h"

class Camera
{
private:
	int screenWidth;
	int screenHeight;

public:
	Camera(int screenWidth, int screenHeight);
	void Render(Image img, Intensity objectColor, Intensity bgColor);
};

