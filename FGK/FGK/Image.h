#pragma once
#include "Intensity.h"

class Image
{
private:
	int width, height;
	Intensity *pixels;

public:
	Image(int w, int h);
	~Image();

	void SetPixel(int x, int y, Intensity intensity);
	void FillImage(Intensity intensity);
	void DrawOnWindow();
	int GetWidth();
	int GetHeight();
};

