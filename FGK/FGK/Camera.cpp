#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include <iostream>

#define M_PI 3.14159265358979323846

Camera::Camera(Vector3 camPos, Vector3 camTarget, Vector3 camUp, float fovDegree, float nPlane, float fPlane, Image img, bool isOrtographic)
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
}

void Camera::Render(Intensity objectColor)
{
    for (int x = 0; x < screenWidth; x++)
    {
        for (int y = 0; y < screenHeight; y++)
        {
            float px = (2.0f * (x + 0.5f) / screenWidth - 1.0f) * aspectRatio * tan(fov / 2.0f);
            float py = (1.0f - 2.0f * (y + 0.5f) / screenHeight) * tan(fov / 2.0f);
            
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
                Vector3 rayOrigin = cameraPosition + Vector3(1,0,0) * px + Vector3(0,1,0) * py;
                ray = Ray(rayOrigin, rayDir);
            }

            Sphere s(1.0f, Vector3(0.0f, 0.0f, -5.0f));
            Vector3 contactPoint;
            if (ray.intersectsSphere(s, contactPoint))
            {
                img.SetPixel(x, y, objectColor);
            }
        }
    }
    img.DrawOnWindow();
}
