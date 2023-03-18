#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include <iostream>

Camera::Camera(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void Camera::Render(Image img, Intensity objectColor, Intensity bgColor)
{
	float pixelWidth = 2.0f / screenHeight;
	float pixelHeight = 2.0f / screenWidth;
	
	for (int i = 0; i < img.GetWidth(); i++)
	{
		for (int j = 0; j < img.GetHeight(); j++)
		{
			float centerX = -1.0f + (i + 0.5f) * pixelWidth;
			float centerY = 1.0f - (j + 0.5f) * pixelHeight;

			Vector3 contactPoint({0.0f, 0.0f, 0.0f});
			Ray ray({ centerX, centerY, 0.0f}, {0.0f, 0.0f, 1.0f});
			Sphere s(5.0f, {0.0f, 0.0f, 10.0f});

			if (ray.intersectsSphere(s, contactPoint))
			{
				img.SetPixel(i, j, objectColor);
			}
			else
			{
				img.SetPixel(i, j, bgColor);
			}
		}
	}
	img.DrawOnWindow();
}
