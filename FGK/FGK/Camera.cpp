#include "Camera.h"
#include "Ray.h"
#include <iostream>
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

Camera::Camera(Vector3 camPos, Vector3 camTarget, Vector3 camUp, float fovDegree, float nPlane, float fPlane, int maxDepth,
    Image img, Intensity objectColor, Intensity backgroundColor, 
    std::vector<Sphere> spheres, std::vector<Mesh> meshes, PointLight pLight, bool isOrtographic)
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
    this->maxDepth = maxDepth;
    this->meshes = meshes;
    this->pLight = pLight;
}

void Camera::Render()
{
    int currentDepth = 0;

    for (int x = 0; x < screenWidth; x++)
    {
        for (int y = 0; y < screenHeight; y++)
        {
            float p1x = 2.0f * x / screenWidth - 1.0f;
            float p1y = 1.0f - 2.0f * y / screenHeight;
            float p2x = 2.0f * (x + 0.5f) / screenWidth - 1.0f;
            float p2y = 1.0f - 2.0f * (y + 0.5f) / screenHeight;
            img.SetPixel(x, y, PixelDivider(p1x, p1y, p2x, p2y, currentDepth));
        }
    }
    img.DrawOnWindow();
}

Intensity Camera::PixelDivider(float p1x, float p1y, float p2x, float p2y, int depth) 
{
    Intensity zero;

    std::vector<Intensity> allColors;
    
    std::vector<float> pointsX = { (p1x + p2x) / 2, std::min(p1x, p2x), std::max(p1x, p2x), std::min(p1x, p2x), std::max(p1x, p2x) };
    std::vector<float> pointsY = { (p1y + p2y) / 2, std::min(p1y, p2y), std::min(p1y, p2y), std::max(p1y, p2y), std::max(p1y, p2y) };

    for (int i = 0; i < 5; i++) {
        float px = pointsX.at(i) * aspectRatio * tan(fov / 2.0f);
        float py = pointsY.at(i) * tan(fov / 2.0f);

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
        bool drawColor = false;
        for (int i = 0; i < spheres.size(); i++)
        {
            if (ray.intersectsSphere(spheres[i], contactPoint))
            {
                drawColor = true;
                break;
            }
        } 
        std::vector<Mesh> newMeshes;
        for (int k = 0; k < meshes.size(); k++)
        {
            for (int j = 0; j < meshes[k].GetTriangles().size(); j++)
            {
                if (ray.intersectTriangle(meshes[k].GetTriangles()[j], contactPoint))
                {
                    drawColor = true;
                    break;
                }
            }
            if (drawColor) 
            {
                break;
            }   
        }
        if (drawColor)
        {


            //float r, g, b, cosinus;
            //
            //Vector3 I = ray.GetDirection().Normalize();
            //Vector3 N = ;

            //// Light 
            Vector3 intersectionToLight = (pLight.GetPosition() - contactPoint).Normalize();
            // Calculate length from light to contact point
            float distanceToLight = (pLight.GetPosition() - contactPoint).Length();
            float attenuation = 1.0f / (pLight.GetConstant() + pLight.GetLinear() * distanceToLight + pLight.GetQuadratic() * distanceToLight * distanceToLight);
            Intensity lightColor = pLight.GetColor() * pLight.GetIntensity() * attenuation;
            
            Intensity resultColor = objectColor * lightColor;


            //allColors.push_back(objectColor * lightColor);'
            // 
            //std::cout << "\nC: ";
            //objectColor.WriteToConsole();
            //std::cout << "\nL: ";
            //lightColor.WriteToConsole();
            //std::cout << "\nCL: ";
            //resultColor.WriteToConsole();

            //allColors.push_back(objectColor);
            allColors.push_back(resultColor);
        }
        else
        {
            allColors.push_back(backgroundColor);
        }
        drawColor = false;
    }

    // Average color of all the pixels
    Intensity averageColor;

    for (int i = 1; i < allColors.size(); i++)
    {
        if (allColors[0] - allColors[i] != zero && depth < maxDepth)
        {
            averageColor = averageColor + PixelDivider(pointsX[0], pointsY[0], pointsX[i], pointsY[i], depth + 1);
        }
        else
        {
            averageColor = averageColor + (allColors[0] + allColors[i]) / 2;
        }
    }

    return averageColor / 4;
}