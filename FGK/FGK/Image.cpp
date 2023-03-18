#include "Image.h"

Image::Image(int w, int h)
{
	width = w;
	height = h;
	pixels = new Intensity[width * height];
}

Image::~Image()
{
	delete[] pixels;
}

void Image::SetPixel(int x, int y, Intensity intensity)
{
	int index = y * width + x;
	pixels[index] = intensity;
}

void Image::DrawOnWindow()
{

}
