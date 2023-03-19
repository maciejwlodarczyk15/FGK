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
	for (int x = 0; x < screenWidth; x++)
	{
		for (int y = 0; y < screenHeight; y++)
		{
			float px = (x - screenWidth / 2.0f) / screenWidth;
			float py = -(y - screenHeight / 2.0f) / screenHeight;
			Vector3 rayDir(px, py, 1.0f);
			rayDir.Normalize();
			Ray ray(Vector3(0.0f, 0.0f, 0.0f), rayDir);

			Sphere s(1.0f, { 0.0f, 0.0f, 10.0f });
			Vector3 contactPoint({ 0.0f, 0.0f, 0.0f });
			if (ray.intersectsSphere(s, contactPoint))
			{
				img.SetPixel(x, y, objectColor);
			}
		}
	}

	img.DrawOnWindow();
}
