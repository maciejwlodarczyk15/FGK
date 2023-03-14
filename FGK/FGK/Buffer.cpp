#define _CRT_SECURE_NO_WARNINGS 1
#include "Buffer.h"
#include <fstream>

Buffer::Buffer()
{
	SetSize(0, 0);
}

Buffer::Buffer(int weight, int height)
{
	SetSize(weight, height);
}

bool Buffer::Save()
{
	unsigned short header[9] = {
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0100, 0x0100,
		0x0820 };

	FILE* f = fopen("Z.tga", "wb+");
	if (NULL == f) return false;

	header[6] = w;
	header[7] = h;

	fwrite(header, 2, 9, f);
	fwrite(color, 4, size, f);
	return true;
}

int Buffer::GetWidth()
{
	return w;
}

int Buffer::GetHeight()
{
	return h;
}

void Buffer::SetSize(int width, int height)
{
	w = width;
	h = height;
	size = w * h;
	color = new unsigned int[size];
}

void Buffer::ClearColor(unsigned int pickedColor)
{
	for (unsigned int i = 0; i < size; i++)
	{
		color[i] = pickedColor;
	}
}