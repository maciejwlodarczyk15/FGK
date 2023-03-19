#pragma once
#include "Intensity.h"

class Image
{
private:
	int width;
	int	height;
	int size;
	Intensity *pixels;

public:
	Image(int w, int h);

	void SetSize(int w, int h);
	void SetPixel(int x, int y, Intensity intensity);
	void FillImage(Intensity intensity);
	void DrawOnWindow();
	int GetWidth();
	int GetHeight();
};

