#include "Camera.h"
#include "Ray.h"
#include <iostream>
#include <vector>

#define M_PI 3.14159265358979323846

Camera::Camera(Vector3 camPos, Vector3 camTarget, Vector3 camUp, float fovDegree, float nPlane, float fPlane, 
    Image img, Intensity objectColor, Intensity backgroundColor, std::vector<Sphere> spheres, bool isOrtographic)
{
    cameraPosition = camPos;
    cameraTarget = camTarget;
    cameraVecUp = camUp;

    this->img = img;
    screenWidth = img.GetWidth();
    screenHeight = img.GetHeight();
    aspectRatio = (float)screenWidth / (float)screenHeight;

    fov = tan(fovDegree * M_PI / 360.0f);
    nearPlane = nPlane;
    farPlane = fPlane;
    this->isOrtographic = isOrtographic;

    this->objectColor = objectColor;
    this->backgroundColor = backgroundColor;
    this->spheres = spheres;
}

void Camera::Render(int depth)
{
    Sphere s(1.0f, Vector3(0.0f, 0.0f, -5.0f));
    Intensity zero;
    
    int currentDepth = 0;
    int maxDepth = 4;

    bool drawColor = false;

    for (int x = 0; x < screenWidth; x++)
    {
        for (int y = 0; y < screenHeight; y++)
        {

            std::vector<Intensity> allColors;

            for (int i = 0; i < 4; i++)
            {
                float px = (2.0f * (x + (i % 2) * 0.5f) / screenWidth - 1.0f) * aspectRatio * tan(fov / 2.0f);
                float py = (1.0f - 2.0f * (y + (i / 2) * 0.5f) / screenHeight) * tan(fov / 2.0f);

                Vector3 rayDir(px, py, -1.0f);
                rayDir.Normalize();

                if (!isOrtographic)
                {
                    Vector3 cameraDir = (cameraTarget - cameraPosition).Normalize();
                    Vector3 cameraVectorRight = cameraVecUp.Cross(cameraDir).Normalize();
                    Vector3 cameraUpNew = cameraDir.Cross(cameraVectorRight).Normalize();
                    rayDir = (cameraVectorRight * px + cameraUpNew * py + cameraDir / fov).Normalize();
                }

                Ray ray(cameraPosition, rayDir);

                if (isOrtographic)
                {
                    Vector3 rayOrigin = cameraPosition + Vector3(1, 0, 0) * px + Vector3(0, 1, 0) * py;
                    ray = Ray(rayOrigin, rayDir);
                }

                // Check whether to draw object or background
                Vector3 contactPoint;
                for (int i = 0; i < spheres.size(); i++)
                {
                    if (ray.intersectsSphere(spheres[i], contactPoint))
                    {
                        drawColor = true;
                    }
                }
                if (drawColor)
                {
                    allColors.push_back(objectColor);
                }
                else
                {
                    allColors.push_back(backgroundColor);
                }
                drawColor = false;
            }

            // Average color of all the pixels
            Intensity averageColor;
            for (int i = 0; i < allColors.size(); i++)
            {
                averageColor = averageColor + allColors[i];
            }

            averageColor = averageColor / allColors.size();

            for (int i = 1; i < allColors.size(); i++)
            {
                if (allColors[0] - allColors[i] != zero)
                {

                    // DO RECURSIVE PIXEL DIVISION
                }
                else
                {
                    img.SetPixel(x, y, averageColor);
                }
            }
        }
    }
    img.DrawOnWindow();
}