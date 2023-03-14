#include "Triangle.h"
#include <corecrt_math.h>
#include <utility>

Triangle::Triangle(Vector3 vert1, Vector3 vert2, Vector3 vert3, Vector4 color1, Vector4 color2, Vector4 color3, Buffer mBuffer, Buffer dBuffer)
{
	v1 = vert1;
	v2 = vert2;
	v3 = vert3;
	c1 = color1;
	c2 = color2;
	c3 = color3;
	mainBuffer = mBuffer;
	depthBuffer = dBuffer;

	int w = mBuffer.GetWidth();
	int h = mBuffer.GetHeight();

	float x1 = (v1.x + 1.0f) * w * 0.5f;
	float x2 = (v2.x + 1.0f) * w * 0.5f;
	float x3 = (v3.x + 1.0f) * w * 0.5f;
	float y1 = (v1.y + 1.0f) * h * 0.5f;
	float y2 = (v2.y + 1.0f) * h * 0.5f;
	float y3 = (v3.y + 1.0f) * h * 0.5f;

	// Rectangle search
	int minX = std::min((int)x1, std::min((int)x2, (int)x3));
	int maxX = std::max((int)x1, std::max((int)x2, (int)x3));
	int minY = std::min((int)y1, std::min((int)y2, (int)y3));
	int maxY = std::max((int)y1, std::max((int)y2, (int)y3));

	// Edge cutting
	minX = std::max(minX, 0);
	maxX = std::min(maxX, w - 1);
	minY = std::max(minY, 0);
	maxY = std::min(maxY, h - 1);

	float dx13 = x1 - x3;
	float dx23 = x2 - x3;
	float dx32 = x3 - x2;
	float dy23 = y2 - y3;
	float dy13 = y1 - y3;
	float dy31 = y3 - y1;

	float dy12 = y1 - y2;
	float dx12 = x1 - x2;
	float dx31 = x3 - x1;

	bool tl1 = false;
	bool tl2 = false;
	bool tl3 = false;

	if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) tl1 = true;
	if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) tl2 = true;
	if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) tl3 = true;

	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			float f1 = (x1 - x2) * (y - y1) - (y1 - y2) * (x - x1);
			float f2 = (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2);
			float f3 = (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3);

			float lam1 = ((((dy23) * (x - x3)) + ((dx32) * (y - y3))) / (((dy23) * (dx13)) + ((dx32) * (dy13))));
			float lam2 = ((((dy31) * (x - x3)) + ((dx13) * (y - y3))) / (((dy31) * (dx23)) + ((dx13) * (dy23))));
			float lam3 = 1 - lam1 - lam2;

			float depth =
				(lam1 * v1.z + lam2 * v2.z + lam3 * v3.z);

			bool topleft1;
			bool topleft2;
			bool topleft3;

			// Top-left edge
			if (tl1) topleft1 = f1 >= 0;
			else topleft1 = f1 > 0;

			if (tl2) topleft2 = f2 >= 0;
			else topleft2 = f2 > 0;

			if (tl3) topleft3 = f3 >= 0;
			else topleft3 = f3 > 0;

			if (topleft1 && topleft2 && topleft3)
			{
				Vector4 cumulative = c1 * lam1 + c2 * lam2 + c3 * lam3;
				float r = cumulative.x * 255;
				float g = cumulative.y * 255;
				float b = cumulative.z * 255;
				float a = cumulative.w * 255;
				unsigned int colorValue = ((unsigned int)a << 24) | ((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b;

				// Z-buffer
				if (depth < depthBuffer.color[y * w + x])
				{
					mainBuffer.color[y * w + x] = colorValue;
					depthBuffer.color[y * w + x] = depth;
				}
			}
		}
	}
}
